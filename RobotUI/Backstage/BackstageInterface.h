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

	//任务结构体
	struct Target
	{
		int ID;///特征码，（其值为1~9999）
		double PosX;///横坐标，单位mm，精确到0.32mm
		double PosY;///纵坐标，单位mm，精确到0.32mm
		float Aangle;///旋转角度,精确到0.5度。平行X轴为0度，正值代表顺时针偏转，负值相反
		long EncoderValue;///编码器值，十位
	};
	struct RCInfo
	{
		WCHAR* IP;
		int Port;
		int RcID;
	};
	//总开关
	EXTERN_C BACKSTAGE_API int WINAPI Backstage_Startup(RCInfo *pInfos,int infoCount,WCHAR* localIP);
	EXTERN_C BACKSTAGE_API int WINAPI Backstage_Shutdown();
	//编码器相关接口
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Startup();
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Shutdown();
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Read(int axis_no, int *value);
	//任务分配相关接口
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_Startup(RCInfo *pInfos,int num);
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_Shutdown();
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_AddNewTargets(Target *targets,int num);
	//通讯相关接口
	EXTERN_C BACKSTAGE_API int WINAPI Networker_Startup(RCInfo *pInfos,int num,WCHAR* localIP);
	EXTERN_C BACKSTAGE_API int WINAPI Networker_Shutdown();
	EXTERN_C BACKSTAGE_API int WINAPI Networker_SendTargets(int RCID, vector<Target> *pVecTargets);
}