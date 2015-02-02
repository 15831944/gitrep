// PLC_COMM.cpp : 实现文件
//

#include "stdafx.h"
#include "laser.h"
#include "PLC_COMM.h"


// PLC_COMM 对话框

IMPLEMENT_DYNAMIC(PLC_COMM, CDialog)

PLC_COMM::PLC_COMM(CWnd* pParent /*=NULL*/)
	: CDialog(PLC_COMM::IDD, pParent)
{

}

PLC_COMM::~PLC_COMM()
{
}

void PLC_COMM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PLC_COMM, CDialog)
END_MESSAGE_MAP()


// PLC_COMM 消息处理程序
BEGIN_EVENTSINK_MAP(PLC_COMM, CDialog)
//	ON_EVENT(PLC_COMM, IDC_MSCOMM2, 1, PLC_COMM::OnCommMscomm_PLC, VTS_NONE)
END_EVENTSINK_MAP()

void PLC_COMM::OnCommMscomm_PLC()
{
	// TODO: 在此处添加消息处理程序代码
}
