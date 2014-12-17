#pragma once

#include "HPSocket.h"
#include "SocketInterface.h"
#include "RobotNetworkInterface.h"
#include <vector>
#include <tchar.h>
#include <string>
#include <atlstr.h>
#include <tchar.h>

namespace robot
{
	using namespace std;	


	class AgentListener :public CTcpAgentListener
	{
	public:
		AgentListener(Listener *pListener) : m_pListener(pListener)										 {}

		virtual EnHandleResult OnReceive(CONNID dwConnID, int iLength)								     { return HR_IGNORE; }
		virtual EnHandleResult OnReceive(CONNID dwConnID, const BYTE* pData, int iLength)			     { return HR_IGNORE; }
		virtual EnHandleResult OnSend(CONNID dwConnID, const BYTE* pData, int iLength)				     { return HR_IGNORE; }
		virtual EnHandleResult OnPrepareConnect(CONNID dwConnID, SOCKET socket)						     { return HR_IGNORE; }
		virtual EnHandleResult OnConnect(CONNID dwConnID)											     { return HR_IGNORE; }
		virtual EnHandleResult OnAgentShutdown()													     { return HR_IGNORE; }
		virtual EnHandleResult OnClose(CONNID dwConnID)												     { return HR_IGNORE; }
		virtual EnHandleResult OnError(CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)   { return HR_IGNORE; }

	private:
		Listener *m_pListener;
	};

	typedef struct IDMatch
	{
		CONNID dwRCID;
		CONNID dwConnID;
	}IDMATCH,*IDMATCHPTR;

	class RobotNet
	{
	public:
		RobotNet(Listener *pListener)
			: m_AgentListener(pListener)
			, m_pAgent(&m_AgentListener)
			, m_vIDMap()
			, m_mutex_idmap(CreateMutex(NULL,FALSE,NULL))
			, m_packetID(0)
		{}

		virtual ~RobotNet(){ m_pAgent->Stop(); }

		BOOL StartUp(LPCTSTR pszBindAddress);
		BOOL ConnectRC(LPCTSTR pszRCAddress, USHORT usTargetPort, CONNID dwRCID);
		BOOL SendTargets(CONNID dwRCID, Target *pTargets, unsigned uNum);

	private:
		AgentListener m_AgentListener;
		CTcpAgentPtr m_pAgent;

		vector<IDMATCH> m_vIDMap;
		HANDLE m_mutex_idmap;

		USHORT m_packetID;
		USHORT GeneratePacketID(){ return ++m_packetID; }

		BOOL Bale(string &str)
		{
			string sBuffer("\x02");
			USHORT id = GeneratePacketID();
			sBuffer += id / 1000 + 0x30;
			sBuffer += id / 100%10 + 0x30;
			sBuffer += id / 10 % 10 + 0x30;
			sBuffer += id % 10 + 0x30;
			sBuffer += str.length() / 1000 + 0x30;
			sBuffer += str.length() / 100 % 10 + 0x30;
			sBuffer += str.length() / 10 % 10 + 0x30;
			sBuffer += str.length() % 10 + 0x30;
			sBuffer += str;
			str = sBuffer;
			str += "\xFF\xFF\x03";
			return TRUE;
		}
	};

}