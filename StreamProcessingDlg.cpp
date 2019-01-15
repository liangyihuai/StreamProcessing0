
// StreamProcessingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StreamProcessing.h"
#include "StreamProcessingDlg.h"
#include "afxdialogex.h"

#include "ExecuteScheduler.h"
#include "SpecUtils.h"
#include <thread>
#include "ThreadOfInputStreamPrint.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CString CStreamProcessingDlg::inputstream_to_display;



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStreamProcessingDlg dialog



CStreamProcessingDlg::CStreamProcessingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STREAMPROCESSING_DIALOG, pParent)
{
	//initialize name and value
	event_filter_name = _T("targetData");

	event_filter_rule = _T("If not duplicate(id) & not unusual(speed)\
		\r\nFrom rawData\
		\r\nThen targetData");

	event_capture_name = _T("allytarget");

	event_capture_rule = _T("If target.iff = ally\
		\r\nFrom targetData\
		\r\nThen allytarget");

	cq_name = _T("flyingTarget");

	cq_rule = _T("If iff = ally & speed>500\
		\r\nFrom allytarget\
		\r\nThen flyingTarget");

	cep_name = _T("cepTarget1");

	cep_rule = _T("If exist(flyingTarget)\
		\r\nFrom flyingTarget\
		\r\nThen cepTarget1");

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CStreamProcessingDlg::~CStreamProcessingDlg() {
	delete threadOfInputStream;
}

void CStreamProcessingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_EVENT_FILTER_NAME, event_filter_name);
	DDX_Text(pDX, IDC_EDIT_EVENT_FILTER_RULE, event_filter_rule);
	DDX_Text(pDX, IDC_EDIT_CAPTURE_NAME, event_capture_name);
	DDX_Text(pDX, IDC_EDIT_CAPTURE_RULE, event_capture_rule);
	DDX_Text(pDX, IDC_EDIT_CQ_NAME, cq_name);
	DDX_Text(pDX, IDC_EDIT_CQ_RULE, cq_rule);
	DDX_Text(pDX, IDC_EDIT_CEP_NAME, cep_name);
	DDX_Text(pDX, IDC_EDIT_CEP_RULE, cep_rule);
	DDX_Control(pDX, IDC_COMBO_SINK, sink_combobox);
}

BEGIN_MESSAGE_MAP(CStreamProcessingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_CEP_RULE, &CStreamProcessingDlg::OnEnChangeEditCepRule)
	ON_BN_CLICKED(IDC_BUTTON_EVENT_FILTER_ADD, &CStreamProcessingDlg::OnBnClickedButtonEventFilterAdd)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE_ADD, &CStreamProcessingDlg::OnBnClickedButtonCaptureAdd)
	ON_BN_CLICKED(IDC_BUTTON_CQ_ADD, &CStreamProcessingDlg::OnBnClickedButtonCqAdd)
	ON_BN_CLICKED(IDC_BUTTON_CEP_ADD, &CStreamProcessingDlg::OnBnClickedButtonCepAdd)
	ON_BN_CLICKED(IDC_BUTTON_START, &CStreamProcessingDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CStreamProcessingDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_STREAM, &CStreamProcessingDlg::OnBnClickedButtonInputStream)
END_MESSAGE_MAP()


// CStreamProcessingDlg message handlers

