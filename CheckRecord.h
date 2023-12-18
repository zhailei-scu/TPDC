//---------------------------------------------------------------------------
#pragma once

#ifndef CheckRecordH
#define CheckRecordH

//------------------------------------------------------------------------
#include "Util.h"

enum CHECKTYPE{
  //default:0/-1:unChoosed

  //Absolute
  ABS_DD = 1,
  ABS_DTA_FloatWay = 2,
  ABS_DTA_MidValueWay = 3,
  ABS_DTA_SamePositionWay = 4,
  ABS_GAMMA = 5,

  ABS_BESTFIVE_DTA = 22,
  ABS_BESTFIVE_GAMMA = 23,


  //Relative
  REL_DTA_FloatWay = 31,
  REL_DTA_MidValueWay = 32,
  REL_DTA_SamePositionWay = 33,
  REL_GAMMA = 34,

  REL_BESTFIVE_DTA = 61,
  REL_BESTFIVE_GAMMA = 62,
};

//---------------------------Class:StandardParam-----------------------
class StandardParam{
public:
  double distance;      //mm
  double actualDosegap; //cGy
  double percentDifference; //%

  double threshold;     //%

  double doseUncertainty;  //%

  double bestFiveDoseThreadhold;   //%
public:
  /*Constructor*/
  StandardParam();
  /*Destructor*/
  ~StandardParam();
  /*Copy Constructor*/
  StandardParam(const StandardParam& r);
  /*Overload operator = */
  StandardParam operator=(const StandardParam& r);
public:
  void reset();
};
//----------------------------Class:TResult--------------------------------
class TResult{
public:
  double totalPassPercent;
  int totalComparedCount;
  int passedCount;
  MatrixData<double> everyPointResults;
  PhysicalPoint normPosition_measure;
  PhysicalPoint normPosition_calculate;

  bool manualSelectMeasureNormValue;
  bool manualSelectCalculateNormValue;

  string normValue_measure;
  string normValue_calculate;
public:
  /*Constructor*/
  TResult();
  /*Destructor*/
  ~TResult();
  /*Copy Constructor*/
  TResult(const TResult& r);
  /*Overload operator = */
  TResult operator = (const TResult& r);
public:
  void reset();
};


//-----------------------Class:BestFiveSingleRecord-----------------
class BestFive_Single{
public:
  double totalPassPercent;
  int totalComparedCount;
  int passedCount;
  GridPoint normPoint;
public:
  /*Constructor*/
  BestFive_Single();

  /*Destructor*/
  ~BestFive_Single();

  /*Copy Constructor*/
  BestFive_Single(const BestFive_Single& r);

  /*Overload operator = */
  BestFive_Single operator =(const BestFive_Single&r);

public:
  void reset();
};

//----------------------------Class:BestFiveResult-----------------------------
class BestFiveResult{
public:
  BestFive_Single bestFiveResult[5];
public:
  /*Constructor*/
  BestFiveResult();
  /*Destructor*/
  ~BestFiveResult();
  /*Copy Constructor*/
  BestFiveResult(const BestFiveResult& r);
  /*Overload operator = */
  BestFiveResult operator = (const BestFiveResult& r);
public:
  void reset();
};

//----------------------------Class:CheckedRecord----------------------------
class CheckedRecord{
private:
  bool checkedStatus;
  TResult singleDDResult;
  TResult singleDTAResult;
  TResult singleGammaResult;

  BestFiveResult bestFiveResult;
  CHECKTYPE checkType;
public:
  /*Constructor*/
  CheckedRecord();
  /*Destructor*/
  ~CheckedRecord();
  /*Copy Constructor*/
  CheckedRecord(const CheckedRecord& r);
  /*Overload operator = */
  CheckedRecord operator = (const CheckedRecord& r);

public:
  bool getCheckedStatus();
  void setCheckedStatus(bool checked);

  TResult* getSingleDDResult();
  TResult* getSingleDTAResult();
  TResult* getSingleGammaResult();

  TResult copySingleDDResult();
  TResult copySingleDTAResult();
  TResult copySingleGammaResult();

  void setSingleDDResult(TResult& _singleDDResult);
  void setSingleDTAResult(TResult& _singleDTAResult);
  void setSingleGammaResult(TResult& _singleGammaResult);

  BestFiveResult* getBestFiveResult();
  BestFiveResult copyBestFiveResult();
  void setBestFiveResult(BestFiveResult& _bestFive);
  
  CHECKTYPE getCheckType();
  void setCheckType(CHECKTYPE _type);
  
public:
  void reset();
};
//---------------------------------------------------------------------------
#endif