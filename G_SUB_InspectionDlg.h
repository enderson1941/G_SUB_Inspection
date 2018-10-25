
// G_SUB_InspectionDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"
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
//OpenCV
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
#include "DbSqlite.h"
//Basler
#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#    include <pylon/PylonGUI.h>
#endif
#include "pylon/gige/_BaslerGigECameraParams.h"
#include "pylon/gige/BaslerGigECamera.h"
#include "pylon/gige/BaslerGigEInstantCamera.h"
#include "pylon/ImageEventHandler.h"
#include "ImageEventPrinter.h"
#include "pylon/ConfigurationEventHandler.h"
#include "pylon/PylonIncludes.h"
#include "pylon/FeaturePersistence.h"
#include "pylon/ImagePersistence.h"
#include "pylon/ImageFormatConverter.h"
#include "pylon/GrabResultPtr.h"

using namespace std;
using namespace cv;
using namespace Pylon;
using namespace GenApi;
using namespace Basler_GigECameraParams;

#define MAX_CAMERA 1

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

// Instant Camera Image Event.
// This is where we are going the receive the grabbed images.
// This method is called from the Instant Camera grab loop thread.
	virtual void OnImageGrabbed(CInstantCamera& camera_act, const CGrabResultPtr& ptrGrabResult_act);

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
	typedef struct camera_data
	{
		int camera_index;
		int real_inspect_number = 0;
		int real_NG_number = 0;
		int frame_width;
		int frame_height;
		int focus;
		CString model_name;
		BOOL inspect_sgn = FALSE;
		VideoCapture camera;
		Mat frame;
		//
		CBaslerGigEInstantCamera camera_basler;
		CBaslerGigEImageEventHandler ImageEventHandler;
		CBaslerGigEGrabResultPtr  m_LastGrabbedImage;

		CGrabResultPtr ptrGrabResult_basler;
		DeviceInfoList_t lstdevices_basler;
		CLock m_lock;
	}; 
	camera_data* camera_dat;
	CBaslerGigEInstantCamera camera_basler;
	int temp_int = 0;
	int temp_index = 0;
	int newmodel_no = 1;
	int plan_num = 0;
	double scale_index;
	char* plan_filename = "plan.ini";

	CImageList* m_pImageList;
	BOOL initialize_sgn = FALSE;
	BOOL load_sgn = FALSE;
	BOOL inquery_pswd = FALSE;
	BOOL pswd_state = FALSE;
	BOOL inquery_pln = FALSE;
	BOOL inquery_dat = FALSE;
	BOOL add_pln = FALSE;
	BOOL add_md = FALSE;
	BOOL add_content = FALSE;
	BOOL mdy_pln = FALSE;
	BOOL mdy_md = FALSE;
	BOOL inspect_sgn = FALSE;
	BOOL m_bIsDrag = FALSE;
	CString error_message;
	CString model_add;
	CString temp_str;
	CString mdy_data;
	CString current_date;
	CString db_command;
	CString* treeNode_str;
	CString* title_str;
	vector<CString> strVecAccount;
	
	Mat paint_ = Mat(1024, 1280, CV_8UC3, Scalar::all(240));

	INIParser ini_parser;
	HTREEITEM* new_item;
	HTREEITEM m_hDragItem;
	HTREEITEM selected_item;
	HTREEITEM hRoot;
	HTREEITEM subRoot;
	HTREEITEM subRoot1;
	HTREEITEM subRoot2;
	HTREEITEM subRoot3;
	HTREEITEM subRoot4;
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
	CComboBox model_sel;

	int planlist_ini(int mode_);
	int index_numbering(int mode_);
	int copy_item(HTREEITEM item, int index_);
	int database_operation(int mode_, CString content);
	int camera_initialization();
	void recordTreeNode(CTreeCtrl& m_tree, HTREEITEM hTreeItem,
		UINT& fileSum, int& layer, CString appPathFile);
	void queryTreeNode(CTreeCtrl& m_tree, HTREEITEM& hTreeItem, CString appPathFile);
	void OnKillfocusEdit();
	void functionarea_init(int mode_);
	void instruction_output();
	void disp_image(UINT disp_ID, Mat dsp_img, CWnd* pt, CRect& img_rect, int cam_index = 0);
	void new_inspectcontent(HTREEITEM hRoot, int& newmodel_no);
	void AutoGainContinuous(CBaslerGigEInstantCamera& camera_basler);
	void AutoExposureContinuous(CBaslerGigEInstantCamera& camera_basler);
	virtual void OnOK();
	afx_msg void OnBnClickedfuncbutton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangepswd();
	afx_msg void OnTvnSelchangedplan(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnBegindragplan(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickplan(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPlanmenu1chkpln();
	afx_msg void OnPlanmenu1chkdata();
	afx_msg void OnDtnDatetimechangedatepick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPlanmenu1addpln();
	afx_msg void OnCbnSelchangemodelsel();
	afx_msg void OnPlanmenu2modpln();
	afx_msg void OnPlanmenu1addmodel();
	afx_msg void OnPlanmenu1addcontent();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
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