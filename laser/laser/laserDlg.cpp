// laserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "laser.h"
#include "laserDlg.h"

#include "PLC_COMMAND.h"

#include <io.h>
#include <odbcinst.h>
#include <afxdb.h>

#include "comdef.h"  

#include "ADODB.h"

#include <windows.h>

#define hostlinktime 1001



#ifdef _DEBUG
#define new DEBUG_NEW
#endif



struct ProPara para;   // ��Ʒ�����洢
 int   m_CurIndex;           // ��ǰ��Ʒ�������´�ֱ����ʾ
 BOOL  b_XiuGai;
 int master;
 CString m_strDate;    //ϵͳʱ��
 CString m_PointDate;

 //IO����Ʋ���
 int DIO[5][12];
// 
 CString   m_sExcelFile;    //·����

extern CAdoDB g_adoDB;

 extern CListCtrl m_IOListCtrl;

int DaBiaoList[m]={7,12,9,4};



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// ClaserDlg �Ի���




ClaserDlg::ClaserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ClaserDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_CurIndex = 0;
	b_XiuGai = false;

	for (int i = 0; i < 5; i ++)
	{
		for (int j = 0; j < 12; j ++)
		{
			DIO[i][j] = 0;
		}
	}
}

void ClaserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, MyCOMM);
	DDX_Control(pDX, IDC_STATIC_Icon, m_Icon_Open);
	DDX_Control(pDX, IDC_STATIC_NG, m_Icon_NG);
	DDX_Control(pDX, IDC_COMBO_PRO, m_ProXH);
	DDX_Control(pDX, IDC_COMBO_SCBC, m_BanCiComb);
	DDX_Control(pDX, IDC_MSCOMM2, PLC_COMM);
	DDX_Control(pDX, IDC_MSCOMM3, CODE_COMM);
	DDX_Control(pDX, IDC_COMBO_SSKaiG, m_comb_SSKaiG);
	DDX_Control(pDX, IDC_COMBO_SSGuangQ, m_Comb_SSGuangX);
}

BEGIN_MESSAGE_MAP(ClaserDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDOK, &ClaserDlg::OnBnClickedOk)
	//ON_BN_CLICKED(IDCANCEL, &ClaserDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_DAOCHU, &ClaserDlg::OnBnClickedBtnDaochu)
	ON_BN_CLICKED(IDC_BTN_PARA, &ClaserDlg::OnBnClickedBtnPara)
	ON_BN_CLICKED(IDC_BTN_INIT, &ClaserDlg::OnBnClickedBtnInit)
	ON_BN_CLICKED(IDC_BTN_STOP, &ClaserDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_QUIT, &ClaserDlg::OnBnClickedBtnQuit)
	ON_BN_CLICKED(IDC_BTN_USER, &ClaserDlg::OnBnClickedBtnUser)
	ON_BN_CLICKED(IDC_BTN_IO, &ClaserDlg::OnBnClickedBtnIo)
	ON_BN_CLICKED(IDC_BTN_YES, &ClaserDlg::OnBnClickedBtnYes)
	//ON_BN_CLICKED(IDC_BTN_KaiGuan, &ClaserDlg::OnBnClickedBtnKaiguan)
	//ON_BN_CLICKED(IDC_BTN_DABIAO, &ClaserDlg::OnBnClickedBtnDabiao)
	ON_BN_CLICKED(IDC_BTN_DAYIN, &ClaserDlg::OnBnClickedBtnDayin)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_VISM, &ClaserDlg::OnBnClickedBtnVism)
	ON_BN_CLICKED(IDC_BTN_YAJIN, &ClaserDlg::OnBnClickedBtnYajin)
	ON_BN_CLICKED(IDC_BTN_TAIQI, &ClaserDlg::OnBnClickedBtnTaiqi)
	ON_BN_CLICKED(IDC_BTN_HOULA, &ClaserDlg::OnBnClickedBtnHoula)
	ON_BN_CLICKED(IDC_BTN_QIANJIN, &ClaserDlg::OnBnClickedBtnQianjin)
	ON_BN_CLICKED(IDC_BTN_SHANGSHENG, &ClaserDlg::OnBnClickedBtnShangsheng)
	ON_BN_CLICKED(IDC_BTN_XIAJIANG, &ClaserDlg::OnBnClickedBtnXiajiang)
	ON_BN_CLICKED(IDC_BTN_SSTC, &ClaserDlg::OnBnClickedBtnSstc)
	ON_BN_CLICKED(IDC_BTN_SSHT, &ClaserDlg::OnBnClickedBtnSsht)
	ON_BN_CLICKED(IDC_BTN_JLTC, &ClaserDlg::OnBnClickedBtnJltc)
	ON_BN_CLICKED(IDC_BTN_JLHT, &ClaserDlg::OnBnClickedBtnJlht)
	ON_BN_CLICKED(IDC_BTN_VISKZ, &ClaserDlg::OnBnClickedBtnViskz)
	ON_BN_CLICKED(IDC_BTN_READ, &ClaserDlg::OnBnClickedBtnRead)
END_MESSAGE_MAP()


// ClaserDlg ��Ϣ�������

