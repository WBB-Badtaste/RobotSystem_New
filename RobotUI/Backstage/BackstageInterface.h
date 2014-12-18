#pragma once

#ifdef BACKSTAGE_EXPORTS
#define BACKSTAGE_API __declspec(dllexport)
#else
#define BACKSTAGE_API __declspec(dllimport)
#endif

#include "Networker.h"
#include "ErrorInfos.h"
#include <vector>

namespace robot
{
	using namespace std;

	//����ṹ��
	struct Target
	{
		int ID;///�����룬����ֵΪ1~9999��
		double PosX;///�����꣬��λmm����ȷ��0.32mm
		double PosY;///�����꣬��λmm����ȷ��0.32mm
		float Aangle;///��ת�Ƕ�,��ȷ��0.5�ȡ�ƽ��X��Ϊ0�ȣ���ֵ����˳ʱ��ƫת����ֵ�෴
		long EncoderValue;///������ֵ��ʮλ
	};
	struct RCInfo
	{
		WCHAR* IP;
		int Port;
		int RcID;
	};
	//�ܿ���
	EXTERN_C BACKSTAGE_API int WINAPI Backstage_Startup(RCInfo *pInfos,int infoCount,WCHAR* localIP);
	EXTERN_C BACKSTAGE_API int WINAPI Backstage_Shutdown();
	//��������ؽӿ�
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Startup();
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Shutdown();
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Read(int axis_no, int *value);
	//���������ؽӿ�
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_Startup(RCInfo *pInfos,int num);
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_Shutdown();
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_AddNewTargets(Target *targets,int num);
	//ͨѶ��ؽӿ�
	EXTERN_C BACKSTAGE_API int WINAPI Networker_Startup(RCInfo *pInfos,int num,WCHAR* localIP);
	EXTERN_C BACKSTAGE_API int WINAPI Networker_Shutdown();
	EXTERN_C BACKSTAGE_API int WINAPI Networker_SendTargets(int RCID, vector<Target> *pVecTargets);
}