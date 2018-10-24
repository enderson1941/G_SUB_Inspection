// SplashWnd.cpp : implementation file
//

#include "stdafx.h"
#include "G_SUB_Inspection.h"
#include "G_SUB_InspectionDlg.h"
#include "SplashWnd.h"
#include "afxdialogex.h"

SplashWnd* spl_wnd;

// SplashWnd dialog

IMPLEMENT_DYNAMIC(SplashWnd, CDialogEx)

SplashWnd::SplashWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SplashWnd, pParent)
{
	theApp.instruction_file = "temp\\instruction.ini";
	theApp.modelList_file = "temp\\modelList.ini";
	theApp.database_file = "database\\G_SUB.db";
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
	spl_wnd = this;
	dwRet = GetCurrentDirectory(MAX_PATH, (LPWSTR)(LPCWSTR)theApp.Currentdir_);
	if (dwRet > MAX_PATH)
	{
		SetCurrentDirectory(L"..");
	}
#pragma region folder_create
	if (!PathIsDirectory(L"database"))
	{
		::CreateDirectory(L"database", NULL);
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

	CString _str;
	CString appPathFile;
	FILE* fp = NULL;
	unsigned short int sUnicodeFlag;
	USES_CONVERSION;
	appPathFile.Format(A2T(theApp.instruction_file));
	if (_access(theApp.instruction_file, 0) == -1)
	{
		sUnicodeFlag = 0xfeff;
		fp = _wfopen(appPathFile, _T("wb"));
		fwrite(&sUnicodeFlag, sizeof(short int), 1, fp);
		fclose(fp);
		_str.Format(L"Cover-inner异欠品检查");
		WritePrivateProfileString(L"INFO", L"软件功能", _str, appPathFile);
		_str.Format(version_);
		WritePrivateProfileString(L"INFO", L"当前版本", _str, appPathFile);
		_str.Format(L"KISYU 2# G_SUB03");
		WritePrivateProfileString(L"INFO", L"工程名称", _str, appPathFile);
		_str.Format(L"大和设备开发部");
		WritePrivateProfileString(L"INFO", L"联系部门", _str, appPathFile);
		_str.Format(L"881");
		WritePrivateProfileString(L"INFO", L"内线电话", _str, appPathFile);
	}
	//
	appPathFile.Format(A2T(theApp.modelList_file));
	theApp.model_.clear();
	if (_access(theApp.modelList_file, 0) == -1)
	{
		fp = _wfopen(appPathFile, _T("wb"));
		fwrite(&sUnicodeFlag, sizeof(short int), 1, fp);
		fclose(fp);
		_str.Format(L"AJ6");
		theApp.model_.push_back(_str);
		ini_parser.SetValue("Model", L"0", _str);
		_str.Format(L"JG5");
		theApp.model_.push_back(_str);
		ini_parser.SetValue("Model", L"1", _str);
		_str.Format(L"TAA");
		theApp.model_.push_back(_str);
		ini_parser.SetValue("Model", L"2", _str);
		_str.Format(L"WLG");
		theApp.model_.push_back(_str);
		ini_parser.SetValue("Model", L"3", _str);
		ini_parser.WriteINI(theApp.modelList_file);
		ini_parser.Clear();
		_str.Format(L"%d", 4);
		WritePrivateProfileString(L"INFO", L"modelsum", _str, appPathFile);
	}
	else
	{
		int op_code = ini_parser.ReadINI(theApp.modelList_file);
		int size_ = 0;
		_str = ini_parser.GetValue("INFO", L"modelsum", size_);
		int nCnt = _ttoi(_str);
		for (int i = 0; i < nCnt; i++)
		{
			_str.Format(L"%d", i );
			_str = ini_parser.GetValue("Model", _str, size_);
			theApp.model_.push_back(_str);
		}
		//
		ini_parser.Clear();
	}
	delete fp;
	CTime time(CTime::GetCurrentTime());
	
	theApp.currentTime.Format(L"%04d-%02d-%02d", time.GetYear(),
		time.GetMonth(),
		time.GetDay());
	BOOL access_sign;
	if (_access(theApp.database_file, 0) == -1)
	{
		access_sign = modify_db.Open(A2T(theApp.database_file));

		db_command.Format(L"CREATE TABLE '%s' ( \r\n 'i_index' TEXT, \r\n 'current_date' TEXT, \r\n \
			'production_index' TEXT, \r\n 'production_in'	TEXT, \r\n 'production_realtime' TEXT, \r\n 'production_NG' TEXT, \r\n \
'admin_pass1' TEXT, \r\n 'admin_pass2'	TEXT)", L"system_data");//IF NOT EXISTS
		access_sign = modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			SendMessage(WM_CLOSE);
			return FALSE;
		}
		//
		db_command.Format(_T("INSERT INTO '%s' VALUES ( %d, '%s', %d, '%s', %d, %d, '%s', '%s')  "),
			L"system_data", 1, theApp.currentTime, 0, L"NULL", 0, 0, L"f", L"h");
		access_sign = modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			return FALSE;
		}
	}
	else
	{
		access_sign = modify_db.Open(A2T(theApp.database_file));
		db_command.Format(L"UPDATE system_data SET current_date = '%s' ", theApp.currentTime);
		access_sign = modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			SendMessage(WM_CLOSE);
			return FALSE;
		}
	}
	db_command.Format(L"SELECT admin_pass1, admin_pass2 FROM system_data");
	db_status = modify_db.Statement(db_command);
	if (db_status != NULL)
	{
		while (db_status->NextRow())
		{
			theApp.admin_pass[0] = db_status->ValueString(0);
			theApp.admin_pass[1] = db_status->ValueString(1);
		}
	}
	delete db_status;

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
