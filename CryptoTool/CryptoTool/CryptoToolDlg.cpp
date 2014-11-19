// CryptoToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CryptoTool.h"
#include "CryptoToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCryptoToolDlg 对话框




CCryptoToolDlg::CCryptoToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCryptoToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCryptoToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CCryptoToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CCryptoToolDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CCryptoToolDlg 消息处理程序

BOOL CCryptoToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_Tab.InsertItem(0, "HASH", 0);					//向标签控件中添加选项卡
	m_Tab.InsertItem(1, "RSA", 1);
	m_Tab.InsertItem(2, "BASE64", 2);
	m_Tab.InsertItem(3, "RC4", 3);
	m_Hash.Create(IDD_DIALOG_HASH, &m_Tab);	//创建子窗口
	m_Rsa.Create(IDD_DIALOG_RSA, &m_Tab);
	m_Base64.Create(IDD_DIALOG_BASE64, &m_Tab);
	m_RC4.Create(IDD_DIALOG_RC4, &m_Tab);

	CRect clientRC;
	m_Tab.GetClientRect(clientRC);						//获取标签客户区域
	clientRC.DeflateRect(2, 30, 2, 2);						//减少客户区域大小
	m_Hash.MoveWindow(clientRC);					//移动子窗口
	m_Rsa.MoveWindow(clientRC);					//移动子窗口
	m_Base64.MoveWindow(clientRC);
	m_RC4.MoveWindow(clientRC);
	m_Hash.ShowWindow(SW_SHOW);					//显示子窗口
	m_Tab.SetCurSel(0);								//设置默认选中的标签页



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCryptoToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCryptoToolDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCryptoToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCryptoToolDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_Tab.GetCurSel();					//获取当前选中的标签页索引
	if (nCurSel == 0)								//如果第一个标签页被选中
	{
		m_Hash.ShowWindow(SW_SHOW);			//显示子对话框
		m_Rsa.ShowWindow(SW_HIDE);			//隐藏子对话框
		m_Base64.ShowWindow(SW_HIDE);
		m_RC4.ShowWindow(SW_HIDE);
	}
	else if (nCurSel == 1)							//如果第2个标签页被选中
	{
		m_Rsa.ShowWindow(SW_SHOW);		//显示子对话框
		m_Hash.ShowWindow(SW_HIDE);			//隐藏子对话框
		m_Base64.ShowWindow(SW_HIDE);
		m_RC4.ShowWindow(SW_HIDE);
	}
	else if(nCurSel == 2)
	{   
		m_Base64.ShowWindow(SW_SHOW);
		m_Hash.ShowWindow(SW_HIDE);
		m_Rsa.ShowWindow(SW_HIDE);
		m_RC4.ShowWindow(SW_HIDE);

	}else if(nCurSel == 3)
	{
		m_RC4.ShowWindow(SW_SHOW);
		m_Base64.ShowWindow(SW_HIDE);
		m_Hash.ShowWindow(SW_HIDE);
		m_Rsa.ShowWindow(SW_HIDE);
	}

	*pResult = 0;
}
