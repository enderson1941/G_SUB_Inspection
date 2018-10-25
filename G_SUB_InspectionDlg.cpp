
// G_SUB_InspectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "G_SUB_Inspection.h"
#include "G_SUB_InspectionDlg.h"
#include "SplashWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDC_crtd_EDIT 9000

ClxTreeCtrl plan_tree;

CG_SUB_InspectionDlg* gsub_ins;
extern SplashWnd* spl_wnd;

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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(ClxTreeCtrl, CTreeCtrl)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(ClxTreeCtrl, CTreeCtrl)

ClxTreeCtrl::ClxTreeCtrl()
{ }

ClxTreeCtrl::~ClxTreeCtrl()
{ }

// CG_SUB_InspectionDlg dialog

IMPLEMENT_DYNAMIC(CG_SUB_InspectionDlg, CDialogEx);

CG_SUB_InspectionDlg::CG_SUB_InspectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_G_SUB_INSPECTION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//
}

CG_SUB_InspectionDlg::~CG_SUB_InspectionDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	
}

void CG_SUB_InspectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_func_button, func_btn);
	DDX_Control(pDX, IDC_plan, plan_tree);
	DDX_Control(pDX, IDC_pswd, pswd_edt);
	DDX_Control(pDX, IDC_datepick, datepick);
	DDX_Control(pDX, IDC_inspec, inspec_pic);
	DDX_Control(pDX, IDC_info_edit, info_edit);
	DDX_Control(pDX, IDC_model_sel, model_sel);
}

BEGIN_MESSAGE_MAP(CG_SUB_InspectionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_func_button, &CG_SUB_InspectionDlg::OnBnClickedfuncbutton)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_pswd, &CG_SUB_InspectionDlg::OnEnChangepswd)
	ON_NOTIFY(TVN_SELCHANGED, IDC_plan, &CG_SUB_InspectionDlg::OnTvnSelchangedplan)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_plan, &CG_SUB_InspectionDlg::OnTvnBegindragplan)
	ON_NOTIFY(NM_RCLICK, IDC_plan, &CG_SUB_InspectionDlg::OnNMRClickplan)
	ON_COMMAND(ID_PLANMENU1_chkpln, &CG_SUB_InspectionDlg::OnPlanmenu1chkpln)
	ON_COMMAND(ID_PLANMENU1_chkdata, &CG_SUB_InspectionDlg::OnPlanmenu1chkdata)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_datepick, &CG_SUB_InspectionDlg::OnDtnDatetimechangedatepick)
	ON_COMMAND(ID_PLANMENU1_addpln, &CG_SUB_InspectionDlg::OnPlanmenu1addpln)
	ON_CBN_SELCHANGE(IDC_model_sel, &CG_SUB_InspectionDlg::OnCbnSelchangemodelsel)
	ON_EN_KILLFOCUS(IDC_crtd_EDIT, &CG_SUB_InspectionDlg::OnKillfocusEdit)
	ON_COMMAND(ID_PLANMENU2_modpln, &CG_SUB_InspectionDlg::OnPlanmenu2modpln)
	ON_COMMAND(ID_PLANMENU1_addmodel, &CG_SUB_InspectionDlg::OnPlanmenu1addmodel)
	ON_COMMAND(ID_PLANMENU1_addcontent, &CG_SUB_InspectionDlg::OnPlanmenu1addcontent)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CG_SUB_InspectionDlg message handlers
BOOL CG_SUB_InspectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	gsub_ins = this;
	CenterWindow();

	//camera initialization
	camera_initialization();

	//
	functionarea_init(-1);
	instruction_output();
	initialize_sgn = TRUE;

	COLORREF oldColor = RGB(240, 240, 240);
	plan_tree.SetBkColor(oldColor);
	plan_tree.SetImageList(&theApp.icontree_list, TVSIL_NORMAL);

	for (int i = 0; i < theApp.model_.size(); i++)
	{
		model_sel.AddString(theApp.model_[i]);
	}

	//repaint screen
	SetTimer(-1, 10, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CG_SUB_InspectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CG_SUB_InspectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CG_SUB_InspectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//function button
void CG_SUB_InspectionDlg::OnBnClickedfuncbutton()
{
	// TODO: Add your control notification handler code here
	if (!inspect_sgn)
	{
		plan_tree.ModifyStyle(0, TVS_DISABLEDRAGDROP, 0);
		functionarea_init(0);
		if (add_pln || mdy_pln)
		{
			add_pln = FALSE;
			mdy_pln = FALSE;
			UINT fileSum = 0;
			int layer = 1;
			CString appPathFile;
			appPathFile.Format(L"temp\\plan\\" + plan_tree.GetItemText(hRoot) + L".ini");
			unsigned short int sUnicodeFlag = 0xfeff;
			FILE *fp;
			fp = _wfopen(appPathFile, _T("wb"));
			fwrite(&sUnicodeFlag, sizeof(short int), 1, fp);
			fclose(fp);
			recordTreeNode(plan_tree, hRoot, fileSum, layer, appPathFile);
			//
			CString _str;
			_str.Format(L"%d", fileSum);
			WritePrivateProfileString(L"INFO", L"filesum", _str, appPathFile);
		}
		int ncode = planlist_ini(2);
		if (ncode != -1)
		{
			func_btn.SetWindowText(L"停止检测");
			pswd_state = FALSE;
			inspect_sgn = TRUE;
			Mat pa_ = imread("lena.jpg");
		//	disp_image(IDC_inspec, pa_, gsub_ins, CRect(0, 0, 100, 100), -1);
		}
		
	}
	else
	{
		plan_tree.ModifyStyle(TVS_DISABLEDRAGDROP, 0);
		inspect_sgn = FALSE;
		func_btn.SetWindowText(L"开始检测");
		plan_tree.DeleteAllItems();
		load_sgn = TRUE;
		disp_image(IDC_inspec, paint_, gsub_ins, CRect(0, 0, 100, 100), -1);
	}
	pswd_state = FALSE;
	SetDlgItemText(IDC_plan_area, L"当日生产计划");
}

#pragma region System
//display image on pic_control
void CG_SUB_InspectionDlg::disp_image(UINT disp_ID, Mat dsp_img, CWnd* pt, 
	CRect& img_rect, int cam_index)
{
	double index_x = 1.0;
	double index_y = 1.0;
	IplImage cpy;
	Mat tmp_img;
	CvvImage cimg;
	CDC* _pDC;
	HDC hDC;
	CRect rect;
	CRect rect_p;
	_pDC = pt->GetDlgItem(disp_ID)->GetDC();
	hDC = _pDC->GetSafeHdc();
	pt->GetDlgItem(disp_ID)->GetClientRect(&rect);
	//repaint
	if (load_sgn)
	{
		load_sgn = FALSE;
		rect_p = CRect(rect.TopLeft().x, rect.TopLeft().y, rect.BottomRight().x, rect.BottomRight().y);
		Mat grey_img = Mat(rect.Width(), rect.Height(), CV_8UC3, Scalar::all(240));
		cpy = grey_img;
		cimg.CopyOf(&cpy);
		cimg.DrawToHDC(hDC, &rect_p);
	//	pt->ReleaseDC(_pDC);
	//	return;
	}
	switch (cam_index % 4)
	{
	case 0:
	{
		rect = CRect(CPoint(0, 0), rect.CenterPoint());
		break;
	}
	case 1:
	{
		rect = CRect(CPoint(rect.CenterPoint().x, 0), CPoint(rect.BottomRight().x, rect.CenterPoint().y));
		break;
	}
	case 2:
	{
		rect = CRect(CPoint(0, rect.CenterPoint().y), CPoint(rect.CenterPoint().x, rect.BottomRight().y));
		break;
	}
	default:
		break;
	}
	if (dsp_img.channels() > 3)
	{
		cvtColor(dsp_img.clone(), tmp_img, CV_BGRA2BGR);
	}
	else
	{
		tmp_img = dsp_img.clone();
	}
	index_x = double(dsp_img.cols) / double(rect.Width());//
	index_y = double(dsp_img.rows) / double(rect.Height());//
	if (index_x > index_y)
	{
		img_rect = CRect(rect.TopLeft(), CSize(rect.Width() - 4, int(dsp_img.rows / index_x) - 4));
		scale_index = index_x;
	}
	else
	{
		img_rect = CRect(rect.TopLeft(), CSize(int(dsp_img.cols / index_y) - 4, rect.Height() - 4));
		scale_index = index_y;
	}
	SetRect(img_rect, 
		img_rect.TopLeft().x + (rect.Width() - img_rect.Width())*0.5, 
		img_rect.TopLeft().y + (rect.Height() - img_rect.Height())*0.5,
		img_rect.BottomRight().x + (rect.Width() - img_rect.Width())*0.5, 
		img_rect.BottomRight().y + (rect.Height() - img_rect.Height())*0.5);
	cpy = tmp_img;
	cimg.CopyOf(&cpy);
	cimg.DrawToHDC(hDC, &img_rect);
	pt->ReleaseDC(_pDC);
}

//Timer Ctrl
void CG_SUB_InspectionDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case -2:
	{
		HWND hWnd = ::FindWindow(NULL, L"异常信息");
		if (hWnd)
		{
			keybd_event(13, 0, 0, 0);
			KillTimer(nIDEvent);
		}
		hWnd = ::FindWindow(NULL, L"提示信息");
		if (hWnd)
		{
			keybd_event(13, 0, 0, 0);
			KillTimer(nIDEvent);
		}
		hWnd = ::FindWindow(NULL, L"设备连接异常");
		if (hWnd)
		{
			keybd_event(13, 0, 0, 0);
			KillTimer(nIDEvent);
			SendMessage(WM_CLOSE);
		}
		break;
	}
	case -1:
	{
		KillTimer(nIDEvent);
		planlist_ini(0);
		load_sgn = TRUE;
		disp_image(IDC_inspec, paint_, gsub_ins, CRect(0, 0, 100, 100));
		func_btn.SetFocus();
		break;
	}
	case 0:
	{
		KillTimer(nIDEvent);
		info_edit.SetWindowText(L"");
		instruction_output();
		break;
	}
	case 1:
	{
		camera_dat[0].camera >> camera_dat[0].frame;
	//	disp_image(IDC_inspec, camera_dat[0].frame, gsub_ins, CRect(0, 0, 100, 100), -1);
		break;
	}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

//Password Ctrl
void CG_SUB_InspectionDlg::OnEnChangepswd()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO:  Add your control notification handler code here
	CString pswd_text;
	pswd_edt.GetWindowText(pswd_text);
	if (add_md)
	{
		if (pswd_text == theApp.admin_pass[1])
		{
			pswd_state = TRUE;
			pswd_edt.SetWindowText(NULL);
			functionarea_init(2);
			SetDlgItemText(IDC_plan_area, L"添加机种信息");
		}
	}
	else
	{
		if (pswd_text == theApp.admin_pass[0])
		{
			pswd_state = TRUE;
			pswd_edt.SetWindowText(NULL);
			if (add_pln)
			{
				functionarea_init(2);
			}
			else if (inquery_pln || inquery_dat)
			{
				functionarea_init(3);
			}
		}
	}
}

