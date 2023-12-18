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

extern "C" __declspec(dllimport)bool __stdcall opennew(const char* filename);//�����ݣ�ͬʱ��ֵ��frame(��ʾ3d����),row(��)��col���У�
extern "C" __declspec(dllimport)void __stdcall closenew(const char* filename);  //�ͷ��ڴ�
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
  bool loadMapCHECKMeasureFile()throw (const char*);   //��MapCHECK���������ı��ļ�
  bool loadZCMeasureFile()throw(const char*);         //���в���������ı��ļ�
  bool loadMatrixMeasureDoseFile()throw (const char*);    //��Matrix��ʽ���������ļ�

  /*read calculate file*/
  bool loadDICOMCalcFile()throw(const char*);         //��DICOM�����ļ�
  bool loadSCUCalcFile()throw(const char*);           //��SCU�����ļ�

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
  //void GetArray(int filetype);   //�õ�̽��������
  bool LoadMapCHECKDose(char *file);  //��MapCHECK���������ı��ļ�
  bool LoadZCDose(char *file);  //���в���������ı��ļ�
  bool LoadMatrixDose(char *file);  //��Matrix��ʽ���������ļ�
  bool LoadDIDose(char *file);   //��DICOM�ļ�������ʱ���Ϊ1mm
  bool LoadDIDose(char *file, float hardwarepixel);  //��̬����DICOM�ļ�������ʱ���Ϊ�û��Զ���̽������ࣨ�ļ���,Ӳ����̽������������ش�С)
  //void ReadDose(FILE *fp,int filetype);
  void BlineInterp();   //˫���Բ�ֵ
  inline int** FindFourBasePoints(int x,int y,std::vector<int> positiveSlopeSeries,std::vector<int> negativeSlopeSeries); //����MapCHECK������̽�������У���˫���Բ�ֵ��Ϊÿ������ֵ���ҵ�4����ֵ����
  inline void neighbor(int num,std::vector<int> Series,int start,int end,int* result); //���ڶ�б��Ϊ1��-1��̽���������ߴ����ҵ�����ֵ���������ڵ�����б̽������(̽�����պ���������б̽������֮��)
  void Interpolationx(int fftype);  //��x�����ֵ
  void Interpolationy(int fftype);  //��y�����ֵ
  //int detarray[45][45]; //������¼ÿ��������̽����
public:
  int lx,hx;  //X������С���������
  int ly,hy;  //y������С���������
  int lz,hz;  //z������С���������
  int nx,ny,nz; //x,y,z��������ݵ���
  int frame,row,col;  //DICOM�ļ���������ά�Ĳ���������������
  const char* theunits;   //������λ
  int irange,jrange; //DICOM��ӳ�䵽��������֮�������������
  int icenter,jcenter;  //ӳ��֮�����㣨ͼ��ļ������ģ����������������е��к���(��0����)
  int ifirst,jfirst;  //ӳ��֮�������������·���һ����̽����λ����Ӧ�ĵ����������������е��к���(��0����)��ʵ�ʼ���ʱ
                      //�Ǵ����п�ʼ��������
  double piexlspace[2],origin[3]; //DICOM�ļ��е����غͿռ�ԭ��λ��
public:
  char* fileName;
  int nData;    //�ܵ����ݵ���
  float dosemax; //������
  float dosemin; //��С����(��ͼʱ����)
  float *NormDose; //��һ������
  float *DoseAbs;    //���Լ���

  int recordsegments;  //��¼���
public:
  int cuthoriz[2],cutverit[2]; //ȥ��0.000000֮����ĸ���λ��
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