BOOL ClaserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//ShowWindow(SW_MAXIMIZE);
	if (b_XiuGai == TRUE)
	{
		GetDlgItem(IDC_BTN_PARA)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_PARA)->EnableWindow(FALSE);
	}

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_hIcon_open = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_OK));
    m_hIcon_close = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_NG));

	m_Icon_Open.SetIcon(m_hIcon_close);
	m_Icon_NG.SetIcon(m_hIcon_close);

	//��ȡϵͳʱ��

	CTime m_time;
	CString Datestr;
	m_time = CTime::GetCurrentTime();
	Datestr = m_time.Format(_T("%Y%m%d"));

	m_strDate = Datestr.Right(6);

	CString strr,str1,str2,str3;
	strr = m_strDate.Left(4);
	str1 = strr.Left(2);
	str2 = strr.Right(2);
	str3 = m_strDate.Right(2);

	m_PointDate = str1+"."+str2+"."+str3;




	//�����ݿ����
	CString sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	int nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	m_sExcelFile = sPath+"\\laser.xls";    //Ҫ������Excel�ļ�

	if (!g_adoDB.IsOpen())
	{
		if (!g_adoDB.Open(_T("LaserPara"))) 
		{
			MessageBox(_T("���ܴ�����Դ������!"),_T("������ʾ"));
			return FALSE;
		}
	}

	ExcelToAccess();

	//��ʼ������
	m_BanCiComb.SetCurSel(0);
	m_comb_SSKaiG.SetCurSel(0);
	m_Comb_SSGuangX.SetCurSel(0);

	m_IOListDlg.Create(IDD_DLG_IO,this);
	

	CString str;

	//������ǰ
	SetWindowPos(&CWnd::wndTopMost,0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);  //OnTop


	//���д�����
	HINSTANCE hNewExe = ShellExecute(NULL,"open","C:\\marker\\bin\\atgui30.exe",NULL,NULL,SW_MINIMIZE);  //SW_SHOWNORMAL SW_SHOWMINIMIZED
	Sleep(2000);
	if ((DWORD)hNewExe <= 32)
	{
		//str.Format("renturn value:%d\n",(DWORD)hNewExe);
		str.Format("�������ʧ��!");
		MessageBox(str);
		return 0;
	}
	else
	{
		str.Format("������򿪳ɹ�!\r\n");
		//CaoZuoDisp(str);

		//MessageBox(str);
	}

	//ȡ����ǰ
	SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);  //NoOnTop


	//bar code init
	if(CODE_COMM.get_PortOpen()==1)
		CODE_COMM.put_PortOpen(false);
	CODE_COMM.put_CommPort(1);
	CODE_COMM.put_InBufferSize(2048);
	CODE_COMM.put_OutBufferSize(2048);
	CODE_COMM.put_PortOpen(true);
	CODE_COMM.put_InputMode(1);
	CODE_COMM.put_Settings(_T("115200,N,8,1"));
	CODE_COMM.put_RThreshold(1);
	CODE_COMM.put_InputLen(0);
	CODE_COMM.get_Input();	
	//PLC COMM INIT
	if(PLC_COMM.get_PortOpen()==1)
		PLC_COMM.put_PortOpen(false);
	PLC_COMM.put_CommPort(4);
	PLC_COMM.put_InBufferSize(2048);
	PLC_COMM.put_OutBufferSize(2048);
	PLC_COMM.put_PortOpen(true);
	PLC_COMM.put_InputMode(1);
	PLC_COMM.put_Settings(_T("19200,N,8,1"));
	PLC_COMM.put_RThreshold(1);
	PLC_COMM.put_InputLen(0);
	PLC_COMM.get_Input();
	//laser init
	if(MyCOMM.get_PortOpen()==1)
		MyCOMM.put_PortOpen(false);
	MyCOMM.put_CommPort(3);
	MyCOMM.put_InBufferSize(2048);
	MyCOMM.put_OutBufferSize(2048);
	MyCOMM.put_PortOpen(true);
	MyCOMM.put_InputMode(1);
	MyCOMM.put_Settings(_T("9600,N,8,1"));
	MyCOMM.put_RThreshold(1);
	MyCOMM.put_InputLen(0);
	MyCOMM.get_Input();



	para.m_VISFile = "";
	data_length = 0;
	chlen = 0;
	edit1_str = "";
	edit2_str = "";
	alarm[0] = 0;
	alarm[1] = 0;
	io_sign = 0;
	laser_sign = 0;
	laser_time = 0;
	laser_ctr = 0;
	laser_conf = 0;
	H260[0] = 0;
	H260[1] = 0;
	I260[0] = 0;
	I260[1] = 0;
	Q100[0] = 0;
	Q100[1] = 0;
	Q101[0] = 0;
	Q101[1] = 0;
	barlen = 0;

	SetTimer(hostlinktime, 100,NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void ClaserDlg::CaoZuoDisp(CString str)
{
	CString strOld;
	CTime m_time;
	CString m_strDate,m_strTime,m_strDateTime;
	m_time = CTime::GetCurrentTime();
	m_strDate = m_time.Format(_T("%x"));
	m_strTime = m_time.Format(_T("%x"));
	m_strDateTime = m_time.Format(_T("%Y-%m-%d  %H:%M:%S  %A"));

	GetDlgItem(IDC_EDIT_Erro1)->GetWindowText(strOld);

	strOld += m_strDateTime+"\r\n"+str;
	GetDlgItem(IDC_EDIT_Erro1)->SetWindowText(strOld);
}

void ClaserDlg::ExcelToAccess()
{
	CDatabase  database;
	CString    sSql,sAccess;
	CString    sItem1,sItem2,sItem3,sItem4,sItem5,sItem6,sItem7,sItem8,sItem9;
	CString    sDriver = "MICROSOFT EXCEL DRIVER(*.XLS)";
	CString    sDsn;
	CString    sExcelFile,sPath;
	CDBVariant varValue; 

	CString    str;

	int num = 0;

	//�������
	sAccess = "CREATE TABLE LaserPara(��Ʒ�ͺ� TEXT,��Ʒ���� TEXT,���� TEXT,AUTOLIV�� TEXT,��Ӧ�̱��� TEXT,ģ�߱��� TEXT,����ʶ��ӽ����� TEXT,����ʶ����� TEXT,ģ�� TEXT)";
	g_adoDB.Execute(sAccess);

	//·��������ѡ���޸�
	sExcelFile = m_sExcelFile;

	// �����Ƿ�װ��Excel���� "Microsoft Excel Driver (*.xls)" 
	sDriver = GetExcelDriver();
	if (sDriver.IsEmpty())
	{
		// û�з���Excel����
		AfxMessageBox("û�а�װExcel����!");
		return;
	}

	// �������д�ȡ���ַ���
	//sDsn.Format("ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sExcelFile);
	sDsn.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, sExcelFile, sExcelFile);

	TRY
	{
		// �����ݿ�(��Excel�ļ�)
		//database.Open(NULL, false, false, sDsn);
		database.OpenEx(sDsn,CDatabase::noOdbcDialog);

		CRecordset recset(&database);
		// ���ö�ȡ�Ĳ�ѯ���.ע��˴�������д��
		sSql = "SELECT * FROM laser"; 

		// ִ�в�ѯ���
		recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);

		// ��ȡ��ѯ���
		while (!recset.IsEOF())
		{
			//��ȡExcel�ڲ���ֵ
			recset.GetFieldValue("��Ʒ�ͺ�", sItem1);
			recset.GetFieldValue("��Ʒ����", sItem2);
			recset.GetFieldValue("����", sItem3);
			recset.GetFieldValue("AUTOLIV��", sItem4);
			recset.GetFieldValue("��Ӧ�̱���", sItem5);
			recset.GetFieldValue("ģ�߱���", sItem6);
			recset.GetFieldValue("����ʶ��ӽ�����", sItem7);
			recset.GetFieldValue("����ʶ�����", sItem8);
			recset.GetFieldValue("ģ��", sItem9);

			//����Ʒ�ͺſؼ���ֵ
			m_ProXH.AddString(sItem1);

			para.m_CPXH = sItem1;
			para.m_ChanPJH = sItem2;
			para.m_Data = sItem3;
			para.m_AUTOLIV = sItem4;
			para.m_CustomNo = sItem5;
			para.m_MoJuBM = sItem6;
			para.m_SSKaiG = sItem7;
			para.m_SSGuangX = sItem8;
			para.m_VISFile = sItem9;

			num ++;


			//��Excel�д洢�����ݿ���
			sAccess.Format("INSERT INTO LaserPara(��Ʒ�ͺ�,��Ʒ����,����,AUTOLIV��,��Ӧ�̱���,ģ�߱���,����ʶ��ӽ�����, ����ʶ�����, ģ��)" 
				"VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s')",	sItem1,sItem2,sItem3,sItem4,sItem5,sItem6,sItem7,sItem8,sItem9);
			g_adoDB.Execute(sAccess);
			// �Ƶ���һ��
			recset.MoveNext();
		}

		if (num != 0)
		{
			m_ProXH.SetCurSel(num-1);
		}
		
		// �ر����ݿ�
		database.Close();
	}
	CATCH(CDBException, e)
	{
		// ���ݿ���������쳣ʱ...
		AfxMessageBox("���ݿ����: " + e->m_strError);
	}
	END_CATCH;
}

