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
  void MapCHECKMeasureBlineInterpolation();   //双线性插值
  void MapCHECKMeasureInterpolationX();  //作x方向插值
  void MapCHECKMeasureInterpolationY();  //作y方向插值

  void dataEnhance();
  void smoothing();

private:
  inline bool FindFourBasePoints(int x,int y,std::vector<int> positiveSlopeSeries,std::vector<int> negativeSlopeSeries,MatrixData<int>& result); //对于MapCHECK不规则探测器阵列，对双线性插值，为每个待插值点找到4个插值基点
  inline void neighbor(int num,std::vector<int> Series,int start,int end,int* result); //在众多斜率为1和-1的探测器排列线簇中找到待插值点所最相邻的两个斜探测器线(探测器刚好在这两个斜探测器线之间)


  void MapCHECKMeasureBlineInterpolation(Dose* dose);
  void MapCHECKMeasureInterpolationX(Dose* dose);
  void MapCHECKMeasureInterpolationY(Dose* dose);
};
//---------------------------------------------------------------------------
#endif