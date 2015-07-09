
// ServerSocketTestDlg.h : ͷ�ļ�
//

#pragma once
#include "ServerSocket.h"
#include "resource.h"
#include "ClientSocket.h"
class CServerSocket;

// CServerSocketTestDlg �Ի���
class CServerSocketTestDlg : public CDialogEx
{
// ����
public:
	CServerSocketTestDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void acceptConnection();
	CString m_netState;
	CServerSocket m_serverSocket;
	CClientSocket m_clientSocket;
	CString m_hostIP;
	CString m_clientIP;
	CFont m_font;
	int m_port;


// �Ի�������
	enum { IDD = IDD_SERVERSOCKETTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStartlisten();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
