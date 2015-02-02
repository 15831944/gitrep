// DlgParaSet.cpp : 实现文件
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



extern struct ProPara para;   // 产品参数存储
extern int m_CurIndex;


extern CString  m_sExcelFile;    //路径名
extern  CString m_strDate;
extern CString m_PointDate;

// CDlgParaSet 对话框

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


// CDlgParaSet 消息处理程序
BOOL CDlgParaSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
     
	InitListCtrl();	

	//初始化编辑框	
	//GetDlgItem(IDC_COMBO_PARA)->SetWindowText("A");
	//GetDlgItem(IDC_EDIT_PartNum)->SetWindowText("CHINA");     //产品件号 6
	//GetDlgItem(IDC_EDIT_CustomNo)->SetWindowText("JS004");    //客户编号 9
	//GetDlgItem(IDC_EDIT_PlantNo)->SetWindowText("1000004");   //工厂编号 3
	//GetDlgItem(IDC_EDIT_Certificate)->SetWindowText("CCC");   //CCC标志  1
	//GetDlgItem(IDC_EDIT_Brand)->SetWindowText("TYPE HA-B");   //品牌号   5
	//GetDlgItem(IDC_COMBO_NolePokeyoka)->SetWindowText("s");   //防错孔   2
	//GetDlgItem(IDC_EDIT_FixNo)->SetWindowText("15.01.01");          //模板编号 7
	//GetDlgItem(IDC_EDIT_AUTOLIVNO)->SetWindowText("630 9361 00");   //AUTOLIV编号 12
	//GetDlgItem(IDC_EDIT_COMPONENTNO)->SetWindowText("FK72-611B09-AB8PVJ");//组件编号  11
	//GetDlgItem(IDC_EDIT_CARTYPE)->SetWindowText("LANDROVER");       //车型号  10  
	//GetDlgItem(IDC_EDIT_LOGONO)->SetWindowText("MEETS GB14166");    //Logo号  8      
 //   GetDlgItem(IDC_EDIT_NHACODE)->SetWindowText("FK72-611B09-AB8PVJ 140825"); //二维码  4
	//GetDlgItem(IDC_EDIT_VISFILE)->SetWindowText("AUTOLIV_140825.wlj");  //job路径
	
	GetDlgItem(IDC_EDIT_CPZJ2)->SetWindowText("FK72-611B09-AB8PVJ");
	GetDlgItem(IDC_EDIT_DATA2)->SetWindowText(m_PointDate);
	GetDlgItem(IDC_EDIT_AUTOLIV2)->SetWindowText("630 9361 00");
	GetDlgItem(IDC_EDIT_GYSBM2)->SetWindowText("JS004");
	GetDlgItem(IDC_EDIT_MOJU2)->SetWindowText("0");
	m_Comb_SSKaiG.SetCurSel(0);
	m_Comb_GuangX.SetCurSel(0);
	GetDlgItem(IDC_EDIT_TEMP)->SetWindowText("AUTOLIV_140825.wlj");  //job路径


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgParaSet::OnBnClickedBtnAddpro()
{
	// TODO: 在此添加控件通知处理程序代码
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
	GetDlgItem(IDC_EDIT_TEMP)->GetWindowText(str8);  //job路径



	//查询是否存在该产品名称
	while (!flag)
	{
		sSql.Format("select * from LaserPara where 产品型号 = '%s'",strName);
		g_adoDB.ExecuteQuery(sSql,FInfo);

		if (g_adoDB.GetAdoItemCount(sSql) == 0)
		{
			int ret = MessageBox("确定要保存该产品参数吗？","",MB_YESNO);
			if (ret != 6)
			{
				return;
			}
			else
			{
				m_COMBO_PARA.AddString(strName);  //如果不存在，增加该产品
				//给主界面添加信息
				m_pParent->m_ProXH.AddString(strName);   //主界面上的产品

				//如果产品名称不存在，参数进行插入
				sSql.Format("INSERT INTO LaserPara VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s')",strName,str1,str2,str3,str4,str5,str6,str7,str8);
				g_adoDB.Execute(sSql);

				flag = 1;
			}
		}
		else if(g_adoDB.GetAdoItemCount(sSql) > 0)
		{
			MessageBox("该产品已经存在，如果要修改参数，请选择修改操作");
			return ;
		}
	}
}

void CDlgParaSet::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
	CString    sSql;
	CString    sExcelFile,sPath;
	CString    str, strName;
	int        nIndex;

	GetDlgItem(IDC_COMBO_PARA)->GetWindowText(strName);
	m_pParent = (ClaserDlg*)AfxGetMainWnd();

	str.Format("确定要删除%s产品的参数吗？",strName);
	int ret = MessageBox(str,NULL,MB_OKCANCEL);

	if (ret!= IDOK)
		return;

	sSql.Format("delete from LaserPara where 产品型号 = '%s'",strName);

	g_adoDB.Execute(sSql);

	MessageBox("产品参数删除成功！");
	for (int i = 0; i < m_COMBO_PARA.GetCount();i ++)
	{
		nIndex = m_COMBO_PARA.GetCurSel();
		m_COMBO_PARA.GetLBText(nIndex,str);

		if (str == strName)
		{
			m_COMBO_PARA.DeleteString(nIndex);
			m_pParent->m_ProXH.DeleteString(nIndex);   //主界面上的产品
		}	
	}
}

void CDlgParaSet::InitListCtrl()
{
	//把数据导入到List控件表中
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

		// 如果等于当前索引，把值赋给编辑框f
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
			

			//赋值给para 需要修改
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
	// TODO: 在此添加控件通知处理程序代码
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
	GetDlgItem(IDC_EDIT_TEMP)->GetWindowText(str8);  //job路径


	while (!flag)
	{
		sSql.Format("select * from LaserPara where 产品型号 = '%s'",strName);

		if (g_adoDB.GetAdoItemCount(sSql) == 1)
		{
			int ret = MessageBox("确定要修改该产品参数吗？","",MB_YESNO);
			if (ret != 6)
			{
				return;
			}
			else
			{
				sSql.Format(_T("delete from LaserPara where 产品型号 = '%s'"),strName);
				g_adoDB.Execute(sSql);
				sSql.Format("insert into LaserPara values('%s','%s','%s','%s','%s','%s','%s','%s','%s')",strName,str1,str2,str3,str4,str5,str6,str7,str8);
				g_adoDB.Execute(sSql); 

				MessageBox("参数修改成功！");
				
				flag = 1;
			}
		}
		else
		{
			MessageBox("该产品不存在，不能进行参数修改");
			flag = 1;
		}
	}
}

void CDlgParaSet::OnBnClickedBtnGuanbi()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

HBRUSH CDlgParaSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
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


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CDlgParaSet::OnCbnSelchangeComboPara()
{
	//TODO: 在此添加控件通知处理程序代码
	CString    sSql,str;
	CDStrs     FInfo;
	CStrs      Item;
	CString    sItem1,sItem2,sItem3,sItem4,sItem5,sItem6,sItem7,sItem8,sItem9;
	CString    sExcelFile,sPath;

	//路径名根据选择修改
	sExcelFile = m_sExcelFile;

	int nIndex = m_COMBO_PARA.GetCurSel();
	m_CurIndex = nIndex;    
	m_COMBO_PARA.GetLBText(nIndex,str);

	int flag = 0;

	while(!flag)
	{
		sSql.Format("Select * from LaserPara where 产品型号 = '%s'",str);
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
			MessageBox("产品参数有多行");
			return;
		}
	}
}