//Database Operation
int CG_SUB_InspectionDlg::database_operation(int mode_, CString content)
{
	int nReturn = 0;
	switch (mode_)
	{
	case -4:
	{
		db_command.Format(L"CREATE TABLE '%s' ( \r\n 'i_index' TEXT, \r\n \'current_date' TEXT, \r\n \
			'production_index' TEXT, \r\n 'production_in'	TEXT, \r\n 'production_realtime' TEXT, \r\n \
'production_NG' TEXT, \r\n 'admin_pass1' TEXT, \r\n 'admin_pass2'	TEXT)", L"system_data");//IF NOT EXISTS
		BOOL access_sign = spl_wnd->modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			SendMessage(WM_CLOSE);
			return FALSE;
		}
		break;
	}
	case -3:
	{
		db_command.Format(_T("INSERT INTO '%s' VALUES ( %d, '%s', %d, '%s', %d, %d, '%s', '%s')  "),
			L"system_data", 1, content, 0, L"nul", 0, 0, L"f", L"h");
		BOOL access_sign = spl_wnd->modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			return FALSE;
		}
		break;
	}
	case -2:
	{
		CString db_command;
		db_command.Format(L"UPDATE system_data SET current_date = '%s' ", content);
		BOOL access_sign = spl_wnd->modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			SendMessage(WM_CLOSE);
			return FALSE;
		}
		break;
	}
	case -1:
	{
		CString db_command;
		db_command.Format(L"SELECT admin_pass1, admin_pass2 FROM system_data");
		spl_wnd->db_status = spl_wnd->modify_db.Statement(db_command);
		if (spl_wnd->db_status != NULL)
		{
			while ((spl_wnd->db_status)->NextRow())
			{
				theApp.admin_pass[0] = (spl_wnd->db_status)->ValueString(0);
				theApp.admin_pass[1] = (spl_wnd->db_status)->ValueString(1);
			}
		}
		delete spl_wnd->db_status;
		break;
	}
	case 0://confirm selected model
	{
		db_command.Format(L"select count(*)  from sqlite_master where type='table' and name = '%s' ", content);
		spl_wnd->db_status = spl_wnd->modify_db.Statement(db_command);
		if (spl_wnd->db_status != NULL)
		{
			while (spl_wnd->db_status->NextRow())
			{
				temp_int = _ttoi(spl_wnd->db_status->ValueString(0));
			}
		}
		delete spl_wnd->db_status;
		break;
	}
	case 1://create model table
	{
		if (!add_content)
		{
			db_command.Format(L"CREATE TABLE '%s' ( \r\n 'i_index' TEXT, \r\n 'camera_index' TEXT, \r\n \
			'contents_remarks' TEXT, \r\n 'image_file'	TEXT, \r\n 'ROI' TEXT, \r\n 'threshold' TEXT)", content);
			BOOL access_sign = spl_wnd->modify_db.DirectStatement(db_command);
			if (!access_sign)
			{
				nReturn = -1;
				return nReturn;
			}
		}
		db_command.Format(_T("INSERT INTO '%s' VALUES ( %d, %d, '%s', '%s', '%s', %.2f)  "),
			content, newmodel_no, 0, L"nul", L"nul", L"nul", 0.75f);
		BOOL access_sign = spl_wnd->modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			return FALSE;
		}
		break;
	}
	case 2://check selected model
	{
		CString db_content;
		db_command.Format(L"SELECT * FROM %s", model_add);
		spl_wnd->db_status = spl_wnd->modify_db.Statement(db_command);
		if (spl_wnd->db_status != NULL)
		{
			while (spl_wnd->db_status->NextRow())
			{
				db_content = spl_wnd->db_status->ValueString(0);
				newmodel_no = _ttoi(db_content);
				new_inspectcontent(hRoot, newmodel_no);
				db_content = spl_wnd->db_status->ValueString(1);
				plan_tree.SetItemText(subRoot, treeNode_str[1] + L": " + db_content);//camera_index
				db_content = spl_wnd->db_status->ValueString(2);
				plan_tree.SetItemText(subRoot1, treeNode_str[2] + L": " + db_content);//inspect_content
				db_content = spl_wnd->db_status->ValueString(3);
				int ind = db_content.ReverseFind('\\');
				db_content = db_content.Mid(ind + 1);
				plan_tree.SetItemText(subRoot2, treeNode_str[3] + L": " + db_content);//image_file
				db_content = spl_wnd->db_status->ValueString(4);
				plan_tree.SetItemText(subRoot3, treeNode_str[4] + L": " + db_content);//ROI
				db_content = spl_wnd->db_status->ValueString(5);
				plan_tree.SetItemText(subRoot4, treeNode_str[5] + L": " + db_content);//threshold
			}
		}
		delete spl_wnd->db_status;
		break;
	}
	case 3://update selected model info
	{
		int index_ = plan_tree.GetItemData(plan_tree.GetParentItem(selected_item));
		temp_int = plan_tree.GetItemData(selected_item);
		db_command.Format(L"UPDATE '%s' SET '%s' = '%s' WHERE i_index == %d",
			model_add, title_str[temp_int], content, index_);
		BOOL access_sign = spl_wnd->modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			return FALSE;
		}
		break;
	}
	default:
		break;
	}

	return nReturn;
}

