#pragma once

namespace robot
{
	static Target *referTargets=nullptr;
	static int referNum=0;
	static double threshold=0;
	static double encoderRate=1;
	int Filter_HandleObjects(Target *targets,int *num);
	int Filter_CleanRefer();
	int Filter_SetThreshold(double vlaue);
}
