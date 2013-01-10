#include "stdafx.h"
/*
 ���Ǳ����CWindowImpl�м̳У�
 �������ǽ��޷��õ��κδ�����Ϣ��
 ����Ҫ�������ٴ�˵��һ�£�����ҲҪ��CCustomDraw�м̳С�
 ������CHAIN_MSG_MAP(CCustomDraw<MyListView>)��һ��
 �������ܹ����׵�����CListViewControl���ƵĹ��̡�
*/
class MyListView:	public CWindowImpl< MyListView,CListViewCtrl >,
					public CCustomDraw< MyListView >
{
public:
	BEGIN_MSG_MAP(MyListView)
		CHAIN_MSG_MAP(CCustomDraw< MyListView > )
	END_MSG_MAP()



	DWORD OnPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)  
	{          
		return  CDRF_NOTIFYITEMDRAW;  
	}  
	DWORD OnItemPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw)  
	{  
		NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( lpNMCustomDraw );  
		// This is the prepaint stage for an item. Here's where we set the  
		// item's text color. Our return value will tell Windows to draw the  
		// item itself, but it will use the new color we set here for the background  
		COLORREF crText;  
		if ( (pLVCD->nmcd.dwItemSpec % 2) == 0 )  
			crText = RGB(200,200,255);  
		else   
			crText = RGB(255,255,255);          
		// Store the color back in the NMLVCUSTOMDRAW struct.  
		pLVCD->clrTextBk = crText;  
		// Tell Windows to paint the control itself.  
		return CDRF_DODEFAULT;  
	} 

};