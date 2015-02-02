// laser.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "laser.h"
#include "laserDlg.h"
#include <io.h>
#include <odbcinst.h>
#include <afxdb.h>

#include "ADODB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL  b_EXIT;

CAdoDB  g_adoDB;
// ClaserApp

BEGIN_MESSAGE_MAP(ClaserApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// ClaserApp 构造

ClaserApp::ClaserApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 ClaserApp 对象

ClaserApp theApp;


// ClaserApp 初始化

BOOL ClaserApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 连接数据库
	//char  HostName[128];
	//CString StrName;
	//if( gethostname(HostName, sizeof(HostName)) == 0 )
	//{
	//	struct hostent * pHost;
	//	pHost = gethostbyname(HostName);
	//	StrName += HostName;
	//}
	CString sql;
	sql = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=LaserData.mdb";
	if (!g_adoDB.Open(sql,adModeUnknown))
		return -1;


	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	///////////////////////
	//if (CoInitialize(NULL)!=0) 
	//{ 
	//	AfxMessageBox(_T("初始化COM支持库失败!")); 
	//	exit(1); 
	//}
	///////////////////////

	ClaserDlg dlg;

	//管理员或操作员登陆
	b_EXIT = TRUE;
	m_UseDlg.DoModal();


	if (b_EXIT == TRUE)
	{
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: 在此放置处理何时用
			//  “确定”来关闭对话框的代码
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: 在此放置处理何时用
			//  “取消”来关闭对话框的代码
		}
	}


	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////
//名称：GetExcelDriver
//功能：获取ODBC中Excel驱动
/////////////////////////////////////////////////////////////////////////////
CString GetExcelDriver()
{
	char szBuf[2001];
	WORD cbBufMax = 2000;
	WORD cbBufOut;
	char *pszBuf = szBuf;
	CString sDriver;

	// 获取已安装驱动的名称(涵数在odbcinst.h里)
	if (!SQLGetInstalledDrivers(szBuf, cbBufMax, &cbBufOut))
		return "";

	// 检索已安装的驱动是否有Excel...
	do
	{
		if (strstr(pszBuf, "Excel") != 0)
		{
			//发现 !
			sDriver = CString(pszBuf);
			break;
		}
		pszBuf = strchr(pszBuf, '\0') + 1;
	}
	while (pszBuf[1] != '\0');

	return sDriver;
}

///////////////////////////////////////////////////////////////////////////////
//	BOOL MakeSurePathExists( CString &Path,bool FilenameIncluded)
//	参数：
//		Path				路径
//		FilenameIncluded	路径是否包含文件名
//	返回值:
//		文件是否存在
//	说明:
//		判断Path文件(FilenameIncluded=true)是否存在,存在返回TURE，不存在返回FALSE
//		自动创建目录
//
///////////////////////////////////////////////////////////////////////////////
BOOL MakeSurePathExists( CString &Path,
						bool FilenameIncluded)
{
	int Pos=0;
	while((Pos=Path.Find('\\',Pos+1))!=-1)
		CreateDirectory(Path.Left(Pos),NULL);
	if(!FilenameIncluded)
		CreateDirectory(Path,NULL);
	//	return ((!FilenameIncluded)?!_access(Path,0):
	//	!_access(Path.Left(Path.ReverseFind('\\')),0));

	return !_access(Path,0);
}

