#include "stdafx.h"
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

	BACKSTAGE_API int WINAPI Networker_Startup(RCInfo *pInfos,int num,LPCTSTR localIP)
	{
		 
		if(netWorker_isStarted) return 0;
		if (!mutex_connid) mutex_connid=CreateMutex(NULL,FALSE,NULL);
		WaitForSingleObject(mutex_connid,INFINITE);
 		if(pAgent->Start(localIP,FALSE)==FALSE)
 		{
 			DWORD res=GetLastError();
 		}
		while(--num>=0)
		{
			while(rcIDmatchConnID.size() <= (unsigned)pInfos[num].RcID) rcIDmatchConnID.push_back(0);
			if(pAgent->Connect((LPCTSTR)pInfos[num].IP,(USHORT)pInfos[num].Port,&(rcIDmatchConnID[pInfos[num].RcID]))==FALSE)
				if(pAgent->Connect((LPCTSTR)pInfos[num].IP,(USHORT)pInfos[num].Port,&(rcIDmatchConnID[pInfos[num].RcID]))==FALSE)
					if(pAgent->Connect((LPCTSTR)pInfos[num].IP,(USHORT)pInfos[num].Port,&(rcIDmatchConnID[pInfos[num].RcID]))==FALSE)
					{
						DWORD res=GetLastError();
						ReleaseMutex(mutex_connid);
						return ERROR_NETWORK_CONNECT_FAILED;
					}
		}
		ReleaseMutex(mutex_connid);
		netWorker_isStarted=true;
		return 0;
	}
	BACKSTAGE_API int WINAPI Networker_Shutdown()
	{
		if (!netWorker_isStarted) return 0;
		WaitForSingleObject(mutex_connid,INFINITE);
		if(pAgent->Stop()==FALSE) 
		{
			ReleaseMutex(mutex_connid);
			return ERROR_NETWORK_SHUTDOWN_FAILED;
		}
		ReleaseMutex(mutex_connid);
		rcIDmatchConnID.clear();
		if (mutex_connid) CloseHandle(mutex_connid);
		mutex_connid=0;
		netWorker_isStarted=false;
		return 0;
	}
	int Networker_SendTargets(int RCID, vector<Target> *pVecTargets)
	{
		WaitForSingleObject(mutex_connid,INFINITE);
		CONNID dwConnID = rcIDmatchConnID[RCID];
		if (!dwConnID) 
		{
			ReleaseMutex(mutex_connid);
			return ERROR_NETWORK_CONNECT_MISSED;
		}
		double dBuffer = 0;
		CString sBuffer("");
		string str("\x54");
		sBuffer.Format(_T("%d%d"), pVecTargets->size() / 10, pVecTargets->size() % 10);
		str += (char*)sBuffer.GetBuffer();
		for(vector<Target>::iterator iter=(*pVecTargets).begin();iter!=(*pVecTargets).end();++iter)
		{
			sBuffer.Format(_T("%d%d%d%d"), iter->ID / 1000, iter->ID / 100 % 10, iter->ID / 10 % 10, iter->ID % 10);
			str += (char*)sBuffer.GetBuffer();
			if (iter->PosX >= 0)
			{
				str += "\xAA";
				dBuffer = iter->PosX;
			}
			else
			{
				str += "\x55";
				dBuffer = -iter->PosX;
			}
			sBuffer.Format(_T("%d%d%d%d%d%d"), (long)dBuffer / 1000, (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10, (long)(dBuffer / 0.1) % 10, (long)(dBuffer / 0.01) % 10);
			str += (char*)sBuffer.GetBuffer();
			if (iter->PosY >= 0)
			{
				str += "\xAA";
				dBuffer = iter->PosY;
			}
			else
			{
				str += "\x55";
				dBuffer = -iter->PosY;
			}
			sBuffer.Format(_T("%d%d%d%d%d%d"), (long)dBuffer / 1000, (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10, (long)(dBuffer / 0.1) % 10, (long)(dBuffer / 0.01) % 10);
			str += (char*)sBuffer.GetBuffer();
			if (iter->Aangle >= 0)
			{
				str += "\xAA";
				dBuffer = iter->Aangle;
			}
			else
			{
				str += "\x55";
				dBuffer = -iter->Aangle;
			}
			sBuffer.Format(_T("%d%d%d%d"), (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10, (long)(dBuffer / 0.1) % 10);
			str += (char*)sBuffer.GetBuffer();
			if (iter->EncoderValue >= 0)
			{
				str += "\xAA";
				dBuffer = iter->EncoderValue;
			}
			else
			{
				str += "\x55";
				dBuffer = -iter->EncoderValue;
			}
			sBuffer.Format(_T("%d%d%d%d%d%d%d%d%d%d"), (long)dBuffer / 1000000000 % 10, (long)dBuffer / 100000000 % 10, (long)dBuffer / 10000000 % 10, (long)dBuffer / 1000000 % 10, (long)dBuffer / 100000 % 10, (long)dBuffer / 10000 % 10, (long)dBuffer / 1000, (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10);
			str += (char*)sBuffer.GetBuffer();
		}
		Bale(str);//加上包头包尾
		pAgent->Send(dwConnID, (const BYTE*)str.c_str(), str.length());
		ReleaseMutex(mutex_connid);
		return TRUE;
	}
}