void ClaserDlg::AccessToExcel()
{
	CDatabase database;
	CString sSql, sAccess;
	CDStrs FInfo;
	CString sDriver = "MICROSOFT EXCEL DRIVER(*.XLS)";
	CString sExcelFile = m_sExcelFile;
	BOOL    B_exist = false;
	CString strName, sItem1;

	CString str1,str2,str3,str4,str5,str6,str7,str8,str9;

	CString path;
	CString SystemPath;
	CString ProductFileName;

	BOOL    m_bChanPE = FALSE;

	//int ret = MessageBox("ȷ��Ҫ���������Excel�������","",MB_YESNO);
	//if (ret != 6)
	//	return;

	// �����Ƿ�װ��Excel������Microsoft Excel Driver(*.xls)��
	sDriver = GetExcelDriver();
	if (sDriver.IsEmpty())
	{
		// û�з���Excel����
		AfxMessageBox("û�а�װExcel������");
		return;
	}

	// ��ѯ�Ƿ����
	int exist = _access(sExcelFile,0);
	if (exist == -1)
	{
		B_exist = true;
	}
	else
	{
		B_exist = false;
		//ɾ��Excel�ļ�
		DeleteFile(sExcelFile);
		//B_exist = true;
		//����һ�����е��ļ�
		CopyFile("D:\\laser.xls",sExcelFile,false);
	}

	// �������д�ȡ���ַ���
	TRY
	{
		sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, sExcelFile, sExcelFile);
		if(database.OpenEx(sSql,CDatabase::noOdbcDialog))
		{
			if (B_exist)
			{
				// ������
				sSql = "CREATE TABLE laser(��Ʒ�ͺ� TEXT,��Ʒ���� TEXT,���� TEXT,AUTOLIV�� TEXT,��Ӧ�̱��� TEXT,ģ�߱��� TEXT,����ʶ��ӽ����� TEXT,����ʶ����� TEXT,ģ�� TEXT)";
				database.ExecuteSQL(sSql);
			}

			//�������ݿ��е����ݵ��б���
			sAccess.Format(_T("Select * from LaserPara"));
			g_adoDB.ExecuteQuery(sAccess,FInfo);

			CStringArray items;
			for (size_t i = 0;i < FInfo.size();i++)
			{
				items.RemoveAll();
				for (size_t j = 0;j < ShuJuNum; j++)
				{
					items.Add(FInfo[i][j]);
				}
				//���뵽Excel��
				//sSql.Format("INSERT INTO demo(��Ʒ�ͺ�,��Ʒ����,AUTOLIV,�ͻ�����,��֤����,"
				//	"���ͺ�,LogoNo,Ʒ�ƺ�,�����,�������,NHA����,������,ģ����,VISFile)" 
				sSql.Format("INSERT INTO laser(��Ʒ�ͺ�,��Ʒ����,����,AUTOLIV��,��Ӧ�̱���,ģ�߱���,����ʶ��ӽ�����,����ʶ�����,ģ��)" 
					"VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s')",
					items.GetAt(0),items.GetAt(1),items.GetAt(2),items.GetAt(3),items.GetAt(4),items.GetAt(5),items.GetAt(6),items.GetAt(7),items.GetAt(8));
				database.ExecuteSQL(sSql);
			}
			//�ر����ݿ�
			database.Close();
		}
	}
	CATCH_ALL(e)
	{
		TRACE1("Excelд�����%s",sDriver);
		MessageBox("���ݱ������");
	}
	END_CATCH_ALL;
}

void ClaserDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
	//	CByteArray hexdata;
	if(!PLC_COMM.get_PortOpen())
		return;
	BYTE send[20];

	send[0] = (BYTE)0x1F;//head
	send[1] = (BYTE)0x01;
	send[2] = (BYTE)0x0; //I0;
	send[3] = (BYTE)0x0;
	send[4] = (BYTE)0x0;//I1
	send[5] = (BYTE)0x0;
	send[6] = (BYTE)0x0;//I2
	send[7] = (BYTE)0x0;
	send[8] =  (BYTE)0x0;
	send[9] = Q100[1];
	send[10] = 0x0;
	send[11] = Q101[1];
	send[12] = (BYTE)0x0;
	send[13] =Q102[1];
	send[14] = (BYTE)0x0;
	send[15] = (BYTE)0x0;
	send[16] = I260[0];
	send[17] = (BYTE)0x0;
	send[18] = (BYTE)0x0D;
	send[19] = (BYTE)0x0A;
	CByteArray hexdata;
	hexdata.SetSize(20);
	for(int i=0;i<20;i++)
		hexdata.SetAt( i, *((BYTE *) &send+i));
	PLC_COMM.put_Output(COleVariant(hexdata));

	if((Q101[1] & 0x080) != 0)
	{
		if(laser_ctr++>10)
		{
			laser_ctr = 0;
			Q101[1] = Q101[1] & 0x7F;
		}

	}

	//���IO�����
	//X000-X007
	if((I0[0] & 0x01) == 0)
		DIO[0][0] = 0;
	else
		DIO[0][0] = 1;

	if (I0[0]&0x02 == 0)
		DIO[0][1] = 0;
	else
		DIO[0][1] = 1;

	if((I0[0] & 0x03) == 0)
		DIO[0][2] = 0;
	else
		DIO[0][2] = 1;

	if (I0[0]&0x04 == 0)
		DIO[0][3] = 0;
	else
		DIO[0][3] = 1;

	if((I0[0] & 0x05) == 0)
		DIO[0][4] = 0;
	else
		DIO[0][4] = 1;

	if (I0[0]&0x06 == 0)
		DIO[0][5] = 0;
	else
		DIO[0][5] = 1;

	if((I0[0] & 0x07) == 0)
		DIO[0][6] = 0;
	else
		DIO[0][6] = 1;

	if (I0[0]&0x08 == 0)
		DIO[0][7] = 0;
	else
		DIO[0][7] = 1;

	//X008-X011
	if((I0[1] & 0x01) == 0)
		DIO[0][8] = 0;
	else
		DIO[0][8] = 1;

	if (I0[1]&0x02 == 0)
		DIO[0][9] = 0;
	else
		DIO[0][9] = 1;

	if((I0[1] & 0x03) == 0)
		DIO[0][10] = 0;
	else
		DIO[0][10] = 1;

	if (I0[1]&0x04 == 0)
		DIO[0][11] = 0;
	else
		DIO[0][11] = 1;

	//X100-X107
	if((I1[0] & 0x01) == 0)
		DIO[1][0] = 0;
	else
		DIO[1][0] = 1;

	if (I1[0]&0x02 == 0)
		DIO[1][1] = 0;
	else
		DIO[1][1] = 1;

	if((I1[0] & 0x03) == 0)
		DIO[1][2] = 0;
	else
		DIO[1][2] = 1;

	if (I1[0]&0x04 == 0)
		DIO[1][3] = 0;
	else
		DIO[1][3] = 1;

	if((I1[0] & 0x05) == 0)
		DIO[1][4] = 0;
	else
		DIO[1][4] = 1;

	if (I1[0]&0x06 == 0)
		DIO[1][5] = 0;
	else
		DIO[1][5] = 1;

	if((I1[0] & 0x07) == 0)
		DIO[1][6] = 0;
	else
		DIO[1][6] = 1;

	if (I1[0]&0x08 == 0)
		DIO[1][7] = 0;
	else
		DIO[1][7] = 1;

	//X108-X111
	if((I1[1] & 0x01) == 0)
		DIO[1][8] = 0;
	else
		DIO[1][8] = 1;

	if (I1[1]&0x02 == 0)
		DIO[1][9] = 0;
	else
		DIO[1][9] = 1;

	if((I1[1] & 0x03) == 0)
		DIO[1][10] = 0;
	else
		DIO[1][10] = 1;

	if (I1[1]&0x04 == 0)
		DIO[1][11] = 0;
	else
		DIO[1][11] = 1;

	//X200-X207
	if((I2[0] & 0x01) == 0)
		DIO[2][0] = 0;
	else
		DIO[2][0] = 1;

	if (I2[2]&0x02 == 0)
		DIO[2][1] = 0;
	else
		DIO[2][1] = 1;

	if((I1[2] & 0x03) == 0)
		DIO[2][2] = 0;
	else
		DIO[2][2] = 1;

	if (I2[0]&0x04 == 0)
		DIO[2][3] = 0;
	else
		DIO[2][3] = 1;

	if((I2[0] & 0x05) == 0)
		DIO[2][4] = 0;
	else
		DIO[2][4] = 1;

	if (I2[0]&0x06 == 0)
		DIO[2][5] = 0;
	else
		DIO[2][5] = 1;

	if((I2[0] & 0x07) == 0)
		DIO[2][6] = 0;
	else
		DIO[2][6] = 1;

	if (I2[0]&0x08 == 0)
		DIO[2][7] = 0;
	else
		DIO[2][7] = 1;

	//X108-X111
	if((I2[1] & 0x01) == 0)
		DIO[2][8] = 0;
	else
		DIO[2][8] = 1;

	if (I2[1]&0x02 == 0)
		DIO[2][9] = 0;
	else
		DIO[2][9] = 1;

	if((I2[1] & 0x03) == 0)
		DIO[2][10] = 0;
	else
		DIO[2][10] = 1;

	if (I2[1]&0x04 == 0)
		DIO[2][11] = 0;
	else
		DIO[2][11] = 1;

	

	//Y10100-Y10107
	if((Q100[0] & 0x01) == 0)
		DIO[3][0] = 0;
	else
		DIO[3][0] = 1;

	if (Q100[0]&0x02 == 0)
		DIO[3][1] = 0;
	else
		DIO[3][1] = 1;

	if((Q100[0] & 0x03) == 0)
		DIO[3][2] = 0;
	else
		DIO[3][2] = 1;

	if (Q100[0]&0x04 == 0)
		DIO[3][3] = 0;
	else
		DIO[3][3] = 1;

	if((Q100[0] & 0x05) == 0)
		DIO[3][4] = 0;
	else
		DIO[3][4] = 1;

	if (Q100[0]&0x06 == 0)
		DIO[3][5] = 0;
	else
		DIO[3][5] = 1;

	if((Q100[0] & 0x07) == 0)
		DIO[3][6] = 0;
	else
		DIO[3][6] = 1;

	if (Q100[0]&0x08 == 0)
		DIO[3][7] = 0;
	else
		DIO[3][7] = 1;

	//Y10100-Y10107
	if((Q101[0] & 0x01) == 0)
		DIO[3][8] = 0;
	else
		DIO[3][8] = 1;

	if (Q101[0]&0x02 == 0)
		DIO[3][9] = 0;
	else
		DIO[3][9] = 1;

	if((Q101[0] & 0x03) == 0)
		DIO[3][10] = 0;
	else
		DIO[3][10] = 1;

	if (Q101[0]&0x04 == 0)
		DIO[3][11] = 0;
	else
		DIO[3][11] = 1;

	if((Q101[0] & 0x05) == 0)
		DIO[4][0] = 0;
	else
		DIO[4][0] = 1;

	if (Q101[0]&0x06 == 0)
		DIO[4][1] = 0;
	else
		DIO[4][1] = 1;

	if((Q101[0] & 0x07) == 0)
		DIO[4][2] = 0;
	else
		DIO[4][2] = 1;

	if (Q101[0]&0x08 == 0)
		DIO[3][3] = 0;
	else
		DIO[4][3] = 1;

	//Y10200-Y10207
	if((Q102[0] & 0x01) == 0)
		DIO[4][4] = 0;
	else
		DIO[4][4] = 1;

	if (Q102[0]&0x02 == 0)
		DIO[4][5] = 0;
	else
		DIO[4][5] = 1;

	if((Q102[0] & 0x03) == 0)
		DIO[4][6] = 0;
	else
		DIO[4][6] = 1;

	if (Q102[0]&0x04 == 0)
		DIO[4][7] = 0;
	else
		DIO[4][7] = 1;

	if((Q102[0] & 0x05) == 0)
		DIO[4][8] = 0;
	else
		DIO[4][8] = 1;

	if (Q102[0]&0x06 == 0)
		DIO[4][9] = 0;
	else
		DIO[4][9] = 1;

	if((Q102[0] & 0x07) == 0)
		DIO[4][10] = 0;
	else
		DIO[4][10] = 1;

	if (Q102[0]&0x08 == 0)
		DIO[4][11] = 0;
	else
		DIO[4][11] = 1;

	DispIO1( );


	CString str;
	str.Format("%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x",
		send[0],send[1],send[2],send[3],send[4],send[5],send[6],send[7],send[8],send[9],send[10],send[11],send[12],send[13],send[14],send[15],send[16],send[17],send[18],send[19]);
	GetDlgItem(IDC_EDIT_ZSHM2)->SetWindowText(str);
}
void ClaserDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{		//ShowWindow(SW_MAXIMIZE);
		if (nID == SC_MOVE || nID ==0xF012)
		{
			return;
		}
		else
		{
			CDialog::OnSysCommand(nID, lParam);
		}
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void ClaserDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR ClaserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(ClaserDlg, CDialog)
	ON_EVENT(ClaserDlg, IDC_MSCOMM1, 1, ClaserDlg::OnCommMscomm, VTS_NONE)
	ON_EVENT(ClaserDlg, IDC_MSCOMM2, 1, ClaserDlg::OnCommMscomm2, VTS_NONE)
	ON_EVENT(ClaserDlg, IDC_MSCOMM3, 1, ClaserDlg::OnCommMscomm3, VTS_NONE)
END_EVENTSINK_MAP()

void ClaserDlg::OnCommMscomm()
{
	// TODO: �ڴ˴������Ϣ����������
	VARIANT recv_tmp;
	COleSafeArray recv_tmp1;
//	int length;
	BYTE ch[50];
	CString text_output;
	char buffer[50];
	int data_sign = 0;
	recv_tmp = MyCOMM.get_Input();
	//length = recv_tmp1.GetOneDimSize();
	//for(long i=0;i<length;i++)
	//	recv_tmp1.GetElement(&i,(ch+i+data_length));
}

void ClaserDlg::OnDestroy()
{
	CDialog::OnDestroy();
	KillTimer(hostlinktime);
}

//���ݲ�Ʒ���Ƶ�����Ӧ�Ĳ���
void ClaserDlg::OnBnClickedBtnDaochu()   //����������Ϣ��ָ���ļ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"All Files(*.*)|*.*||",AfxGetMainWnd());
	CString  strPath, strText = "";
	char write[1000];

	GetDlgItem(IDC_EDIT_MOJERRO)->GetWindowText(str);

	//��ȡ��ǰʱ��
	CTime m_time;
	CString m_strDate,m_strTime,m_strDateTime;
	m_time = CTime::GetCurrentTime();
	m_strDate = m_time.Format(_T("%x"));
	m_strTime = m_time.Format(_T("%x"));
	m_strDateTime = m_time.Format(_T("%Y-%m-%d  %H:%M:%S  %A"));

	if (dlg.DoModal() == IDOK)
	{
		strPath = dlg.GetPathName();
		if (strPath.Right(4) != ".txt")
			strPath += ".txt";

		int n = _access(strPath,0);
		if (n == -1)
		{
			CFile file(_T(strPath),CFile::modeCreate|CFile::modeWrite);

			file.SeekToEnd();

			strText = m_strDateTime+"\r\n"+str+"\r\n";
			strcpy(write,strText);
			file.Write(write,strText.GetLength());
			file.Close();
			MessageBox("�������");
		}
		else
		{
			CFile file(_T(strPath),CFile::modeReadWrite);

			file.SeekToEnd();

			strText = m_strDateTime+"\r\n"+str+"\r\n";
			strcpy(write,strText);
			file.Write(write,strText.GetLength());
			file.Close();
			MessageBox("�������");
		}

	}
}

