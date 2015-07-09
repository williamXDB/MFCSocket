
// ServerSocketTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServerSocketTest.h"
#include "ServerSocketTestDlg.h"
#include "afxdialogex.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerSocketTestDlg �Ի���



CServerSocketTestDlg::CServerSocketTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerSocketTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerSocketTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_NetState,m_netState);
	DDX_Text(pDX, IDC_Edit_ClientInfo, m_clientIP);
}

BEGIN_MESSAGE_MAP(CServerSocketTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_StartListen, &CServerSocketTestDlg::OnBnClickedButtonStartlisten)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CServerSocketTestDlg ��Ϣ�������

BOOL CServerSocketTestDlg::OnInitDialog()
{
#pragma region
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
#pragma endregion

	char hostName[MAX_PATH];
	memset(hostName, 0, MAX_PATH);
	WSADATA wsData;
	::WSAStartup(MAKEWORD(1,1),&wsData);
	int err = gethostname(hostName,MAX_PATH);
	hostent * phost = gethostbyname(hostName);
	if (phost)
	{
		char * pIP = inet_ntoa(*(in_addr*)phost->h_addr_list[0]);
		m_hostIP = pIP;
	}
	m_port = 6000;
	m_netState.Format(_T("%s%s%s%d"),_T("IP��ַ��"),m_hostIP,_T("  �˿ںţ�"),m_port);
	UpdateData(false);
	m_font.CreatePointFont(150,_T("���Ŀ���"));

	

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_serverSocket.m_pServerSocketDlg = this;


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CServerSocketTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerSocketTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CServerSocketTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerSocketTestDlg::OnBnClickedButtonStartlisten()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_serverSocket.Create(m_port,SOCK_STREAM,m_hostIP);
	m_serverSocket.Listen();
	((CButton*)GetDlgItem(IDC_BUTTON_StartListen))->EnableWindow(false);

}

void CServerSocketTestDlg::acceptConnection()
{
	//MessageBox(_T("��ʼ���ܿͻ�������"));
	CString csClientIP;
	UINT port;
	m_serverSocket.Accept(m_clientSocket);
	m_clientSocket.GetSockName(csClientIP, port);
	
	m_clientIP.Format(_T("�ͻ��˵�ַ��%s �˿ںţ� %d"), csClientIP, port);
	UpdateData(false);
}


HBRUSH CServerSocketTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_Edit_ClientInfo||pWnd->GetDlgCtrlID()==IDC_NetState)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,100,0));
		pDC->SelectObject(&m_font);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
