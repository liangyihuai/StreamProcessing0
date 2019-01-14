
// StreamProcessingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StreamProcessing.h"
#include "StreamProcessingDlg.h"
#include "afxdialogex.h"

#include "ExecuteScheduler.h"
#include "SpecUtils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
		\r\nFrom target\
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
END_MESSAGE_MAP()


// CStreamProcessingDlg message handlers

BOOL CStreamProcessingDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

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


void CStreamProcessingDlg::OnBnClickedButtonEventFilterAdd()
{
	
}


void CStreamProcessingDlg::OnBnClickedButtonCaptureAdd(){
	UpdateData(true);

	if (event_capture_name.GetLength() == 0 || event_capture_rule.GetLength() == 0) {
		MessageBox(_T("fill the name and the rule"), NULL, MB_OK);
		return;
	}
	

	//pause names 
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
}


void CStreamProcessingDlg::OnBnClickedButtonCqAdd()
{
	
}


void CStreamProcessingDlg::OnBnClickedButtonCepAdd()
{

}
