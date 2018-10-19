
// G_SUB_InspectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "G_SUB_Inspection.h"
#include "G_SUB_InspectionDlg.h"
#include "afxdialogex.h"
#include "iostream"
#include "CvvImage.h"
#include "vector"
#include "Strsafe.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "cstdlib"
#include "utility"
#include "fstream"
#include "io.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDC_crtd_EDIT 9000

ClxTreeCtrl plan_tree;

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

CG_SUB_InspectionDlg* gsub_ins;

IMPLEMENT_DYNAMIC(CG_SUB_InspectionDlg, CDialogEx);

CG_SUB_InspectionDlg::CG_SUB_InspectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_G_SUB_INSPECTION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
	pWnd = GetDlgItem(IDC_func_button);
	pWnd->GetWindowRect(ori_rect);
	pWnd->SetWindowPos(NULL, 0, 0, ori_rect.Width() + 170, ori_rect.Height(),
		SWP_NOZORDER | SWP_NOMOVE);
	pWnd = GetDlgItem(IDC_datepick);
	pWnd->GetWindowRect(datepick_);
	ScreenToClient(datepick_);
	pWnd = GetDlgItem(IDC_model_sel);
	pWnd->GetWindowRect(mdl_sel);
	ScreenToClient(mdl_sel);

	info_edit.SetWindowText(L"G-SUB03外观检查软件");
	
	COLORREF oldColor = RGB(240, 240, 240);
	plan_tree.SetBkColor(oldColor);
	model_sel.AddString(L"AJ6");
	model_sel.AddString(L"JG3");
	model_sel.AddString(L"TAA");
	datepick.SetFormat(L"yyyy-MM-dd");
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

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

		/*if (pswd_state)
		{
			CString pswd_text;
			pswd_edt.GetWindowText(pswd_text);
			if (pswd_text != L"fxsz")
			{
				info_edit.SetWindowText(L"wrong pswd");
				pswd_edt.SetWindowText(NULL);
				OnBnClickeduser();
			}
		}*/

void CG_SUB_InspectionDlg::OnBnClickedfuncbutton()
{
	// TODO: Add your control notification handler code here
	Mat* img = new Mat[3];
	img[0] = imread("lena.jpg");
	CRect img_rect = CRect(0, 0, 100, 100);
	load_sgn = TRUE;
	disp_image(IDC_inspec, img[0], gsub_ins, img_rect, temp_int);
	temp_int++;
}

void CG_SUB_InspectionDlg::disp_image(UINT disp_ID, Mat dsp_img, CWnd* pt, CRect& img_rect, int cam_index)
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

void ClxTreeCtrl::OnDropFiles(HDROP hDropInfo)
{


}

void CG_SUB_InspectionDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case -1:
	{
		KillTimer(nIDEvent);
		planlist_ini(0);
		Mat paint_ = Mat(1024, 1280, CV_8UC3, Scalar::all(240));
		load_sgn = TRUE;
		disp_image(IDC_inspec, paint_, gsub_ins, CRect(0, 0, 100, 100));
		func_btn.SetFocus();
		break;
	}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

int CG_SUB_InspectionDlg::planlist_ini(int mode_)
{
	int nReturn = 0;
	switch (mode_)
	{
	case 0:
	{
		plan_tree.DeleteAllItems();
		CTime time(CTime::GetCurrentTime());
		CString currentTime;
		currentTime.Format(L"%04d-%02d-%02d", time.GetYear(),
			time.GetMonth(),
			time.GetDay());

		hRoot = plan_tree.InsertItem(currentTime, 0, 0, TVI_ROOT, TVI_LAST);
		break;
	}
	case 1:
	{
		plan_num++;
		model_sel.GetWindowText(model_add);
		subRoot = plan_tree.InsertItem(model_add, 0, 0, hRoot, TVI_LAST);
		plan_tree.SetItemData(subRoot, plan_num);
		subRoot1 = plan_tree.InsertItem(L"计划生产量", 0, 0, subRoot, TVI_LAST);
		plan_tree.SetItemData(subRoot, 0);
		subRoot2 = plan_tree.InsertItem(L"实际生产量", 0, 0, subRoot, TVI_LAST);
		plan_tree.SetItemData(subRoot, 0);
		subRoot3 = plan_tree.InsertItem(L"NG发生率", 0, 0, subRoot, TVI_LAST);
		plan_tree.SetItemData(subRoot, 0);
		plan_tree.Expand(hRoot, TVE_EXPAND);
		plan_tree.Expand(subRoot, TVE_EXPAND);
		break;
	}
	default:
		break;
	}


	return nReturn;
}

