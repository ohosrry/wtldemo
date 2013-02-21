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

// �л���ť��С����
#define BTN_WIDTH  170
#define BTN_HEIGHT 63

// �Խ���ťId����
#define IDC_CLOSE		4002
#define IDC_BTN_1		4003
#define IDC_BTN_2		4004
#define IDC_BTN_3		4005
#define IDC_BTN_4		4006

// ͼƬ�ƶ���ʱ�����
#define TIMER_MOVE		1

// ��׼���캯��
CWndPreview::CWndPreview()
{
	m_iHovering = -1;
	m_iSelected = -1;

	m_iXButtonHovering = -1;

	m_bHovering = FALSE;
	m_bTracking = FALSE;

	m_bAutoMove = FALSE;
	m_bMouseDown = FALSE;
	m_iMouseMoveWidth = 0;

	m_iMoveWidthPerSecond = 0;
}

// ��׼��������
CWndPreview::~CWndPreview()
{
}

// ������Ϣӳ���
BEGIN_MESSAGE_MAP(CWndPreview, CWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(IDC_CLOSE, &CWndPreview::OnBtnClose)
	ON_MESSAGE(WM_MOUSELEAVE, &CWndPreview::OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, &CWndPreview::OnMouseHover)
END_MESSAGE_MAP()

// WM_ERASEBKGND��Ϣ������
BOOL CWndPreview::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

// WM_CREATE��Ϣ������
int  CWndPreview::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowText(_T("�°�����"));

	// ��ҳ��ǰ����Դ
	Image* pFrameImage = CImageInfo::Instance()->ImageFromResource(IDR_FRAME);

	// ��ҳ�汳����Դ
	Image* pBackFree = CImageInfo::Instance()->ImageFromResource(IDR_BACK_FREE);

	// ���������ڴ�С��λ��
	CRect cClientRect;
	GetClientRect(&cClientRect);
	cClientRect.right = pFrameImage->GetWidth();
	cClientRect.bottom = pFrameImage->GetHeight();
	MoveWindow(&cClientRect);
	CenterWindow(GetParent());

	// �������ڱ�ΪԲ�Ǵ���
	CRgn hRgnClient;
	hRgnClient.CreateRoundRectRgn(0,pFrameImage->GetHeight()-pBackFree->GetHeight(),pFrameImage->GetWidth()+1,pFrameImage->GetHeight()+1,7,7); 
	CRgn hRgnButton;
	hRgnButton.CreateRoundRectRgn(19,0,120+1,40+1,3,3); 
	hRgnClient.CombineRgn(&hRgnButton,&hRgnClient,RGN_OR);
	SetWindowRgn(hRgnClient,FALSE); 

	// �����ҳ����ʾ��Ϣ
	AddButton(_T("360��ȫ����"), IDR_ICON_DESKTOP, IDR_BACK_DESKTOP);
	AddButton(_T("��������"), IDR_ICON_UCENTER, IDR_BACK_UCENTER);
	AddButton(_T("ľ�����ǽ"), IDR_ICON_BAOHU, IDR_BACK_BAOHU);
	AddButton(_T("��������"), IDR_ICON_SCAN, IDR_BACK_SCAN);

	CRect rtButton;
	CXButton dcControl;

	// �����رհ�ť
	rtButton.top = pFrameImage->GetHeight()-pBackFree->GetHeight();
	rtButton.bottom = rtButton.top + 22;
	rtButton.right = cClientRect.Width()-4;
	rtButton.left = rtButton.right-47;
	dcControl.CreateButton(this, rtButton, IDR_BTN_CLOSE, 4, NULL, 0, IDC_CLOSE);
	m_XButtonList.push_back(dcControl);
	m_XButtonRectList.push_back(rtButton);

	// ������ҳ��1�а�ť
	rtButton.left = 374;
	rtButton.top = 222;
	rtButton.bottom = rtButton.top + 52;
	rtButton.right = rtButton.left +158;
	dcControl.CreateButton(this, rtButton, IDR_BTN_GREEN, 3, NULL, 0, IDC_BTN_1);
	m_XButtonList.push_back(dcControl);
	m_XButtonRectList.push_back(rtButton);

	// ������ҳ��2�а�ť
	rtButton.left = pFrameImage->GetWidth()*1 + 385;
	rtButton.top = 202;
	rtButton.bottom = rtButton.top + 52;
	rtButton.right = rtButton.left +158;
	dcControl.CreateButton(this, rtButton, IDR_BTN_GREEN, 3, NULL, 0, IDC_BTN_2);
	m_XButtonList.push_back(dcControl);
	m_XButtonRectList.push_back(rtButton);

	// ������ҳ��3�а�ť
	rtButton.left = pFrameImage->GetWidth()*2 + 385;
	rtButton.top = 202;
	rtButton.bottom = rtButton.top + 52;
	rtButton.right = rtButton.left +158;
	dcControl.CreateButton(this, rtButton, IDR_BTN_GREEN, 3, NULL, 0, IDC_BTN_3);
	m_XButtonList.push_back(dcControl);
	m_XButtonRectList.push_back(rtButton);

	// ������ҳ��4�а�ť
	rtButton.left = pFrameImage->GetWidth()*3 + 372;
	rtButton.top = 180;
	rtButton.bottom = rtButton.top + 52;
	rtButton.right = rtButton.left +158;
	dcControl.CreateButton(this, rtButton, IDR_BTN_GREEN, 3, NULL, 0, IDC_BTN_4);
	m_XButtonList.push_back(dcControl);
	m_XButtonRectList.push_back(rtButton);

	// ���õ�ǰ��ʾ��1����ҳ��
	m_iSelected = 0;

	return 0;
}

