#pragma once


// CRSADlg dialog

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
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString m_rsa_e;
	CString m_rsa_n;
	CString m_rsa_d;
	CString m_rsa_data;
	CString m_rsa_enc;
	CString m_rsa_dec;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
	virtual BOOL OnInitDialog();
};
