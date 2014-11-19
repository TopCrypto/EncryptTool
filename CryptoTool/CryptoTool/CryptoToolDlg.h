// CryptoToolDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "HashDlg.h"
#include "RSADlg.h"
#include "Base64Dlg.h"
#include "RC4Dlg.h"


// CCryptoToolDlg 对话框
class CCryptoToolDlg : public CDialog
{
// 构造
public:
	CCryptoToolDlg(CWnd* pParent = NULL);	// 标准构造函数

    CHashDlg m_Hash;
	CRSADlg  m_Rsa;
	CBase64Dlg m_Base64;
	CRC4Dlg m_RC4;

// 对话框数据
	enum { IDD = IDD_CRYPTOTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
