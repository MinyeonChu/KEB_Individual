
// VideoProjectDlg.h: ��� ����
//

#pragma once

#include "ServerDlg.h"
#include "ClientDlg.h"

// CVideoProjectDlg ��ȭ ����
class CVideoProjectDlg : public CDialog
{
private:
	BOOL m_bInitial;
	BOOL Initialize(BOOL fInitialize);

	CRect m_re_XY;
	CRect m_re_XY_Svr;
	CRect m_re_XY_Cnt;
	void MoveCtrl(BOOL bCreate = FALSE);

public:
	BOOL ACCEPT(SOCKET sdAccept);
	void SendMpgDatSrc(AVS_PACKET* pAVS_dat);

private:
	CServerDlg m_dlgSvr;
	CClientDlg m_dlgCnt;

private:
	CStatic m_Server_stc;
	CStatic m_Client_stc;

	// �����Դϴ�.
public:
	CVideoProjectDlg(CWnd* pParent = nullptr);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEOPROJECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;
	HICON m_hIcon2;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
