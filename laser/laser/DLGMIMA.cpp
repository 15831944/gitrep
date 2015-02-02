// DLGMIMA.cpp : 实现文件
//

#include "stdafx.h"
#include "laser.h"
#include "DLGMIMA.h"


extern CString  m_nPasswordGL;
extern CString  m_nPasswordCZ;
extern CString  m_nUserID;


// CDLGMIMA 对话框

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


// CDLGMIMA 消息处理程序

BOOL CDLGMIMA::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	int nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	m_sFile = sPath+"\\";

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDLGMIMA::OnBnClickedBtnYes()
{
	// TODO: 在此添加控件通知处理程序代码
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
		MessageBox("请输入六位密码");
		return;
	}

	if (m_nUserID == "管理员")
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
			MessageBox("新密码两次输入不一致，请重新输入新密码");
			return;
		}
	}
	else
	{
		MessageBox("要修改的密码不正确，请重新输入旧密码");
		return;
	}

	if (B_ID)
	{
		m_nPasswordGL = IDStr;
		MessageBox("管理员密码修改成功");
	}
	else
	{
		m_nPasswordCZ = IDStr;
		MessageBox("操作员密码修改成功");
	}
	SavePara(m_sFile);

	//OnClose();
	OnOK();	
}

void CDLGMIMA::OnBnClickedBtnCancell()
{
	// TODO: 在此添加控件通知处理程序代码
	OnClose();
	OnCancel();
}

void CDLGMIMA::SavePara(CString ProductFileName)   //保存参数
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	

	CDialog::OnClose();
}

HBRUSH CDLGMIMA::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	else if (nCtlColor == CTLCOLOR_DLG)
	{
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(160,189,239));

		aBrush = CreateSolidBrush(RGB(160,189,239));
		hbr = aBrush;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
