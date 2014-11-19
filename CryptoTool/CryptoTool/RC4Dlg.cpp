// RC4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "CryptoTool.h"
#include "RC4Dlg.h"


// CRC4Dlg dialog

IMPLEMENT_DYNAMIC(CRC4Dlg, CDialog)

CRC4Dlg::CRC4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRC4Dlg::IDD, pParent)
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
}


BEGIN_MESSAGE_MAP(CRC4Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CRC4Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRC4Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CRC4Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CRC4Dlg message handlers



static void rc4_operate(const unsigned char *plaintext, int plaintext_len, unsigned char *ciphertext, const unsigned char *key, int key_len)
{
	int i, j;
	unsigned char S[256];
	unsigned char tmp;
	for(i = 0; i < 256; i++)
		S[i] = i;

	j = 0; 
	for(i = 0; i < 256; i++)
	{
		j = (j + S[i] + key[i % key_len]) % 256;
		tmp = S[i];
		S[i] = S[j];
		S[j] =tmp;
	}

	i = 0;
	j = 0;

	while(plaintext_len--)
	{
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		tmp = S[i];
		S[i] = S[j];
		S[j] = tmp;
		*(ciphertext++) = *(plaintext++) ^S[(S[i] + S[j]) % 256];
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
   char *pOutData;
   int input_len;
   int key_len;
   
   CString str;
   GetDlgItemText(IDC_EDIT1, str);
   input_len = str.GetLength();
   pData = (unsigned char *)malloc(input_len);
   memcpy(pData, str, str.GetLength());

	GetDlgItemText(IDC_EDIT2, str);
	key_len = str.GetLength();
	key = (unsigned char *)malloc(key_len);
	memcpy(key, str, key_len);

    pOutData = (char *)malloc(input_len+1);
	memset(pOutData, '\0', input_len+1);

	rc4_operate((const unsigned char *)pData, input_len, (unsigned char *)pOutData, (const unsigned char *)key, key_len);
	SetDlgItemText(IDC_EDIT3, pOutData);

    free(pData);
	free(key);
	free(pOutData);



}

void CRC4Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	unsigned char *pData;
	char *pOutData;
	unsigned char *key;
    
	int input_len;
	int key_len;

    CString str;
	GetDlgItemText(IDC_EDIT3, str);
	input_len = str.GetLength();
	pData = (unsigned char *)malloc(input_len);
	memcpy(pData, str, input_len);
	
	GetDlgItemText(IDC_EDIT2, str);
	key_len = str.GetLength();
	key = (unsigned char *)malloc(key_len);
	memcpy(key, str, key_len);


    pOutData = (char *)malloc(input_len+1);
	memset(pOutData, '\0', input_len+1);

	rc4_operate((const unsigned char *)pData, input_len, (unsigned char *)pOutData, (const unsigned char *)key, key_len);
	SetDlgItemText(IDC_EDIT4, pOutData);
    
	free(pData);
	free(pOutData);
	free(key);
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
