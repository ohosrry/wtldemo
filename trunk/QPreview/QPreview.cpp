/************************************************************************
ģ����:		��360��ȫ��ʿ����
����:		��δ��ģ�鹦�ܽ�������
�������:	2010-10-20
����:		��ΰ�� Yang Weifeng(Email: 11259500@qq.com)

�������������ʹ�ã�����ʹ�ñ�������ɵĺ�������˲��е��κ�����
************************************************************************/

#include "stdafx.h"
#include "QPreview.h"

#include "WndPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CQPreview

BEGIN_MESSAGE_MAP(CQPreview, CWinApp)
END_MESSAGE_MAP()


// Ψһ��һ�� CQPreview ����

CQPreview theApp;

// CQPreview ����

CQPreview::CQPreview()
// ��ʹ��������GUID
:m_siSingleInst(_T("{B758ACA3-0D85-4518-B852-722B9460F6F2}"))
{
}

// CQPreview ��ʼ��

BOOL CQPreview::InitInstance()
{
	// �жϽ������Ƿ��Ѿ������б������ʵ��
	BOOL bRunning = !m_siSingleInst.AppStart();
	if(bRunning)
	{
		// ����Ѿ����������Ѿ�����ʵ���������ʵ��
		HWND hMainWnd;
		m_siSingleInst.WaitForInitCompleted(&hMainWnd, sizeof(HWND));

		SendMessage(hMainWnd, WM_SYSCOMMAND,SC_RESTORE ,NULL);
		SetForegroundWindow(hMainWnd);

		return FALSE;
	}
	else
	{
		CWinApp::InitInstance();

		// ��ʼ��GDI+���л���
		GdiplusStartupInput gdiplusStartupInput;
		GdiplusStartup(&m_GdiplusToken, &gdiplusStartupInput, NULL);

		CWnd * pMainWnd = new CWndPreview();

		// ���������ڣ������˳�ʱCDlgMainFrame���Զ��ͷ�
		LPCTSTR lpszClassName=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,
			::LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW)));
		// WS_EX_APPWINDOW�������Ӵ�����ʾ����������
		m_pMainWnd = pMainWnd;
		BOOL bResult = pMainWnd->CreateEx(WS_EX_APPWINDOW, lpszClassName, NULL, 
			WS_POPUP|WS_VISIBLE, 0, 0, 0, 0, NULL, 0);   
		if(!bResult)
		{
			AfxMessageBox(_T("���ڳ�ʼ��ʧ�ܣ�"));
			return FALSE;
		}
		pMainWnd->UpdateWindow();
		pMainWnd->ShowWindow(SW_SHOW);
		// ���浱ǰ���������ڣ��Ա����ʵ�����м���
		HWND hMainWnd = m_pMainWnd->GetSafeHwnd();
		m_siSingleInst.InitCompleted(&hMainWnd, sizeof(hMainWnd));

		return TRUE;
	}
}

int  CQPreview::ExitInstance()
{
	// �ͷŽ�����Դ
	CImageInfo::Instance()->Release();

	// ���� gdi+ ����
	GdiplusShutdown(m_GdiplusToken);

	// �����������Դ
	m_siSingleInst.AppEnd();

	return CWinApp::ExitInstance();
}
