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
	//任务结构体
	struct Target
	{
		int ID;///特征码，（其值为1~9999）
		double PosX;///横坐标，单位mm，精确到0.32mm
		double PosY;///纵坐标，单位mm，精确到0.32mm
		float Aangle;///旋转角度,精确到0.5度。平行X轴为0度，正值代表顺时针偏转，负值相反
		long EncoderValue;///编码器值，十位
		int RcID;
	};
	struct RCInfo
	{
		WCHAR* IP;
		int Port;
		int RcID;
	};
	//编码器相关接口
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Read(int axis_no, int *value);
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_StartUp();
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Close();
	//任务分配相关接口
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_Start(int rcs[],int num);
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_Allocate(Target targets[],int num);
	//通讯相关接口
	EXTERN_C BACKSTAGE_API int WINAPI Networker_Start(RCInfo *pInfos,int num);
	EXTERN_C BACKSTAGE_API int WINAPI Networker_Stop();
	EXTERN_C BACKSTAGE_API int WINAPI Networker_SendTargets(int RCID, Target *pTargets, int uNum);
}