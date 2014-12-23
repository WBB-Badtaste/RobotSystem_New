#pragma once

#include <string>
#include <vector>
#include <atlstr.h>
#include "Helper.h"
#include "BackstageInterface.h"

namespace robot
{
	using namespace std;

	static int index_RC=0;
	static vector<Target> vecNewTargets;
	static vector<AllocatedInfo> vecSendInfos;
	static vector<AllocatedInfo> vecAllocatedInfos;
	static HANDLE mutex_AllocatedTarget=0;
	static HANDLE mutex_newTarget=0;
	static HANDLE hThreadAllocate=0;
	static bool allocater_isStarted=false;

	int Allocater_AddNewTargets(Target *targets,int num);
}
