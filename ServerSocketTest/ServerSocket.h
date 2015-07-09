#pragma once
#include "afxsock.h"

class CServerSocketTestDlg;

class CServerSocket :
	public CSocket
{
public:
	CServerSocket();
	~CServerSocket();
	CServerSocketTestDlg * m_pServerSocketDlg;
	virtual void OnAccept(int nErrorCode);
};


