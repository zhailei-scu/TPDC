//---------------------------------------------------------------------------
#pragma once
#ifndef HandledPairDoseH
#define HandledPairDoseH

#include "IObserver.h"
#include "Util.h"
#include "cache.h"

//-----------------------------------------------------------------------------
enum NORMLIZE_TYPE{
  //Abs: the measure plan and the calculate plan use same normlization value
  //Rel: the measure plan and the calculate plan use two different normlization values(but in same position)
  NORM_DOUBLE_Abs = 1,
  NORM_DOUBLE_Rel = 2,
  
  NORM_SINGLE_MEASUREMENT_Abs_or_Rel = 3,

  NORM_SINGLE_CALCULATION_Abs = 4,
  NORM_SINGLE_CALCULATION_Rel = 5,
};

//----------------------------Class:HandledPairDose----------------------------

class HandledPairDose :public IObserver{
private:
  Dose* measureDoseHandled;
  Dose* calculateDoseHandled;

  //measure norm
  Dose* NormMeasureDoseHandled;


  //calculate norm
  //absolute
  Dose* Abs_NormCalculateDoseHandled;
  //relative
  Dose* Rel_NormCalculateDoseHandled;

  PhysicalPoint NormlizationPosition_Measure;
  PhysicalPoint NormlizationPosition_Calculate;

  NORMLIZE_TYPE normlize_Type;

  GridPoint offsetPoint;

  bool manualSpecialMeasureNormValue;
  bool manualSpecialCalcNormValue;

  string normValueStr_measure;
  string normValueStr_calculate;
public:
  /*Constructor*/
  HandledPairDose();
  /*Destructor*/
  ~HandledPairDose();
  /*Copy Constructor*/
  HandledPairDose(const HandledPairDose& r);
  /*Overload operator = */
  HandledPairDose operator = (const HandledPairDose& r);

  void update(Message_Notify message);
public:

  Dose* getMeasureDoseHandled();
  void setMeasureDoseHandled(Dose& r);
  Dose copyMeasureDoseHandled();
  void allocateMeasureDoseHandled();
  void cleanMeasureDoseHandled();

  Dose* getCalculateDoseHandled();
  void setCalculateDoseHandled(Dose& r);
  Dose copyCalculateDoseHandled();
  void allocateCalculateDoseHandled();
  void cleanCalculateDoseHandled();

  //measure norm
  Dose* getNormMeasureDoseHandled();
  void setNormMeasureDoseHandled(Dose& r);
  Dose copyNormMeasureDoseHandled();
  void allocateNormMeasureDoseHandled();
  void cleanNormMeasureDoseHandled();

  //calculate norm
  //absoulte
  Dose* getAbs_NormCalculateDoseHandled();
  void setAbs_NormCalculateDoseHandled(Dose& r);
  Dose copyAbs_NormCalculateDoseHandled();
  void allocateAbs_NormCalculateDoseHandled();
  void cleanAbs_NormCalculateDoseHandled();
  //relative
  Dose* getRel_NormCalculateDoseHandled();
  void setRel_NormCalculateDoseHandled(Dose& r);
  Dose copyRel_NormCalculateDoseHandled();
  void allocateRel_NormCalculateDoseHandled();
  void cleanRel_NormCalculateDoseHandled();


  bool getManualSpecialMeasureNormValue();
  bool getManualSpecialCalcNormValue();

  string getNormValueStr_measure();
  string getNormValueStr_calculate();
  
public:
  void Notify(Message_Notify message);
  void AddObserver(IObserver *pObserver);
  void DeleteObserver(IObserver *pObserver);

public:
  /*Functions*/

  GridPoint getOffsetPoint();
  void setOffsetPoint(GridPoint _offsetPoint);


  PhysicalPoint* getNormlizationPosition_Measure();  //Only get method
  PhysicalPoint* getNormlizationPosition_Calculate(); //Only get method

  PhysicalPoint copyNormlizationPosition_Measure();
  PhysicalPoint copyNormlizationPosition_Calculate();

  NORMLIZE_TYPE getNormlize_Type();          //Only get method

  bool normlize(NORMLIZE_TYPE normlize_Type,HANDLE_MODEL handel_Model);

  bool normlize(NORMLIZE_TYPE normlize_Type,GridPoint _normPoint,HANDLE_MODEL handel_Model);

  bool normlize_ActualValue(NORMLIZE_TYPE normlize_Type,double normlizeValue,HANDLE_MODEL handel_Model);

  bool normlize_PercentValue(NORMLIZE_TYPE normlize_Type,double normlizeValue_Percente,HANDLE_MODEL handel_Model);

  bool normlize(NORMLIZE_TYPE normlize_Type,PhysicalPoint _normPoint);

  bool alignmentAndSegments_Abs();

  
private:
  bool unSync_Normlize(Dose* sourceDose,Dose* destinct,double normlizeValue,HANDLE_MODEL handel_Model);

  GridPoint getCorrespondingPointInCalcPlan(Dose* measure,Dose* calc,GridPoint point);
  GridPoint getCorrespondingPointInCalcPlan_And_Adjust(Dose* measure,Dose* calc,GridPoint point);

  PhysicalPoint getCorrespondingPhysicalPointInCalcPlan(Dose* measure,Dose* calc,PhysicalPoint point);
private:
  vector<IObserver*> ObserverList;
  virtual bool SEHNotify(IObserver* observer, Message_Notify message);
};
//---------------------------------------------------------------------------
#endif