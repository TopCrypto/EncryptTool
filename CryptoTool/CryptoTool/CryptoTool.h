// CryptoTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCryptoToolApp:
// �йش����ʵ�֣������ CryptoTool.cpp
//

class CCryptoToolApp : public CWinApp
{
public:
	CCryptoToolApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCryptoToolApp theApp;