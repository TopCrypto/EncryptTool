// RSADlg.cpp : implementation file
//
#include "stdafx.h"
#include "CryptoTool.h"
#include "RSADlg.h"


int hash_idx, prng_idx;
int g_AsyAlgList_Index = 0;
int err, padding, rsa_byte_len;

// CRSADlg dialog

IMPLEMENT_DYNAMIC(CRSADlg, CDialog)

CRSADlg::CRSADlg(CWnd* pParent /*=NULL*/)
    : CDialog(CRSADlg::IDD, pParent)
	, m_e(_T("010001"))
	, m_e_n(_T("3"))
{

}

CRSADlg::~CRSADlg()
{
}

void CRSADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_RSALength, m_ListBox);
	DDX_Text(pDX, IDC_EDIT_e, m_e);
	DDX_Text(pDX, IDC_EDIT_E_Num, m_e_n);
	DDX_Control(pDX, IDC_EDIT_e, m_edit_E);
	DDX_Control(pDX, IDC_EDIT_N, m_edit_N);
	DDX_Control(pDX, IDC_EDIT_D, m_edit_D);
	DDX_Control(pDX, IDC_EDIT_P, m_edit_P);
	DDX_Control(pDX, IDC_EDIT_Q, m_edit_Q);
	DDX_Control(pDX, IDC_EDIT_DP, m_edit_DP);
	DDX_Control(pDX, IDC_EDIT_DQ, m_edit_DQ);
	DDX_Control(pDX, IDC_EDIT_Qinv, m_edit_Qinv);
	DDX_Control(pDX, IDC_EDIT_Data, m_edit_Data);
	DDX_Control(pDX, IDC_EDIT_Out, m_edit_Out);
}


BEGIN_MESSAGE_MAP(CRSADlg, CDialog)
    ON_BN_CLICKED(IDC_BTN_GenRsaKey, &CRSADlg::OnBnClickedBtnGenrsakey)
    ON_BN_CLICKED(IDC_BTN_PublicKeyEncrypt, &CRSADlg::OnBnClickedBtnPublickeyencrypt)
    ON_BN_CLICKED(IDC_BTN_PrivateKeyDecrypt, &CRSADlg::OnBnClickedBtnPrivatekeydecrypt)
    ON_BN_CLICKED(IDC_BTN_PrivateKeySign, &CRSADlg::OnBnClickedBtnPrivatekeysign)
    ON_BN_CLICKED(IDC_BTN_PublicKeyVerify, &CRSADlg::OnBnClickedBtnPublickeyverify)
    ON_CBN_SELCHANGE(IDC_COMBO_RSALength, &CRSADlg::OnCbnSelchangeComboRsalength)
	ON_EN_CHANGE(IDC_EDIT_N, &CRSADlg::OnEnChangeEditN)
	ON_EN_CHANGE(IDC_EDIT_D, &CRSADlg::OnEnChangeEditD)
	ON_EN_CHANGE(IDC_EDIT_P, &CRSADlg::OnEnChangeEditP)
	ON_EN_CHANGE(IDC_EDIT_Q, &CRSADlg::OnEnChangeEditQ)
	ON_EN_CHANGE(IDC_EDIT_DP, &CRSADlg::OnEnChangeEditDp)
	ON_EN_CHANGE(IDC_EDIT_DQ, &CRSADlg::OnEnChangeEditDq)
	ON_EN_CHANGE(IDC_EDIT_Qinv, &CRSADlg::OnEnChangeEditQinv)
	ON_EN_CHANGE(IDC_EDIT_Data, &CRSADlg::OnEnChangeEditData)
	ON_EN_CHANGE(IDC_EDIT_Out, &CRSADlg::OnEnChangeEditOut)
END_MESSAGE_MAP()

