// DlgParaSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "laser.h"
#include "DlgParaSet.h"
#include "laserDlg.h"

#include <io.h>
#include <odbcinst.h>
#include <afxdb.h>

#include "ADODB.h"


extern CAdoDB g_adoDB;

extern 	ClaserDlg * m_pParent;



extern struct ProPara para;   // ��Ʒ�����洢
extern int m_CurIndex;


extern CString  m_sExcelFile;    //·����
extern  CString m_strDate;
extern CString m_PointDate;

// CDlgParaSet �Ի���

IMPLEMENT_DYNAMIC(CDlgParaSet, CDialog)

CDlgParaSet::CDlgParaSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParaSet::IDD, pParent)
{
	m_nItemSel = -1;
}

CDlgParaSet::~CDlgParaSet()
{
}

void CDlgParaSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PARA, m_COMBO_PARA);
	DDX_Control(pDX, IDC_COMBO_SSKaiG, m_Comb_SSKaiG);
	DDX_Control(pDX, IDC_COMBO_SSGuangQ, m_Comb_GuangX);
}


BEGIN_MESSAGE_MAP(CDlgParaSet, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADDPro, &CDlgParaSet::OnBnClickedBtnAddpro)
	ON_BN_CLICKED(IDC_BTN_DEL, &CDlgParaSet::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_XIUGAI, &CDlgParaSet::OnBnClickedBtnXiugai)
	ON_BN_CLICKED(IDC_BTN_GUANBI, &CDlgParaSet::OnBnClickedBtnGuanbi)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO_PARA, &CDlgParaSet::OnCbnSelchangeComboPara)
END_MESSAGE_MAP()


