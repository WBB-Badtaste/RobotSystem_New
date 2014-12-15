/*	
 *	Copyright: ShenZhen BaiTaiYuan Tech Inc.
 *
 *	Version	 : 1.0
 *	Date	 : 2014-11-22
 *	Author	 : MartinWu(sos901012@gmail.com)
 *
 *	There is a Interface defining file for RobotNetwork base on HP-Socket.
 */

#pragma once


#ifdef ROBOTNETWORK_EXPORTS
#define ROBOTNETWORK_API __declspec(dllexport)
#else
#define ROBOTNETWORK_API __declspec(dllimport)
#endif

#include <winsock2.h>
namespace robot
{
	class Listener
	{
		public:
			ROBOTNETWORK_API Listener();
	};
	typedef struct Point
	{
		//单位mm，精确到0.32mm
		double x;
		double y;
	}POINT;
	typedef struct Target
	{
		USHORT		uID;//特征码，（其值为1~9999）
		POINT		position;
		float		angle;//旋转角度,精确到0.5度。平行X轴为0度，正值代表顺时针偏转，负值相反
		long		encoderValue;//编码器值，十位
	}TARGET, *TARGETPRT;
	EXTERN_C ROBOTNETWORK_API int WINAPI StartUp(LPCTSTR pszBindAddress, Listener *pListener);
	EXTERN_C ROBOTNETWORK_API int WINAPI Shutdown();
	EXTERN_C ROBOTNETWORK_API int WINAPI ConnectRC(LPCTSTR pszRCAddress, USHORT usTargetPort, USHORT dwRCID);
	EXTERN_C ROBOTNETWORK_API int WINAPI SendTargets(USHORT dwRCID, TARGETPRT pTargets, unsigned uNum);
}