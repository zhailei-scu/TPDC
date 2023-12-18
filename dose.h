//---------------------------------------------------------------------------
//Purpose:store the dose data
//Created by:huangning
//Time:2015/01/12
//---------------------------------------------------------------------------
#pragma once

#ifndef DoseH
#define DoseH

#include "Stdio.h"
#include "Util.h"
#include <vector>
#include <string>
#include <windows.h>
#include "thechangedll.h"
using namespace std;
#pragma comment(lib,"thechangedll.lib")

extern "C" __declspec(dllimport)bool __stdcall opennew(const char* filename);//读数据，同时赋值给frame(表示3d层数),row(行)，col（列）
extern "C" __declspec(dllimport)void __stdcall closenew(const char* filename);  //释放内存
extern "C" __declspec(dllimport)double* __stdcall ReadDatanew(int &frame,int& row,int& col);
extern "C" __declspec(dllimport)bool __stdcall ReadPixelSpacenew(double pixelspasing[2]);
extern "C" __declspec(dllimport)bool __stdcall ReadNormaPointnew(double npoint[3]);
extern "C" __declspec(dllimport)double __stdcall ReadDoseGridScalingnew();
extern "C" __declspec(dllimport)const char* __stdcall ReadDoseUnitsnew();
extern "C" __declspec(dllimport)bool __stdcall ReadOrgPointnew(double orgpoint[3]);
extern "C" __declspec(dllimport)const char* __stdcall ReadDoseTypenew();
extern "C" __declspec(dllimport)const char* __stdcall ReadDoseCommentsnew();
extern "C" __declspec(dllimport)const char* __stdcall ReadDoseSummationTypenew();
extern "C" __declspec(dllimport)DWORD __stdcall ReadNumberOfFramesnew();
extern "C" __declspec(dllimport)const char* __stdcall ReadGridFrameOffsetVectornew();

//-------------------------enum DoseType----------------------------------------
enum DoseType{
  DOSE_ABSOLUTE = 0,   //default
  DOSE_RELATIVE = 1,
};

//-------------------------Class:Dose----------------------------------------
class Dose{
private:
  /*read and writer lock;the details about the lock referenced in Util.h*/
  TRWLock rwLock;
private:
  MatrixData<double>* doseMatrix;

  string fileName;             //fileName for the dose Source
  FILETYPE fileType;          //indicate the fileType of the dose Source
  string doseUnit;
  double gridSizes[3]; //physic sizes between two neighbor points
  int segments[3];    //segments for grid density enhance

  PhysicalPoint doseCentral;      //physical aligment central
  GridPoint firstAlignmentCentral;//first aligment grid Central
  GridPoint boundaryPoints[8];//8 grid boundary points for a cubic

  DoseType doseType;     //dose type, identify these dose as a relative/absolute dose distribution
  bool doseInterploated; //default:fasle we notify that in some case, check software would ouput some interploated dose(mapCHECK in some case)
public:
  /*Constructor*/
  Dose();

  /*Copy Constructor*/
  Dose(Dose& r);

  /*Destructor*/
  ~Dose();

  /*Overload operation*/
  Dose operator = (Dose& r);

public:
  /*Get and Set:read/write safe*/
  MatrixData<double>* getDoseMatrix();
  void sync_setDoseMatrix( MatrixData<double>* _doseMatrix);

  void sync_allocateMatrix(int _rows,int _cols,int _heights);
  void sync_clearnMatrix();

  MatrixData<double> sync_copyDoseMatrix()throw(const char*);

  string sync_getFileName();
  void sync_setFileName(string fileName);

  FILETYPE sync_getFileType();
  void sync_setFileType(FILETYPE fileType);

  string sync_getDoseUnit();
  void sync_setDoseUnit(string doseUnit);

  double* getGridSizes();
  void sync_copyGridSizes(double resultGridSizes[3]);
  void sync_setGridSizes(double gridSize[3]);
  void sync_upDateGridSizes(double gridSizes[3]);

  int* getSegments();
  void sync_copySegments(int resultSegments[3]);
  void sync_setSegments(int segments[3]);

  PhysicalPoint* getDoseCentral();
  void sync_setDoseCentral(PhysicalPoint doseCentral);

  GridPoint* getFirstAlignmentCentral();
  void sync_setFirstAlignmentCentral(GridPoint firstAlignmentCentral);

  GridPoint* getBoundaryPoints();
  void sync_copyBoundaryPoints(GridPoint resultBoundaryPoints[8]);
  void sync_setBoundaryPoints(GridPoint boundaryPoints[8]);

  DoseType sync_getDoseType();        //Only get method

  bool sync_getDoseInterploated();     //Only get method
public:
  /*Get and Set:read/write unsafe*/
  void unSync_setDoseMatrix( MatrixData<double>* _doseMatrix);

  MatrixData<double> unSync_copyDoseMatrix()throw(const char*);

  void unSync_allocateMatrix(int _rows,int _cols,int _heights);
  void unSync_clearnMatrix();

  string unSync_getFileName();
  void unSync_setFileName(string fileName);

  FILETYPE unSync_getFileType();
  void unSync_setFileType(FILETYPE fileType);

