#pragma once


// PLC_COMM 对话框

class PLC_COMM : public CDialog
{
	DECLARE_DYNAMIC(PLC_COMM)

public:
	PLC_COMM(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PLC_COMM();

// 对话框数据
	enum { IDD = IDD_LASER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm_PLC();
};