//Press ENTER Button
void CG_SUB_InspectionDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if (mdy_pln && m_Edit)
	{
		func_btn.SetFocus();
	}
	if (inquery_pswd)
	{
		SetTimer(-2, 900, NULL);
		if (MessageBox(L"密码错误。", L"异常信息", MB_ICONERROR | MB_OK) == IDOK)
		{
			pswd_edt.SetWindowText(NULL);
			pswd_state = FALSE;
			temp_int--;
		}
		if (temp_int < 1)
		{
			functionarea_init(0);
			inquery_pswd = FALSE;
			pswd_state = FALSE;
			add_md = FALSE;
			return;
		}
	}
}

//Modify Date Ctrl
void CG_SUB_InspectionDlg::OnDtnDatetimechangedatepick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	CTime m_date;
	datepick.GetTime(m_date);
	if (inquery_dat)
	{
		planlist_ini(3);
	}
	else if (inquery_pln)
	{
		planlist_ini(2);
	}
}

//Function Area Initialization
void CG_SUB_InspectionDlg::functionarea_init(int mode_)
{
	inquery_pswd = FALSE;
	switch (mode_)
	{
	case -1:
	{
		pWnd = GetDlgItem(IDC_func_button);
		pWnd->GetWindowRect(ori_rect);
		pWnd = GetDlgItem(IDC_datepick);
		pWnd->GetWindowRect(datepick_);
		ScreenToClient(datepick_);
		pWnd = GetDlgItem(IDC_model_sel);
		pWnd->GetWindowRect(mdl_sel);
		ScreenToClient(mdl_sel);
		pWnd = GetDlgItem(IDC_func_button);
		pWnd->SetWindowPos(NULL, 0, 0, ori_rect.Width() + 170, ori_rect.Height(),
			SWP_NOZORDER | SWP_NOMOVE);
		current_date = theApp.currentTime;
		datepick.SetFormat(L"yyyy-MM-dd");
		break;
	}
	case 0:
	{
		pswd_edt.ShowWindow(FALSE);
		datepick.ShowWindow(FALSE);
		model_sel.ShowWindow(FALSE);
		pWnd = GetDlgItem(IDC_func_button);
		pWnd->SetWindowPos(NULL, 0, 0, ori_rect.Width() + 170, ori_rect.Height(),
			SWP_NOZORDER | SWP_NOMOVE);
		break;
	}
	case 1://pswd
	{
		temp_int = 3;
		datepick.ShowWindow(FALSE);
		model_sel.ShowWindow(FALSE);
		pWnd = GetDlgItem(IDC_func_button);
		pWnd->SetWindowPos(NULL, 0, 0, ori_rect.Width(), ori_rect.Height(),
			SWP_NOZORDER | SWP_NOMOVE);
		pswd_edt.ShowWindow(TRUE);
		pswd_edt.SetFocus();
		inquery_pswd = TRUE;
		break;
	}
	case 2://add
	{
		pswd_edt.ShowWindow(FALSE);
		datepick.ShowWindow(FALSE);
		model_sel.ShowWindow(TRUE);
		pWnd = GetDlgItem(IDC_model_sel);
		pWnd->SetWindowPos(NULL, mdl_sel.TopLeft().x, mdl_sel.TopLeft().y - 40,
			mdl_sel.Width(), mdl_sel.Height() + 100, SWP_NOZORDER);
		SetDlgItemText(IDC_plan_area, L"添加生产计划");
		break;
	}
	case 3://chk
	{
		pswd_edt.ShowWindow(FALSE);
		model_sel.ShowWindow(FALSE);
		datepick.ShowWindow(TRUE);
		pWnd = GetDlgItem(IDC_datepick);
		pWnd->SetWindowPos(NULL, datepick_.TopLeft().x, datepick_.TopLeft().y - 80,
			datepick_.Width(), datepick_.Height() + 80, SWP_NOZORDER);
		SetDlgItemText(IDC_plan_area, L"数据查询");
		break;
	}
	default:
		break;
	}

}

//Change Target Model
void CG_SUB_InspectionDlg::OnCbnSelchangemodelsel()
{
	// TODO: Add your control notification handler code here
	if (add_md)
	{
		planlist_ini(-1);
	}
	else
	{
		planlist_ini(1);
		mdy_pln = FALSE;
	}
}

//Finish Info Modification
void CG_SUB_InspectionDlg::OnKillfocusEdit()
{
	CString tmp_node;
	m_Edit.GetWindowText(mdy_data);
	temp_str = plan_tree.GetItemText(selected_item);
	int size_ = temp_str.ReverseFind(':');
	if (size_ == -1)
	{
		tmp_node = temp_str;
	}
	else
	{
		tmp_node = temp_str.Mid(0, size_);
	}
	plan_tree.SetItemText(selected_item, tmp_node + L": " + mdy_data);
	database_operation(3, mdy_data);
	m_Edit.DestroyWindow();
}

#pragma region Mouse Operation
//Left ButtonDown
void CG_SUB_InspectionDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnLButtonDown(nFlags, point);
}

//Left ButtonUp
void CG_SUB_InspectionDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bIsDrag)
	{
		plan_tree.SelectItem(NULL);
		CPoint treePt(point);
		MapWindowPoints(&plan_tree, &treePt, 1);
		HTREEITEM hItem = plan_tree.HitTest(treePt);
		if (NULL != hItem)
		{
			int index_ = plan_tree.GetItemData(hItem);
			copy_item(hItem, index_);
		}
		else
		{
			if (MessageBox(L"是否删除所选条目内容 ?", L"Warning", MB_ICONWARNING | MB_OKCANCEL) == IDOK)
			{
				index_numbering(1);
			}
			else
			{
				return;
			}
		}
		plan_tree.SelectDropTarget(NULL);
		m_pImageList->DragLeave(&plan_tree);
		m_pImageList->EndDrag();
	}
	m_bIsDrag = FALSE;
	::ReleaseCapture();
	CDialogEx::OnLButtonUp(nFlags, point);
}

