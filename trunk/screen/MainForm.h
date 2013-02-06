#ifndef _MAIN_FRAME_h_
#define _MAIN_FRAME_h_
#include "stdafx.h"
#include "ScreenForm.h"
//������
class MainForm : public CWindowImpl<MainForm>
{
protected:
	BEGIN_MSG_MAP(MainForm)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)
		COMMAND_CODE_HANDLER(BN_CLICKED,OnClick)
	END_MSG_MAP()
protected:
	void OnClose()
	{
		DestroyWindow();
		::PostMessage(NULL,WM_QUIT,0,0);
	}
	BOOL OnEraseBkgnd(CDCHandle dc)  //�ⲻ����Ϊ�����ڼӸ�����ͼ����
	{
		CRect rc;
		GetClientRect(&rc);
		CBitmap bk;
		bk.LoadBitmap(IDB_BITMAP1);
		CDC mem;
		mem.CreateCompatibleDC(dc);
		mem.SelectBitmap(bk);
		BITMAP bkInf;
		bk.GetBitmap(&bkInf);
		dc.StretchBlt(0,0,rc.Width(),rc.Height(),mem,0,0,bkInf.bmWidth,bkInf.bmHeight,SRCCOPY);
		return TRUE;
	}
	LRESULT OnClick(WORD,WORD id,HWND,BOOL&)
	{
		CRect rc;
		switch(id)
		{
		case IDC_CREATE :
			ShowWindow(SW_HIDE);
			Sleep(300);		//��Ҫ�ȴ�һ�£�������������ͼ��Ҳ��׽����
			{
				//��׽��Ļ
				CRect rcDesk;
				CWindow wndDesk = ::GetDesktopWindow();
				wndDesk.GetClientRect(&rcDesk);
				rc = rcDesk;
				CDCHandle dcDesk = wndDesk.GetDC();
				CDC dcMem;
				dcMem.CreateCompatibleDC(dcDesk);
				if(bmp_srcreen.IsNull() == FALSE)
					bmp_srcreen.DeleteObject();
				bmp_srcreen.CreateCompatibleBitmap(dcDesk,rcDesk.Width(),rcDesk.Height());
				dcMem.SelectBitmap(bmp_srcreen);
				dcMem.BitBlt(0,0,rcDesk.Width(),rcDesk.Height(),dcDesk,0,0,SRCCOPY);
				wndDesk.ReleaseDC(dcDesk);
			}
			sf.Create(m_hWnd,rc,NULL,WS_VISIBLE|WS_POPUP);
			break;
		default:
			break;
		}
		return 0;
	}
public:
	void InitForm()
	{
		font_btn.CreatePointFont(110,"����");
		// 400 * 300
		btn_create.Create(m_hWnd,CRect(20,10,120,40),"�½�",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,0,IDC_CREATE);
		btn_create.SetFont(font_btn);
	}
private:
	CButton btn_create;		
	CFont font_btn;
	ScreenForm sf;

	enum { IDC_CREATE = 10001 };
};

#endif