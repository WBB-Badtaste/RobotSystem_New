//   2014/12/17
//   线程安全

#include "stdafx.h"
#include "Encoder.h"
#include "BackstageInterface.h"

namespace robot
{
	BACKSTAGE_API int WINAPI Encoder_Startup()
	{
		if (encoder_isStarted) return 0;
		WaitForSingleObject(g_mutex, INFINITE);
		p9014_close();
		I32 CardCount = 0;
		if (p9014_initial(&CardCount, &g_CardID)) goto F;
		if (p9014_set_pls_iptmode(g_CardID * 4 + 0, 0)) goto F;
		if (p9014_set_pls_iptmode(g_CardID * 4 + 1, 0)) goto F;
		if (p9014_set_pls_iptmode(g_CardID * 4 + 2, 0)) goto F;
		if (p9014_set_pls_iptmode(g_CardID * 4 + 3, 0)) goto F;
		if (p9014_set_pos(g_CardID * 4 + 0, 1, 0)) goto F;
		if (p9014_set_pos(g_CardID * 4 + 1, 1, 0)) goto F;
		if (p9014_set_pos(g_CardID * 4 + 2, 1, 0)) goto F;
		if (p9014_set_pos(g_CardID * 4 + 3, 1, 0)) goto F;
		ReleaseMutex(g_mutex);
		encoder_isStarted=true;
		return 0;
F:		ReleaseMutex(g_mutex);
		return 1;
	}
	BACKSTAGE_API int WINAPI Encoder_Shutdown()
	{
		if(!encoder_isStarted) return 0;
		WaitForSingleObject(g_mutex, INFINITE);
		if (p9014_close())
		{
			ReleaseMutex(g_mutex);
			return 1;
		}
		ReleaseMutex(g_mutex);
		encoder_isStarted = false;
		return 0;
	}
	BACKSTAGE_API int WINAPI Encoder_Read(int axis_no,int *value)
	{
		WaitForSingleObject(g_mutex, INFINITE);
		if (p9014_get_pos(g_CardID * 4 + axis_no, 1, value))
		{
			ReleaseMutex(g_mutex);
			return 1;
		}
		ReleaseMutex(g_mutex);
		return 0;
	}
}

