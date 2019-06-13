#include "../stdafx.h"

#include "MultiThreads.h"

#include "../execution/ProcessRegister.h"
#include "StreamProcessingDlg.h"
#include "../execution/ExecuteScheduler.h"

//void ThreadOfTimerToPerformCEP::run() {
//	while (true) {
//		std::this_thread::sleep_for(std::chrono::milliseconds(500));
//		//cout << "cep timer" << endl;
//		//set<CEPProcess*> ceps = ExecuteScheduler::getCEPs();
//		set<CEPProcess*> ceps = ProcessRegister::getCEPs();
//		for (CEPProcess * c : ceps) {
//			c->result();
//		}
//	}
//}
//
//std::thread ThreadOfTimerToPerformCEP::runThread() {
//	return std::thread(&ThreadOfTimerToPerformCEP::run, this);
//}

////////////////////////////////////////////////
ThreadOfEventFilter::ThreadOfEventFilter(bool isWithGUI) {
	this->isWithGUI = isWithGUI;
}

void ThreadOfEventFilter::run() {
	EventProcess * eventProcess = ProcessRegister::getProcessOfEventFiltering();
	while (!isStop) {
		Sleep(500);
		EventPtr e = EventGenerator::generateEvent();
		eventProcess->process(e);

		//update the variable of "inputstream_to_display"
		CString cstr(e->toString().c_str());
		if (isWithGUI) {
			CStreamProcessingDlg::inputstream_to_display = cstr + "\r\n" + CStreamProcessingDlg::inputstream_to_display;
			if (CStreamProcessingDlg::inputstream_to_display.GetLength() > 5000)
				CStreamProcessingDlg::inputstream_to_display.Truncate(3000);
		}
	}
}

std::thread ThreadOfEventFilter::runThread() {
	return std::thread(&ThreadOfEventFilter::run, this);
}

void ThreadOfEventFilter::stop() {
	this->isStop = true;
}

/////////////////////////////////////////////////////


void ThreadOfProcessUnit::run() {
	ExecuteScheduler::runProcessQueue();
}

std::thread ThreadOfProcessUnit::runThread() {
	return std::thread(&ThreadOfProcessUnit::run, this);
}

///////////////////////////////////////////////////////