#pragma once

// mscomm32.ocxPropPage.h : Cmscomm32ocxPropPage ����ҳ���������


// Cmscomm32ocxPropPage : �й�ʵ�ֵ���Ϣ������� mscomm32.ocxPropPage.cpp��

class Cmscomm32ocxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(Cmscomm32ocxPropPage)
	DECLARE_OLECREATE_EX(Cmscomm32ocxPropPage)

// ���캯��
public:
	Cmscomm32ocxPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_MSCOMM32OCX };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

