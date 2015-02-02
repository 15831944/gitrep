// DlgUSER.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "laser.h"
#include "DlgUSER.h"



extern BOOL  b_XiuGai;
extern BOOL  b_EXIT;
extern int master;

//1226�¼Ӵ���
CString  m_nUserID;
CString  m_nPasswordCZ;
CString  m_nPasswordGL;





// CDlgUSER �Ի���

IMPLEMENT_DYNAMIC(CDlgUSER, CDialog)

CDlgUSER::CDlgUSER(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUSER::IDD, pParent)
{
	m_nTimes = 0;
	m_nPasswordGL = "aaaaaa";
	m_nPasswordCZ = "bbbbbb";
}

CDlgUSER::~CDlgUSER()
{
}

void CDlgUSER::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//DDX_Text(pDX, IDC_EDIT_KEYWORD, m_nPassword);
}


BEGIN_MESSAGE_MAP(CDlgUSER, CDialog)
	ON_BN_CLICKED(IDC_YES, &CDlgUSER::OnBnClickedYes)
	ON_BN_CLICKED(IDC_CANCEL, &CDlgUSER::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_ID, &CDlgUSER::OnCbnSelchangeComboId)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_XIUGAI, &CDlgUSER::OnBnClickedBtnXiugai)
END_MESSAGE_MAP()


// CDlgUSER ��Ϣ�������

void CDlgUSER::OnBnClickedYes()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	GetDlgItem(IDC_COMBO_ID)->GetWindowText(m_nUserID);
	CString str;
	GetDlgItem(IDC_EDIT_KEYWORD)->GetWindowText(str);
	for (int i = 0; i < 3; i ++)
	{
		if (m_nUserID == "����Ա")
		{
			if (m_nPasswordGL == str)
			{
				//MessageBox("��½�ɹ�");
				m_nTimes = 0;
				b_XiuGai = true;

				master = 1;
				OnOK();
				return;
			} 
			else
			{
				if (m_nTimes > 3)
				{
					MessageBox("��½�������࣬�������Ա��ϵ");
					return;
				}
				MessageBox(_T("��¼ʧ��!\r\n�����û����������Ƿ�������ȷ��"));
				m_nTimes ++;
				return;
			}
		}
		else if (m_nUserID == "����Ա")
		{
			if (m_nPasswordCZ == str)
			{
				//MessageBox("��½�ɹ�");
				m_nTimes = 0;

				b_XiuGai = false;

				master = 0;

				OnOK();
				return;
			} 
			else
			{
				if (m_nTimes > 3)
				{
					MessageBox("��½�������࣬�������Ա��ϵ");
					//GetDlgItem(IDC_EDIT_KEYWORD)->EnableWindow(false);
					return;
				}
				MessageBox(_T("��¼ʧ��!\r\n�����û����������Ƿ�������ȷ��"));
				m_nTimes ++;
				return;
			}
		}

	}
}

void CDlgUSER::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	OnCancel();
	b_EXIT = FALSE;
}

BOOL CDlgUSER::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	((CComboBox*)GetDlgItem(IDC_COMBO_ID))->SetCurSel(0);

	CString sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	int nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	m_sFile = sPath+"\\";

	LoadPara(m_sFile);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgUSER::LoadPara(CString ProductFileName)   //�������
{
	CFile paraFile;
	if(!paraFile.Open(ProductFileName+"Password"+".dat",CFile::modeRead))
	{
		MessageBox("�����ļ���ʧ�ܣ�������ʹ�ó�ʼ���룡");
		return;
	}
	char strGL[30]= {0};
	char strCZ[30]= {0};

	paraFile.Read(strGL,7);
	paraFile.Read(strCZ,7);


	m_nPasswordGL.Format("%s",strGL);
	m_nPasswordCZ.Format("%s",strCZ);

	paraFile.Close();
}

void CDlgUSER::OnCbnSelchangeComboId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//GetDlgItem(IDC_COMBO_ID)->GetWindowText(m_nUserID);
	//if (m_nUserID == "����Ա")
	//{
	//	GetDlgItem(IDC_EDIT_KEYWORD)->EnableWindow(true);
	//}
}

HBRUSH CDlgUSER::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CDlgUSER::OnBnClickedBtnXiugai()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_DlgMiMa.DoModal();
}
