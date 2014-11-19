// CryptoToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CryptoTool.h"
#include "CryptoToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCryptoToolDlg �Ի���




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


// CCryptoToolDlg ��Ϣ�������

BOOL CCryptoToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_Tab.InsertItem(0, "HASH", 0);					//���ǩ�ؼ������ѡ�
	m_Tab.InsertItem(1, "RSA", 1);
	m_Tab.InsertItem(2, "BASE64", 2);
	m_Tab.InsertItem(3, "RC4", 3);
	m_Hash.Create(IDD_DIALOG_HASH, &m_Tab);	//�����Ӵ���
	m_Rsa.Create(IDD_DIALOG_RSA, &m_Tab);
	m_Base64.Create(IDD_DIALOG_BASE64, &m_Tab);
	m_RC4.Create(IDD_DIALOG_RC4, &m_Tab);

	CRect clientRC;
	m_Tab.GetClientRect(clientRC);						//��ȡ��ǩ�ͻ�����
	clientRC.DeflateRect(2, 30, 2, 2);						//���ٿͻ������С
	m_Hash.MoveWindow(clientRC);					//�ƶ��Ӵ���
	m_Rsa.MoveWindow(clientRC);					//�ƶ��Ӵ���
	m_Base64.MoveWindow(clientRC);
	m_RC4.MoveWindow(clientRC);
	m_Hash.ShowWindow(SW_SHOW);					//��ʾ�Ӵ���
	m_Tab.SetCurSel(0);								//����Ĭ��ѡ�еı�ǩҳ



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCryptoToolDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCryptoToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCryptoToolDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_Tab.GetCurSel();					//��ȡ��ǰѡ�еı�ǩҳ����
	if (nCurSel == 0)								//�����һ����ǩҳ��ѡ��
	{
		m_Hash.ShowWindow(SW_SHOW);			//��ʾ�ӶԻ���
		m_Rsa.ShowWindow(SW_HIDE);			//�����ӶԻ���
		m_Base64.ShowWindow(SW_HIDE);
		m_RC4.ShowWindow(SW_HIDE);
	}
	else if (nCurSel == 1)							//�����2����ǩҳ��ѡ��
	{
		m_Rsa.ShowWindow(SW_SHOW);		//��ʾ�ӶԻ���
		m_Hash.ShowWindow(SW_HIDE);			//�����ӶԻ���
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
