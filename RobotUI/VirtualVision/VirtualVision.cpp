// VirtualVision.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "VirtualVision.h"
#include "BackstageInterface.h"
#include <process.h>
#include<stdlib.h>

namespace robot
{
	
	static HANDLE eventWork=0;
	static Target targets[6];
	static int targetID=0;
	static int GetTargetID()
	{
		if (++targetID==10000) targetID=0;
		return targetID;
	}
	static unsigned WINAPI GenerateThread( LPVOID lpParameter )
	{
		while(WaitForSingleObject(eventWork,INFINITE)==WAIT_OBJECT_0)
		{
			Sleep(1000);
			switch(rand()%7)
			{
			case 1:
				targets[0].ID=GetTargetID();
				targets[0].PosX=50;
				targets[0].PosY=(rand()%500+50);
				targets[0].Aangle=0;
				targets[0].EncoderValue=0;
				Backstage_AddNewTargets(targets,1);
				break;
			case 2:
				targets[0].ID=GetTargetID();
				targets[0].PosX=50;
				targets[0].PosY=(rand()%200+50);
				targets[0].Aangle=0;
				targets[0].EncoderValue=0;
				targets[1].ID=GetTargetID();
				targets[1].PosX=50;
				targets[1].PosY=(rand()%200+350);
				targets[1].Aangle=0;
				targets[1].EncoderValue=0;
				Backstage_AddNewTargets(targets,2);
				break;
			case 3:
				targets[0].ID=GetTargetID();
				targets[0].PosX=50;
				targets[0].PosY=(rand()%100+50);
				targets[0].Aangle=0;
				targets[0].EncoderValue=0;
				targets[1].ID=GetTargetID();
				targets[1].PosX=50;
				targets[1].PosY=(rand()%100+250);
				targets[1].Aangle=0;
				targets[1].EncoderValue=0;
				targets[2].ID=GetTargetID();
				targets[2].PosX=50;
				targets[2].PosY=(rand()%100+450);
				targets[2].Aangle=0;
				targets[2].EncoderValue=0;
				Backstage_AddNewTargets(targets,3);
				break;
			case 4:
				targets[0].ID=GetTargetID();
				targets[0].PosX=50;
				targets[0].PosY=(rand()%50+50);
				targets[0].Aangle=0;
				targets[0].EncoderValue=0;
				targets[1].ID=GetTargetID();
				targets[1].PosX=50;
				targets[1].PosY=(rand()%50+200);
				targets[1].Aangle=0;
				targets[1].EncoderValue=0;
				targets[2].ID=GetTargetID();
				targets[2].PosX=50;
				targets[2].PosY=(rand()%50+350);
				targets[2].Aangle=0;
				targets[2].EncoderValue=0;
				targets[3].ID=GetTargetID();
				targets[3].PosX=50;
				targets[3].PosY=(rand()%50+500);
				targets[3].Aangle=0;
				targets[3].EncoderValue=0;
				Backstage_AddNewTargets(targets,4);
				break;
			case 5:
				targets[0].ID=GetTargetID();
				targets[0].PosX=50;
				targets[0].PosY=(rand()%20+50);
				targets[0].Aangle=0;
				targets[0].EncoderValue=0;
				targets[1].ID=GetTargetID();
				targets[1].PosX=50;
				targets[1].PosY=(rand()%20+170);
				targets[1].Aangle=0;
				targets[1].EncoderValue=0;
				targets[2].ID=GetTargetID();
				targets[2].PosX=50;
				targets[2].PosY=(rand()%20+290);
				targets[2].Aangle=0;
				targets[2].EncoderValue=0;
				targets[3].ID=GetTargetID();
				targets[3].PosX=50;
				targets[3].PosY=(rand()%20+410);
				targets[3].Aangle=0;
				targets[3].EncoderValue=0;
				targets[4].ID=GetTargetID();
				targets[4].PosX=50;
				targets[4].PosY=(rand()%20+530);
				targets[4].Aangle=0;
				targets[4].EncoderValue=0;
				Backstage_AddNewTargets(targets,5);
				break;
			case 6:
				targets[0].ID=GetTargetID();
				targets[0].PosX=50;
				targets[0].PosY=50;
				targets[0].Aangle=0;
				targets[0].EncoderValue=0;
				targets[1].ID=GetTargetID();
				targets[1].PosX=50;
				targets[1].PosY=150;
				targets[1].Aangle=0;
				targets[1].EncoderValue=0;
				targets[2].ID=GetTargetID();
				targets[2].PosX=50;
				targets[2].PosY=250;
				targets[2].Aangle=0;
				targets[2].EncoderValue=0;
				targets[3].ID=GetTargetID();
				targets[3].PosX=50;
				targets[3].PosY=350;
				targets[3].Aangle=0;
				targets[3].EncoderValue=0;
				targets[4].ID=GetTargetID();
				targets[4].PosX=50;
				targets[4].PosY=450;
				targets[4].Aangle=0;
				targets[4].EncoderValue=0;
				targets[5].ID=GetTargetID();
				targets[5].PosX=50;
				targets[5].PosY=550;
				targets[5].Aangle=0;
				targets[5].EncoderValue=0;
				Backstage_AddNewTargets(targets,6);
				break;
			default:
				break;
			}
		}
		return 0;
	}
	static HANDLE hGenerateThread =0;
	VIRTUALVISION_API int WINAPI VirtualVision_Start()
	{
		if(!hGenerateThread)
			hGenerateThread=(HANDLE)_beginthreadex(NULL,0,GenerateThread,NULL,0,NULL);
		if(!eventWork)
			eventWork=CreateEvent(NULL, TRUE, FALSE, NULL);
		SetEvent(eventWork);
		return 0;
	}
	VIRTUALVISION_API int WINAPI VirtualVision_Stop()
	{
		ResetEvent(eventWork);
		return 0;
	}
}

