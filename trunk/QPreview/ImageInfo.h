/************************************************************************
ģ����:		��360��ȫ��ʿ����
����:		��δ��ģ�鹦�ܽ�������
�������:	2010-10-20
����:		��ΰ�� Yang Weifeng(Email: 11259500@qq.com)

�������������ʹ�ã�����ʹ�ñ�������ɵĺ�������˲��е��κ�����
************************************************************************/

#pragma once
#include <map>
#include <memory>
using namespace std;

class CImageInfo
{
public:
	static CImageInfo * Instance();

	~CImageInfo(void);

	// �ͷ����н�����Դ
	void	Release();

	// �ͷŽ�����ԴId���ؽ�����Դ
	Image*	ImageFromResource(UINT uId);

private:
	CImageInfo(void);
	static std::auto_ptr<CImageInfo> sm_inst;

	Image*	FromResource(UINT uId);

	map<UINT, Image*> m_mpImage;
};
