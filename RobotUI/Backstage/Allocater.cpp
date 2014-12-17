// Allocater.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Allocater.h"
#include "BackstageInterface.h"

namespace robot
{
	BACKSTAGE_API int WINAPI Allocater_Start(int rcs[],int num)
	{
		while (num>=0) vecRC.push_back(rcs[--num]);
		return 0;
	}

	BACKSTAGE_API int WINAPI Allocater_Allocate(Target *targets,int num)
	{
		int i=0;
		while(i<num)
		{
			targets[i++].RcID=vecRC[lastAllocatingRC];
			if(++lastAllocatingRC==vecRC.size()) lastAllocatingRC=0;
		}
		return 0;
	}
}
