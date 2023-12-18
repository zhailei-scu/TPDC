//---------------------------------------------------------------------------
//Purpose:calculation about the dose check
//Created by:huangning
//Created time:2015/01/12
//---------------------------------------------------------------------------
#ifndef CheckH
#define CheckH
#include "dose.h"
#include "DoseConfig.h"
#include "Distance.h"
#include "CheckRecord.h"
#include "Util.h"
#include <list>
#include <vector>

using namespace std;

//----------------------------Class:DoseCheck---------------------------------
class DoseCheck{
private:
  CheckedRecord checkedRecord;
  StandardParam standardParam;

public:
  /*Constructor*/
  DoseCheck();
  /*Destructor*/
  ~DoseCheck();
  /*Copy Constructor*/
  DoseCheck(const DoseCheck &r);
  /*Overload operator =*/
  DoseCheck operator = (const DoseCheck &r);

public:
  void check(CHECKTYPE checkType);
  void check(CHECKTYPE checkType,GridPoint normPoint);
  void reset();

  CheckedRecord* getCheckedRecord();
  CheckedRecord  copyCheckedRecord();

  StandardParam* getStandardParam();
  StandardParam copyStandardParam();
  void setStandardParam(StandardParam& _standardParam);

private:
  void doseDifferenceCheck();
  void gammaCheck(CHECKTYPE checkType);
  void dtaCheck_FloatWay(CHECKTYPE checkType);
  void dtaCheck_MidValueWay(CHECKTYPE checkType);
  void dtaCheck_SamePositionWay(CHECKTYPE checkType);

  //void bestFive_DDCheck(CHECKTYPE checkType);
  void bestFive_Abs_DTACheck();
  void bestFive_Abs_GammaCheck();
  void bestFive_Rel_DTACheck();
  void bestFive_Rel_GammaCheck();

private:
  void dtaCheck_FloatWay(CHECKTYPE checkType,GridPoint normPoint);
  void dtaCheck_MidValueWay(CHECKTYPE checkType,GridPoint normPoint);
  void dtaCheck_SamePositionWay(CHECKTYPE checkType,GridPoint normPoint);

  void doseDifferenceCheck(GridPoint normPoint);
  void gammaCheck(CHECKTYPE checkType,GridPoint normPoint);

private:
  void doseDifferenceCheck(Dose* measureDose,Dose* NormMeasureDose,Dose* calcDose,Dose* NormCalcDose,HANDLE_MODEL handle_model);

  void dtaCheck_FloatWay(CHECKTYPE checkType,Dose* NormMeasureDose,Dose* NormCalcDose,HANDLE_MODEL handle_model);

  void dtaCheck_MidValueWay(CHECKTYPE checkType,Dose* measureDose,Dose* calcDose,HANDLE_MODEL handle_model);

  void dtaCheck_SamePositionWay(CHECKTYPE checkType,Dose* NormMeasureDose,Dose* NormCalcDose,HANDLE_MODEL handle_model);

  void gammaCheck(CHECKTYPE checkType,Dose* measureDose,Dose* calcDose,HANDLE_MODEL handle_model);

  vector< pair<double,GridPoint> > presort(int rowRadius,int colRadius,double rowGridSize,double colGridSize);

  bool getInnerPoint(int outX,int outY,int& innerX,int& innerY,int halfWidth);

  void CalcIndices(int& rowSubIndex,int& colSubIndex);

  double DTAValueCalculate(double measureValue,MatrixData<double>* calcMatarix,
                           int cCentralRowPos,int cCentralColPos,int searchingRowPos,int searchingColPos,double distanceStandard);

};


//-------------------------------Old One-----------------------------
class TDICheck      //适应DICOM
{
public:
  TDICheck(TDose *md,TDose *di,StandardParam theStandard); //NormType:0(default)  （默认）默认情况下，DICOM对齐之后，选择剂量最大值点作为归一化点（这与中期验收时选择DICOM中对齐后中心点剂量作为最大值的做法有所不同，主要由于测量平面中选取最大值作为归一化点(最大值为100%)，所以选择DICOM中对齐后中心点剂量作为最大值不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)）
  ~TDICheck();                                             // 1   按照用户所选的归一化点
public:                                                    // 2   BestFive
  float M_RM,M_DM,M_TH;   //M_RM即用户设定的GAMA标准中的半径值
                     //M_DM即用户设定的GAMA标准中的百分误差
  int isdetpass[45][45];   //探测器是否满足阈值条件
  int totaldet;     //满足条件，将会用来进行剂量验证的探测器总数
  float *M_GAMA,*Dta,*DD;  //gama因子,DTA和Dosedifference
private:
  TDose *pmead;  //用来接收测量数据信息
  TDose *pdi;  //用来接收DICOM数据信息
  float *m_DOSE;  //归一化之后的测量值
  float *M_DC;     //经过坐标映射和归一化之后的DICOM计算值
  //int detectorinfo[45][45];  //探测器阵列信息
  int Nz,Ny,Nx;  //经过坐标映射和归一化之后的DICOM计算值各方向上的点数
  int nnx,nny;
  //void GetArrayinfo();
  //void startDIJob(CheckChoose theChoose);

  //CheckResult* startDIJob_best5(CheckChoose theChoose);  //计算出最佳Gamma通过率的5个点
  void getgama();
 // void findpassdet(); //寻找通过阈值TH的探测器点
};
//---------------------------------------------------------------------------
class TDoseCheck        //适应侯老师的版本
{
public:
  TDoseCheck(TDose *md,TDose *cd,TDoseConfig *cg,TDistance *setrcut,float a,float b,float th);
  ~TDoseCheck();

  void StartJob();
private:
  void Check();
  void SaveGamaResult(char *file);
  void SaveDdResult(char *file);
  void SaveDtaResult(char *file);
  TDose *pmd;      //测量剂量类指针
  TDose *pcd;      //计算剂量类指针
  TDoseConfig *pcfg;//计算参数指针
  TDistance *SetRCUT;

  float *m_x;    //探测器坐标值
  float *m_y;
//  float *m_z;
  float *DOSE;//用于接收从dose.cpp中传来的dose0.dat和dose1.dat文件中剂量值
  float *m_DOSE;
  float *M_DC;
  float *d;

  float *x_M,*y_M;  //细化单元的坐标值
  float *Factor0,*Factor2,*Factor4,*Factor6;
  float *m_Rtrack; //Randomcheck时记录被检查点的相对位置

  int NVP;  //探测器总点数
  int N;  //细化单元总数
  int Nz,Ny,Nx;  //各个方向上的点数
  float M_RCUT;
  float m_lenx,m_leny,m_lenz,m_lenmx,m_lenmy,m_lenmz,M_lenx0,M_leny0,M_lenz0;
  int m_maxn;      //探测器点数上限
  int m_lx,m_hx,m_ly,m_hy,m_lz,m_hz;
  float dosemax0,dosemax1,dosemax2;//分别dose0,dose1以及两者共同的最大值
  float detpassTH;      //设置的探测器通过阈值

public:
  float dtamin,gamamin,ddmin;      //dta,gama因子和dd的最小值
  float *M_GAMA,*Dta,*DD;  //gama因子,DTA和Dosedifference
  float *M_RGAMA,*RDta; //random
  float M_RM,M_DM;   //M_RM即用户设定的GAMA标准中的半径值(单位cm)的平方
                     //M_DM即用户设定的GAMA标准中的百分误差的平方
};
//---------------------------------------------------------------------------
#endif