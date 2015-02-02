// laserDlg.cpp : 实现文件
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



struct ProPara para;   // 产品参数存储
 int   m_CurIndex;           // 当前产品索引，下次直接显示
 BOOL  b_XiuGai;
 int master;
 CString m_strDate;    //系统时间
 CString m_PointDate;

 //IO表控制参数
 int DIO[5][12];
// 
 CString   m_sExcelFile;    //路径名

extern CAdoDB g_adoDB;

 extern CListCtrl m_IOListCtrl;

int DaBiaoList[m]={7,12,9,4};



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// ClaserDlg 对话框




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


// ClaserDlg 消息处理程序

BOOL ClaserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MAXIMIZE);
	if (b_XiuGai == TRUE)
	{
		GetDlgItem(IDC_BTN_PARA)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_PARA)->EnableWindow(FALSE);
	}

	// TODO: 在此添加额外的初始化代码
	m_hIcon_open = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_OK));
    m_hIcon_close = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_NG));

	m_Icon_Open.SetIcon(m_hIcon_close);
	m_Icon_NG.SetIcon(m_hIcon_close);

	//获取系统时间

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




	//打开数据库操作
	CString sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	int nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	m_sExcelFile = sPath+"\\laser.xls";    //要建立的Excel文件

	if (!g_adoDB.IsOpen())
	{
		if (!g_adoDB.Open(_T("LaserPara"))) 
		{
			MessageBox(_T("不能打开数据源的连接!"),_T("友情提示"));
			return FALSE;
		}
	}

	ExcelToAccess();

	//初始化开关
	m_BanCiComb.SetCurSel(0);
	m_comb_SSKaiG.SetCurSel(0);
	m_Comb_SSGuangX.SetCurSel(0);

	m_IOListDlg.Create(IDD_DLG_IO,this);
	

	CString str;

	//设置置前
	SetWindowPos(&CWnd::wndTopMost,0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);  //OnTop


	//运行打标软件
	HINSTANCE hNewExe = ShellExecute(NULL,"open","C:\\marker\\bin\\atgui30.exe",NULL,NULL,SW_MINIMIZE);  //SW_SHOWNORMAL SW_SHOWMINIMIZED
	Sleep(2000);
	if ((DWORD)hNewExe <= 32)
	{
		//str.Format("renturn value:%d\n",(DWORD)hNewExe);
		str.Format("打标程序打开失败!");
		MessageBox(str);
		return 0;
	}
	else
	{
		str.Format("打标程序打开成功!\r\n");
		//CaoZuoDisp(str);

		//MessageBox(str);
	}

	//取消置前
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
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

	//创建表格
	sAccess = "CREATE TABLE LaserPara(产品型号 TEXT,产品件号 TEXT,日期 TEXT,AUTOLIV号 TEXT,供应商编码 TEXT,模具编码 TEXT,锁舌识别接近开关 TEXT,锁舌识别光纤 TEXT,模板 TEXT)";
	g_adoDB.Execute(sAccess);

	//路径名根据选择修改
	sExcelFile = m_sExcelFile;

	// 检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)" 
	sDriver = GetExcelDriver();
	if (sDriver.IsEmpty())
	{
		// 没有发现Excel驱动
		AfxMessageBox("没有安装Excel驱动!");
		return;
	}

	// 创建进行存取的字符串
	//sDsn.Format("ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sExcelFile);
	sDsn.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, sExcelFile, sExcelFile);

	TRY
	{
		// 打开数据库(既Excel文件)
		//database.Open(NULL, false, false, sDsn);
		database.OpenEx(sDsn,CDatabase::noOdbcDialog);

		CRecordset recset(&database);
		// 设置读取的查询语句.注意此处表名的写法
		sSql = "SELECT * FROM laser"; 

		// 执行查询语句
		recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);

		// 获取查询结果
		while (!recset.IsEOF())
		{
			//读取Excel内部数值
			recset.GetFieldValue("产品型号", sItem1);
			recset.GetFieldValue("产品件号", sItem2);
			recset.GetFieldValue("日期", sItem3);
			recset.GetFieldValue("AUTOLIV号", sItem4);
			recset.GetFieldValue("供应商编码", sItem5);
			recset.GetFieldValue("模具编码", sItem6);
			recset.GetFieldValue("锁舌识别接近开关", sItem7);
			recset.GetFieldValue("锁舌识别光纤", sItem8);
			recset.GetFieldValue("模板", sItem9);

			//给产品型号控件赋值
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


			//从Excel中存储到数据库中
			sAccess.Format("INSERT INTO LaserPara(产品型号,产品件号,日期,AUTOLIV号,供应商编码,模具编码,锁舌识别接近开关, 锁舌识别光纤, 模板)" 
				"VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s')",	sItem1,sItem2,sItem3,sItem4,sItem5,sItem6,sItem7,sItem8,sItem9);
			g_adoDB.Execute(sAccess);
			// 移到下一行
			recset.MoveNext();
		}

		if (num != 0)
		{
			m_ProXH.SetCurSel(num-1);
		}
		
		// 关闭数据库
		database.Close();
	}
	CATCH(CDBException, e)
	{
		// 数据库操作产生异常时...
		AfxMessageBox("数据库错误: " + e->m_strError);
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

	//int ret = MessageBox("确定要保存参数到Excel表格中吗？","",MB_YESNO);
	//if (ret != 6)
	//	return;

	// 检索是否安装有Excel驱动“Microsoft Excel Driver(*.xls)”
	sDriver = GetExcelDriver();
	if (sDriver.IsEmpty())
	{
		// 没有发现Excel驱动
		AfxMessageBox("没有安装Excel驱动！");
		return;
	}

	// 查询是否存在
	int exist = _access(sExcelFile,0);
	if (exist == -1)
	{
		B_exist = true;
	}
	else
	{
		B_exist = false;
		//删除Excel文件
		DeleteFile(sExcelFile);
		//B_exist = true;
		//拷贝一个已有的文件
		CopyFile("D:\\laser.xls",sExcelFile,false);
	}

	// 创建进行存取的字符串
	TRY
	{
		sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, sExcelFile, sExcelFile);
		if(database.OpenEx(sSql,CDatabase::noOdbcDialog))
		{
			if (B_exist)
			{
				// 创建表
				sSql = "CREATE TABLE laser(产品型号 TEXT,产品件号 TEXT,日期 TEXT,AUTOLIV号 TEXT,供应商编码 TEXT,模具编码 TEXT,锁舌识别接近开关 TEXT,锁舌识别光纤 TEXT,模板 TEXT)";
				database.ExecuteSQL(sSql);
			}

			//导出数据库中的数据到列表中
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
				//导入到Excel中
				//sSql.Format("INSERT INTO demo(产品型号,产品件数,AUTOLIV,客户编码,认证类型,"
				//	"车型号,LogoNo,品牌号,防错孔,工厂编号,NHA编码,组件编号,模板编号,VISFile)" 
				sSql.Format("INSERT INTO laser(产品型号,产品件号,日期,AUTOLIV号,供应商编码,模具编码,锁舌识别接近开关,锁舌识别光纤,模板)" 
					"VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s')",
					items.GetAt(0),items.GetAt(1),items.GetAt(2),items.GetAt(3),items.GetAt(4),items.GetAt(5),items.GetAt(6),items.GetAt(7),items.GetAt(8));
				database.ExecuteSQL(sSql);
			}
			//关闭数据库
			database.Close();
		}
	}
	CATCH_ALL(e)
	{
		TRACE1("Excel写入出错：%s",sDriver);
		MessageBox("数据保存出错");
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

	//添加IO表控制
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void ClaserDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	// TODO: 在此处添加消息处理程序代码
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

//根据产品名称导出相应的参数
void ClaserDlg::OnBnClickedBtnDaochu()   //导出错误信息到指定文件
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"All Files(*.*)|*.*||",AfxGetMainWnd());
	CString  strPath, strText = "";
	char write[1000];

	GetDlgItem(IDC_EDIT_MOJERRO)->GetWindowText(str);

	//获取当前时间
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
			MessageBox("保存完成");
		}
		else
		{
			CFile file(_T(strPath),CFile::modeReadWrite);

			file.SeekToEnd();

			strText = m_strDateTime+"\r\n"+str+"\r\n";
			strcpy(write,strText);
			file.Write(write,strText.GetLength());
			file.Close();
			MessageBox("保存完成");
		}

	}
}

