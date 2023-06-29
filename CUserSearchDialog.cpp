// CUserSearchDialog.cpp : implementation file
//

#include "pch.h"
#include "LibraryManagementSystem.h"
#include "CUserSearchDialog.h"
#include "afxdialogex.h"


// CUserSearchDialog dialog

IMPLEMENT_DYNAMIC(CUserSearchDialog, CDialogEx)

CUserSearchDialog::CUserSearchDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_str_book_title(_T(""))
	, m_str_book_author(_T(""))
{

}

CUserSearchDialog::~CUserSearchDialog()
{
}

void CUserSearchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctr_list_user_books);
	DDX_Text(pDX, IDC_EDIT_book_title, m_str_book_title);
	DDX_Text(pDX, IDC_EDIT_book_author, m_str_book_author);
}


BEGIN_MESSAGE_MAP(CUserSearchDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_book_dispaly, &CUserSearchDialog::OnBnClickedButtonbookdispaly)
	ON_BN_CLICKED(IDC_BUTTON_borrow, &CUserSearchDialog::OnBnClickedButtonborrow)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CUserSearchDialog::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CUserSearchDialog message handlers


void CUserSearchDialog::OnBnClickedButtonbookdispaly()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	LVITEM lvitem;
	int nItem = m_ctr_list_user_books.GetItemCount();
	CStdioFile iofile;

	iofile.Open(_T("User1.txt"), CFile::modeCreate| CFile::modeWrite | CFile::typeText);

	lvitem.mask = LVFIF_TEXT;
	lvitem.iItem = nItem;
	lvitem.iSubItem = 0;
	lvitem.pszText = _T("");
	m_ctr_list_user_books.InsertItem(&lvitem);
	if (m_str_book_title.IsEmpty() | m_str_book_title.IsEmpty() | m_str_book_author.IsEmpty())
	{
		AfxMessageBox(_T("Please, fill all details"));
	}
	else
	{

		int validate = 0;
		for (int i = 0; i < nItem; i++)
		{
			CString str;
			str = m_ctr_list_user_books.GetItemText(i, 0);
			if (str == m_str_book_title)
			{
				validate = -1;
				break;
			}
		}
		if (validate == -1)
		{
			AfxMessageBox(_T(" phir se wahi book ullu mat bnao"));
		}
		else
		{


			CString index;
			index.Format(_T("%d"), nItem + 1);
			

			iofile.WriteString(m_str_book_title);
			iofile.WriteString(_T("\n "));
			iofile.WriteString(m_str_book_author);
			iofile.WriteString(_T("\n"));

			m_ctr_list_user_books.SetItemText(nItem, 0, (LPCTSTR)index);
			m_ctr_list_user_books.SetItemText(nItem, 1, (LPCTSTR)m_str_book_title);
			m_ctr_list_user_books.SetItemText(nItem, 2, (LPCTSTR)m_str_book_author);


		
			UpdateData(FALSE);

			
		}
	}
}


BOOL CUserSearchDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

//TODO:  Add extra initialization here

	m_ctr_list_user_books.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	   m_ctr_list_user_books.InsertColumn(0, _T("Book ID"), LVCFMT_RIGHT, 120);
	   m_ctr_list_user_books.InsertColumn(1, _T("Book Title"), LVCFMT_CENTER, 120);
	   m_ctr_list_user_books.InsertColumn(2, _T("Author"), LVCFMT_CENTER, 120);

	   return TRUE;  // return TRUE unless you set the focus to a control
}


void CUserSearchDialog::OnBnClickedButtonborrow()
{
	 //TODO: Add your control notification handler code here
	UpdateData(TRUE);
	LVITEM lvitem;
	int nItem = m_ctr_list_user_books.GetItemCount();

	lvitem.mask = LVFIF_TEXT;
	lvitem.iItem = nItem;
	lvitem.iSubItem = 0;
	lvitem.pszText = _T("");
	m_ctr_list_user_books.InsertItem(&lvitem);


	CString index;
	index.Format(_T("%d"), nItem);

	m_ctr_list_user_books.SetItemText(nItem, 0, (LPCTSTR)index);
	m_ctr_list_user_books.SetItemText(nItem, 1, (LPCTSTR)m_str_book_title);
	m_ctr_list_user_books.SetItemText(nItem, 2, (LPCTSTR)m_str_book_author);

	UpdateData(FALSE);

}


void CUserSearchDialog::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