void ClaserDlg::OnBnClickedBtnPara()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ParaSetDlg.DoModal();
	//m_ParaSetDlg.ShowWindow(SW_SHOW);
}

void ClaserDlg::OnBnClickedBtnInit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ����������
}

void ClaserDlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	// ֹͣ����
}

void ClaserDlg::OnBnClickedBtnQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ��������

	//������Excel
	//AccessToExcel();
	OnClose();
	// �˳�����
	OnCancel();
}

void ClaserDlg::OnBnClickedBtnUser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_USERDlg.DoModal();
	//MessageBox("fine");

	if(b_XiuGai)
	{
		GetDlgItem(IDC_BTN_PARA)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_PARA)->EnableWindow(FALSE);
	}	
}

void ClaserDlg::OnBnClickedBtnIo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
 
	m_IOListDlg.ShowWindow(SW_SHOW);
	//m_IOListDlg.DoModal();
	io_sign = 1;
}

void ClaserDlg::OnBnClickedBtnYes()  //��ʾ���ݵ�������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString    sSql;
	CString    strName;
	int        CurIndex = m_CurIndex;
	CDStrs     FInfo;
	CStringArray items;

	GetDlgItem(IDC_COMBO_PRO)->GetWindowText(strName);

	sSql.Format("Select * from LaserPara where ��Ʒ�ͺ� = '%s'",strName);
	g_adoDB.ExecuteQuery(sSql,FInfo);

	if (g_adoDB.GetAdoItemCount(sSql) > 0)
	{
		for (size_t i = 0;i < FInfo.size();i++)
		{
			items.RemoveAll();
			for (size_t j = 0;j < ShuJuNum; j++)
			{
				items.Add(FInfo[i][j]);
			}
		}

		//���������汾���ؼ���
		GetDlgItem(IDC_EDIT_CPZJ)->SetWindowText(items.GetAt(1));
		GetDlgItem(IDC_EDIT_DATA)->SetWindowText(items.GetAt(2));
		GetDlgItem(IDC_EDIT_AUTOLIV)->SetWindowText(items.GetAt(3));
		GetDlgItem(IDC_EDIT_GYSBM)->SetWindowText(items.GetAt(4));
		GetDlgItem(IDC_EDIT_MOJU)->SetWindowText(items.GetAt(5));
		GetDlgItem(IDC_COMBO_SSKaiG)->SetWindowText(items.GetAt(6));
		GetDlgItem(IDC_COMBO_SSGuangQ)->SetWindowText(items.GetAt(7));
		GetDlgItem(IDC_EDIT_TEMP)->SetWindowText(items.GetAt(8));


		//��ֵ��para 
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


//void ClaserDlg::OnBnClickedBtnKaiguan()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//
//	CString str;
//	if (GetDlgItemText(IDC_BTN_KaiGuan,str),str == "��")
//	{
//		SetDlgItemText(IDC_BTN_KaiGuan,_T("��"));
//		m_Icon_Open.SetIcon(m_hIcon_open);
//		m_Icon_NG.SetIcon(m_hIcon_open);
//	}
//	else 
//	{
//		SetDlgItemText(IDC_BTN_KaiGuan,_T("��"));
//		m_Icon_Open.SetIcon(m_hIcon_close);
//		m_Icon_NG.SetIcon(m_hIcon_close);
//	}
//}

//void ClaserDlg::OnBnClickedBtnDabiao()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CString str;
//
//	str = "SET,control,local\r";
//	send_str(str);
//
//	str = "SET,control,host\r";
//	send_str(str);
//
//	if (para.m_VISFile == "")
//	{
//		MessageBox("��ѡ�������");
//		return;
//	}
//
//	str = "OPEN,file,"+para.m_VISFile+"\r";
//	send_str(str);
//
//	//1�޸Ĳ�Ʒ����
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[0],para.m_ChanPJH);
//	int n = DaBiaoList[4];
//	send_str(str);
//
//	//2�޸�AUTOLIV
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[1],para.m_AUTOLIV);
//	send_str(str);
//
//	//3�޸Ŀͻ�����
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[2],para.m_CustomNo);
//	send_str(str);
//
//	//4�޸���֤��Ϣ
//	//str.Format("MODIFY,field,%d,para.m_CertifiType\r",DaBiaoList[3]);
//	//send_str(str);
//
//	//5�޸ĳ�����
//	//str.Format("MODIFY,field,%d,para.m_CarTyle\r",DaBiaoList[4]);
//	//send_str(str);
//
//	//6�޸�logoNo
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[5],para.m_LogoNo);
//	send_str(str);
//
//	//7�޸�Ʒ�ƺ�
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[6],para.m_PinPaiNo);
//	send_str(str);
//
//	//8�޸ķ����
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[7],para.m_FangCuoK);
//	send_str(str);
//
//	//9�޸Ĺ������
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[8],para.m_GongChanNo);
//	send_str(str);
//
//	//10�޸Ķ�ά��
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[9],para.m_NHANo);
//	send_str(str);
//
//	//11�޸������
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[10],para.m_ComponentNo);
//	send_str(str);
//
//	//12�޸�ģ���
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[11],para.m_FixNo);
//	send_str(str);
//
//	str = "RUN\r";
//	send_str(str);
//
//	Sleep(2000);
//
//	str = "SET,control,local\r";
//	send_str(str);
//}