//Mouse Move
void CG_SUB_InspectionDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bIsDrag)
	{
		CPoint treePt(point);
		CPoint screenPt(point);
		MapWindowPoints(&plan_tree, &treePt, 1);
		ClientToScreen(&screenPt);
		CWnd* pCurWindow = WindowFromPoint(screenPt);
		if (pCurWindow != &plan_tree)
		{
			m_pImageList->DragShowNolock(FALSE);
			plan_tree.SelectDropTarget(m_hDragItem);
		}
		else
		{
			HTREEITEM hItem = plan_tree.HitTest(treePt);
			if (NULL != hItem)
			{
				m_pImageList->DragShowNolock(FALSE);//
				plan_tree.SelectDropTarget(hItem);
				m_pImageList->DragShowNolock(TRUE);//
			}
		}
		m_pImageList->DragMove(treePt);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}
#pragma endregion

//Display Instruction 
void CG_SUB_InspectionDlg::instruction_output()
{
	if (!initialize_sgn)
	{
		CString strValue = L"NULL";
		USES_CONVERSION;
		CString strConfigIniPath = A2T(theApp.instruction_file);
		TCHAR szBuffer[MAX_PATH] = { 0 };
		int nBufferSize = GetPrivateProfileSection(L"INFO", szBuffer, MAX_PATH, strConfigIniPath);
		TCHAR szKey[MAX_PATH] = { 0 };
		CString strKey = _T("");
		CString strKeyName = _T("");
		CString strKeyValue = _T("");
		strVecAccount.clear();
		for (int n = 0, i = 0; n < nBufferSize; n++)
		{
			if (szBuffer[n] == 0)
			{
				szKey[i] = 0;
				strKey = szKey;
				strKeyName = strKey.Left(strKey.Find('='));
				strKeyValue = strKey.Mid(strKey.Find('=') + 1);
				strValue.Format(strKeyName + L": " + strKeyValue + L"\r\n");
				strVecAccount.push_back(strValue);
				info_edit.ReplaceSel(strValue);
				i = 0;
			}
			else
			{
				szKey[i] = szBuffer[n];
				i++;
			}
		}
		strVecAccount.shrink_to_fit();
	}
	else
	{
		info_edit.SetWindowText(NULL);
		for (size_t i = 0; i < strVecAccount.size(); i++)
		{
			info_edit.ReplaceSel(strVecAccount[i]);
		}
		UpdateData(FALSE);
		info_edit.LineScroll(info_edit.GetLineCount() - 15);
	}
}
#pragma endregion

#pragma region TreeCtrl
void ClxTreeCtrl::OnDropFiles(HDROP hDropInfo)
{


}

//Tree Ctrl initialization
int CG_SUB_InspectionDlg::planlist_ini(int mode_)
{
	int nReturn = 0;
	switch (mode_)
	{
	case -2:
	{
		database_operation(1, model_add);
		new_inspectcontent(hRoot, newmodel_no);
		break;
	}
	case -1:
	{
		plan_tree.DeleteAllItems();
		model_sel.GetWindowText(model_add);
		//model name
		hRoot = plan_tree.InsertItem(model_add, 0, 0, TVI_ROOT, TVI_LAST);
		database_operation(0, model_add);
		if (temp_int == 0)//new
		{
			database_operation(1, model_add);
			new_inspectcontent(hRoot, newmodel_no);
		}
		else//modify
		{
			mdy_md = TRUE;
			database_operation(2, model_add);
		}
		temp_int = 0;
		break;
	}
	case 0://init
	{
		plan_tree.DeleteAllItems();
		hRoot = plan_tree.InsertItem(current_date, 0, 0, TVI_ROOT, TVI_LAST);
		break;
	}
	case 1://add
	{
		plan_num++;
		model_sel.GetWindowText(model_add);
		if (plan_tree.GetItemText(hRoot) == L"")
		{
			hRoot = plan_tree.InsertItem(current_date, 0, 0, TVI_ROOT, TVI_LAST);
		}
		subRoot = plan_tree.InsertItem(model_add, 1, 1, hRoot, TVI_LAST);
		plan_tree.SetItemData(subRoot, plan_num);
		subRoot1 = plan_tree.InsertItem(treeNode_str[0], 1, 1, subRoot, TVI_LAST);
		plan_tree.SetItemData(subRoot1, 0);
		subRoot2 = plan_tree.InsertItem(treeNode_str[1], 1, 1, subRoot, TVI_LAST);
		plan_tree.SetItemData(subRoot2, 0);
		subRoot3 = plan_tree.InsertItem(treeNode_str[2], 1, 1, subRoot, TVI_LAST);
		plan_tree.SetItemData(subRoot3, 0);
		plan_tree.Expand(hRoot, TVE_EXPAND);
		plan_tree.Expand(subRoot, TVE_EXPAND);
		break;
	}
	case 2://check plan
	{
		CString temp_;
		plan_tree.DeleteAllItems();
		if (inspect_sgn)
		{
			temp_ = current_date;
		}
		else
		{
			datepick.GetWindowText(temp_);
		}
		temp_str.Format(L"temp\\plan\\" + temp_ + L".ini");
		USES_CONVERSION;
		char* file_nme = T2A(temp_str.GetBuffer(0));
		temp_str.ReleaseBuffer();
		if (_access(file_nme, 0) == -1)
		{
			SetTimer(0, 900, NULL);
			info_edit.SetWindowText(L"无法查询生产计划，请确认日期正确。\
\r\n或添加当日生产计划。");
			hRoot = plan_tree.InsertItem(current_date, 0, 0, TVI_ROOT, TVI_LAST);
			nReturn = -1;
		}
		else
		{
			queryTreeNode(plan_tree, hRoot, temp_str);
		}
		break;
	}
	case 3://check dat
	{
		CString temp_;
		plan_tree.DeleteAllItems();
		datepick.GetWindowText(temp_);
		temp_str.Format(L"temp\\error\\" + temp_ + L".ini");

		USES_CONVERSION;
		char* file_nme = T2A(temp_str.GetBuffer(0));
		temp_str.ReleaseBuffer();
		if (_access(file_nme, 0) == -1)
		{
			SetTimer(0, 900, NULL);
			info_edit.SetWindowText(L"无法查询检查数据，请确认日期正确。");
		}
		else
		{
			queryTreeNode(plan_tree, hRoot, temp_str);
		}
		break;
	}

	default:
		break;
	}


	return nReturn;
}

