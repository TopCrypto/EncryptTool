// CryptoToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "HashDlg.h"
#include "RSADlg.h"
#include "Base64Dlg.h"
#include "RC4Dlg.h"


// CCryptoToolDlg �Ի���
class CCryptoToolDlg : public CDialog
{
// ����
public:
	CCryptoToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

    CHashDlg m_Hash;
	CRSADlg  m_Rsa;
	CBase64Dlg m_Base64;
	CRC4Dlg m_RC4;

// �Ի�������
	enum { IDD = IDD_CRYPTOTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