  string unSync_getDoseUnit();
  void unSync_setDoseUnit(string doseUnit);

  void unSync_copyGridSizes(double resultGridSizes[3]);
  void unSync_setGridSizes(double gridSize[3]);
  void unSync_upDateGridSizes(double gridSizes[3]);

  void unSync_copySegments(int resultSegments[3]);
  void unSync_setSegments(int segments[3]);

  void unSync_setDoseCentral(PhysicalPoint doseCentral);

  void unSync_setFirstAlignmentCentral(GridPoint firstAlignmentCentral);

  void unSync_copyBoundaryPoints(GridPoint resultBoundaryPoints[8]);
  void unSync_setBoundaryPoints(GridPoint boundaryPoints[8]);

  DoseType unSync_getDoseType();     //Only get method

  bool unSync_getDoseInterploated();   //Only get method

public:
  /*Function*/
  bool loadDoseFile(string fileName,FILETYPE fileType)throw (const char*);
  bool loadDoseFile()throw (const char*);
  bool SaveDose();

private:

  /*read measurement file*/
  bool loadMapCHECKMeasureFile()throw (const char*);   //读MapCHECK测量数据文本文件
  bool loadZCMeasureFile()throw(const char*);         //读中测测量数据文本文件
  bool loadMatrixMeasureDoseFile()throw (const char*);    //读Matrix格式测量数据文件

  /*read calculate file*/
  bool loadDICOMCalcFile()throw(const char*);         //读DICOM计算文件
  bool loadSCUCalcFile()throw(const char*);           //读SCU计算文件

public:
  void sync_Read_Start();
  void sync_Write_Start();
  void sync_finish();
};










//-----------------------------Old One--------------------------------------
class TDose
{
public:
  /*Constructor:vars*/
  TDose(char *file,int ftype);

  /*Destructor*/
  ~TDose();

//inline float operator[](int ix);
//  TDose& operator=(TDose &);
  void SaveDose(char *file);
protected:
  //void GetArray(int filetype);   //得到探测器阵列
  bool LoadMapCHECKDose(char *file);  //读MapCHECK测量数据文本文件
  bool LoadZCDose(char *file);  //读中测测量数据文本文件
  bool LoadMatrixDose(char *file);  //读Matrix格式测量数据文件
  bool LoadDIDose(char *file);   //读DICOM文件，对齐时间距为1mm
  bool LoadDIDose(char *file, float hardwarepixel);  //多态，读DICOM文件，对齐时间距为用户自定义探测器间距（文件名,硬件上探测器间隔（像素大小)
  //void ReadDose(FILE *fp,int filetype);
  void BlineInterp();   //双线性插值
  inline int** FindFourBasePoints(int x,int y,std::vector<int> positiveSlopeSeries,std::vector<int> negativeSlopeSeries); //对于MapCHECK不规则探测器阵列，对双线性插值，为每个待插值点找到4个插值基点
  inline void neighbor(int num,std::vector<int> Series,int start,int end,int* result); //在众多斜率为1和-1的探测器排列线簇中找到待插值点所最相邻的两个斜探测器线(探测器刚好在这两个斜探测器线之间)
  void Interpolationx(int fftype);  //作x方向插值
  void Interpolationy(int fftype);  //作y方向插值
  //int detarray[45][45]; //用来记录每个点有无探测器
public:
  int lx,hx;  //X方向最小和最大的序号
  int ly,hy;  //y方向最小和最大的序号
  int lz,hz;  //z方向最小和最大的序号
  int nx,ny,nz; //x,y,z方向的数据点数
  int frame,row,col;  //DICOM文件中数据三维的层数，行数和列数
  const char* theunits;   //剂量单位
  int irange,jrange; //DICOM中映射到物理坐标之后的行数和列数
  int icenter,jcenter;  //映射之后对齐点（图像的几何中心）在物理坐标数组中的行和列(从0算起)
  int ifirst,jfirst;  //映射之后与与对齐点左下方第一个与探测器位置相应的点在物理坐标数组中的行和列(从0算起)，实际计算时
                      //是从这行开始算起对齐的
  double piexlspace[2],origin[3]; //DICOM文件中的像素和空间原点位置
public:
  char* fileName;
  int nData;    //总的数据点数
  float dosemax; //最大剂量
  float dosemin; //最小剂量(作图时有用)
  float *NormDose; //归一化剂量
  float *DoseAbs;    //绝对剂量

  int recordsegments;  //记录间隔
public:
  int cuthoriz[2],cutverit[2]; //去掉0.000000之后的四个边位置
};

float* __fastcall regularBinearInterploate(float *array,int &row,int &col,int multi);


float* __fastcall BicubicInterploate(float *array,int &row,int &col,int multi);
float __fastcall getBicubicValue(float u,float v,float B[4][4]);
float __fastcall getBicubicParam(float uorV);
float* GaussianSmoothingOrderThree(float* array,int row,int col);
float* GaussianSmoothingOrderFive(float* array,int row,int col);
float* midValueSmoothing(float* array,int row,int col,const int orders);
float* averageSmoothing(float* array,int row, int col,const int orders);
float* bilateralSmoothing(float* array,int row,int col);
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#endif