//Select Item in the Tree Ctrl
void CG_SUB_InspectionDlg::OnTvnSelchangedplan(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

//Drag Item in the Tree Ctrl
void CG_SUB_InspectionDlg::OnTvnBegindragplan(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	m_hDragItem = pNMTreeView->itemNew.hItem;
	CPoint treePt = pNMTreeView->ptDrag;
	CString label_;
	MapWindowPoints(&plan_tree, &treePt, 1);
	if (NULL == m_hDragItem)
	{
		return;
	}
	label_ = plan_tree.GetItemText(plan_tree.GetParentItem(m_hDragItem));
	if (label_ != current_date)
	{
		return;

	}

	m_pImageList = plan_tree.CreateDragImage(m_hDragItem);
	if (NULL == m_pImageList)
	{
		return;
	}

	m_pImageList->BeginDrag(0, CPoint(0, 0)); //拖拽图像相对于鼠标焦点的偏移坐标
	m_pImageList->DragEnter(&plan_tree, treePt);//设置图像初次显示的位置（包含偏移量）并锁定窗口为m_treeIndicators
	m_bIsDrag = TRUE;
	mdy_pln = TRUE;
	SetCapture();

	*pResult = 0;
}

//Tree Ctrl Menu Pop-up
void CG_SUB_InspectionDlg::OnNMRClickplan(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	if (inspect_sgn)
	{
		SetTimer(-2, 900, NULL);
		MessageBox(L"请先停止当前检测。", L"异常信息", MB_ICONINFORMATION | MB_OK);
		return;
	}
	/*if (mdy_pln == TRUE && add_md == FALSE)
	{
	SetTimer(-2, 900, NULL);
	MessageBox(L"请单击“开始检测”保存当前计划。", L"提示信息", MB_ICONINFORMATION | MB_OK);
	return;
	}*/
	// Load menu
	CMenu m_Menu, *p_Menu = NULL;
	m_Menu.LoadMenu(IDR_MENU1);
	//
	CPoint pt;
	GetCursorPos(&pt);
	plan_tree.ScreenToClient(&pt);
	UINT uFlags = 0;
	HTREEITEM hItem = plan_tree.HitTest(pt, &uFlags);
	plan_tree.ClientToScreen(&pt);
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		plan_tree.Select(hItem, TVGN_CARET);
		CString item_tiltle;
		item_tiltle = plan_tree.GetItemText(hItem);
		item_tiltle = item_tiltle.Mid(0, 5);
		if (item_tiltle == L"计划生产量" || add_md)
		{
			selected_item = hItem;
			p_Menu = (CMenu*)m_Menu.GetSubMenu(1);//0
			if (p_Menu != NULL)
				p_Menu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, pt.x, pt.y, this);
			p_Menu = NULL;
		}
		else
		{
			return;
		}

	}
	else//if (iCode)
	{
		p_Menu = (CMenu*)m_Menu.GetSubMenu(0);//1
		if (p_Menu != NULL)
			p_Menu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, pt.x, pt.y, this);
		p_Menu = NULL;
	}
}

//Add Production Plan Menu
void CG_SUB_InspectionDlg::OnPlanmenu1addpln()
{
	// TODO: Add your command handler code here
	add_pln = TRUE;
	delete[] treeNode_str;
	treeNode_str = new CString[3];
	treeNode_str[0] = L"计划生产量";
	treeNode_str[1] = L"实际生产量";
	treeNode_str[2] = L"NG发生率";
	if (!pswd_state)
	{
		functionarea_init(1);
	}
	else
	{
		functionarea_init(2);
	}
}

//Check Production Plan
void CG_SUB_InspectionDlg::OnPlanmenu1chkpln()
{
	// TODO: Add your command handler code here
	inquery_pln = TRUE;
	inquery_dat = FALSE;
	if (!pswd_state)
	{
		functionarea_init(1);
	}
	else
	{
		functionarea_init(3);
	}
}

//Check Inspection Data
void CG_SUB_InspectionDlg::OnPlanmenu1chkdata()
{
	// TODO: Add your command handler code here
	inquery_dat = TRUE;
	inquery_pln = FALSE;
	if (!pswd_state)
	{
		functionarea_init(1);
	}
	else
	{
		functionarea_init(3);
	}
	//CString appPathFile;
	//appPathFile.Format(L"temp\\error\\2018-10-21.ini");
	//unsigned short int sUnicodeFlag = 0xfeff;
	//FILE *fp;
	//fp = _wfopen(appPathFile, _T("wb"));
	//fwrite(&sUnicodeFlag, sizeof(short int), 1, fp);
	//fclose(fp);
	//CString _str;
	//WritePrivateProfileString(L"NODE0", L"name", L"2018-10-21", appPathFile);
	//_str.Format(L"%d", 0);
	//WritePrivateProfileString(L"NODE0", L"index", _str, appPathFile);
	//_str.Format(L"%d", 0);
	//WritePrivateProfileString(L"NODE0", L"id", _str, appPathFile);
	//_str.Format(L"%d", 1);
	//WritePrivateProfileString(L"NODE0", L"layer", _str, appPathFile);
	////
	//WritePrivateProfileString(L"NODE1" , L"name", L"11-15-35-AJ6", appPathFile);
	//_str.Format(L"%d", 1);
	//WritePrivateProfileString(L"NODE1" , L"index", _str, appPathFile);
	//_str.Format(L"%d", 0);
	//WritePrivateProfileString(L"NODE1" , L"id", _str, appPathFile);
	//_str.Format(L"%d", 2);
	//WritePrivateProfileString(L"NODE1" , L"layer", _str, appPathFile);
	////
	//WritePrivateProfileString(L"NODE2", L"name", L"固定块1-异品检出", appPathFile);
	//_str.Format(L"%d", 2);
	//WritePrivateProfileString(L"NODE2", L"index", _str, appPathFile);
	//_str.Format(L"%d", 0);
	//WritePrivateProfileString(L"NODE2", L"id", _str, appPathFile);
	//_str.Format(L"%d", 3);
	//WritePrivateProfileString(L"NODE2", L"layer", _str, appPathFile);
	////
	//WritePrivateProfileString(L"NODE3", L"name", L"11-17-46-JG3", appPathFile);
	//_str.Format(L"%d", 3);
	//WritePrivateProfileString(L"NODE3", L"index", _str, appPathFile);
	//_str.Format(L"%d", 0);
	//WritePrivateProfileString(L"NODE3", L"id", _str, appPathFile);
	//_str.Format(L"%d", 2);
	//WritePrivateProfileString(L"NODE3", L"layer", _str, appPathFile);
	////
	//WritePrivateProfileString(L"NODE4", L"name", L"卡脚3-异品检出", appPathFile);
	//_str.Format(L"%d", 4);
	//WritePrivateProfileString(L"NODE4", L"index", _str, appPathFile);
	//_str.Format(L"%d", 0);
	//WritePrivateProfileString(L"NODE4", L"id", _str, appPathFile);
	//_str.Format(L"%d", 3);
	//WritePrivateProfileString(L"NODE4", L"layer", _str, appPathFile);
	////
	//WritePrivateProfileString(L"NODE5", L"name", L"11-17-55-AJ6", appPathFile);
	//_str.Format(L"%d", 5);
	//WritePrivateProfileString(L"NODE5", L"index", _str, appPathFile);
	//_str.Format(L"%d", 0);
	//WritePrivateProfileString(L"NODE5", L"id", _str, appPathFile);
	//_str.Format(L"%d", 2);
	//WritePrivateProfileString(L"NODE5", L"layer", _str, appPathFile);
	////
	//WritePrivateProfileString(L"NODE6", L"name", L"标签2-欠品检出", appPathFile);
	//_str.Format(L"%d", 6);
	//WritePrivateProfileString(L"NODE6", L"index", _str, appPathFile);
	//_str.Format(L"%d", 0);
	//WritePrivateProfileString(L"NODE6", L"id", _str, appPathFile);
	//_str.Format(L"%d", 3);
	//WritePrivateProfileString(L"NODE6", L"layer", _str, appPathFile);
	//_str.Format(L"%d", 7);
	//WritePrivateProfileString(L"INFO", L"filesum", _str, appPathFile);
}

