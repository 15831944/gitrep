// laserDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"

#include "resource.h"

#include "DlgIOList.h"
#include "DlgParaSet.h"
#include "DlgUSER.h"




struct ProPara 
{ 
	CString  m_CPXH;          //��Ʒ�ͺ�
	CString  m_ChanPJH;     // ��Ʒ����
	CString  m_Data;            //����
	CString  m_AUTOLIV;    // Autoliv
	CString  m_CustomNo;    // ��Ӧ�̱��

	CString  m_MoJuBM;      //ģ�߱���
	CString  m_SSKaiG;        //����ӽ�����
	CString  m_SSGuangX;   //�������
	CString  m_VISFile;     // ·��	
};



// ClaserDlg �Ի���
class ClaserDlg : public CDialog
{
// ����
public:
	ClaserDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LASER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CMscomm1 MyCOMM;
	int data_length;
	

public:
	CDlgIOList   m_IOListDlg;
	CDlgParaSet  m_ParaSetDlg;
	CDlgUSER     m_USERDlg;

	CComboBox m_ProXH;

	//int  m_num;
	BYTE send[20];
	BYTE I0[2],I1[2],I2[2],Q100[2],Q101[2],Q102[2],H260[2],I260[2];
	BYTE M_state;
	BYTE recv[50];
	BYTE barcode[100];
	int chlen,barlen;
	CString edit1_str,edit2_str;
	BYTE alarm[2];
	int io_sign;
	int laser_sign;
	int laser_time;
	int laser_ctr;
	int laser_conf;
	CString laser_code;




// ʵ��
protected:
	HICON m_hIcon;

	HICON   m_hIcon_close;
	HICON   m_hIcon_open;



	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	void CaoZuoDisp(CString str);
	void ExcelToAccess();
	void AccessToExcel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CMscomm1 MyCOMM;
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	//afx_msg void OnBnClickedOk();
	//afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnDaochu();
	afx_msg void OnBnClickedBtnPara();
	afx_msg void OnBnClickedBtnInit();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnQuit();
	afx_msg void OnBnClickedBtnUser();
	afx_msg void OnBnClickedBtnIo();
	afx_msg void OnBnClickedBtnManual();
	afx_msg void OnBnClickedBtnYes();
	//CListBox m_ListInfo;
	//void ClaserDlg::InitList();
	CStatic m_Icon_Open;
	CStatic m_Icon_NG;
	//afx_msg void OnBnClickedBtnKaiguan();
	//afx_msg void OnBnClickedBtnDabiao();

	//void send_strr(CString str);
	afx_msg void OnBnClickedBtnDayin();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnVism();
	void lasermark();
	CComboBox m_BanCiComb;
	CMscomm1 PLC_COMM;
	CMscomm1 CODE_COMM;
	void OnCommMscomm2();
	void OnCommMscomm3();
	afx_msg void OnBnClickedBtnYajin();
	afx_msg void OnBnClickedBtnTaiqi();
	afx_msg void OnBnClickedBtnHoula();
	afx_msg void OnBnClickedBtnQianjin();
	afx_msg void OnBnClickedBtnShangsheng();
	afx_msg void OnBnClickedBtnXiajiang();
	afx_msg void OnBnClickedBtnSstc();
	afx_msg void OnBnClickedBtnSsht();
	afx_msg void OnBnClickedBtnJltc();
	afx_msg void OnBnClickedBtnJlht();
	afx_msg void OnBnClickedBtnViskz();
	afx_msg void OnBnClickedBtnRead();
	CComboBox m_comb_SSKaiG;
	CComboBox m_Comb_SSGuangX;
	void   DispIO1(void);
};
