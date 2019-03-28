
// StreamProcessingDlg.h : header file
//

#pragma once
#include <string>

using namespace std;


// CStreamProcessingDlg dialog
class CStreamProcessingDlg : public CDialogEx{
// Construction
public:
	CStreamProcessingDlg(CWnd* pParent = nullptr);	// standard constructor

	~CStreamProcessingDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STREAMPROCESSING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString event_filter_name;
	CString event_filter_rule;
	CString event_capture_name;
	CString event_capture_rule;
	CString cq_name;
	CString cq_rule;
	CString cep_name;
	CString cep_rule;
	afx_msg void OnEnChangeEditCepRule();
	afx_msg void OnBnClickedButtonEventFilterAdd();
	afx_msg void OnBnClickedButtonCaptureAdd();
	afx_msg void OnBnClickedButtonCqAdd();
	afx_msg void OnBnClickedButtonCepAdd();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonInputStream();

	void updataPrintInputStream();

public:

	static CString inputstream_to_display;

	CWinThread * threadOfInputStream = nullptr;
	afx_msg void OnBnClickedButtonSearch();
	// use the name of output stream to search a rule specification
	CString outputStreamNameForSearch;
	// edit control or display rule specifications
	CString editBoxOfRule;
	afx_msg void OnEnChangeInputStream();
	afx_msg void OnBnClickedButtonDisplayAllRule();
	afx_msg void OnBnClickedButtonDeleteRule();
	afx_msg void OnBnClickedButtonUpdateRule();

private:
	void addEventCaptureRule(CString outputStreamName, CString ruleStrs);
	void addCQRule(CString outputStreamName, CString ruleStrs);
	void addCEPRule(CString outputStreamName, CString ruleStrs);

public:
	CString outputStreamForUpdate;
	afx_msg void OnBnClickedButton1();
};

namespace gui {
	//to paint the processing flow graph
	class ProcessFlowDrawing {
	public:
		ProcessFlowDrawing(CStreamProcessingDlg* dlg);

		void DrawEllipse(CDC *pDC, CPoint &relative_center, int radius, CString text);
		void DrawEllipse(CDC *pDC, int x_off, int y_off, int width, int length, CString text);
		
		void DrawRect(CDC *pDC);
		void DrawArrow(CDC* pdc, CPoint &point1, CPoint &point2, int nFlag);
		void DrawLine(CDC *pDC, const CPoint &p1, const CPoint &p2);
		void DrawText(CDC *pDC, int x, int y, CString str);

		void paintStaticGraph(CDC *pDC);
	private:
		CPen m_pen;
		CPoint m_point;
		int x;
		int y;
		CStreamProcessingDlg* dlg;
	};
}