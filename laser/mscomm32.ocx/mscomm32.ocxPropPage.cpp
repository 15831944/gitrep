// mscomm32.ocxPropPage.cpp : Cmscomm32ocxPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "mscomm32.ocx.h"
#include "mscomm32.ocxPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(Cmscomm32ocxPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(Cmscomm32ocxPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(Cmscomm32ocxPropPage, "MSCOMM32OCX.mscomm32ocxPropPage.1",
	0x5355e5dc, 0xeac2, 0x4a2b, 0x9f, 0x4c, 0x27, 0x64, 0xeb, 0x6e, 0x23, 0x58)



// Cmscomm32ocxPropPage::Cmscomm32ocxPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� Cmscomm32ocxPropPage ��ϵͳע�����

BOOL Cmscomm32ocxPropPage::Cmscomm32ocxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MSCOMM32OCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// Cmscomm32ocxPropPage::Cmscomm32ocxPropPage - ���캯��

Cmscomm32ocxPropPage::Cmscomm32ocxPropPage() :
	COlePropertyPage(IDD, IDS_MSCOMM32OCX_PPG_CAPTION)
{
}



// Cmscomm32ocxPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void Cmscomm32ocxPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// Cmscomm32ocxPropPage ��Ϣ�������
