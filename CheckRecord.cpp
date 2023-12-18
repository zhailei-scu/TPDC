//---------------------------------------------------------------------------
#include "CheckRecord.h"
#include <windows.h>

//---------------------------Class:StandardParam-----------------------
/*Constructor*/
StandardParam::StandardParam(){
  this->distance = 3.0; //mm
  this->percentDifference = 3;    //%
  this->threshold = 10; //%

  this->doseUncertainty = 2.5; //%

  this->bestFiveDoseThreadhold = 50; //%

  this->actualDosegap = 0.0; //cGy
}

/*Destructor*/
StandardParam::~StandardParam(){
  this->distance = 3.0; //mm
  this->percentDifference = 3;    //%
  this->threshold = 10; //%

  this->doseUncertainty = 2.5; //%

  this->bestFiveDoseThreadhold = 50; //%

  this->actualDosegap = 0.0; //cGy
}

/*Copy Constructor*/
StandardParam::StandardParam(const StandardParam& r){
  if(NULL != &r){
    this->distance = r.distance;
    this->percentDifference = r.percentDifference;
    this->threshold = r.threshold;
    this->doseUncertainty = r.doseUncertainty;
    this->bestFiveDoseThreadhold = r.bestFiveDoseThreadhold;

    this->actualDosegap = r.actualDosegap;
  }else{
    this->distance = 3.0; //mm
    this->percentDifference = 3;    //%
    this->threshold = 10; //%
    this->doseUncertainty = 2.5; //%

    this->bestFiveDoseThreadhold = 50; //%

    this->actualDosegap = 0.0; //cGy
  }
}

/*Overload operator = */
StandardParam StandardParam::operator=(const StandardParam& r){
  if(NULL != &r){
    this->distance = r.distance;
    this->percentDifference = r.percentDifference;
    this->threshold = r.threshold;
    this->doseUncertainty = r.doseUncertainty;
    this->bestFiveDoseThreadhold = r.bestFiveDoseThreadhold;

    this->actualDosegap = r.actualDosegap;
  }else{
    this->distance = 3.0; //mm
    this->percentDifference = 3;    //%
    this->threshold = 10; //%
    this->doseUncertainty = 2.5; //%

    this->bestFiveDoseThreadhold = 50; //%

    this->actualDosegap = 0.0; //cGy
  }
  return *this;
}

void StandardParam::reset(){
  this->distance = 3.0; //mm
  this->percentDifference = 3;    //%
  this->threshold = 10; //%
  this->doseUncertainty = 2.5; //%
  this->bestFiveDoseThreadhold = 50; //%

  this->actualDosegap = 0.0; //cGy
}
//----------------------Class:TResult---------------------------------
/*Constructor*/
TResult::TResult(){
  this->totalPassPercent = -1;
  this->totalComparedCount = 0;
  this->passedCount = 0;
  this->everyPointResults.reset();
  this->normPosition_measure.reset();
  this->normPosition_calculate.reset();

  this->manualSelectMeasureNormValue = false;
  this->manualSelectCalculateNormValue = false;

  this->normValue_measure = "";
  this->normValue_calculate = "";
}

/*Destructor*/
TResult::~TResult(){
  this->totalPassPercent = -1;
  this->totalComparedCount = 0;
  this->passedCount = 0;
  this->everyPointResults.reset();
  this->normPosition_measure.reset();
  this->normPosition_calculate.reset();

  this->manualSelectMeasureNormValue = false;
  this->manualSelectCalculateNormValue = false;

  this->normValue_measure = "";
  this->normValue_calculate = "";
}

/*Copy Constructor*/
TResult::TResult(const TResult& r){
  if(NULL!= &r){
    this->totalPassPercent = r.totalPassPercent;
    this->totalComparedCount = r.totalComparedCount;
    this->passedCount = r.passedCount;
    this->everyPointResults = r.everyPointResults;
    this->normPosition_measure = r.normPosition_measure;
    this->normPosition_calculate = r.normPosition_calculate;

    this->manualSelectMeasureNormValue = r.manualSelectMeasureNormValue;
    this->manualSelectCalculateNormValue = r.manualSelectCalculateNormValue;

    this->normValue_measure = r.normValue_measure;
    this->normValue_calculate = r.normValue_calculate;
    
  }else{
    this->totalPassPercent = -1;
    this->totalComparedCount = 0;
    this->passedCount = 0;
    this->everyPointResults.reset();
    this->normPosition_measure.reset();
    this->normPosition_calculate.reset();

    this->manualSelectMeasureNormValue = false;
    this->manualSelectCalculateNormValue = false;

    this->normValue_measure = "";
    this->normValue_calculate = "";
  }
}

