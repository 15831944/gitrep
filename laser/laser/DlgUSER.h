#pragma once

#include "DLGMIMA.h"


// CDlgUSER �Ի���

class CDlgUSER : public CDialog
{
	DECLARE_DYNAMIC(CDlgUSER)

public:
	CDlgUSER(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgUSER();

// �Ի�������
	enum { IDD = IDD_DLG_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	int      m_nTimes;


	//1226hua�¼Ӵ���
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
	void LoadPara(CString ProductFileName);   //�������
};
