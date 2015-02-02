#pragma once

// mscomm32.ocxPropPage.h : Cmscomm32ocxPropPage 属性页类的声明。


// Cmscomm32ocxPropPage : 有关实现的信息，请参阅 mscomm32.ocxPropPage.cpp。

class Cmscomm32ocxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(Cmscomm32ocxPropPage)
	DECLARE_OLECREATE_EX(Cmscomm32ocxPropPage)

// 构造函数
public:
	Cmscomm32ocxPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_MSCOMM32OCX };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