//Add Inspection Model Info
void CG_SUB_InspectionDlg::OnPlanmenu1addmodel()
{
	// TODO: Add your command handler code here
	add_md = TRUE;
	delete[] treeNode_str;
	delete[] title_str;
	treeNode_str = new CString[6];
	title_str = new CString[6];
	treeNode_str[0] = L"检查项目";
	treeNode_str[1] = L"相机编号";
	treeNode_str[2] = L"检查内容";
	treeNode_str[3] = L"图像名称";
	treeNode_str[4] = L"ROI设定";
	treeNode_str[5] = L"检查阈值";
	//
	title_str[0] = L"i_index";
	title_str[1] = L"camera_index";
	title_str[2] = L"contents_remarks";
	title_str[3] = L"image_file";
	title_str[4] = L"ROI";
	title_str[5] = L"threshold";
	if (!pswd_state)
	{
		new_item = new HTREEITEM[15];
		functionarea_init(1);
	}
}

//Add Inspection Model Content Info
void CG_SUB_InspectionDlg::OnPlanmenu1addcontent()
{
	// TODO: Add your command handler code here
	if (pswd_state  && add_md)//== TRUE
	{
		temp_str = plan_tree.GetItemText(subRoot2);
		temp_int = temp_str.ReverseFind(':');
		temp_str = temp_str.Mid(temp_int + 2);
		if (temp_str == _T("nul"))
		{
			SetTimer(0, 800, NULL);
			info_edit.SetWindowText(L"当前检查内容未添加完整，请确认。");
			return;
		}
		add_content = TRUE;
		planlist_ini(-2);
	}
	else
	{
		SetTimer(0, 100, NULL);
		info_edit.SetWindowText(L"no use");
		return;
	}
}

//Modify  Data in the Tree Ctrl
void CG_SUB_InspectionDlg::OnPlanmenu2modpln()
{
	// TODO: Add your command handler code here
	mdy_pln = TRUE;
	m_Edit.Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN,
		CRect(0, 0, 0, 0), this, IDC_crtd_EDIT);

	m_Edit.SetFont(this->GetFont(), FALSE);
	m_Edit.SetParent(&plan_tree);
	CRect  EditRect;
	plan_tree.GetItemRect(selected_item, EditRect, TRUE);
	EditRect.SetRect(EditRect.left + EditRect.Width() + 10, EditRect.top + 1,
		EditRect.right + EditRect.Width() + 10, EditRect.bottom - 1);

	m_Edit.MoveWindow(&EditRect);
	m_Edit.ShowWindow(SW_SHOW);
	m_Edit.SetFocus();
	m_Edit.SetSel(-1);
}

//Write TreeNode File
void CG_SUB_InspectionDlg::recordTreeNode(CTreeCtrl& m_tree, HTREEITEM hTreeItem,
	UINT& fileSum, int& layer, CString appPathFile)
{
	CString   strNode, _str, _id, _layer; //TVIS_BOLD
	_str.Format(L"%d", fileSum++);
	strNode = m_tree.GetItemText(hTreeItem);
	_id.Format(L"%d", m_tree.GetItemData(hTreeItem));
	_layer.Format(L"%d", layer);
	WritePrivateProfileString(L"NODE" + _str, L"name", strNode, appPathFile);
	WritePrivateProfileString(L"NODE" + _str, L"index", _str, appPathFile);
	WritePrivateProfileString(L"NODE" + _str, L"id", _id, appPathFile);
	WritePrivateProfileString(L"NODE" + _str, L"layer", _layer, appPathFile);
	HTREEITEM hFirstChild = m_tree.GetChildItem(hTreeItem);
	if (hFirstChild != NULL)
	{
		layer++;
		recordTreeNode(m_tree, hFirstChild, fileSum, layer, appPathFile);
		layer--;
	}
	hFirstChild = m_tree.GetNextItem(hTreeItem, TVGN_NEXT);
	if (hFirstChild != NULL)
		recordTreeNode(m_tree, hFirstChild, fileSum, layer, appPathFile);
}

//Read TreeNode File
void CG_SUB_InspectionDlg::queryTreeNode(CTreeCtrl& m_tree, HTREEITEM& hTreeItem,
	CString appPathFile)
{
	TCHAR   inBuf[255];
	CString   _layer, strNode, _str;
	int currLayer = 0;
	int _id = 0;
	int rec_layer = 0;
	HTREEITEM m_htreeItem = TVI_ROOT;// TVI_ROOT;
	HTREEITEM m_ntreeItem = TVI_ROOT;
	//------------------
	plan_num = 0;
	int _fileSum = GetPrivateProfileInt(L"INFO", L"filesum", NULL, appPathFile);
	for (int i = 0; i < _fileSum; i++)
	{
		_str.Format(L"%d", i);
		_layer.Format(L"layer%d", i);
		GetPrivateProfileString(L"NODE" + _str, L"layer", NULL, inBuf, 255, appPathFile);
		_layer = inBuf;
		rec_layer = _ttoi(_layer);
		GetPrivateProfileString(L"NODE" + _str, L"name", NULL, inBuf, 255, appPathFile);
		strNode = inBuf;
		GetPrivateProfileString(L"NODE" + _str, L"id", NULL, inBuf, 255, appPathFile);
		_id = _ttoi(inBuf);
		if (rec_layer == 1)//root
		{
			hTreeItem = m_tree.InsertItem(strNode, 0, 0);
			m_tree.SetItemData(hTreeItem, 0);
			m_htreeItem = hTreeItem;
			currLayer = rec_layer;
		}
		else
		{
			if (rec_layer < currLayer)//up
			{
				m_ntreeItem = m_htreeItem;
				plan_num++;
				while (rec_layer != currLayer)
				{
					m_ntreeItem = m_tree.GetParentItem(m_ntreeItem);
					--currLayer;
				}
				m_ntreeItem = m_tree.GetParentItem(m_ntreeItem);
				m_htreeItem = m_tree.InsertItem(strNode, 1, 1, m_ntreeItem, TVI_LAST);
				m_tree.SetItemData(m_htreeItem, _id);
			}
			else if (rec_layer > currLayer)//low
			{
				m_htreeItem = m_tree.InsertItem(strNode, 1, 1, m_htreeItem, TVI_LAST);
				m_tree.SetItemData(m_htreeItem, _id);
				currLayer++;
				m_tree.Expand(m_tree.GetParentItem(m_htreeItem), TVE_EXPAND);
			}
			else if (rec_layer == currLayer)//same
			{
				m_ntreeItem = m_tree.GetParentItem(m_htreeItem);
				m_htreeItem = m_tree.InsertItem(strNode, 1, 1, m_ntreeItem, TVI_LAST);
				m_tree.SetItemData(m_htreeItem, _id);
			}
		}
	}
	plan_num++;
}

//TreeNode Indexing
int CG_SUB_InspectionDlg::index_numbering(int mode_)
{
	HTREEITEM temp_item;

	switch (mode_)
	{
	case 0:
	{
		int index_ = 0;
		temp_item = plan_tree.GetChildItem(hRoot);
		while (temp_item != NULL)
		{
			plan_tree.SetItemData(temp_item, index_);
			temp_item = plan_tree.GetNextSiblingItem(temp_item);
			index_++;
		}
		break;
	}
	case 1:
	{
		plan_tree.DeleteItem(m_hDragItem);
		index_numbering(0);
		break;
	}
	default:
		break;
	}
	return -1;
}

