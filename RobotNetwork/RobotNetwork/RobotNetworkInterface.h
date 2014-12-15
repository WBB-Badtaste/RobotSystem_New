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
		//��λmm����ȷ��0.32mm
		double x;
		double y;
	}POINT;
	typedef struct Target
	{
		USHORT		uID;//�����룬����ֵΪ1~9999��
		POINT		position;
		float		angle;//��ת�Ƕ�,��ȷ��0.5�ȡ�ƽ��X��Ϊ0�ȣ���ֵ����˳ʱ��ƫת����ֵ�෴
		long		encoderValue;//������ֵ��ʮλ
	}TARGET, *TARGETPRT;
	EXTERN_C ROBOTNETWORK_API int WINAPI StartUp(LPCTSTR pszBindAddress, Listener *pListener);
	EXTERN_C ROBOTNETWORK_API int WINAPI Shutdown();
	EXTERN_C ROBOTNETWORK_API int WINAPI ConnectRC(LPCTSTR pszRCAddress, USHORT usTargetPort, USHORT dwRCID);
	EXTERN_C ROBOTNETWORK_API int WINAPI SendTargets(USHORT dwRCID, TARGETPRT pTargets, unsigned uNum);
}