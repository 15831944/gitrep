// laser.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "DlgUSER.h"

// ClaserApp:
// �йش����ʵ�֣������ laser.cpp
//

class ClaserApp : public CWinApp
{
public:
	ClaserApp();


// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

public:
	CDlgUSER   m_UseDlg;
};

extern ClaserApp theApp;

CString		GetExcelDriver();
BOOL		MakeSurePathExists( CString &Path,	bool FilenameIncluded=true);
void		ExportListToExcel(CListCtrl* pList, CString strTitle);
