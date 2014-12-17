#pragma once

#ifdef BACKSTAGE_EXPORTS
#define BACKSTAGE_API __declspec(dllexport)
#else
#define BACKSTAGE_API __declspec(dllimport)
#endif

#include "Networker.h"
#include "ErrorInfos.h"

namespace robot
{
	//����ṹ��
	struct Target
	{
		int ID;///�����룬����ֵΪ1~9999��
		double PosX;///�����꣬��λmm����ȷ��0.32mm
		double PosY;///�����꣬��λmm����ȷ��0.32mm
		float Aangle;///��ת�Ƕ�,��ȷ��0.5�ȡ�ƽ��X��Ϊ0�ȣ���ֵ����˳ʱ��ƫת����ֵ�෴
		long EncoderValue;///������ֵ��ʮλ
		int RcID;
	};
	struct RCInfo
	{
		WCHAR* IP;
		int Port;
		int RcID;
	};
	//��������ؽӿ�
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Read(int axis_no, int *value);
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_StartUp();
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Close();
	//���������ؽӿ�
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_Start(int rcs[],int num);
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_Allocate(Target targets[],int num);
	//ͨѶ��ؽӿ�
	EXTERN_C BACKSTAGE_API int WINAPI Networker_Start(RCInfo *pInfos,int num);
	EXTERN_C BACKSTAGE_API int WINAPI Networker_Stop();
	EXTERN_C BACKSTAGE_API int WINAPI Networker_SendTargets(int RCID, Target *pTargets, int uNum);
}