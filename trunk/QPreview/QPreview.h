/************************************************************************
ģ����:		��360��ȫ��ʿ����
����:		��δ��ģ�鹦�ܽ�������
�������:	2010-10-20
����:		��ΰ�� Yang Weifeng(Email: 11259500@qq.com)

�������������ʹ�ã�����ʹ�ñ�������ɵĺ�������˲��е��κ�����
************************************************************************/

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "SingleInst.h"

// CQPreview:
// �йش����ʵ�֣������ QPreview.cpp
class CQPreview : public CWinApp
{
public:
	CQPreview();

	DECLARE_MESSAGE_MAP()

private:
	virtual BOOL InitInstance();
	virtual int  ExitInstance();

	ULONG_PTR	m_GdiplusToken;
	CSingleInst	m_siSingleInst;
};

extern CQPreview theApp;