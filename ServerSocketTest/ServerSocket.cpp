#include "stdafx.h"
#include "ServerSocket.h"

#include "ServerSocketTestDlg.h"

CServerSocket::CServerSocket()
{
}


CServerSocket::~CServerSocket()
{
}


void CServerSocket::OnAccept(int nErrorCode)
{
	m_pServerSocketDlg->acceptConnection();
}