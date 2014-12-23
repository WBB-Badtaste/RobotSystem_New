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

	//任务结构体
	struct Target
	{
		int ID;///特征码，（其值为1~9999）
 		double PosX;///横坐标，单位mm，精确到0.32mm
 		double PosY;///纵坐标，单位mm，精确到0.32mm
 		double Aangle;///旋转角度,精确到0.5度。平行X轴为0度，正值代表顺时针偏转，负值相反
 		int EncoderValue;///编码器值，十位
	};
	struct RCInfo
	{
		WCHAR* IP;
		int Port;
		int RcID;
	};
	//总开关
	EXTERN_C BACKSTAGE_API int WINAPI Backstage_Startup(RCInfo *pInfos,int infoCount,LPCTSTR localIP);
	EXTERN_C BACKSTAGE_API int WINAPI Backstage_Shutdown();
	//添加新Target
	EXTERN_C BACKSTAGE_API int WINAPI Backstage_AddNewTargets(Target *targets,int num);
	//设置UI回调函数
	typedef int (WINAPI *CB2UI_NEWTARGET)(Target *targets,int num);
	typedef int (WINAPI *CB2UI_CATCHTARGET)(int *targetIDs,int num);
	EXTERN_C BACKSTAGE_API int WINAPI Backstage_SetCallback(CB2UI_NEWTARGET func1,CB2UI_CATCHTARGET func2);


	//编码器相关接口
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Startup();
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Shutdown();
	EXTERN_C BACKSTAGE_API int WINAPI Encoder_Read(int axis_no, int *value);
	//任务分配相关接口
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_Startup(RCInfo *pInfos,int num);
	EXTERN_C BACKSTAGE_API int WINAPI Allocater_Shutdown();
	//通讯相关接口
	EXTERN_C BACKSTAGE_API int WINAPI Networker_Startup(RCInfo *pInfos,int num,LPCTSTR localIP);
	EXTERN_C BACKSTAGE_API int WINAPI Networker_Shutdown();
}