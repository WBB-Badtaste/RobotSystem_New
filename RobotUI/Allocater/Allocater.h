// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ALLOCATER_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ALLOCATER_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef ALLOCATER_EXPORTS
#define ALLOCATER_API __declspec(dllexport)
#else
#define ALLOCATER_API __declspec(dllimport)
#endif

#include <vector>

struct Target
{
	unsigned short ID;///特征码，（其值为1~9999）
	double PosX;///横坐标，单位mm，精确到0.32mm
	double PosY;///纵坐标，单位mm，精确到0.32mm
	float Aangle;///旋转角度,精确到0.5度。平行X轴为0度，正值代表顺时针偏转，负值相反
	long EncoderValue;///编码器值，十位
	int RcID;
};

static std::vector<int> vecRC;
static int lastAllocatingRC=0;

EXTERN_C ALLOCATER_API int WINAPI Start(int rcs[],int num);

EXTERN_C ALLOCATER_API int WINAPI Allocate(Target targets[],int num);


