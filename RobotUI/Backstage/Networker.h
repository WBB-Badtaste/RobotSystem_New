#pragma once

#include <string>
#include <vector>
#include <atlstr.h>
#include "HPSocket.h"
#pragma comment(lib,"HPSocket.lib")

namespace robot
{
	using namespace std;
	class MyListener:public ITcpAgentListener
	{
		virtual EnHandleResult OnReceive(CONNID dwConnID, int iLength)								     ;
		virtual EnHandleResult OnReceive(CONNID dwConnID, const BYTE* pData, int iLength)			     ;
		virtual EnHandleResult OnSend(CONNID dwConnID, const BYTE* pData, int iLength)				     ;
		virtual EnHandleResult OnPrepareConnect(CONNID dwConnID, SOCKET socket)						     ;
		virtual EnHandleResult OnConnect(CONNID dwConnID)											     ;
		virtual EnHandleResult OnAgentShutdown()													     ;
		virtual EnHandleResult OnClose(CONNID dwConnID)												     ;
		virtual EnHandleResult OnError(CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)   ;
	};
	static bool netWorker_isStarted=false;
	static MyListener listener;
	static CTcpAgentPtr pAgent(&listener);
	static vector<CONNID> rcIDmatchConnID;
	static HANDLE mutex_connid=0;
	static USHORT packetID;
	static USHORT GeneratePacketID(){ return ++packetID; }
	static void Bale(string &str)
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
	}	
}