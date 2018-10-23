// SplashWnd.cpp : implementation file
//

#include "stdafx.h"
#include "G_SUB_Inspection.h"
#include "G_SUB_InspectionDlg.h"
#include "SplashWnd.h"
#include "afxdialogex.h"


// SplashWnd dialog

IMPLEMENT_DYNAMIC(SplashWnd, CDialogEx)

SplashWnd::SplashWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SplashWnd, pParent)
{

}

SplashWnd::~SplashWnd()
{
}

void SplashWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SplashWnd, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// SplashWnd message handlers
BOOL SplashWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	dwRet = GetCurrentDirectory(MAX_PATH, (LPWSTR)(LPCWSTR)theApp.Currentdir_);
	if (dwRet > MAX_PATH)
	{
		SetCurrentDirectory(L"..");
	}
#pragma region folder_create
	if (!PathIsDirectory(L"data_base"))
	{
		::CreateDirectory(L"data_base", NULL);
	}
	if (!PathIsDirectory(L"error_image"))
	{
		::CreateDirectory(L"error_image", NULL);
	}
	if (!PathIsDirectory(L"temp"))
	{
		::CreateDirectory(L"temp", NULL);
	}
	if (!PathIsDirectory(L"temp\\error"))
	{
		::CreateDirectory(L"temp\\error", NULL);
	}
	if (!PathIsDirectory(L"temp\\plan"))
	{
		::CreateDirectory(L"temp\\plan", NULL);
	}
#pragma endregion
	version_.LoadString(IDS_version);
	SetDlgItemText(IDC_version_no, L"version: " + version_);
	SetBackgroundImage(IDB_BITMAP1, CDialogEx::BACKGR_TILE);

	icon_file = new HICON[2];
	theApp.icontree_list.Create(25, 25, ILC_COLOR32, 3, 3);
	//
	icon_file[0] = AfxGetApp()->LoadIcon(IDI_ICON1);
	icon_file[1] = AfxGetApp()->LoadIcon(IDI_ICON2);
	theApp.icontree_list.Add(icon_file[0]);
	theApp.icontree_list.Add(icon_file[1]);

	//BOOL access_sign = modify_db.Open(L"data_base\\G_SUB.db");
	//CTime time(CTime::GetCurrentTime());
	//CString currentTime;
	//currentTime.Format(L"%04d-%02d-%02d", time.GetYear(),
	//	time.GetMonth(),
	//	time.GetDay());

	//db_command.Format(L"UPDATE system SET current_date = '2018-10-23'");//, currentTime
	//access_sign = modify_db.DirectStatement(db_command);
	//if (!access_sign)
	//{
	//	SendMessage(WM_CLOSE);
	//	return FALSE;
	//}
	SetTimer(0, 2500, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void SplashWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case 0:
	{
		KillTimer(nIDEvent);
		SendMessage(WM_CLOSE);
		CG_SUB_InspectionDlg main_dlg;
		INT_PTR nResponse = main_dlg.DoModal();
		break;
	}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

BOOL SplashWnd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return FALSE; //return CDialogEx::PreTranslateMessage(pMsg);
}
