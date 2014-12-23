#include "stdafx.h"
#include "BackstageInterface.h"

namespace robot
{
	static unsigned WINAPI ReceiveThread( LPVOID lpParameter )
	{
		int targetCount=0;
		int index=0;
		int catchCount=0;
		ReceiveThreadInfo *pInfo=(ReceiveThreadInfo*)lpParameter;
		switch(pInfo->data[9])
		{
		case 0x46://抓取反馈
			targetCount=pInfo->data[10]&0x0f*10+pInfo->data[11]&0x0f;
			while(index<targetCount)
			{
				if (pInfo->data[16+5*index]==0xAA)
				{
					//抓取成功
					catchedTargetIDs[index]=pInfo->data[12+5*index]&0x0f*1000+pInfo->data[13+5*index]&0x0f*100+pInfo->data[14+5*index]&0x0f*10+pInfo->data[15+5*index]&0x0f;
					catchCount++;
				}
				else
				{
					//抓取失败
				}
				SendCatchInfos(catchedTargetIDs,catchCount);
			}
			break;
		default:
			break;
		}
		delete[] pInfo->data;
		delete pInfo;
		return 0;
	}
	//实现监听类
	EnHandleResult MyListener::OnReceive(CONNID dwConnID, int iLength)								     { return HR_IGNORE; }
	EnHandleResult MyListener::OnReceive(CONNID dwConnID, const BYTE* pData, int iLength)			     
	{
		ReceiveThreadInfo *pInfo=new ReceiveThreadInfo();
		pInfo->data=new BYTE[iLength];
		for(int i=0;i<iLength;++i)
		{
			pInfo->data[i]=pData[i];
		}
		HANDLE h=(HANDLE)_beginthreadex(NULL,0,ReceiveThread,pInfo,0,NULL);
		hReceiveThreads.push_back(h);
		return HR_OK;
	}
	EnHandleResult MyListener::OnSend(CONNID dwConnID, const BYTE* pData, int iLength)				     { return HR_IGNORE; }
	EnHandleResult MyListener::OnPrepareConnect(CONNID dwConnID, SOCKET socket)						     { return HR_IGNORE; }
	EnHandleResult MyListener::OnConnect(CONNID dwConnID)											     { return HR_IGNORE; }
	EnHandleResult MyListener::OnAgentShutdown()													     { return HR_IGNORE; }
	EnHandleResult MyListener::OnClose(CONNID dwConnID)												     { return HR_IGNORE; }
	EnHandleResult MyListener::OnError(CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)   { return HR_IGNORE; }
	BACKSTAGE_API int WINAPI Networker_Startup(RCInfo *pInfos,int num,LPCTSTR localIP)
	{
		if(netWorker_isStarted) return 0;
		ZeroMemory(catchedTargetIDs,100);
		if (!mutex_connid) mutex_connid=CreateMutex(NULL,FALSE,NULL);
		WaitForSingleObject(mutex_connid,INFINITE);
 		if(pAgent->Start(localIP,FALSE)==FALSE)
 		{
 			DWORD res=GetLastError();
 		}
		while(--num>=0)
		{
			if(pAgent->Connect((LPCTSTR)pInfos[num].IP,(USHORT)pInfos[num].Port,&(RCID_CONNID[pInfos[num].RcID]))==FALSE)
				if(pAgent->Connect((LPCTSTR)pInfos[num].IP,(USHORT)pInfos[num].Port,&(RCID_CONNID[pInfos[num].RcID]))==FALSE)
					if(pAgent->Connect((LPCTSTR)pInfos[num].IP,(USHORT)pInfos[num].Port,&(RCID_CONNID[pInfos[num].RcID]))==FALSE)
					{
						DWORD res=GetLastError();
						ReleaseMutex(mutex_connid);
						return ERROR_NETWORK_CONNECT_FAILED;
					}
			CONNID_RCID[RCID_CONNID[pInfos[num].RcID]]=pInfos[num].RcID;
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
		RCID_CONNID.clear();
		if (mutex_connid) CloseHandle(mutex_connid);
		mutex_connid=0;
		netWorker_isStarted=false;
		return 0;
	}
	int Networker_SendTargets(int RCID, vector<Target> *pVecTargets)
	{
		WaitForSingleObject(mutex_connid,INFINITE);
		CONNID dwConnID = RCID_CONNID[RCID];
		if (!dwConnID) 
		{
			ReleaseMutex(mutex_connid);
			return ERROR_NETWORK_CONNECT_MISSED;
		}
		double dBuffer = 0;
		string str("\x54");
		ostringstream oss;
		oss<<pVecTargets->size() / 10<<pVecTargets->size() % 10 ;
		str +=oss.str();
		oss.str("");
		for(vector<Target>::iterator iter=(*pVecTargets).begin();iter!=(*pVecTargets).end();++iter)
		{
			oss<<iter->ID / 1000<<iter->ID / 100 % 10<<iter->ID / 10 % 10<<iter->ID % 10;
			str +=oss.str();
			oss.str("");
			if (iter->PosX >= 0)
			{
				str +="\xAA";
				dBuffer = iter->PosX;
			}
			else
			{
				str +="\x55";
				dBuffer = -iter->PosX;
			}
			oss<<(long)dBuffer / 1000<<(long)dBuffer / 100 % 10<<(long)dBuffer / 10 % 10<< (long)dBuffer % 10<<(long)(dBuffer / 0.1) % 10<<(long)(dBuffer / 0.01) % 10;
			str +=oss.str();
			oss.str("");
			if (iter->PosY >= 0)
			{
				str +="\xAA";
				dBuffer = iter->PosY;
			}
			else
			{
				str +="\x55";
				dBuffer = -iter->PosY;
			}
			oss<<(long)dBuffer / 1000<< (long)dBuffer / 100 % 10<< (long)dBuffer / 10 % 10<< (long)dBuffer % 10<< (long)(dBuffer / 0.1) % 10<< (long)(dBuffer / 0.01) % 10 ;
			str +=oss.str();
			oss.str("");
			if (iter->Aangle >= 0)
			{
				str +="\xAA";
				dBuffer = iter->Aangle;
			}
			else
			{
				str +="\x55";
				dBuffer = -iter->Aangle;
			}
			oss<<(long)dBuffer / 100 % 10<< (long)dBuffer / 10 % 10<< (long)dBuffer % 10<< (long)(dBuffer / 0.1) % 10 ;
			str +=oss.str();
			oss.str("");
			if (iter->EncoderValue >= 0)
			{
				str +="\xAA";
				dBuffer = iter->EncoderValue;
			}
			else
			{
				str +="\x55";
				dBuffer = -iter->EncoderValue;
			}
			oss<<(long)dBuffer / 1000000000 % 10<< (long)dBuffer / 100000000 % 10<< (long)dBuffer / 10000000 % 10<< (long)dBuffer / 1000000 % 10<< (long)dBuffer / 100000 % 10<< (long)dBuffer / 10000 % 10<< (long)dBuffer / 1000<< (long)dBuffer / 100 % 10<< (long)dBuffer / 10 % 10<< (long)dBuffer % 10 ;
			str +=oss.str();
			oss.str("");
		}
		Bale(str);//加上包头包尾
		pAgent->Send(dwConnID, (const BYTE*)str.c_str(), str.length());
		ReleaseMutex(mutex_connid);
		return TRUE;
	}
}