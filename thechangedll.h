#ifndef THECHANGEDLL_H
#define THECHANGEDLL_H
#include "Windows.h"
extern "C" __declspec(dllexport)bool __stdcall opennew(const char* filename);  //���ļ�
extern "C" __declspec(dllexport)void __stdcall closenew(const char* filename);  //�ͷ��ڴ�
extern "C" __declspec(dllexport)double* __stdcall ReadDatanew(int &frame,int& row,int& col); //�����ݣ�ͬʱ��ֵ��frame(��ʾ3d����),row(��)��col���У�
extern "C" __declspec(dllexport)bool __stdcall ReadPixelSpacenew(double pixelspasing[2]);//������
extern "C" __declspec(dllexport)bool __stdcall ReadNormaPointnew(double npoint[3]); //����һ����
extern "C" __declspec(dllexport)double __stdcall ReadDoseGridScalingnew();//
extern "C" __declspec(dllexport)bool __stdcall ReadOrgPointnew(double orgpoint[3]);//
extern "C" __declspec(dllexport)const char* __stdcall ReadDoseUnitsnew(); 
extern "C" __declspec(dllexport)const char* __stdcall ReadDoseTypenew();
extern "C" __declspec(dllexport)const char* __stdcall ReadDoseCommentsnew();
extern "C" __declspec(dllexport)const char* __stdcall ReadDoseSummationTypenew();
extern "C" __declspec(dllexport)DWORD __stdcall ReadNumberOfFramesnew();
extern "C" __declspec(dllexport)const char* __stdcall ReadGridFrameOffsetVectornew();
#endif