/*Overload operator = */
TResult TResult::operator = (const TResult& r){
  if(NULL!= &r){
    this->totalPassPercent = r.totalPassPercent;
    this->totalComparedCount = r.totalComparedCount;
    this->passedCount = r.passedCount;
    this->everyPointResults = r.everyPointResults;
    this->normPosition_measure = r.normPosition_measure;
    this->normPosition_calculate = r.normPosition_calculate;

    this->manualSelectMeasureNormValue = r.manualSelectMeasureNormValue;
    this->manualSelectCalculateNormValue = r.manualSelectCalculateNormValue;

    this->normValue_measure = r.normValue_measure;
    this->normValue_calculate = r.normValue_calculate;
  }else{
    this->totalPassPercent = -1;
    this->totalComparedCount = 0;
    this->passedCount = 0;
    this->everyPointResults.reset();
    this->normPosition_measure.reset();
    this->normPosition_calculate.reset();

    this->manualSelectMeasureNormValue = false;
    this->manualSelectCalculateNormValue = false;

    this->normValue_measure = "";
    this->normValue_calculate = "";
  }
  return *this;
}


void TResult::reset(){
  this->totalPassPercent = -1;
  this->totalComparedCount = 0;
  this->passedCount = 0;
  this->everyPointResults.reset();
  this->normPosition_measure.reset();
  this->normPosition_calculate.reset();

  this->manualSelectMeasureNormValue = false;
  this->manualSelectCalculateNormValue = false;

  this->normValue_measure = "";
    this->normValue_calculate = "";
}

//-----------------------Class:BestFiveSingleRecord-----------------
  /*Constructor*/
BestFive_Single::BestFive_Single(){
  this->totalPassPercent = -1;
  this->totalComparedCount = 0;
  this->passedCount = 0;
  this->normPoint.reset();
}

/*Destructor*/
BestFive_Single::~BestFive_Single(){
  this->totalPassPercent = -1;
  this->totalComparedCount = 0;
  this->passedCount = 0;
  this->normPoint.reset();
}

/*Copy Constructor*/
BestFive_Single::BestFive_Single(const BestFive_Single& r){
  if(NULL == &r){
    this->totalPassPercent = -1;
    this->totalComparedCount = 0;
    this->passedCount = 0;
    this->normPoint.reset();
  }else{
    this->totalPassPercent = r.totalPassPercent;
    this->totalComparedCount = r.totalComparedCount;
    this->passedCount = r.passedCount;
    this->normPoint = r.normPoint;
  }
}

/*Overload operator = */
BestFive_Single BestFive_Single::operator =(const BestFive_Single&r){
  if(NULL == &r){
    this->totalPassPercent = -1;
    this->totalComparedCount = 0;
    this->passedCount = 0;
    this->normPoint.reset();
  }else{
    this->totalPassPercent = r.totalPassPercent;
    this->totalComparedCount = r.totalComparedCount;
    this->passedCount = r.passedCount;
    this->normPoint = r.normPoint;
  }

  return *this;
}

void BestFive_Single::reset(){
  this->totalPassPercent = -1;
  this->totalComparedCount = 0;
  this->passedCount = 0;
  this->normPoint.reset();
}



//----------------------------Class:BestFiveResult-----------------------------
/*Constructor*/
BestFiveResult::BestFiveResult(){
  for(int i=0;i<5;i++){
    this->bestFiveResult[i].reset();
  }
}
/*Destructor*/
BestFiveResult::~BestFiveResult(){
  for(int i=0;i<5;i++){
    this->bestFiveResult[i].reset();
  }
}
/*Copy Constructor*/
BestFiveResult::BestFiveResult(const BestFiveResult& r){
  if(NULL != &r){
    for(int i=0;i<5;i++){
      this->bestFiveResult[i] = r.bestFiveResult[i];
    }
  }else{
    for(int i=0;i<5;i++){
      this->bestFiveResult[i].reset();
    }
  }
}
/*Overload operator = */
BestFiveResult BestFiveResult::operator = (const BestFiveResult& r){
  if(NULL != &r){
    for(int i=0;i<5;i++){
      this->bestFiveResult[i] = r.bestFiveResult[i];
    }
  }else{
    for(int i=0;i<5;i++){
      this->bestFiveResult[i].reset();
    }
  }
  return *this;
}

