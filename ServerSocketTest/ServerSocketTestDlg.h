
// ServerSocketTestDlg.h : 头文件
//

#pragma once
#include "ServerSocket.h"
#include "resource.h"
#include "ClientSocket.h"
class CServerSocket;

// CServerSocketTestDlg 对话框
class CServerSocketTestDlg : public CDialogEx
{
// 构造
public:
	CServerSocketTestDlg(CWnd* pParent = NULL);	// 标准构造函数
	void acceptConnection();
	CString m_netState;
	CServerSocket m_serverSocket;
	CClientSocket m_clientSocket;
	CString m_hostIP;
	CString m_clientIP;
	CFont m_font;
	int m_port;


// 对话框数据
	enum { IDD = IDD_SERVERSOCKETTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStartlisten();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