BOOL CStreamProcessingDlg::OnInitDialog(){

	CDialogEx::OnInitDialog();

	//initialize combo box for data sinking.
	sink_combobox.AddString(_T("print out"));
	sink_combobox.AddString(_T("save to file"));
	sink_combobox.SetCurSel(0);


	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStreamProcessingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStreamProcessingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStreamProcessingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStreamProcessingDlg::OnEnChangeEditCepRule()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CStreamProcessingDlg::OnBnClickedButtonEventFilterAdd(){
	UpdateData(true);

	if (event_filter_name.GetLength() == 0 || event_filter_rule.GetLength() == 0) {
		MessageBox(_T("fill the name and the rule"), NULL, MB_OK);
		return;
	}

	//parse names 
	string name_str(CW2A(event_filter_name.GetString()));
	vector<string> names = Utils::split(name_str, " ");

	//parse event capture rules
	string str(CW2A(event_filter_rule.GetString()));
	vector<string> lines = Utils::split(str, "\r\n");
	list<string>lines_list;
	for (string line : lines) {
		line = Utils::trim(line);
		lines_list.push_back(line);
	}
	
	list<EventFilterSpec*> eventcaptureSpecs = EventFilterParser::parseAllEventFilterSpec(lines_list);
	for (EventFilterSpec* spec : eventcaptureSpecs) {
		EventProcess* ec = spec->instance();
		ExecuteScheduler::registerEventProcess(*ec);
	}

	MessageBox(_T("Add Event Filter rule successfully"), NULL, MB_OK);
}

//add rule specification of event capture
void CStreamProcessingDlg::OnBnClickedButtonCaptureAdd(){
	UpdateData(true);

	if (event_capture_name.GetLength() == 0 || event_capture_rule.GetLength() == 0) {
		MessageBox(_T("fill the name and the rule"), NULL, MB_OK);
		return;
	}
	
	//parse names 
	string name_str(CW2A(event_capture_name.GetString()));
	vector<string> names = Utils::split(name_str, " ");

	//parse event capture rules
	string str(CW2A(event_capture_rule.GetString()));
	vector<string> lines = Utils::split(str, "\r\n");
	list<string>lines_list;
	for (string line : lines) {
		line = Utils::trim(line);
		lines_list.push_back(line);
	}
	list<EventCaptureSpec*> eventcaptureSpecs = EventCaptureSpecParser::parseAllEventCaptureSpec(lines_list);
	for (EventCaptureSpec* spec : eventcaptureSpecs) {
		EventCapture* ec = spec->instance();
		ExecuteScheduler::registerEventCapture(ec);
	}
	MessageBox(_T("Add Event Capture rule successfully"), NULL, MB_OK);

	event_capture_rule = _T("");
	event_capture_name = _T("");
	UpdateData(false);
}

//add rule specification of CQ
void CStreamProcessingDlg::OnBnClickedButtonCqAdd()
{
	UpdateData(true);

	if (cq_name.GetLength() == 0 || cq_rule.GetLength() == 0) {
		MessageBox(_T("fill the name and the rule"), NULL, MB_OK);
		return;
	}

	//parse names 
	string name_str(CW2A(cq_name.GetString()));
	vector<string> names = Utils::split(name_str, " ");

	//parse event capture rules
	string str(CW2A(cq_rule.GetString()));
	vector<string> lines = Utils::split(str, "\r\n");
	list<string>lines_list;
	for (string line : lines) {
		line = Utils::trim(line);
		lines_list.push_back(line);
	}
	list<CQSpec*> eventcaptureSpecs = CQSpecParser::parseAllCQSpec(lines_list);
	for (CQSpec* spec : eventcaptureSpecs) {
		CQProcess* cq = spec->instance();
		ExecuteScheduler::registerCQProcess(cq);
	}
	MessageBox(_T("Add CQ rule successfully"), NULL, MB_OK);
	cq_rule = _T("");
	cq_name = _T("");;
	UpdateData(false);
}

//add rule specification of CEP
void CStreamProcessingDlg::OnBnClickedButtonCepAdd()
{
	UpdateData(true);

	if (cep_name.GetLength() == 0 || cep_rule.GetLength() == 0) {
		MessageBox(_T("fill the name and the rule"), NULL, MB_OK);
		return;
	}

	//parse names 
	string name_str(CW2A(cep_name.GetString()));
	vector<string> names = Utils::split(name_str, " ");

	//parse event capture rules
	string str(CW2A(cep_rule.GetString()));
	vector<string> lines = Utils::split(str, "\r\n");
	list<string>lines_list;
	for (string line : lines) {
		line = Utils::trim(line);
		lines_list.push_back(line);
	}
	list<CEPSpec*> eventcaptureSpecs = CEPSpecParser::parseAllCEPSpec(lines_list);
	for (CEPSpec* spec : eventcaptureSpecs) {
		CEPProcess* cep = spec->instance();
		
		ExecuteScheduler::registerCEPProcess(cep);
	}

	MessageBox(_T("Add CEP rule successfully"), NULL, MB_OK);
	cep_name = _T("");
	cep_rule = _T("");
	UpdateData(false);
}

//the thread to run the backend of stream processing
class ThreadWrapper {
private:
	bool isStop = false;
public:
	void run() {
		//launch a console
		FILE* fp = NULL;
		AllocConsole();
		freopen_s(&fp, "CONOUT$", "w+t", stdout);
		cout << "start stream processing..." << endl;
		for (int i = 0; i < 1000000 && !isStop; i++) {
			//Sleep(200);
			EventPtr e = EventGenerator::generateEvent();

			//update the variable of "inputstream_to_display"
			CString cstr(e->toString().c_str());
			
			CStreamProcessingDlg::inputstream_to_display = cstr + "\r\n"+ CStreamProcessingDlg::inputstream_to_display;
			if (CStreamProcessingDlg::inputstream_to_display.GetLength() > 5000)
				CStreamProcessingDlg::inputstream_to_display.Truncate(3000);

			//cout << "input: " << *e << endl;
			ExecuteScheduler::run(e);
			ExecuteScheduler::executeCEPProcess();
		}

		fclose(stdout);
		//fclose(stdin);
		FreeConsole();
	}


	std::thread runThread() {
		return std::thread(&ThreadWrapper::run, this);
	}

	void stop() {
		this->isStop = true;
	}
};

bool isStarted = false;
ThreadWrapper *w = nullptr;//thread to run stream processing

void CStreamProcessingDlg::OnBnClickedButtonStart(){
	if (!isStarted) {
		w = new ThreadWrapper();
		std::thread tw1 = w->runThread();
		//tw1.join();
		tw1.detach();

		isStarted = true;
	}
	else {
		MessageBox(_T("The processing has already started."), NULL, MB_OK);
	}
}


void CStreamProcessingDlg::OnBnClickedButtonStop(){
	if (isStarted) {
		w->stop();
		isStarted = false;
		delete w;
		w = nullptr;
	}
}

int length = 0;//store the history length of "inputstream_to_display"
void CStreamProcessingDlg::updataPrintInputStream() {
	if (length != inputstream_to_display.GetLength()) {\
		//change the content of edit control
		GetDlgItem(IDC_INPUT_STREAM)->SetWindowText(inputstream_to_display);
		length = inputstream_to_display.GetLength();
	}
	
}


//button for displaying input stream
void CStreamProcessingDlg::OnBnClickedButtonInputStream(){
	if (threadOfInputStream == nullptr) {
		//start a new thread
		threadOfInputStream = AfxBeginThread(ThreadOfInputStreamPrint::runThread, this);
	}
}

