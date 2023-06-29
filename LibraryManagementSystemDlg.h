
// LibraryManagementSystemDlg.h : header file
//

#pragma once


// CLibraryManagementSystemDlg dialog
class CLibraryManagementSystemDlg : public CDialogEx
{
// Construction
public:
	CStatusBar m_bar;
	CLibraryManagementSystemDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIBRARYMANAGEMENTSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
//	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_str_user_id;
	CString m_str_password;
	afx_msg void OnBnClickedButtonlogin();
	CButton m_ctr_radio_user;
	CButton m_ctr_radio_admin;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedRadiouser();
};