void CRSADlg::OnBnClickedBtnGenrsakey()
{
    // TODO: Add your control notification handler code here
    rsa_key  key;
    unsigned char outRSA[4096];
    unsigned long outlenRSA = 4096;

    padding = LTC_PKCS_1_V1_5;

    switch(g_AsyAlgList_Index)
    {
    case eASYMKEY_ALG_1024:
        rsa_byte_len = 1024 / 8;
        break;
    case eASYMKEY_ALG_2048:
        rsa_byte_len = 2048 / 8;
        break;
    case eASYMKEY_ALG_4096:
        rsa_byte_len = 4096 / 8;
        break;
    default:
        break;
    }

    /* make an RSA-1024 key */
    if ((err = rsa_make_key(NULL, /* PRNG state */
                            prng_idx, /* PRNG idx */
                            rsa_byte_len, /*key byte length*/
                            65537, /* we like e=65537 */
                            &key) /* where to store the key */
        ) != CRYPT_OK)
    {
        printf("rsa_make_key %s", error_to_string(err));
    }

    if ((err = rsa_export((unsigned char*)outRSA, &outlenRSA, PK_PRIVATE, &key)) != CRYPT_OK)
    {
        printf("Export error: %s", error_to_string(err));

        outlenRSA = 0;
    }

     //unsigned char *tmp;
	 //int len = 0;
	 //len = mp_unsigned_bin_size((mp_int *)key.N);
	 //tmp = (unsigned char *) malloc(len);
	 //mp_to_unsigned_bin((mp_int *)key.N, tmp);


	 //   unsigned char *msg;
	 //// N
	 //   msg = (unsigned char *) malloc(2*len+1);
	 //   *(msg+(2*len)) = '\0';
	 //   StdCharsToHexChars(tmp, msg, len);
	 //   SetDlgItemText(IDC_EDIT_N, (LPCTSTR)msg);
	 //   if(msg != NULL)
	 //{
	 //	free(msg);
	 //	msg = NULL;
	 //}



    struct asn1struct certificate;
    struct RsaKeyBlob ExportKey;
    memset(&ExportKey, 0, sizeof(RsaKeyBlob));

    asn1parse(outRSA, outlenRSA, &certificate);
    ExportKey.m_IndexCount = 0;
    ans1GetKey(0, &certificate, &ExportKey);
    asn1free( &certificate );

    unsigned long len = ExportKey.m_ulKeyBits;
    unsigned char *msg;
	// N
    msg = (unsigned char *) malloc(2*len+1);
    *(msg+(2*len)) = '\0';
    StdCharsToHexChars(ExportKey.m_N, msg, len);
    SetDlgItemText(IDC_EDIT_N, (LPCTSTR)msg);
    if(msg != NULL)
	{
		free(msg);
		msg = NULL;
	}
    
	//D
	len = ExportKey.m_ulKeyBits;
	msg = (unsigned char *) malloc(2*len+1);
	*(msg+(2*len)) = '\0';
	StdCharsToHexChars(ExportKey.m_D, msg, len);
	SetDlgItemText(IDC_EDIT_D, (LPCTSTR)msg);
	if(msg != NULL)
	{
		free(msg);
		msg = NULL;
	}


    //P
	len = ExportKey.m_ulKeyBits / 2;
	msg = (unsigned char *) malloc(2*len+1);
	*(msg+(2*len)) = '\0';
	StdCharsToHexChars(ExportKey.m_p, msg, len);
	SetDlgItemText(IDC_EDIT_P, (LPCTSTR)msg);
	if(msg != NULL)
	{
		free(msg);
		msg = NULL;
	}

    // Q
    len = ExportKey.m_ulKeyBits / 2;
	msg = (unsigned char *) malloc(2*len+1);
	*(msg+(2*len)) = '\0';
	StdCharsToHexChars(ExportKey.m_q, msg, len);
	SetDlgItemText(IDC_EDIT_Q, (LPCTSTR)msg);
	if(msg != NULL)
	{
		free(msg);
		msg = NULL;
	}

	// DP
    len = ExportKey.m_ulKeyBits / 2;
	msg = (unsigned char *) malloc(2*len+1);
	*(msg+(2*len)) = '\0';
	StdCharsToHexChars(ExportKey.m_dp, msg, len);
	SetDlgItemText(IDC_EDIT_DP, (LPCTSTR)msg);
	if(msg != NULL)
	{
		free(msg);
		msg = NULL;
	}

    // DQ
	len = ExportKey.m_ulKeyBits / 2;
	msg = (unsigned char *) malloc(2*len+1);
	*(msg+(2*len)) = '\0';
	StdCharsToHexChars(ExportKey.m_dq, msg, len);
	SetDlgItemText(IDC_EDIT_DQ, (LPCTSTR)msg);
	if(msg != NULL)
	{
		free(msg);
		msg = NULL;
	}

	// Qinv
	len = ExportKey.m_ulKeyBits / 2;
	msg = (unsigned char *) malloc(2*len+1);
	*(msg+(2*len)) = '\0';
	StdCharsToHexChars(ExportKey.m_qinv, msg, len);
	SetDlgItemText(IDC_EDIT_Qinv, (LPCTSTR)msg);
	if(msg != NULL)
	{
		free(msg);
		msg = NULL;
	}
	
}

