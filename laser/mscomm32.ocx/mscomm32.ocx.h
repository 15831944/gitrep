#pragma once

// mscomm32.ocx.h : mscomm32.ocx.DLL ����ͷ�ļ�

#if !defined( __AFXCTL_H__ )
#error "�ڰ������ļ�֮ǰ������afxctl.h��"
#endif

#include "resource.h"       // ������


// Cmscomm32ocxApp : �й�ʵ�ֵ���Ϣ������� mscomm32.ocx.cpp��

class Cmscomm32ocxApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

