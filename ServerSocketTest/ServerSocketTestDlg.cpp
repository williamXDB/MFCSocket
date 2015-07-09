
// ServerSocketTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerSocketTest.h"
#include "ServerSocketTestDlg.h"
#include "afxdialogex.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CServerSocketTestDlg 对话框



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


// CServerSocketTestDlg 消息处理程序

BOOL CServerSocketTestDlg::OnInitDialog()
{
#pragma region
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
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
	m_netState.Format(_T("%s%s%s%d"),_T("IP地址："),m_hostIP,_T("  端口号："),m_port);
	UpdateData(false);
	m_font.CreatePointFont(150,_T("华文楷体"));

	

	// TODO:  在此添加额外的初始化代码
	m_serverSocket.m_pServerSocketDlg = this;


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerSocketTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerSocketTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerSocketTestDlg::OnBnClickedButtonStartlisten()
{
	// TODO:  在此添加控件通知处理程序代码
	m_serverSocket.Create(m_port,SOCK_STREAM,m_hostIP);
	m_serverSocket.Listen();
	((CButton*)GetDlgItem(IDC_BUTTON_StartListen))->EnableWindow(false);

}

void CServerSocketTestDlg::acceptConnection()
{
	//MessageBox(_T("开始接受客户端连接"));
	CString csClientIP;
	UINT port;
	m_serverSocket.Accept(m_clientSocket);
	m_clientSocket.GetSockName(csClientIP, port);
	
	m_clientIP.Format(_T("客户端地址：%s 端口号： %d"), csClientIP, port);
	UpdateData(false);
}


HBRUSH CServerSocketTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_Edit_ClientInfo||pWnd->GetDlgCtrlID()==IDC_NetState)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,100,0));
		pDC->SelectObject(&m_font);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