void ClaserDlg::OnBnClickedBtnDayin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AccessToExcel();
	ShellExecute(NULL,"print",m_sExcelFile,NULL,NULL,SW_SHOWNORMAL);
}

void ClaserDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//������Excel
	AccessToExcel();
	//ɾ�����ر����ݿ�
	g_adoDB.Execute("DROP TABLE LaserPara");
	g_adoDB.Close();

	CDialog::OnClose();
}
void ClaserDlg::lasermark()
{
	CString str;
	if (para.m_VISFile == "" && laser_sign == 50)
	{
		MessageBox("��ѡ�������");
		return;
	}
	if(laser_sign == 50 || laser_sign == 1)
	{
		str = "SET,control,local\r";
		send_str(str);
		str = "SET,control,host\r";
		send_str(str);
// 		if (para.m_VISFile == "")
// 		{
// 			MessageBox("��ѡ�������");
// 			laser_sign = 0;
// 			return;
// 		}
		str = "OPEN,file,C:\\marker\\job\\"+para.m_VISFile+"\r";
		send_str(str);

	////1�޸Ĳ�Ʒ����
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[0],para.m_ChanPJH);
	//int n = DaBiaoList[4];
	//send_str(str);

	////2�޸�AUTOLIV
// 	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[1],para.m_AUTOLIV);
// 	send_str(str);

	////3�޸Ŀͻ�����
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[2],para.m_CustomNo);
//	send_str(str);

	////4�޸���֤��Ϣ
	////str.Format("MODIFY,field,%d,para.m_CertifiType\r",DaBiaoList[3]);
	////send_str(str);

	////5�޸ĳ�����
	////str.Format("MODIFY,field,%d,para.m_CarTyle\r",DaBiaoList[4]);
	////send_str(str);

	////6�޸�logoNo
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[5],para.m_LogoNo);
	//send_str(str);

	////7�޸�Ʒ�ƺ�
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[6],para.m_PinPaiNo);
	//send_str(str);

	////8�޸ķ����
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[7],para.m_FangCuoK);
	//send_str(str);

	////9�޸Ĺ������
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[8],para.m_GongChanNo);
	//send_str(str);

	////10�޸Ķ�ά��

// 	CTime m_time;
// 	CString m_strDate,m_strTime,m_strDateTime;
// 	m_time = CTime::GetCurrentTime();
// 	// 	m_strDate = m_time.Format(_T("%x"));
// 	// 	m_strTime = m_time.Format(_T("%x"));
// 	m_strDateTime = m_time.Format(_T("%Y%m%d"));
// 	laser_code = para.m_NHANo + " " + m_strDateTime;
// 	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[9],laser_code);
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[9],para.m_NHANo);
	//send_str(str);

	////11�޸������
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[10],para.m_ComponentNo);
	//send_str(str);

	////12�޸�ģ���
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[11],para.m_FixNo);
	//send_str(str);

		str = "RUN\r";
		send_str(str);
		if (laser_sign == 1)
			laser_sign = 2;
	}
	if(laser_sign == 50)
		Sleep(2000);
	if(laser_sign == 3 || laser_sign==50)
	{
		str = "SET,control,local\r";
		send_str(str);
		if(laser_sign == 3)
			laser_sign = 4;
	}

}
void ClaserDlg::OnBnClickedBtnVism()
{

	if (para.m_VISFile == "")
	{
//		MessageBox("��ѡ�������");
		return;
	}
	laser_sign = 50;
	//lasermark();

	// TODO: �ڴ���ӿؼ�֪ͨ����������
 	CString str;
 
 	str = "SET,control,local\r";
 	send_str(str);
 
 	str = "SET,control,host\r";
 	send_str(str);
 
 	if (para.m_VISFile == "")
 	{
 		MessageBox("��ѡ�������");
 		return;
 	}
 
 	str = "OPEN,file,C:\\marker\\job\\"+para.m_VISFile+"\r";
 	send_str(str);
// 

	//2�޸�����
	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[0],m_strDate);   
	send_str(str);

 	//3�޸�AUTOLIV
  	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[1],para.m_AUTOLIV);
 	send_str(str);

	//4�޸Ĺ�Ӧ�̱���
	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[2],para.m_CustomNo);
	send_str(str);

	//5�޸Ķ�ά��
	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[3],para.m_ChanPJH+" "+m_strDate);
	send_str(str);
 


 	str = "RUN\r";
 	send_str(str);
 
 	Sleep(2000);
 
 	str = "SET,control,local\r";
 	send_str(str);
}

