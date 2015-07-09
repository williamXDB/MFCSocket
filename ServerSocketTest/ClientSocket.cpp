#include "stdafx.h"
#include "ClientSocket.h"


CClientSocket::CClientSocket()
{
}


CClientSocket::~CClientSocket()
{
}


void CClientSocket::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);
}