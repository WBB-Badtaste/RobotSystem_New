
#ifdef VIRTUALVISION_EXPORTS
#define VIRTUALVISION_API __declspec(dllexport)
#else
#define VIRTUALVISION_API __declspec(dllimport)
#endif

#pragma comment(lib,"Backstage.lib")
// �����Ǵ� VirtualVision.dll ������
namespace robot
{
	EXTERN_C VIRTUALVISION_API int WINAPI VirtualVision_Start();
	EXTERN_C VIRTUALVISION_API int WINAPI VirtualVision_Stop();
}