// CDlgParaSet ��Ϣ�������
BOOL CDlgParaSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
     
	InitListCtrl();	

	//��ʼ���༭��	
	//GetDlgItem(IDC_COMBO_PARA)->SetWindowText("A");
	//GetDlgItem(IDC_EDIT_PartNum)->SetWindowText("CHINA");     //��Ʒ���� 6
	//GetDlgItem(IDC_EDIT_CustomNo)->SetWindowText("JS004");    //�ͻ���� 9
	//GetDlgItem(IDC_EDIT_PlantNo)->SetWindowText("1000004");   //������� 3
	//GetDlgItem(IDC_EDIT_Certificate)->SetWindowText("CCC");   //CCC��־  1
	//GetDlgItem(IDC_EDIT_Brand)->SetWindowText("TYPE HA-B");   //Ʒ�ƺ�   5
	//GetDlgItem(IDC_COMBO_NolePokeyoka)->SetWindowText("s");   //�����   2
	//GetDlgItem(IDC_EDIT_FixNo)->SetWindowText("15.01.01");          //ģ���� 7
	//GetDlgItem(IDC_EDIT_AUTOLIVNO)->SetWindowText("630 9361 00");   //AUTOLIV��� 12
	//GetDlgItem(IDC_EDIT_COMPONENTNO)->SetWindowText("FK72-611B09-AB8PVJ");//������  11
	//GetDlgItem(IDC_EDIT_CARTYPE)->SetWindowText("LANDROVER");       //���ͺ�  10  
	//GetDlgItem(IDC_EDIT_LOGONO)->SetWindowText("MEETS GB14166");    //Logo��  8      
 //   GetDlgItem(IDC_EDIT_NHACODE)->SetWindowText("FK72-611B09-AB8PVJ 140825"); //��ά��  4
	//GetDlgItem(IDC_EDIT_VISFILE)->SetWindowText("AUTOLIV_140825.wlj");  //job·��
	
	GetDlgItem(IDC_EDIT_CPZJ2)->SetWindowText("FK72-611B09-AB8PVJ");
	GetDlgItem(IDC_EDIT_DATA2)->SetWindowText(m_PointDate);
	GetDlgItem(IDC_EDIT_AUTOLIV2)->SetWindowText("630 9361 00");
	GetDlgItem(IDC_EDIT_GYSBM2)->SetWindowText("JS004");
	GetDlgItem(IDC_EDIT_MOJU2)->SetWindowText("0");
	m_Comb_SSKaiG.SetCurSel(0);
	m_Comb_GuangX.SetCurSel(0);
	GetDlgItem(IDC_EDIT_TEMP)->SetWindowText("AUTOLIV_140825.wlj");  //job·��


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgParaSet::OnBnClickedBtnAddpro()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str1,str2,str3,str4,str5,str6,str7,str8,str9;
	CString sSql;
	BOOL    m_bChanPE = FALSE;
	CString strName;
	int     flag = 0;
	CDStrs  FInfo;
	m_pParent = (ClaserDlg*)AfxGetMainWnd();

	GetDlgItem(IDC_COMBO_PARA)->GetWindowText(strName);

	GetDlgItem(IDC_EDIT_CPZJ2)->GetWindowText(str1);
	GetDlgItem(IDC_EDIT_DATA2)->GetWindowText(str2);
	GetDlgItem(IDC_EDIT_AUTOLIV2)->GetWindowText(str3);
	GetDlgItem(IDC_EDIT_GYSBM2)->GetWindowText(str4);
	GetDlgItem(IDC_EDIT_MOJU2)->GetWindowText(str5);
	GetDlgItem(IDC_COMBO_SSKaiG)->GetWindowText(str6);
	GetDlgItem(IDC_COMBO_SSGuangQ)->GetWindowText(str7);
	GetDlgItem(IDC_EDIT_TEMP)->GetWindowText(str8);  //job·��



	//��ѯ�Ƿ���ڸò�Ʒ����
	while (!flag)
	{
		sSql.Format("select * from LaserPara where ��Ʒ�ͺ� = '%s'",strName);
		g_adoDB.ExecuteQuery(sSql,FInfo);

		if (g_adoDB.GetAdoItemCount(sSql) == 0)
		{
			int ret = MessageBox("ȷ��Ҫ����ò�Ʒ������","",MB_YESNO);
			if (ret != 6)
			{
				return;
			}
			else
			{
				m_COMBO_PARA.AddString(strName);  //��������ڣ����Ӹò�Ʒ
				//�������������Ϣ
				m_pParent->m_ProXH.AddString(strName);   //�������ϵĲ�Ʒ

				//�����Ʒ���Ʋ����ڣ��������в���
				sSql.Format("INSERT INTO LaserPara VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s')",strName,str1,str2,str3,str4,str5,str6,str7,str8);
				g_adoDB.Execute(sSql);

				flag = 1;
			}
		}
		else if(g_adoDB.GetAdoItemCount(sSql) > 0)
		{
			MessageBox("�ò�Ʒ�Ѿ����ڣ����Ҫ�޸Ĳ�������ѡ���޸Ĳ���");
			return ;
		}
	}
}

void CDlgParaSet::OnBnClickedBtnDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString    sSql;
	CString    sExcelFile,sPath;
	CString    str, strName;
	int        nIndex;

	GetDlgItem(IDC_COMBO_PARA)->GetWindowText(strName);
	m_pParent = (ClaserDlg*)AfxGetMainWnd();

	str.Format("ȷ��Ҫɾ��%s��Ʒ�Ĳ�����",strName);
	int ret = MessageBox(str,NULL,MB_OKCANCEL);

	if (ret!= IDOK)
		return;

	sSql.Format("delete from LaserPara where ��Ʒ�ͺ� = '%s'",strName);

	g_adoDB.Execute(sSql);

	MessageBox("��Ʒ����ɾ���ɹ���");
	for (int i = 0; i < m_COMBO_PARA.GetCount();i ++)
	{
		nIndex = m_COMBO_PARA.GetCurSel();
		m_COMBO_PARA.GetLBText(nIndex,str);

		if (str == strName)
		{
			m_COMBO_PARA.DeleteString(nIndex);
			m_pParent->m_ProXH.DeleteString(nIndex);   //�������ϵĲ�Ʒ
		}	
	}
}