// WM_PAINT��Ϣ������
void CWndPreview::OnPaint()
{
	// ʹ��UNICODE�ַ�ת��
	USES_CONVERSION;

	CPaintDC dc(this);
	CMemoryDC dcMem(&dc);

	// ��ȡ���ھ���λ��
	CRect rtClient;
	GetClientRect(rtClient);

	// ��ȡ�ػ����λ��
	CRect rcPaint;
	dcMem.GetClipBox(&rcPaint);

	Gdiplus::Graphics graphics(dcMem.m_hDC);

	// ��ҳ��ǰ����Դ
	Image* pFrameImage = CImageInfo::Instance()->ImageFromResource(IDR_FRAME);

	// ��ť�Ϸ���ͷ��Դ
	Image *pArrowImage = CImageInfo::Instance()->ImageFromResource(IDR_ARROW);

	// ��ҳ�汳����Դ
	Image* pBackFree = CImageInfo::Instance()->ImageFromResource(IDR_BACK_FREE);

	// �������Ϸ��°����԰�ť�ı���
	RectF gdiRect;
	gdiRect.X = 19, gdiRect.Y = 0, gdiRect.Width = 120, gdiRect.Height = 5;
	graphics.DrawImage(pBackFree, gdiRect, 0, 0, 120, 5,UnitPixel);

	// ��������ܱ���ͼƬ
	for(int i = -1; i <= (int)m_ButtonList.size(); i++)
	{
		// ���㵱ǰͼƬ��ʾλ���Ƿ�����������ʾ��Χ
		int iCurrentX = (i*(int)pFrameImage->GetWidth() - (m_iSelected * (int)pFrameImage->GetWidth())+m_iMouseMoveWidth);
		if(iCurrentX > rtClient.Width() ||  iCurrentX + rtClient.Width() < 0)
		{
			continue;
		}

		Image* pBackImage = NULL;
		if(i == -1 || i == (int)m_ButtonList.size())
		{
			pBackImage = pBackFree;
		}
		else
		{
			pBackImage = CImageInfo::Instance()->ImageFromResource(m_ButtonList[i].nBack);
		}
		gdiRect.X = iCurrentX;
		gdiRect.Y=pFrameImage->GetHeight()-pBackImage->GetHeight();
		gdiRect.Height = pBackImage->GetHeight();
		gdiRect.Width = pBackImage->GetWidth();
		graphics.DrawImage(pBackImage, gdiRect, 0, 0, pBackImage->GetWidth(), pBackImage->GetHeight(),UnitPixel);
	}

	// ���������ǰ��ͼƬ
	graphics.DrawImage(pFrameImage, 0, 0, pFrameImage->GetWidth(), pFrameImage->GetHeight());

	// ���ƽ����л���ť�Ϸ��ļ�ͷ
	int iCurrent = ((m_iSelected * (int)pFrameImage->GetWidth())-m_iMouseMoveWidth)*BTN_WIDTH/(int)pFrameImage->GetWidth();
	if(iCurrent >= 0)
	{
		gdiRect.X=0, gdiRect.Y=299; gdiRect.Width = iCurrent; gdiRect.Height = pArrowImage->GetHeight();
		graphics.DrawImage(pArrowImage, gdiRect, 0, 0, 1, pArrowImage->GetHeight(), UnitPixel);
	}

	gdiRect.X=iCurrent, gdiRect.Y=299; gdiRect.Width = pArrowImage->GetWidth(); gdiRect.Height = pArrowImage->GetHeight();
	graphics.DrawImage(pArrowImage, gdiRect, 0,0, pArrowImage->GetWidth(), pArrowImage->GetHeight(), UnitPixel);

	if( iCurrent + (int)pArrowImage->GetWidth() < (int)pFrameImage->GetWidth())
	{
		gdiRect.X=iCurrent + (int)pArrowImage->GetWidth(), gdiRect.Y=299; gdiRect.Width = pFrameImage->GetWidth() - (iCurrent + pArrowImage->GetWidth()); gdiRect.Height = pArrowImage->GetHeight();
		graphics.DrawImage(pArrowImage, gdiRect, 0,0, 1, pArrowImage->GetHeight(), UnitPixel);
	}

	// ������չʾ����ͼƬ�л���ť
	StringFormat stringFormat;
	stringFormat.SetFormatFlags( StringFormatFlagsNoWrap);
	stringFormat.SetAlignment(StringAlignmentNear);
	stringFormat.SetLineAlignment(StringAlignmentNear);

	LOGFONT lfFont;
	memset(&lfFont, 0, sizeof(lfFont));
	lfFont.lfHeight = -15;
	lfFont.lfWeight |= FW_BOLD;
	lstrcpy(lfFont.lfFaceName, _T("����"));
	Font font(dcMem.GetSafeHdc(), &lfFont);
	Image *pBackHover = CImageInfo::Instance()->ImageFromResource(IDR_HOVER);
	for(int i = 0; i < (int)m_ButtonList.size(); i++)
	{
		CRect rcButton;
		GetButtonRect( i, rcButton );
		Point point(rcButton.left, rcButton.top);
		// �жϰ�ť�Ƿ���Ҫˢ��
		if(!rcPaint.IsRectEmpty() && !CRect().IntersectRect(&rcButton, rcPaint))
		{
			continue;
		}

		// ��ȡ��ť״̬
		int iOffset = 0;
		if(m_iSelected == i)iOffset = 2;
		else if(m_iHovering == i)iOffset = 1;
		else iOffset = 0;

		// ���ư�ť����
		RectF gdiRect;
		gdiRect.X=point.X, gdiRect.Y=point.Y; gdiRect.Width = pBackHover->GetWidth()/3; gdiRect.Height = pBackHover->GetHeight();
		graphics.DrawImage(pBackHover, gdiRect, pBackHover->GetWidth()/3*iOffset, 0 , pBackHover->GetWidth()/3, pBackHover->GetHeight(), UnitPixel);

		// ���ư�ťͼ��
		Image* pIconImage = CImageInfo::Instance()->ImageFromResource(m_ButtonList[i].nIcon);
		gdiRect.X=point.X+10, gdiRect.Y=point.Y+6; gdiRect.Width = pIconImage->GetWidth(); gdiRect.Height = pIconImage->GetHeight();
		graphics.DrawImage(pIconImage, gdiRect);

		// ���ư�ť����
		CString sName = m_ButtonList[i].sName;
		CStringW wName = T2W(sName.GetBuffer());
		SolidBrush brush((ARGB)Color::White);
		gdiRect.X=point.X+49, gdiRect.Y=point.Y+15; gdiRect.Width = rcButton.Width()-52; gdiRect.Height = rcButton.Height() -15;
		graphics.DrawString(wName, wName.GetLength(), &font, gdiRect,&stringFormat, &brush);
	}

	// ���ƽ���رհ�ť��������ť
	for(size_t i = 0; i< m_XButtonList.size(); i++)
	{
		CXButton& dcControl = m_XButtonList[i];
		CRect rcControl;
		if(i == 0)
		{
			// ��ǰ��ť�Ǵ��ڹرհ�ť
			dcControl.GetRect(&rcControl);
		}
		else
		{
			// ��ǰ��ť����ҳ���еĹ��ܰ�ť
			rcControl = m_XButtonRectList[i];
			rcControl.left -= ((m_iSelected * (int)pFrameImage->GetWidth())-m_iMouseMoveWidth);
			rcControl.right -= ((m_iSelected * (int)pFrameImage->GetWidth())-m_iMouseMoveWidth);
			dcControl.SetRect(&rcControl);
		}
		// �жϵ�ǰ��ť�Ƿ���Ҫ�ػ�
		if(!rcPaint.IsRectEmpty() && !CRect().IntersectRect(&rcControl, rcPaint))
		{
			continue;
		}

		dcControl.DrawButton(graphics);
	}
}

