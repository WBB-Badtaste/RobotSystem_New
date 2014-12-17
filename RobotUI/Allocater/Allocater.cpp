// Allocater.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Allocater.h"


ALLOCATER_API int WINAPI Start(int rcs[],int num)
{
	while (num>=0) vecRC.push_back(rcs[--num]);
	return 0;
}

ALLOCATER_API int WINAPI Allocate(Target *targets,int num)
{
	int i=0;
 	while(i<num)
 	{
 		targets[i++].RcID=vecRC[lastAllocatingRC];
 		if(++lastAllocatingRC==vecRC.size()) lastAllocatingRC=0;
 	}
	return 0;
}