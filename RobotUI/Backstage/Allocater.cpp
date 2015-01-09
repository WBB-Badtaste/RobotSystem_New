// Allocater.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "BackstageInterface.h"

namespace robot
{
	BACKSTAGE_API int WINAPI Allocater_Startup(RCInfo *pInfos,int num)
	{
		if(allocater_isStarted) return 0;
		for (int i=0;i<num;++i)
		{
			RCIDs.push_back(pInfos[i].RcID);
		}
		allocater_isStarted=true;
		return 0;
	}
	BACKSTAGE_API int WINAPI Allocater_Shutdown()
	{
		if(!allocater_isStarted) return 0;
		if(hThreadAllocate)
		{
			switch(WaitForSingleObject(hThreadAllocate,1000))
			{
			case WAIT_FAILED:
				return ERROR_ALLOCATE_SHUTDOWN_FAILED;
				break;
			case WAIT_OBJECT_0:
				CloseHandle(hThreadAllocate);
				CloseHandle(mutex_newTarget);
				break;
			case WAIT_TIMEOUT:
				return ERROR_ALLOCATE_SHUTDOWN_TIMEOUT;
				break;
			case WAIT_ABANDONED:
				return ERROR_ALLOCATE_SHUTDOWN_ABANDONED;
				break;
			default:
				break;
			}
		}
		allocater_isStarted=false;
		return 0;
	}
	static unsigned WINAPI ThreadAllocate ( LPVOID lpParameter )
	{
		WaitForSingleObject(mutex_newTarget,INFINITE);
		while (vecNewTargets.size()>0)
		{
			WaitForSingleObject(mutex_AllocatedTarget,INFINITE);
			RCID_AllocatedTargets[RCIDs[index_RC]].push_back(vecNewTargets.front());
			RCID_SendTargets[RCIDs[index_RC]].push_back(vecNewTargets.front());
			vecNewTargets.erase(vecNewTargets.begin());
			if(++index_RC==RCIDs.size()) index_RC=0;
			ReleaseMutex(mutex_AllocatedTarget);
		}
		ReleaseMutex(mutex_newTarget);
		for (map<int,vector<Target>>::iterator iter=RCID_SendTargets.begin();iter!=RCID_SendTargets.end();++iter)
		{
			Networker_SendTargets(iter->first,&iter->second);
			iter->second.clear();
		}
		return 0;
	}
	int Allocater_AddNewTargets(Target *targets,int num)
	{
		if(!allocater_isStarted) return ERROR_ALLOCATE_STARTUP_FAILED;
		if (num<=0) return 0;
		WaitForSingleObject(mutex_newTarget,INFINITE);
		int index=0;
		while (index<num)
		{
			vecNewTargets.push_back(targets[index++]);
		}
		ReleaseMutex(mutex_newTarget);
		hThreadAllocate=(HANDLE)_beginthreadex(NULL,0,ThreadAllocate,NULL,0,NULL);
		return 0;
	}
	int Allocater_DelCatchedTarget(int *targetIDs,int targetCount,int RCID)
	{
		WaitForSingleObject(mutex_AllocatedTarget,INFINITE);
		while(targetCount--)
		{
			vector<Target> *p=&RCID_AllocatedTargets[RCID];
			for(vector<Target>::iterator iter=p->begin();iter !=p->end();++iter)
			{
				if(iter->ID==targetIDs[targetCount])
					p->erase(iter);
			}
		}
		ReleaseMutex(mutex_AllocatedTarget);
		return 0;
	}
}
