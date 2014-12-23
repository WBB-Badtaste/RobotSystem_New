#pragma once

#ifdef BACKSTAGE_EXPORTS
#define BACKSTAGE_API __declspec(dllexport)
#else
#define BACKSTAGE_API __declspec(dllimport)
#endif


#include "ErrorInfos.h"


namespace robot
{
	using namespace std;

	//����ṹ��
	struct Target
	{
		int ID;///�����룬����ֵΪ1~9999��
 		double PosX;///�����꣬��λmm����ȷ��0.32mm
 		double PosY;///�����꣬��λmm����ȷ��0.32mm
 		double Aangle;///��ת�Ƕ�,��ȷ��0.5�ȡ�ƽ��X��Ϊ0�ȣ���ֵ����˳ʱ��ƫת����ֵ�෴
 		int EncoderValue;///������ֵ��ʮλ
	};
	struct RCInfo
	{
		WCHAR* IP;
		int Port;
		int RcID;
	};
	//�ܿ���
	EXTERN_C BACKSTAGE_API int WINAPI Backstage_Startup(RCInfo *pInfos,int infoCount,LPCTSTR localIP);
	EXTERN_C BACKSTAGE_API int WINAPI Backstage_Shutdown();
	//�����Target
	EXTERN_C BACKSTAGE_API int WINAPI Backstage_AddNewTargets(Target *targets,int num);
	//����UI�ص�����
	typedef int (WINAPI *CB2UI_NEWTARGET)(Target *targets,int num);
	typedef int (WINAPI *CB2UI_CATCHTARGET)(int *targetIDs,int num);
	EXTERN_C BACKSTAGE_API int WINAPI Backstage_SetCallback(CB2UI_NEWTARGET func1,CB2UI_CATCHTARGET func2);


	//��������ؽӿ�
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Startup();
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Shutdown();
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Read(int axis_no, int *value);
	//���������ؽӿ�
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_Startup(RCInfo *pInfos,int num);
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_Shutdown();
	//ͨѶ��ؽӿ�
	EXTERN_C BACKSTAGE_API int WINAPI Networker_Startup(RCInfo *pInfos,int num,LPCTSTR localIP);
	EXTERN_C BACKSTAGE_API int WINAPI Networker_Shutdown();
}