void ClaserDlg::OnCommMscomm2()//PLC
{
	// TODO: �ڴ˴������Ϣ����������
	VARIANT recv_tmp;
	COleSafeArray recv_tmp1;
	int length = 0;
	BYTE ch[50];
	recv_tmp = PLC_COMM.get_Input();
	recv_tmp1 = recv_tmp;
	length = recv_tmp1.GetOneDimSize();
	for(long i=0;i<length;i++)
		recv_tmp1.GetElement(&i,(ch+i));
	for (long i=0;i<length;i++,chlen++)
	{
		if (chlen>49 || length>49)
		{
			chlen = 0;
			break;
		}
		recv[chlen] = ch[i];		
	}
	if(recv[chlen-2] == (BYTE)0x0D && recv[chlen-1] == (BYTE)0x0A)
		chlen = 0;
	else
		return;
	if(recv[0] == 0x2F && recv[1] == 0x02)
	{
		I0[1] = recv[2];
		I0[0] = recv[3];
		I1[1] = recv[4];
		I1[0] = recv[5];
		I2[1] = recv[6];
		I2[0] = recv[7];
		Q100[0] = recv[9];
		Q101[0] = recv[11];
		Q102[0] = recv[13];
		H260[0] = recv[15];
		H260[1] = recv[14];
		I260[1] = recv[16];
		if (((Q101[1] &0x80) == 0x80)&& ((I260[0] & 0x020)!= 0))//barcode enable
		{
			if((Q101[0] & 0x080) ==0x080)
				Q101[1] = Q101[1] &0x7F;
		}
		if(((Q101[1] & 0x020)==0x20) &&((I260[0] & 0x020) != 0) ) // laser enable  
		{
			if ((Q101[0] & 0x020 )== 0x020)
				Q101[1] = Q101[1] & 0x0DF;
			
		}


		if(((I260[1] &0x10)!= 0) || ((I260[1] & 0x20)!=0)) //��ɺ������־λ
		{
			I260[0] = I260[0] &0x0F8;
			MessageBox("��ɺ����");
		}

		if ((I260[1]&0x04) == 0x04 )  // 0-ֹͣ��1-�Զ�
		{
			CString str1;
			M_state = 1;//�Զ�
			I260[0] = I260[0] & 0x0BF;
			if (para.m_VISFile == "")
			{
				if(laser_conf == 0)
				{
					CString str1;
					str1.Format("laser_conf=%d,260[1]=%x",laser_conf,I260[1]);
	//				MessageBox(str1);
//					MessageBox("����ѡ���Ʒ������");
					laser_conf = 2;
				}
			}
			else
				laser_conf = 1;
		}
		else
		{
			I260[0] = I260[0] & 0x0F8;
			M_state = 0 ;
		}


		if ((I260[1] & 0x02) == 0)
			I260[0] = I260[0] & 0x0FE;

		if((I260[1] &0x02) != 0 && laser_sign == 0 && laser_conf == 1)
				laser_sign = 1;

		if(laser_sign ==1 || laser_sign == 3)
			//lasermark();
		if(laser_sign ==2)
		{
			if(laser_time++>20)
			{
				laser_time = 0;
				laser_sign = 3;	
			}
		}
		if(laser_sign == 4)
		{
			if(laser_time++ > 80)
			{
				laser_time = 0;
				laser_sign = 5;
				I260[0] = I260[0] | 0x01;
			}
		}
		if(laser_sign == 5)
		{
			if(laser_time++ >20)
			{
				laser_time = 0;
				laser_sign =0;
			}
		}
// 		if ((I260[1] & (BYTE)0x030) !=0) //FINISH, NG OR OK 
//  			laser_conf = 0;

		
		if ((H260[0] !=0 || H260[1] !=0) && (H260[0] != alarm[0] || H260[1] != alarm[1]))
		{
			CTime m_time;
			CString m_strDate,m_strTime,m_strDateTime;
			m_time = CTime::GetCurrentTime();
			m_strDate = m_time.Format(_T("%x"));
			m_strTime = m_time.Format(_T("%x"));
//			m_strDateTime = m_time.Format(_T("%Y-%m-%d  %H:%M:%S  %A"));
			m_strDateTime = m_time.Format(_T("%Y-%m-%d  %H:%M:%S "));

			if ((H260[0] & 0x01) !=0 && (alarm[0] & 0x01) == 0)
				edit1_str = edit1_str+m_strDateTime +" ���� H260.00-ģ�߱ȶ�NG��"+"\r\n";
			if((H260[0] & 0x02) !=0 && (alarm[0]&0x02)==0)
				edit1_str =  edit1_str + m_strDateTime +" ���� H260.01-δ��⵽���࣡" + "\r\n";
			if((H260[0] & 0x04) !=0 && (alarm[0] &0x04)==0)
				edit1_str = edit1_str + m_strDateTime +" ���� H260.03-��ѹԴǷѹ��" + "\r\n";
			if ((H260[0] & 0x10) !=0 && (alarm[0] & 0x10)==0)
				edit1_str = edit1_str + m_strDateTime +" ���� H260.04-��ͣ��"+"\r\n";
			if((H260[0] & 0x20) !=0 && (alarm[0] &0x20)==0)
				edit1_str = edit1_str + m_strDateTime +" ���� H260.05-���ű��򿪣�"+"\r\n";
			if((H260[0] & 0x40) !=0 && (alarm[0]&0x40)==0)
				edit1_str = edit1_str + m_strDateTime +" ���� H260.06-����Ͱʧ�ܣ�" +"\r\n";
			if ((H260[0] & 0x80) !=0 && (alarm[0] &0x80) ==0)
				edit1_str = edit1_str + m_strDateTime +" ���� H260.07-�豸����ԭ�㣡"+"\r\n";
			if ((H260[1] & 0x04) !=0 && (alarm[1]&0x04)==0)
				edit1_str = edit1_str  + m_strDateTime +" ���� H260.10-��ȫ��Ļ������" + "\r\n";		
		}

		GetDlgItem(IDC_EDIT_MOJERRO)->SetWindowText(edit1_str);
		alarm[0] = H260[0];
		alarm[1] = H260[1];

		CString str;
		str.Format("%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,laser_sign=%d,laser_conf=%d,laser_time=%d",
			recv[0],recv[1],recv[2],recv[3],recv[4],recv[5],recv[6],recv[7],recv[8],recv[9],recv[10],recv[11],recv[12],recv[13],recv[14],recv[15],recv[16],recv[17],recv[18],recv[19],laser_sign,laser_conf,laser_time);
		GetDlgItem(IDC_EDIT_ZSHM)->SetWindowText(str);	


// 		if( I0[0]  & 0x01)
// 		{
// 			GetDlgItem(IDC_STATIC42)->ShowWindow(true);
// 			GetDlgItem(IDC_STATIC43)->ShowWindow(false);
// 		}
// 		else
// 		{
// 			GetDlgItem(IDC_STATIC42)->ShowWindow(false);
// 			GetDlgItem(IDC_STATIC43)->ShowWindow(true);
// 		}
	}

}

