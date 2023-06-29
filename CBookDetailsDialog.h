#pragma once


// CBookDetailsDialog dialog

class CBookDetailsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CBookDetailsDialog)

public:
	
	CBookDetailsDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CBookDetailsDialog();
	

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_str_book_id;
	CString m_str_book_title;
	CString m_str_author;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtondelete();
	afx_msg void OnBnClickedButtonupdate();
	afx_msg void OnBnClickedButtondisplay();
	afx_msg void OnBnClickedButtonclear();
	CListCtrl m_ctr_list_book_table;
	virtual BOOL OnInitDialog();
	CStdioFile iofile;
};
