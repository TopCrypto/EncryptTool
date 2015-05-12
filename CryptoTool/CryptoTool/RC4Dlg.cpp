// RC4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "CryptoTool.h"
#include "RC4Dlg.h"
#include "tool.h"



// CRC4Dlg dialog

IMPLEMENT_DYNAMIC(CRC4Dlg, CDialog)

CRC4Dlg::CRC4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRC4Dlg::IDD, pParent)
	, m_edit1(_T(""))
	, m_edit2(_T(""))
	, m_edit3(_T(""))
	, m_edit4(_T(""))
{

}

CRC4Dlg::~CRC4Dlg()
{
}

void CRC4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_PlainText);
	DDX_Control(pDX, IDC_EDIT2, m_Key);
	DDX_Control(pDX, IDC_EDIT3, m_CipherText);
	DDX_Control(pDX, IDC_EDIT4, m_DecryptText);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDV_MaxChars(pDX, m_edit1, 2147483647);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDV_MaxChars(pDX, m_edit2, 256);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDV_MaxChars(pDX, m_edit3, 2147483647);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
	DDV_MaxChars(pDX, m_edit4, 2147483647);
}


BEGIN_MESSAGE_MAP(CRC4Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CRC4Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRC4Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CRC4Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CRC4Dlg message handlers



static void rc4_operate(BYTE  *plaintext, int plaintext_len, BYTE *ciphertext, BYTE *key, int key_len)
{
	int i, j;
	unsigned char S[256];
	unsigned char tmp;
	for(i = 0; i < 256; i++)
		S[i] = i;

	j = 0; 
	for(i = 0; i < 256; i++)
	{
		j = (j + S[i] + key[i % key_len])&0xFF;
		tmp = S[i];
		S[i] = S[j];
		S[j] =tmp;
	}

	i = 0;
	j = 0;

	while(plaintext_len--)
	{
		i = (i + 1) & 0xFF;
		j = (j + S[i]) & 0xFF;
		tmp = S[i];
		S[i] = S[j];
		S[j] = tmp;
		*(ciphertext++) = *(plaintext++) ^S[(S[i] + S[j]) & 0xFF];
	}

}

void CRC4Dlg::AscToHex(char*pIn, char*pOut)
{
	int hexValue = 0;
	for(int i = 0; i < (int)strlen(pIn); i++)
	{
		hexValue = pIn[i];
		sprintf(pOut + 2*i, "%02X", hexValue);
	}
}

void CRC4Dlg::HexToAsc(char*pIn, int nLen, char*pOut)
{
	if(nLen <= 0 || pIn == NULL || pOut == NULL)
	{
		MessageBox(_T("传入参数有误"));
		return;
	}

	char tmp[2] = {0};
	int intValue = 0;

	for(int i = 0; i < nLen; i++)
	{
		memset(tmp, 0, sizeof(tmp));
		tmp[0] = pIn[2*i];
		tmp[1] = pIn[2*i+1];

		if(tmp[0]>= 'a' && tmp[0] <= 'f')
		{
			intValue = 16 * (tmp[0] - 'a');
		}
		else if(tmp[0] >= 'A' && tmp[0] <= 'F')
		{
			intValue = 16 * (tmp[0] - 'A');
		}
		else if(tmp[0] >= '0' && tmp[0] <= '9')
		{
			intValue = 16 *(tmp[0] - '0');
		}else
		{
			MessageBox("Data is illegal");
			return;
		}

		// 个位数
		if(tmp[1] >= 'a' && tmp[1] <= 'f')
		{
			intValue += (tmp[1] - 'a') + 10;
		}
		else if(tmp[1] >= 'A' && tmp[1] <= 'F')
		{
			intValue += (tmp[1] - 'A') + 10;
		}
		else if(tmp[1] >= '0' && tmp[1] <= '9')
		{
			intValue += (tmp[1] - '0');
		}else
		{
			MessageBox(_T("Data is illegal"));
			return;
		}

		sprintf(&pOut[i], "%c", intValue);
	}

}




void CRC4Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

   unsigned char *pData;
   unsigned char *key;
   unsigned char *msg;
   int keylen;
   int pDatalen;
   int  tmp;
   
  

   CString str;
   GetDlgItemText(IDC_EDIT1, str);
   tmp = str.GetLength();
   if((tmp == 0) ||  (tmp %2 !=0))
   {
	   MessageBox("输入数据为必须是16进制格式");
	   return;
   }
   pDatalen = tmp / 2;
   pData = (unsigned char *)malloc(pDatalen);
   memset(pData, 0, pDatalen);

   UpdateData(TRUE);
   HexCharsToStdChars((PBYTE)m_edit1.GetBuffer(m_edit1.GetLength()), pData, pDatalen);
   UpdateData(FALSE);


	GetDlgItemText(IDC_EDIT2, str);
	tmp = str.GetLength();
	if( (tmp == 0) || (tmp %2 != 0) || (tmp > 512) )
	{
		MessageBox("输入密钥长度为1-256字节之间");
		return;
	}
	keylen = tmp / 2;
	key = (unsigned char *)malloc(keylen);
	memset(key, 0, keylen);
	UpdateData(TRUE);
	HexCharsToStdChars((PBYTE)m_edit2.GetBuffer(m_edit2.GetLength()), key, keylen);
	UpdateData(FALSE);

	rc4_operate(pData, pDatalen, pData, key, keylen);
     
	msg = (unsigned char *) malloc(2*pDatalen+1);
    *(msg+(2*pDatalen)) = '\0';
    StdCharsToHexChars(pData, msg, pDatalen);
    
	SetDlgItemText(IDC_EDIT3, (LPCTSTR)msg);

    free(pData);
	free(key);
	free(msg);
}

