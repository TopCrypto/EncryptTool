#pragma once
#include "afxwin.h"


// CHashDlg dialog

class CHashDlg : public CDialog
{
	DECLARE_DYNAMIC(CHashDlg)

public:
	CHashDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHashDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_HASH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	CEdit m_input;
	CEdit m_output;
};
