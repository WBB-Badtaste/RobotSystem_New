#include "StdAfx.h"
#include "Filter.h"
#include <math.h>


namespace robot
{
	//��Ϊtarget��������ģ�����ֻ��Ҫ�Ա���target����ǰ���ݺ;�target���ĺ󲿷�
	//��˳���ҵ���target���е�һ�������ھ�target����target�����ɴ˴���ȡ��target��������ɹ���
	int Filter_HandleObjects(Target *targets,int *num)
	{
		if(referTargets==nullptr) 
		{
			referTargets=new Target[*num];
			*referTargets= *targets;
			referNum=*num;
			return 0;
		}
		int currentEncoderValue=0;
		Encoder_Read(0,&currentEncoderValue);
		for (int i=0;i<*num;++i)
		{
			for (int j=referNum-1;j>=0;--j)
			{
				double currentPosX=(currentEncoderValue-referTargets[j].EncoderValue)*encoderRate;
				double diffX=referTargets[j].PosX+currentPosX-targets[i].PosX;
				double diffY=referTargets[j].PosY-targets[i].PosY;
				if (sqrt(diffX*diffX+diffY*diffY)>threshold )//threshold�ǹ�����ֵ������target�����ĵ�Ĳ������ֵ���ж�Ϊ������ͬ��target
				{
					
					for(int k=0;k<*num-i;++k)
					{
						targets[k]=targets[k+i];
					}
					*num-=i;
					delete[] referTargets;
					referTargets=new Target[*num];
					*referTargets= *targets;
					referNum=*num;
					return 1;
				}
			}
		}
		return 0;
	}
	int Filter_Reset()
	{
		if(referTargets) 
			delete[] referTargets;
		referTargets=nullptr;
		referNum=0;
		return 0;
	}
	int Filter_SetThreshold(double thresholdValue)
	{
		threshold=thresholdValue;
		return 0;
	}
}