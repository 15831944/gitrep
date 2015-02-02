#pragma once
#include "afxcmn.h"
#include "afxwin.h"



class ClaserDlg;
// CDlgParaSet �Ի���

class CDlgParaSet : public CDialog
{
	DECLARE_DYNAMIC(CDlgParaSet)

public:
	CDlgParaSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgParaSet();

// �Ի�������
	enum { IDD = IDD_DLG_PARASET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_LIST_ParaBB;
	int  m_nItemSel;
	CString dat;
	CComboBox m_COMBO_PARA;
	//CString   m_sExcelFile;


public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAddpro();
	afx_msg void OnBnClickedBtnDel();
	void InitListCtrl();	
	afx_msg void OnBnClickedBtnXiugai();
	afx_msg void OnBnClickedBtnGuanbi();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCbnSelchangeComboPara();
	CComboBox m_Comb_SSKaiG;
	CComboBox m_Comb_GuangX;
};
