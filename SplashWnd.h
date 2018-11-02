#pragma once


// SplashWnd dialog

class SplashWnd : public CDialogEx
{
	DECLARE_DYNAMIC(SplashWnd)

public:
	SplashWnd(CWnd* pParent = NULL);   // standard constructor
	virtual ~SplashWnd();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SplashWnd };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString version_;
	CString db_command;

	DWORD dwRet;
	INIParser	ini_parser;
	HICON* icon_file;
	
	void wr_unicodefile(CString file_path);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
