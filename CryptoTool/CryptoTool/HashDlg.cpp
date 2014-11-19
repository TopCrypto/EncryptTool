// HashDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CryptoTool.h"
#include "HashDlg.h"
#include "algorithm_md5.h"
#include "algorithm_sha1.h"
#include "algorithm_crc32.h"


// CHashDlg dialog

IMPLEMENT_DYNAMIC(CHashDlg, CDialog)

CHashDlg::CHashDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHashDlg::IDD, pParent)
{

}

CHashDlg::~CHashDlg()
{
}

void CHashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_input);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_output);
}


BEGIN_MESSAGE_MAP(CHashDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CHashDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHashDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CHashDlg message handlers

void CHashDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	unsigned char * input;
	int len;
	unsigned int hash[MD5_RESULT_SIZE];
	unsigned int hash2[SHA1_RESULT_SIZE];
	unsigned int hash3[CRC32_RESULT_SIZE];
	char tmp[256];

	CString str, str2, strout;
	GetDlgItemText(IDC_EDIT_INPUT,str);
	len = str.GetLength();
	if(len == 0)
	{
		MessageBox(_T("输入不能为空"));
		return;
	}

	input = (unsigned char *)malloc(len);
	memcpy(input, str, len);

	if(((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck() == BST_CHECKED)
	{
		md5_hash(input, len, hash);

		for(int j = 0; j < MD5_RESULT_SIZE; j++)
		{
			sprintf(tmp, "%08X", ((hash[j] & 0xFF000000)>>24 | (hash[j] & 0x00FF0000)>>8 | (hash[j] & 0x0000FF00)<<8 | (hash[j] & 0x000000FF)<<24));
			str2=(CString)tmp;
			strout += str2;
		}

	}else if(((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck() == BST_CHECKED)
	{


		sha1_hash(input, len, hash2);
		for(int j = 0; j < SHA1_RESULT_SIZE; j++)
		{
			sprintf(tmp, "%08X", ((hash2[j] & 0xFF000000)>>24 | (hash2[j] & 0x00FF0000)>>8 | (hash2[j] & 0x0000FF00)<<8 | (hash2[j] & 0x000000FF)<<24));
			str2=(CString)tmp;
			strout += str2;
		}

	}else if(((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck() == BST_CHECKED )
	{

		crc32_hash(input, len, hash3);

		for(int j = 0; j < CRC32_RESULT_SIZE; j++)
		{
			sprintf(tmp, "%08X", hash3[j]);
			str2=(CString)tmp;
			strout += str2;
		}

	}

	SetDlgItemText(IDC_EDIT_OUTPUT, strout);
	free(input);
}

void CHashDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	m_input.SetWindowText(_T(""));
	m_output.SetWindowText(_T(""));
}

BOOL CHashDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

    ((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);//设置为选中 


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
