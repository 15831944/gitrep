// laser.cpp : ����Ӧ�ó��������Ϊ��
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


// ClaserApp ����

ClaserApp::ClaserApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� ClaserApp ����

ClaserApp theApp;


// ClaserApp ��ʼ��

BOOL ClaserApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// �������ݿ�
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


	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	///////////////////////
	//if (CoInitialize(NULL)!=0) 
	//{ 
	//	AfxMessageBox(_T("��ʼ��COM֧�ֿ�ʧ��!")); 
	//	exit(1); 
	//}
	///////////////////////

	ClaserDlg dlg;

	//����Ա�����Ա��½
	b_EXIT = TRUE;
	m_UseDlg.DoModal();


	if (b_EXIT == TRUE)
	{
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: �ڴ˷��ô����ʱ��
			//  ��ȷ�������رնԻ���Ĵ���
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: �ڴ˷��ô����ʱ��
			//  ��ȡ�������رնԻ���Ĵ���
		}
	}


	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////
//���ƣ�GetExcelDriver
//���ܣ���ȡODBC��Excel����
/////////////////////////////////////////////////////////////////////////////
CString GetExcelDriver()
{
	char szBuf[2001];
	WORD cbBufMax = 2000;
	WORD cbBufOut;
	char *pszBuf = szBuf;
	CString sDriver;

	// ��ȡ�Ѱ�װ����������(������odbcinst.h��)
	if (!SQLGetInstalledDrivers(szBuf, cbBufMax, &cbBufOut))
		return "";

	// �����Ѱ�װ�������Ƿ���Excel...
	do
	{
		if (strstr(pszBuf, "Excel") != 0)
		{
			//���� !
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
//	������
//		Path				·��
//		FilenameIncluded	·���Ƿ�����ļ���
//	����ֵ:
//		�ļ��Ƿ����
//	˵��:
//		�ж�Path�ļ�(FilenameIncluded=true)�Ƿ����,���ڷ���TURE�������ڷ���FALSE
//		�Զ�����Ŀ¼
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

//���Ĭ�ϵ��ļ���
BOOL GetDefaultXlsFileName(CString& sExcelFile)
{
	///Ĭ���ļ�����yyyymmddhhmmss.xls
	CString timeStr;
	CTime day;
	day=CTime::GetCurrentTime();
	int filenameday,filenamemonth,filenameyear,filehour,filemin,filesec;
	filenameday=day.GetDay();//dd
	filenamemonth=day.GetMonth();//mm�·�
	filenameyear=day.GetYear();//yyyy
	filehour=day.GetHour();//hh
	filemin=day.GetMinute();//mm����
	filesec=day.GetSecond();//ss
	timeStr.Format("%04d%02d%02d%02d%02d%02d",filenameyear,filenamemonth,filenameday,filehour,filemin,filesec);

	sExcelFile =  timeStr + ".xls";
	// prompt the user (with all document templates)
	CFileDialog dlgFile(FALSE,".xls",sExcelFile);
	CString title;
	CString strFilter;

	title = "����";
	strFilter = "Excel�ļ�(*.xls)";
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
			AfxMessageBox("�����ļ�ʱ����");
			return FALSE;
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//	void GetExcelDriver(CListCtrl* pList, CString strTitle)
//	������
//		pList		��Ҫ������List�ؼ�ָ��
//		strTitle	���������ݱ����
//	˵��:
//		����CListCtrl�ؼ���ȫ�����ݵ�Excel�ļ���Excel�ļ������û�ͨ�������Ϊ��
//		�Ի�������ָ����������ΪstrTitle�Ĺ�������List�ؼ��ڵ��������ݣ�����
//		��������������ı�����ʽ���浽Excel�������С��������й�ϵ��
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

		// �����Ƿ�װ��Excel���� "Microsoft Excel Driver (*.xls)" 
		sDriver = GetExcelDriver();
		if (sDriver.IsEmpty())
		{
			// û�з���Excel����
			AfxMessageBox("û�а�װExcel!\n���Ȱ�װExcel�������ʹ�õ�������!");
			return;
		}

		///Ĭ���ļ���
		if (!GetDefaultXlsFileName(sExcelFile))
			return;

		// �������д�ȡ���ַ���
		sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, sExcelFile, sExcelFile);

		// �������ݿ� (��Excel����ļ�)
		if( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
		{
			// ������ṹ
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

			// ����������
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

		// �ر����ݿ�
		database.Close();

		warningStr.Format("�����ļ�������%s!",sExcelFile);
		AfxMessageBox(warningStr);
	}
}

///////////////////////////////

//��¼��Ϣ��Excel

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

		// �����Ƿ�װ��Excel���� "Microsoft Excel Driver (*.xls)" 
		sDriver = GetExcelDriver();
		if (sDriver.IsEmpty())
		{
			// û�з���Excel����
			AfxMessageBox("û�а�װExcel!\n���Ȱ�װExcel�������ʹ�õ�������!");
			return;
		}

		///Ĭ���ļ���
		if (!GetDefaultXlsFileName(sExcelFile))
			return;

		// �������д�ȡ���ַ���
		sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, sExcelFile, sExcelFile);

		// �������ݿ� (��Excel����ļ�)
		if( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
		{
			// ������ṹ
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

			// ����������
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

		// �ر����ݿ�
		database.Close();

		warningStr.Format("�����ļ�������%s!",sExcelFile);
		AfxMessageBox(warningStr);
	}
}