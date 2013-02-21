/************************************************************************
ģ����:		��360��ȫ��ʿ����
����:		��δ��ģ�鹦�ܽ�������
�������:	2010-10-20
����:		��ΰ�� Yang Weifeng(Email: 11259500@qq.com)

�������������ʹ�ã�����ʹ�ñ�������ɵĺ�������˲��е��κ�����
************************************************************************/

#include "StdAfx.h"
#include "XButton.h"

// ���ư�ť
void CXButton::DrawButton( Gdiplus::Graphics&  graphics)
{
	// ��ȡ��ťͼƬ��Ϣ
	Image* pImage = CImageInfo::Instance()->ImageFromResource(m_nImageContorl);
	UINT iCount = m_nImageCount;
	if(m_bCheck && m_nAltImageContorl != 0)
	{
		pImage = CImageInfo::Instance()->ImageFromResource(m_nAltImageContorl);;
		iCount = m_nAltImageCount;
	}

	// ��ȡ��ť״̬��Ϣ
	int	iButtonIndex = 0;
	if(m_bDisabled && iCount >= 4) iButtonIndex = 3;
	else if(m_bPressed && iCount >= 3)iButtonIndex = 2;
	else if(m_bHovering && iCount >= 2)iButtonIndex = 1;
	else iButtonIndex = 0;

	// ��ָ��λ�û��ư�ť
	int iWidth = pImage->GetWidth()/iCount;
	int iHeight = pImage->GetHeight();
	RectF grect;
	grect.X=m_rcRect.left, grect.Y=m_rcRect.top; grect.Width = m_rcRect.Width(); grect.Height = m_rcRect.Height();
	graphics.DrawImage(pImage, grect, iWidth*iButtonIndex,0,iWidth,iHeight, UnitPixel);
}

// ������ť
void CXButton::CreateButton( CWnd* pParent, LPRECT lpRect, UINT nImage, UINT nCount /*= 4*/, UINT nAltImage /*= _T("")*/, UINT nAltCount /*= 0*/ , UINT nID/* = 0*/ )
{
	m_pParent = pParent;
	m_rcRect = lpRect;
	m_nImageContorl = nImage;
	m_nImageCount = nCount;
	m_nAltImageContorl = nAltImage;
	m_nAltImageCount = nAltCount;
	m_nID = nID;
}