void CRSADlg::Encode(rsa_key  key)
{

  CString str;
  int tmp;
  RsaKeyBlob expkey;
  
  memset(&expkey, 0, sizeof(expkey));

  //N
  UpdateData(TRUE);
  GetDlgItemText(IDC_EDIT_N, str);
  UpdateData(FALSE);
  tmp = str.GetLength();
  if(tmp == 0 || tmp %2 != 0)
  {
	  MessageBox(" 密钥格式有误");
	  return;
  }

  UpdateData(TRUE);
  HexCharsToStdChars((PBYTE)str.GetBuffer(str.GetLength()), expkey.m_N, tmp/2);
  UpdateData(FALSE);

  //e 
  UpdateData(TRUE);
  GetDlgItemText(IDC_EDIT_e, str);
  UpdateData(FALSE);
  tmp = str.GetLength();
  if(tmp == 0 || tmp %2 != 0)
  {
	  MessageBox(" 密钥格式有误");
	  return;
  }

  UpdateData(TRUE);
  HexCharsToStdChars((PBYTE)str.GetBuffer(str.GetLength()), expkey.m_E, tmp/2);
  UpdateData(FALSE);


  //D
  UpdateData(TRUE);
  GetDlgItemText(IDC_EDIT_D, str);
  UpdateData(FALSE);
  tmp = str.GetLength();
  if(tmp == 0 || tmp %2 != 0)
  {
	  MessageBox(" 密钥格式有误");
	  return;
  }

  UpdateData(TRUE);
  HexCharsToStdChars((PBYTE)str.GetBuffer(str.GetLength()), expkey.m_D, tmp/2);
  UpdateData(FALSE);


  //p
  UpdateData(TRUE);
  GetDlgItemText(IDC_EDIT_P, str);
  UpdateData(FALSE);
  tmp = str.GetLength();
  if(tmp == 0 || tmp %2 != 0)
  {
	  MessageBox(" 密钥格式有误");
	  return;
  }

  UpdateData(TRUE);
  HexCharsToStdChars((PBYTE)str.GetBuffer(str.GetLength()), expkey.m_p, tmp/2);
  UpdateData(FALSE);


  //Q
  UpdateData(TRUE);
  GetDlgItemText(IDC_EDIT_Q, str);
  UpdateData(FALSE);
  tmp = str.GetLength();
  if(tmp == 0 || tmp %2 != 0)
  {
	  MessageBox(" 密钥格式有误");
	  return;
  }

  UpdateData(TRUE);
  HexCharsToStdChars((PBYTE)str.GetBuffer(str.GetLength()), expkey.m_q, tmp/2);
  UpdateData(FALSE);


  //dp
  UpdateData(TRUE);
  GetDlgItemText(IDC_EDIT_DP, str);
  UpdateData(FALSE);
  tmp = str.GetLength();
  if(tmp == 0 || tmp %2 != 0)
  {
	  MessageBox(" 密钥格式有误");
	  return;
  }

  UpdateData(TRUE);
  HexCharsToStdChars((PBYTE)str.GetBuffer(str.GetLength()), expkey.m_dp, tmp/2);
  UpdateData(FALSE);


  //dq
  UpdateData(TRUE);
  GetDlgItemText(IDC_EDIT_DQ, str);
  UpdateData(FALSE);
  tmp = str.GetLength();
  if(tmp == 0 || tmp %2 != 0)
  {
	  MessageBox(" 密钥格式有误");
	  return;
  }

  UpdateData(TRUE);
  HexCharsToStdChars((PBYTE)str.GetBuffer(str.GetLength()), expkey.m_dq, tmp/2);
  UpdateData(FALSE);


  // Qinv
  UpdateData(TRUE);
  GetDlgItemText(IDC_EDIT_Qinv, str);
  UpdateData(FALSE);
  tmp = str.GetLength();
  if(tmp == 0 || tmp %2 != 0)
  {
	  MessageBox(" 密钥格式有误");
	  return;
  }

  UpdateData(TRUE);
  HexCharsToStdChars((PBYTE)str.GetBuffer(str.GetLength()), expkey.m_qinv, tmp/2);
  UpdateData(FALSE);





}




// 公钥加密
void CRSADlg::OnBnClickedBtnPublickeyencrypt()
{
    // TODO: Add your control notification handler code here
	rsa_key key;
    Encode(key);

}

//私钥解密
void CRSADlg::OnBnClickedBtnPrivatekeydecrypt()
{
    // TODO: Add your control notification handler code here
    //unsigned char * Data;
    //unsigned long DataLen;
    //unsigned char * Out;
    //unsigned long OutLen;
    //rsa_key key;
    //int res;


    //if ((err = rsa_decrypt_key_ex(Data, /* encrypted data */
    //	DataLen, /* length of ciphertext */
    //	Out, /* where to put plaintext */
    //	&OutLen, /* plaintext length */
    //	(unsigned char*)"TestApp", /* lparam for this program */
    //	7, /* lparam is 7 bytes long */
    //	hash_idx, /* hash idx */
    //	padding,
    //	&res, /* validity of data */
    //	&key) /* our RSA key */
    //	) != CRYPT_OK) {
    //		printf("rsa_decrypt_key %s", error_to_string(err));
    //		return EXIT_FAILURE;
    //}

}

