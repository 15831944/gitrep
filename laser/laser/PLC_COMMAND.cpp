
#include "stdafx.h"
#include "PLC_COMMAND.h"
#include "laserDlg.h"

ClaserDlg * m_pParent;



void send_str(CString str)
{
	int i, nSize;
	m_pParent = (ClaserDlg*)AfxGetMainWnd();

	//nSize = str.GetLength()*sizeof(TCHAR);
	nSize = str.GetLength();
	CByteArray m_Array;
	m_Array.RemoveAll();
	m_Array.SetSize(nSize);

	for(i=0;i<nSize;i++)
		m_Array.SetAt(i,str.GetAt(i));

	//memcpy(ba.GetData(), str.GetBuffer(), nSize);
	//ba.SetAt(nSize,'\r');
	//ba.SetAt(nSize,13);
	str.ReleaseBuffer();

	m_pParent->MyCOMM.put_Output(COleVariant(m_Array));
}
