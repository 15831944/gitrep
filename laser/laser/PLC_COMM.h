#pragma once


// PLC_COMM �Ի���

class PLC_COMM : public CDialog
{
	DECLARE_DYNAMIC(PLC_COMM)

public:
	PLC_COMM(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PLC_COMM();

// �Ի�������
	enum { IDD = IDD_LASER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm_PLC();
};
