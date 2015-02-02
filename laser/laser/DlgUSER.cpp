// DlgUSER.cpp : 实现文件
//

#include "stdafx.h"
#include "laser.h"
#include "DlgUSER.h"



extern BOOL  b_XiuGai;
extern BOOL  b_EXIT;
extern int master;

//1226新加代码
CString  m_nUserID;
CString  m_nPasswordCZ;
CString  m_nPasswordGL;





// CDlgUSER 对话框

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


// CDlgUSER 消息处理程序

void CDlgUSER::OnBnClickedYes()
{
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItem(IDC_COMBO_ID)->GetWindowText(m_nUserID);
	CString str;
	GetDlgItem(IDC_EDIT_KEYWORD)->GetWindowText(str);
	for (int i = 0; i < 3; i ++)
	{
		if (m_nUserID == "管理员")
		{
			if (m_nPasswordGL == str)
			{
				//MessageBox("登陆成功");
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
					MessageBox("登陆次数过多，请与管理员联系");
					return;
				}
				MessageBox(_T("登录失败!\r\n请检查用户名或密码是否输入正确。"));
				m_nTimes ++;
				return;
			}
		}
		else if (m_nUserID == "操作员")
		{
			if (m_nPasswordCZ == str)
			{
				//MessageBox("登陆成功");
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
					MessageBox("登陆次数过多，请与管理员联系");
					//GetDlgItem(IDC_EDIT_KEYWORD)->EnableWindow(false);
					return;
				}
				MessageBox(_T("登录失败!\r\n请检查用户名或密码是否输入正确。"));
				m_nTimes ++;
				return;
			}
		}

	}
}

void CDlgUSER::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	OnCancel();
	b_EXIT = FALSE;
}

BOOL CDlgUSER::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	((CComboBox*)GetDlgItem(IDC_COMBO_ID))->SetCurSel(0);

	CString sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	int nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	m_sFile = sPath+"\\";

	LoadPara(m_sFile);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgUSER::LoadPara(CString ProductFileName)   //保存参数
{
	CFile paraFile;
	if(!paraFile.Open(ProductFileName+"Password"+".dat",CFile::modeRead))
	{
		MessageBox("密码文件打开失败，密码请使用初始密码！");
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
	// TODO: 在此添加控件通知处理程序代码
	//GetDlgItem(IDC_COMBO_ID)->GetWindowText(m_nUserID);
	//if (m_nUserID == "管理员")
	//{
	//	GetDlgItem(IDC_EDIT_KEYWORD)->EnableWindow(true);
	//}
}

HBRUSH CDlgUSER::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CDlgUSER::OnBnClickedBtnXiugai()
{
	// TODO: 在此添加控件通知处理程序代码
	m_DlgMiMa.DoModal();
}
