
// G_SUB_InspectionDlg.h : header file
//

#pragma once
//System
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
#include "algorithm"
#include "INIParser.h"
#include "map"
#include "DbSqlite.h"

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

//Basler
#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#    include <pylon/PylonGUI.h>
#endif

#include "pylon/gige/_BaslerGigECameraParams.h"
#include "pylon/gige/BaslerGigECamera.h"
#include "pylon/gige/BaslerGigEInstantCamera.h"
#include "pylon/usb/BaslerUsbCamera.h"
#include "pylon/usb/BaslerUsbInstantCamera.h"
#include "pylon/ImageEventHandler.h"
#include "ImageEventPrinter.h"
#include "pylon/TransportLayer.h"
#include "pylon/ConfigurationEventHandler.h"
#include "pylon/PylonIncludes.h"
#include "pylon/FeaturePersistence.h"
#include "pylon/ImagePersistence.h"
#include "pylon/PylonBase.h"
#include "pylon/ImageFormatConverter.h"

using namespace std;
using namespace cv;
using namespace Pylon;
using namespace GenApi;
using namespace Basler_GigECameraParams;
//using namespace Basler_UsbCameraParams;

#define MAX_CAMERA 2

// CG_SUB_InspectionDlg dialog
class CG_SUB_InspectionDlg : public CDialogEx, public CImageEventHandler
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
	virtual void OnImageGrabbed(CInstantCamera& camera_basler, 
		const CGrabResultPtr& ptrGrabResult_basler);

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
	typedef CBaslerGigEInstantCamera Camera_basler;
//	typedef CBaslerUsbInstantCamera Camera_basler;

	struct camera_data
	{
		int camera_index = -1;
		int focus;
		CString model_name;
		VideoCapture cam_web;
		Mat frame;
	}; 
	camera_data* cam_data;

	struct inspectcontents_data
	{
		int number = 0;
		vector<CString> contents_remarks;
		vector<CString> contents_names;
		vector<Mat> image_file;
		vector<Rect> ROI;
		vector<double> threshold;
		BOOL inspect_Result = FALSE;
		CString Error = L"";
	};
	inspectcontents_data* inspect_data;

	//basler camera
	Camera_basler	cam_basler;
	DeviceInfoList_t devices_list;
	TriggerSourceEnums trigger_source;
	CPylonImage	targetImage;
	CImageFormatConverter converter;
	CGrabResultPtr ptrGrabResult_basler;

	int plan_produce = 0;
	int real_produce = 0;
	int ng_produce = 0;
	int temp_int = 0;
	int temp_index = 0;
	int current_index = 1;
	int newmodel_no = 1;
	int plan_num = 1;
	int frame_width;
	int frame_height;
	int camera_index = -1;
	double scale_index;
	char* temp_filename;

	BOOL initialize_sgn = FALSE;
	BOOL cam_initializesign = FALSE;
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
	BOOL clip_sgn = FALSE;
	BOOL new_filesgn = FALSE;
	BOOL inspect_complete = FALSE;
	CString error_message;
	CString model_add;
	CString temp_str;
	CString mdy_data;
	CString current_date;
	CString current_model;
	CString clip_filepath;
	CString error_imagefile;
	CString error_datafile;
	CString dynamic_info;
	CString* treeNode_str;
	CString* title_str;
	CImageList* m_pImageList;
	vector<CString> strVecAccount;
	vector<CString> modify_history;
	vector<CString> m_FileList;
	
	Mat paint_ = Mat(1080, 1920, CV_8UC3, Scalar::all(240));
	Mat basler_frame;
	Mat target_image;

	CRectTracker m_RectTracker;
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
	CRect disp_rect;
	Rect cut_rect;
	CWnd *pWnd;
	CButton func_btn;
	CButton user;
	CEdit pswd_edt;
	CEdit info_edit;
	CEdit m_Edit;
	CEdit m_Info;
	CStatic inspec_pic;
	CDbSQLite modify_db;
	CSqlStatement* db_status;
	CDateTimeCtrl datepick;
	CComboBox model_sel;

	int planlist_ini(int mode_);
	int index_numbering(int mode_);
	int copy_item(HTREEITEM item, int index_);
	int database_operation(int mode_, CString content);
	int camera_initialization();
	void recordTreeNode(CTreeCtrl& m_tree, HTREEITEM hTreeItem,	UINT& fileSum, 
		int& layer, CString appPathFile);
	void queryTreeNode(CTreeCtrl& m_tree, HTREEITEM& hTreeItem, CString appPathFile);
	void OnKillfocusEdit();
	void functionarea_init(int mode_);
	void instruction_output();
	void create_edit(CWnd* ctrl, CRect  EditRect, CString contents_reserved, int mode_ = 0);
	void disp_image(UINT disp_ID, Mat dsp_img, CWnd* pt, CRect& img_rect, int cam_index = 0);
	void new_inspectcontent(HTREEITEM hRoot, int& newmodel_no);
	void AutoGainContinuous(Camera_basler& camera_basler);
	void AutoExposureContinuous(Camera_basler& camera_basler);
	void record_errormessage(CString value1, CString value2, CString file_path);
	virtual void OnOK();
	virtual void OnCancel();

	BOOL get_produceinfo(HTREEITEM model);
	BOOL Inspect_function(int index_, Mat template_img, Mat& inspect_img, 
		Rect ROI, double& threshold, CString& Error);

	afx_msg void OnClose();
	afx_msg void OnBnClickedfuncbutton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPlanmenu1chkpln();
	afx_msg void OnPlanmenu1chkdata();
	afx_msg void OnPlanmenu1addmodel();
	afx_msg void OnPlanmenu1addcontent();
	afx_msg void OnPlanmenu1addpln();
	afx_msg void OnPlanmenu2modpln();
	afx_msg void OnEnChangepswd();
	afx_msg void OnCbnSelchangemodelsel();
	afx_msg void OnTvnSelchangedplan(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnBegindragplan(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickplan(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangedatepick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPlanmenu1export();
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