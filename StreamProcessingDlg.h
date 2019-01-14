
// StreamProcessingDlg.h : header file
//

#pragma once
#include <string>

using namespace std;


// CStreamProcessingDlg dialog
class CStreamProcessingDlg : public CDialogEx
{
// Construction
public:
	CStreamProcessingDlg(CWnd* pParent = nullptr);	// standard constructor

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
	afx_msg void OnCbnSelchangeComboboxex1();
	afx_msg void OnEnChangeEditCepRule();
	afx_msg void OnBnClickedButtonEventFilterAdd();
	afx_msg void OnBnClickedButtonCaptureAdd();
	afx_msg void OnBnClickedButtonCqAdd();
	afx_msg void OnBnClickedButtonCepAdd();
};
