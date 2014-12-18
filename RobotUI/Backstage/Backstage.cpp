// Backstage.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "BackstageInterface.h"


namespace robot
{
	static int res=0;
	BACKSTAGE_API int WINAPI Backstage_Startup(RCInfo *pInfos,int infoCount,WCHAR* localIP=_T("127.0.0.1"))
	{
		res=Encoder_Startup();
		if(res!=0)return res;
		res=Allocater_Startup(pInfos,infoCount);
		if(res!=0)return res;
		res=Networker_Startup(pInfos,infoCount,localIP);
		if(res!=0)return res;
		return 0;
	}
	BACKSTAGE_API int WINAPI Backstage_Shutdown()
	{
		res=Encoder_Shutdown();
		if(res!=0)return res;
		res=Allocater_Shutdown();
		if(res!=0)return res;
		res=Networker_Shutdown();
		if(res!=0)return res;
		return 0;
	}
}

