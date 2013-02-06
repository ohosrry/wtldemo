#pragma  once

#include "stdafx.h"
#include "resource.h"
#include "gdiplus.h"
using namespace Gdiplus;
 
#define TITLE_BAR_HEIGHT 100
// typedef CWinTraits<WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE>		CFrameWinTraits;
typedef CWinTraits< WS_CLIPCHILDREN | WS_POPUP|WS_VISIBLE|WS_SYSMENU, WS_EX_WINDOWEDGE>		CMyTraits;
//WS_POPUP|WS_VISIBLE|WS_SYSMENU
class MyWindow : public CWindowImpl<MyWindow,CWindow,CFrameWinTraits>
{
public:
	DECLARE_WND_CLASS("mYwINDOW");

	BEGIN_MSG_MAP(theClass)
		MESSAGE_HANDLER(WM_CREATE,OnCreate)
		MESSAGE_HANDLER(WM_DESTROY,OnDestroy)
		MESSAGE_HANDLER(WM_NCHITTEST,OnNCHitTest)		// ����Ƿ��Ǳ�����
		MESSAGE_HANDLER(WM_NCPAINT,OnNcPaint)			// �ǿͻ��������
		MESSAGE_HANDLER(WM_NCACTIVATE,OnNcActive)		// 
		MESSAGE_HANDLER(WM_NCCALCSIZE,OnNcCalcSize)	//�ı�������Ĵ�С

		//MESSAGE_HANDLER(WM_NCMOUSEMOVE,OnNcMouseMove)	// �������Ƿ�ͣ�������С���رհ�ť
		//CHAIN_MSG_MAP( CWindowImpl< MyWindow > )
	END_MSG_MAP()

	LRESULT OnDestroy(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL&handled)
	{
		PostQuitMessage(1);
		return false;
	}

	LRESULT OnNCHitTest(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL&handled)
	{
		RECT WndRc;
		POINT ptMouse;
		GetWindowRect(&WndRc);
		GetCursorPos(&ptMouse);
		ScreenToClient(&ptMouse);
		if(ptMouse.y <= mHeightCap + mHeightTool)
			return HTCAPTION;
		else
			return HTCLIENT; 
	}

	LRESULT OnNcCalcSize(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL&handled)
	{
		/*
		typedef struct _NCCALCSIZE_PARAMS {
		RECT        rgrc[3]; 
		PWINDOWPOS  lppos; 
		} NCCALCSIZE_PARAMS, *LPNCCALCSIZE_PARAMS;  

		��rgrc
		�������顣
		��һ�����ΰ����������ƶ���ı��С��������꣬Ҳ����˵�����ǽ�����´������ꡣ
		�ڶ������ΰ����˴������ƶ���ı��Сǰ�����ꡣ
		�����������˴����ƶ���ı��Сǰ�Ŀͻ������ꡣ
		����ô������Ӵ��ڣ���Щ��������ڸ����ڵĿͻ�������������Ƕ��㴰�ڣ������������Ļԭ�㡣

		��lppos
		ָ��WINDOWPOS�ṹ��ָ�롣�ýṹ�����˶Դ��ڽ����ƶ���ı��С�Ĳ���ʱָ���Ĵ�С��λ�á� 
		*/
		LPNCCALCSIZE_PARAMS pSizePtr = (LPNCCALCSIZE_PARAMS)lParam;
		//pSizePtr->rgrc[0].
		DoNcPaint();
		return 0;

	}

	LRESULT OnNcPaint(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL&handled)
	{

		DoNcPaint();
		return false;
	}

	LRESULT OnNcActive(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL&handled)
	{
		DoNcPaint();
		return true;
	}
	
	void DoNcPaint()
	{
		RECT rc,rcTitle;
		GetWindowRect(&rc);
		rcTitle.bottom = 0 + TITLE_BAR_HEIGHT;
		rcTitle.left = 0;
		rcTitle.right = 0 + rc.right - rc.left;
		rcTitle.top = 0;
		CWindowDC dc(m_hWnd);
		//dc.Draw3dRect(0,0,rc.right-rc.left,TITLE_BAR_HEIGHT,RGB(255,0,127),RGB(255,0,127));
		Graphics graphic(dc.m_hDC);
		// fill background
		SolidBrush solidBrush(Color(21, 103, 165));
		graphic.FillRectangle(&solidBrush, 0, 0, rcTitle.right - rcTitle.left, mHeightCap + mHeightTool);

		SolidBrush brush(Color(255,255,255,255));
		FontFamily fontFamily(L"΢���ź�");
		Font font(&fontFamily,12,FontStyleUnderline,UnitPixel);
		PointF pointF(10.0,5.0f);
		graphic.DrawString(L"360��ȫ��ʿ 8.9",-1,&font,pointF,&brush);
		//graphic.
		//graphic.DrawImage(mImage,0,0);
		BITMAP bitmap;
		HDC hdcMem = CreateCompatibleDC(dc.m_hDC);
		HGDIOBJ oldbitmap = SelectObject(hdcMem,hBitmap);
		GetObject(hBitmap,sizeof(bitmap),&bitmap);
			
		for(int i = 0; i < rcTitle.right - rcTitle.left; i* bitmap.bmWidth > rcTitle.right - rcTitle.left)
		{
			::BitBlt(dc.m_hDC,i * bitmap.bmWidth,mHeightCap,bitmap.bmWidth,bitmap.bmHeight,hdcMem,0,0,SRCCOPY);
			i++;
		}
		

		SelectObject(hdcMem,oldbitmap);
		DeleteDC(hdcMem);


	}

	LRESULT OnNcMouseMove(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL&handled)		
	{
		return false;
	}

	LRESULT OnCreate(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL&handled)
	{
		CenterWindow();
		mHeightCap = GetSystemMetrics (SM_CYCAPTION);
		//GetSystemMetrics()
		//mImage = new Image((wchar_t*)"Skin.bmp");
		hBitmap = (HBITMAP)LoadImage(_Module.GetResourceInstance(),"Skin.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

		BITMAP bitmap;
		GetObject(hBitmap,sizeof(bitmap),&bitmap);
		mHeightTool = bitmap.bmHeight;
		return false;
	}

private:
	Gdiplus::Image *mImage;
	HBITMAP hBitmap;

	int mHeightCap;
	int mHeightTool;
};