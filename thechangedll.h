#ifndef THECHANGEDLL_H
#define THECHANGEDLL_H
#include "Windows.h"
extern "C" __declspec(dllexport)bool __stdcall opennew(const char* filename);  //打开文件
extern "C" __declspec(dllexport)void __stdcall closenew(const char* filename);  //释放内存
extern "C" __declspec(dllexport)double* __stdcall ReadDatanew(int &frame,int& row,int& col); //读数据，同时赋值给frame(表示3d层数),row(行)，col（列）
extern "C" __declspec(dllexport)bool __stdcall ReadPixelSpacenew(double pixelspasing[2]);//读像素
extern "C" __declspec(dllexport)bool __stdcall ReadNormaPointnew(double npoint[3]); //读归一化点
extern "C" __declspec(dllexport)double __stdcall ReadDoseGridScalingnew();//
extern "C" __declspec(dllexport)bool __stdcall ReadOrgPointnew(double orgpoint[3]);//
extern "C" __declspec(dllexport)const char* __stdcall ReadDoseUnitsnew(); 
extern "C" __declspec(dllexport)const char* __stdcall ReadDoseTypenew();
extern "C" __declspec(dllexport)const char* __stdcall ReadDoseCommentsnew();
extern "C" __declspec(dllexport)const char* __stdcall ReadDoseSummationTypenew();
extern "C" __declspec(dllexport)DWORD __stdcall ReadNumberOfFramesnew();
extern "C" __declspec(dllexport)const char* __stdcall ReadGridFrameOffsetVectornew();
#endif