
// G_SUB_InspectionDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"

#include "opencv2/opencv_modules.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/photo/photo.hpp"
#include "algorithm"
#include "INIParser.h"
#include "map"
//
#include "afxpropertygridctrl.h"

using namespace std;
using namespace cv;

// CG_SUB_InspectionDlg dialog
class CG_SUB_InspectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CG_SUB_InspectionDlg);

// Construction
public:
	CG_SUB_InspectionDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CG_SUB_InspectionDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_G_SUB_INSPECTION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	int temp_int = 0;
	int plan_num = 0;
	double scale_index;
	BOOL load_sgn = FALSE;
	BOOL pswd_state = FALSE;
	BOOL inquery_pln = FALSE;
	BOOL inquery_dat = FALSE;
	BOOL add_pln = FALSE;
	BOOL mdy_pln = FALSE;
	CString model_add;
	CString temp_str;
	CString mdy_data;
	HTREEITEM selected_item;
	HTREEITEM hRoot;
	HTREEITEM subRoot;
	HTREEITEM subRoot1;
	HTREEITEM subRoot2;
	HTREEITEM subRoot3;
	CRect ori_rect;
	CRect datepick_;
	CRect mdl_sel;
	CWnd *pWnd;
	CButton func_btn;
	CButton user;
	CEdit pswd_edt;
	CEdit info_edit;
	CEdit m_Edit;
	CStatic inspec_pic;
	CDateTimeCtrl datepick;
	int planlist_ini(int mode_);
	void OnKillfocusEdit();
	void disp_image(UINT disp_ID, Mat dsp_img, CWnd* pt, CRect& img_rect, int cam_index = 0);
	afx_msg void OnBnClickedfuncbutton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangepswd();
	afx_msg void OnTvnSelchangedplan(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnBegindragplan(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickplan(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPlanmenu1chkpln();
	afx_msg void OnPlanmenu1chkdata();
	virtual void OnOK();
	afx_msg void OnDtnDatetimechangedatepick(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox model_sel;
	afx_msg void OnPlanmenu1addpln();
	afx_msg void OnCbnSelchangemodelsel();
	afx_msg void OnPlanmenu2modpln();
};

// ClxTreeCtrl
class ClxTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(ClxTreeCtrl)
public:
	ClxTreeCtrl();
	virtual ~ClxTreeCtrl();

	afx_msg void OnDropFiles(HDROP hDropInfo);
protected:
	DECLARE_MESSAGE_MAP()
};