#pragma once
#include "afxcmn.h"


// CDlgIOList �Ի���

class CDlgIOList : public CDialog
{
	DECLARE_DYNAMIC(CDlgIOList)

public:
	CDlgIOList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgIOList();

// �Ի�������
	enum { IDD = IDD_DLG_IO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//CListCtrl m_IOListCtrl;
	virtual BOOL OnInitDialog();
	void DispIO(void);
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
