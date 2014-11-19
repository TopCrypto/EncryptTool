#pragma once


// CBase64Dlg dialog

class CBase64Dlg : public CDialog
{
	DECLARE_DYNAMIC(CBase64Dlg)

public:
	CBase64Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBase64Dlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_BASE64 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
    void base64_encode(const unsigned char *input, int len, unsigned char *output);
    int base64_decode(const unsigned char *input, int len, unsigned char *output);
   
};