//Tree Ctrl Copy Item
int CG_SUB_InspectionDlg::copy_item(HTREEITEM item, int index_)
{
	HTREEITEM hItem = item;
	CString strDrag = plan_tree.GetItemText(m_hDragItem);
	int datDrag = plan_tree.GetItemData(m_hDragItem);
	//
	HTREEITEM new_item = plan_tree.InsertItem(strDrag, 1, 1, hRoot, hItem);
	plan_tree.SelectItem(hItem);
	plan_tree.SetItemData(new_item, datDrag);
	m_pImageList->DragShowNolock(FALSE);
	if (plan_tree.ItemHasChildren(m_hDragItem))
	{
		hItem = plan_tree.GetChildItem(m_hDragItem);
		while (hItem != NULL)
		{
			strDrag = plan_tree.GetItemText(hItem);
			datDrag = plan_tree.GetItemData(hItem);
			HTREEITEM new_child = plan_tree.InsertItem(strDrag, 1, 1, new_item, TVI_LAST);
			plan_tree.SetItemData(new_child, datDrag);
			hItem = plan_tree.GetNextSiblingItem(hItem);
		}
	}
	plan_tree.Expand(new_item, TVE_EXPAND);
	plan_tree.DeleteItem(m_hDragItem);
	index_numbering(0);
	return -1;
}

//Add New Inspect Content
void CG_SUB_InspectionDlg::new_inspectcontent(HTREEITEM hRoot, int& newmodel_no)
{
	temp_str.Format(treeNode_str[0] + L"%d", newmodel_no);
	new_item[newmodel_no] = plan_tree.InsertItem(temp_str, 1, 1, hRoot, TVI_LAST);
	plan_tree.SetItemData(new_item[newmodel_no], newmodel_no);
	//camera index
	subRoot = plan_tree.InsertItem(treeNode_str[1], 1, 1, new_item[newmodel_no], TVI_LAST);
	plan_tree.SetItemData(subRoot, 1);
	//inspect content name
	subRoot1 = plan_tree.InsertItem(treeNode_str[2], 1, 1, new_item[newmodel_no], TVI_LAST);
	plan_tree.SetItemData(subRoot1, 2);
	//inspect image name
	subRoot2 = plan_tree.InsertItem(treeNode_str[3], 1, 1, new_item[newmodel_no], TVI_LAST);
	plan_tree.SetItemData(subRoot2, 3);
	//inspect ROI
	subRoot3 = plan_tree.InsertItem(treeNode_str[4], 1, 1, new_item[newmodel_no], TVI_LAST);
	plan_tree.SetItemData(subRoot3, 4);
	//inspect threshold
	subRoot4 = plan_tree.InsertItem(treeNode_str[5], 1, 1, new_item[newmodel_no], TVI_LAST);
	plan_tree.SetItemData(subRoot4, 5);
	plan_tree.Expand(hRoot, TVE_EXPAND);
	plan_tree.Expand(new_item[newmodel_no], TVE_EXPAND);
	newmodel_no++;
}
#pragma endregion

#pragma region Camera
int CG_SUB_InspectionDlg::camera_initialization()
{
	int nReturn = 0;
	//WEB Camera
	camera_dat = new camera_data[2];
	int op_code = ini_parser.ReadINI(theApp.camera_file);
	int size_ = 0;
	for (int i = 0; i < MAX_CAMERA; i++)
	{
		camera_dat[i].camera_index = i;
		temp_str = ini_parser.GetValue("Web Camera", L"frame_width", size_);
		camera_dat[i].frame_width = _ttoi(temp_str);
		temp_str = ini_parser.GetValue("Web Camera", L"frame_height", size_);
		camera_dat[i].frame_height = _ttoi(temp_str);
		temp_str = ini_parser.GetValue("Web Camera", L"focus", size_);
		camera_dat[i].focus = _ttoi(temp_str);
		camera_dat[i].camera.open(i);
		camera_dat[i].camera.set(CAP_PROP_FRAME_WIDTH, camera_dat[i].frame_width);
		camera_dat[i].camera.set(CAP_PROP_FRAME_HEIGHT, camera_dat[i].frame_height);
		camera_dat[i].camera.set(CAP_PROP_FOCUS, camera_dat[i].focus);
	}


	CTlFactory& TlFactory = CTlFactory::GetInstance();
	TlFactory.EnumerateDevices(camera_dat[2].lstdevices_basler);
	if (camera_dat[2].lstdevices_basler.empty())
	{
		if (MessageBox(L"Basler相机连接异常，单击确认键等待程序退出后，检查相机电源是否松动，并重启程序。", L"设备连接异常", MB_OK | MB_ICONERROR) == IDOK)
		{
			SetTimer(-2, 600, NULL);
			MessageBox(L"正在退出程序，请等待...", L"设备连接异常", MB_OK | MB_ICONWARNING);
		}
		nReturn = -1;
		return nReturn;
	}
	else
	{
		camera_dat[2].camera_basler.RegisterConfiguration(new CAcquireContinuousConfiguration, RegistrationMode_ReplaceAll, Ownership_TakeOwnership);

//		HICON _hIcon = NULL;
//		_hIcon = AfxGetApp()->LoadIcon(IDI_ICON77);
//		cam_indi_[2].SetIcon(_hIcon);
//		camera_act.Attach(CTlFactory::GetInstance().CreateFirstDevice());
//		camera_act.Open();
//		//camera_act.GetTLParams().HeartbeatTimeout.SetValue(9000);
//		camera_act.AcquisitionMode.SetValue(AcquisitionMode_Continuous);
//		CString cam_nam;
//		cam_nam = camera_act.GetDeviceInfo().GetModelName();
//		SetDlgItemText(IDC_caminuse, cam_nam);
//		SetTimer(1, 500, NULL);
//		MessageBox(L"相机连接成功", L"设备初始化");
//		// Carry out luminance control by using the "continuous" gain auto function.
//		AutoGainContinuous1(camera_act);
//		// Carry out luminance control by using the "continuous" exposure auto function.
//		AutoExposureContinuous1(camera_act);
//#pragma region Camera Initialization
//		SetTimer(1, 1000, NULL);
//		MessageBox(L"相机初始中，请等待...", L"设备初始化");
//		Sleep(500);
//		camera_act.TriggerMode.SetValue(TriggerMode_Off);
//		ShotImage(camera_act, m_StopWatch1);
//		long mclk = 0;
//		while (mclk<58000)
//		{
//			for (int i = 0; i < 10; i++)
//			{
//				mclk++;
//			}
//		}
//		camera_act.StopGrabbing();
//		camera_act.AcquisitionMode.SetValue(AcquisitionMode_Continuous);
//		camera_act.TriggerSelector.SetValue(TriggerSelector_FrameStart);
//		camera_act.TriggerMode.SetValue(TriggerMode_On);
//		camera_act.TriggerSource.SetValue(TriggerSource_Line1);
//		camera_act.TriggerActivation.SetValue(TriggerActivation_FallingEdge);
//		camera_act.TriggerDelayAbs.SetValue(635000);//900000
//		camera_act.Width.SetValue(IMAGE_WIDTH);
//		camera_act.Height.SetValue(IMAGE_HEIGHT);
//		/*HICON _hIcon = NULL;
//		_hIcon = AfxGetApp()->LoadIcon(IDI_ICON77);
//		cam_indi_[2].SetIcon(_hIcon);*/
//		SetTimer(1, 800, NULL);
//		MessageBox(L"相机已初始化完毕。", L"设备初始化");
//		tmp_.Format(L"Basler相机已成功打开，请等待检测开始。");
//		SetDlgItemText(IDC_instxt, tmp_);
#pragma endregion
	}
#pragma endregion

	ini_parser.Clear();
//	SetTimer(1, 500, NULL);
	return nReturn;
}


