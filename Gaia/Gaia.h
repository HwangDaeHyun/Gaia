
// Gaia.h : Gaia ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include <GdiPlus.h>
using namespace Gdiplus;

// GaiaApp:
// �� Ŭ������ ������ ���ؼ��� Gaia.cpp�� �����Ͻʽÿ�.
//

class GaiaApp : public CWinApp
{
public:
	GaiaApp();
	ULONG_PTR gdiplusToken;

	// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	// �����Դϴ�.
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern GaiaApp theApp;
