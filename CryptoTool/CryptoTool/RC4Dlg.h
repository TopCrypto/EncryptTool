#pragma once
#include "afxwin.h"


// CRC4Dlg dialog

class CRC4Dlg : public CDialog
{
	DECLARE_DYNAMIC(CRC4Dlg)

public:
	CRC4Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRC4Dlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_RC4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	void AscToHex(char*pIn, char*pOut);
	void HexToAsc(char*pIn, int nLen, char*pOut);
	CEdit m_PlainText;
	CEdit m_Key;
	CEdit m_CipherText;
	CEdit m_DecryptText;
};