// WM_LBUTTONDOWN��Ϣ������
void CWndPreview::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_bMouseDown)
		return;

	// ��������Ƿ����л���ť��
	CRect rtButton;
	int iButton = HitTest(point, rtButton);
	if(iButton != -1)
	{
		if(m_bAutoMove)
		{
			return;
		}

		// ����������ͼƬ�Զ��ƶ�����ת��ѡ��ͼƬ
		CRect rtClient;
		GetClientRect(&rtClient);
		m_iMouseMoveWidth = (iButton-m_iSelected)*rtClient.Width();
		m_iMoveWidthPerSecond = (m_iMouseMoveWidth>0?m_iMouseMoveWidth:-m_iMouseMoveWidth)/10;
		if(m_iMoveWidthPerSecond < 20)m_iMoveWidthPerSecond = 20;

		SetTimer(TIMER_MOVE, 30, NULL);
		m_bAutoMove = TRUE;

		m_iSelected = iButton;
		return;
	}

	// ��������Ƿ���������ť��
	iButton = XButtonHitTest(point, rtButton);
	if(iButton != -1)
	{
		if(m_bAutoMove)
		{
			return;
		}
		m_XButtonList[iButton].LButtonDown();
		return;
	}

	// ��괦�ڱ���λ��
	if(point.y < 28)
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
		return;
	}

	// ��괦�ڽ���ͼƬ֮��
	if(m_bAutoMove)
	{
		// ��ǰͼƬ�����Զ��ƶ�
		KillTimer(TIMER_MOVE);
		m_bAutoMove = FALSE;
		m_iMouseDownX = point.x - m_iMouseMoveWidth;
	}
	else
	{
		m_iMouseDownX = point.x;
	}
	m_bMouseDown = TRUE;
	SetCapture();
}