void ClaserDlg::OnCommMscomm3()   // bar code
{
	// TODO: �ڴ˴������Ϣ����������
	VARIANT recv_tmp;
	COleSafeArray recv_tmp1;
	int length = 0;
	BYTE ch[100];
	recv_tmp = CODE_COMM.get_Input();
	recv_tmp1 = recv_tmp;
	length = recv_tmp1.GetOneDimSize();
	for(long i=0;i<length;i++)
		recv_tmp1.GetElement(&i,(ch+i));
	for (long i=0;i<length;i++,barlen++)
	{
		if (barlen>99 || length>99)
		{
			barlen = 0;
			break;
		}
		barcode[barlen] = ch[i];		
	}
	if(barcode[barlen-2] == (BYTE)0x0D && barcode[barlen-1] == (BYTE)0x0A)
	{
		
		length = barlen-2;
		barlen = 0;
	}
	else
		return;
	BYTE *code1;
	CString ex1 = "FK72-611B09-AB8PVJ 140825";
	code1 = (BYTE *)ex1.GetBuffer(ex1.GetLength());
	ex1.Format("%s",code1);

// CString str1;
// str1.Format("%s,%s",laser_code,code);
// GetDlgItem(IDC_EDIT_ZSHM2)->SetWindowText(str1);

	if ((barcode[0] == 0x3F) && (barcode[1] == 0x03))
	{
		int i,laser_ok;
		for ( i=2;i<length; i++)
		{
			if(barcode[i] !=code1[i-2])
				break;
		}
		if (i==length && M_state==1)
		{
			I260[0] = I260[0] | 0x02;
			I260[0] = I260[0] & 0x0BF;
			laser_ok = 1;
		}
		else
		{
			I260[0] = I260[0] | 0x04;
			I260[0] = I260[0] &0x0FD;
			laser_ok = 0;
		}

		CString str;
		str.Format("%s||%s,%d,%d,%d",barcode,code1,laser_ok,i,length);
		GetDlgItem(IDC_EDIT20)->SetWindowText(str);
	}

}

void ClaserDlg::OnBnClickedBtnYajin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(M_state==0)
	{
		I260[0] = I260[0] | 0x20;
		Q101[1] = Q101[1] | 0x04;
	}
	else
		MessageBox("pls stop the machine first!");
}

void ClaserDlg::OnBnClickedBtnTaiqi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(M_state==0)
	{
		I260[0] = I260[0] | 0x20;
		Q101[1] = Q101[1] & 0x0FB;
	}
	else
		MessageBox("pls stop the machine first!");
}

void ClaserDlg::OnBnClickedBtnHoula()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(M_state==0)
	{
		I260[0] = I260[0] | 0x20;
		Q101[1] = Q101[1] |0x02;
	}
	else
		MessageBox("pls stop the machine first!");
}


void ClaserDlg::OnBnClickedBtnQianjin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(M_state==0)
	{
		I260[0] = I260[0] | 0x20;
		Q101[1] = Q101[1] & 0x0FD;
	}
	else
		MessageBox("pls stop the machine first!");
}

void ClaserDlg::OnBnClickedBtnShangsheng()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(M_state==0)
	{
		I260[0] = I260[0]|0x20;
		Q101[1] = Q101[1] | 0x01;
	}
	else
		MessageBox("pls stop the machine first!");
}

void ClaserDlg::OnBnClickedBtnXiajiang()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(M_state==0)
	{
		I260[0] = I260[0] | 0x20;
		Q101[1] = Q101[1] & 0x0FE;
	}
	else
		MessageBox("pls stop the machine first!");
}

void ClaserDlg::OnBnClickedBtnSstc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(M_state==0)
	{
		I260[0] = I260[0] | 0x20;
		Q100[1] = Q100[1] & 0x0BF;
	}
	else
		MessageBox("pls stop the machine first!");
}

void ClaserDlg::OnBnClickedBtnSsht()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(M_state==0)
	{
		I260[0] = I260[0]  | 0x20;
		Q100[1] = Q100[1] | 0x040;
	}
	else
		MessageBox("pls stop the machine first!");
}

void ClaserDlg::OnBnClickedBtnJltc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(M_state==0)
	{
		I260[0] = I260[0] | 0x20;
		Q100[1] = Q100[1] | 0x080;
	}
	else
		MessageBox("pls stop the machine first!");
}

void ClaserDlg::OnBnClickedBtnJlht()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(M_state==0)
	{
		I260[0] = I260[0] | 0x20;
		Q100[1] = Q100[1] & 0x07F;
	}
	else
		MessageBox("pls stop the machine first!");
}

void ClaserDlg::OnBnClickedBtnViskz()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(M_state==0)
	{
		I260[0] = I260[0] | 0x20;
		Q101[1] = Q101[1] | 0x020;
	}
	else
		MessageBox("pls stop the machine first!");
}

void ClaserDlg::OnBnClickedBtnRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (M_state == 0)
	{
		I260[0] = I260[0] | 0x02;
		Q101[1] = Q101[1] | 0x080;
	}
	else
		MessageBox("pls stop the machine first!");

}

void ClaserDlg::DispIO1(void)
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