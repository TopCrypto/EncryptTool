#pragma once
#include "afxwin.h"
#include "tool.h"
#include "ASN1/asn1.h"
#define LTM_DESC

#include "tomcrypt.h"
#include "tommath.h"
#pragma comment(lib, "tommath.lib")
#pragma comment(lib, "tomcrypt.lib")

// CRSADlg dialog

typedef enum
{
   eASYMKEY_ALG_1024 = 0,
   eASYMKEY_ALG_2048 = 1,
   eASYMKEY_ALG_4096 = 2,
}eASYMKEY_ALG;

typedef struct{
    int index;
	CString strName;
}stuListBox;

#define MAX_LIST 10
const stuListBox g_AsyAlgList[MAX_LIST]=
{
	{eASYMKEY_ALG_1024, _T("  1024")},
	{eASYMKEY_ALG_2048, _T("  2048")},
	{eASYMKEY_ALG_4096, _T("  4096")},
};


class CRSADlg : public CDialog
{
	DECLARE_DYNAMIC(CRSADlg)

public:
	CRSADlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRSADlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_RSA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnGenrsakey();
	afx_msg void OnBnClickedBtnPublickeyencrypt();
	afx_msg void OnBnClickedBtnPrivatekeydecrypt();
	afx_msg void OnBnClickedBtnPrivatekeysign();
	afx_msg void OnBnClickedBtnPublickeyverify();
	virtual BOOL OnInitDialog();

	CComboBox m_ListBox;
	afx_msg void OnCbnSelchangeComboRsalength();
	CString m_e;
	CString m_e_n;
	afx_msg void OnEnChangeEditN();
	afx_msg void OnEnChangeEditD();
	afx_msg void OnEnChangeEditP();
	afx_msg void OnEnChangeEditQ();
	afx_msg void OnEnChangeEditDp();
	afx_msg void OnEnChangeEditDq();
	afx_msg void OnEnChangeEditQinv();
	afx_msg void OnEnChangeEditData();
	afx_msg void OnEnChangeEditOut();
	void Encode(rsa_key key);
	CEdit m_edit_E;
	CEdit m_edit_N;
	CEdit m_edit_D;
	CEdit m_edit_P;
	CEdit m_edit_Q;
	CEdit m_edit_DP;
	CEdit m_edit_DQ;
	CEdit m_edit_Qinv;
	CEdit m_edit_Data;
	CEdit m_edit_Out;
};
