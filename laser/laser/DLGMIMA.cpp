// DLGMIMA.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "laser.h"
#include "DLGMIMA.h"


extern CString  m_nPasswordGL;
extern CString  m_nPasswordCZ;
extern CString  m_nUserID;


// CDLGMIMA �Ի���

IMPLEMENT_DYNAMIC(CDLGMIMA, CDialog)

CDLGMIMA::CDLGMIMA(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGMIMA::IDD, pParent)
{

}

CDLGMIMA::~CDLGMIMA()
{
}

void CDLGMIMA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDLGMIMA, CDialog)
	ON_BN_CLICKED(IDC_BTN_YES, &CDLGMIMA::OnBnClickedBtnYes)
	ON_BN_CLICKED(IDC_BTN_CANCELL, &CDLGMIMA::OnBnClickedBtnCancell)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDLGMIMA ��Ϣ�������

BOOL CDLGMIMA::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	int nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	m_sFile = sPath+"\\";

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDLGMIMA::OnBnClickedBtnYes()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strOld,strNew,strTwoNew;
	CString IDStr;
	BOOL  B_ID;

	GetDlgItem(IDC_EDIT_OldMM)->GetWindowText(strOld);
	GetDlgItem(IDC_EDIT_NewMM)->GetWindowText(strNew);
	GetDlgItem(IDC_EDIT_TwoNMM)->GetWindowText(strTwoNew);

	int sizeNew1 = strNew.GetLength();
	int sizeNew2 = strTwoNew.GetLength();

	if ((sizeNew1 != 6) | (sizeNew2 != 6))
	{
		MessageBox("��������λ����");
		return;
	}

	if (m_nUserID == "����Ա")
	{
		IDStr = m_nPasswordGL;
		B_ID = TRUE;
	}
	else
	{
		IDStr = m_nPasswordCZ;
		B_ID = FALSE;
	}

	if (strcmp(IDStr,strOld)==0)
	{
		if (strcmp(strNew,strTwoNew)==0)
		{
			IDStr = strNew;
		}
		else
		{
			MessageBox("�������������벻һ�£�����������������");
			return;
		}
	}
	else
	{
		MessageBox("Ҫ�޸ĵ����벻��ȷ�����������������");
		return;
	}

	if (B_ID)
	{
		m_nPasswordGL = IDStr;
		MessageBox("����Ա�����޸ĳɹ�");
	}
	else
	{
		m_nPasswordCZ = IDStr;
		MessageBox("����Ա�����޸ĳɹ�");
	}
	SavePara(m_sFile);

	//OnClose();
	OnOK();	
}

void CDLGMIMA::OnBnClickedBtnCancell()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnClose();
	OnCancel();
}

void CDLGMIMA::SavePara(CString ProductFileName)   //�������
{
	CFile paraFile;
	paraFile.Open(ProductFileName+"Password"+".dat",CFile::modeCreate | CFile::modeWrite);

	char *pGL = (LPSTR)(LPCTSTR)m_nPasswordGL;
	char *pCZ = (LPSTR)(LPCTSTR)m_nPasswordCZ;

	paraFile.Write(pGL,7);
	paraFile.Write(pCZ,7);


	paraFile.Close();
}


void CDLGMIMA::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	

	CDialog::OnClose();
}

HBRUSH CDLGMIMA::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	HBRUSH aBrush;

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(160,189,239));
		aBrush = CreateSolidBrush(RGB(160,189,239));
		hbr = aBrush;
	}
	else if (nCtlColor == CTLCOLOR_DLG)
	{
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(160,189,239));

		aBrush = CreateSolidBrush(RGB(160,189,239));
		hbr = aBrush;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
