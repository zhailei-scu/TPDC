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
class TDICheck      //��ӦDICOM
{
public:
  TDICheck(TDose *md,TDose *di,StandardParam theStandard); //NormType:0(default)  ��Ĭ�ϣ�Ĭ������£�DICOM����֮��ѡ��������ֵ����Ϊ��һ���㣨������������ʱѡ��DICOM�ж�������ĵ������Ϊ���ֵ������������ͬ����Ҫ���ڲ���ƽ����ѡȡ���ֵ��Ϊ��һ����(���ֵΪ100%)������ѡ��DICOM�ж�������ĵ������Ϊ���ֵ��̫��ѧ(����˵DICOM���ĵ㴦��ֵΪ���ֵ��10%����ô���������Ϊ��һ���ĵ㣬��ôDICOMƽ�����кܶ����Լ����ᳬ��100%�����ֵ����Լ�����ﵽ1000%��������Ϊ����������ƽ���һ���Ľ��������󣬲����޴����)��
  ~TDICheck();                                             // 1   �����û���ѡ�Ĺ�һ����
public:                                                    // 2   BestFive
  float M_RM,M_DM,M_TH;   //M_RM���û��趨��GAMA��׼�еİ뾶ֵ
                     //M_DM���û��趨��GAMA��׼�еİٷ����
  int isdetpass[45][45];   //̽�����Ƿ�������ֵ����
  int totaldet;     //���������������������м�����֤��̽��������
  float *M_GAMA,*Dta,*DD;  //gama����,DTA��Dosedifference
private:
  TDose *pmead;  //�������ղ���������Ϣ
  TDose *pdi;  //��������DICOM������Ϣ
  float *m_DOSE;  //��һ��֮��Ĳ���ֵ
  float *M_DC;     //��������ӳ��͹�һ��֮���DICOM����ֵ
  //int detectorinfo[45][45];  //̽����������Ϣ
  int Nz,Ny,Nx;  //��������ӳ��͹�һ��֮���DICOM����ֵ�������ϵĵ���
  int nnx,nny;
  //void GetArrayinfo();
  //void startDIJob(CheckChoose theChoose);

  //CheckResult* startDIJob_best5(CheckChoose theChoose);  //��������Gammaͨ���ʵ�5����
  void getgama();
 // void findpassdet(); //Ѱ��ͨ����ֵTH��̽������
};
//---------------------------------------------------------------------------
class TDoseCheck        //��Ӧ����ʦ�İ汾
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
  TDose *pmd;      //����������ָ��
  TDose *pcd;      //���������ָ��
  TDoseConfig *pcfg;//�������ָ��
  TDistance *SetRCUT;

  float *m_x;    //̽��������ֵ
  float *m_y;
//  float *m_z;
  float *DOSE;//���ڽ��մ�dose.cpp�д�����dose0.dat��dose1.dat�ļ��м���ֵ
  float *m_DOSE;
  float *M_DC;
  float *d;

  float *x_M,*y_M;  //ϸ����Ԫ������ֵ
  float *Factor0,*Factor2,*Factor4,*Factor6;
  float *m_Rtrack; //Randomcheckʱ��¼����������λ��

  int NVP;  //̽�����ܵ���
  int N;  //ϸ����Ԫ����
  int Nz,Ny,Nx;  //���������ϵĵ���
  float M_RCUT;
  float m_lenx,m_leny,m_lenz,m_lenmx,m_lenmy,m_lenmz,M_lenx0,M_leny0,M_lenz0;
  int m_maxn;      //̽������������
  int m_lx,m_hx,m_ly,m_hy,m_lz,m_hz;
  float dosemax0,dosemax1,dosemax2;//�ֱ�dose0,dose1�Լ����߹�ͬ�����ֵ
  float detpassTH;      //���õ�̽����ͨ����ֵ

public:
  float dtamin,gamamin,ddmin;      //dta,gama���Ӻ�dd����Сֵ
  float *M_GAMA,*Dta,*DD;  //gama����,DTA��Dosedifference
  float *M_RGAMA,*RDta; //random
  float M_RM,M_DM;   //M_RM���û��趨��GAMA��׼�еİ뾶ֵ(��λcm)��ƽ��
                     //M_DM���û��趨��GAMA��׼�еİٷ�����ƽ��
};
//---------------------------------------------------------------------------
#endif