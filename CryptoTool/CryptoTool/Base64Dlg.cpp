// Base64Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "CryptoTool.h"
#include "Base64Dlg.h"
#include <assert.h>

static char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";  //base64的编码表
static int unbase64[] =
{
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
	52,53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, 0, -1, -1,
	-1,0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1,
	26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
	42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1, -1
}; 



// CBase64Dlg dialog

IMPLEMENT_DYNAMIC(CBase64Dlg, CDialog)

CBase64Dlg::CBase64Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBase64Dlg::IDD, pParent)
{

}

CBase64Dlg::~CBase64Dlg()
{
}

void CBase64Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBase64Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CBase64Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBase64Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CBase64Dlg message handlers

void CBase64Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString csInput;
    GetDlgItemText(IDC_EDIT1, csInput);
	
	int input_len;
    input_len = csInput.GetLength();
   
	unsigned char *input;
	input = (unsigned char *)malloc(input_len);
	memcpy(input, csInput, input_len);

    unsigned char *output;
	output = (unsigned char *)malloc((input_len/3 + 1) * 5);

	base64_encode((const unsigned char *)input, input_len, output);
    
    CString csOutput;
	csOutput = (CString)output;
	SetDlgItemText(IDC_EDIT2, csOutput);

	free(input);
	free(output);
}

void CBase64Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CString csOutput;
	GetDlgItemText(IDC_EDIT2, csOutput);

	int output_len;
	output_len = csOutput.GetLength();

	unsigned char *output;
	output = (unsigned char *)malloc(output_len + 1);
	memset(output, '\0',output_len + 1);
	memcpy(output, csOutput, output_len);

	unsigned char *input;
	input = (unsigned char *)malloc(output_len);
	memset(input, '\0', output_len);

	base64_decode((const unsigned char *)output, output_len, input);

	CString csInput;
	csInput = (CString)input;
	SetDlgItemText(IDC_EDIT1, csInput);

	free(input);
	free(output);


}


/*在电子邮件中,根据RFC822规定，每76个字符，还需要加上一个换行。*/


void CBase64Dlg::base64_encode( const unsigned char *input, int len, unsigned char *output )
{  
	do
	{
		*output++ = base64[ ( input[ 0 ] & 0xFC ) >> 2 ]; // 取第一字节左移两位

		if ( len == 1 )
		{
			*output++ = base64[ ( ( input[ 0 ] & 0x03 ) << 4 ) ]; // 如果长度为1，则后面2bit做第二个编码同时，补上两个= 号
			*output++ = '=';
			*output++ = '=';
			break;
		}

		*output++ = base64[                             //继续编码第二个字节
			( ( input[ 0 ] & 0x03 ) << 4 ) | ( ( input[ 1 ] & 0xF0 ) >> 4 ) ];

			if ( len == 2 )                                 //若果长度为2后面不补上一个=
			{
				*output++ = base64[ ( ( input[ 1 ] & 0x0F ) << 2 ) ];
				*output++ = '=';
				break;
			}

			*output++ = base64[
				( ( input[ 1 ] & 0x0F ) << 2 ) | ( ( input[ 2 ] & 0xC0 ) >> 6 ) ]; //第一字节的后4位和第二字节的后6位合并得第3个编码
				*output++ = base64[ ( input[ 2 ] & 0x3F ) ];  //第三字节最后6位作为编码4
				input += 3;
	}
	while ( len -= 3 );

	*output = '\0';
}



int CBase64Dlg:: base64_decode( const unsigned char *input, int len, unsigned char *output )
{
	int out_len = 0, i; 
	assert( !( len & 0x03 ) ); // Is an even multiple of 4

	do
	{

		//每4个字符检查一下，它的合法性。
		for ( i = 0; i <= 3; i++ )
		{
			// Check for illegal base64 characters
			if ( input[ i ] > 128 || unbase64[ input[ i ] ] == -1 )
			{
				return -1;
			}
		}
		*output++ = unbase64[ input[ 0 ] ] << 2 |
			( unbase64[ input[ 1 ] ] & 0x30 ) >> 4;   // 得到第一字节的数
		out_len++;
		if ( input[ 2 ] != '=' )
		{
			*output++ = ( unbase64[ input[ 1 ] ] & 0x0F ) << 4 |
				( unbase64[ input[ 2 ] ] & 0x3C ) >> 2;        //得到第二字节
			out_len++;
		}

		if ( input[ 3 ] != '=' )
		{
			*output++ = ( unbase64[ input[ 2 ] ] & 0x03 ) << 6 |  //得到第三字节
				unbase64[ input[ 3 ] ];
			out_len++;
		} 
		input += 4;
	}
	while ( len -= 4 ); 
	return out_len;
} 