void CDlgParaSet::InitListCtrl()
{
	//�����ݵ��뵽List�ؼ�����
	CString    sSql,str;
	int        CurIndex = m_CurIndex;

	sSql.Format(_T("Select * from LaserPara"));
	CDStrs FInfo;
	g_adoDB.ExecuteQuery(sSql,FInfo);
	CStringArray items;

	m_COMBO_PARA.ResetContent();

	for (size_t i = 0;i < FInfo.size();i++)
	{
		items.RemoveAll();
		for (size_t j = 0;j < ShuJuNum; j++)
		{
			items.Add(FInfo[i][j]);
		}
		m_COMBO_PARA.AddString(items.GetAt(0));

		// ������ڵ�ǰ��������ֵ�����༭��f
		if (i == CurIndex)
		{
			m_COMBO_PARA.SetCurSel(CurIndex);

			GetDlgItem(IDC_EDIT_CPZJ2)->SetWindowText(items.GetAt(1));
			GetDlgItem(IDC_EDIT_DATA2)->SetWindowText(items.GetAt(2));
			GetDlgItem(IDC_EDIT_AUTOLIV2)->SetWindowText(items.GetAt(3));
			GetDlgItem(IDC_EDIT_GYSBM2)->SetWindowText(items.GetAt(4));
			GetDlgItem(IDC_EDIT_MOJU2)->SetWindowText(items.GetAt(5));
			GetDlgItem(IDC_COMBO_SSKaiG)->SetWindowText(items.GetAt(6));
			GetDlgItem(IDC_COMBO_SSGuangQ)->SetWindowText(items.GetAt(7));
			GetDlgItem(IDC_EDIT_TEMP)->SetWindowText(items.GetAt(8));
			

			//��ֵ��para ��Ҫ�޸�
			para.m_CPXH = items.GetAt(0);
            para.m_ChanPJH = items.GetAt(1);
			para.m_Data = items.GetAt(2);
			para.m_AUTOLIV = items.GetAt(3);
			para.m_CustomNo = items.GetAt(4);
			para.m_MoJuBM = items.GetAt(5);
			para.m_SSKaiG = items.GetAt(6);
			para.m_SSGuangX = items.GetAt(7);
			para.m_VISFile = items.GetAt(8);
		}
	}
}

void CDlgParaSet::OnBnClickedBtnXiugai()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString    sSql;
	CString    sExcelFile,sPath;
	CString    str, strName;
	int        flag = 0;

	CString str1,str2,str3,str4,str5,str6,str7,str8,str9;

	GetDlgItem(IDC_COMBO_PARA)->GetWindowText(strName);

	GetDlgItem(IDC_EDIT_CPZJ2)->GetWindowText(str1);
	GetDlgItem(IDC_EDIT_DATA2)->GetWindowText(str2);
	GetDlgItem(IDC_EDIT_AUTOLIV2)->GetWindowText(str3);
	GetDlgItem(IDC_EDIT_GYSBM2)->GetWindowText(str4);
	GetDlgItem(IDC_EDIT_MOJU2)->GetWindowText(str5);
	GetDlgItem(IDC_COMBO_SSKaiG)->GetWindowText(str6);
	GetDlgItem(IDC_COMBO_SSGuangQ)->GetWindowText(str7);
	GetDlgItem(IDC_EDIT_TEMP)->GetWindowText(str8);  //job·��


	while (!flag)
	{
		sSql.Format("select * from LaserPara where ��Ʒ�ͺ� = '%s'",strName);

		if (g_adoDB.GetAdoItemCount(sSql) == 1)
		{
			int ret = MessageBox("ȷ��Ҫ�޸ĸò�Ʒ������","",MB_YESNO);
			if (ret != 6)
			{
				return;
			}
			else
			{
				sSql.Format(_T("delete from LaserPara where ��Ʒ�ͺ� = '%s'"),strName);
				g_adoDB.Execute(sSql);
				sSql.Format("insert into LaserPara values('%s','%s','%s','%s','%s','%s','%s','%s','%s')",strName,str1,str2,str3,str4,str5,str6,str7,str8);
				g_adoDB.Execute(sSql); 

				MessageBox("�����޸ĳɹ���");
				
				flag = 1;
			}
		}
		else
		{
			MessageBox("�ò�Ʒ�����ڣ����ܽ��в����޸�");
			flag = 1;
		}
	}
}

