// ThreadOfInputStreamPrint.cpp : implementation file
//

#include "stdafx.h"
#include "StreamProcessing.h"
#include "ThreadOfInputStreamPrint.h"
#include "StreamProcessingDlg.h"


// ThreadOfInputStreamPrint

IMPLEMENT_DYNCREATE(ThreadOfInputStreamPrint, CWinThread)

ThreadOfInputStreamPrint::ThreadOfInputStreamPrint()
{
}

ThreadOfInputStreamPrint::~ThreadOfInputStreamPrint()
{
}

BOOL ThreadOfInputStreamPrint::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int ThreadOfInputStreamPrint::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

UINT ThreadOfInputStreamPrint::runThread(LPVOID param) {
	CStreamProcessingDlg * dlg = (CStreamProcessingDlg*)param;
	while (true) {
		dlg->updataPrintInputStream();
		Sleep(1000);
	}
}

BEGIN_MESSAGE_MAP(ThreadOfInputStreamPrint, CWinThread)
END_MESSAGE_MAP()


// ThreadOfInputStreamPrint message handlers
