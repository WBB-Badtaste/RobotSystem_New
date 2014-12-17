// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ALLOCATER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ALLOCATER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef ALLOCATER_EXPORTS
#define ALLOCATER_API __declspec(dllexport)
#else
#define ALLOCATER_API __declspec(dllimport)
#endif

#include <vector>

struct Target
{
	unsigned short ID;///�����룬����ֵΪ1~9999��
	double PosX;///�����꣬��λmm����ȷ��0.32mm
	double PosY;///�����꣬��λmm����ȷ��0.32mm
	float Aangle;///��ת�Ƕ�,��ȷ��0.5�ȡ�ƽ��X��Ϊ0�ȣ���ֵ����˳ʱ��ƫת����ֵ�෴
	long EncoderValue;///������ֵ��ʮλ
	int RcID;
};

static std::vector<int> vecRC;
static int lastAllocatingRC=0;

EXTERN_C ALLOCATER_API int WINAPI Start(int rcs[],int num);

EXTERN_C ALLOCATER_API int WINAPI Allocate(Target targets[],int num);


