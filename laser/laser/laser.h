// laser.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#include "DlgUSER.h"

// ClaserApp:
// 有关此类的实现，请参阅 laser.cpp
//

class ClaserApp : public CWinApp
{
public:
	ClaserApp();


// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

public:
	CDlgUSER   m_UseDlg;
};

extern ClaserApp theApp;

CString		GetExcelDriver();
BOOL		MakeSurePathExists( CString &Path,	bool FilenameIncluded=true);
void		ExportListToExcel(CListCtrl* pList, CString strTitle);
