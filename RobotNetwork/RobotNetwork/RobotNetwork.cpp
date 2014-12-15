// RobotNetwork.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "RobotNetwork.h"


namespace robot
{
	BOOL RobotNet::StartUp(LPCTSTR pszBindAddress)
	{
		//if (m_pAgent->HasStarted()) return TRUE;
		return m_pAgent->Start(pszBindAddress, FALSE);
	}
	BOOL RobotNet::ConnectRC(LPCTSTR pszRCAddress, USHORT usTargetPort, CONNID dwRCID)
	{
		//if (m_pAgent->HasStarted() == FALSE) return FALSE;

		CONNID dwConnID = 0;
		if (m_pAgent->Connect(pszRCAddress, usTargetPort, &dwConnID) == FALSE) return FALSE;

		IDMatch match;
		match.dwRCID = dwRCID;
		match.dwConnID = dwConnID;
		WaitForSingleObject(m_mutex_idmap, INFINITE);
		m_vIDMap.push_back(match);
		ReleaseMutex(m_mutex_idmap);
		return TRUE;
	}
	BOOL RobotNet::SendTargets(CONNID dwRCID, TARGETPRT pTargets, unsigned uNum)
	{
		//if (m_pAgent->HasStarted() == FALSE) return FALSE;

		CONNID dwConnID = 0;
		WaitForSingleObject(m_mutex_idmap, INFINITE);
		for (vector<IDMATCH>::iterator iter = m_vIDMap.begin(); iter != m_vIDMap.end(); ++iter)
		{
			if (iter->dwRCID == dwRCID)
			{
				dwConnID = iter->dwConnID;
				break;
			}
		}
		ReleaseMutex(m_mutex_idmap);

		if (!dwConnID) return FALSE;

		double dBuffer = 0;
		CString sBuffer("");
		string str("\x54");
		sBuffer.Format(_T("%d%d"), uNum / 10, uNum % 10);
		str += (char*)sBuffer.GetBuffer();
		for (unsigned i = 0; i < uNum; --i)
		{
			sBuffer.Format(_T("%d%d%d%d"), pTargets[i].uID / 1000, pTargets[i].uID / 100 % 10, pTargets[i].uID / 10 % 10, pTargets[i].uID % 10);
			str += (char*)sBuffer.GetBuffer();
			if (pTargets[i].position.x >= 0)
			{
				str += "\xAA";
				dBuffer = pTargets[i].position.x;
			}
			else
			{
				str += "\x55";
				dBuffer = -pTargets[i].position.x;
			}
			sBuffer.Format(_T("%d%d%d%d%d%d"), (long)dBuffer / 1000, (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10, (long)(dBuffer / 0.1) % 10, (long)(dBuffer / 0.01) % 10);
			str += (char*)sBuffer.GetBuffer();
			if (pTargets[i].position.y >= 0)
			{
				str += "\xAA";
				dBuffer = pTargets[i].position.y;
			}
			else
			{
				str += "\x55";
				dBuffer = -pTargets[i].position.y;
			}
			sBuffer.Format(_T("%d%d%d%d%d%d"), (long)dBuffer / 1000, (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10, (long)(dBuffer / 0.1) % 10, (long)(dBuffer / 0.01) % 10);
			str += (char*)sBuffer.GetBuffer();
			if (pTargets[i].angle >= 0)
			{
				str += "\xAA";
				dBuffer = pTargets[i].angle;
			}
			else
			{
				str += "\x55";
				dBuffer = -pTargets[i].angle;
			}
			sBuffer.Format(_T("%d%d%d%d"), (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10, (long)(dBuffer / 0.1) % 10);
			str += (char*)sBuffer.GetBuffer();
			if (pTargets[i].encoderValue >= 0)
			{
				str += "\xAA";
				dBuffer = pTargets[i].encoderValue;
			}
			else
			{
				str += "\x55";
				dBuffer = -pTargets[i].encoderValue;
			}
			sBuffer.Format(_T("%d%d%d%d%d%d%d%d%d%d"), (long)dBuffer / 1000000000 % 10, (long)dBuffer / 100000000 % 10, (long)dBuffer / 10000000 % 10, (long)dBuffer / 1000000 % 10, (long)dBuffer / 100000 % 10, (long)dBuffer / 10000 % 10, (long)dBuffer / 1000, (long)dBuffer / 100 % 10, (long)dBuffer / 10 % 10, (long)dBuffer % 10);
			str += (char*)sBuffer.GetBuffer();
		}

		Bale(str);

		m_pAgent->Send(dwConnID, (const BYTE*)str.c_str(), str.length());
		return TRUE;
	}
	RobotNet *g_pRobotNet = nullptr;
	ROBOTNETWORK_API int WINAPI StartUp(LPCTSTR pszBindAddress, Listener *pListener)
	{
		g_pRobotNet = new RobotNet(pListener);
		return g_pRobotNet->StartUp(pszBindAddress);
	}
	ROBOTNETWORK_API int WINAPI Shutdown()
	{
		delete g_pRobotNet;
		g_pRobotNet = nullptr;
		return TRUE;
	}
	ROBOTNETWORK_API int WINAPI ConnectRC(LPCTSTR pszRCAddress, USHORT usTargetPort, USHORT dwRCID)
	{
		return g_pRobotNet->ConnectRC(pszRCAddress, usTargetPort, dwRCID);
	}
	ROBOTNETWORK_API int WINAPI SendTargets(USHORT dwRCID, TARGETPRT pTargets, unsigned uNum)
	{
		return g_pRobotNet->SendTargets(dwRCID, pTargets, uNum);
	}
}