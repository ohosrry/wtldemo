#include "ScreenForm.h"
#include "MainForm.h"

CBitmap bmp_srcreen;	//��������ȫ��ͼƬ
MainForm *mf_ptr = NULL;

void ScreenForm::OnRButtonDown(UINT nFlags, CPoint point)
{
	DestroyWindow();
	mf_ptr->ShowWindow(SW_SHOW);
}