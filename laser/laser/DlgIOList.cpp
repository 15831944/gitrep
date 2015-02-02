// DlgIOList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "laser.h"
#include "DlgIOList.h"

#include "PLC_COMMAND.h"
#include "laserDlg.h"


 extern int DIO[5][12];

 CListCtrl m_IOListCtrl;




// CDlgIOList �Ի���

IMPLEMENT_DYNAMIC(CDlgIOList, CDialog)

CDlgIOList::CDlgIOList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIOList::IDD, pParent)
{

}

CDlgIOList::~CDlgIOList()
{
}

void CDlgIOList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_IOListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgIOList, CDialog)
//	ON_WM_CTLCOLOR()
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgIOList ��Ϣ�������

//HBRUSH CDlgIOList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
//
//	// TODO:  �ڴ˸��� DC ���κ�����
//	HBRUSH aBrush;
//
//	if (nCtlColor == CTLCOLOR_STATIC)
//	{
//		pDC->SetTextColor(RGB(0,0,0));
//		pDC->SetBkColor(RGB(160,189,239));
//		aBrush = CreateSolidBrush(RGB(160,189,239));
//		hbr = aBrush;
//	}
//	else if (nCtlColor == CTLCOLOR_DLG)
//	{
//		pDC->SetTextColor(RGB(0,0,0));
//		pDC->SetBkColor(RGB(160,189,239));
//
//		aBrush = CreateSolidBrush(RGB(160,189,239));
//		hbr = aBrush;
//	}
//
//	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
//	return hbr;
//}

BOOL CDlgIOList::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	int i,j;
	CString strX[3][12];
	CString strY[3][8];
	CString strYY[2][12];
	CBitmap bitmap;
	CImageList *m_pImageList;
	bitmap.LoadBitmap(IDB_BITMAP1);
	m_pImageList = new CImageList();
	m_pImageList->Create(32,32,TRUE,2,2);
	m_pImageList->Add(&bitmap, RGB(0, 0, 0));


	m_IOListCtrl.SetExtendedStyle(m_IOListCtrl.GetExtendedStyle()
		|LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);

	m_IOListCtrl.SetImageList(m_pImageList,LVSIL_SMALL);


	m_IOListCtrl.InsertColumn(0,"IO����",LVCFMT_LEFT,80,-1);
	m_IOListCtrl.InsertColumn(1,"",LVCFMT_LEFT,32,-1);
	m_IOListCtrl.InsertColumn(2,"IO����",LVCFMT_LEFT,80,-1);
	m_IOListCtrl.InsertColumn(3,"",LVCFMT_LEFT,32,-1);
	m_IOListCtrl.InsertColumn(4,"IO����",LVCFMT_LEFT,80,-1);
	m_IOListCtrl.InsertColumn(5,"",LVCFMT_LEFT,32,-1);
	m_IOListCtrl.InsertColumn(6,"IO����",LVCFMT_LEFT,80,-1);
	m_IOListCtrl.InsertColumn(7,"",LVCFMT_LEFT,32,-1);
	m_IOListCtrl.InsertColumn(8,"IO����",LVCFMT_LEFT,80,-1);
	m_IOListCtrl.InsertColumn(9,"",LVCFMT_LEFT,32,-1);	



	int countnum = m_IOListCtrl.GetItemCount();

	//����X000-X200��ǰ9������
	for (i = 0;i < 10; i ++)
	{
		strX[0][i].Format("X00%d",i);
		strX[1][i].Format("X10%d",i);
		strX[2][i].Format("X20%d",i);

		m_IOListCtrl.InsertItem(i,strX[0][i],-1);
		m_IOListCtrl.SetItemText(i,2,strX[1][i]);
		m_IOListCtrl.SetItemText(i,4,strX[2][i]);
	}
	//����X000-X200��X010-X012����
	for (i = 10; i < 12; i ++)
	{
		strX[0][i].Format("X0%d",i);
		strX[1][i].Format("X1%d",i);
		strX[2][i].Format("X2%d",i);

		m_IOListCtrl.InsertItem(i,strX[0][i],-1);
		m_IOListCtrl.SetItemText(i,2,strX[1][i]);
		m_IOListCtrl.SetItemText(i,4,strX[2][i]);
	}
	//����Y10000-Y10200��8������
	for (i = 0; i < 8; i ++)
	{
		strY[0][i].Format("Y1000%d",i);
		strY[1][i].Format("Y1010%d",i);
		strY[2][i].Format("Y1020%d",i);
	}

	int mm = 0; 
	int nn = 0;

	for (i = 0; i < 3; i ++)
	{
		for (j = 0; j < 8; j ++)
		{
			strYY[mm][nn] = strY[i][j];
			m_IOListCtrl.SetItemText(nn,mm*2+6,strYY[mm][nn]);
			nn ++;
			if (nn >= 12)
			{
				nn = 0;
				mm = 1;
			}
		}

	}
	//DispIO();


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgIOList::DispIO(void)
{
	for (int i = 0; i < 5; i ++)
	{
		for (int j = 0; j < 12; j ++)
		{
			if (DIO[i][j] == 1)
			{
				m_IOListCtrl.SetItem(j,i*2+1,LVIF_TEXT|LVIF_IMAGE,_T(""),1,NULL,NULL, 0);
			}
			else
			{
				m_IOListCtrl.SetItem(j,i*2+1,LVIF_TEXT|LVIF_IMAGE,_T(""),0,NULL,NULL, 0);
			}
		}
	}
}


