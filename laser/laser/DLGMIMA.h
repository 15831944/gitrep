#pragma once


// CDLGMIMA �Ի���

class CDLGMIMA : public CDialog
{
	DECLARE_DYNAMIC(CDLGMIMA)

public:
	CDLGMIMA(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLGMIMA();

// �Ի�������
	enum { IDD = IDD_DIALOG_MIMA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString m_sFile;

	CString  PassGL;
	CString  PassCZ;

public:
	afx_msg void OnBnClickedBtnYes();
	afx_msg void OnBnClickedBtnCancell();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void SavePara(CString ProductFileName);   //�������
};
