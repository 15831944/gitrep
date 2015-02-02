#ifndef ADO_DB_H
#define ADO_DB_H

#pragma   warning(disable:4146)
#import "C:\Program Files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#pragma   warning(default:4146)

#pragma warning(disable:4786)

#include <vector>
//����vector����ṹ����һά�ַ�������
typedef ::std::vector<CString> CStrs;
//����vector����ṹ�����ά�ַ�������
typedef ::std::vector<CStrs> CDStrs;


class CAdoDB
{
public:
	CAdoDB();
	virtual ~CAdoDB();
public:
	//���ݿ�����
	BOOL Open(LPCTSTR lpszConnect =_T(""), long lOptions = adConnectUnspecified);
	//���ݿ�ر�
	void Close();
	//�ж����ݿ��Ƿ��ڴ�״̬
	BOOL IsOpen();	
	//�������ݿ�����ָ��
	_ConnectionPtr GetConnection() {return m_pConn;};
	//���ؼ�¼��ָ��
	_RecordsetPtr GetRecordset() {return m_pRs;};
	//���������ַ���
	CString GetConString() {return m_strConn;};
	//ִ��SQL���
	_RecordsetPtr Execute(LPCTSTR strSQL, long lOptions = adCmdText);
    //_variant_t���ݸ�ʽ������ת��Ϊ�ַ�����ʽ
	CString vartostr(_variant_t& var);
	//����SQL����ѯ���ݿ⣬��ȡ�ļ�¼�������ڶ�ά�ַ���������
	BOOL ExecuteQuery(LPCTSTR lpszSQL,CDStrs& Fields);
	//����SQL����ѯ���ݿ⣬��ȡ�ļ�¼��������һά�ַ���������
	BOOL ExecuteQuery(LPCTSTR lpszSQL,CStrs& Fields);
	//����SQL����ѯ���ݿ⣬��ȡһ���ֶ�ֵ
	void ExecuteQueryValue(LPCTSTR lpszSQL,CString& value);
	//��ü�¼����Ŀ
	int GetAdoItemCount(CString sql);
	//��ʼһ������
	bool BeginTrans();
	//�ύһ������
	bool CommitTrans();
	//�ع�һ������
	bool RollbackTrans();



protected:
	//�����ַ���
	CString			m_strConn;
	//���ݿ�����ָ��
	_ConnectionPtr	m_pConn;	
	//��¼��ָ��
	_RecordsetPtr	m_pRs;	
};

#endif