//---------------------------------------------------------------------------
#pragma once
#ifndef DisplayPairDoseH
#define DisplayPairDoseH

#include "IObserver.h"
#include "HandledPairDose.h"
#include "doseshell.h"
#include "Util.h"

//-----------------------Class:DisplayPairDose----------------------------
class DisplayPairDose:public IObserver{
private:
  Dose* measureDisplayDose;
  Dose* calcDisplayDose;

  Dose* NormMeasureDisplayDose;
  Dose* NormCalcDisplayDose;
public:
  /*Constructor*/
  DisplayPairDose();

  /*Destructor*/
  ~DisplayPairDose();

  /*Copy Constructor*/
  DisplayPairDose(const DisplayPairDose &r);

  /*Overload operator = */
  DisplayPairDose operator = (const DisplayPairDose &r);
public:
  void update(Message_Notify message);
public:
  /*Get and Set*/
  Dose* getMeasureDisplayDose();
  void setMeasureDisplayDose(Dose& r);
  Dose copyMeasureDisplayDose();
  void allocateMeasureDisplayDose();
  void cleanMeasureDisplayDose();

  Dose* getCalcDisplayDose();
  void setCalcDisplayDose(Dose& r);
  Dose copyCalcDisplayDose();
  void allocateCalcDisplayDose();
  void cleanCalcDisplayDose();

  Dose* getNormMeasureDisplayDose();
  void setNormMeasureDisplayDose(Dose& r);
  Dose copyNormMeasureDisplayDose();
  void allocateNormMeasureDisplayDose();
  void cleanNormMeasureDisplayDose();

  Dose* getNormCalcDisplayDose();
  void setNormCalcDisplayDose(Dose& r);
  Dose copyNormCalcDisplayDose();
  void allocateNormCalcDisplayDose();
  void cleanNormCalcDisplayDose();

  /*Functions*/
  void MapCHECKMeasureBlineInterpolation();   //˫���Բ�ֵ
  void MapCHECKMeasureInterpolationX();  //��x�����ֵ
  void MapCHECKMeasureInterpolationY();  //��y�����ֵ

  void dataEnhance();
  void smoothing();

private:
  inline bool FindFourBasePoints(int x,int y,std::vector<int> positiveSlopeSeries,std::vector<int> negativeSlopeSeries,MatrixData<int>& result); //����MapCHECK������̽�������У���˫���Բ�ֵ��Ϊÿ������ֵ���ҵ�4����ֵ����
  inline void neighbor(int num,std::vector<int> Series,int start,int end,int* result); //���ڶ�б��Ϊ1��-1��̽���������ߴ����ҵ�����ֵ���������ڵ�����б̽������(̽�����պ���������б̽������֮��)


  void MapCHECKMeasureBlineInterpolation(Dose* dose);
  void MapCHECKMeasureInterpolationX(Dose* dose);
  void MapCHECKMeasureInterpolationY(Dose* dose);
};
//---------------------------------------------------------------------------
#endif