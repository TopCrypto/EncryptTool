// RSADlg.cpp : implementation file
//

#include "stdafx.h"
#include "CryptoTool.h"
#include "RSADlg.h"
#include "tool.h"
#include "rsa.h"

// CRSADlg dialog

IMPLEMENT_DYNAMIC(CRSADlg, CDialog)

CRSADlg::CRSADlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRSADlg::IDD, pParent)
	, m_rsa_e(_T("00010001"))
	, m_rsa_n(_T("C4F8E9E15DCADF2B96C763D981006A644FFB4415030A16ED1283883340F2AA0E2BE2BE8FA60150B9046965837C3E7D151B7DE237EBB957C20663898250703B3F"))
	, m_rsa_d(_T("8a7e79f3fbfea8ebfd18351cb9979136f705b4d9114a06d4aa2fd1943816677a5374661846a30c45b30a024b4d22b15ab323622b2de47ba29115f06ee42c41"))
	, m_rsa_data(_T(""))
	, m_rsa_enc(_T(""))
	, m_rsa_dec(_T(""))
{

}

CRSADlg::~CRSADlg()
{
}

void CRSADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_rsa_e);
	DDX_Text(pDX, IDC_EDIT2, m_rsa_n);
	DDX_Text(pDX, IDC_EDIT3, m_rsa_d);
	DDX_Text(pDX, IDC_EDIT4, m_rsa_data);
	DDX_Text(pDX, IDC_EDIT5, m_rsa_enc);
	DDX_Text(pDX, IDC_EDIT6, m_rsa_dec);
}


BEGIN_MESSAGE_MAP(CRSADlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, &CRSADlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CRSADlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CRSADlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &CRSADlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRSADlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CRSADlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CRSADlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CRSADlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CRSADlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CRSADlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CRSADlg::OnEnChangeEdit6)
END_MESSAGE_MAP()


// CRSADlg message handlers

void CRSADlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_EDIT1, "");
	SetDlgItemText(IDC_EDIT2, "");
	SetDlgItemText(IDC_EDIT3, "");

}

void CRSADlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
     SetDlgItemText(IDC_EDIT4, "");
}

void CRSADlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	   SetDlgItemText(IDC_EDIT5, "");
	   SetDlgItemText(IDC_EDIT6, "");
}

void CRSADlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	int exeponent_len;
	int modulus_len;
	int e_len, n_len, data_len;
	unsigned char *exponent;
	unsigned char *modulus;
	unsigned char *data;
	rsa_key  public_key;


	UpdateData(TRUE);
	data_len = m_rsa_data.GetLength() / 2;
	e_len = m_rsa_e.GetLength() / 2;
    n_len = m_rsa_n.GetLength() / 2;
	UpdateData(FALSE);

    if(e_len == 0 || m_rsa_e.GetLength() % 2 == 1 || n_len == 0 || m_rsa_n.GetLength() % 2 == 1)
	{
		MessageBox(_T("输入公钥数据格式有误，不能为空，输入长度字节必须为整数"));
		return;

	}

	if(data_len == 0 ||  m_rsa_data.GetLength() % 2 == 1)
	{
		MessageBox(_T("输入数据格式有误，不能为空，输入长度字节必须为整数"));
		return;
	}






	data = (unsigned char *)malloc(data_len);
	HexCharsToStdChars((PBYTE)m_rsa_data.GetBuffer(m_rsa_data.GetLength()), data, data_len);


	public_key.modulus = ( huge * ) malloc( sizeof( huge ) );
	public_key.exponent = ( huge * ) malloc( sizeof( huge ) );

	UpdateData(TRUE);
	modulus_len = m_rsa_n.GetLength()/2;
	exeponent_len = m_rsa_e.GetLength()/2;
	UpdateData(FALSE);


	modulus = (unsigned char *)malloc(modulus_len);
	exponent = (unsigned char *)malloc(exeponent_len);

	HexCharsToStdChars((PBYTE)m_rsa_n.GetBuffer(m_rsa_n.GetLength()), modulus, modulus_len);
	HexCharsToStdChars((PBYTE)m_rsa_e.GetBuffer(m_rsa_e.GetLength()),exponent, exeponent_len);


	unsigned char *encrypted;
	int encrypted_len;

	load_huge(public_key.modulus, modulus, modulus_len);
	load_huge(public_key.exponent, exponent, exeponent_len);

	encrypted_len = rsa_encrypt(data, data_len, &encrypted, &public_key);

	CString cstmp, csEncrypt;
	char tmp[256];

	for(int j = 0; j < encrypted_len; j++)
	{
		sprintf(tmp, "%02X", encrypted[j]);
		cstmp=(CString)tmp;
		csEncrypt += cstmp;
	}
	SetDlgItemText(IDC_EDIT5, csEncrypt);


	free(encrypted);
	free(data);
	free(modulus);
	free(exponent);


}

void CRSADlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	int exeponent_len;
	int modulus_len;
	int n_len, d_len, data_len;
	unsigned char *exponent;
	unsigned char *modulus;
	unsigned char *data;
	rsa_key private_key;



	UpdateData(TRUE);
	data_len = m_rsa_data.GetLength() / 2;
	d_len = m_rsa_e.GetLength() / 2;
	n_len = m_rsa_n.GetLength() / 2;
	UpdateData(FALSE);

	if(d_len == 0 || m_rsa_d.GetLength() % 2 == 1 || n_len == 0 || m_rsa_n.GetLength() % 2 == 1)
	{
		MessageBox(_T("输入私钥数据格式有误，不能为空，输入长度字节必须为整数"));
		return;

	}

	if(data_len == 0 ||  m_rsa_data.GetLength() % 2 == 1 || m_rsa_data.GetLength() != m_rsa_n.GetLength())
	{
		MessageBox(_T("输入数据格式有误，不能为空，且必须为16进制表示"));
		return;
	}

	data = (unsigned char *)malloc(data_len);
	HexCharsToStdChars((PBYTE)m_rsa_data.GetBuffer(m_rsa_data.GetLength()), data, data_len);


	private_key.modulus = ( huge * ) malloc( sizeof( huge ) );
	private_key.exponent = ( huge * ) malloc( sizeof( huge ) );

	UpdateData(TRUE);
	modulus_len = m_rsa_n.GetLength()/2;
	exeponent_len = m_rsa_d.GetLength()/2;
	UpdateData(FALSE);


	modulus = (unsigned char *)malloc(modulus_len);
	exponent = (unsigned char *)malloc(exeponent_len);

	HexCharsToStdChars((PBYTE)m_rsa_n.GetBuffer(m_rsa_n.GetLength()), modulus, modulus_len);
	HexCharsToStdChars((PBYTE)m_rsa_d.GetBuffer(m_rsa_d.GetLength()),exponent, exeponent_len);


	unsigned char *decrypted;
	int decrypted_len;

	load_huge(private_key.modulus, modulus, modulus_len);
	load_huge(private_key.exponent, exponent, exeponent_len);

	decrypted_len = rsa_decrypt(data, data_len, &decrypted, &private_key);

	CString cstmp, csDecrypt;
	char tmp[256];

	for(int j = 0; j < decrypted_len; j++)
	{
		sprintf(tmp, "%02X", decrypted[j]);
		cstmp=(CString)tmp;
		csDecrypt += cstmp;
	}
	SetDlgItemText(IDC_EDIT6, csDecrypt);


	free(decrypted);
	free(data);
	free(modulus);
	free(exponent);

}

void CRSADlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	UpdateData(TRUE);
	dlen = m_rsa_e.GetLength() / 2.0;
	UpdateData(FALSE);

	CString strnum;
	if( m_rsa_e.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);
	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT7, strnum);
	UpdateData(FALSE);



}

void CRSADlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	UpdateData(TRUE);
	dlen = m_rsa_n.GetLength() / 2.0;
	UpdateData(FALSE);

	CString strnum;
	if( m_rsa_n.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);
	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT8, strnum);
	UpdateData(FALSE);




}

void CRSADlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	UpdateData(TRUE);
	dlen = m_rsa_d.GetLength() / 2.0;
	UpdateData(FALSE);

	CString strnum;
	if( m_rsa_d.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);
	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT9, strnum);
	UpdateData(FALSE);





}

void CRSADlg::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	UpdateData(TRUE);
	dlen = m_rsa_data.GetLength() / 2.0;
	UpdateData(FALSE);

	CString strnum;
	if( m_rsa_data.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);
	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT10, strnum);
	UpdateData(FALSE);




}

void CRSADlg::OnEnChangeEdit5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	UpdateData(TRUE);
	dlen = m_rsa_enc.GetLength() / 2.0;
	UpdateData(FALSE);

	CString strnum;
	if( m_rsa_enc.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);
	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT11, strnum);
	UpdateData(FALSE);



}

void CRSADlg::OnEnChangeEdit6()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	UpdateData(TRUE);
	dlen = m_rsa_dec.GetLength() / 2.0;
	UpdateData(FALSE);

	CString strnum;
	if( m_rsa_dec.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);
	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT12, strnum);
	UpdateData(FALSE);

}

BOOL CRSADlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
    OnEnChangeEdit1();
	OnEnChangeEdit2();
	OnEnChangeEdit3();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
