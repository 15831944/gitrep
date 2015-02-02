// mscomm32.ocxCtrl.cpp : Cmscomm32ocxCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "mscomm32.ocx.h"
#include "mscomm32.ocxCtrl.h"
#include "mscomm32.ocxPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(Cmscomm32ocxCtrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(Cmscomm32ocxCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(Cmscomm32ocxCtrl, COleControl)
	DISP_FUNCTION_ID(Cmscomm32ocxCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(Cmscomm32ocxCtrl, COleControl)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(Cmscomm32ocxCtrl, 1)
	PROPPAGEID(Cmscomm32ocxPropPage::guid)
END_PROPPAGEIDS(Cmscomm32ocxCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(Cmscomm32ocxCtrl, "MSCOMM32OCX.mscomm32ocxCtrl.1",
	0x7699c356, 0xf53e, 0x49ac, 0x97, 0xcf, 0xa4, 0xea, 0x36, 0x88, 0x87, 0x73)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(Cmscomm32ocxCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID BASED_CODE IID_Dmscomm32ocx =
		{ 0x3A9DD7C3, 0xE510, 0x441D, { 0x95, 0x98, 0x1A, 0xD7, 0xE0, 0x7F, 0x80, 0xCD } };
const IID BASED_CODE IID_Dmscomm32ocxEvents =
		{ 0x822182DD, 0xAC76, 0x4E15, { 0x97, 0xD4, 0x71, 0x5E, 0x76, 0x33, 0xD9, 0x21 } };



// �ؼ�������Ϣ

static const DWORD BASED_CODE _dwmscomm32ocxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(Cmscomm32ocxCtrl, IDS_MSCOMM32OCX, _dwmscomm32ocxOleMisc)



// Cmscomm32ocxCtrl::Cmscomm32ocxCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� Cmscomm32ocxCtrl ��ϵͳע�����

BOOL Cmscomm32ocxCtrl::Cmscomm32ocxCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

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



// Cmscomm32ocxCtrl::Cmscomm32ocxCtrl - ���캯��

Cmscomm32ocxCtrl::Cmscomm32ocxCtrl()
{
	InitializeIIDs(&IID_Dmscomm32ocx, &IID_Dmscomm32ocxEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}



// Cmscomm32ocxCtrl::~Cmscomm32ocxCtrl - ��������

Cmscomm32ocxCtrl::~Cmscomm32ocxCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}



// Cmscomm32ocxCtrl::OnDraw - ��ͼ����

void Cmscomm32ocxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// Cmscomm32ocxCtrl::DoPropExchange - �־���֧��

void Cmscomm32ocxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// Cmscomm32ocxCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void Cmscomm32ocxCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// Cmscomm32ocxCtrl::AboutBox - ���û���ʾ�����ڡ���

void Cmscomm32ocxCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_MSCOMM32OCX);
	dlgAbout.DoModal();
}



// Cmscomm32ocxCtrl ��Ϣ�������
