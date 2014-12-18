#pragma once

#include <vector>
#include "BackstageInterface.h"

namespace robot
{
	using namespace std;

	struct AllocatedInfo
	{
		int RCID;
		vector<Target> targets;
	};
}