#pragma once

// mscomm32.ocxCtrl.h : Cmscomm32ocxCtrl ActiveX 控件类的声明。


// Cmscomm32ocxCtrl : 有关实现的信息，请参阅 mscomm32.ocxCtrl.cpp。

class Cmscomm32ocxCtrl : public COleControl
{
	DECLARE_DYNCREATE(Cmscomm32ocxCtrl)

// 构造函数
public:
	Cmscomm32ocxCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~Cmscomm32ocxCtrl();

	DECLARE_OLECREATE_EX(Cmscomm32ocxCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(Cmscomm32ocxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(Cmscomm32ocxCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(Cmscomm32ocxCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
	};
};

