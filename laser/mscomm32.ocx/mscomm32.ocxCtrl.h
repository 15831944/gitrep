#pragma once

// mscomm32.ocxCtrl.h : Cmscomm32ocxCtrl ActiveX �ؼ����������


// Cmscomm32ocxCtrl : �й�ʵ�ֵ���Ϣ������� mscomm32.ocxCtrl.cpp��

class Cmscomm32ocxCtrl : public COleControl
{
	DECLARE_DYNCREATE(Cmscomm32ocxCtrl)

// ���캯��
public:
	Cmscomm32ocxCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~Cmscomm32ocxCtrl();

	DECLARE_OLECREATE_EX(Cmscomm32ocxCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(Cmscomm32ocxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(Cmscomm32ocxCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(Cmscomm32ocxCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
	};
};