//获得默认的文件名
BOOL GetDefaultXlsFileName(CString& sExcelFile)
{
	///默认文件名：yyyymmddhhmmss.xls
	CString timeStr;
	CTime day;
	day=CTime::GetCurrentTime();
	int filenameday,filenamemonth,filenameyear,filehour,filemin,filesec;
	filenameday=day.GetDay();//dd
	filenamemonth=day.GetMonth();//mm月份
	filenameyear=day.GetYear();//yyyy
	filehour=day.GetHour();//hh
	filemin=day.GetMinute();//mm分钟
	filesec=day.GetSecond();//ss
	timeStr.Format("%04d%02d%02d%02d%02d%02d",filenameyear,filenamemonth,filenameday,filehour,filemin,filesec);

	sExcelFile =  timeStr + ".xls";
	// prompt the user (with all document templates)
	CFileDialog dlgFile(FALSE,".xls",sExcelFile);
	CString title;
	CString strFilter;

	title = "导出";
	strFilter = "Excel文件(*.xls)";
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += _T("*.xls");
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.nMaxCustFilter++;
	dlgFile.m_ofn.nFilterIndex = 1;
	// append the "*.*" all files filter
	CString allFilter;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += _T("*.*");
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.nMaxCustFilter++;

	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;

	if (dlgFile.DoModal()==IDCANCEL)
		return FALSE; // open cancelled
	sExcelFile.ReleaseBuffer();
	if (MakeSurePathExists(sExcelFile,true)) {
		if(!DeleteFile(sExcelFile)) {    // delete the file
			AfxMessageBox("覆盖文件时出错！");
			return FALSE;
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//	void GetExcelDriver(CListCtrl* pList, CString strTitle)
//	参数：
//		pList		需要导出的List控件指针
//		strTitle	导出的数据表标题
//	说明:
//		导出CListCtrl控件的全部数据到Excel文件。Excel文件名由用户通过“另存为”
//		对话框输入指定。创建名为strTitle的工作表，将List控件内的所有数据（包括
//		列名和数据项）以文本的形式保存到Excel工作表中。保持行列关系。
//	
//	edit by [r]@dotlive.cnblogs.com
///////////////////////////////////////////////////////////////////////////////
void ExportListToExcel(CListCtrl* pList, CString strTitle)
{
	CString warningStr;
	if (pList->GetItemCount()>0) 
	{	
		CDatabase database;
		CString sDriver;
		CString sExcelFile; 
		CString sSql;
		CString tableName = strTitle;

		// 检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)" 
		sDriver = GetExcelDriver();
		if (sDriver.IsEmpty())
		{
			// 没有发现Excel驱动
			AfxMessageBox("没有安装Excel!\n请先安装Excel软件才能使用导出功能!");
			return;
		}

		///默认文件名
		if (!GetDefaultXlsFileName(sExcelFile))
			return;

		// 创建进行存取的字符串
		sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, sExcelFile, sExcelFile);

		// 创建数据库 (既Excel表格文件)
		if( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
		{
			// 创建表结构
			int i;
			LVCOLUMN columnData;
			CString columnName;
			int columnNum = 0;
			CString strH;
			CString strV;

			sSql = "";
			strH = "";
			columnData.mask = LVCF_TEXT;
			columnData.cchTextMax =100;
			columnData.pszText = columnName.GetBuffer (100);
			for(i=0;pList->GetColumn(i,&columnData);i++)
			{
				if (i!=0)
				{
					sSql = sSql + ", " ;
					strH = strH + ", " ;
				}
				sSql = sSql + " " + columnData.pszText +" TEXT";
				strH = strH + " " + columnData.pszText +" ";
			}
			columnName.ReleaseBuffer ();
			columnNum = i;

			sSql = "CREATE TABLE " + tableName + " ( " + sSql +  " ) ";
			database.ExecuteSQL(sSql);

			// 插入数据项
			int nItemIndex;
			for (nItemIndex=0;nItemIndex<pList->GetItemCount ();nItemIndex++){
				strV = "";
				for(i=0;i<columnNum;i++)
				{
					if (i!=0)
					{
						strV = strV + ", " ;
					}
					strV = strV + " '" + pList->GetItemText(nItemIndex,i) +"' ";
				}

				sSql = "INSERT INTO "+ tableName 
					+" ("+ strH + ")"
					+" VALUES("+ strV + ")";
				database.ExecuteSQL(sSql);
			}

		}      

		// 关闭数据库
		database.Close();

		warningStr.Format("导出文件保存于%s!",sExcelFile);
		AfxMessageBox(warningStr);
	}
}

///////////////////////////////

//记录信息到Excel

///////////////////////////////
void InPortToExcel(CListCtrl* pList, CString strTitle)
{
	CString warningStr;
	if (pList->GetItemCount ()>0) {	
		CDatabase database;
		CString sDriver;
		CString sExcelFile; 
		CString sSql;
		CString tableName = strTitle;

		// 检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)" 
		sDriver = GetExcelDriver();
		if (sDriver.IsEmpty())
		{
			// 没有发现Excel驱动
			AfxMessageBox("没有安装Excel!\n请先安装Excel软件才能使用导出功能!");
			return;
		}

		///默认文件名
		if (!GetDefaultXlsFileName(sExcelFile))
			return;

		// 创建进行存取的字符串
		sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, sExcelFile, sExcelFile);

		// 创建数据库 (既Excel表格文件)
		if( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
		{
			// 创建表结构
			int i;
			LVCOLUMN columnData;
			CString columnName;
			int columnNum = 0;
			CString strH;
			CString strV;

			sSql = "";
			strH = "";
			columnData.mask = LVCF_TEXT;
			columnData.cchTextMax =100;
			columnData.pszText = columnName.GetBuffer (100);
			for(i=0;pList->GetColumn(i,&columnData);i++)
			{
				if (i!=0)
				{
					sSql = sSql + ", " ;
					strH = strH + ", " ;
				}
				sSql = sSql + " " + columnData.pszText +" TEXT";
				strH = strH + " " + columnData.pszText +" ";
			}
			columnName.ReleaseBuffer ();
			columnNum = i;

			sSql = "CREATE TABLE " + tableName + " ( " + sSql +  " ) ";
			database.ExecuteSQL(sSql);

			// 插入数据项
			int nItemIndex;
			for (nItemIndex=0;nItemIndex<pList->GetItemCount ();nItemIndex++){
				strV = "";
				for(i=0;i<columnNum;i++)
				{
					if (i!=0)
					{
						strV = strV + ", " ;
					}
					strV = strV + " '" + pList->GetItemText(nItemIndex,i) +"' ";
				}

				sSql = "INSERT INTO "+ tableName 
					+" ("+ strH + ")"
					+" VALUES("+ strV + ")";
				database.ExecuteSQL(sSql);
			}

		}      

		// 关闭数据库
		database.Close();

		warningStr.Format("导出文件保存于%s!",sExcelFile);
		AfxMessageBox(warningStr);
	}
}