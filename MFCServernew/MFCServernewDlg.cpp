
// MFCServernewDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCServernew.h"
#include "MFCServernewDlg.h"
#include "afxdialogex.h"
#include"afxsock.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCServernewDlg 对话框



CMFCServernewDlg::CMFCServernewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSERVERNEW_DIALOG, pParent)
	, m_port(0), m_socket(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCServernewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Control(pDX, IDC_BUTTON_START, m_start);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_stop);
	DDX_Control(pDX, IDC_LIST_BOX, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CMFCServernewDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CMFCServernewDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMFCServernewDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CMFCServernewDlg::OnBnClickedButtonClean)
END_MESSAGE_MAP()


// CMFCServernewDlg 消息处理程序

BOOL CMFCServernewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码
	m_port = 8888;// 服务器端口
	m_stop.EnableWindow(FALSE);//将停止服务器摁键灰化
	UpdateData(FALSE); //对话框初始化
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCServernewDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCServernewDlg::OnPaint()
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
HCURSOR CMFCServernewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





// 清空消息列表
void CMFCServernewDlg::OnBnClickedButtonClean()
{
	// TODO: 在此添加控件通知处理程序代码
	m_listCtrl.DeleteAllItems();
	//m_serverSocket.SendMsg(_T("aaaa"));
}

// 启动服务器
void CMFCServernewDlg::OnBnClickedButtonStart()
{
	UpdateData(TRUE);
	BOOL ret = m_socket.Create(m_port, SOCK_STREAM);
	if (ret)
	{

		ret = m_socket.Listen();
		if (ret)
		{
			m_start.EnableWindow(FALSE);
			m_stop.EnableWindow(TRUE);
			return;
		}
		else
		{
			MessageBox(_T("监听套接字监听失败"));
		}
	}
	else
	{
		MessageBox(_T("创建监听套接字失败"));
	}
	m_start.EnableWindow(TRUE);
	m_stop.EnableWindow(FALSE);
}

// 停止服务器
void CMFCServernewDlg::OnBnClickedButtonStop()
{
	m_socket.CloseAllConn();
	m_start.EnableWindow(TRUE);
	m_stop.EnableWindow(FALSE);
}

void CMFCServernewDlg::AddMsg(CString msg)
{
	m_listCtrl.InsertItem(0, msg);
}