void ClaserDlg::OnBnClickedBtnPara()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ParaSetDlg.DoModal();
	//m_ParaSetDlg.ShowWindow(SW_SHOW);
}

void ClaserDlg::OnBnClickedBtnInit()
{
	// TODO: 在此添加控件通知处理程序代码

	// 数据做处理
}

void ClaserDlg::OnBnClickedBtnStop()
{
	// TODO: 在此添加控件通知处理程序代码
	
	// 停止处理
}

void ClaserDlg::OnBnClickedBtnQuit()
{
	// TODO: 在此添加控件通知处理程序代

	//导出到Excel
	//AccessToExcel();
	OnClose();
	// 退出操作
	OnCancel();
}

void ClaserDlg::OnBnClickedBtnUser()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
 
	m_IOListDlg.ShowWindow(SW_SHOW);
	//m_IOListDlg.DoModal();
	io_sign = 1;
}

void ClaserDlg::OnBnClickedBtnYes()  //显示数据到界面上
{
	// TODO: 在此添加控件通知处理程序代码
	CString    sSql;
	CString    strName;
	int        CurIndex = m_CurIndex;
	CDStrs     FInfo;
	CStringArray items;

	GetDlgItem(IDC_COMBO_PRO)->GetWindowText(strName);

	sSql.Format("Select * from LaserPara where 产品型号 = '%s'",strName);
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

		//导出参数版本到控件中
		GetDlgItem(IDC_EDIT_CPZJ)->SetWindowText(items.GetAt(1));
		GetDlgItem(IDC_EDIT_DATA)->SetWindowText(items.GetAt(2));
		GetDlgItem(IDC_EDIT_AUTOLIV)->SetWindowText(items.GetAt(3));
		GetDlgItem(IDC_EDIT_GYSBM)->SetWindowText(items.GetAt(4));
		GetDlgItem(IDC_EDIT_MOJU)->SetWindowText(items.GetAt(5));
		GetDlgItem(IDC_COMBO_SSKaiG)->SetWindowText(items.GetAt(6));
		GetDlgItem(IDC_COMBO_SSGuangQ)->SetWindowText(items.GetAt(7));
		GetDlgItem(IDC_EDIT_TEMP)->SetWindowText(items.GetAt(8));


		//赋值给para 
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
//	// TODO: 在此添加控件通知处理程序代码
//
//	CString str;
//	if (GetDlgItemText(IDC_BTN_KaiGuan,str),str == "开")
//	{
//		SetDlgItemText(IDC_BTN_KaiGuan,_T("关"));
//		m_Icon_Open.SetIcon(m_hIcon_open);
//		m_Icon_NG.SetIcon(m_hIcon_open);
//	}
//	else 
//	{
//		SetDlgItemText(IDC_BTN_KaiGuan,_T("开"));
//		m_Icon_Open.SetIcon(m_hIcon_close);
//		m_Icon_NG.SetIcon(m_hIcon_close);
//	}
//}

//void ClaserDlg::OnBnClickedBtnDabiao()
//{
//	// TODO: 在此添加控件通知处理程序代码
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
//		MessageBox("请选择参数！");
//		return;
//	}
//
//	str = "OPEN,file,"+para.m_VISFile+"\r";
//	send_str(str);
//
//	//1修改产品件数
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[0],para.m_ChanPJH);
//	int n = DaBiaoList[4];
//	send_str(str);
//
//	//2修改AUTOLIV
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[1],para.m_AUTOLIV);
//	send_str(str);
//
//	//3修改客户编码
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[2],para.m_CustomNo);
//	send_str(str);
//
//	//4修改认证信息
//	//str.Format("MODIFY,field,%d,para.m_CertifiType\r",DaBiaoList[3]);
//	//send_str(str);
//
//	//5修改车类型
//	//str.Format("MODIFY,field,%d,para.m_CarTyle\r",DaBiaoList[4]);
//	//send_str(str);
//
//	//6修改logoNo
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[5],para.m_LogoNo);
//	send_str(str);
//
//	//7修改品牌号
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[6],para.m_PinPaiNo);
//	send_str(str);
//
//	//8修改防错孔
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[7],para.m_FangCuoK);
//	send_str(str);
//
//	//9修改工厂编号
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[8],para.m_GongChanNo);
//	send_str(str);
//
//	//10修改二维码
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[9],para.m_NHANo);
//	send_str(str);
//
//	//11修改组件号
//	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[10],para.m_ComponentNo);
//	send_str(str);
//
//	//12修改模板号
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
	// TODO: 在此添加控件通知处理程序代码
	AccessToExcel();
	ShellExecute(NULL,"print",m_sExcelFile,NULL,NULL,SW_SHOWNORMAL);
}

void ClaserDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//导出到Excel
	AccessToExcel();
	//删除表，关闭数据库
	g_adoDB.Execute("DROP TABLE LaserPara");
	g_adoDB.Close();

	CDialog::OnClose();
}
void ClaserDlg::lasermark()
{
	CString str;
	if (para.m_VISFile == "" && laser_sign == 50)
	{
		MessageBox("请选择参数！");
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
// 			MessageBox("请选择参数！");
// 			laser_sign = 0;
// 			return;
// 		}
		str = "OPEN,file,C:\\marker\\job\\"+para.m_VISFile+"\r";
		send_str(str);

	////1修改产品件数
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[0],para.m_ChanPJH);
	//int n = DaBiaoList[4];
	//send_str(str);

	////2修改AUTOLIV
// 	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[1],para.m_AUTOLIV);
// 	send_str(str);

	////3修改客户编码
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[2],para.m_CustomNo);
//	send_str(str);

	////4修改认证信息
	////str.Format("MODIFY,field,%d,para.m_CertifiType\r",DaBiaoList[3]);
	////send_str(str);

	////5修改车类型
	////str.Format("MODIFY,field,%d,para.m_CarTyle\r",DaBiaoList[4]);
	////send_str(str);

	////6修改logoNo
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[5],para.m_LogoNo);
	//send_str(str);

	////7修改品牌号
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[6],para.m_PinPaiNo);
	//send_str(str);

	////8修改防错孔
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[7],para.m_FangCuoK);
	//send_str(str);

	////9修改工厂编号
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[8],para.m_GongChanNo);
	//send_str(str);

	////10修改二维码

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

	////11修改组件号
	//str.Format("MODIFY,field,%d,%s\r",DaBiaoList[10],para.m_ComponentNo);
	//send_str(str);

	////12修改模板号
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
//		MessageBox("请选择参数！");
		return;
	}
	laser_sign = 50;
	//lasermark();

	// TODO: 在此添加控件通知处理程序代码
 	CString str;
 
 	str = "SET,control,local\r";
 	send_str(str);
 
 	str = "SET,control,host\r";
 	send_str(str);
 
 	if (para.m_VISFile == "")
 	{
 		MessageBox("请选择参数！");
 		return;
 	}
 
 	str = "OPEN,file,C:\\marker\\job\\"+para.m_VISFile+"\r";
 	send_str(str);
