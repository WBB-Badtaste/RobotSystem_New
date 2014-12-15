// Encoder.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Encoder.h"

static I32 g_CardID = 0;
static BOOL g_bStarted = FALSE;
static HANDLE g_mutex = CreateMutex(NULL,FALSE,NULL);

ENCODER_API int WINAPI Encoder_StartUp()
{
	WaitForSingleObject(g_mutex, INFINITE);
	if (g_bStarted) goto T;
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
	g_bStarted = TRUE;
T:	ReleaseMutex(g_mutex);
	return 0;
F:	ReleaseMutex(g_mutex);
	return 1;
}

ENCODER_API int WINAPI Encoder_Close()
{
	WaitForSingleObject(g_mutex, INFINITE);
	if (p9014_close())
	{
		ReleaseMutex(g_mutex);
		return 1;
	}
	g_bStarted = FALSE;
	ReleaseMutex(g_mutex);
	return 0;
}

ENCODER_API int WINAPI Encoder_Read(int axis_no,int *value)
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