// void AutoGainContinuous(Camera_t& camera)
void CG_SUB_InspectionDlg::AutoGainContinuous(CBaslerGigEInstantCamera& camera_basler)
{
	// Check whether the Gain Auto feature is available.
	if (!IsWritable(camera_basler.GainAuto))
	{
		cout << "The camera does not support Gain Auto." << endl << endl;
		return;
	}
	// Maximize the grabbed image area of interest (Image AOI).
	if (IsWritable(camera_basler.OffsetX))
	{
		camera_basler.OffsetX.SetValue(camera_basler.OffsetX.GetMin());
	}
	if (IsWritable(camera_basler.OffsetY))
	{
		camera_basler.OffsetY.SetValue(camera_basler.OffsetY.GetMin());
	}
	camera_basler.Width.SetValue(camera_basler.Width.GetMax());
	camera_basler.Height.SetValue(camera_basler.Height.GetMax());

	// Set the Auto Function AOI for luminance statistics.
	// Currently, AutoFunctionAOISelector_AOI1 is predefined to gather
	// luminance statistics.
	camera_basler.AutoFunctionAOISelector.SetValue(AutoFunctionAOISelector_AOI1);
	camera_basler.AutoFunctionAOIOffsetX.SetValue(0);
	camera_basler.AutoFunctionAOIOffsetY.SetValue(0);
	camera_basler.AutoFunctionAOIWidth.SetValue(camera_basler.Width.GetMax());
	camera_basler.AutoFunctionAOIHeight.SetValue(camera_basler.Height.GetMax());

	// Set the target value for luminance control. The value is always expressed
	// as an 8 bit value regardless of the current pixel data output format,
	// i.e., 0 -> black, 255 -> white.
	camera_basler.AutoTargetValue.SetValue(80);

	// We are trying GainAuto = Continuous.
	cout << "Trying 'GainAuto = Continuous'." << endl;
	cout << "Initial Gain = " << camera_basler.GainRaw.GetValue() << endl;

	camera_basler.GainAuto.SetValue(GainAuto_Continuous);

	// When "continuous" mode is selected, the parameter value is adjusted repeatedly while images are acquired.
	// Depending on the current frame rate, the automatic adjustments will usually be carried out for
	// every or every other image unless the camera�s micro controller is kept busy by other tasks.
	// The repeated automatic adjustment will proceed until the "once" mode of operation is used or
	// until the auto function is set to "off", in which case the parameter value resulting from the latest
	// automatic adjustment will operate unless the value is manually adjusted.
	//	for (int n = 0; n < 20; n++)            // For demonstration purposes, we will grab "only" 20 images.
	//	{
	//		GrabResultPtr_t ptrGrabResult;
	//		camera.GrabOne(5000, ptrGrabResult);
	//#ifdef PYLON_WIN_BUILD
	//		Pylon::DisplayImage(1, ptrGrabResult);
	//#endif
	//
	//		//For demonstration purposes only. Wait until the image is shown.
	//		WaitObject::Sleep(100);
	//	}
	//	camera1.GainAuto.SetValue(GainAuto_Off); // Switch off GainAuto.
	//
	//	cout << "Final Gain = " << camera1.GainRaw.GetValue() << endl << endl;
}

// void AutoExposureContinuous(Camera_t& camera)
void CG_SUB_InspectionDlg::AutoExposureContinuous(CBaslerGigEInstantCamera& camera_basler)
{
	// Check whether the Exposure Auto feature is available.
	if (!IsWritable(camera_basler.ExposureAuto))
	{
		cout << "The camera does not support Exposure Auto." << endl << endl;
		return;
	}

	// Maximize the grabbed area of interest (Image AOI).
	if (IsWritable(camera_basler.OffsetX))
	{
		camera_basler.OffsetX.SetValue(camera_basler.OffsetX.GetMin());
	}
	if (IsWritable(camera_basler.OffsetY))
	{
		camera_basler.OffsetY.SetValue(camera_basler.OffsetY.GetMin());
	}
	camera_basler.Width.SetValue(camera_basler.Width.GetMax());
	camera_basler.Height.SetValue(camera_basler.Height.GetMax());

	// Set the Auto Function AOI for luminance statistics.
	// Currently, AutoFunctionAOISelector_AOI1 is predefined to gather
	// luminance statistics.
	camera_basler.AutoFunctionAOISelector.SetValue(AutoFunctionAOISelector_AOI1);
	camera_basler.AutoFunctionAOIOffsetX.SetValue(0);
	camera_basler.AutoFunctionAOIOffsetY.SetValue(0);
	camera_basler.AutoFunctionAOIWidth.SetValue(camera_basler.Width.GetMax());
	camera_basler.AutoFunctionAOIHeight.SetValue(camera_basler.Height.GetMax());

	// Set the target value for luminance control. The value is always expressed
	// as an 8 bit value regardless of the current pixel data output format,
	// i.e., 0 -> black, 255 -> white.
	camera_basler.AutoTargetValue.SetValue(80);

	cout << "ExposureAuto 'GainAuto = Continuous'." << endl;
	cout << "Initial exposure time = ";
	cout << camera_basler.ExposureTimeAbs.GetValue() << " us" << endl;

	camera_basler.ExposureAuto.SetValue(ExposureAuto_Continuous);

	// When "continuous" mode is selected, the parameter value is adjusted repeatedly while images are acquired.
	// Depending on the current frame rate, the automatic adjustments will usually be carried out for
	// every or every other image, unless the camera�s microcontroller is kept busy by other tasks.
	// The repeated automatic adjustment will proceed until the "once" mode of operation is used or
	// until the auto function is set to "off", in which case the parameter value resulting from the latest
	// automatic adjustment will operate unless the value is manually adjusted.
	//	for (int n = 0; n < 20; n++)    // For demonstration purposes, we will use only 20 images.
	//	{
	//		GrabResultPtr_t ptrGrabResult;
	//		camera.GrabOne(5000, ptrGrabResult);
	//#ifdef PYLON_WIN_BUILD
	//		Pylon::DisplayImage(1, ptrGrabResult);
	//#endif
	//
	//		//For demonstration purposes only. Wait until the image is shown.
	//		WaitObject::Sleep(100);
	//	}
	//	camera.ExposureAuto.SetValue(ExposureAuto_Off); // Switch off Exposure Auto.
	//
	//	cout << "Final exposure time = ";
	//	cout << camera.ExposureTimeAbs.GetValue() << " us" << endl << endl;

}

void CG_SUB_InspectionDlg::OnImageGrabbed(CInstantCamera& camera_basler, const CGrabResultPtr& ptrGrabResult_basler)
{

}

#pragma endregion
