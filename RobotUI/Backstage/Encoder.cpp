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
		encoderRes=p9014_close();
		I32 CardCount = 0;
		encoderRes=p9014_initial(&CardCount, cardIDs);
		if (CardCount<=0) 
		{
			ReleaseMutex(g_mutex);
			return ERROR_ENCODER_STARTUP_MISSPCI9014;
		}
		while(CardCount-->0)
		{
			encoderRes=p9014_set_pls_iptmode(cardIDs[CardCount] * 4 + 0, 0);
			encoderRes=p9014_set_pls_iptmode(cardIDs[CardCount] * 4 + 1, 0);
			encoderRes=p9014_set_pls_iptmode(cardIDs[CardCount] * 4 + 2, 0);
			encoderRes=p9014_set_pls_iptmode(cardIDs[CardCount] * 4 + 3, 0);
			encoderRes=p9014_set_pos(cardIDs[CardCount] * 4 + 0, 1, 0);
			encoderRes=p9014_set_pos(cardIDs[CardCount] * 4 + 1, 1, 0);
			encoderRes=p9014_set_pos(cardIDs[CardCount] * 4 + 2, 1, 0);
			encoderRes=p9014_set_pos(cardIDs[CardCount] * 4 + 3, 1, 0);
		}
		ReleaseMutex(g_mutex);
		encoder_isStarted=true;
		return 0;
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
		if (!encoder_isStarted)	return ERROR_ENCODER_STARTUP_FAILED;
		WaitForSingleObject(g_mutex, INFINITE);
		if (p9014_get_pos(cardIDs[0] * 4 + axis_no, 1, value))
		{
			ReleaseMutex(g_mutex);
			return 1;
		}
		ReleaseMutex(g_mutex);
		return 0;
	}
}