// 

	//2修改日期
	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[0],m_strDate);   
	send_str(str);

 	//3修改AUTOLIV
  	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[1],para.m_AUTOLIV);
 	send_str(str);

	//4修改供应商编码
	str.Format("MODIFY,field,%d,%s\r",DaBiaoList[2],para.m_CustomNo);
	send_str(str);

	//5修改二维码
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
	// TODO: 在此处添加消息处理程序代码
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


		if(((I260[1] &0x10)!= 0) || ((I260[1] & 0x20)!=0)) //完成后清除标志位
		{
			I260[0] = I260[0] &0x0F8;
			MessageBox("完成后清除");
		}

		if ((I260[1]&0x04) == 0x04 )  // 0-停止，1-自动
		{
			CString str1;
			M_state = 1;//自动
			I260[0] = I260[0] & 0x0BF;
			if (para.m_VISFile == "")
			{
				if(laser_conf == 0)
				{
					CString str1;
					str1.Format("laser_conf=%d,260[1]=%x",laser_conf,I260[1]);
	//				MessageBox(str1);
//					MessageBox("请先选择产品参数！");
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
				edit1_str = edit1_str+m_strDateTime +" 报警 H260.00-模具比对NG！"+"\r\n";
			if((H260[0] & 0x02) !=0 && (alarm[0]&0x02)==0)
				edit1_str =  edit1_str + m_strDateTime +" 报警 H260.01-未检测到锁舌！" + "\r\n";
			if((H260[0] & 0x04) !=0 && (alarm[0] &0x04)==0)
				edit1_str = edit1_str + m_strDateTime +" 报警 H260.03-空压源欠压！" + "\r\n";
			if ((H260[0] & 0x10) !=0 && (alarm[0] & 0x10)==0)
				edit1_str = edit1_str + m_strDateTime +" 报警 H260.04-急停！"+"\r\n";
			if((H260[0] & 0x20) !=0 && (alarm[0] &0x20)==0)
				edit1_str = edit1_str + m_strDateTime +" 报警 H260.05-后门被打开！"+"\r\n";
			if((H260[0] & 0x40) !=0 && (alarm[0]&0x40)==0)
				edit1_str = edit1_str + m_strDateTime +" 报警 H260.06-丢红桶失败！" +"\r\n";
			if ((H260[0] & 0x80) !=0 && (alarm[0] &0x80) ==0)
				edit1_str = edit1_str + m_strDateTime +" 报警 H260.07-设备不在原点！"+"\r\n";
			if ((H260[1] & 0x04) !=0 && (alarm[1]&0x04)==0)
				edit1_str = edit1_str  + m_strDateTime +" 报警 H260.10-安全光幕报警！" + "\r\n";		
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
	// TODO: 在此处添加消息处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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