// WM_MOUSEMOVE��Ϣ������
void CWndPreview::OnMouseMove(UINT nFlags, CPoint point) 
{
	// ������뿪�¼����и���
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}

	if(m_bAutoMove)
	{
		return;
	}

	// ����Ѿ���������ͼƬ����
	if(m_bMouseDown)
	{
		CRect rtClient;
		GetClientRect(&rtClient);
		m_iMouseMoveWidth = point.x - m_iMouseDownX;
		if(m_iSelected == 0 && m_iMouseMoveWidth > rtClient.Width())
		{
			m_iMouseMoveWidth = rtClient.Width();
		}
		if(m_iSelected == (int)m_ButtonList.size()-1 && -m_iMouseMoveWidth > rtClient.Width())
		{
			m_iMouseMoveWidth = -rtClient.Width();
		}
		Invalidate();
		return;
	}

	// ��������Ƿ����л���ť��
	CRect rtButton;
	int iButton = HitTest(point, rtButton);
	if(iButton != m_iHovering)
	{
		if(m_iHovering != -1)
		{
			CRect oldRect;
			GetButtonRect(m_iHovering, oldRect);
			m_iHovering = -1;
			InvalidateRect(oldRect);
		}
		if(iButton != -1)
		{
			m_iHovering = iButton;
			InvalidateRect(rtButton);
		};
	}

	// ��������Ƿ���������ť��
	iButton = XButtonHitTest(point, rtButton);
	if(iButton != m_iXButtonHovering)
	{
		if(m_iXButtonHovering != -1)
		{
			m_XButtonList[m_iXButtonHovering].MouseLeave();
			m_iXButtonHovering = -1;
		}
		if(iButton != -1)
		{
			m_iXButtonHovering = iButton;
			m_XButtonList[m_iXButtonHovering].MouseHover();
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

// WM_LBUTTONUP��Ϣ������
void CWndPreview::OnLButtonUp(UINT nFlags, CPoint point)
{
	// ����Ѿ���������ͼƬ����
	if(m_bMouseDown)
	{
		m_bMouseDown = FALSE;
		ReleaseCapture();

		CRect rtClient;
		GetClientRect(&rtClient);
		// ��������϶���
		if(m_iMouseMoveWidth > 0)
		{
			if(m_iSelected > 0 && m_iMouseMoveWidth > rtClient.Width()/4)
			{
				m_iMouseMoveWidth -= rtClient.Width();
				m_iSelected--;
			}
		}
		// ��������϶���
		else
		{
			if(m_iSelected < (int)m_ButtonList.size()-1 && -m_iMouseMoveWidth > rtClient.Width()/4)
			{
				m_iMouseMoveWidth += rtClient.Width();
				m_iSelected++;
			}
		}
		// ����������ͼƬ�Զ��ƶ����ָ���ǰͼƬ������ת��ѡ��ͼƬ
		m_iMoveWidthPerSecond = (m_iMouseMoveWidth>0?m_iMouseMoveWidth:-m_iMouseMoveWidth)/10;
		if(m_iMoveWidthPerSecond < 20)m_iMoveWidthPerSecond = 20;
		SetTimer(TIMER_MOVE, 30, NULL);
		m_bAutoMove = TRUE;
		return;
	}

	// ��������Ƿ���������ť��
	CRect rtButton;
	int iButton = XButtonHitTest(point, rtButton);
	if(iButton != -1)
	{
		m_XButtonList[iButton].LButtonUp();
	}
}

// WM_LBUTTONDBLCLK��Ϣ������
void CWndPreview::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnLButtonDown(nFlags, point);
}

// WM_TIMER��Ϣ������
void CWndPreview::OnTimer(UINT_PTR nIDEvent)
{
	if(!m_bAutoMove)
		return;

	// ����Ѿ������϶������Ѿ�ѡ����ͼƬ
	if(m_iMouseMoveWidth > 0)
	{
		if(m_iMouseMoveWidth - m_iMoveWidthPerSecond <= 0)
		{
			m_iMouseMoveWidth = 0;
			Invalidate();
			KillTimer(TIMER_MOVE);
			m_bAutoMove = FALSE;
		}
		else
		{
			m_iMouseMoveWidth-= m_iMoveWidthPerSecond;
			Invalidate();
		}
	}
	// ����Ѿ������϶������Ѿ�ѡ���ҷ�ͼƬ
	else
	{
		if(m_iMouseMoveWidth + m_iMoveWidthPerSecond >= 0)
		{
			m_iMouseMoveWidth = 0;
			Invalidate();
			KillTimer(TIMER_MOVE);
			m_bAutoMove = FALSE;
		}
		else
		{
			m_iMouseMoveWidth+= m_iMoveWidthPerSecond;
			Invalidate();
		}
	}

	CWnd::OnTimer(nIDEvent);
}

// �ڴ������ٺ����
void CWndPreview::PostNcDestroy()
{
	CWnd::PostNcDestroy();

	// �Զ��ͷŴ�����Դ
	delete this;
}

// ���ڹرհ�ť�¼�
void CWndPreview::OnBtnClose()
{
	SendMessage( WM_SYSCOMMAND,SC_CLOSE);
}

// ���ͼƬҳ�溯��
int  CWndPreview::AddButton( LPCTSTR szName, UINT nIcon, UINT nBack )
{
	ButtonInfo buttonInfo;
	buttonInfo.sName = szName;
	buttonInfo.nIcon = nIcon;
	buttonInfo.nBack = nBack;
	m_ButtonList.push_back(buttonInfo);
	return (int)m_ButtonList.size()-1;
}

// ������������л���ťλ��
int  CWndPreview::HitTest( CPoint point, CRect& rtButton )
{
	if(point.y < 317 || point.y > 362)
	{
		return -1;
	}

	if(point.x%BTN_WIDTH < 6 || point.x%BTN_WIDTH > 162)
	{
		return -1;
	}

	if(!GetButtonRect(point.x/BTN_WIDTH, rtButton))
	{
		return -1;
	}

	return point.x/BTN_WIDTH;
}

// ��ȡָ���л���ť����λ��
BOOL CWndPreview::GetButtonRect( int iButton, CRect& rtButton )
{
	if(iButton >= (int)m_ButtonList.size())
	{
		return FALSE;
	}

	rtButton.top = 317;
	rtButton.bottom = 362;
	rtButton.left = 1+ iButton * BTN_WIDTH + 6;
	rtButton.right =  1+ iButton * BTN_WIDTH + 163;

	return TRUE;
}

// �����������������ťλ��
int  CWndPreview::XButtonHitTest( CPoint point, CRect& rtButton )
{
	for(size_t i = 0; i< m_XButtonList.size(); i++)
	{
		CXButton& dcControl = m_XButtonList[i];
		if(dcControl.PtInButton(point))
		{
			m_XButtonList[i].GetRect(&rtButton);
			return (int)i;
		}
	}
	return -1;
}

// �����봰����Ϣ֪ͨ
LRESULT CWndPreview::OnMouseHover(WPARAM wparam, LPARAM lparam) 
{
	m_bHovering = TRUE;

	return 0;
}

// ����뿪������Ϣ֪ͨ
LRESULT CWndPreview::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bTracking = FALSE;
	m_bHovering = FALSE;
	if(m_iHovering != -1)
	{
		CRect oldRect;
		GetButtonRect(m_iHovering, oldRect);
		m_iHovering = -1;
		InvalidateRect(oldRect);
	}
	if(m_iXButtonHovering != -1)
	{
		m_XButtonList[m_iXButtonHovering].MouseLeave();
		m_iXButtonHovering = -1;
	}
	return 0;
}


