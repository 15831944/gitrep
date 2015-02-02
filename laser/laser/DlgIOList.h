#pragma once
#include "afxcmn.h"


// CDlgIOList 对话框

class CDlgIOList : public CDialog
{
	DECLARE_DYNAMIC(CDlgIOList)

public:
	CDlgIOList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgIOList();

// 对话框数据
	enum { IDD = IDD_DLG_IO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//CListCtrl m_IOListCtrl;
	virtual BOOL OnInitDialog();
	void DispIO(void);
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
