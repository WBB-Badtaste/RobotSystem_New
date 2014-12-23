// Backstage.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"



namespace robot
{
	
	BACKSTAGE_API int WINAPI Backstage_Startup(RCInfo *pInfos,int infoCount,LPCTSTR localIP=_T("127.0.0.1"))
	{
		backstageRes=Encoder_Startup();
		if(backstageRes!=0)return backstageRes;
		backstageRes=Allocater_Startup(pInfos,infoCount);
		if(backstageRes!=0)return backstageRes;
		backstageRes=Networker_Startup(pInfos,infoCount,localIP);
		if(backstageRes!=0)return backstageRes;
		return 0;
	}
	BACKSTAGE_API int WINAPI Backstage_Shutdown()
	{
		backstageRes=Encoder_Shutdown();
		if(backstageRes!=0)return backstageRes;
		backstageRes=Allocater_Shutdown();
		if(backstageRes!=0)return backstageRes;
		backstageRes=Networker_Shutdown();
		if(backstageRes!=0)return backstageRes;
		return 0;
	}
	BACKSTAGE_API int WINAPI Backstage_SetCallback(CB2UI_NEWTARGET func1,CB2UI_CATCHTARGET func2)
	{
		SendNewTargetToUI=func1;
		SendCatchInfos=func2;
		return 0;
	}
	BACKSTAGE_API int WINAPI Backstage_AddNewTargets(Target *targets,int num)
	{
		backstageRes = SendNewTargetToUI(targets,num);
		if(backstageRes) return backstageRes;
		backstageRes = Allocater_AddNewTargets(targets,num);
		if(backstageRes) return backstageRes;
		return 0;
	}
}

