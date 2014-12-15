
// 此类是从 Encoder.dll 导出的
#ifndef __ENCODER_H__
#define __ENCODER_H__

#ifdef ENCODER_EXPORTS
#define ENCODER_API _declspec(dllexport) 
#else
#define ENCODER_API _declspec(dllimport) 
#endif

EXTERN_C ENCODER_API int WINAPI Encoder_Read(int axis_no, int *value);
EXTERN_C ENCODER_API int WINAPI Encoder_StartUp();
EXTERN_C ENCODER_API int WINAPI Encoder_Close();

#endif
