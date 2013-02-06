#ifndef _screen_form_h_
#define _screen_form_h_
#include "stdafx.h"
#include <atlimage.h>

class MainForm;


//��������
class ScreenForm : public CWindowImpl<ScreenForm>
{
public:
	ScreenForm() : is_lbutton_down(false){}
protected:
	BEGIN_MSG_MAP(ScreenForm)
		MSG_WM_CREATE(OnCreate)
		MESSAGE_HANDLER(WM_KEYDOWN,OnKeyDown)
		MSG_WM_RBUTTONDOWN(OnRButtonDown)
		MSG_WM_SETCURSOR(OnSetCursor)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)
		MSG_WM_PAINT(OnPaint)
	END_MSG_MAP()
protected:
	int OnCreate(LPCREATESTRUCT)
	{
		CRect rc(0,0,0,0);
		SetWindowPos(HWND_TOPMOST,&rc,SWP_NOMOVE|SWP_NOSIZE);	//�ö�
		return 0;
	}
	LRESULT OnKeyDown(UINT,WPARAM wp,LPARAM,BOOL&)
	{
		if(wp == VK_LWIN || wp == VK_RWIN || VK_ESCAPE)	//��WIN + ��WIN + ESC
			OnRButtonDown(0,CPoint(0,0));
		return 0;
	}
	void OnRButtonDown(UINT nFlags, CPoint point);
	//{
	//	DestroyWindow();
	//	mf_ptr->ShowWindow(SW_SHOW);
	//}
	BOOL OnSetCursor(CWindow wnd, UINT nHitTest, UINT message)
	{
		static CCursor cursor = AtlLoadCursor(IDC_CURSOR1);  //��������Դ��ʮ ����״
		::SetCursor(cursor);
		return TRUE;
	}
	void OnLButtonDown(UINT nFlags, CPoint point)
	{
		is_lbutton_down = true;
		pt_old = point;
	}
	void OnMouseMove(UINT nFlags, CPoint point)
	{
		pt_end = point;
		Invalidate();	
	}
	void OnLButtonUp(UINT nFlags, CPoint point)
	{
		extern CBitmap bmp_srcreen;	//��������ȫ��ͼƬ
		is_lbutton_down = false;
		int ret = MessageBox("���Ƶ�������(OK)�򱣴�ΪPNGͼƬ(CANCEL)��","ASK",MB_OKCANCEL|MB_ICONQUESTION);

		CDC dc1,dc2;
		dc1.CreateCompatibleDC(NULL);
		dc1.SelectBitmap(bmp_srcreen);
		CRect rc(pt_old.x,pt_old.y,pt_end.x,pt_end.y);
		dc2.CreateCompatibleDC(dc1);
		CBitmap bmp;	//dc1ѡ����ȫ��ͼƬ��dc2ѡ���˽�ͼ����
		bmp.CreateCompatibleBitmap(dc1,rc.Width(),rc.Height());
		dc2.SelectBitmap(bmp);
		dc2.BitBlt(0,0,rc.Width(),rc.Height(),dc1,pt_old.x,pt_old.y,SRCCOPY);
		if(ret == IDOK)
		{
			if(OpenClipboard())	//���Ƶ�������
			{
				::EmptyClipboard();
				::SetClipboardData(CF_BITMAP,bmp);
				::CloseClipboard();
			}
		}
		else
		{
			CImage img;
			img.Attach(bmp);
			img.Save("catch.png");	//����Ϊpng����Ϊ����ΪbmpͼƬ̫����
			img.Detach();
		}

		OnRButtonDown(0,CPoint(0,0));
	}
	BOOL OnEraseBkgnd(CDCHandle dc)
	{		
		return TRUE;
	}
	void OnPaint(CDCHandle)
	{
		extern CBitmap bmp_srcreen;	//��������ȫ��ͼƬ

		CPaintDC dc(m_hWnd);

		CRect rc;
		GetClientRect(&rc);

		CMemoryDC mem(dc,rc);	//WTL�ṩ��˫���棬����ʱ�Զ�����

		CBrush br;
		br.CreateSolidBrush(RGB(255,255,255));

		mem.FillRect(&rc,br);	//�Ѵ��ڵ�ɫˢ��

		if(bmp_srcreen.IsNull())
			return;

		CDC dcMem;
		dcMem.CreateCompatibleDC(mem);
		dcMem.SelectBitmap(bmp_srcreen);

		BLENDFUNCTION bf;
		bf.AlphaFormat = 0;
		bf.BlendFlags = 0;
		bf.BlendOp = AC_SRC_OVER;
		bf.SourceConstantAlpha = 100;
		//���ư�͸����ȫ��ͼ������win7�Դ��Ľ�ͼ���
		mem.AlphaBlend(0,0,rc.Width(),rc.Height(),dcMem,0,0,rc.Width(),rc.Height(),bf);

		if(is_lbutton_down)
		{
			CRect rc_catch(pt_old.x,pt_old.y,pt_end.x,pt_end.y);
			//��͸������ʾѡ������ͼ��
			mem.BitBlt(pt_old.x,pt_old.y,rc_catch.Width(),rc_catch.Height(),dcMem,pt_old.x,pt_old.y,SRCCOPY);
			mem.Draw3dRect(&rc_catch,RGB(255,0,0),RGB(0,0,255));
		}
	}
private:
	CPoint pt_old;
	CPoint pt_end;
	bool is_lbutton_down;	
};

#endif