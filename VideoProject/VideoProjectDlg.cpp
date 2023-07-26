
// VideoProjectDlg.cpp: ���� ����
//

#include "pch.h"
#include "framework.h"
#include "VideoProject.h"
#include "VideoProjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVideoProjectDlg ��ȭ ����


CVideoProjectDlg::CVideoProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_VIDEOPROJECT_DIALOG, pParent)
{
	m_hIcon = NULL;
	m_hIcon2 = NULL;

	m_bInitial = FALSE;
}

void CVideoProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_SERVER, m_Server_stc);
	DDX_Control(pDX, IDC_STATIC_CLIENT, m_Client_stc);
}

BEGIN_MESSAGE_MAP(CVideoProjectDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CVideoProjectDlg �޽��� ó����

BOOL CVideoProjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	WORD wversionRequested = MAKEWORD(2, 2);

	WSADATA wsadata;
	if (WSAStartup(wversionRequested, &wsadata) != 0) return FALSE;
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 2) return FALSE;

	if (Initialize(TRUE) == FALSE)
	{
		Initialize(FALSE);
		return FALSE;
	}

	m_bInitial = TRUE;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���ø����̼��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CVideoProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CVideoProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVideoProjectDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	m_bInitial = FALSE;

	Initialize(FALSE);

	WSACleanup();
}

void CVideoProjectDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if (!m_bInitial)
		return;
	if ((nType == SIZE_RESTORED) || (nType == SIZE_MAXIMIZED))
	{
		MoveCtrl();
	}
}

BOOL CVideoProjectDlg::Initialize(BOOL fInitialize)
{
	if (fInitialize)
	{
		WCHAR szPath[MAX_PATH];
		swprintf_s(szPath, L"%s\\VMS.ico", _cmn_IcoPath());
		m_hIcon = (HICON)::LoadImage(NULL, szPath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
		m_hIcon2 = (HICON)::LoadImage(NULL, szPath, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
		SetIcon(m_hIcon, TRUE);
		SetIcon(m_hIcon2, FALSE);

		_lang_Set(ID_Korean);

		WCHAR szLan[64];
		_lang_(IDS_VIDEO_PROJECT, szLan); SetWindowText(szLan);

		if (!_codec_ffmpeg_Init())
			return FALSE;

		MoveCtrl(TRUE);
	}
	else
	{
		m_dlgSvr.DestroyWindow();
		m_dlgCnt.DestroyWindow();

		if (m_hIcon) DestroyIcon(m_hIcon);
		if (m_hIcon2) DestroyIcon(m_hIcon2);

		_codec_ffmpeg_Exit();
	}
	return TRUE;
}

void CVideoProjectDlg::MoveCtrl(BOOL bCreate)
{
	if (!m_bInitial && !bCreate)
		return;

	if (bCreate)
	{
		GetClientRect(&m_re_XY);
		m_Server_stc.GetWindowRect(&m_re_XY_Svr);
		ScreenToClient(&m_re_XY_Svr);
		m_Client_stc.GetWindowRect(&m_re_XY_Cnt);
		ScreenToClient(&m_re_XY_Cnt);
	}
	else
	{
		CRect re;
		GetClientRect(&re);
		int cx = re.Width() - m_re_XY.Width();
		int cy = re.Height() - m_re_XY.Height();

		CRect re_XY_Svr(&m_re_XY_Svr);
		re_XY_Svr.right += cx / 2;
		re_XY_Svr.bottom += cy;
		m_Server_stc.MoveWindow(&re_XY_Svr);

		CRect re_XY_Cnt(&m_re_XY_Cnt);
		re_XY_Cnt.OffsetRect(cx / 2, 0);
		re_XY_Cnt.right += cx / 2;
		re_XY_Cnt.bottom += cy;
		m_Client_stc.MoveWindow(&re_XY_Cnt);
	}

	if (bCreate)
	{
		if (m_dlgSvr.Create(this))
		{
			m_dlgSvr.ShowWindow(SW_SHOW);
		}
		if (m_dlgCnt.Create(this))
		{
			m_dlgCnt.ShowWindow(SW_SHOW);
		}
	}

	CRect re_Svr;
	m_Server_stc.GetWindowRect(&re_Svr);
	ScreenToClient(&re_Svr);
	re_Svr.DeflateRect(5, 5);
	m_dlgSvr.MoveWindow(&re_Svr);

	CRect re_Cnt;
	m_Client_stc.GetWindowRect(&re_Cnt);
	ScreenToClient(&re_Cnt);
	re_Cnt.DeflateRect(5, 5);
	m_dlgCnt.MoveWindow(&re_Cnt);

	Invalidate(FALSE);
}

BOOL CVideoProjectDlg::ACCEPT(SOCKET sdAccept)
{
	if (m_dlgCnt.ACCEPT(sdAccept))
		return TRUE;
	return FALSE;
}
void CVideoProjectDlg::SendMpgDatSrc(AVS_PACKET* pAVS_dat)
{
	m_dlgCnt.SendMpgDatSrc(pAVS_dat);
}
