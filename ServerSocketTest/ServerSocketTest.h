
// ServerSocketTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CServerSocketTestApp: 
// �йش����ʵ�֣������ ServerSocketTest.cpp
//

class CServerSocketTestApp : public CWinApp
{
public:
	CServerSocketTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CServerSocketTestApp theApp;