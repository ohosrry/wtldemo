/************************************************************************
ģ����:		��360��ȫ��ʿ����
����:		��δ��ģ�鹦�ܽ�������
�������:	2010-10-20
����:		��ΰ�� Yang Weifeng(Email: 11259500@qq.com)

�������������ʹ�ã�����ʹ�ñ�������ɵĺ�������˲��е��κ�����
************************************************************************/

#pragma once

#include <vector>
#include "XButton.h"

using std::vector;

class CWndPreview : public CWnd
{
public:
	// ��׼������������
	CWndPreview();
	virtual ~CWndPreview();

protected:

	// ͼƬ�л�������Դ��Ϣ
	struct ButtonInfo
	{
		CString sName;
		UINT nIcon; 
		UINT nBack;
	};

	DECLARE_MESSAGE_MAP()

	// WM_CREATE��Ϣ������
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	// WM_PAINT��Ϣ������
	afx_msg void OnPaint();
	// WM_ERASEBKGND��Ϣ������
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// ���ڹرհ�ť�¼�
	afx_msg void OnBtnClose();
	// WM_TIMER��Ϣ������
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// �ڴ������ٺ����
	virtual void PostNcDestroy();
	// WM_MOUSEMOVE��Ϣ������
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// WM_LBUTTONDOWN��Ϣ������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// WM_LBUTTONUP��Ϣ������
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// WM_LBUTTONDBLCLK��Ϣ������
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	// ����뿪������Ϣ֪ͨ
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	// �����봰����Ϣ֪ͨ
	afx_msg LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam) ;
	// ���ͼƬҳ�溯��
	int		AddButton(LPCTSTR szName, UINT nIcon, UINT nBack );
	// ��ȡָ���л���ť����λ��
	BOOL	GetButtonRect(int iButton, CRect& rtButton);
	// ������������л���ťλ��
	int		HitTest(CPoint point, CRect& rtButton);
	// �����������������ťλ��
	int		XButtonHitTest(CPoint point, CRect& rtButton);

private:
	// ָʾ����Ѿ����д���
	BOOL	m_bHovering;
	// ָʾ�Ѿ���ʼ�����������뿪�����¼�����
	BOOL	m_bTracking;
	// ��ǰ������ڰ�ť
	int		m_iHovering;
	// ��ǰѡ���İ�ť
	int		m_iSelected;
	// ��ǰ����ͼƬ�Ƿ��Զ��ƶ�
	BOOL	m_bAutoMove;
	// ��ǰ����Ƿ��Ѿ�����
	BOOL	m_bMouseDown;
	// ��ǰ��갴��λ��
	int		m_iMouseDownX;
	// ��ǰ��갴�º��ƶ����
	int		m_iMouseMoveWidth;
	// ��ǰ����ͼƬÿ���Զ��ƶ��Ŀ��
	int		m_iMoveWidthPerSecond;
	// ������ͼƬ�л���ť�б�
	vector<ButtonInfo>	m_ButtonList;
	// ��ǰ�������������ť���
	int					m_iXButtonHovering;
	// ������ť����λ��
	vector<CRect>		m_XButtonRectList;
	// ������ť�б�
	vector<CXButton>	m_XButtonList;
};

