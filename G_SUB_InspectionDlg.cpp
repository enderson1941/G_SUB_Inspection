
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
#define IDC_crtd_INFO 9001

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
	error_imagefile = L"temp\\error\\image\\";
	error_datafile = L"temp\\error\\data\\";
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
	ON_WM_CLOSE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_PLANMENU1_export, &CG_SUB_InspectionDlg::OnPlanmenu1export)
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
	//
	USES_CONVERSION;
	BOOL access_sign;
	if (_access(theApp.database_file, 0) == -1)
	{
		access_sign = modify_db.Open(A2T(theApp.database_file));
		database_operation(-4, L"");
		database_operation(-3, theApp.currentTime);
	}
	else
	{
		access_sign = modify_db.Open(A2T(theApp.database_file));
		database_operation(-2, theApp.currentTime);
	}
	database_operation(-1, L"");
	//
	functionarea_init(-1);
	m_hIcon = NULL;
	m_hIcon = (HICON)LoadImage(AfxGetApp()->m_hInstance, 
		MAKEINTRESOURCE(IDI_ICON4), IMAGE_ICON, 40, 40, LR_DEFAULTCOLOR);
	func_btn.SetIcon(m_hIcon);
	func_btn.SetWindowText(L"开始\r\n检测");
	instruction_output();
	initialize_sgn = TRUE;
	//
	///camera initialization
	camera_initialization();
	//
	COLORREF oldColor = RGB(240, 240, 240);
	plan_tree.SetBkColor(oldColor);
	plan_tree.SetImageList(&theApp.icontree_list, TVSIL_NORMAL);
	plan_tree.ModifyStyle(TVS_DISABLEDRAGDROP, 0);
	modify_history.clear();

	for (int i = 0; i < theApp.model_.size(); i++)
	{
		model_sel.AddString(theApp.model_[i]);
	}

	m_RectTracker.m_nStyle = CRectTracker::resizeOutside | CRectTracker::hatchedBorder;
	m_RectTracker.m_nHandleSize = 6;
	m_RectTracker.m_rect.SetRect(0, 0, 0, 0);
	//
	///repaint screen
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
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{
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
		if (m_RectTracker.m_rect.Height() > 0)//IsRectEmpty()
		{
			m_RectTracker.Draw(&dc);
		}
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
#pragma region clearSection
	load_sgn = TRUE;
	disp_image(IDC_inspec, paint_, gsub_ins, CRect(0, 0, 100, 100));
	add_md = FALSE;
	add_content = FALSE;
	add_pln = FALSE;
	mdy_pln = FALSE;
	inquery_pswd = FALSE;
	pswd_state = FALSE;
	inquery_pln = FALSE;
	inquery_dat = FALSE;
	mdy_md = FALSE;
	m_Info.DestroyWindow();
	functionarea_init(0);
	if (!cam_initializesign)
	{
		planlist_ini(0);
		SetTimer(0, 900, NULL);
		info_edit.SetWindowText(L"相机未初始化成功，不能进行检测。");
		return;
	}
#pragma endregion
	if (!inspect_sgn)
	{
		plan_tree.ModifyStyle(0, TVS_DISABLEDRAGDROP, 0);
		int ret = database_operation(-5, L"NULL");
		if (ret == 1)
		{
			return;
		}
		temp_str = plan_tree.GetItemText(hRoot);
		CString temp_;
		datepick.GetWindowText(temp_);
		if (temp_str == current_date || temp_str == temp_)
		{
			planlist_ini(4);
		}
		int ncode = planlist_ini(2);
		if (ncode != -1)
		{
			SetTimer(0, 100, NULL);
#pragma region Basler
			cam_basler.StopGrabbing();
			Sleep(200);
			cam_basler.TriggerMode.SetValue(TriggerMode_On);
			cam_basler.TriggerActivation.SetValue(TriggerActivation_RisingEdge);
			cam_basler.TriggerSelector.SetValue(TriggerSelector_FrameStart);
		//	cam_basler.TriggerDelay.SetValue(635000);
			cam_basler.TriggerDelayAbs.SetValue(635000);
			cam_basler.AcquisitionMode.SetValue(AcquisitionMode_Continuous);
			cam_basler.StartGrabbing(GrabStrategy_OneByOne, 
				GrabLoop_ProvidedByInstantCamera);
			cam_basler.AcquisitionStart();
			Sleep(200);
#pragma endregion
#pragma region Plan
			selected_item = plan_tree.GetChildItem(hRoot);
			temp_int = plan_tree.GetItemData(selected_item);
			while (temp_int == -1)
			{
				selected_item = plan_tree.GetNextSiblingItem(selected_item);
				temp_int = plan_tree.GetItemData(selected_item);
			}
			current_model = plan_tree.GetItemText(selected_item);
			BOOL op = get_produceinfo(selected_item);
			if (!op)
			{
				planlist_ini(0);
				return;
			}
			database_operation(5, current_model);
#pragma endregion
			inspect_sgn = TRUE;
			m_hIcon = NULL;
			m_hIcon = (HICON)LoadImage(AfxGetApp()->m_hInstance, 
				MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 40, 40, LR_DEFAULTCOLOR);
			func_btn.SetIcon(m_hIcon);
			func_btn.SetWindowText(L"停止\r\n检测");
		}
	}
	else
	{
		plan_tree.ModifyStyle(TVS_DISABLEDRAGDROP, 0);
		planlist_ini(4);
		inspect_sgn = FALSE;
		inspect_complete = FALSE;
		m_hIcon = NULL;
		m_hIcon = (HICON)LoadImage(AfxGetApp()->m_hInstance, 
			MAKEINTRESOURCE(IDI_ICON4), IMAGE_ICON, 40, 40, LR_DEFAULTCOLOR);
		func_btn.SetIcon(m_hIcon);
		func_btn.SetWindowText(L"开始\r\n检测");
		plan_tree.DeleteAllItems();
		cam_basler.StopGrabbing();
		cam_basler.AcquisitionStop();
		load_sgn = TRUE;
		disp_image(IDC_inspec, paint_, gsub_ins, CRect(0, 0, 100, 100), -1);
		SetTimer(0, 100, NULL);
		plan_num = 1;
		plan_produce = 0;
		real_produce = 0;
		ng_produce = 0;
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
	Mat tmp_img;
	IplImage cpy;
	CvvImage cimg;
	CDC* _pDC;
	HDC hDC;
	CRect rect;
	_pDC = pt->GetDlgItem(disp_ID)->GetDC();
	hDC = _pDC->GetSafeHdc();
	pt->GetDlgItem(disp_ID)->GetClientRect(&rect);
	//repaint
	if (load_sgn)
	{
		load_sgn = FALSE;
		CRect rect_p;
		rect_p = CRect(rect.TopLeft().x, rect.TopLeft().y, rect.BottomRight().x, rect.BottomRight().y);
		Mat grey_img = Mat(rect.Width(), rect.Height(), CV_8UC3, Scalar::all(240));
		cpy = grey_img;
		cimg.CopyOf(&cpy);
		cimg.DrawToHDC(hDC, &rect_p);
		return;
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
	disp_rect = img_rect;
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
			::SetForegroundWindow(hWnd);
			::SendMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, NULL);
			KillTimer(nIDEvent);
			KillTimer(1);
		}
		hWnd = ::FindWindow(NULL, L"设备连接异常");
		if (hWnd)
		{
			KillTimer(nIDEvent);
			/*::SetForegroundWindow(hWnd);*/
			::SendMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, NULL);
			SendMessage(WM_CLOSE);
		}
		hWnd = ::FindWindow(NULL, L"系统信息");
		if (hWnd)
		{
			KillTimer(nIDEvent);
			::SetForegroundWindow(hWnd);
			keybd_event(13, 0, 0, 0);
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
		for (int i = 0; i < MAX_CAMERA; i++)
		{
			cam_data[i].cam_web >> cam_data[i].frame;
		}
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
	m_Info.DestroyWindow();
	if (add_md)
	{
		if (pswd_text == theApp.admin_pass[1])
		{
			pswd_state = TRUE;
			pswd_edt.SetWindowText(NULL);
			functionarea_init(2);
			SetDlgItemText(IDC_plan_area, L"添加机种信息");
			plan_tree.ModifyStyle(TVS_DISABLEDRAGDROP, 0);
			mdy_md = TRUE;
		}
	}
	else
	{
		if (pswd_text == theApp.admin_pass[0] || pswd_text == theApp.admin_pass[1])
		{
			pswd_state = TRUE;
			pswd_edt.SetWindowText(NULL);
			if (add_pln)
			{
				functionarea_init(2);
				int op = planlist_ini(2);
				if (op == -1)
				{
					plan_num = 1;
				}
			}
			else if (inquery_pln || inquery_dat)
			{
				functionarea_init(3);
			}
			plan_tree.ModifyStyle(TVS_DISABLEDRAGDROP, 0);
		}
	}
}

