// mscomm32.ocx.cpp : Cmscomm32ocxApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "mscomm32.ocx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


Cmscomm32ocxApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x215AB02D, 0x187D, 0x450C, { 0x9B, 0xF8, 0x42, 0xDB, 0x62, 0xF7, 0xF, 0x66 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// Cmscomm32ocxApp::InitInstance - DLL 初始化

BOOL Cmscomm32ocxApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// Cmscomm32ocxApp::ExitInstance - DLL 终止

int Cmscomm32ocxApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
