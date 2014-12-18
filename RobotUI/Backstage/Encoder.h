#pragma once

#include "Pci9014.h"
#pragma comment(lib,"Pci9014.lib")

namespace robot
{
	static I32 g_CardID = 0;
	static HANDLE g_mutex = CreateMutex(NULL,FALSE,NULL);
	static bool encoder_isStarted=false;
}