void CRSADlg::OnBnClickedBtnPrivatekeysign()
{
    // TODO: Add your control notification handler code here
}

void CRSADlg::OnBnClickedBtnPublickeyverify()
{
    // TODO: Add your control notification handler code here
}


BOOL CRSADlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here

    // 添加list数据
    for(int i = 0; i < MAX_LIST; i++)
    {
        if(!g_AsyAlgList[i].strName.IsEmpty())
        {
            m_ListBox.InsertString(i, g_AsyAlgList[i].strName);
        }
    }

    m_ListBox.SetCurSel(0);
    g_AsyAlgList_Index = g_AsyAlgList[0].index;


    /* register prng/hash */
    if (register_prng(&sprng_desc) == -1)
    {
        MessageBox("Error registering sprng");
    }

    /* register a math library (in this case TomsFastMath)*/
    ltc_mp = ltm_desc;
    if (register_hash(&sha1_desc) == -1)
    {
        MessageBox("Error registering sha1");
    }

    hash_idx = find_hash("sha1");
    prng_idx = find_prng("sprng");

	UpdateData(TRUE);
	m_e = _T("010001");
	m_e_n = _T("3");
	UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void CRSADlg::OnCbnSelchangeComboRsalength()
{
    // TODO: Add your control notification handler code here
    int index = 0, i = 0;
    CString str;
    index = m_ListBox.GetCurSel();
    m_ListBox.GetLBText(index, str);

    for( i = 0; i < MAX_LIST; i++)
    {
        if(str.CompareNoCase(g_AsyAlgList[i].strName)==0)
        {
            g_AsyAlgList_Index = g_AsyAlgList[i].index;
        }

    }

}

void CRSADlg::OnEnChangeEditN()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	CString str, strnum;

	GetDlgItemText(IDC_EDIT_N, str);
	UpdateData(TRUE);
	dlen = str.GetLength() / 2.0;
	UpdateData(FALSE);

	if( str.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);

	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT_N_Num, strnum);
	UpdateData(FALSE);
}

void CRSADlg::OnEnChangeEditD()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	CString str, strnum;
	GetDlgItemText(IDC_EDIT_D, str);
	dlen = str.GetLength() / 2.0;

	if( str.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);
	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT_D_Num, strnum);
	UpdateData(FALSE);
}

void CRSADlg::OnEnChangeEditP()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	CString str, strnum;
	GetDlgItemText(IDC_EDIT_P, str);
	dlen = str.GetLength() / 2.0;

	if( str.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);
	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT_P_Num, strnum);
	UpdateData(FALSE);
}

void CRSADlg::OnEnChangeEditQ()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	CString str, strnum;
	GetDlgItemText(IDC_EDIT_Q, str);
	dlen = str.GetLength() / 2.0;

	if( str.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);
	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT_Q_Num, strnum);
	UpdateData(FALSE);
}

void CRSADlg::OnEnChangeEditDp()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	CString str, strnum;
	GetDlgItemText(IDC_EDIT_DP, str);
	dlen = str.GetLength() / 2.0;

	if( str.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);
	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT_DP_Num, strnum);
	UpdateData(FALSE);
}

void CRSADlg::OnEnChangeEditDq()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	CString str, strnum;
	GetDlgItemText(IDC_EDIT_DQ, str);
	dlen = str.GetLength() / 2.0;

	if( str.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);
	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT_DQ_Num, strnum);
	UpdateData(FALSE);
}

void CRSADlg::OnEnChangeEditQinv()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	CString str, strnum;
	GetDlgItemText(IDC_EDIT_Qinv, str);
	dlen = str.GetLength() / 2.0;

	if( str.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);
	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT_Qinv_Num, strnum);
	UpdateData(FALSE);
}

void CRSADlg::OnEnChangeEditData()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	double dlen;
	CString str, strnum;
	GetDlgItemText(IDC_EDIT_Data, str);
	dlen = str.GetLength() / 2.0;

	if( str.GetLength() % 2 == 0)
	{
		strnum.Format(_T("%.0lf"), dlen);
	}else
	{
		strnum.Format(_T("%.1lf"), dlen);
	}

	UpdateData(TRUE);
	SetDlgItemText(IDC_EDIT_Data_Num, strnum);
	UpdateData(FALSE);
}

void CRSADlg::OnEnChangeEditOut()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