void CRC4Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	unsigned char *pData;
	unsigned char *key;
	unsigned char *msg;
	int keylen;
	int pDatalen;
	int  tmp;

	CString str;
	GetDlgItemText(IDC_EDIT3, str);
	tmp = str.GetLength();
	if(tmp == 0 || tmp % 2 != 0)
	{
		MessageBox("输入数据为必须是16进制格式");
		return;
	}
	pDatalen = tmp / 2;
	pData = (unsigned char *)malloc(pDatalen);
	memset(pData, 0, pDatalen);
	UpdateData(TRUE);
	HexCharsToStdChars((PBYTE)m_edit3.GetBuffer(m_edit3.GetLength()), pData, pDatalen);
	UpdateData(FALSE);


	GetDlgItemText(IDC_EDIT2, str);
	tmp = str.GetLength();
	if( (tmp == 0) || (tmp %2 != 0) || (tmp > 512) )
	{
		MessageBox("输入密钥长度为1-256字节之间");
		return;
	}
	keylen = tmp / 2;
	key = (unsigned char *)malloc(keylen);
	memset(key, 0, keylen);
	UpdateData(TRUE);
	HexCharsToStdChars((PBYTE)m_edit2.GetBuffer(m_edit2.GetLength()), key, keylen);
	UpdateData(FALSE);

	rc4_operate(pData, pDatalen, pData, key, keylen);

	msg = (unsigned char *) malloc(2*pDatalen+1);
	*(msg+(2*pDatalen)) = '\0';                     // 此处由于自己将指针位置搞错，导致指向出错。
	StdCharsToHexChars(pData, msg, pDatalen);

	SetDlgItemText(IDC_EDIT4, (LPCTSTR)msg);

	free(pData);
	free(key);
	free(msg);
}

void CRC4Dlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_PlainText.SetWindowText(_T(""));
	m_Key.SetWindowText(_T(""));
	m_CipherText.SetWindowText(_T(""));
	m_DecryptText.SetWindowText(_T(""));
	UpdateData(FALSE);
}
