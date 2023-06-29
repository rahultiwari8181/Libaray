
// LibraryManagementSystemDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "LibraryManagementSystem.h"
#include "LibraryManagementSystemDlg.h"
#include "afxdialogex.h"
#include "CBookDetailsDialog.h"
#include "CUserSearchDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define MY_TIMER 3000
static UINT BASED_CODE indicators[] = {
	ID_INDICATOR_TIME,
	ID_INDICATOR_POINT
};


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
public:
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CLibraryManagementSystemDlg dialog



CLibraryManagementSystemDlg::CLibraryManagementSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIBRARYMANAGEMENTSYSTEM_DIALOG, pParent)
	, m_str_user_id(_T(""))
	, m_str_password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLibraryManagementSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_user_id, m_str_user_id);
	DDX_Text(pDX, IDC_EDIT_password, m_str_password);
	DDX_Control(pDX, IDC_RADIO_user, m_ctr_radio_user);
	DDX_Control(pDX, IDC_RADIO_admin, m_ctr_radio_admin);
}

BEGIN_MESSAGE_MAP(CLibraryManagementSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_login, &CLibraryManagementSystemDlg::OnBnClickedButtonlogin)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_RADIO_user, &CLibraryManagementSystemDlg::OnBnClickedRadiouser)
END_MESSAGE_MAP()


// CLibraryManagementSystemDlg message handlers

BOOL CLibraryManagementSystemDlg::OnInitDialog()
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
	m_bar.Create(this);
	m_bar.SetIndicators(indicators, 2);

	CRect rect;
	GetClientRect(&rect);
	m_bar.SetPaneInfo(1, ID_INDICATOR_TIME, SBPS_NORMAL, rect.Width());
	m_bar.GetStatusBarCtrl().SetBkColor(RGB(192, 192, 192));
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, ID_INDICATOR_TIME);

	SetTimer(MY_TIMER, 1000, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLibraryManagementSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

//void CLibraryManagementSystemDlg::OnPaint()
//{
//	if (IsIconic())
//	{
//		CPaintDC dc(this); // device context for painting
//
//		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
//
//		// Center icon in client rectangle
//		int cxIcon = GetSystemMetrics(SM_CXICON);
//		int cyIcon = GetSystemMetrics(SM_CYICON);
//		CRect rect;
//		GetClientRect(&rect);
//		int x = (rect.Width() - cxIcon + 1) / 2;
//		int y = (rect.Height() - cyIcon + 1) / 2;
//
//		// Draw the icon
//		dc.DrawIcon(x, y, m_hIcon);
//	}
//	else
//	{
//		CDialogEx::OnPaint();
//	}
//}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLibraryManagementSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLibraryManagementSystemDlg::OnBnClickedButtonlogin()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CStdioFile user;

	if (m_ctr_radio_admin.GetCheck() == 1)
	{
		user.Open(_T("Library.txt"), CFile::modeRead|CFile::typeText);
		CString user_id, password;
		user.ReadString(user_id);
		user.ReadString(password);
		if (m_str_user_id == user_id && m_str_password == password)
		{
			CBookDetailsDialog objCBookDetailsDialog;
			objCBookDetailsDialog.DoModal();
		}
		else
		{
			AfxMessageBox(_T("Please enter valid details"));
		}
		user.Close();
	}
	else if (m_ctr_radio_user.GetCheck() == 1)
	{
		user.Open(_T("User.txt"), CFile::modeRead | CFile::typeText);
		CString user_id, password;
		user.ReadString(user_id);
		user.ReadString(password);
		if (m_str_user_id == user_id && m_str_password == password)
		{
			CUserSearchDialog objCUserSearchDialog;
			objCUserSearchDialog.DoModal();
		}
		else
		{
			AfxMessageBox(_T("Please enter valid details"));
		}
		user.Close();
	}
	else
	{
		AfxMessageBox(_T("Please make a selection"));
	}
}





void CLibraryManagementSystemDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CTime t1;

	t1 = CTime::GetCurrentTime();
	m_bar.SetPaneText(1, t1.Format("%H:%M:%S, %D"));
	CDialogEx::OnTimer(nIDEvent);
}


void CLibraryManagementSystemDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	str.Format(_T("x = %d y = %d"), point.x, point.y);
	m_bar.SetPaneText(0, str);

	CDialogEx::OnMouseMove(nFlags, point);
}


void CLibraryManagementSystemDlg::OnBnClickedRadiouser()
{
	// TODO: Add your control notification handler code here
}
