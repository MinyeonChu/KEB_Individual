
// VideoProject.h: PROJECT_NAME ���ø����̼ǿ� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
#error "PCH�� ���� �� ������ �����ϱ� ���� 'pch.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CVideoProjectApp:
// �� Ŭ������ ������ ���ؼ��� VideoProject.cpp��(��) �����ϼ���.
//

class CVideoProjectApp : public CWinApp
{
public:
	CVideoProjectApp();

	// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CVideoProjectApp theApp;