void BestFiveResult::reset(){
  for(int i=0;i<5;i++){
    this->bestFiveResult[i].reset();
  }
}

//----------------------------Class:CheckedRecord----------------------------
/*Constructor*/
CheckedRecord::CheckedRecord(){
  this->checkedStatus =false;

  this->singleDDResult.reset();
  this->singleDTAResult.reset();
  this->singleGammaResult.reset();
  
  this->bestFiveResult.reset();
  this->checkType = 0;
}

/*Destructor*/
CheckedRecord::~CheckedRecord(){
  this->checkedStatus =false;

  this->singleDDResult.reset();
  this->singleDTAResult.reset();
  this->singleGammaResult.reset();

  this->bestFiveResult.reset();
  this->checkType = 0;
}

/*Copy Constructor*/
CheckedRecord::CheckedRecord(const CheckedRecord& r){
  if(NULL != &r){
    this->checkedStatus = r.checkedStatus;

    this->singleDDResult = r.singleDDResult;
    this->singleDTAResult = r.singleDTAResult;
    this->singleGammaResult = r.singleGammaResult;

    this->bestFiveResult = r.bestFiveResult;
    this->checkType = r.checkType;
  }else{
    this->checkedStatus =false;

    this->singleDDResult.reset();
    this->singleDTAResult.reset();
    this->singleGammaResult.reset();

    this->bestFiveResult.reset();
    this->checkType = 0;
  }
}

/*Overload operator = */
CheckedRecord CheckedRecord::operator = (const CheckedRecord& r){
  if(NULL != &r){
    this->checkedStatus = r.checkedStatus;

    this->singleDDResult = r.singleDDResult;
    this->singleDTAResult = r.singleDTAResult;
    this->singleGammaResult = r.singleGammaResult;

    this->bestFiveResult = r.bestFiveResult;
    this->checkType = r.checkType;
  }else{
    this->checkedStatus =false;

    this->singleDDResult.reset();
    this->singleDTAResult.reset();
    this->singleGammaResult.reset();

    this->bestFiveResult.reset();
    this->checkType = 0;
  }
  return *this;
}

/*All only have get method*/
bool CheckedRecord::getCheckedStatus(){
  return this->checkedStatus;
}

void CheckedRecord::setCheckedStatus(bool checked){
  this->checkedStatus = checked;
}

TResult* CheckedRecord::getSingleDDResult(){
  return &this->singleDDResult;
}

TResult* CheckedRecord::getSingleDTAResult(){
  return &this->singleDTAResult;
}

TResult* CheckedRecord::getSingleGammaResult(){
  return &this->singleGammaResult;
}

TResult CheckedRecord::copySingleDDResult(){
  return this->singleDDResult;
}

TResult CheckedRecord::copySingleDTAResult(){
  return this->singleDTAResult;
}

TResult CheckedRecord::copySingleGammaResult(){
  return this->singleGammaResult;
}

void CheckedRecord::setSingleDDResult(TResult& _singleDDResult){
  this->singleDDResult = _singleDDResult;
}

void CheckedRecord::setSingleDTAResult(TResult& _singleDTAResult){
  this->singleDTAResult = _singleDTAResult;
}

void CheckedRecord::setSingleGammaResult(TResult& _singleGammaResult){
  this->singleGammaResult = _singleGammaResult;
}

BestFiveResult* CheckedRecord::getBestFiveResult(){
  return &this->bestFiveResult;
}

BestFiveResult CheckedRecord::copyBestFiveResult(){
  return this->bestFiveResult;
}

void CheckedRecord::setBestFiveResult(BestFiveResult& _bestFive){
  this->bestFiveResult = _bestFive;
}
  
CHECKTYPE CheckedRecord::getCheckType(){
  return this->checkType;
}

void CheckedRecord::setCheckType(CHECKTYPE _type){
  this->checkType = _type;
}

void CheckedRecord::reset(){
  this->checkedStatus =false;

  this->singleDDResult.reset();
  this->singleDTAResult.reset();
  this->singleGammaResult.reset();

  this->bestFiveResult.reset();
  this->checkType = 0;
}
