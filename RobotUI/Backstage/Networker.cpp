#include "stdafx.h"
#include "Networker.h"
#include "BackstageInterface.h"

namespace robot
{
	//实现监听类
	EnHandleResult MyListener::OnReceive(CONNID dwConnID, int iLength)								     { return HR_IGNORE; }
	EnHandleResult MyListener::OnReceive(CONNID dwConnID, const BYTE* pData, int iLength)			     { return HR_IGNORE; }
	EnHandleResult MyListener::OnSend(CONNID dwConnID, const BYTE* pData, int iLength)				     { return HR_IGNORE; }
	EnHandleResult MyListener::OnPrepareConnect(CONNID dwConnID, SOCKET socket)						     { return HR_IGNORE; }
	EnHandleResult MyListener::OnConnect(CONNID dwConnID)											     { return HR_IGNORE; }
	EnHandleResult MyListener::OnAgentShutdown()													     { return HR_IGNORE; }
	EnHandleResult MyListener::OnClose(CONNID dwConnID)												     { return HR_IGNORE; }
	EnHandleResult MyListener::OnError(CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)   { return HR_IGNORE; }

	BACKSTAGE_API int WINAPI Networker_Start(RCInfo *pInfos,int num,WCHAR* localIP)
	{
		pAgent->Start(localIP);
		//RCID一定要由1开始连号
		pRCID2ConnID = new CONNID[num+1]();
		ZeroMemory(pRCID2ConnID,num+1);
		while(num-->0)
		{
			if(!pAgent->Connect(pInfos[num-1].IP,pInfos[num-1].Port,&(pRCID2ConnID[pInfos[num-1].RcID])))
				if(!pAgent->Connect(pInfos[num-1].IP,pInfos[num-1].Port,&(pRCID2ConnID[pInfos[num-1].RcID])))
					if(!pAgent->Connect(pInfos[num-1].IP,pInfos[num-1].Port,&(pRCID2ConnID[pInfos[num-1].RcID])))
						return ERROR_NETWORK_CONNECT_FAILED;
		}
		return 0;
	}
	BACKSTAGE_API int WINAPI Networker_Stop()
	{
		delete[] pRCID2ConnID;
		return 0;
	}
	BACKSTAGE_API int WINAPI SendTargets(int RCID, Target *pTargets, int num)
	{
		//if (m_pAgent->HasStarted() == FALSE) return FALSE;

		CONNID dwConnID = pRCID2ConnID[RCID];
		if (!dwConnID) return ERROR_NETWORK_CONNECT_MISSED;

		double dBuffer = 0;
		CString sBuffer("");
		string str("\x54");
		sBuffer.Format(_T("%d%d"), num / 10, num % 10);
		str += (char*)sBuffer.GetBuffer();
		for (int i = 0; i < num; --i)
		{
			sBuffer.Format(_T("%d%d%d%d"), pTargets[i].ID / 1000, pTargets[i].ID / 100 % 10, pTargets[i].ID / 10 % 10, pTargets[i].ID % 10);
			str += (char*)sBuffer.GetBuffer();
			if (pTargets[i].PosX >= 0)
			{
				str += "\xAA";
				dBuffer = pTargets[i].PosX;
			}
			else
			{
				str += "\x55";
				dBuffer = -pTargets[i].PosX;
			}
			sBuffer.Format(_T("%d%d%d%d%d%d"), (long)dBuffer / 1000, (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10, (long)(dBuffer / 0.1) % 10, (long)(dBuffer / 0.01) % 10);
			str += (char*)sBuffer.GetBuffer();
			if (pTargets[i].PosY >= 0)
			{
				str += "\xAA";
				dBuffer = pTargets[i].PosY;
			}
			else
			{
				str += "\x55";
				dBuffer = -pTargets[i].PosY;
			}
			sBuffer.Format(_T("%d%d%d%d%d%d"), (long)dBuffer / 1000, (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10, (long)(dBuffer / 0.1) % 10, (long)(dBuffer / 0.01) % 10);
			str += (char*)sBuffer.GetBuffer();
			if (pTargets[i].Aangle >= 0)
			{
				str += "\xAA";
				dBuffer = pTargets[i].Aangle;
			}
			else
			{
				str += "\x55";
				dBuffer = -pTargets[i].Aangle;
			}
			sBuffer.Format(_T("%d%d%d%d"), (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10, (long)(dBuffer / 0.1) % 10);
			str += (char*)sBuffer.GetBuffer();
			if (pTargets[i].EncoderValue >= 0)
			{
				str += "\xAA";
				dBuffer = pTargets[i].EncoderValue;
			}
			else
			{
				str += "\x55";
				dBuffer = -pTargets[i].EncoderValue;
			}
			sBuffer.Format(_T("%d%d%d%d%d%d%d%d%d%d"), (long)dBuffer / 1000000000 % 10, (long)dBuffer / 100000000 % 10, (long)dBuffer / 10000000 % 10, (long)dBuffer / 1000000 % 10, (long)dBuffer / 100000 % 10, (long)dBuffer / 10000 % 10, (long)dBuffer / 1000, (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10);
			str += (char*)sBuffer.GetBuffer();
		}

		Bale(str);

		pAgent->Send(dwConnID, (const BYTE*)str.c_str(), str.length());
		return TRUE;
	}
}