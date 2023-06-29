#pragma once


// CUserSearchDialog dialog

class CUserSearchDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CUserSearchDialog)

public:
	CUserSearchDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUserSearchDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonbookdispaly();
	virtual BOOL OnInitDialog();
	CListCtrl m_ctr_list_user_books;
	CString m_str_book_title;
	CString m_str_book_author;
	CStdioFile iofile;
	afx_msg void OnBnClickedButtonborrow();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