void CDlgParaSet::OnBnClickedBtnGuanbi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

HBRUSH CDlgParaSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	else if (nCtlColor == CTLCOLOR_EDIT)
	{
		//pDC->SetTextColor(RGB(0,0,0));
		//pDC->SetBkColor(RGB(160,189,239));

		//aBrush = CreateSolidBrush(RGB(160,189,239));
		//hbr = aBrush;

	}
	else if (nCtlColor == CTLCOLOR_DLG)
	{
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(160,189,239));

		aBrush = CreateSolidBrush(RGB(160,189,239));
		hbr = aBrush;
	}
	else if (nCtlColor == CTLCOLOR_BTN)
	{
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(160,189,239));

		aBrush = CreateSolidBrush(RGB(160,189,239));
		hbr = aBrush;
	}


	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CDlgParaSet::OnCbnSelchangeComboPara()
{
	//TODO: �ڴ���ӿؼ�֪ͨ����������
	CString    sSql,str;
	CDStrs     FInfo;
	CStrs      Item;
	CString    sItem1,sItem2,sItem3,sItem4,sItem5,sItem6,sItem7,sItem8,sItem9;
	CString    sExcelFile,sPath;

	//·��������ѡ���޸�
	sExcelFile = m_sExcelFile;

	int nIndex = m_COMBO_PARA.GetCurSel();
	m_CurIndex = nIndex;    
	m_COMBO_PARA.GetLBText(nIndex,str);

	int flag = 0;

	while(!flag)
	{
		sSql.Format("Select * from LaserPara where ��Ʒ�ͺ� = '%s'",str);
		g_adoDB.ExecuteQuery(sSql,FInfo);

		if (FInfo.size() == 1)
		{		
			CStringArray items;

			for (size_t i = 0;i < FInfo.size();i++)
			{
				items.RemoveAll();
				for (size_t j = 0;j < ShuJuNum; j++)
				{
					items.Add(FInfo[i][j]);
				}
			}
			GetDlgItem(IDC_EDIT_CPZJ2)->SetWindowText(items.GetAt(1));
			GetDlgItem(IDC_EDIT_DATA2)->SetWindowText(items.GetAt(2));
			GetDlgItem(IDC_EDIT_AUTOLIV2)->SetWindowText(items.GetAt(3));
			GetDlgItem(IDC_EDIT_GYSBM2)->SetWindowText(items.GetAt(4));
			GetDlgItem(IDC_EDIT_MOJU2)->SetWindowText(items.GetAt(5));
			GetDlgItem(IDC_COMBO_SSKaiG)->SetWindowText(items.GetAt(6));
			GetDlgItem(IDC_COMBO_SSGuangQ)->SetWindowText(items.GetAt(7));
			GetDlgItem(IDC_EDIT_TEMP)->SetWindowText(items.GetAt(8));

			para.m_CPXH = items.GetAt(0);
			para.m_ChanPJH = items.GetAt(1);
			para.m_Data = items.GetAt(2);
			para.m_AUTOLIV = items.GetAt(3);
			para.m_CustomNo = items.GetAt(4);
			para.m_MoJuBM = items.GetAt(5);
			para.m_SSKaiG = items.GetAt(6);
			para.m_SSGuangX = items.GetAt(7);
			para.m_VISFile = items.GetAt(8);

			flag = 1;
		}
		else  
		{  
			MessageBox("��Ʒ�����ж���");
			return;
		}
	}
}