/*

int oldState = user.GetCheck();
if (m_userType == 0)
{
m_userType = -1;
user.SetCheck(0);
pWnd = GetDlgItem(IDC_func_button);
pWnd->SetWindowPos(NULL, 0, 0, ori_rect.Width() + 135, ori_rect.Height(),
SWP_NOZORDER | SWP_NOMOVE);
pswd_edt.ShowWindow(FALSE);
//
pWnd = GetDlgItem(IDC_datepick);
pWnd->SetWindowPos(NULL, datepick_.TopLeft().x, datepick_.TopLeft().y,
datepick_.Width(), datepick_.Height(), SWP_NOZORDER);
datepick.ShowWindow(FALSE);
//
pswd_state = FALSE;
}
else if (m_userType == -1)
{
m_userType = 0;
user.SetCheck(1);
pWnd = GetDlgItem(IDC_func_button);
pWnd->SetWindowPos(NULL, 0, 0, ori_rect.Width(), ori_rect.Height(),
SWP_NOZORDER | SWP_NOMOVE);
pswd_edt.ShowWindow(TRUE);
pswd_edt.SetFocus();
}

*/



void CG_SUB_InspectionDlg::OnEnChangepswd()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO:  Add your control notification handler code here
	CString pswd_text;
	pswd_edt.GetWindowText(pswd_text);
	if (pswd_text == L"f")
	{
		pswd_state = TRUE;
		pswd_edt.SetWindowText(NULL);
		pswd_edt.ShowWindow(FALSE);
		if (add_pln)
		{
			model_sel.ShowWindow(TRUE);
			pWnd = GetDlgItem(IDC_model_sel);
			pWnd->SetWindowPos(NULL, mdl_sel.TopLeft().x, mdl_sel.TopLeft().y - 40,
				mdl_sel.Width(), mdl_sel.Height() + 100, SWP_NOZORDER);
		}
		else if (inquery_pln || inquery_dat)
		{
			datepick.ShowWindow(TRUE);
			pWnd = GetDlgItem(IDC_datepick);
			pWnd->SetWindowPos(NULL, datepick_.TopLeft().x, datepick_.TopLeft().y - 80,
				datepick_.Width(), datepick_.Height() + 80, SWP_NOZORDER);
		}
	}
}

void CG_SUB_InspectionDlg::OnTvnSelchangedplan(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CG_SUB_InspectionDlg::OnTvnBegindragplan(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CG_SUB_InspectionDlg::OnNMRClickplan(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
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
		if (item_tiltle != L"计划生产量")
		{
			return;
		}
		else
		{
			selected_item = hItem;
			p_Menu = (CMenu*)m_Menu.GetSubMenu(1);//0
			if (p_Menu != NULL)
				p_Menu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, pt.x, pt.y, this);
			p_Menu = NULL;
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

void CG_SUB_InspectionDlg::OnPlanmenu1chkpln()
{
	// TODO: Add your command handler code here
	inquery_pln = TRUE;
	if (!pswd_state)
	{
		pWnd = GetDlgItem(IDC_func_button);
		pWnd->SetWindowPos(NULL, 0, 0, ori_rect.Width(), ori_rect.Height(),
			SWP_NOZORDER | SWP_NOMOVE);
		pswd_edt.ShowWindow(TRUE);
		pswd_edt.SetFocus();
	}
}

void CG_SUB_InspectionDlg::OnPlanmenu1chkdata()
{
	// TODO: Add your command handler code here
	inquery_dat = TRUE;
	if (!pswd_state)
	{
		pWnd = GetDlgItem(IDC_func_button);
		pWnd->SetWindowPos(NULL, 0, 0, ori_rect.Width(), ori_rect.Height(),
			SWP_NOZORDER | SWP_NOMOVE);
		pswd_edt.ShowWindow(TRUE);
		pswd_edt.SetFocus();
	}
}

void CG_SUB_InspectionDlg::OnPlanmenu1addpln()
{
	// TODO: Add your command handler code here
	add_pln = TRUE;
	if (!pswd_state)
	{
		pWnd = GetDlgItem(IDC_func_button);
		pWnd->SetWindowPos(NULL, 0, 0, ori_rect.Width(), ori_rect.Height(),
			SWP_NOZORDER | SWP_NOMOVE);
		pswd_edt.ShowWindow(TRUE);
		pswd_edt.SetFocus();
	}
}

void CG_SUB_InspectionDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	if (mdy_pln && m_Edit)
	{
		func_btn.SetFocus();
	}
}


void CG_SUB_InspectionDlg::OnDtnDatetimechangedatepick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	CTime m_date;  
	datepick.GetTime(m_date); 
	CString temp_;
	datepick.GetWindowText(temp_);
	info_edit.SetWindowText(temp_);
}





void CG_SUB_InspectionDlg::OnCbnSelchangemodelsel()
{
	// TODO: Add your control notification handler code here
	planlist_ini(1);
}


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

void CG_SUB_InspectionDlg::OnKillfocusEdit()
{
	mdy_pln = FALSE;
	m_Edit.GetWindowText(mdy_data);
	temp_str = plan_tree.GetItemText(selected_item);
	temp_str = temp_str.Mid(0, 5);
	plan_tree.SetItemText(selected_item, temp_str + L": " + mdy_data);
	plan_tree.SetItemData(selected_item, _ttoi(mdy_data));
	m_Edit.DestroyWindow();
}