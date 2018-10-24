
// G_SUB_Inspection.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "vector"
#include "resource.h"		// main symbols


// CG_SUB_InspectionApp:
// See G_SUB_Inspection.cpp for the implementation of this class
//

class CG_SUB_InspectionApp : public CWinApp
{
public:
	CG_SUB_InspectionApp();

// Overrides
public:
	char* instruction_file;
	char* database_file;
	char* modelList_file;
	CString Currentdir_;
	CString currentTime;
	CString admin_pass[2];
	std::vector<CString> model_;

	HICON* icon_file;
	CImageList icontree_list;

	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CG_SUB_InspectionApp theApp;