//Database Operation
int CG_SUB_InspectionDlg::database_operation(int mode_, CString content)
{
	int nReturn = 0;
	CString db_command;
	BOOL access_sign;
	switch (mode_)
	{
	case -5:
	{
		db_command.Format(L"SELECT production_index, production_in FROM system_data");
		db_status = modify_db.Statement(db_command);
		if (db_status != NULL)
		{
			while ((db_status)->NextRow())
			{
				temp_str = (db_status)->ValueString(1);
				if (temp_str == L"NULL")
				{
					SetTimer(-2, 800, NULL);
					MessageBox(L"生产计划已完成，请继续添加。", L"提示信息", MB_OK | MB_ICONINFORMATION);
					nReturn = 1;
				}
				else
				{
					temp_str = (db_status)->ValueString(0);
					temp_index = _ttoi(temp_str);
				}
			}
		}
		delete db_status;
		break;
	}
	case -4:
	{
		db_command.Format(L"CREATE TABLE '%s' ( \r\n 'i_index' TEXT, \r\n \'cur_date' TEXT, \r\n \
			'production_index' TEXT, \r\n 'production_in'	TEXT, \r\n 'production_realtime' TEXT, \r\n \
'production_NG' TEXT, 'inspect_complete' TEXT, \r\n 'admin_pass1' TEXT, \r\n 'admin_pass2'	TEXT)", L"system_data");
		access_sign = modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			SendMessage(WM_CLOSE);
			return FALSE;
		}
		break;
	}
	case -3:
	{
		db_command.Format(_T("INSERT INTO '%s' VALUES ( %d, '%s', %d, '%s', %d, %d, %d, '%s', '%s')  "),
			L"system_data", 1, content, 0, L"nul", 0, 0, 0, L"f", L"h");
		access_sign = modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			nReturn = -1;
			return nReturn;
		}
		break;
	}
	case -2:
	{
		db_command.Format(L"UPDATE system_data SET cur_date = '%s' ", content);
		access_sign = modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			nReturn = -1;
			return nReturn;
		}
		break;
	}
	case -1:
	{
		db_command.Format(L"SELECT admin_pass1, admin_pass2 FROM system_data");
		db_status = modify_db.Statement(db_command);
		if (db_status != NULL)
		{
			while ((db_status)->NextRow())
			{
				theApp.admin_pass[0] = (db_status)->ValueString(0);
				theApp.admin_pass[1] = (db_status)->ValueString(1);
			}
		}
		delete db_status;
		break;
	}
	case 0://confirm selected model
	{
		db_command.Format(L"select count(*)  from sqlite_master where type = 'table' and name = '%s' ", content);
		db_status = modify_db.Statement(db_command);
		if (db_status != NULL)
		{
			while (db_status->NextRow())
			{
				temp_int = _ttoi(db_status->ValueString(0));
			}
		}
		delete db_status;
		break;
	}
	case 1://create model table
	{
		if (!add_content)
		{
			db_command.Format(L"CREATE TABLE '%s' ( \r\n 'i_index' TEXT, \r\n 'camera_index' TEXT, \r\n \
			'contents_remarks' TEXT, \r\n 'image_file'	TEXT, \r\n 'ROI' TEXT, \r\n 'threshold' TEXT)", content);
			access_sign = modify_db.DirectStatement(db_command);
			if (!access_sign)
			{
				nReturn = -1;
				return nReturn;
			}
		}
		db_command.Format(_T("INSERT INTO '%s' VALUES ( %d, %d, '%s', '%s', '%s', %.2f)  "),
			content, newmodel_no, 0, L"nul", L"nul", L"nul", 0.75f);
		access_sign = modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			nReturn = -1;
			return nReturn;
		}
		break;
	}
	case 2://check selected model
	{
		CString db_content;
		db_command.Format(L"SELECT * FROM %s", model_add);
		db_status = modify_db.Statement(db_command);
		if (db_status != NULL)
		{
			while (db_status->NextRow())
			{
				db_content = db_status->ValueString(0);
				newmodel_no = _ttoi(db_content);
				new_inspectcontent(hRoot, newmodel_no);
				db_content = db_status->ValueString(1);
				plan_tree.SetItemText(subRoot, treeNode_str[1] + L": " + db_content);//camera_index
				db_content = db_status->ValueString(2);
				plan_tree.SetItemText(subRoot1, treeNode_str[2] + L": " + db_content);//inspect_content
				db_content = db_status->ValueString(3);
				int ind = db_content.ReverseFind('\\');
				db_content = db_content.Mid(ind + 1);
				plan_tree.SetItemText(subRoot2, treeNode_str[3] + L": " + db_content);//image_file
				db_content = db_status->ValueString(4);
				plan_tree.SetItemText(subRoot3, treeNode_str[4] + L": " + db_content);//ROI
				db_content = db_status->ValueString(5);
				plan_tree.SetItemText(subRoot4, treeNode_str[5] + L": " + db_content);//threshold
			}
		}
		delete db_status;
		break;
	}
	case 3://update selected model info
	{
		int index_ = plan_tree.GetItemData(plan_tree.GetParentItem(selected_item));
		temp_int = plan_tree.GetItemData(selected_item);
		db_command.Format(L"UPDATE '%s' SET '%s' = '%s' WHERE i_index == %d",
			model_add, title_str[temp_int], content, index_);
		access_sign = modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			nReturn = -1;
			return nReturn;
		}
		break;
	}
	case 4:
	{
		db_command.Format(L"SELECT * FROM %s WHERE camera_index == %d", content, 
			camera_index);
		db_status = modify_db.Statement(db_command);
		USES_CONVERSION;
		if (db_status != NULL)
		{
			while (db_status->NextRow())
			{
				temp_int = 0;
				//contents remarks
				temp_str = db_status->ValueString(2);
				inspect_data[camera_index].contents_remarks.push_back(temp_str);
				//image file
				temp_str = db_status->ValueString(3);
				char* file_name = T2A(temp_str.GetBuffer(0));
				temp_str.ReleaseBuffer();
				Mat temp_image = imread(file_name);
				inspect_data[camera_index].image_file.push_back(temp_image);
				temp_int = temp_str.ReverseFind('\\');
				temp_str = temp_str.Mid(temp_int + 1, temp_int - 3);
				inspect_data[camera_index].contents_names.push_back(temp_str);
				//ROI
				temp_int = 0;
				Rect temp_rect;
				temp_str = db_status->ValueString(4);
				int* componts = new int[4];
				temp_str = temp_str.Trim();
				int index = temp_str.ReverseFind(',');
				while (index > 0)
				{
					componts[temp_int] = _ttoi(temp_str.Mid(index + 1));
					temp_str = temp_str.Mid(0, index);
					index = temp_str.ReverseFind(',');
					temp_int++;
				}
				componts[temp_int] = _ttoi(temp_str);
				temp_int = 0;
				temp_rect = Rect(componts[3], componts[2], componts[1], componts[0]);
				inspect_data[camera_index].ROI.push_back(temp_rect);
				//threshold
				temp_str = db_status->ValueString(5);
				inspect_data[camera_index].threshold.push_back(_ttof(temp_str));
				delete[] componts;
			}
			inspect_data[camera_index].number = 
				inspect_data[camera_index].contents_remarks.size();
		}
		delete db_status;
		break;
	}
	case 5:
	{
		if (content == L"NULL")
		{
			db_command.Format(L"UPDATE system_data SET production_index = %d, \
production_in = '%s', production_realtime = %d, production_NG = %d, inspect_complete = '%d' ", \
0, content, 0, 0, inspect_complete);
		}
		else
		{
			db_command.Format(L"UPDATE system_data SET production_index = %d, \
production_in = '%s', production_realtime = %d, production_NG = %d, inspect_complete = '%d'  ", \
current_index, content, real_produce, ng_produce, inspect_complete);
		}
		access_sign = modify_db.DirectStatement(db_command);
		if (!access_sign)
		{
			nReturn = -1;
			return nReturn;
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
	if (mdy_md | add_md)
	{
		func_btn.SetFocus();
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
		//
		dynamic_info = L"请输入管理员密码";
		CRect  EditRect;
		pWnd = GetDlgItem(IDC_pswd);
		pWnd->GetWindowRect(EditRect);
		ScreenToClient(&EditRect);
		create_edit(this, EditRect, dynamic_info, 1);
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
		//
		dynamic_info = L"请选择机种名称";
		CRect  EditRect;
		pWnd = GetDlgItem(IDC_model_sel);
		pWnd->GetWindowRect(EditRect);
		ScreenToClient(&EditRect);
		create_edit(this, EditRect, dynamic_info, 1);
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
		newmodel_no = 1;
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
	if (mdy_md)
	{
		if (tmp_node == L"图像名称")
		{
			mdy_data = L"model\\" + model_add + L"\\" + mdy_data;
		}
		database_operation(3, mdy_data);
		if (new_filesgn)
		{
			temp_str = clip_filepath + L"temp.bmp";
			CFile::Rename(temp_str, mdy_data);
			new_filesgn = FALSE;
		}
		if (tmp_node == L"相机编号")
		{
			int index_ = _ttoi(mdy_data);
			if (index_ < 0)
			{
				index_ = 0;
			}
			if (index_ > MAX_CAMERA)
			{
				index_ = MAX_CAMERA;
			}
			if (index_ < MAX_CAMERA)
			{
				cam_data[index_].cam_web >> cam_data[index_].frame;
				disp_image(IDC_inspec, cam_data[index_].frame, gsub_ins, 
					CRect(0, 0, 100, 100), -1);
				target_image = cam_data[index_].frame.clone();
			}
			else
			{
#pragma region Basler
				cam_basler.StopGrabbing();
				cam_basler.TriggerMode.SetValue(TriggerMode_On);
				Sleep(200);
				cam_basler.AcquisitionMode.SetValue(AcquisitionMode_Continuous);
				cam_basler.StartGrabbing(GrabStrategy_OneByOne, 
					GrabLoop_ProvidedByInstantCamera);
				cam_basler.AcquisitionStart();
				cam_basler.TriggerSource.SetValue(TriggerSource_Software);
				cam_basler.TriggerSoftware.Execute();
				/*cam_basler.TriggerSource.SetValue(TriggerSource_SoftwareSignal1);
				cam_basler.SoftwareSignalSelector.SetValue(SoftwareSignalSelector_SoftwareSignal1);
				cam_basler.SoftwareSignalPulse.Execute();*/
				Sleep(200);
				cam_basler.StopGrabbing();
				cam_basler.TriggerSource.SetValue(trigger_source);
#pragma endregion
				disp_image(IDC_inspec, basler_frame, gsub_ins, 
					CRect(0, 0, 100, 100), -1);
				target_image = basler_frame.clone();
			}
			clip_sgn = TRUE;
		}
		else
		{
			load_sgn = TRUE;
			clip_sgn = FALSE;
			disp_image(IDC_inspec, paint_, gsub_ins, CRect(0, 0, 100, 100), -1);
		}
	}
	if (tmp_node == L"计划生产量")
	{
		plan_tree.SetItemData(selected_item, _ttoi(mdy_data));
		CTime time(CTime::GetCurrentTime());
		temp_str.Format(L"%04d-%02d-%02d-%02d-%02d-%02d", 
			time.GetYear(),
			time.GetMonth(),
			time.GetDay(),
			time.GetHour(),
			time.GetMinute(),
			time.GetSecond());
		modify_history.push_back(temp_str);
	}
	m_Edit.DestroyWindow();
	mdy_pln = FALSE;
	m_RectTracker.m_rect.SetRectEmpty();
}

#pragma region Mouse Operation
//Left ButtonDown
void CG_SUB_InspectionDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CPoint cur_pos;
	CPoint start_point;
	CPoint clip_point;
	CRect cwrect;
	CRect clip_rect;
	start_point = point;
	clip_rect = disp_rect;
	clip_rect.TopLeft().x += 23;
	clip_rect.TopLeft().y += 40;
	clip_rect.BottomRight().x += 23;
	clip_rect.BottomRight().y += 40;
	clip_point.x = clip_rect.TopLeft().x;
	clip_point.y = clip_rect.TopLeft().y;
	start_point.x -= clip_point.x;
	start_point.y -= clip_point.y;

	GetCursorPos(&cur_pos);
	ClientToScreen(clip_rect);
	if (clip_rect.PtInRect(cur_pos) && clip_sgn)//cur_pos
	{
		ClipCursor(clip_rect);
		if (m_RectTracker.HitTest(point)<0)
		{
			m_RectTracker.TrackRubberBand(this, point, TRUE);
		}
		else
		{
			m_RectTracker.Track(this, point, TRUE);
			start_point = m_RectTracker.m_rect.TopLeft();
			start_point.x -= clip_point.x;
			start_point.y -= clip_point.y;
		}
		m_RectTracker.m_rect.NormalizeRect();
		cut_rect.x = start_point.x * scale_index;
		cut_rect.y = start_point.y * scale_index;
		cut_rect.width = m_RectTracker.m_rect.Width() *  scale_index;
		cut_rect.height = m_RectTracker.m_rect.Height() *  scale_index;

		temp_str.Format(L"Start Point(%d, %d)\r\nClip Rect(width: %d, height: %d)",
			cut_rect.x, cut_rect.y, cut_rect.width, cut_rect.height);
		info_edit.SetWindowText(temp_str);

		inspec_pic.GetWindowRect(&cwrect);
		ScreenToClient(cwrect);
	//	InvalidateRect(&cwrect, TRUE);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

//Right ButtonDown
void CG_SUB_InspectionDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (clip_sgn)
	{
		ClipCursor(NULL);
		clip_sgn = FALSE;
		USES_CONVERSION;
		HTREEITEM temp_item;
		temp_item = selected_item;
		temp_str = plan_tree.GetItemText(temp_item);
		while (temp_str.Mid(0,2) != L"图像")
		{
			temp_item = plan_tree.GetNextSiblingItem(temp_item);
			temp_str = plan_tree.GetItemText(temp_item);
		}
		temp_int = temp_str.ReverseFind(':');
		if (temp_int == -1)
		{
			new_filesgn = TRUE;
			CRect  EditRect;
			plan_tree.GetItemRect(temp_item, EditRect, TRUE);
			CString contents_reserved = plan_tree.GetItemText(temp_item);
			create_edit(&plan_tree, EditRect, contents_reserved);
			selected_item = temp_item;
			temp_str = L"temp.bmp";
		}
		else
		{
			temp_str = temp_str.Mid(temp_int + 2);
			if (temp_str == L"nul")
			{
				new_filesgn = TRUE;
				CRect  EditRect;
				plan_tree.GetItemRect(temp_item, EditRect, TRUE);
				CString contents_reserved = plan_tree.GetItemText(temp_item);
				create_edit(&plan_tree, EditRect, contents_reserved);
				selected_item = temp_item;
				temp_str = L"temp.bmp";
			}
		}
		clip_filepath = L"model\\" + model_add + L"\\";
		temp_str = clip_filepath + temp_str;
		temp_filename = T2A(temp_str.GetBuffer(0));
		temp_str.ReleaseBuffer();
		Mat clip_image = target_image(cut_rect);
		cv::imwrite(temp_filename, clip_image);
		//ROI
		temp_item = plan_tree.GetNextSiblingItem(temp_item);
		temp_str = plan_tree.GetItemText(temp_item);
		int size_ = temp_str.ReverseFind(':');
		if (size_ != -1)
		{
			temp_str = temp_str.Mid(0, size_);
		}
		CString roi_;
		int* set_roi = new int[4];
		set_roi[0] = cut_rect.tl().x - 40;
		if (set_roi[0] < 0)
		{
			set_roi[0] = 5;
		}
		set_roi[1] = cut_rect.tl().y - 40;
		if (set_roi[1] < 0)
		{
			set_roi[1] = 5;
		}
		set_roi[2] = cut_rect.width + 80;
		if (set_roi[0] + set_roi[2] > 1905)
		{
			set_roi[2] = 1905 - set_roi[0];
		}
		set_roi[3] = cut_rect.height + 80;
		if (set_roi[1] + set_roi[3] > 1060)
		{
			set_roi[3] = 1060 - set_roi[1];
		}
		roi_.Format(L"%d, %d, %d, %d", set_roi[0], set_roi[1], set_roi[2], set_roi[3]);
		plan_tree.SetItemText(temp_item, temp_str + L": " + roi_);
		selected_item = temp_item;
		database_operation(3, roi_);
		selected_item = plan_tree.GetPrevSiblingItem(selected_item);
		delete[] set_roi;
	}
	else
	{
		if (cam_basler.IsPylonDeviceAttached())
		{
			cam_basler.TriggerSource.SetValue(TriggerSource_Software);
			cam_basler.TriggerSoftware.Execute();
			Sleep(200);
		}
	}
	CDialogEx::OnRButtonDown(nFlags, point);
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
				mdy_pln = FALSE;
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

void CG_SUB_InspectionDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	plan_tree.DeleteAllItems();
	if (cam_initializesign)
	{
		for (int i = 0; i < MAX_CAMERA; i++)
		{
			if (cam_data[i].cam_web.isOpened())
			{
				cam_data[i].cam_web.release();
			}
		}
		if (cam_basler.IsPylonDeviceAttached())
		{
			cam_basler.StopGrabbing();
		}
	}
	delete[] cam_data;
	delete[] inspect_data;
	CDialogEx::OnCancel();
}

void CG_SUB_InspectionDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	SetTimer(-2, 800, NULL);
	MessageBox(L"程序正在退出，请稍后...", L"提示信息", 
		MB_OKCANCEL | MB_ICONINFORMATION);
	OnClose();
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
		model_sel.SetCurSel(-1);
		if (!PathIsDirectory(L"model\\"+ model_add))
		{
			::CreateDirectory(L"model\\" + model_add, NULL);
		}
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
	case 1://insert plan
	{
		model_sel.GetWindowText(model_add);
		model_sel.SetCurSel(-1);
		if (plan_tree.GetItemText(hRoot) != current_date)
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
		subRoot4 = plan_tree.InsertItem(treeNode_str[3], 1, 1, subRoot, TVI_LAST);
		plan_tree.SetItemData(subRoot4, 0);
		plan_tree.Expand(hRoot, TVE_EXPAND);
		plan_tree.Expand(subRoot, TVE_EXPAND);
		plan_num++;
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
			current_index = 1;
			nReturn = -1;
		}
		else
		{
			queryTreeNode(plan_tree, hRoot, temp_str);
		}
		database_operation(5, L"none");
		break;
	}
	case 3://check dat
	{
		CString temp_;
		plan_tree.DeleteAllItems();
		datepick.GetWindowText(temp_);
		temp_str.Format(L"temp\\error\\data\\" + temp_ + L".ini");

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
			//
			CString csDirPath;
			datepick.GetWindowText(csDirPath);
			csDirPath = error_imagefile + csDirPath;
			csDirPath += L"\\*.bmp";
			HANDLE file;
			WIN32_FIND_DATA fileData;
			char line[1024];
			char fn[1000];
			file = FindFirstFile(csDirPath.GetBuffer(), &fileData);
			m_FileList.push_back(fileData.cFileName);
			bool bState = false;
			bState = FindNextFile(file, &fileData);
			while (bState)
			{
				m_FileList.push_back(fileData.cFileName);
				bState = FindNextFile(file, &fileData);
			}
			m_FileList.shrink_to_fit();
		}
		break;
	}
	case 4://save plan
	{
		if (plan_tree.ItemHasChildren(hRoot))
		{
			UINT fileSum = 0;
			int layer = 1;
			CString appPathFile;
			appPathFile.Format(L"temp\\plan\\" + current_date + L".ini");
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
			for (int i = 0; i < modify_history.size(); i++)
			{
				_str.Format(L"Modified");
				WritePrivateProfileString(L"Modify", modify_history[i], _str,
					L"temp\\plan\\" + current_date + L".ini");
			}
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
	if (inquery_dat)
	{
		int index = -1;
		CString selected_date;
		datepick.GetWindowText(selected_date);
		selected_item = plan_tree.GetSelectedItem();
		CString selected_text = plan_tree.GetItemText(selected_item);//part
		for (int i = 0; i < m_FileList.size(); i++)
		{
			index = m_FileList[i].Find(selected_text, 0);
			if (index != -1)
			{
				USES_CONVERSION;
				temp_str = error_imagefile + selected_date + L"\\" + m_FileList[i];
				temp_filename = T2A(temp_str.GetBuffer(0));
				temp_str.ReleaseBuffer();
				Mat error_image = imread(temp_filename);
				if (error_image.data)
				{
					disp_image(IDC_inspec, error_image, gsub_ins, CRect(0, 0, 100, 100), -1);
				}
				break;
			}
		}
	}
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
	if (add_md || add_content || mdy_pln || mdy_md)
	{
		return;
	}
	add_pln = TRUE;
	delete[] treeNode_str;
	treeNode_str = new CString[4];
	treeNode_str[0] = L"计划生产量";
	treeNode_str[1] = L"实际生产量";
	treeNode_str[2] = L"NG发生率";
	treeNode_str[3] = L"检查状态";
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
		newmodel_no++;
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

//Export Check-out Data
void CG_SUB_InspectionDlg::OnPlanmenu1export()
{
	// TODO: Add your command handler code here
	CString wr_str;
	CString filePath;
	CString* data_;
	CStdioFile m_file;
	HTREEITEM sel_item[2];
	int mode_ = -1;
	int number = 1;
	datepick.GetWindowText(temp_str);
	if (!plan_tree.ItemHasChildren(hRoot))
	{
		SetTimer(0, 800, NULL);
		info_edit.SetWindowText(L"无数据导出，请确认日期正确。");
		return;
	}
	sel_item[0] = plan_tree.GetChildItem(hRoot);
	if (inquery_pln)
	{
		mode_ = 0;
		filePath = theApp.Desktopdir_ + L"\\" + temp_str + L"-生产计划导出.csv";
	}
	else if (inquery_dat)
	{
		mode_ = 1;
		filePath = theApp.Desktopdir_ + L"\\" + temp_str + L"-异常数据导出.csv";
	}
	else
	{
		return;
	}
	spl_wnd->wr_unicodefile(filePath);
	//CFile::modeCreate | CFile::modeNoTruncate |
	BOOL op_sign = m_file.Open((LPCTSTR)filePath, CFile::modeReadWrite | CFile::typeUnicode);
	if (!op_sign)
	{
		SetTimer(0, 800, NULL);
		info_edit.SetWindowText(L"目标文件无法打开。");
		return;
	}
	m_file.SeekToEnd();
	switch (mode_)
	{
	case 0://plan
	{
		data_ = new CString[5];
		wr_str = _T("G-SUB03 \t 生产计划导出");
		m_file.WriteString(wr_str);//(LPCTSTR)
		m_file.WriteString(L"\n");
		wr_str.Format(L"导出日期: \t %s ", theApp.currentTime);
		m_file.WriteString((LPCTSTR)wr_str);
		m_file.WriteString(L"\n");
		wr_str = _T(" No. \t 生产日期 \t 机种名称 \t 计划生产 \t 实际生产 \t NG发生 \t 检查状态 ");
		m_file.WriteString((LPCTSTR)wr_str);
		m_file.WriteString(L"\n");
		while (NULL != sel_item[0])
		{
			data_[0] = plan_tree.GetItemText(sel_item[0]);//model
			sel_item[1] = plan_tree.GetChildItem(sel_item[0]);
			data_[1] = plan_tree.GetItemText(sel_item[1]);//plan
			data_[1] = data_[1].Mid((data_[1].ReverseFind(':')) + 2);
			sel_item[1] = plan_tree.GetNextSiblingItem(sel_item[1]);
			data_[2] = plan_tree.GetItemText(sel_item[1]);//OK
			data_[2] = data_[2].Mid((data_[2].ReverseFind(':')) + 2);
			sel_item[1] = plan_tree.GetNextSiblingItem(sel_item[1]);
			data_[3] = plan_tree.GetItemText(sel_item[1]);//NG
			data_[3] = data_[3].Mid((data_[3].ReverseFind(':')) + 2);
			sel_item[1] = plan_tree.GetNextSiblingItem(sel_item[1]);
			data_[4] = plan_tree.GetItemText(sel_item[1]);//state
			data_[4] = data_[4].Mid((data_[4].ReverseFind(':')) + 2);
			wr_str.Format(L" %d \t %s \t %s \t %s \t %s \t %s \t %s",
				number, temp_str, data_[0], data_[1], data_[2], data_[3], data_[4]);
			m_file.WriteString((LPCTSTR)wr_str);
			m_file.WriteString(L"\n");
			number++;
			sel_item[0] = plan_tree.GetNextSiblingItem(sel_item[0]);		
		}
		delete[] data_;
		break;
	}
	case 1://data
	{
		data_ = new CString[6];
		wr_str = _T("G-SUB03 \t 异常数据导出");
		m_file.WriteString(wr_str);
		m_file.WriteString(L"\n");
		wr_str.Format(L"导出日期: \t %s ", theApp.currentTime);
		m_file.WriteString((LPCTSTR)wr_str);
		m_file.WriteString(L"\n");
		wr_str = _T(" No. \t 生产日期 \t 具体时间 \t 机种名称 \t 检查项目 \t 异常状况 ");
		m_file.WriteString((LPCTSTR)wr_str);
		m_file.WriteString(L"\n");
		while (NULL != sel_item[0])
		{
			data_[0] = plan_tree.GetItemText(sel_item[0]);
			data_[1] = data_[0].Mid(0, data_[0].ReverseFind('-'));//time
			data_[2] = data_[0].Mid((data_[0].ReverseFind('-')) + 1);//model
			sel_item[1] = plan_tree.GetChildItem(sel_item[0]);
			data_[3] = plan_tree.GetItemText(sel_item[1]);
			data_[4] = data_[3].Mid(0, data_[3].ReverseFind('-'));//remarks
			data_[5] = data_[3].Mid((data_[3].ReverseFind('-')) + 1);//error
			wr_str.Format(L" %d \t %s \t %s \t %s \t %s \t %s ",
				number, temp_str, data_[1], data_[2], data_[4], data_[5]);
			m_file.WriteString(wr_str);
			m_file.WriteString(L"\n");
			number++;
			sel_item[0] = plan_tree.GetNextSiblingItem(sel_item[0]);
		}
		delete[] data_;
		break;
	}
	default:
		break;
	}
	
	SetTimer(0, 800, NULL);
	info_edit.SetWindowText(L"数据已导出至桌面，请确认。");
	ShellExecute(NULL, _T("explore"), theApp.Desktopdir_, NULL, NULL, SW_SHOWNORMAL);
}

//Modify  Data in the Tree Ctrl
void CG_SUB_InspectionDlg::OnPlanmenu2modpln()
{
	// TODO: Add your command handler code here
	mdy_pln = TRUE;
	CRect  EditRect;
	plan_tree.GetItemRect(selected_item, EditRect, TRUE);
	CString contents_reserved = plan_tree.GetItemText(selected_item);
	create_edit(&plan_tree, EditRect, contents_reserved);
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
	plan_num = 1;
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
		if (strNode.Mid(0, 2) == L"实际")
		{
			if (_id == 0)
			{
				current_index = plan_num;
			}
		}
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
		plan_num = 1;
		temp_item = plan_tree.GetChildItem(hRoot);
		while (temp_item != NULL)
		{
			if (plan_tree.GetItemData(temp_item) != -1)
			{
				plan_tree.SetItemData(temp_item, plan_num);
				plan_num++;
			}
			temp_item = plan_tree.GetNextSiblingItem(temp_item);
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
}

//Dynamiclly Create Edit Ctrl
void CG_SUB_InspectionDlg::create_edit(CWnd* ctrl, CRect  EditRect, CString contents_reserved, int mode_)
{
	switch (mode_)
	{
	case 0:
	{
		m_Edit.Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN,
			CRect(0, 0, 0, 0), this, IDC_crtd_EDIT);
		m_Edit.SetFont(this->GetFont(), FALSE);
		m_Edit.SetParent(ctrl);//&plan_tree
		int index = contents_reserved.ReverseFind(':');
		if (index != -1)
		{
			contents_reserved = contents_reserved.Mid(index + 2);
		}
		else
		{
			contents_reserved = L" ";
		}
		EditRect.SetRect(EditRect.left + EditRect.Width() + 10, EditRect.top + 1,
			EditRect.right + EditRect.Width() + 10, EditRect.bottom - 1);

		m_Edit.MoveWindow(&EditRect);
		m_Edit.SetWindowText(contents_reserved);
		m_Edit.ShowWindow(SW_SHOW);
		m_Edit.SetFocus();
		m_Edit.SetSel(0, -1);
		break;
	}
	case 1:
	{
		m_Info.Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN | ES_READONLY,
			CRect(0, 0, 0, 0), this, IDC_crtd_INFO);
		m_Info.SetFont(this->GetFont(), FALSE);
		m_Edit.SetParent(ctrl);
		EditRect.SetRect(EditRect.TopLeft().x, EditRect.TopLeft().y + EditRect.Height() + 5,
			EditRect.BottomRight().x, EditRect.BottomRight().y + EditRect.Height() + 5);
		m_Info.MoveWindow(&EditRect);
		m_Info.SetWindowText(contents_reserved);
		m_Info.ShowWindow(SW_SHOW);
		break;
	}
	default:
		break;
	}
}

//Get Current Production Info
BOOL CG_SUB_InspectionDlg::get_produceinfo(HTREEITEM model)
{
	database_operation(0, current_model);
	if (temp_int == 0)
	{
		SetTimer(-2, 800, NULL);
		MessageBox(L"数据库中没有该机种信息，请重新添加。", L"提示信息", MB_OK | MB_ICONINFORMATION);
		return FALSE;
	}
	for (int i = 0; i < MAX_CAMERA + 1; i++)
	{
		camera_index = i;
		inspect_data[i].contents_remarks.clear();
		inspect_data[i].contents_remarks.clear();
		inspect_data[i].ROI.clear();
		inspect_data[i].threshold.clear();
		database_operation(4, current_model);
	}
	subRoot = plan_tree.GetChildItem(model);
	subRoot1 = plan_tree.GetNextSiblingItem(subRoot);
	subRoot2 = plan_tree.GetNextSiblingItem(subRoot1);
	subRoot3 = plan_tree.GetNextSiblingItem(subRoot2);
	plan_produce = plan_tree.GetItemData(subRoot);
	current_index = plan_tree.GetItemData(model);
	real_produce = plan_tree.GetItemData(subRoot1);
	ng_produce = plan_tree.GetItemData(subRoot2);
	delete[] treeNode_str;
	treeNode_str = new CString[4];
	treeNode_str[0] = L"计划生产量";
	treeNode_str[1] = L"实际生产量";
	treeNode_str[2] = L"NG发生率";
	treeNode_str[3] = L"检查状态";
	temp_str.Format(L": %d", real_produce);
	plan_tree.SetItemText(subRoot1, treeNode_str[1] + temp_str);
	temp_str.Format(L": %d", ng_produce);
	plan_tree.SetItemText(subRoot2, treeNode_str[2] + temp_str);
	temp_str.Format(L": %s", L"未完成");
	plan_tree.SetItemText(subRoot3, treeNode_str[3] + temp_str);
	return TRUE;
}
#pragma endregion

#pragma region Camera
int CG_SUB_InspectionDlg::camera_initialization()
{
	int nReturn = 0;
	cam_initializesign = FALSE;
	/*WEB Camera*/
	cam_data = new camera_data[MAX_CAMERA];
	inspect_data = new inspectcontents_data[MAX_CAMERA + 1];
	int op_code = ini_parser.ReadINI(theApp.camera_file);
	int size_ = 0;
	temp_str = ini_parser.GetValue("Camera", L"frame_width", size_);
	frame_width = _ttoi(temp_str);
	temp_str = ini_parser.GetValue("Camera", L"frame_height", size_);
	frame_height = _ttoi(temp_str);
	for (int i = 0; i < MAX_CAMERA; i++)//MAX_CAMERA
	{
		cam_data[i].camera_index = i;
		temp_str = ini_parser.GetValue("Camera", L"focus", size_);
		cam_data[i].focus = _ttoi(temp_str);
		cam_data[i].cam_web.open(CAP_DSHOW + i);
		if (cam_data[i].cam_web.isOpened())
		{
			cam_data[i].cam_web.set(CAP_PROP_FRAME_WIDTH, frame_width);
			cam_data[i].cam_web.set(CAP_PROP_FRAME_HEIGHT, frame_height);
			cam_data[i].cam_web.set(CAP_PROP_FOCUS, cam_data[i].focus);
		}
		else
		{
			temp_str.Format(L"USB相机%d连接异常，单击确认键等待程序退出后，\
检查相机电源及连接线是否松动，并重启程序。", i + 1);
			int WAPI = MessageBox(temp_str, L"设备连接异常", MB_COMPOSITE | MB_ICONERROR);
			if (WAPI == IDABORT)
			{
				SetTimer(-2, 600, NULL);
				MessageBox(L"程序正在退出，请稍后...", L"设备连接异常", 
					MB_OKCANCEL | MB_ICONWARNING);
			}
			else if (WAPI == IDRETRY)
			{
				OnClose();
				//get exe path
				TCHAR szAppName[MAX_PATH];
				::GetModuleFileName(theApp.m_hInstance, szAppName, MAX_PATH);
				CString strAppFullName;
				strAppFullName.Format(_T("%s"), szAppName);
				//restart	
				STARTUPINFO StartInfo;
				PROCESS_INFORMATION procStruct;
				memset(&StartInfo, 0, sizeof(STARTUPINFO));
				StartInfo.cb = sizeof(STARTUPINFO);
				::CreateProcess((LPCTSTR)strAppFullName, NULL, NULL, NULL, FALSE,
					NORMAL_PRIORITY_CLASS, NULL, NULL, &StartInfo, &procStruct);
			}
			cam_initializesign = FALSE;
			ini_parser.Clear();
			nReturn = -1;
			return nReturn;
		}
	}
	/*Basler Camera*/
	CTlFactory& TlFactory = CTlFactory::GetInstance();// Get the transport layer factory.
	if (TlFactory.EnumerateDevices(devices_list) == 0)
	{
		int WAPI = MessageBox(L"Basler相机连接异常，单击确认键等待程序退出后，检查相机电源是否松动，\
并重启程序。", L"设备连接异常", MB_COMPOSITE | MB_ICONERROR);
		if (WAPI == IDABORT)
		{
			SetTimer(-2, 600, NULL);
			MessageBox(L"程序正在退出，请稍后...", L"设备连接异常",
				MB_OKCANCEL | MB_ICONWARNING);
		}
		else if (WAPI == IDRETRY)
		{
			OnClose();
			//get exe path
			TCHAR szAppName[MAX_PATH];
			::GetModuleFileName(theApp.m_hInstance, szAppName, MAX_PATH);
			CString strAppFullName;
			strAppFullName.Format(_T("%s"), szAppName);
			//restart	
			STARTUPINFO StartInfo;
			PROCESS_INFORMATION procStruct;
			memset(&StartInfo, 0, sizeof(STARTUPINFO));
			StartInfo.cb = sizeof(STARTUPINFO);
			::CreateProcess((LPCTSTR)strAppFullName, NULL, NULL, NULL, FALSE,
				NORMAL_PRIORITY_CLASS, NULL, NULL, &StartInfo, &procStruct);
		}
		cam_initializesign = FALSE;
		ini_parser.Clear();
		nReturn = -1;
		return nReturn;
	}
	else
	{
		//create device
		cam_basler.Attach(TlFactory.CreateFirstDevice());
		cam_basler.RegisterConfiguration(new CAcquireContinuousConfiguration, 
			RegistrationMode_ReplaceAll, Ownership_TakeOwnership);
		cam_basler.RegisterImageEventHandler(this, RegistrationMode_Append, 
			Ownership_ExternalOwnership);
		cam_basler.Open();
		cam_basler.AcquisitionMode.SetValue(AcquisitionMode_Continuous);
		// Carry out luminance control by using the "continuous" gain auto function.
		AutoGainContinuous(cam_basler);
		// Carry out luminance control by using the "continuous" exposure auto function.
		AutoExposureContinuous(cam_basler);
		temp_str = ini_parser.GetValue("Basler Camera", L"trigger_source", size_);
		trigger_source = (TriggerSourceEnums)_ttoi(temp_str);
		cam_basler.TriggerSource.SetValue(trigger_source);
		cam_basler.TriggerMode.SetValue(TriggerMode_Off);
		converter.OutputPixelFormat = PixelType_Mono8;
		cam_basler.Width.SetValue(frame_width);
		cam_basler.Height.SetValue(frame_height);
		cam_basler.CenterX.SetValue(TRUE);
		cam_basler.CenterY.SetValue(TRUE);
		//
		cam_basler.StartGrabbing(GrabStrategy_OneByOne, 
			GrabLoop_ProvidedByInstantCamera);
		SetTimer(-2, 1200, NULL);
		MessageBox(L"相机初始化中，请稍后...", L"提示信息", 
			MB_ICONINFORMATION | MB_OK);
	}
	SetTimer(1, 100, NULL);
	ini_parser.Clear();
	cam_initializesign = TRUE;
	return nReturn;
}

//AutoGain
void CG_SUB_InspectionDlg::AutoGainContinuous(Camera_basler& camera_basler)
{
	// Check whether the Gain Auto feature is available.
	if (!IsWritable(camera_basler.GainAuto))
	{
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
	//if (IsAvailable(camera_basler.AutoFunctionROISelector))
	//{
	//	// Set the Auto Function ROI for luminance statistics.
	//	// We want to use ROI1 for gathering the statistics.
	//	if (IsWritable(camera_basler.AutoFunctionROIUseBrightness))
	//	{
	//		camera_basler.AutoFunctionROISelector.SetValue(AutoFunctionROISelector_ROI1);
	//		camera_basler.AutoFunctionROIUseBrightness.SetValue(true);   // ROI 1 is used for brightness control
	//		camera_basler.AutoFunctionROISelector.SetValue(AutoFunctionROISelector_ROI2);
	//		camera_basler.AutoFunctionROIUseBrightness.SetValue(false);   // ROI 2 is not used for brightness control
	//	}
	//	// Set the ROI (in this example the complete sensor is used)
	//	camera_basler.AutoFunctionROISelector.SetValue(AutoFunctionROISelector_ROI1);  // configure ROI 1
	//	camera_basler.AutoFunctionROIOffsetX.SetValue(0);
	//	camera_basler.AutoFunctionROIOffsetY.SetValue(0);
	//	camera_basler.AutoFunctionROIWidth.SetValue(camera_basler.Width.GetMax());
	//	camera_basler.AutoFunctionROIHeight.SetValue(camera_basler.Height.GetMax());
	//}

	// Set the target value for luminance control. The value is always expressed
	// as an 8 bit value regardless of the current pixel data output format,
	// i.e., 0 -> black, 255 -> white.

	camera_basler.AutoTargetValue.SetValue(80);
	//camera_basler.AutoTargetBrightness.SetValue(0.3);
	camera_basler.GainAuto.SetValue(GainAuto_Continuous);
}

//AutoExposure
void CG_SUB_InspectionDlg::AutoExposureContinuous(Camera_basler& camera_basler)
{
	// Check whether the Exposure Auto feature is available.
	if (!IsWritable(camera_basler.ExposureAuto))
	{
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
	//if (IsAvailable(camera_basler.AutoFunctionROISelector))
	//{
	//	// Set the Auto Function ROI for luminance statistics.
	//	// We want to use ROI1 for gathering the statistics.
	//	if (IsWritable(camera_basler.AutoFunctionROIUseBrightness))
	//	{
	//		camera_basler.AutoFunctionROISelector.SetValue(AutoFunctionROISelector_ROI1);
	//		camera_basler.AutoFunctionROIUseBrightness.SetValue(true);   // ROI 1 is used for brightness control
	//		camera_basler.AutoFunctionROISelector.SetValue(AutoFunctionROISelector_ROI2);
	//		camera_basler.AutoFunctionROIUseBrightness.SetValue(false);   // ROI 2 is not used for brightness control
	//	}
	//	// Set the ROI (in this example the complete sensor is used)
	//	camera_basler.AutoFunctionROISelector.SetValue(AutoFunctionROISelector_ROI1);  // configure ROI 1
	//	camera_basler.AutoFunctionROIOffsetX.SetValue(0);
	//	camera_basler.AutoFunctionROIOffsetY.SetValue(0);
	//	camera_basler.AutoFunctionROIWidth.SetValue(camera_basler.Width.GetMax());
	//	camera_basler.AutoFunctionROIHeight.SetValue(camera_basler.Height.GetMax());
	//}

	// Set the target value for luminance control. The value is always expressed
	// as an 8 bit value regardless of the current pixel data output format,
	// i.e., 0 -> black, 255 -> white.
	camera_basler.AutoTargetValue.SetValue(80);
	//camera_basler.AutoTargetBrightness.SetValue(0.3);
	camera_basler.ExposureAuto.SetValue(ExposureAuto_Continuous);
}

void CG_SUB_InspectionDlg::OnImageGrabbed(CInstantCamera& camera_basler, 
	const CGrabResultPtr& ptrGrabResult_basler)
{
	if (ptrGrabResult_basler->GrabSucceeded())
	{
		converter.Convert(targetImage, ptrGrabResult_basler);
		Mat cv_img = Mat(targetImage.GetHeight(), targetImage.GetWidth(), CV_8UC1);
		cv_img = cv::Mat(targetImage.GetHeight(), targetImage.GetWidth(), CV_8UC1, 
			(uint8_t*)targetImage.GetBuffer());
		basler_frame = cv_img.clone();
		if (inspect_sgn)
		{
			BOOL general_sign = TRUE;
			for (int m = 0; m < MAX_CAMERA; m++)//web camera
			{
				cam_data[m].cam_web >> cam_data[m].frame;
				cam_data[m].cam_web >> cam_data[m].frame;
				camera_index = m;
				for (int n = 0; n < inspect_data[m].number; n++)
				{
					double thres_ = inspect_data[m].threshold[n];
					inspect_data[m].inspect_Result = Inspect_function(n, inspect_data[m].image_file[n], 
						cam_data[m].frame,	inspect_data[m].ROI[n], thres_);
					disp_image(IDC_inspec, cam_data[m].frame, gsub_ins, CRect(0, 0, 100, 100), m);
					general_sign *= inspect_data[m].inspect_Result;
				}
			}
			for (int p = 0; p < inspect_data[MAX_CAMERA].number; p++)//basler camera
			{
				camera_index = MAX_CAMERA;
				double thres_ = inspect_data[MAX_CAMERA].threshold[p];
				inspect_data[MAX_CAMERA].inspect_Result = Inspect_function(p, 
					inspect_data[MAX_CAMERA].image_file[p], basler_frame, 
					inspect_data[MAX_CAMERA].ROI[p], thres_);
				disp_image(IDC_inspec, basler_frame, gsub_ins, 
					CRect(0, 0, 100, 100), MAX_CAMERA);
				general_sign *= inspect_data[MAX_CAMERA].inspect_Result;
			}
			if (general_sign)
			{
				real_produce++;
				temp_str.Format(L": %d", real_produce);
				plan_tree.SetItemText(subRoot1, treeNode_str[1] + temp_str);
				plan_tree.SetItemData(subRoot1, real_produce);
			}
			else
			{
				ng_produce++;
				temp_str.Format(L": %d", ng_produce);
				plan_tree.SetItemText(subRoot2, treeNode_str[2] + temp_str);
				plan_tree.SetItemData(subRoot2, ng_produce);
			}
			//change model
			if (real_produce == plan_produce)
			{
				load_sgn = TRUE;
				disp_image(IDC_inspec, paint_, gsub_ins, CRect(0, 0, 100, 100));
				plan_tree.SetItemData(selected_item, -1);
				plan_tree.SetItemText(subRoot3, treeNode_str[3] + L": 已完成");
				plan_tree.SetItemData(subRoot3, 1);
				selected_item = plan_tree.GetNextSiblingItem(selected_item);
				if (selected_item != NULL)
				{
					current_model = plan_tree.GetItemText(selected_item);
					temp_str.Format(L"机种变更: %s\r\n请注意确认。", current_model);
					if (MessageBox(temp_str, L"机种变更确认", 
						MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
					{
						get_produceinfo(selected_item);
						real_produce = 0;
						ng_produce = 0;
						database_operation(5, current_model);
					}
					else
					{
						//stop inspecting
						OnBnClickedfuncbutton();
					}
				}
				else
				{
					if (MessageBox(L"生产计划已完成。", L"提示信息", 
						MB_OK | MB_ICONINFORMATION) == IDOK)
					{
						//stop inspecting
						inspect_complete = TRUE;
						database_operation(5, L"NULL");
						OnBnClickedfuncbutton();
					}
				}
			}
			else//update infomation
			{
				database_operation(5, current_model);
				planlist_ini(4);
			}
		}
	}
}
#pragma endregion

#pragma region Inspection
//Template matching
BOOL CG_SUB_InspectionDlg::Inspect_function(int index_, Mat template_img, 
	Mat& inspect_img, Rect ROI, double& threshold)
{
	int res_cols;
	int res_rows;
	int count_process;
	double err_value = 0;
	double minVal;
	double maxVal;
	double scale_precise = 0.1;
	double max_scale = 0.2;

	Mat tpl_image;
	Mat temp_image;
	Mat res_image;
	Mat ori_image;
	Mat gray_image;
	Point temp_Loc;
	Point minLoc;
	Point maxLoc;
	BOOL check_sgn = FALSE;

	tpl_image = template_img.clone();
	ori_image = inspect_img.clone();
	
	count_process = (int)((2 * max_scale) / scale_precise) + 1;
	if (inspect_img.channels() > 1)
	{
		cvtColor(inspect_img.clone(), gray_image, CV_BGR2GRAY);
	}
	else
	{
		gray_image = inspect_img.clone();
		cvtColor(inspect_img.clone(), ori_image, CV_GRAY2BGR);
	}
	if (tpl_image.channels() > 1)
	{
		cvtColor(tpl_image.clone(), tpl_image, CV_BGR2GRAY);
	}
	gray_image = gray_image(ROI);
	for (int i = 0; i < 4; i++)
	{
		double scale_ = 0.8 + 0.1 * i;
		cv::resize(tpl_image.clone(), temp_image, 
			cv::Size(tpl_image.cols * scale_, tpl_image.rows * scale_));

		res_cols = gray_image.cols - temp_image.cols + 1;
		res_rows = gray_image.rows - temp_image.rows + 1;
		if (res_cols < 0 || res_rows < 0)
		{
			check_sgn = FALSE;
			break;
		}
		res_image = Mat(res_cols, res_rows, CV_32FC1);

		matchTemplate(gray_image, temp_image, res_image, CV_TM_CCOEFF_NORMED);
		minMaxLoc(res_image, &minVal, &maxVal, &minLoc, &temp_Loc);
		temp_Loc.x += ROI.x;
		temp_Loc.y += ROI.y;
		if (maxVal > threshold)
		{
			threshold = maxVal;
			maxLoc = temp_Loc;
			check_sgn = TRUE;
		}
		else
		{
			if (err_value < maxVal)
			{
				err_value = maxVal;
			}
		}
	}
	if (!check_sgn)//NG
	{
		rectangle(ori_image, ROI.tl(), ROI.br(), cvScalar(0, 0, 255, 0), 6, 8, 0);
		USES_CONVERSION;
		CString err_text;
		err_text.Format(L"err: %.2f", err_value);
		char* err_msg = T2A(err_text.GetBuffer(0));
		err_text.ReleaseBuffer();
		putText(ori_image, err_msg, ROI.br(), FONT_HERSHEY_COMPLEX, 2.5, Scalar(0, 0, 255), 2);
		if (!PathIsDirectory(error_imagefile + current_date))
		{
			::CreateDirectory(error_imagefile + current_date, NULL);
		}
		if (abs(err_value - threshold) < 0.15)
		{
			err_text = inspect_data[camera_index].contents_remarks[index_] + L"-异品检出";
		}
		else
		{
			err_text = inspect_data[camera_index].contents_remarks[index_] + L"-欠品检出";
		}
		CString err_date;
		CTime time(CTime::GetCurrentTime());
		err_date.Format(L"%02d-%02d-%02d-%s", time.GetHour(),
			time.GetMinute(),
			time.GetSecond(), current_model);
		//image
		temp_str.Format(L"%s%s\\%s-%s.bmp" , error_imagefile, current_date,
			err_date, inspect_data[camera_index].contents_names[index_]);
		err_msg = T2A(temp_str.GetBuffer(0));
		temp_str.ReleaseBuffer();
		cv::imwrite(err_msg, ori_image);
		//data
		record_errormessage(err_date, err_text, error_datafile);
	}
	else//OK
	{
		rectangle(ori_image, maxLoc, Point(maxLoc.x + tpl_image.cols, maxLoc.y + tpl_image.rows),
			cvScalar(0, 255, 0, 0), 6, 8, 0);
	}
	inspect_img = ori_image.clone();
	return check_sgn;
}

//Record error message
void CG_SUB_InspectionDlg::record_errormessage(CString value1, CString value2,
	CString file_path)
{
	CString num_;
	CString node_;
	file_path += current_date + L".ini";
	USES_CONVERSION;
	temp_filename = T2A(file_path.GetBuffer(0));
	file_path.ReleaseBuffer();
	if (_access(temp_filename, 0) == -1)
	{
		spl_wnd->wr_unicodefile(file_path);
		WritePrivateProfileString(L"Node0", L"name", current_date + L"Error", file_path);
		WritePrivateProfileString(L"Node0", L"index", L"0", file_path);
		WritePrivateProfileString(L"Node0", L"id", L"0", file_path);
		WritePrivateProfileString(L"Node0", L"layer", L"1", file_path);
		num_ = L"1";
	}
	else
	{
		GetPrivateProfileString(L"INFO", L"filesum", L"nul", num_.GetBuffer(128), 128, file_path);
		num_.ReleaseBuffer();
	}
	node_.Format(L"Node" + num_);
	WritePrivateProfileString(node_, L"name", value1, file_path);
	WritePrivateProfileString(node_, L"index", num_, file_path);
	WritePrivateProfileString(node_, L"id", L"0", file_path);
	WritePrivateProfileString(node_, L"layer", L"2", file_path);
	node_.Format(L"Node%d", _ttoi(num_) + 1);
	num_.Format(L"%d", _ttoi(num_) + 1);
	WritePrivateProfileString(node_, L"name", value2, file_path);
	WritePrivateProfileString(node_, L"index", num_, file_path);
	WritePrivateProfileString(node_, L"id", L"0", file_path);
	WritePrivateProfileString(node_, L"layer", L"3", file_path);
	num_.Format(L"%d", _ttoi(num_) + 1);
	WritePrivateProfileString(L"INFO", L"filesum", num_, file_path);
}
#pragma endregion