/************************************************************************
ģ����:		��360��ȫ��ʿ����
����:		��δ��ģ�鹦�ܽ�������
�������:	2010-10-20
����:		��ΰ�� Yang Weifeng(Email: 11259500@qq.com)

�������������ʹ�ã�����ʹ�ñ�������ɵĺ�������˲��е��κ�����
************************************************************************/

#pragma once

class CXButton
{
public:
	// ��׼���캯��
	CXButton()
	{
		m_bCheck = FALSE;
		m_bHovering = FALSE;
		m_bPressed = FALSE;
		m_bDisabled = FALSE;
		m_nImageContorl = 0;
		m_nAltImageContorl = 0;
	}

	// ���ð�ť����λ��
	void SetRect(LPCRECT lpRect){m_rcRect = lpRect;};
	// ��ȡ��ť����λ��
	void GetRect(LPRECT lpRect){*lpRect = *m_rcRect;};
	// ���ָ�����Ƿ��ڰ�ť��
	BOOL PtInButton(CPoint& point){return m_rcRect.PtInRect(point);};
	// ���ư�ť
	void DrawButton( Gdiplus::Graphics&  graphics);
	// ������ť
	void CreateButton(CWnd* pParent, LPRECT lpRect,UINT nImage, UINT nCount = 4, UINT sAltImage = 0, UINT nAltCount = 0, UINT nID = 0);
	// ���ð�ť״̬
	void EnableButton(BOOL bEnable)
	{
		m_bDisabled = !bEnable;
		m_pParent->InvalidateRect(m_rcRect);
	}

	// ���ð�ťѡ��״̬
	void SetCheck(BOOL bCheck)
	{
		m_bCheck = bCheck;
		m_pParent->InvalidateRect(m_rcRect);
	}
	// ��ȡ��ťId
	UINT GetControlId(){return m_nID;};
	// ������ť�¼�
	void DoCommand()
	{
		if(!m_bDisabled)
		{
			m_bCheck = !m_bCheck;
			m_pParent->InvalidateRect(m_rcRect);
			m_pParent->PostMessage(WM_COMMAND, m_nID);
		}
	}

	// ��갴�°�ť�¼�
	void LButtonDown()
	{
		if(!m_bDisabled)
		{
			m_bPressed = TRUE;
			m_pParent->InvalidateRect(m_rcRect);
		}
	};
	// �����°�ť�¼�
	void LButtonUp()
	{
		if(!m_bDisabled)
		{
			if(m_bPressed == TRUE)
			{
				m_bCheck = !m_bCheck;
				m_bPressed = FALSE;
				m_pParent->InvalidateRect(m_rcRect);
				m_pParent->PostMessage(WM_COMMAND, m_nID);
			}
		}
	}
	// �����밴ť�����¼�
	void MouseHover()
	{
		if(!m_bDisabled)
		{
			m_bHovering = TRUE;
			m_pParent->InvalidateRect(m_rcRect);
		}
	}
	// ����뿪��ť�����¼�
	void MouseLeave()
	{
		if(!m_bDisabled)
		{
			m_bPressed = FALSE;
			m_bHovering = FALSE;
			m_pParent->InvalidateRect(m_rcRect);
		}
	}
private:
	// ��ť����λ��
	CRect	m_rcRect;
	// ��ʶ�����밴ť����
	BOOL	m_bHovering;
	// ��ʶ�Ѿ������ť
	BOOL	m_bPressed;
	// ��ʶ��ť�Ѿ�������
	BOOL	m_bDisabled;
	// ��ʶ��ť�Ѿ���ѡ��
	BOOL	m_bCheck;
	// ��ťͼƬ���
	UINT	m_nImageContorl;
	// ��ť����״̬ͼƬ���
	UINT	m_nAltImageContorl;
	// ��ťͼƬ�а�����ͼƬ����
	UINT	m_nImageCount;
	// ��ťѡ��ͼƬ�а�����ͼƬ����
	UINT	m_nAltImageCount;
	// ��ťId��
	int		m_nID;
	// ��ť������
	CWnd*	m_pParent;
};
