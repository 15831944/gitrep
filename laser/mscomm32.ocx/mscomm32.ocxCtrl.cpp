// mscomm32.ocxCtrl.cpp : Cmscomm32ocxCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "mscomm32.ocx.h"
#include "mscomm32.ocxCtrl.h"
#include "mscomm32.ocxPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(Cmscomm32ocxCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(Cmscomm32ocxCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(Cmscomm32ocxCtrl, COleControl)
	DISP_FUNCTION_ID(Cmscomm32ocxCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(Cmscomm32ocxCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(Cmscomm32ocxCtrl, 1)
	PROPPAGEID(Cmscomm32ocxPropPage::guid)
END_PROPPAGEIDS(Cmscomm32ocxCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(Cmscomm32ocxCtrl, "MSCOMM32OCX.mscomm32ocxCtrl.1",
	0x7699c356, 0xf53e, 0x49ac, 0x97, 0xcf, 0xa4, 0xea, 0x36, 0x88, 0x87, 0x73)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(Cmscomm32ocxCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID BASED_CODE IID_Dmscomm32ocx =
		{ 0x3A9DD7C3, 0xE510, 0x441D, { 0x95, 0x98, 0x1A, 0xD7, 0xE0, 0x7F, 0x80, 0xCD } };
const IID BASED_CODE IID_Dmscomm32ocxEvents =
		{ 0x822182DD, 0xAC76, 0x4E15, { 0x97, 0xD4, 0x71, 0x5E, 0x76, 0x33, 0xD9, 0x21 } };



// 控件类型信息

static const DWORD BASED_CODE _dwmscomm32ocxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(Cmscomm32ocxCtrl, IDS_MSCOMM32OCX, _dwmscomm32ocxOleMisc)



// Cmscomm32ocxCtrl::Cmscomm32ocxCtrlFactory::UpdateRegistry -
// 添加或移除 Cmscomm32ocxCtrl 的系统注册表项

BOOL Cmscomm32ocxCtrl::Cmscomm32ocxCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MSCOMM32OCX,
			IDB_MSCOMM32OCX,
			afxRegApartmentThreading,
			_dwmscomm32ocxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// Cmscomm32ocxCtrl::Cmscomm32ocxCtrl - 构造函数

Cmscomm32ocxCtrl::Cmscomm32ocxCtrl()
{
	InitializeIIDs(&IID_Dmscomm32ocx, &IID_Dmscomm32ocxEvents);
	// TODO: 在此初始化控件的实例数据。
}



// Cmscomm32ocxCtrl::~Cmscomm32ocxCtrl - 析构函数

Cmscomm32ocxCtrl::~Cmscomm32ocxCtrl()
{
	// TODO: 在此清理控件的实例数据。
}



// Cmscomm32ocxCtrl::OnDraw - 绘图函数

void Cmscomm32ocxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// Cmscomm32ocxCtrl::DoPropExchange - 持久性支持

void Cmscomm32ocxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// Cmscomm32ocxCtrl::OnResetState - 将控件重置为默认状态

void Cmscomm32ocxCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// Cmscomm32ocxCtrl::AboutBox - 向用户显示“关于”框

void Cmscomm32ocxCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_MSCOMM32OCX);
	dlgAbout.DoModal();
}



// Cmscomm32ocxCtrl 消息处理程序
