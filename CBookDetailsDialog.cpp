// CBookDetailsDialog.cpp : implementation file
//

#include "pch.h"
#include "LibraryManagementSystem.h"
#include "CBookDetailsDialog.h"
#include "afxdialogex.h"


// CBookDetailsDialog dialog

IMPLEMENT_DYNAMIC(CBookDetailsDialog, CDialogEx)

CBookDetailsDialog::CBookDetailsDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_str_book_id(_T(""))
	, m_str_book_title(_T(""))
	, m_str_author(_T(""))
{

}

CBookDetailsDialog::~CBookDetailsDialog()
{
}

void CBookDetailsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_book_id, m_str_book_id);
	DDX_Text(pDX, IDC_EDIT_book_title, m_str_book_title);
	DDX_Text(pDX, IDC_EDIT_Author, m_str_author);
	DDX_Control(pDX, IDC_LIST1, m_ctr_list_book_table);
}


BEGIN_MESSAGE_MAP(CBookDetailsDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CBookDetailsDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_delete, &CBookDetailsDialog::OnBnClickedButtondelete)
	ON_BN_CLICKED(IDC_BUTTON_update, &CBookDetailsDialog::OnBnClickedButtonupdate)
	ON_BN_CLICKED(IDC_BUTTON_display, &CBookDetailsDialog::OnBnClickedButtondisplay)
	ON_BN_CLICKED(IDC_BUTTON_clear, &CBookDetailsDialog::OnBnClickedButtonclear)
END_MESSAGE_MAP()


// CBookDetailsDialog message handlers


void CBookDetailsDialog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	LVITEM lvitem;
	int nItem = m_ctr_list_book_table.GetItemCount();

	lvitem.mask = LVFIF_TEXT;
	lvitem.iItem = nItem;
	lvitem.iSubItem = 0;
	lvitem.pszText = _T("");
	m_ctr_list_book_table.InsertItem(&lvitem);

	if (m_str_book_id.IsEmpty() | m_str_book_title.IsEmpty() | m_str_author.IsEmpty())
	{
		AfxMessageBox(_T("Please, fill all details"));
	}
	else
	{

		int validate = 0;
		for (int i = 0; i < nItem; i++)
		{
			CString str;
			str = m_ctr_list_book_table.GetItemText(i, 0);
			if (str == m_str_book_id)
			{
				validate = -1;
				break;
			}
		}
		if (validate == -1)
		{
			AfxMessageBox(_T(" phir se wahi book kuch naya try karo"));
		}
		else
		{
			m_ctr_list_book_table.SetItemText(nItem, 0, (LPCTSTR)m_str_book_id);
			m_ctr_list_book_table.SetItemText(nItem, 1, (LPCTSTR)m_str_book_title);
			m_ctr_list_book_table.SetItemText(nItem, 2, (LPCTSTR)m_str_author);

			iofile.WriteString(m_str_book_id);			iofile.WriteString(_T(" "));			iofile.WriteString(m_str_book_title);			iofile.WriteString(_T(" "));			iofile.WriteString(m_str_author);			iofile.WriteString(_T("\n"));


			OnBnClickedButtonclear();
			UpdateData(FALSE);
		}
	}
}


void CBookDetailsDialog::OnBnClickedButtondelete()
{
	// TODO: Add your control notification handler code here
	UINT count = m_ctr_list_book_table.GetItemCount();
	UINT select_count = m_ctr_list_book_table.GetSelectedCount();
	if (count == 0)
	{
		AfxMessageBox(_T("No item Available"));
	}
	else if (select_count > 0)
	{
		UINT sel = m_ctr_list_book_table.GetNextItem(-1, LVNI_SELECTED);
		m_ctr_list_book_table.DeleteItem(sel);
	}
	else
	{
		AfxMessageBox(_T("Please select an Item"));
	}
}


void CBookDetailsDialog::OnBnClickedButtonupdate()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	LVITEM lvitem;
	int nItem = m_ctr_list_book_table.GetItemCount();

	lvitem.mask = LVFIF_TEXT;
	lvitem.iItem = nItem;
	lvitem.iSubItem = 0;
	lvitem.pszText = _T("");
	m_ctr_list_book_table.InsertItem(&lvitem);

	for (int i = 0; i < nItem; i++)
	{
		CString str;
		str = m_ctr_list_book_table.GetItemText(i, 0);
		if (str == m_str_book_id)
		{
			m_ctr_list_book_table.SetItemText(i, 0, (LPCTSTR)m_str_book_id);
			m_ctr_list_book_table.SetItemText(i, 1, (LPCTSTR)m_str_book_title);
			m_ctr_list_book_table.SetItemText(i, 2, (LPCTSTR)m_str_author);
			UpdateData(FALSE);
			break;

		}
	}
}


void CBookDetailsDialog::OnBnClickedButtondisplay()
{
	// TODO: Add your control notification handler code here
}


void CBookDetailsDialog::OnBnClickedButtonclear()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_str_book_id = _T("");
	m_str_book_title = _T("");
	m_str_author = _T("");
	UpdateData(FALSE);
}


BOOL CBookDetailsDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	m_ctr_list_book_table.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_ctr_list_book_table.InsertColumn(0, _T("Book Id"),LVCFMT_RIGHT,120);
	m_ctr_list_book_table.InsertColumn(1, _T("Book Title"),LVCFMT_CENTER, 220);
	m_ctr_list_book_table.InsertColumn(2, _T("Author"), LVCFMT_CENTER, 220);

	iofile.Open(_T("Books.txt"), CFile::modeWrite | CFile::typeText);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
