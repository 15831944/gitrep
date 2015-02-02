#pragma once

#include "DLGMIMA.h"


// CDlgUSER 对话框

class CDlgUSER : public CDialog
{
	DECLARE_DYNAMIC(CDlgUSER)

public:
	CDlgUSER(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUSER();

// 对话框数据
	enum { IDD = IDD_DLG_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	int      m_nTimes;


	//1226hua新加代码
	CDLGMIMA m_DlgMiMa;
	CString m_sFile;

	CString  PassGL;
	CString  PassCZ;
    //////////////////

public:
	afx_msg void OnBnClickedYes();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboId();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnXiugai();
	void LoadPara(CString ProductFileName);   //保存参数
};
