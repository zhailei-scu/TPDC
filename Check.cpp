//---------------------------------------------------------------------------
#include "Paraset.h"
#include "stdlib.h"
#include "Check.h"
#include "doseshell.h"
#include "GlobalData.h"
#include "LogFrame.h"

//----------------------------Class:DoseCheck---------------------------------
/*Constructor*/
DoseCheck::DoseCheck(){
  this->checkedRecord.reset();
  this->standardParam.reset();
}
/*Destructor*/
DoseCheck::~DoseCheck(){
  this->checkedRecord.reset();
  this->standardParam.reset();
}
/*Copy Constructor*/
DoseCheck::DoseCheck(const DoseCheck &r){
  this->checkedRecord.reset();
  this->standardParam.reset();
  if(NULL != &r){
    this->checkedRecord = r.checkedRecord;
    this->standardParam = r.standardParam;
  }
}
/*Overload operator =*/
DoseCheck DoseCheck::operator = (const DoseCheck &r){
  if(NULL == &r){
    this->checkedRecord.reset();
    this->standardParam.reset();
  }else{
    this->checkedRecord = r.checkedRecord;
    this->standardParam = r.standardParam;
  }
  return *this;
}


/*Functions*/
void DoseCheck::check(CHECKTYPE checkType){

  this->reset();

  switch(checkType)
  {
    //Absoulte
    case CHECKTYPE(ABS_DD):
    {
      doseDifferenceCheck();
    }
    break;

    case CHECKTYPE(ABS_DTA_FloatWay):
    {
      dtaCheck_FloatWay(checkType);
    }
    break;

    case CHECKTYPE(ABS_DTA_MidValueWay):
    {
      dtaCheck_MidValueWay(checkType);
    }
    break;

    case CHECKTYPE(ABS_DTA_SamePositionWay):
    {
      dtaCheck_SamePositionWay(checkType);
    }
    break;

    case CHECKTYPE(ABS_GAMMA):
    {
      gammaCheck(checkType);
    }
    break;

    case CHECKTYPE(ABS_BESTFIVE_DTA):
    {
      bestFive_Abs_DTACheck();
    }
    break;

    case CHECKTYPE(ABS_BESTFIVE_GAMMA):
    {
      bestFive_Abs_GammaCheck();
    }
    break;

    //Relative
    case CHECKTYPE(REL_DTA_FloatWay):
    {
      dtaCheck_FloatWay(checkType);
    }
    break;

    case CHECKTYPE(REL_DTA_MidValueWay):
    {
      dtaCheck_MidValueWay(checkType);
    }
    break;

    case CHECKTYPE(REL_DTA_SamePositionWay):
    {
      dtaCheck_SamePositionWay(checkType);
    }
    break;

    case CHECKTYPE(REL_GAMMA):
    {
      gammaCheck(checkType);
    }
    break;

    case CHECKTYPE(REL_BESTFIVE_DTA):
    {
      bestFive_Rel_DTACheck();
    }
    break;

    case CHECKTYPE(REL_BESTFIVE_GAMMA):
    {
      bestFive_Rel_GammaCheck();
    }
    break;

    default:
    {
      RunningLog::writeLog("Unknown check type",__LINE__);
    }
    break;
    
  }

  this->checkedRecord.setCheckedStatus(true);
  this->checkedRecord.setCheckType(checkType);

}


void DoseCheck::check(CHECKTYPE checkType,GridPoint normPoint){
   switch(checkType)
  {
    case CHECKTYPE(ABS_DD):
    {
      doseDifferenceCheck(normPoint);
    }
    break;

    case CHECKTYPE(ABS_DTA_FloatWay):
    case CHECKTYPE(REL_DTA_FloatWay):
    {
      dtaCheck_FloatWay(checkType,normPoint);
    }
    break;

    case CHECKTYPE(ABS_DTA_MidValueWay):
    case CHECKTYPE(REL_DTA_MidValueWay):
    {
      dtaCheck_MidValueWay(checkType,normPoint);
    }
    break;

    case CHECKTYPE(ABS_DTA_SamePositionWay):
    case CHECKTYPE(REL_DTA_SamePositionWay):
    {
      dtaCheck_SamePositionWay(checkType,normPoint);
    }
    break;


    case CHECKTYPE(ABS_GAMMA):
    case CHECKTYPE(REL_GAMMA):
    {
      gammaCheck(checkType,normPoint);
    }
    break;

    default:
    {
      RunningLog::writeLog("Unkable checkType",__LINE__);
      return;
    }
    break;
    
  }

  this->checkedRecord.setCheckedStatus(true);
  this->checkedRecord.setCheckType(checkType);
}

//---------------------------------------------------------------------
void DoseCheck::doseDifferenceCheck(){
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  Dose* measureDose = NULL;
  Dose* NormMeasureDose = NULL;
  Dose* calcDose = NULL;
  Dose* NormCalcDose = NULL;

  HANDLE_MODEL handle_model;


  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }
  handle_model = globalMem->getHandel_Model();

  NormMeasureDose = handledPairDose->getNormMeasureDoseHandled();
  if(NULL == NormMeasureDose){
    RunningLog::writeLog("The NormMeasureDose is NULL;",__LINE__);
    return;
  }

  NormCalcDose = handledPairDose->getAbs_NormCalculateDoseHandled();
  if(NULL == NormCalcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }


  measureDose = handledPairDose->getMeasureDoseHandled();
  if(NULL == measureDose){
        RunningLog::writeLog("The measureDose is NULL;",__LINE__);
        return;
  }

  calcDose = handledPairDose->getCalculateDoseHandled();
  if(NULL == calcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }
   
  this->checkedRecord.getSingleDDResult()->manualSelectMeasureNormValue = handledPairDose->getManualSpecialMeasureNormValue();
  this->checkedRecord.getSingleDDResult()->manualSelectCalculateNormValue = handledPairDose->getManualSpecialCalcNormValue();

  this->checkedRecord.getSingleDDResult()->normValue_measure = handledPairDose->getNormValueStr_measure();
  this->checkedRecord.getSingleDDResult()->normValue_calculate = handledPairDose->getNormValueStr_calculate();

  this->checkedRecord.getSingleDDResult()->normPosition_measure = *handledPairDose->getNormlizationPosition_Measure();
  this->checkedRecord.getSingleDDResult()->normPosition_calculate = *handledPairDose->getNormlizationPosition_Calculate();

  doseDifferenceCheck(measureDose,NormMeasureDose,calcDose,NormCalcDose,handle_model);

  globalMem = NULL;
  handledPairDose = NULL;
  measureDose = NULL;
  NormMeasureDose = NULL;
  calcDose = NULL;
  NormCalcDose = NULL;
}

void DoseCheck::gammaCheck(CHECKTYPE checkType){
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  Dose* measureDose = NULL;
  Dose* calcDose = NULL;

  HANDLE_MODEL handle_model;


  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }

  handle_model = globalMem->getHandel_Model();

  switch(handle_model)
  {
    case HANDLE_MODEL(SNDAC):
    {
      measureDose = handledPairDose->getNormMeasureDoseHandled();

      if(CHECKTYPE(ABS_GAMMA)==checkType){

        calcDose = handledPairDose->getAbs_NormCalculateDoseHandled();

      }else if(CHECKTYPE(REL_GAMMA)==checkType){

        calcDose = handledPairDose->getRel_NormCalculateDoseHandled();
      }

    }
    break;

    case HANDLE_MODEL(ADAC):
    default:
    {
      if(CHECKTYPE(ABS_GAMMA)==checkType){

        measureDose = handledPairDose->getMeasureDoseHandled();

        calcDose = handledPairDose->getCalculateDoseHandled();

      }else if(CHECKTYPE(REL_GAMMA)==checkType){

        measureDose = handledPairDose->getNormMeasureDoseHandled();

        calcDose = handledPairDose->getRel_NormCalculateDoseHandled();
      }

    }
    break;
  }

  if(NULL == measureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }

  if(NULL == calcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }

  this->checkedRecord.getSingleGammaResult()->manualSelectMeasureNormValue = handledPairDose->getManualSpecialMeasureNormValue();
  this->checkedRecord.getSingleGammaResult()->manualSelectCalculateNormValue = handledPairDose->getManualSpecialCalcNormValue();

  this->checkedRecord.getSingleGammaResult()->normValue_measure = handledPairDose->getNormValueStr_measure();
  this->checkedRecord.getSingleGammaResult()->normValue_calculate = handledPairDose->getNormValueStr_calculate();

  this->checkedRecord.getSingleGammaResult()->normPosition_measure = *handledPairDose->getNormlizationPosition_Measure();
  this->checkedRecord.getSingleGammaResult()->normPosition_calculate = *handledPairDose->getNormlizationPosition_Calculate();

  gammaCheck(checkType,measureDose,calcDose,handle_model);

  globalMem = NULL;
  handledPairDose = NULL;
  measureDose = NULL;
  calcDose = NULL;
}

void DoseCheck::dtaCheck_FloatWay(CHECKTYPE checkType){
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  Dose* NormMeasureDose = NULL;
  Dose* NormCalcDose = NULL;

  HANDLE_MODEL handle_model;


  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }

  handle_model = globalMem->getHandel_Model();

  NormMeasureDose = handledPairDose->getNormMeasureDoseHandled();
  if(NULL == NormMeasureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }

  if(CHECKTYPE(ABS_DTA_FloatWay)==checkType){

    NormCalcDose = handledPairDose->getAbs_NormCalculateDoseHandled();
    if(NULL == NormCalcDose){
      RunningLog::writeLog("The calcDose is NULL;",__LINE__);
      return;
    }

  }else if(CHECKTYPE(REL_DTA_FloatWay)==checkType){

    NormCalcDose = handledPairDose->getRel_NormCalculateDoseHandled();
    if(NULL == NormCalcDose){
      RunningLog::writeLog("The calcDose is NULL;",__LINE__);
      return;
    }
  }


  this->checkedRecord.getSingleDTAResult()->manualSelectMeasureNormValue = handledPairDose->getManualSpecialMeasureNormValue();
  this->checkedRecord.getSingleDTAResult()->manualSelectCalculateNormValue = handledPairDose->getManualSpecialCalcNormValue();

  this->checkedRecord.getSingleDTAResult()->normValue_measure = handledPairDose->getNormValueStr_measure();
  this->checkedRecord.getSingleDTAResult()->normValue_calculate = handledPairDose->getNormValueStr_calculate();

  this->checkedRecord.getSingleDTAResult()->normPosition_measure = *handledPairDose->getNormlizationPosition_Measure();
  this->checkedRecord.getSingleDTAResult()->normPosition_calculate = *handledPairDose->getNormlizationPosition_Calculate();

  dtaCheck_FloatWay(checkType,NormMeasureDose,NormCalcDose,handle_model);

  globalMem = NULL;
  handledPairDose = NULL;
  NormMeasureDose = NULL;
  NormCalcDose = NULL;
}

void DoseCheck::dtaCheck_MidValueWay(CHECKTYPE checkType){
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  Dose* measureDose = NULL;
  Dose* calcDose = NULL;

  HANDLE_MODEL handle_model;


  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }

  handle_model = globalMem->getHandel_Model();

  switch(handle_model)
  {
    case HANDLE_MODEL(SNDAC):
    {
      measureDose = handledPairDose->getNormMeasureDoseHandled();

      if(CHECKTYPE(ABS_DTA_MidValueWay)==checkType){

        calcDose = handledPairDose->getAbs_NormCalculateDoseHandled();

      }else if(CHECKTYPE(REL_DTA_MidValueWay)==checkType){

        calcDose = handledPairDose->getRel_NormCalculateDoseHandled();
      }

    }
    break;

    case HANDLE_MODEL(ADAC):
    default:
    {
      if(CHECKTYPE(ABS_DTA_MidValueWay)==checkType){

        measureDose = handledPairDose->getMeasureDoseHandled();

        calcDose = handledPairDose->getCalculateDoseHandled();

      }else if(CHECKTYPE(REL_DTA_MidValueWay)==checkType){

        measureDose = handledPairDose->getNormMeasureDoseHandled();

        calcDose = handledPairDose->getRel_NormCalculateDoseHandled();
      }

    }
    break;
  }

  if(NULL == measureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }

  if(NULL == calcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }

  
  this->checkedRecord.getSingleDTAResult()->manualSelectMeasureNormValue = handledPairDose->getManualSpecialMeasureNormValue();
  this->checkedRecord.getSingleDTAResult()->manualSelectCalculateNormValue = handledPairDose->getManualSpecialCalcNormValue();

  this->checkedRecord.getSingleDTAResult()->normValue_measure = handledPairDose->getNormValueStr_measure();
  this->checkedRecord.getSingleDTAResult()->normValue_calculate = handledPairDose->getNormValueStr_calculate();

  this->checkedRecord.getSingleDTAResult()->normPosition_measure = *handledPairDose->getNormlizationPosition_Measure();
  this->checkedRecord.getSingleDTAResult()->normPosition_calculate = *handledPairDose->getNormlizationPosition_Calculate();

  dtaCheck_MidValueWay(checkType,measureDose,calcDose,handle_model);

  globalMem = NULL;
  handledPairDose = NULL;
  measureDose = NULL;
  calcDose = NULL;
}

void DoseCheck::dtaCheck_SamePositionWay(CHECKTYPE checkType){
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  Dose* NormMeasureDose = NULL;
  Dose* NormCalcDose = NULL;

  HANDLE_MODEL handle_model;


  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }

  handle_model = globalMem->getHandel_Model();

  NormMeasureDose = handledPairDose->getNormMeasureDoseHandled();
  if(NULL == NormMeasureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }

  if(CHECKTYPE(ABS_DTA_SamePositionWay)==checkType){

    NormCalcDose = handledPairDose->getAbs_NormCalculateDoseHandled();
    if(NULL == NormCalcDose){
      RunningLog::writeLog("The calcDose is NULL;",__LINE__);
      return;
    }

  }else if(CHECKTYPE(REL_DTA_SamePositionWay)==checkType){

    NormCalcDose = handledPairDose->getRel_NormCalculateDoseHandled();
    if(NULL == NormCalcDose){
      RunningLog::writeLog("The calcDose is NULL;",__LINE__);
      return;
    }
  }

  this->checkedRecord.getSingleDTAResult()->manualSelectMeasureNormValue = handledPairDose->getManualSpecialMeasureNormValue();
  this->checkedRecord.getSingleDTAResult()->manualSelectCalculateNormValue = handledPairDose->getManualSpecialCalcNormValue();

  this->checkedRecord.getSingleDTAResult()->normValue_measure = handledPairDose->getNormValueStr_measure();
  this->checkedRecord.getSingleDTAResult()->normValue_calculate = handledPairDose->getNormValueStr_calculate();

  this->checkedRecord.getSingleDTAResult()->normPosition_measure = *handledPairDose->getNormlizationPosition_Measure();
  this->checkedRecord.getSingleDTAResult()->normPosition_calculate = *handledPairDose->getNormlizationPosition_Calculate();

  dtaCheck_SamePositionWay(checkType,NormMeasureDose,NormCalcDose,handle_model);

  globalMem = NULL;
  handledPairDose = NULL;
  NormMeasureDose = NULL;
  NormCalcDose = NULL;
}



//-------------------------------------dose difference Check-------------------------------
void DoseCheck::doseDifferenceCheck(Dose* measureDose,Dose* NormMeasureDose,Dose* calcDose,Dose* NormCalcDose,HANDLE_MODEL handle_model){

  MatrixData<double>* measureDoseMatrix = NULL;
  MatrixData<double>* NormMeasureDoseMatrix = NULL;

  MatrixData<double>* calcDoseMatrix = NULL;
  MatrixData<double>* NormCalcDoseMatrix = NULL;

  int rows,cols;

  double tempNormMeasureValue,tempNormCalcValue;
  double tempValue;

  int totalCompare = 0;
  int passCount = 0;

  int measureFirstAlignmentRow,measureFirstAlignmentCol;
  int calcFirstAlignmentRow,calcFirstAlignmentCol;

  int rowSegments,colSegments;

  int correspondRowInCalc,correspondColInCalc;


  measureDoseMatrix = measureDose->getDoseMatrix();
  NormMeasureDoseMatrix = NormMeasureDose->getDoseMatrix();
  calcDoseMatrix = calcDose->getDoseMatrix();
  NormCalcDoseMatrix = NormCalcDose->getDoseMatrix();

  //sysc the standardParam
  this->standardParam = MainFormTempValue.checkStandardParam;

  rows = measureDoseMatrix->getRowLength();
  cols = measureDoseMatrix->getColLength();

  this->checkedRecord.getSingleDDResult()->everyPointResults.allocate(rows,cols,1);

  measureFirstAlignmentRow = measureDose->getFirstAlignmentCentral()->row;
  measureFirstAlignmentCol = measureDose->getFirstAlignmentCentral()->col;

  calcFirstAlignmentRow = calcDose->getFirstAlignmentCentral()->row;
  calcFirstAlignmentCol = calcDose->getFirstAlignmentCentral()->col;
  rowSegments = measureDose->getSegments()[0];
  colSegments = measureDose->getSegments()[1];

  for(int j= 0;j<cols;j++){
    for(int i=0;i<rows;i++){
      //consider the detector point only
      if(true == MainFormTempValue.detectorArray.at(i,j,0)){
        //consider the point dose should larger than threshod
        correspondRowInCalc = (i-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
        correspondColInCalc = (j-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

        if(correspondRowInCalc>=0 && correspondRowInCalc<calcDoseMatrix->getRowLength() &&
             correspondColInCalc>=0 && correspondColInCalc<calcDoseMatrix->getColLength()){

          tempNormMeasureValue = NormMeasureDoseMatrix->at(i,j,0);
          tempNormCalcValue = NormCalcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
          if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){


             tempValue = measureDoseMatrix->at(i,j,0) - calcDoseMatrix->at(correspondRowInCalc,
                                                                          correspondColInCalc,
                                                                          0);
             this->checkedRecord.getSingleDDResult()->everyPointResults.modifyValue(i,j,0,fabs(tempValue));

             if( (tempNormMeasureValue - tempNormCalcValue)<=this->standardParam.percentDifference){
               passCount++;
             }

             totalCompare++;
          }else{
             this->checkedRecord.getSingleDDResult()->everyPointResults.modifyValue(i,j,0,-888888);
          }

        }else{
          this->checkedRecord.getSingleDDResult()->everyPointResults.modifyValue(i,j,0,-888888);
        }

      }else{
        this->checkedRecord.getSingleDDResult()->everyPointResults.modifyValue(i,j,0,-888888);
      }
    }
  }


  this->checkedRecord.getSingleDDResult()->totalComparedCount = totalCompare;
  this->checkedRecord.getSingleDDResult()->passedCount = passCount;
  this->checkedRecord.getSingleDDResult()->totalPassPercent = 100*((double)passCount)/totalCompare;
  
  measureDoseMatrix = NULL;
  NormMeasureDoseMatrix = NULL;

  calcDoseMatrix = NULL;
  NormCalcDoseMatrix = NULL;
}

//-------------------------------------dta Check(3 ways)---------------------------------------
void DoseCheck::dtaCheck_FloatWay(CHECKTYPE checkType,Dose* NormMeasureDose,Dose* NormCalcDose,HANDLE_MODEL handle_model){

  MatrixData<double>* measureDoseMatrix = NULL;
  MatrixData<double>* calcDoseMatrix = NULL;

  int rows,cols;
  int iOffSet,jOffSet;

  double tempValueGap,tempDistancePower2;
  double distanceStandardPower2;
  int passCount = 0;
  int considerCount = 0;

  double tempNormMeasureValue,tempNormCalcValue;

  int measureFirstAlignmentRow,measureFirstAlignmentCol;
  int calcFirstAlignmentRow,calcFirstAlignmentCol;

  int rowSegments,colSegments;

  int correspondRowInCalc,correspondColInCalc;

  double calcRowGridSize,calcColGridSize;
  int searchRadioRow,searchRadioCol;

  bool isbreak;
  bool getADta;

  measureDoseMatrix = NormMeasureDose->getDoseMatrix();
  calcDoseMatrix = NormCalcDose->getDoseMatrix();

  //sysc the standardParam
  this->standardParam = MainFormTempValue.checkStandardParam;

  rows = measureDoseMatrix->getRowLength();
  cols = measureDoseMatrix->getColLength();


  this->checkedRecord.getSingleDTAResult()->everyPointResults.allocate(rows,cols,1);

  measureFirstAlignmentRow = NormMeasureDose->getFirstAlignmentCentral()->row;
  measureFirstAlignmentCol = NormMeasureDose->getFirstAlignmentCentral()->col;

  calcFirstAlignmentRow = NormCalcDose->getFirstAlignmentCentral()->row;
  calcFirstAlignmentCol = NormCalcDose->getFirstAlignmentCentral()->col;

  rowSegments = NormMeasureDose->getSegments()[0];
  colSegments = NormMeasureDose->getSegments()[1];

  calcRowGridSize = NormMeasureDose->getGridSizes()[0]/rowSegments;
  calcColGridSize = NormMeasureDose->getGridSizes()[1]/colSegments;
  searchRadioRow = TrimFloat_Up(this->standardParam.distance/calcRowGridSize,0.02);
  searchRadioCol = TrimFloat_Up(this->standardParam.distance/calcColGridSize,0.02);

  distanceStandardPower2 = this->standardParam.distance*this->standardParam.distance;

  vector< pair<double,GridPoint> > presortResult =  presort(searchRadioRow,searchRadioCol,calcRowGridSize,calcColGridSize);

  isbreak = false;
  getADta = false;
  
  for(int j= 0;j<cols;j++){
    for(int i=0;i<rows;i++){
      //consider the detector point only
      if(true == MainFormTempValue.detectorArray.at(i,j,0)){
        //consider the point dose should larger than threshod

        correspondRowInCalc = (i-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
        correspondColInCalc = (j-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

        if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<calcDoseMatrix->getRowLength()
            &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<calcDoseMatrix->getColLength()){

          tempNormMeasureValue = measureDoseMatrix->at(i,j,0);
          tempNormCalcValue = calcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
          if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){

            isbreak = false;
            getADta = false;
            
            for(vector< pair<double,GridPoint> >::iterator iterat = presortResult.begin();iterat != presortResult.end();iterat++){

              if(true==isbreak){
                break;
              }

              iOffSet = iterat->second.row;
              jOffSet = iterat->second.col;


              tempValueGap = fabs(measureDoseMatrix->at(i,j,0) - calcDoseMatrix->at(iOffSet + correspondRowInCalc,
                                                                                      jOffSet + correspondColInCalc,
                                                                                      0));
              tempDistancePower2 = iterat->first;
              if(tempValueGap<=this->standardParam.doseUncertainty){
                  getADta = true;
              }

              if(tempDistancePower2>distanceStandardPower2){
                isbreak = true;
              }



            }

            if(true == getADta){
              this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,sqrt(tempDistancePower2));
              passCount++;
            }else{
              this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,-1);
            }
            considerCount++;
          }

        }

      }
    }
  }

  this->checkedRecord.getSingleDTAResult()->totalPassPercent = 100*((double)passCount)/considerCount;
  this->checkedRecord.getSingleDTAResult()->totalComparedCount = considerCount;
  this->checkedRecord.getSingleDTAResult()->passedCount = passCount;
  

  measureDoseMatrix = NULL;
  calcDoseMatrix = NULL;
}
//-------------------------------------------------------------------------------------
void DoseCheck::dtaCheck_MidValueWay(CHECKTYPE checkType,Dose* measureDose,Dose* calcDose,HANDLE_MODEL handle_model){
  MatrixData<double>* measureDoseMatrix = NULL;
  MatrixData<double>* calcDoseMatrix = NULL;


  int rows,cols;
  int iOffSet,jOffSet;

  double tempValueGap,tempDistancePower2;
  double distanceStandardPower2;
  int passCount = 0;
  int considerCount = 0;

  int decimal = 3;

  bool findBigger = false;
  bool findLitter = false;

  double firstLable;

  double tempActualMeasureValue,tempActualCalcValue;
  double tempNormMeasureValue,tempNormCalcValue;
  double tempPercentDoseDifference;

  double actualMaxMeasureDose,actualMaxCalcDose;

  int measureFirstAlignmentRow,measureFirstAlignmentCol;
  int calcFirstAlignmentRow,calcFirstAlignmentCol;

  int rowSegments,colSegments;

  int correspondRowInCalc,correspondColInCalc;


  double measureRowGridSize,measureColGridSize;
  double calcRowGridSize,calcColGridSize;
  int searchRadioRow,searchRadioCol;

  bool getADta;

  bool isbreak;

  double dtaValue = 32000.0;

  measureDoseMatrix = measureDose->getDoseMatrix();
  calcDoseMatrix = calcDose->getDoseMatrix();

  //sysc the standardParam
  this->standardParam = MainFormTempValue.checkStandardParam;

  rows = measureDoseMatrix->getRowLength();
  cols = measureDoseMatrix->getColLength();

  this->checkedRecord.getSingleDTAResult()->everyPointResults.allocate(rows,cols,1);

  measureFirstAlignmentRow = measureDose->getFirstAlignmentCentral()->row;
  measureFirstAlignmentCol = measureDose->getFirstAlignmentCentral()->col;

  calcFirstAlignmentRow = calcDose->getFirstAlignmentCentral()->row;
  calcFirstAlignmentCol = calcDose->getFirstAlignmentCentral()->col;

  rowSegments = measureDose->getSegments()[0];
  colSegments = measureDose->getSegments()[1];

  measureRowGridSize = measureDose->getGridSizes()[0];
  measureColGridSize = measureDose->getGridSizes()[1];
  
  calcRowGridSize = measureRowGridSize/rowSegments;
  calcColGridSize = measureColGridSize/colSegments;

  distanceStandardPower2 = this->standardParam.distance*this->standardParam.distance;

  getADta = false;

  switch(handle_model)
  {
    case HANDLE_MODEL(SNDAC):
    {
      double radius = 4.5;
      int nRange = TrimFloat_Down(radius/calcRowGridSize, 0.02);

      searchRadioRow = TrimFloat_Up(this->standardParam.distance/calcRowGridSize,0.02);
      searchRadioCol = TrimFloat_Up(this->standardParam.distance/calcColGridSize,0.02);

      for(int j = 0; j < cols; j++){
        for(int i = 0; i < rows; i++){
          //consider the detector point only
          if (true == MainFormTempValue.detectorArray.at(i, j, 0)){
            //consider the point dose should larger than threshod
            correspondRowInCalc = (i - measureFirstAlignmentRow)*rowSegments + calcFirstAlignmentRow;
            correspondColInCalc = (j - measureFirstAlignmentCol)*colSegments + calcFirstAlignmentCol;

            if((correspondRowInCalc - nRange) >= 0 && (correspondRowInCalc + nRange) < calcDoseMatrix->getRowLength()
                && (correspondColInCalc - nRange) >= 0 && (correspondColInCalc + nRange) < calcDoseMatrix->getColLength()){

              double mValue = measureDoseMatrix->at(i, j, 0);

              double cValue = calcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);

              int tagFirst = mValue>=cValue?-1:1;

              isbreak = false;

              getADta = false;

              tempNormMeasureValue = measureDoseMatrix->at(i,j,0);
              tempNormCalcValue = calcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
              if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){

                double tmVPublic,temv;

                double innerCalcDose, outCalcDose;
                tempDistancePower2 = DBL_MAX;


                if (doubleToAroundPowInt(mValue, decimal) == doubleToAroundPowInt(cValue, decimal)){
                  tempDistancePower2 = 0;
                  getADta = true;
                }
                else{

		  int subCol = 0;

                  int v111 = correspondRowInCalc;
                  int v138 = correspondColInCalc - correspondRowInCalc;
                  int v136 = correspondRowInCalc - correspondColInCalc;

                  double slope,xInterp,yInterp;

                  isbreak = false;

                  do{
                    if(isbreak){
                      break;
                    }

                    int v33 = 0;
                    int v110 = 0;
                    if(subCol >= 0){

                      while(!isbreak){
                        tmVPublic = (v33 * v33)*calcRowGridSize*calcRowGridSize
                                + (subCol * subCol)*calcColGridSize*calcColGridSize;


                        if (v33 || tmVPublic<tempDistancePower2){
                          int v34 = v33;
                          int v99 = v33;
                          int v104 = subCol;

                          CalcIndices(v99,v104);
                          
                          int v35 = 2;

                          if (!v110 || v110 == subCol){
                            v35 = 1;
                          }

                          int v140 = v111 + v138;
                          int v36 = v99;
                          int v70 = v35;

                          int v141 = correspondColInCalc + subCol + v136;
                          int v129 = correspondColInCalc + subCol;

                          bool v57 = false;

                          while (!v57){
                            int v90 = v36 + correspondRowInCalc;
                            int v78 = correspondColInCalc - v104;
                            innerCalcDose = calcDoseMatrix->at(v36 + correspondRowInCalc, correspondColInCalc - v104, 0);

                            int v100 = v34 + correspondRowInCalc;
                            outCalcDose = calcDoseMatrix->at(v100, v140,0);

                            if (outCalcDose == 0x40000000 || tagFirst*(mValue - outCalcDose) <= 0){
                              if (!(tagFirst * (mValue - outCalcDose)) && tmVPublic < tempDistancePower2){
                                tempDistancePower2 = tmVPublic;
                              }
                            }
                            else{
                              slope = (double)(mValue - innerCalcDose)/(double)(outCalcDose - innerCalcDose);
                              xInterp = (v100 - v90) * slope + v90;
                              yInterp = slope * (v140 -v78) + v78 - correspondColInCalc;
                              temv = (xInterp - correspondRowInCalc)*(xInterp -correspondRowInCalc) * calcRowGridSize*calcRowGridSize
                                   + yInterp * yInterp * calcColGridSize*calcColGridSize;
                              if (temv < tempDistancePower2 && temv <= radius*radius){
                                tempDistancePower2 = temv;
                              }
                            }

                            int v79 = v99 + correspondColInCalc;
                            int v91 = v104 + correspondRowInCalc;
                            innerCalcDose = calcDoseMatrix->at(v104 + correspondRowInCalc, v99 + correspondColInCalc, 0);
                            v100 = v141;
                            int v85 = v34 + correspondColInCalc;
                            outCalcDose = calcDoseMatrix->at(v141, v85,0);
                            if(outCalcDose == 0x40000000 || tagFirst*(mValue - outCalcDose) <= 0){
                              if (!(tagFirst * (mValue - outCalcDose)) && tmVPublic < tempDistancePower2){
                                tempDistancePower2 = tmVPublic;
                              }
                            }
                            else{
                              slope = (double)(mValue - innerCalcDose) / (double)(outCalcDose - innerCalcDose);
                              xInterp = (v100 - v91) * slope + v91;
                              yInterp = slope * (v85 - v79) + v79 - correspondColInCalc;
                              temv = (xInterp - correspondRowInCalc)*(xInterp - correspondRowInCalc) * calcRowGridSize*calcRowGridSize
			           + yInterp * yInterp * calcColGridSize*calcColGridSize;

			      if (temv < tempDistancePower2 && temv <= radius*radius){
                                tempDistancePower2 = temv;
                              }
                            }

                            int v92 = correspondRowInCalc - v99;
                            int v80 = correspondColInCalc + v104;
                            v34 = -v34;
                            innerCalcDose = calcDoseMatrix->at(correspondRowInCalc - v99, correspondColInCalc + v104, 0);
                            int v86 = v129;
                            v100 = v34 + correspondRowInCalc;
                            outCalcDose = calcDoseMatrix->at(v100, v129, 0);

                            if(outCalcDose == 0x40000000 || tagFirst*(mValue - outCalcDose)<= 0){
                              if (!(tagFirst * (mValue - outCalcDose)) && tmVPublic < tempDistancePower2){
                                tempDistancePower2 = tmVPublic;
                              }
                            }
                            else{
                              slope = (double)(mValue - innerCalcDose)/(double)(outCalcDose - innerCalcDose);
                              xInterp = (v100 - v92) * slope + v92;
                              yInterp = slope * (v86 - v80) + v80 - correspondColInCalc;
                              temv = (xInterp - correspondRowInCalc)*(xInterp - correspondRowInCalc) * calcRowGridSize*calcRowGridSize
			           + yInterp * yInterp * calcColGridSize*calcColGridSize;
                              if (temv < tempDistancePower2 && temv <= radius*radius){
                                tempDistancePower2 = temv;
                              }
                            }

                            int v93 = correspondRowInCalc - v104;
                            int v81 = correspondColInCalc - v99;

                            innerCalcDose = calcDoseMatrix->at(correspondRowInCalc - v104, correspondColInCalc - v99, 0);
                            v100 = v111;
                            int v87 = v34 + correspondColInCalc;
                            outCalcDose = calcDoseMatrix->at(v111, v87, 0);
                            if (outCalcDose == 0x40000000 || tagFirst*(mValue - outCalcDose) <= 0){
                              if (!(tagFirst * (mValue - outCalcDose)) && tmVPublic < tempDistancePower2){
                                tempDistancePower2 = tmVPublic;
                              }
                            }
                            else{
                              slope = (double)(mValue - innerCalcDose) / (double)(outCalcDose - innerCalcDose);
                              xInterp = (v100 - v93) * slope + v93;
                              yInterp = slope * (v87 - v81) + v81 - correspondColInCalc;
                              temv = (xInterp - correspondRowInCalc)*(xInterp - correspondRowInCalc) * calcRowGridSize*calcRowGridSize
															+ yInterp * yInterp * calcColGridSize*calcColGridSize;
                              if (temv < tempDistancePower2 && temv <= radius*radius){
                                tempDistancePower2 = temv;
                              }
                            }
                            v36 = -v99;

                            v57 = (v70 == 1)?true:false;
                            v99 = -v99;
                            --v70;
                          }


                        }
                        else{
                          isbreak = true;
                        }

                        if (++v110 > subCol){
                          break;
                        }
                        v33 = v110;
                      }


                    }

                    --v111;

                  }while( (subCol++ + 1)<=nRange);

                }


                if(tempDistancePower2<distanceStandardPower2){
                  getADta = true;
                }

                if(true == getADta){
                  this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,sqrt(tempDistancePower2));
                  passCount++;
                }else{
                  this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,-1);
                }
                considerCount++;


              }



            }
          }
        }
      }
    }
    break;
    /*
    case HANDLE_MODEL(MODEL_OMNIPRO):
    {
       int nRange = TrimFloat_Down(4.5/calcRowGridSize,0.02);
       
       for(int j= 0;j<cols;j++){
        for(int i=0;i<rows;i++){
        //consider the detector point only
          if(true == MainFormTempValue.detectorArray.at(i,j,0)){
            //consider the point dose should larger than threshod
            correspondRowInCalc = (i-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
            correspondColInCalc = (j-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

            if( (correspondRowInCalc-nRange)>=0 && (correspondRowInCalc+nRange)<calcDoseMatrix->getRowLength()
               &&(correspondColInCalc-nRange)>=0 && (correspondColInCalc+nRange)<calcDoseMatrix->getColLength()){

              if(passedThreshold(measureDoseMatrix,i,j,0,calcDoseMatrix,correspondRowInCalc,correspondColInCalc,0,
                                 this->standardParam.threshold,handle_model)){

                double tmV;
                tempDistancePower2 = DBL_MAX;

                double mValue = measureDoseMatrix->at(i,j,0);

                double cValue = calcDoseMatrix->at(correspondRowInCalc,
                                               correspondColInCalc,
                                               0);
                isbreak = false;

                getADta = false;

                if(doubleToAroundPowInt(mValue,decimal) == doubleToAroundPowInt(cValue,decimal)){
                  tempDistancePower2 = 0;
                  getADta = true;

                }else{

                  int tagFirst = mValue>cValue?1:-1;

                  int r,jr,ir;

                  for(r=1;r<=nRange;r++){

                    if(true==isbreak){
                      break;
                    }

                    ir = 0;
                    jr = r;

                    
                    while(ir<=r){

                      int innerRi;
                      int innerRj;

                      if(true==isbreak){
                        break;
                      }

                      tmV = ir*ir*calcRowGridSize*calcRowGridSize
                          + jr*jr*calcColGridSize*calcColGridSize;

                      if(tmV>=tempDistancePower2 && 0==ir){
                        isbreak = true;
                      }

                      double outCalcDose,innerCalcDose;

                      outCalcDose = calcDoseMatrix->at(correspondRowInCalc + ir,
                                                       correspondColInCalc + jr,
                                                       0);


                      if(tagFirst*(mValue-outCalcDose)<=0){

                          if(tmV<tempDistancePower2){
                            tempDistancePower2 = tmV;
                          }

                      }else if(getInnerPoint(ir,jr,innerRi,innerRj,r)){
                      
                        innerCalcDose = calcDoseMatrix->at(correspondRowInCalc + innerRi,
                                                           correspondColInCalc + innerRj,
                                                           0);

                        if(! (outCalcDose==innerCalcDose)){
                          double slope = (mValue - innerCalcDose)/(outCalcDose - innerCalcDose);
                          tmV = calcRowGridSize*calcRowGridSize*( (slope*(ir-innerRi)+innerRi)*(slope*(ir-innerRi)+innerRi)
                                                                + (slope*(jr-innerRj)+innerRj)*(slope*(jr-innerRj)+innerRj));

                          if(tmV<tempDistancePower2){
                            tempDistancePower2 = tmV;
                          }
                        }
                      }


                      outCalcDose = calcDoseMatrix->at(correspondRowInCalc + jr,
                                                       correspondColInCalc + ir,
                                                       0);

                      if(tagFirst*(mValue-outCalcDose)<=0){

                          if(tmV<tempDistancePower2){
                            tempDistancePower2 = tmV;
                          }

                      }else if(getInnerPoint(jr,ir,innerRi,innerRj,r)){
                      
                        innerCalcDose = calcDoseMatrix->at(correspondRowInCalc + innerRi,
                                                           correspondColInCalc + innerRj,
                                                           0);
                        if(! (outCalcDose==innerCalcDose)){
                          double slope = (mValue - innerCalcDose)/(outCalcDose - innerCalcDose);
                          tmV = calcRowGridSize*calcRowGridSize*( (slope*(jr-innerRi)+innerRi)*(slope*(jr-innerRi)+innerRi)
                                                              +   (slope*(ir-innerRj)+innerRj)*(slope*(ir-innerRj)+innerRj));

                          if(tmV<tempDistancePower2){
                            tempDistancePower2 = tmV;
                          }
                        }
                      }


                      outCalcDose = calcDoseMatrix->at(correspondRowInCalc + jr,
                                                       correspondColInCalc - ir,
                                                       0);

                      if(tagFirst*(mValue-outCalcDose)<=0){

                        if(tmV<tempDistancePower2){
                          tempDistancePower2 = tmV;
                        }

                      }else if(getInnerPoint(jr,-ir,innerRi,innerRj,r)){

                        innerCalcDose = calcDoseMatrix->at(correspondRowInCalc + innerRi,
                                                           correspondColInCalc + innerRj,
                                                           0);

                        if(! (outCalcDose==innerCalcDose)){
                          double slope = (mValue - innerCalcDose)/(outCalcDose - innerCalcDose);
                          tmV = calcRowGridSize*calcRowGridSize*( (slope*(jr-innerRi)+innerRi)*(slope*(jr-innerRi)+innerRi)
                                                                + (slope*(-ir- innerRj)+innerRj)*(slope*(-ir- innerRj)+innerRj));

                          if(tmV<tempDistancePower2){
                            tempDistancePower2 = tmV;
                          }
                        }
                      }


                      outCalcDose = calcDoseMatrix->at(correspondRowInCalc + ir,
                                                       correspondColInCalc - jr,
                                                       0);

                      if(tagFirst*(mValue-outCalcDose)<=0){

                        if(tmV<tempDistancePower2){
                          tempDistancePower2 = tmV;
                        }

                      }else if(getInnerPoint(ir,-jr,innerRi,innerRj,r)){

                        innerCalcDose = calcDoseMatrix->at(correspondRowInCalc + innerRi,
                                                           correspondColInCalc + innerRj,
                                                           0);

                        if(! (outCalcDose==innerCalcDose)){
                          double slope = (mValue - innerCalcDose)/(outCalcDose - innerCalcDose);
                          tmV = calcRowGridSize*calcRowGridSize*( (slope*(ir-innerRi)+innerRi)*(slope*(ir-innerRi)+innerRi)
                                                              + (slope*(-jr- innerRj)+innerRj)*(slope*(-jr- innerRj)+innerRj));

                          if(tmV<tempDistancePower2){
                            tempDistancePower2 = tmV;
                          }
                        }
                      }


                      outCalcDose = calcDoseMatrix->at(correspondRowInCalc - ir,
                                                       correspondColInCalc - jr,
                                                       0);

                      if(tagFirst*(mValue-outCalcDose)<=0){

                        if(tmV<tempDistancePower2){
                          tempDistancePower2 = tmV;
                        }

                      }else if(getInnerPoint(-ir,-jr,innerRi,innerRj,r)){

                        innerCalcDose = calcDoseMatrix->at(correspondRowInCalc + innerRi,
                                                           correspondColInCalc + innerRj,
                                                           0);

                        if(! (outCalcDose==innerCalcDose)){
                          double slope = (mValue - innerCalcDose)/(outCalcDose - innerCalcDose);
                          tmV = calcRowGridSize*calcRowGridSize*( (slope*(-ir-innerRi)+innerRi)*(slope*(-ir-innerRi)+innerRi)
                                                              + (slope*(-jr - innerRj)+innerRj)*(slope*(-jr - innerRj)+innerRj));

                          if(tmV<tempDistancePower2){
                            tempDistancePower2 = tmV;
                          }
                        }
                      }


                      outCalcDose = calcDoseMatrix->at(correspondRowInCalc - jr,
                                                       correspondColInCalc - ir,
                                                       0);

                      if(tagFirst*(mValue-outCalcDose)<=0){

                        if(tmV<tempDistancePower2){
                          tempDistancePower2 = tmV;
                        }

                      }else if(getInnerPoint(-jr,-ir,innerRi,innerRj,r)){

                        innerCalcDose = calcDoseMatrix->at(correspondRowInCalc + innerRi,
                                                           correspondColInCalc + innerRj,
                                                           0);

                        if(! (outCalcDose==innerCalcDose)){
                          double slope = (mValue - innerCalcDose)/(outCalcDose - innerCalcDose);
                          tmV = calcRowGridSize*calcRowGridSize*( (slope*(-jr-innerRi)+innerRi)*(slope*(-jr-innerRi)+innerRi)
                                                              + (slope*(-ir - innerRj)+innerRj)*(slope*(-ir - innerRj)+innerRj));

                          if(tmV<tempDistancePower2){
                            tempDistancePower2 = tmV;
                          }
                        }
                      }

                      outCalcDose = calcDoseMatrix->at(correspondRowInCalc - jr,
                                                       correspondColInCalc + ir,
                                                       0);

                      if(tagFirst*(mValue-outCalcDose)<=0){

                        if(tmV<tempDistancePower2){
                          tempDistancePower2 = tmV;
                        }

                      }else if(getInnerPoint(-jr,ir,innerRi,innerRj,r)){

                        innerCalcDose = calcDoseMatrix->at(correspondRowInCalc + innerRi,
                                                           correspondColInCalc + innerRj,
                                                           0);

                        if(! (outCalcDose==innerCalcDose)){
                          double slope = (mValue - innerCalcDose)/(outCalcDose - innerCalcDose);
                          tmV = calcRowGridSize*calcRowGridSize*( (slope*(-jr-innerRi)+innerRi)*(slope*(-jr-innerRi)+innerRi)
                                                              + (slope*(ir - innerRj)+innerRj)*(slope*(ir - innerRj)+innerRj));

                          if(tmV<tempDistancePower2){
                            tempDistancePower2 = tmV;
                          }
                        }
                      }

                      outCalcDose = calcDoseMatrix->at(correspondRowInCalc - ir,
                                                       correspondColInCalc + jr,
                                                       0);
                                                       
                      if(tagFirst*(mValue-outCalcDose)<=0){

                        if(tmV<tempDistancePower2){
                          tempDistancePower2 = tmV;
                        }

                      }else if(getInnerPoint(-ir,jr,innerRi,innerRj,r)){
                      
                        innerCalcDose = calcDoseMatrix->at(correspondRowInCalc + innerRi,
                                                           correspondColInCalc + innerRj,
                                                           0);

                        if(! (outCalcDose==innerCalcDose)){
                          double slope = (mValue - innerCalcDose)/(outCalcDose - innerCalcDose);
                          tmV = calcRowGridSize*calcRowGridSize*( (slope*(-ir-innerRi)+innerRi)*(slope*(-ir-innerRi)+innerRi)
                                                                + (slope*(jr - innerRj)+innerRj)*(slope*(jr - innerRj)+innerRj));

                          if(tmV<tempDistancePower2){
                            tempDistancePower2 = tmV;
                          }
                        }
                      }

                      ir++;

                    }


                  }


                }


                if(tempDistancePower2<distanceStandardPower2){
                  getADta = true;
                }

                if(true == getADta){
                  this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,sqrt(tempDistancePower2));
                  passCount++;
                }else{
                  this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,-1);
                }
                considerCount++;
              }



                /*
                getADta = false;

                double tmV;
                tempDistancePower2 = DBL_MAX;

                double mValue = measureDoseMatrix->at(i,j,0);

                double cValue = calcDoseMatrix->at(correspondRowInCalc,
                                               correspondColInCalc,
                                               0);

                if(doubleToAroundPowInt(mValue,decimal) == doubleToAroundPowInt(cValue,decimal)){
                  tempDistancePower2 = 0;
                  getADta = true;

                }else{

                  int tagFirst = mValue>cValue?-1:1;
                  int tagSecond = 1;

                  for(int jNeigh=-1;jNeigh<=1;jNeigh++){

                    for(int iNeigh=-1;iNeigh<=1;iNeigh++){

                      if(iNeigh != 0 || jNeigh != 0){

                         double tempCValue = calcDoseMatrix->at(correspondRowInCalc + iNeigh*(searchRadioRow-1),
                                                               correspondColInCalc + jNeigh*(searchRadioCol-1),
                                                               0);


//                        double tempCValue = calcDoseMatrix->at(correspondRowInCalc + iNeigh,
//                                                             correspondColInCalc + jNeigh,
//                                                             0);


//                          double tempCValue = calcDoseMatrix->at(correspondRowInCalc + iNeigh*rowSegments,
//                                                                 correspondColInCalc + jNeigh*colSegments,
//                                                                 0);


                        tagSecond = mValue>tempCValue?-1:1;

                        if(tagFirst*tagSecond<0){
                          tmV = iNeigh*iNeigh*(searchRadioRow-1)*(searchRadioRow-1)*calcRowGridSize*calcRowGridSize
                              + jNeigh*jNeigh*(searchRadioCol-1)*(searchRadioCol-1)*calcColGridSize*calcColGridSize;

//                          tmV = iNeigh*iNeigh*calcRowGridSize*calcRowGridSize
//                              + jNeigh*jNeigh*calcColGridSize*calcColGridSize;

//                          tmV = iNeigh*iNeigh*measureRowGridSize*measureRowGridSize
//                              + jNeigh*jNeigh*measureColGridSize*measureColGridSize;

                          if(tmV<tempDistancePower2){
                            tempDistancePower2 = tmV;
                          }

                        }else{
                          double slope = (mValue - cValue)/(tempCValue - cValue);
                          tmV = slope*slope*(iNeigh*iNeigh*(searchRadioRow-1)*(searchRadioRow-1)*calcRowGridSize*calcRowGridSize
                                           + jNeigh*jNeigh*(searchRadioCol-1)*(searchRadioCol-1)*calcColGridSize*calcColGridSize);

//                            tmV = slope*slope*(iNeigh*iNeigh*calcRowGridSize*calcRowGridSize
//                                             + jNeigh*jNeigh*calcColGridSize*calcColGridSize);

//                          tmV = slope*slope*(iNeigh*iNeigh*measureRowGridSize*measureRowGridSize
//                                           + jNeigh*jNeigh*measureColGridSize*measureColGridSize);

                          if(tmV<tempDistancePower2){
                            tempDistancePower2 = tmV;
                          }
                        }

                      }

                    }

                  }
                }


                if(tempDistancePower2<distanceStandardPower2){
                  getADta = true;
                }

                if(true == getADta){
                  this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,sqrt(tempDistancePower2));
                  passCount++;
                }else{
                  this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,-1);
                }
                considerCount++;
              }
              */

              /*

            }

          }
        }
      }
    }
    break;
    */

    
    case HANDLE_MODEL(ADAC):
    default:
    {
      searchRadioRow = TrimFloat_Up(this->standardParam.distance/calcRowGridSize,0.02);
      searchRadioCol = TrimFloat_Up(this->standardParam.distance/calcColGridSize,0.02);

      vector< pair<double,GridPoint> > presortResult =  presort(searchRadioRow,searchRadioCol,calcRowGridSize,calcColGridSize);

      switch(checkType)
      {
        case CHECKTYPE(ABS_DTA_MidValueWay):
        {
          actualMaxMeasureDose = (*measureDoseMatrix)[getMaxValuePoint(*measureDoseMatrix)];
          actualMaxCalcDose = (*calcDoseMatrix)[getMaxValuePoint(*calcDoseMatrix)];
          
          for(int j= 0;j<cols;j++){
            for(int i=0;i<rows;i++){
              //consider the detector point only
              if(true == MainFormTempValue.detectorArray.at(i,j,0)){
                //consider the point dose should larger than threshod
                correspondRowInCalc = (i-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
                correspondColInCalc = (j-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

                if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<calcDoseMatrix->getRowLength()
                  &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<calcDoseMatrix->getColLength()){

                  tempActualMeasureValue = measureDoseMatrix->at(i,j,0);
                  tempActualCalcValue = calcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
                  
                  tempNormMeasureValue = 100*tempActualMeasureValue/actualMaxMeasureDose;
                  tempNormCalcValue = 100*tempActualCalcValue/actualMaxCalcDose; //is actualMaxCalcDose, sure


                  if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){
                    
                    tempPercentDoseDifference = 100*fabs(tempActualMeasureValue - tempActualCalcValue)/tempActualCalcValue;

                    //tempPercentDoseDifference = fabs(tempNormMeasureValue - tempNormCalcValue);

                    if(fabs(tempActualMeasureValue - tempActualCalcValue)<=this->standardParam.actualDosegap ||
                       tempPercentDoseDifference<=this->standardParam.percentDifference){

                      passCount++;
                      this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,0);

                    }else{
                      
                      firstLable = (tempActualMeasureValue - tempActualCalcValue)>=0?1:-1;

                      getADta = false;

                      for(vector< pair<double,GridPoint> >::iterator iterat = presortResult.begin();iterat != presortResult.end();iterat++){
                        tempDistancePower2 = iterat->first;

                        /*
                        if(tempDistancePower2>(distanceStandardPower2+0.5) ){
                          break;
                        }
                        */

                        iOffSet = iterat->second.row;
                        jOffSet = iterat->second.col;

                        tempValueGap = measureDoseMatrix->at(i,j,0) - calcDoseMatrix->at(iOffSet + correspondRowInCalc,
                                                                                      jOffSet + correspondColInCalc,
                                                                                      0);

                        if(firstLable*tempValueGap<=0){

                          dtaValue = fabs(DTAValueCalculate(tempActualMeasureValue,
                                                           calcDoseMatrix,
                                                           correspondRowInCalc,
                                                           correspondColInCalc,
                                                           iOffSet + correspondRowInCalc,
                                                           jOffSet + correspondColInCalc,
                                                           this->standardParam.distance));

                          if(dtaValue<31000.0 &&dtaValue<=1){
                            getADta = true;
                            break;
                          }

                        }else if(firstLable*tempValueGap==0.0){
                          dtaValue = sqrt(tempDistancePower2);
                          getADta = true;
                          break;
                        }

                      }


                      if(true == getADta){
                        this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,sqrt(dtaValue));
                        passCount++;
                      }else{
                        this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,-1);
                      }

                    }

                    considerCount++;
                  }

                }

              }
            }
          }
        }
        break;

        case CHECKTYPE(REL_DTA_MidValueWay):
        {
          for(int j= 0;j<cols;j++){
            for(int i=0;i<rows;i++){
              //consider the detector point only
              if(true == MainFormTempValue.detectorArray.at(i,j,0)){
                //consider the point dose should larger than threshod
                correspondRowInCalc = (i-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
                correspondColInCalc = (j-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

                if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<calcDoseMatrix->getRowLength()
                  &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<calcDoseMatrix->getColLength()){

                  tempNormMeasureValue = measureDoseMatrix->at(i,j,0);
                  tempNormCalcValue = calcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
                  
                  firstLable = (tempNormMeasureValue - tempNormCalcValue)>0.0?1:-1;

                  if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){

                    if(fabs(tempNormMeasureValue - tempNormCalcValue)<=this->standardParam.percentDifference ){
                      passCount++;
                      this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,0);
                    }else{

                      getADta = false;

                      for(vector< pair<double,GridPoint> >::iterator iterat = presortResult.begin();iterat != presortResult.end();iterat++){
                          tempDistancePower2 = iterat->first;

                        /*
                        if(tempDistancePower2>distanceStandardPower2){
                            break;
                        }
                        */

                        iOffSet = iterat->second.row;
                        jOffSet = iterat->second.col;

                        tempValueGap = measureDoseMatrix->at(i,j,0) - calcDoseMatrix->at(iOffSet + correspondRowInCalc,
                                                                                      jOffSet + correspondColInCalc,
                                                                                      0);

                        if(firstLable*tempValueGap<=0){
                          dtaValue = fabs(DTAValueCalculate(tempNormMeasureValue,
                                                       calcDoseMatrix,
                                                       correspondRowInCalc,
                                                       correspondColInCalc,
                                                       iOffSet + correspondRowInCalc,
                                                       jOffSet + correspondColInCalc,
                                                       this->standardParam.distance));

                          if(dtaValue<31000.0 && dtaValue<=1.0){
                            getADta = true;
                            break;
                          }

                        }
                        else if(firstLable*tempValueGap==0){
                          dtaValue = sqrt(tempDistancePower2);
                          getADta = true;
                          break;
                        }

                      }

                      if(true == getADta){
                        this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,dtaValue);
                        passCount++;
                      }else{
                        this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,-1);
                      }

                    }

                    considerCount++;
                  }

                }

              }
            }
          }

        }
        break;

        default:
        {
          RunningLog::writeLog("Unkable checkType",__LINE__);
          return;
        }
        break;
      }

    }
    break;
  }

  this->checkedRecord.getSingleDTAResult()->totalPassPercent = 100*((double)passCount)/considerCount;
  this->checkedRecord.getSingleDTAResult()->totalComparedCount = considerCount;
  this->checkedRecord.getSingleDTAResult()->passedCount = passCount;


  measureDoseMatrix = NULL;
  calcDoseMatrix = NULL;
}
//------------------------------------------------------------------------------
void DoseCheck::dtaCheck_SamePositionWay(CHECKTYPE checkType,Dose* NormMeasureDose,Dose* NormCalcDose,HANDLE_MODEL handle_model){

  MatrixData<double>* measureDoseMatrix = NULL;
  MatrixData<double>* calcDoseMatrix = NULL;

  int rows,cols;

  double tempNormMeasureValue,tempNormCalcValue;
  double tempValueGap;
  int passCount = 0;
  int considerCount = 0;

  int measureFirstAlignmentRow,measureFirstAlignmentCol;
  int calcFirstAlignmentRow,calcFirstAlignmentCol;

  int rowSegments,colSegments;

  int correspondRowInCalc,correspondColInCalc;

  bool getADta;


  measureDoseMatrix = NormMeasureDose->getDoseMatrix();
  calcDoseMatrix = NormCalcDose->getDoseMatrix();

  //sysc the standardParam
  this->standardParam = MainFormTempValue.checkStandardParam;

  rows = measureDoseMatrix->getRowLength();
  cols = measureDoseMatrix->getColLength();

  this->checkedRecord.getSingleDTAResult()->everyPointResults.allocate(rows,cols,1);

  measureFirstAlignmentRow = NormMeasureDose->getFirstAlignmentCentral()->row;
  measureFirstAlignmentCol = NormMeasureDose->getFirstAlignmentCentral()->col;

  calcFirstAlignmentRow = NormCalcDose->getFirstAlignmentCentral()->row;
  calcFirstAlignmentCol = NormCalcDose->getFirstAlignmentCentral()->col;

  rowSegments = NormMeasureDose->getSegments()[0];
  colSegments = NormMeasureDose->getSegments()[1];

  getADta = false;
  
  for(int j= 0;j<cols;j++){
    for(int i=0;i<rows;i++){
      //consider the detector point only
      if(true == MainFormTempValue.detectorArray.at(i,j,0)){
        //consider the point dose should larger than threshod

        correspondRowInCalc = (i-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
        correspondColInCalc = (j-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

        if(correspondRowInCalc>=0 && correspondRowInCalc<calcDoseMatrix->getRowLength() &&
             correspondColInCalc>=0 && correspondColInCalc<calcDoseMatrix->getColLength()){

          tempNormMeasureValue = measureDoseMatrix->at(i,j,0);
          tempNormCalcValue = calcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
          if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){

            getADta = false;

            tempValueGap = fabs(measureDoseMatrix->at(i,j,0) - calcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0));

            if(tempValueGap<=this->standardParam.doseUncertainty){
              getADta = true;
            }

            if(true == getADta){
              this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,0);
              passCount++;
            }else{
              this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,-1);
            }
            considerCount++;

          }

        }

      }
    }
  }

  this->checkedRecord.getSingleDTAResult()->totalPassPercent = 100*((double)passCount)/considerCount;
  this->checkedRecord.getSingleDTAResult()->totalComparedCount = considerCount;
  this->checkedRecord.getSingleDTAResult()->passedCount = passCount;
  

  measureDoseMatrix = NULL;
  calcDoseMatrix = NULL;
}




//---------------------------Private:calculate each dta value---------------------------------
double DoseCheck::DTAValueCalculate(double measureValue,MatrixData<double>* calcMatrix,
                                    int cCentralRowPos,int cCentralColPos,int cSearchingRowPos,int cSearchingColPos,double distanceStandard){
  double result = 32000.0;
  double distance;
  distance = sqrt(pow(cSearchingRowPos - cCentralRowPos,2) + pow(cSearchingColPos - cCentralColPos,2));

  double tempCalcValue,tempSearchingValue,movedCalcValue;

  double slope = 0.0;
  double tempDtaToOne;

  tempCalcValue = calcMatrix->at(cCentralRowPos,cCentralColPos,0);

  tempSearchingValue = calcMatrix->at(cSearchingRowPos,cSearchingColPos,0);
  
  if(distance<=distanceStandard){

    if(cSearchingRowPos>cCentralRowPos && cSearchingColPos>=cCentralColPos){

      if(cSearchingColPos == cCentralColPos){
        movedCalcValue = calcMatrix->at(cSearchingRowPos-1,cSearchingColPos,0);

        if( (movedCalcValue - tempSearchingValue) != 0.0){
          slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
        }

          tempDtaToOne = fabs(cSearchingRowPos - fabs(slope*1.0) - cCentralRowPos)/distanceStandard;

          if(tempDtaToOne<31000.0){
            result = tempDtaToOne;
          }

          return result;
        

      }

        movedCalcValue = calcMatrix->at(cSearchingRowPos-1,cSearchingColPos,0);

        if( (movedCalcValue - tempSearchingValue) != 0.0){
          slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
        }

        tempDtaToOne = sqrt(pow(cSearchingRowPos - fabs(slope*1.0) - cCentralRowPos,2) + pow(cSearchingColPos - cCentralColPos,2))/distanceStandard;

        if(tempDtaToOne<31000.0){
          result = tempDtaToOne;
        }

        movedCalcValue = calcMatrix->at(cSearchingRowPos,cSearchingColPos - 1,0);

        if( (movedCalcValue - tempSearchingValue) != 0.0){
          slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
        }

        tempDtaToOne = sqrt(pow(cSearchingRowPos - cCentralRowPos,2) + pow(cSearchingColPos - fabs(slope*1.0) - cCentralColPos,2))/distanceStandard;

        if(tempDtaToOne<result){
          result = tempDtaToOne;
        }

        return result;

    }

    if(cSearchingRowPos>=cCentralRowPos && cSearchingColPos<cCentralColPos){

      if(cSearchingRowPos == cCentralRowPos){
        movedCalcValue = calcMatrix->at(cSearchingRowPos,cSearchingColPos + 1,0);

        if( (movedCalcValue - tempSearchingValue) != 0.0){
          slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
        }

        tempDtaToOne = fabs(cSearchingColPos + fabs(slope*1.0) - cCentralColPos)/distanceStandard;

        if(tempDtaToOne<31000.0){
          result = tempDtaToOne;
        }

        return result;

      }

        movedCalcValue = calcMatrix->at(cSearchingRowPos,cSearchingColPos + 1,0);

        if( (movedCalcValue - tempSearchingValue) != 0.0){
          slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
        }

        tempDtaToOne = sqrt(pow(cSearchingRowPos - cCentralRowPos,2) + pow(cSearchingColPos + fabs(slope*1.0) - cCentralColPos,2))/distanceStandard;

        if(tempDtaToOne<31000.0){
          result = tempDtaToOne;
        }

        movedCalcValue = calcMatrix->at(cSearchingRowPos - 1,cSearchingColPos,0);

        if( (movedCalcValue - tempSearchingValue) != 0.0){
          slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
        }

        tempDtaToOne = sqrt(pow(cSearchingRowPos  - fabs(slope*1.0) - cCentralRowPos,2) + pow(cSearchingColPos - cCentralColPos,2))/distanceStandard;

        if(tempDtaToOne<result){
          result = tempDtaToOne;
        }

        return result;

    }

    if(cSearchingRowPos<cCentralRowPos && cSearchingColPos<=cCentralColPos){

      if(cSearchingColPos == cCentralColPos){
        movedCalcValue = calcMatrix->at(cSearchingRowPos + 1,cSearchingColPos,0);

        if( (movedCalcValue - tempSearchingValue) != 0.0){
          slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
        }

        tempDtaToOne = fabs(cSearchingRowPos + fabs(slope*1.0) - cCentralRowPos)/distanceStandard;

        if(tempDtaToOne<31000.0){
          result = tempDtaToOne;
        }

        return result;

      }

      movedCalcValue = calcMatrix->at(cSearchingRowPos,cSearchingColPos+1,0);

      if( (movedCalcValue - tempSearchingValue) != 0.0){
        slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
      }

      tempDtaToOne = sqrt(pow(cSearchingRowPos - cCentralRowPos,2) + pow(cSearchingColPos + fabs(slope*1.0) - cCentralColPos,2))/distanceStandard;

      if(tempDtaToOne<31000.0){
        result = tempDtaToOne;
      }

      movedCalcValue = calcMatrix->at(cSearchingRowPos + 1,cSearchingColPos,0);

      if( (movedCalcValue - tempSearchingValue) != 0.0){
        slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
      }

      tempDtaToOne = sqrt(pow(cSearchingRowPos  + fabs(slope*1.0) - cCentralRowPos,2) + pow(cSearchingColPos - cCentralColPos,2))/distanceStandard;

      if(tempDtaToOne<result){
          result = tempDtaToOne;
      }

      return result;

    }

    if( cSearchingRowPos>cCentralRowPos || cSearchingColPos<=cCentralColPos ){
      return result;
    }

    if(cSearchingRowPos == cCentralRowPos){
    
      movedCalcValue = calcMatrix->at(cSearchingRowPos,cSearchingColPos - 1,0);

      if( (movedCalcValue - tempSearchingValue) != 0.0){
        slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
      }

      tempDtaToOne = fabs(cSearchingColPos - fabs(slope*1.0) - cCentralColPos)/distanceStandard;

      if(tempDtaToOne<31000.0){
        result = tempDtaToOne;
      }

      return result;

    }

      movedCalcValue = calcMatrix->at(cSearchingRowPos + 1,cSearchingColPos,0);

      if( (movedCalcValue - tempSearchingValue) != 0.0){
        slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
      }

      tempDtaToOne = sqrt(pow(cSearchingRowPos + fabs(slope*1.0) - cCentralRowPos,2) + pow(cSearchingColPos - cCentralColPos,2))/distanceStandard;

      if(tempDtaToOne<31000.0){
        result = tempDtaToOne;
      }

      movedCalcValue = calcMatrix->at(cSearchingRowPos,cSearchingColPos - 1,0);

      if( (movedCalcValue - tempSearchingValue) != 0.0){
        slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
      }

      tempDtaToOne = sqrt(pow(cSearchingRowPos - cCentralRowPos,2) + pow(cSearchingColPos - fabs(slope*1.0) - cCentralColPos,2))/distanceStandard;

      if(tempDtaToOne<result){
        result = tempDtaToOne;
      }

      return result;

    
  }

  if( (distance<=distanceStandard || (distanceStandard + 1.0)<distance ) && (distance<=(distanceStandard+1.0) || distance>8.0 ) ){ //Cut in 8mm
    return result;
  }
  
  if(cSearchingRowPos>cCentralRowPos && cSearchingColPos>=cCentralColPos){
    
      movedCalcValue = calcMatrix->at(cSearchingRowPos-1,cSearchingColPos,0);

      if( (movedCalcValue - tempSearchingValue) != 0.0){
        slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
      }

      tempDtaToOne = sqrt(pow(cSearchingRowPos - fabs(slope*1.0) - cCentralRowPos,2) + pow(cSearchingColPos - cCentralColPos,2))/distanceStandard;

      if(tempDtaToOne<31000.0){
        result = tempDtaToOne;
      }

      movedCalcValue = calcMatrix->at(cSearchingRowPos,cSearchingColPos - 1,0);

      if( (movedCalcValue - tempSearchingValue) != 0.0){
        slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
      }

      tempDtaToOne = sqrt(pow(cSearchingRowPos - cCentralRowPos,2) + pow(cSearchingColPos - fabs(slope*1.0) - cCentralColPos,2))/distanceStandard;

      if(tempDtaToOne<result){
        result = tempDtaToOne;
      }

      return result;

  }

  if(cSearchingRowPos>=cCentralRowPos && cSearchingColPos<cCentralColPos){

      movedCalcValue = calcMatrix->at(cSearchingRowPos,cSearchingColPos + 1,0);

      if( (movedCalcValue - tempSearchingValue) != 0.0){
        slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
      }

      tempDtaToOne = sqrt(pow(cSearchingRowPos - cCentralRowPos,2) + pow(cSearchingColPos + fabs(slope*1.0) - cCentralColPos,2))/distanceStandard;

      if(tempDtaToOne<31000.0){
        result = tempDtaToOne;
      }

      movedCalcValue = calcMatrix->at(cSearchingRowPos - 1,cSearchingColPos,0);

      if( (movedCalcValue - tempSearchingValue) != 0.0){
        slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
      }

      tempDtaToOne = sqrt(pow(cSearchingRowPos - fabs(slope*1.0) - cCentralRowPos,2) + pow(cSearchingColPos - cCentralColPos,2))/distanceStandard;

      if(tempDtaToOne<result){
        result = tempDtaToOne;
      }

      return result;

  }

  if(cSearchingRowPos<cCentralRowPos && cSearchingColPos<=cCentralColPos){

      movedCalcValue = calcMatrix->at(cSearchingRowPos,cSearchingColPos + 1,0);

      if( (movedCalcValue - tempSearchingValue) != 0.0){
        slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
      }

      tempDtaToOne = sqrt(pow(cSearchingRowPos - cCentralRowPos,2) + pow(cSearchingColPos + fabs(slope*1.0) - cCentralColPos,2))/distanceStandard;

      if(tempDtaToOne<31000.0){
        result = tempDtaToOne;
      }

      movedCalcValue = calcMatrix->at(cSearchingRowPos + 1,cSearchingColPos,0);

      if( (movedCalcValue - tempSearchingValue) != 0.0){
        slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
      }

      tempDtaToOne = sqrt(pow(cSearchingRowPos + fabs(slope*1.0) - cCentralRowPos,2) + pow(cSearchingColPos - cCentralColPos,2))/distanceStandard;

      if(tempDtaToOne<result){
        result = tempDtaToOne;
      }

      return result;

  }

  if( cSearchingRowPos>cCentralRowPos || cSearchingColPos<=cCentralColPos ){
    return result;
  }

  movedCalcValue = calcMatrix->at(cSearchingRowPos + 1,cSearchingColPos,0);

  if( (movedCalcValue - tempSearchingValue) != 0.0){
    slope =(measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
  }

  tempDtaToOne = sqrt(pow(cSearchingRowPos +  fabs(slope*1.0) - cCentralRowPos,2) + pow(cSearchingColPos - cCentralColPos,2))/distanceStandard;

  if(tempDtaToOne<31000.0){
    result = tempDtaToOne;
  }

  movedCalcValue = calcMatrix->at(cSearchingRowPos,cSearchingColPos - 1,0);

  if( (movedCalcValue - tempSearchingValue) != 0.0){
    slope = (measureValue - tempSearchingValue)/(movedCalcValue - tempSearchingValue);
  }

  tempDtaToOne = sqrt(pow(cSearchingRowPos - cCentralRowPos,2) + pow(cSearchingColPos - fabs(slope*1.0) - cCentralColPos,2))/distanceStandard;

  if(tempDtaToOne<result){
    result = tempDtaToOne;
  }

  return result;

}
//-------------------------------------gammaCheck-------------------------------
void DoseCheck::gammaCheck(CHECKTYPE checkType,Dose* measureDose,Dose* calcDose,HANDLE_MODEL handle_model){

  MatrixData<double>* measureDoseMatrix = NULL;
  MatrixData<double>* calcDoseMatrix = NULL;


  int rows,cols;

  double tempActualMeasureValue,tempActualCalcValue;
  double tempNormMeasureValue,tempNormCalcValue;
  double tempPercentDoseDifference;
  double actualMaxMeasureDose,actualMaxCalcDose;
  double tempSubCalcValue;


  double tempValueGap,tempValueGapPartPower2,tempDistancePartPower2,tempGammaPower2,tempGamma;
  int passCount = 0;
  int considerCount = 0;

  int measureFirstAlignmentRow,measureFirstAlignmentCol;
  int calcFirstAlignmentRow,calcFirstAlignmentCol;

  int rowSegments,colSegments;

  int firstLabel;

  int correspondRowInCalc,correspondColInCalc;

  double calcRowGridSize,calcColGridSize;
  int searchRadioRow,searchRadioCol;

  double localMinGammaPower2 = DBL_MAX;
  double tempDtaValueToOnePow2;


  int iOffSet,jOffSet;
  double distanceStandardPower2,doseGapStandardPower2;

  bool isbreak;

  bool usedDTAOnce;

  measureDoseMatrix = measureDose->getDoseMatrix();
  calcDoseMatrix = calcDose->getDoseMatrix();

  //sysc the standardParam
  this->standardParam = MainFormTempValue.checkStandardParam;

  rows = measureDoseMatrix->getRowLength();
  cols = measureDoseMatrix->getColLength();

  this->checkedRecord.getSingleGammaResult()->everyPointResults.allocate(rows,cols,1);

  measureFirstAlignmentRow = measureDose->getFirstAlignmentCentral()->row;
  measureFirstAlignmentCol = measureDose->getFirstAlignmentCentral()->col;

  calcFirstAlignmentRow = calcDose->getFirstAlignmentCentral()->row;
  calcFirstAlignmentCol = calcDose->getFirstAlignmentCentral()->col;

  rowSegments = measureDose->getSegments()[0];
  colSegments = measureDose->getSegments()[1];

  calcRowGridSize = measureDose->getGridSizes()[0]/rowSegments;
  calcColGridSize = measureDose->getGridSizes()[1]/colSegments;


  distanceStandardPower2 = this->standardParam.distance*this->standardParam.distance;
  doseGapStandardPower2 = this->standardParam.percentDifference*this->standardParam.percentDifference;

  isbreak = false;

  switch(handle_model)
  {
    case HANDLE_MODEL(SNDAC):
    {
      searchRadioRow = TrimFloat_Up(this->standardParam.distance/calcRowGridSize,0.02);
      searchRadioCol = TrimFloat_Up(this->standardParam.distance/calcColGridSize,0.02);
      vector< pair<double,GridPoint> > presortResult =  presort(searchRadioRow,searchRadioCol,calcRowGridSize,calcColGridSize);

      for(int j= 0;j<cols;j++){
        for(int i=0;i<rows;i++){
        //consider the detector point only
          if(true == MainFormTempValue.detectorArray.at(i,j,0)){
            //consider the point dose should larger than threshod
            correspondRowInCalc = (i-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
            correspondColInCalc = (j-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

            if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<calcDoseMatrix->getRowLength()
              &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<calcDoseMatrix->getColLength()){

              tempNormMeasureValue = measureDoseMatrix->at(i,j,0);
              tempNormCalcValue = calcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
              if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){

                isbreak = false;

                localMinGammaPower2 = DBL_MAX;

                for(vector< pair<double,GridPoint> >::iterator iterat = presortResult.begin();iterat != presortResult.end();iterat++){

                  if(true==isbreak){
                    break;
                  }

                  iOffSet = iterat->second.row;
                  jOffSet = iterat->second.col;


                  tempValueGap = measureDoseMatrix->at(i,j,0) - calcDoseMatrix->at(iOffSet + correspondRowInCalc,
                                                                                   jOffSet + correspondColInCalc,
                                                                                      0);

                  tempValueGapPartPower2 = tempValueGap*tempValueGap/doseGapStandardPower2;

                  tempDistancePartPower2 = iterat->first/distanceStandardPower2;

                  tempGammaPower2 = tempValueGapPartPower2 + tempDistancePartPower2;

                  if(tempGammaPower2<localMinGammaPower2){
                    localMinGammaPower2 = tempGammaPower2;
                  }

                  //pre-sort work
                  if(tempDistancePartPower2>localMinGammaPower2 || tempDistancePartPower2>1){
                    isbreak = true;
                  }

                }

                tempGamma = sqrt(localMinGammaPower2);
                this->checkedRecord.getSingleGammaResult()->everyPointResults.modifyValue(i,j,0,tempGamma);
            
                if(tempGamma<=1){
                  passCount++;
                }


                considerCount++;
              }

            }

          }
        }
      }
    }
    break;

    case HANDLE_MODEL(ADAC):
    default:
    {
      //searchRadioRow = TrimFloat_Up(this->standardParam.distance/calcRowGridSize,0.02)+1;
      //searchRadioCol = TrimFloat_Up(this->standardParam.distance/calcColGridSize,0.02)+1;
      searchRadioRow = 8;
      searchRadioCol = 8;
      vector< pair<double,GridPoint> > presortResult =  presort(searchRadioRow,searchRadioCol,calcRowGridSize,calcColGridSize);
  
      switch(checkType)
      {
        case CHECKTYPE(ABS_GAMMA):
        {
          actualMaxMeasureDose = (*measureDoseMatrix)[getMaxValuePoint(*measureDoseMatrix)];
          actualMaxCalcDose = (*calcDoseMatrix)[getMaxValuePoint(*calcDoseMatrix)];
          
          for(int j= 0;j<cols;j++){
            for(int i=0;i<rows;i++){
              //consider the detector point only
              if(true == MainFormTempValue.detectorArray.at(i,j,0)){
                //consider the point dose should larger than threshod
                correspondRowInCalc = (i-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
                correspondColInCalc = (j-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

                if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<calcDoseMatrix->getRowLength()
                  &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<calcDoseMatrix->getColLength()){

                  tempActualMeasureValue = measureDoseMatrix->at(i,j,0);
                  tempActualCalcValue = calcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
                  
                  tempNormMeasureValue = 100*tempActualMeasureValue/actualMaxMeasureDose;
                  tempNormCalcValue = 100*tempActualCalcValue/actualMaxCalcDose; //is actualMaxCalcDose,sure

                  if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){

                    tempPercentDoseDifference = 100*fabs(tempActualMeasureValue - tempActualCalcValue)/tempActualCalcValue;

                    if(fabs(tempActualMeasureValue - tempActualCalcValue)<=this->standardParam.actualDosegap ||
                       tempPercentDoseDifference<=this->standardParam.percentDifference){
                      //first critical:percent dose Difference or absolute dose difference
                      
                      passCount++;
                      this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,0);

                    }else{

                      //third critical:gamma critical
                      isbreak = false;

                      localMinGammaPower2 = DBL_MAX;

                      usedDTAOnce = false;

                      firstLabel = (tempActualMeasureValue - tempActualCalcValue)>=0?1:-1;

                      for(vector< pair<double,GridPoint> >::iterator iterat = presortResult.begin();iterat != presortResult.end();iterat++){

                        if(true==isbreak){
                          break;
                        }

                        iOffSet = iterat->second.row;
                        jOffSet = iterat->second.col;

                        tempSubCalcValue = calcDoseMatrix->at(iOffSet + correspondRowInCalc,
                                                              jOffSet + correspondColInCalc,
                                                              0);

                        tempValueGap = 100*(tempActualMeasureValue - tempSubCalcValue)/tempActualMeasureValue;

                        tempValueGapPartPower2 = tempValueGap*tempValueGap/doseGapStandardPower2;

                        tempDistancePartPower2 = iterat->first/distanceStandardPower2;

                        tempGammaPower2 = sqrt(tempValueGapPartPower2 + tempDistancePartPower2);

                        if(tempGammaPower2<localMinGammaPower2){
                          localMinGammaPower2 = tempGammaPower2;
                        }

                        //pre-sort work
                        /*
                        if(tempDistancePartPower2>localMinGammaPower2 || tempDistancePartPower2>1){
                          isbreak = true;
                        }
                        */

                        if(localMinGammaPower2<=1){
                          if(firstLabel*(tempActualMeasureValue - tempSubCalcValue)<=0 && !usedDTAOnce){
                            usedDTAOnce = true;

                            tempDtaValueToOnePow2 = pow(DTAValueCalculate(tempActualMeasureValue,
                                                                                 calcDoseMatrix,
                                                                                 correspondRowInCalc,
                                                                                 correspondColInCalc,
                                                                                 iOffSet + correspondRowInCalc,
                                                                                 jOffSet + correspondColInCalc,
                                                                                 this->standardParam.distance),2);

                            if(tempDtaValueToOnePow2<localMinGammaPower2){
                              localMinGammaPower2 = tempDtaValueToOnePow2;
                            }
                          }
                        }

                        if(firstLabel*(tempActualMeasureValue - tempSubCalcValue)<=0 && !usedDTAOnce){
                          usedDTAOnce = true;

                          tempDtaValueToOnePow2 = pow(DTAValueCalculate(tempActualMeasureValue,
                                                                               calcDoseMatrix,
                                                                               correspondRowInCalc,
                                                                               correspondColInCalc,
                                                                               iOffSet + correspondRowInCalc,
                                                                               jOffSet + correspondColInCalc,
                                                                               this->standardParam.distance),2);


                          if(tempDtaValueToOnePow2<localMinGammaPower2){
                            localMinGammaPower2 = tempDtaValueToOnePow2;
                          }
                        }

                      }

                      tempGamma = sqrt(localMinGammaPower2);
                      this->checkedRecord.getSingleGammaResult()->everyPointResults.modifyValue(i,j,0,tempGamma);
            
                      if(tempGamma<=1){
                        passCount++;
                      }

                    }

                    considerCount++;
                  }

                }

              }
            }
          }
        }
        break;

        case CHECKTYPE(REL_GAMMA):
        {
          for(int j= 0;j<cols;j++){
            for(int i=0;i<rows;i++){
              //consider the detector point only
              if(true == MainFormTempValue.detectorArray.at(i,j,0)){
                //consider the point dose should larger than threshod
                correspondRowInCalc = (i-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
                correspondColInCalc = (j-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

                if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<calcDoseMatrix->getRowLength()
                  &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<calcDoseMatrix->getColLength()){

                  tempNormMeasureValue = measureDoseMatrix->at(i,j,0);
                  tempNormCalcValue = calcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);

                  if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){

                    if(fabs(tempNormMeasureValue - tempNormCalcValue)<=this->standardParam.percentDifference ){
                      passCount++;
                      this->checkedRecord.getSingleDTAResult()->everyPointResults.modifyValue(i,j,0,0);
                    }else{
                      isbreak = false;

                      localMinGammaPower2 = DBL_MAX;

                      firstLabel = (tempNormMeasureValue - tempNormCalcValue)>=0?1:-1;

                      usedDTAOnce = false;
                      
                      for(vector< pair<double,GridPoint> >::iterator iterat = presortResult.begin();iterat != presortResult.end();iterat++){

                        if(true==isbreak){
                          break;
                        }

                        iOffSet = iterat->second.row;
                        jOffSet = iterat->second.col;

                        tempValueGap = measureDoseMatrix->at(i,j,0) - calcDoseMatrix->at(iOffSet + correspondRowInCalc,
                                                                                         jOffSet + correspondColInCalc,
                                                                                         0);

                        tempValueGapPartPower2 = tempValueGap*tempValueGap/doseGapStandardPower2;

                        tempDistancePartPower2 = iterat->first/distanceStandardPower2;

                        tempGammaPower2 = tempValueGapPartPower2 + tempDistancePartPower2;

                        if(tempGammaPower2<localMinGammaPower2){
                          localMinGammaPower2 = tempGammaPower2;
                        }


                        if(localMinGammaPower2<=1){
                          if(firstLabel*tempValueGap<=0 && !usedDTAOnce){
                            usedDTAOnce = true;

                            tempDtaValueToOnePow2 = pow(DTAValueCalculate(tempNormMeasureValue,
                                                                          calcDoseMatrix,
                                                                          correspondRowInCalc,
                                                                          correspondColInCalc,
                                                                          iOffSet + correspondRowInCalc,
                                                                          jOffSet + correspondColInCalc,
                                                                          this->standardParam.distance),2);

                            if(tempDtaValueToOnePow2<localMinGammaPower2){
                              localMinGammaPower2 = tempDtaValueToOnePow2;
                            }
                          }
                        }

                        if(firstLabel*tempValueGap<=0 && !usedDTAOnce){
                          usedDTAOnce = true;

                          tempDtaValueToOnePow2 = pow(DTAValueCalculate(tempNormMeasureValue,
                                                                        calcDoseMatrix,
                                                                        correspondRowInCalc,
                                                                        correspondColInCalc,
                                                                        iOffSet + correspondRowInCalc,
                                                                        jOffSet + correspondColInCalc,
                                                                        this->standardParam.distance),2);


                          if(tempDtaValueToOnePow2<localMinGammaPower2){
                            localMinGammaPower2 = tempDtaValueToOnePow2;
                          }
                        }


                        //pre-sort work
                        /*
                        if(tempDistancePartPower2>localMinGammaPower2 || tempDistancePartPower2>1){
                          isbreak = true;
                        }
                        */

                      }

                      tempGamma = sqrt(localMinGammaPower2);
                      this->checkedRecord.getSingleGammaResult()->everyPointResults.modifyValue(i,j,0,tempGamma);
            
                      if(tempGamma<=1){
                        passCount++;
                      }
                    }

                    considerCount++;
                  }

                }

              }
            }
          }
        }
        break;

        default:
        {
          RunningLog::writeLog("Unkable checkType",__LINE__);
          return;
        }
        break;
      }

    }
    break;
  }

  this->checkedRecord.getSingleGammaResult()->totalPassPercent = 100*((double)passCount)/considerCount;
  this->checkedRecord.getSingleGammaResult()->totalComparedCount = considerCount;
  this->checkedRecord.getSingleGammaResult()->passedCount = passCount;

  measureDoseMatrix = NULL;
  calcDoseMatrix = NULL;
}

//-----------------------------Overload:doseDifferenceCheck(GridPoint normPoint)-----------------------------------
void DoseCheck::doseDifferenceCheck(GridPoint normPoint){
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  /*temp Values*/
  HandledPairDose* tempHandledPairDose = NULL;
  Dose* tempMeasureDose = NULL;
  Dose* tempCalcDose = NULL;

  Dose* tempNormMeasureDose = NULL;
  Dose* tempNormCalcDose = NULL;

  HANDLE_MODEL handle_model;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }

  handle_model = globalMem->getHandel_Model();
  
  tempHandledPairDose = new HandledPairDose();

  *tempHandledPairDose = *handledPairDose;

  tempHandledPairDose->normlize((NORMLIZE_TYPE)NORM_DOUBLE_Abs,normPoint,handle_model);

  tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();
  if(NULL == tempMeasureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }
  tempCalcDose = tempHandledPairDose->getAbs_NormCalculateDoseHandled();
  if(NULL == tempCalcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }

  tempNormMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();
  if(NULL == tempNormMeasureDose){
    RunningLog::writeLog("The NormMeasureDose is NULL;",__LINE__);
    return;
  }

  tempNormCalcDose = tempHandledPairDose->getAbs_NormCalculateDoseHandled();
  if(NULL == tempNormCalcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }

  this->checkedRecord.getSingleDDResult()->manualSelectMeasureNormValue = handledPairDose->getManualSpecialMeasureNormValue();
  this->checkedRecord.getSingleDDResult()->manualSelectCalculateNormValue = handledPairDose->getManualSpecialCalcNormValue();

  this->checkedRecord.getSingleDDResult()->normValue_measure = handledPairDose->getNormValueStr_measure();
  this->checkedRecord.getSingleDDResult()->normValue_calculate = handledPairDose->getNormValueStr_calculate();

  this->checkedRecord.getSingleDDResult()->normPosition_measure = *tempHandledPairDose->getNormlizationPosition_Measure();
  this->checkedRecord.getSingleDDResult()->normPosition_calculate = *tempHandledPairDose->getNormlizationPosition_Calculate();


  doseDifferenceCheck(tempMeasureDose,tempNormMeasureDose,tempCalcDose,tempNormCalcDose,handle_model);

  globalMem = NULL;
  handledPairDose = NULL;

  TryToDelete<HandledPairDose>(tempHandledPairDose);
  tempHandledPairDose = NULL;
  tempMeasureDose = NULL;
  tempCalcDose = NULL;
  tempNormMeasureDose = NULL;
  tempNormCalcDose = NULL;
}
//-----------------------------Overload:dtaCheck(GridPoint normPoint)-----------------------------------
void DoseCheck::dtaCheck_MidValueWay(CHECKTYPE checkType,GridPoint normPoint){
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  /*temp Values*/
  HandledPairDose* tempHandledPairDose = NULL;
  Dose* tempMeasureDose = NULL;
  Dose* tempCalcDose = NULL;

  HANDLE_MODEL handle_model;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }

  handle_model = globalMem->getHandel_Model();

  tempHandledPairDose = new HandledPairDose();

  *tempHandledPairDose = *handledPairDose;

  if(CHECKTYPE(ABS_DTA_MidValueWay)==checkType){
    tempHandledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),normPoint,handle_model);
  }else if(CHECKTYPE(REL_DTA_MidValueWay)==checkType){

    tempHandledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),normPoint,handle_model);
  }

  switch(handle_model)
  {
    case HANDLE_MODEL(SNDAC):
    {
      tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();

      if(CHECKTYPE(ABS_GAMMA)==checkType){

        tempCalcDose = tempHandledPairDose->getAbs_NormCalculateDoseHandled();

      }else if(CHECKTYPE(REL_GAMMA)==checkType){

        tempCalcDose = tempHandledPairDose->getRel_NormCalculateDoseHandled();
      }

    }
    break;

    case HANDLE_MODEL(ADAC):
    default:
    {
      if(CHECKTYPE(ABS_GAMMA)==checkType){

        tempMeasureDose = tempHandledPairDose->getMeasureDoseHandled();

        tempCalcDose = tempHandledPairDose->getCalculateDoseHandled();

      }else if(CHECKTYPE(REL_GAMMA)==checkType){

        tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();

        tempCalcDose = tempHandledPairDose->getRel_NormCalculateDoseHandled();
      }

    }
    break;
  }

  if(NULL == tempMeasureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }

  if(NULL == tempCalcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }


  this->checkedRecord.getSingleDTAResult()->manualSelectMeasureNormValue = handledPairDose->getManualSpecialMeasureNormValue();
  this->checkedRecord.getSingleDTAResult()->manualSelectCalculateNormValue = handledPairDose->getManualSpecialCalcNormValue();

  this->checkedRecord.getSingleDTAResult()->normValue_measure = handledPairDose->getNormValueStr_measure();
  this->checkedRecord.getSingleDTAResult()->normValue_calculate = handledPairDose->getNormValueStr_calculate();

  this->checkedRecord.getSingleDTAResult()->normPosition_measure = *tempHandledPairDose->getNormlizationPosition_Measure();
  this->checkedRecord.getSingleDTAResult()->normPosition_calculate = *tempHandledPairDose->getNormlizationPosition_Calculate();

  dtaCheck_MidValueWay(checkType,tempMeasureDose,tempCalcDose,handle_model);

  globalMem = NULL;
  handledPairDose = NULL;

  TryToDelete<HandledPairDose>(tempHandledPairDose);
  tempHandledPairDose = NULL;
  tempMeasureDose = NULL;
  tempCalcDose = NULL;
}


//-----------------------------Overload:dtaCheck(GridPoint normPoint)-----------------------------------
void DoseCheck::dtaCheck_FloatWay(CHECKTYPE checkType,GridPoint normPoint){
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  /*temp Values*/
  HandledPairDose* tempHandledPairDose = NULL;
  Dose* tempMeasureDose = NULL;
  Dose* tempCalcDose = NULL;

  HANDLE_MODEL handle_model;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }
  handle_model = globalMem->getHandel_Model();

  tempHandledPairDose = new HandledPairDose();

  *tempHandledPairDose = *handledPairDose;


  if(CHECKTYPE(ABS_DTA_MidValueWay)==checkType){
    tempHandledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),normPoint,handle_model);
  }else if(CHECKTYPE(REL_DTA_MidValueWay)==checkType){

    tempHandledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),normPoint,handle_model);
  }

  switch(handle_model)
  {
    case HANDLE_MODEL(SNDAC):
    {
      tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();

      if(CHECKTYPE(ABS_GAMMA)==checkType){

        tempCalcDose = tempHandledPairDose->getAbs_NormCalculateDoseHandled();

      }else if(CHECKTYPE(REL_GAMMA)==checkType){

        tempCalcDose = tempHandledPairDose->getRel_NormCalculateDoseHandled();
      }

    }
    break;

    case HANDLE_MODEL(ADAC):
    default:
    {
      if(CHECKTYPE(ABS_GAMMA)==checkType){

        tempMeasureDose = tempHandledPairDose->getMeasureDoseHandled();

        tempCalcDose = tempHandledPairDose->getCalculateDoseHandled();

      }else if(CHECKTYPE(REL_GAMMA)==checkType){

        tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();

        tempCalcDose = tempHandledPairDose->getRel_NormCalculateDoseHandled();
      }

    }
    break;
  }

  if(NULL == tempMeasureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }

  if(NULL == tempCalcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }

  this->checkedRecord.getSingleDTAResult()->manualSelectMeasureNormValue = handledPairDose->getManualSpecialMeasureNormValue();
  this->checkedRecord.getSingleDTAResult()->manualSelectCalculateNormValue = handledPairDose->getManualSpecialCalcNormValue();

  this->checkedRecord.getSingleDTAResult()->normValue_measure = handledPairDose->getNormValueStr_measure();
  this->checkedRecord.getSingleDTAResult()->normValue_calculate = handledPairDose->getNormValueStr_calculate();

  this->checkedRecord.getSingleDTAResult()->normPosition_measure = *tempHandledPairDose->getNormlizationPosition_Measure();
  this->checkedRecord.getSingleDTAResult()->normPosition_calculate = *tempHandledPairDose->getNormlizationPosition_Calculate();

  dtaCheck_FloatWay(checkType,tempMeasureDose,tempCalcDose,handle_model);

  globalMem = NULL;
  handledPairDose = NULL;

  TryToDelete<HandledPairDose>(tempHandledPairDose);
  tempHandledPairDose = NULL;
  tempMeasureDose = NULL;
  tempCalcDose = NULL;

}

//-----------------------------Overload:dtaCheck(GridPoint normPoint)-----------------------------------
void DoseCheck::dtaCheck_SamePositionWay(CHECKTYPE checkType,GridPoint normPoint){
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  /*temp Values*/
  HandledPairDose* tempHandledPairDose = NULL;
  Dose* tempMeasureDose = NULL;
  Dose* tempCalcDose = NULL;

  HANDLE_MODEL handle_model;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }
  handle_model = globalMem->getHandel_Model();
  
  tempHandledPairDose = new HandledPairDose();

  *tempHandledPairDose = *handledPairDose;


  if(CHECKTYPE(ABS_DTA_MidValueWay)==checkType){
    tempHandledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),normPoint,handle_model);
  }else if(CHECKTYPE(REL_DTA_MidValueWay)==checkType){

    tempHandledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),normPoint,handle_model);
  }

  switch(handle_model)
  {
    case HANDLE_MODEL(SNDAC):
    {
      tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();

      if(CHECKTYPE(ABS_GAMMA)==checkType){

        tempCalcDose = tempHandledPairDose->getAbs_NormCalculateDoseHandled();

      }else if(CHECKTYPE(REL_GAMMA)==checkType){

        tempCalcDose = tempHandledPairDose->getRel_NormCalculateDoseHandled();
      }

    }
    break;

    case HANDLE_MODEL(ADAC):
    default:
    {
      if(CHECKTYPE(ABS_GAMMA)==checkType){

        tempMeasureDose = tempHandledPairDose->getMeasureDoseHandled();

        tempCalcDose = tempHandledPairDose->getCalculateDoseHandled();

      }else if(CHECKTYPE(REL_GAMMA)==checkType){

        tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();

        tempCalcDose = tempHandledPairDose->getRel_NormCalculateDoseHandled();
      }

    }
    break;
  }

  if(NULL == tempMeasureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }

  if(NULL == tempCalcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }

  this->checkedRecord.getSingleDTAResult()->manualSelectMeasureNormValue = handledPairDose->getManualSpecialMeasureNormValue();
  this->checkedRecord.getSingleDTAResult()->manualSelectCalculateNormValue = handledPairDose->getManualSpecialCalcNormValue();

  this->checkedRecord.getSingleDTAResult()->normValue_measure = handledPairDose->getNormValueStr_measure();
  this->checkedRecord.getSingleDTAResult()->normValue_calculate = handledPairDose->getNormValueStr_calculate();

  this->checkedRecord.getSingleDTAResult()->normPosition_measure = *tempHandledPairDose->getNormlizationPosition_Measure();
  this->checkedRecord.getSingleDTAResult()->normPosition_calculate = *tempHandledPairDose->getNormlizationPosition_Calculate();

  dtaCheck_SamePositionWay(checkType,tempMeasureDose,tempCalcDose,handle_model);

  globalMem = NULL;
  handledPairDose = NULL;

  TryToDelete<HandledPairDose>(tempHandledPairDose);
  tempHandledPairDose = NULL;
  tempMeasureDose = NULL;
  tempCalcDose = NULL;
}


//-----------------------------Overload:gammaCheck(GridPoint normPoint)-----------------------------------
void DoseCheck::gammaCheck(CHECKTYPE checkType,GridPoint normPoint){
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  /*temp Values*/
  HandledPairDose* tempHandledPairDose = NULL;
  Dose* tempMeasureDose = NULL;
  Dose* tempCalcDose = NULL;

  HANDLE_MODEL handle_model;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }
  handle_model = globalMem->getHandel_Model();

  tempHandledPairDose = new HandledPairDose();

  *tempHandledPairDose = *handledPairDose;


  if(CHECKTYPE(ABS_DTA_MidValueWay)==checkType){
    tempHandledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),normPoint,handle_model);
  }else if(CHECKTYPE(REL_DTA_MidValueWay)==checkType){

    tempHandledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),normPoint,handle_model);
  }

  switch(handle_model)
  {
    case HANDLE_MODEL(SNDAC):
    {
      tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();

      if(CHECKTYPE(ABS_GAMMA)==checkType){

        tempCalcDose = tempHandledPairDose->getAbs_NormCalculateDoseHandled();

      }else if(CHECKTYPE(REL_GAMMA)==checkType){

        tempCalcDose = tempHandledPairDose->getRel_NormCalculateDoseHandled();
      }

    }
    break;

    case HANDLE_MODEL(ADAC):
    default:
    {
      if(CHECKTYPE(ABS_GAMMA)==checkType){

        tempMeasureDose = tempHandledPairDose->getMeasureDoseHandled();

        tempCalcDose = tempHandledPairDose->getCalculateDoseHandled();

      }else if(CHECKTYPE(REL_GAMMA)==checkType){

        tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();

        tempCalcDose = tempHandledPairDose->getRel_NormCalculateDoseHandled();
      }

    }
    break;
  }

  if(NULL == tempMeasureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }

  if(NULL == tempCalcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }

  this->checkedRecord.getSingleDTAResult()->manualSelectMeasureNormValue = handledPairDose->getManualSpecialMeasureNormValue();
  this->checkedRecord.getSingleDTAResult()->manualSelectCalculateNormValue = handledPairDose->getManualSpecialCalcNormValue();

  this->checkedRecord.getSingleDTAResult()->normValue_measure = handledPairDose->getNormValueStr_measure();
  this->checkedRecord.getSingleDTAResult()->normValue_calculate = handledPairDose->getNormValueStr_calculate();

  this->checkedRecord.getSingleDTAResult()->normPosition_measure = *tempHandledPairDose->getNormlizationPosition_Measure();
  this->checkedRecord.getSingleDTAResult()->normPosition_calculate = *tempHandledPairDose->getNormlizationPosition_Calculate();

  gammaCheck(checkType,tempMeasureDose,tempCalcDose,handle_model);

  globalMem = NULL;
  handledPairDose = NULL;

  TryToDelete<HandledPairDose>(tempHandledPairDose);
  tempHandledPairDose = NULL;
  tempMeasureDose = NULL;
  tempCalcDose = NULL;
}



//-------------------------------BestFive_DD----------------------------------------
/*
void DoseCheck::bestFive_DDCheck(CHECKTYPE checkType){
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  Dose* measureDose = NULL;
  MatrixData<double>* measureDoseMatrix = NULL;
  Dose* calcDose = NULL;

  //Sub temp Values----------------
  HandledPairDose* tempHandledPairDose = NULL;
  Dose* tempMeasureDose = NULL;
  MatrixData<double>* tempMeasureDoseMatrix = NULL;
  Dose* tempCalcDose = NULL;
  MatrixData<double>* tempCalcDoseMatrix = NULL;
  //--------------------------------

  GridPoint tempMeasureNormPoint;

  int rows,cols;

  double tempValue;
  int unPassCount = 0;
  int considerCount = 0;

  double tempDDPass;

  int measureFirstAlignmentRow,measureFirstAlignmentCol;
  int calcFirstAlignmentRow,calcFirstAlignmentCol;

  int rowSegments,colSegments;

  int correspondRowInCalc,correspondColInCalc;
  BestFive_Single tempBestFive_Single;

  vector<pair<double,BestFive_Single> > bestFivePoints;
  GridPoint tempNormPoint;
  pair<double,BestFive_Single> tempPair;
  tempNormPoint.reset();
  tempBestFive_Single.reset();
  for(int p=0;p<5;p++){
    tempPair.first = -1;
    tempPair.second = tempBestFive_Single;
    bestFivePoints.push_back(tempPair);
  } 

  bool isbreak = false;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }

  measureDose = handledPairDose->getNormMeasureDoseHandled();
  if(NULL == measureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }
  calcDose = handledPairDose->getNormCalculateDoseHandled();
  if(NULL == calcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }

  measureDoseMatrix = measureDose->getDoseMatrix();

  //sysc the standardParam
  this->standardParam = MainFormTempValue.checkStandardParam;

  rows = measureDoseMatrix->getRowLength();
  cols = measureDoseMatrix->getColLength();

  this->checkedRecord.getBestFiveResult()->reset();

  measureFirstAlignmentRow = measureDose->getFirstAlignmentCentral()->row;
  measureFirstAlignmentCol = measureDose->getFirstAlignmentCentral()->col;

  calcFirstAlignmentRow = calcDose->getFirstAlignmentCentral()->row;
  calcFirstAlignmentCol = calcDose->getFirstAlignmentCentral()->col;
  rowSegments = measureDose->getSegments()[0];
  colSegments = measureDose->getSegments()[1];

  for(int j= 0;j<cols;j++){
    for(int i=0;i<rows;i++){
      //consider the detector point only
      if(true == MainFormTempValue.detectorArray.at(i,j,0)){
        //consider the point dose should larger than threshod
        if(measureDoseMatrix->at(i,j,0)>=this->standardParam.bestFiveDoseThreadhold){
          TryToDelete<HandledPairDose>(tempHandledPairDose);
          tempHandledPairDose = new HandledPairDose();

          *tempHandledPairDose = *handledPairDose;

          tempMeasureNormPoint.row = i;
          tempMeasureNormPoint.col = j;
          tempMeasureNormPoint.level = 0;

          tempHandledPairDose->normlize(tempMeasureNormPoint);

          tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();
          if(NULL == tempMeasureDose){
            RunningLog::writeLog("The measureDose is NULL;",__LINE__);
            return;
          }
          tempCalcDose = tempHandledPairDose->getNormCalculateDoseHandled();
          if(NULL == tempCalcDose){
            RunningLog::writeLog("The calcDose is NULL;",__LINE__);
            return;
          }

          tempMeasureDoseMatrix = tempMeasureDose->getDoseMatrix();
          tempCalcDoseMatrix = tempCalcDose->getDoseMatrix();

          isbreak = false;
          unPassCount = 0;
          considerCount = 0;

          for(int jSub= 0;jSub<cols;jSub++){
            for(int iSub= 0;iSub<rows;iSub++){
              if(tempMeasureDoseMatrix->at(iSub,jSub,0)>=this->standardParam.threshold){
                considerCount++;
              }
            }
          }

          for(int jSub= 0;jSub<cols;jSub++){
          
            if(true == isbreak){
              break;
            }

            for(int iSub= 0;iSub<rows;iSub++){

              if(true == isbreak){
                break;
              }

              if(tempMeasureDoseMatrix->at(iSub,jSub,0)>=this->standardParam.threshold){

                correspondRowInCalc = (iSub-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
                correspondColInCalc = (jSub-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

                if(correspondRowInCalc>=0 && correspondRowInCalc<tempCalcDoseMatrix->getRowLength() &&
                  correspondColInCalc>=0 && correspondColInCalc<tempCalcDoseMatrix->getColLength()){

                  tempValue = fabs(tempMeasureDoseMatrix->at(iSub,jSub,0) - tempCalcDoseMatrix->at(correspondRowInCalc,
                                                                                                   correspondColInCalc,
                                                                                                   0));

                  if(tempValue>this->standardParam.dosegap){
                    unPassCount++;
                  }


                  if(unPassCount>(1-bestFivePoints[0].first/100.0)*considerCount){
                    isbreak = true;
                  }

                }
              }

            }

          }

          tempDDPass = 100 - 100*((double)unPassCount)/considerCount;
          
          if(tempDDPass>bestFivePoints[0].first){
            tempPair.first = tempDDPass;
            tempPair.second.normPoint = tempMeasureNormPoint;
            tempPair.second.totalPassPercent = tempDDPass;
            tempPair.second.totalComparedCount = considerCount;
            tempPair.second.passedCount = considerCount - unPassCount;
            bestFivePoints[0] = tempPair;
          }

          quickSort<double,BestFive_Single>(bestFivePoints.begin(),0,bestFivePoints.size()-1);

        }

      }
    }
  }

  for(int p=0;p<5;p++){

    this->checkedRecord.getBestFiveResult()->bestFiveResult[p] = bestFivePoints[p].second;
  }


  globalMem = NULL;
  handledPairDose = NULL;
  measureDose = NULL;
  measureDoseMatrix = NULL;
  calcDose = NULL;

  TryToDelete<HandledPairDose>(tempHandledPairDose);
  tempHandledPairDose = NULL;
  tempMeasureDose = NULL;
  tempMeasureDoseMatrix = NULL;
  tempCalcDose = NULL;
  tempCalcDoseMatrix = NULL;
}
*/
//-------------------------------Abs_BsetFive_DTA-------------------------------------------
void DoseCheck::bestFive_Abs_DTACheck(){

  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  Dose* measureDose = NULL;
  MatrixData<double>* measureDoseMatrix = NULL;
  Dose* calcDose = NULL;

  /*Sub temp Values*/
  HandledPairDose* tempHandledPairDose = NULL;
  Dose* tempMeasureDose = NULL;
  MatrixData<double>* tempMeasureDoseMatrix = NULL;
  Dose* tempCalcDose = NULL;
  MatrixData<double>* tempCalcDoseMatrix = NULL;

  HANDLE_MODEL handle_model;
  /*----------*/

  int rows,cols;
  int iOffSet,jOffSet;

  double tempNormMeasureValue,tempNormCalcValue;
  double tempValueGap,tempDistancePower2;
  double distanceStandardPower2;
  double tempDTAPass;

  GridPoint tempMeasureNormPoint;

  int unPassCount = 0;

  int considerCount = 0;

  int measureFirstAlignmentRow,measureFirstAlignmentCol;
  int calcFirstAlignmentRow,calcFirstAlignmentCol;

  int rowSegments,colSegments;

  int correspondRowInCalc,correspondColInCalc;

  double calcRowGridSize,calcColGridSize;
  int searchRadioRow,searchRadioCol;

  bool innerIsbreak = false;
  bool outIsbreak = false;
  bool getADta;

  BestFive_Single tempBestFive_Single;

  vector<pair<double,BestFive_Single> > bestFivePoints;
  GridPoint tempNormPoint;
  pair<double,BestFive_Single> tempPair;
  tempNormPoint.reset();
  tempBestFive_Single.reset();
  for(int p=0;p<5;p++){
    tempPair.first = -1;
    tempPair.second = tempBestFive_Single;
    bestFivePoints.push_back(tempPair);
  } 

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }

  handle_model = globalMem->getHandel_Model();

  measureDose = handledPairDose->getNormMeasureDoseHandled();
  if(NULL == measureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }
  calcDose = handledPairDose->getAbs_NormCalculateDoseHandled();
  if(NULL == calcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }

  measureDoseMatrix = measureDose->getDoseMatrix();

  //sysc the standardParam
  this->standardParam = MainFormTempValue.checkStandardParam;

  rows = measureDoseMatrix->getRowLength();
  cols = measureDoseMatrix->getColLength();

  measureFirstAlignmentRow = measureDose->getFirstAlignmentCentral()->row;
  measureFirstAlignmentCol = measureDose->getFirstAlignmentCentral()->col;

  calcFirstAlignmentRow = calcDose->getFirstAlignmentCentral()->row;
  calcFirstAlignmentCol = calcDose->getFirstAlignmentCentral()->col;

  rowSegments = measureDose->getSegments()[0];
  colSegments = measureDose->getSegments()[1];

  calcRowGridSize = measureDose->getGridSizes()[0]/rowSegments;
  calcColGridSize = measureDose->getGridSizes()[1]/colSegments;
  searchRadioRow = TrimFloat_Up(this->standardParam.distance/calcRowGridSize,0.02);
  searchRadioCol = TrimFloat_Up(this->standardParam.distance/calcColGridSize,0.02);

  distanceStandardPower2 = this->standardParam.distance*this->standardParam.distance;

  vector< pair<double,GridPoint> > presortResult =  presort(searchRadioRow,searchRadioCol,calcRowGridSize,calcColGridSize);

  innerIsbreak = false;
  outIsbreak = false;
  getADta = false;
  
  for(int j= 0;j<cols;j++){
    for(int i=0;i<rows;i++){
      //consider the detector point only
      if(true == MainFormTempValue.detectorArray.at(i,j,0)){
        //consider the point dose should larger than threshod

        if(measureDoseMatrix->at(i,j,0)>=this->standardParam.bestFiveDoseThreadhold){
          TryToDelete<HandledPairDose>(tempHandledPairDose);
          tempHandledPairDose = new HandledPairDose();

          *tempHandledPairDose = *handledPairDose;

          tempMeasureNormPoint.row = i;
          tempMeasureNormPoint.col = j;
          tempMeasureNormPoint.level = 0;

          tempHandledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),tempMeasureNormPoint,handle_model);

          tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();
          if(NULL == tempMeasureDose){
            RunningLog::writeLog("The measureDose is NULL;",__LINE__);
            return;
          }
          tempCalcDose = tempHandledPairDose->getAbs_NormCalculateDoseHandled();
          if(NULL == tempCalcDose){
            RunningLog::writeLog("The calcDose is NULL;",__LINE__);
            return;
          }

          tempMeasureDoseMatrix = tempMeasureDose->getDoseMatrix();
          tempCalcDoseMatrix = tempCalcDose->getDoseMatrix();

          outIsbreak = false;
          unPassCount = 0;
          considerCount = 0;

          for(int jSub= 0;jSub<cols;jSub++){
            for(int iSub= 0;iSub<rows;iSub++){

              correspondRowInCalc = (iSub-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
              correspondColInCalc = (jSub-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

              if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<tempCalcDoseMatrix->getRowLength()
                   &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<tempCalcDoseMatrix->getColLength()){

                tempNormMeasureValue = tempMeasureDoseMatrix->at(iSub,jSub,0);
                tempNormCalcValue = tempCalcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
                
                if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){
                  considerCount++;
                }
              }


            }
          }

          for(int jSub= 0;jSub<cols;jSub++){
          
            if(true == outIsbreak){
              break;
            }

            for(int iSub= 0;iSub<rows;iSub++){

              if(true == outIsbreak){
                break;
              }


              correspondRowInCalc = (iSub-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
              correspondColInCalc = (jSub-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

              if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<tempCalcDoseMatrix->getRowLength()
                   &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<tempCalcDoseMatrix->getColLength()){

                tempNormMeasureValue = tempMeasureDoseMatrix->at(iSub,jSub,0);
                tempNormCalcValue = tempCalcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
                
                if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){

                  innerIsbreak = false;
                  getADta = false;

                  for(vector< pair<double,GridPoint> >::iterator iterat = presortResult.begin();iterat != presortResult.end();iterat++){

                    if(true==innerIsbreak){
                      break;
                    }

                    iOffSet = iterat->second.row;
                    jOffSet = iterat->second.col;

                    tempValueGap = fabs(tempMeasureDoseMatrix->at(iSub,jSub,0) - tempCalcDoseMatrix->at(iOffSet + correspondRowInCalc,
                                                                                                        jOffSet + correspondColInCalc,
                                                                                                        0));
                    tempDistancePower2 = iterat->first;
                    if(tempValueGap<=this->standardParam.doseUncertainty){
                      getADta = true;
                      innerIsbreak = true;
                    }

                    if(tempDistancePower2>distanceStandardPower2){
                        innerIsbreak = true;
                    }

                  }


                  if(false == getADta){
                    unPassCount++;
                  }

                  if(unPassCount>(1-bestFivePoints[0].first/100.0)*considerCount){
                    outIsbreak = true;
                  }


                }
              }

            }

          }


          tempDTAPass = 100 - 100*((double)unPassCount)/considerCount;
          
          if(tempDTAPass>bestFivePoints[0].first){
            tempPair.first = tempDTAPass;
            tempPair.second.normPoint = tempMeasureNormPoint;
            tempPair.second.totalPassPercent = tempDTAPass;
            tempPair.second.totalComparedCount = considerCount;
            tempPair.second.passedCount = considerCount - unPassCount;
            bestFivePoints[0] = tempPair;
          }

          quickSort<double,BestFive_Single>(bestFivePoints.begin(),0,bestFivePoints.size()-1);
        }

      }
    }
  }

  for(int p=0;p<5;p++){

    this->checkedRecord.getBestFiveResult()->bestFiveResult[p] = bestFivePoints[p].second;
  }

  globalMem = NULL;
  handledPairDose = NULL;
  measureDose = NULL;
  measureDoseMatrix = NULL;
  calcDose = NULL;

  TryToDelete<HandledPairDose>(tempHandledPairDose);
  tempHandledPairDose = NULL;
  tempMeasureDose = NULL;
  tempMeasureDoseMatrix = NULL;
  tempCalcDose = NULL;
  tempCalcDoseMatrix = NULL;
}
//-------------------------------Rel_BsetFive_DTA-------------------------------------------
void DoseCheck::bestFive_Rel_DTACheck(){

  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  Dose* measureDose = NULL;
  MatrixData<double>* measureDoseMatrix = NULL;
  Dose* calcDose = NULL;

  /*Sub temp Values*/
  HandledPairDose* tempHandledPairDose = NULL;
  Dose* tempMeasureDose = NULL;
  MatrixData<double>* tempMeasureDoseMatrix = NULL;
  Dose* tempCalcDose = NULL;
  MatrixData<double>* tempCalcDoseMatrix = NULL;

  HANDLE_MODEL handle_model;
  /*----------*/

  int rows,cols;
  int iOffSet,jOffSet;

  double tempNormMeasureValue,tempNormCalcValue;
                

  double tempValueGap,tempDistancePower2;
  double distanceStandardPower2;
  double tempDTAPass;

  GridPoint tempMeasureNormPoint;

  int unPassCount = 0;

  int considerCount = 0;

  int measureFirstAlignmentRow,measureFirstAlignmentCol;
  int calcFirstAlignmentRow,calcFirstAlignmentCol;

  int rowSegments,colSegments;

  int correspondRowInCalc,correspondColInCalc;

  double calcRowGridSize,calcColGridSize;
  int searchRadioRow,searchRadioCol;

  bool innerIsbreak = false;
  bool outIsbreak = false;
  bool getADta;

  BestFive_Single tempBestFive_Single;

  vector<pair<double,BestFive_Single> > bestFivePoints;
  GridPoint tempNormPoint;
  pair<double,BestFive_Single> tempPair;
  tempNormPoint.reset();
  tempBestFive_Single.reset();
  for(int p=0;p<5;p++){
    tempPair.first = -1;
    tempPair.second = tempBestFive_Single;
    bestFivePoints.push_back(tempPair);
  } 

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }

  handle_model = globalMem->getHandel_Model();

  measureDose = handledPairDose->getNormMeasureDoseHandled();
  if(NULL == measureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }
  calcDose = handledPairDose->getRel_NormCalculateDoseHandled();
  if(NULL == calcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }

  measureDoseMatrix = measureDose->getDoseMatrix();

  //sysc the standardParam
  this->standardParam = MainFormTempValue.checkStandardParam;

  rows = measureDoseMatrix->getRowLength();
  cols = measureDoseMatrix->getColLength();

  measureFirstAlignmentRow = measureDose->getFirstAlignmentCentral()->row;
  measureFirstAlignmentCol = measureDose->getFirstAlignmentCentral()->col;

  calcFirstAlignmentRow = calcDose->getFirstAlignmentCentral()->row;
  calcFirstAlignmentCol = calcDose->getFirstAlignmentCentral()->col;

  rowSegments = measureDose->getSegments()[0];
  colSegments = measureDose->getSegments()[1];

  calcRowGridSize = measureDose->getGridSizes()[0]/rowSegments;
  calcColGridSize = measureDose->getGridSizes()[1]/colSegments;
  searchRadioRow = TrimFloat_Up(this->standardParam.distance/calcRowGridSize,0.02);
  searchRadioCol = TrimFloat_Up(this->standardParam.distance/calcColGridSize,0.02);

  distanceStandardPower2 = this->standardParam.distance*this->standardParam.distance;

  vector< pair<double,GridPoint> > presortResult =  presort(searchRadioRow,searchRadioCol,calcRowGridSize,calcColGridSize);

  innerIsbreak = false;
  outIsbreak = false;
  getADta = false;
  
  for(int j= 0;j<cols;j++){
    for(int i=0;i<rows;i++){
      //consider the detector point only
      if(true == MainFormTempValue.detectorArray.at(i,j,0)){
        //consider the point dose should larger than threshod
        if(measureDoseMatrix->at(i,j,0)>=this->standardParam.bestFiveDoseThreadhold){
          TryToDelete<HandledPairDose>(tempHandledPairDose);
          tempHandledPairDose = new HandledPairDose();

          *tempHandledPairDose = *handledPairDose;

          tempMeasureNormPoint.row = i;
          tempMeasureNormPoint.col = j;
          tempMeasureNormPoint.level = 0;

          tempHandledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),tempMeasureNormPoint,handle_model);

          tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();
          if(NULL == tempMeasureDose){
            RunningLog::writeLog("The measureDose is NULL;",__LINE__);
            return;
          }
          tempCalcDose = tempHandledPairDose->getRel_NormCalculateDoseHandled();
          if(NULL == tempCalcDose){
            RunningLog::writeLog("The calcDose is NULL;",__LINE__);
            return;
          }

          tempMeasureDoseMatrix = tempMeasureDose->getDoseMatrix();
          tempCalcDoseMatrix = tempCalcDose->getDoseMatrix();

          outIsbreak = false;
          unPassCount = 0;
          considerCount = 0;


          for(int jSub= 0;jSub<cols;jSub++){
            for(int iSub= 0;iSub<rows;iSub++){

              correspondRowInCalc = (iSub-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
              correspondColInCalc = (jSub-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

              if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<tempCalcDoseMatrix->getRowLength()
                   &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<tempCalcDoseMatrix->getColLength()){

                tempNormMeasureValue = tempMeasureDoseMatrix->at(iSub,jSub,0);
                tempNormCalcValue = tempCalcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
                
                if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){
                  considerCount++;
                }
              }


            }
          }


          for(int jSub= 0;jSub<cols;jSub++){
          
            if(true == outIsbreak){
              break;
            }

            for(int iSub= 0;iSub<rows;iSub++){

              if(true == outIsbreak){
                break;
              }

              correspondRowInCalc = (iSub-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
              correspondColInCalc = (jSub-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

              if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<tempCalcDoseMatrix->getRowLength()
                   &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<tempCalcDoseMatrix->getColLength()){

                tempNormMeasureValue = tempMeasureDoseMatrix->at(iSub,jSub,0);
                tempNormCalcValue = tempCalcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
                
                if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){

                  innerIsbreak = false;
                  getADta = false;

                  for(vector< pair<double,GridPoint> >::iterator iterat = presortResult.begin();iterat != presortResult.end();iterat++){

                    if(true==innerIsbreak){
                      break;
                    }

                    iOffSet = iterat->second.row;
                    jOffSet = iterat->second.col;

                    tempValueGap = fabs(tempMeasureDoseMatrix->at(iSub,jSub,0) - tempCalcDoseMatrix->at(iOffSet + correspondRowInCalc,
                                                                                                        jOffSet + correspondColInCalc,
                                                                                                        0));
                    tempDistancePower2 = iterat->first;
                    if(tempValueGap<=this->standardParam.doseUncertainty){
                      getADta = true;
                      innerIsbreak = true;
                    }

                    if(tempDistancePower2>distanceStandardPower2){
                        innerIsbreak = true;
                    }

                  }


                  if(false == getADta){
                    unPassCount++;
                  }

                  if(unPassCount>(1-bestFivePoints[0].first/100.0)*considerCount){
                    outIsbreak = true;
                  }


                }
              }

            }

          }


          tempDTAPass = 100 - 100*((double)unPassCount)/considerCount;
          
          if(tempDTAPass>bestFivePoints[0].first){
            tempPair.first = tempDTAPass;
            tempPair.second.normPoint = tempMeasureNormPoint;
            tempPair.second.totalPassPercent = tempDTAPass;
            tempPair.second.totalComparedCount = considerCount;
            tempPair.second.passedCount = considerCount - unPassCount;
            bestFivePoints[0] = tempPair;
          }

          quickSort<double,BestFive_Single>(bestFivePoints.begin(),0,bestFivePoints.size()-1);
        }

      }
    }
  }

  for(int p=0;p<5;p++){

    this->checkedRecord.getBestFiveResult()->bestFiveResult[p] = bestFivePoints[p].second;
  }

  globalMem = NULL;
  handledPairDose = NULL;
  measureDose = NULL;
  measureDoseMatrix = NULL;
  calcDose = NULL;

  TryToDelete<HandledPairDose>(tempHandledPairDose);
  tempHandledPairDose = NULL;
  tempMeasureDose = NULL;
  tempMeasureDoseMatrix = NULL;
  tempCalcDose = NULL;
  tempCalcDoseMatrix = NULL;
}
//-------------------------------Abs_BsetFive_Gamma-------------------------------------------
void DoseCheck::bestFive_Abs_GammaCheck(){
  
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  Dose* measureDose = NULL;
  MatrixData<double>* measureDoseMatrix = NULL;
  Dose* calcDose = NULL;

  /*Sub temp Values*/
  HandledPairDose* tempHandledPairDose = NULL;
  Dose* tempMeasureDose = NULL;
  MatrixData<double>* tempMeasureDoseMatrix = NULL;
  Dose* tempCalcDose = NULL;
  MatrixData<double>* tempCalcDoseMatrix = NULL;

  HANDLE_MODEL handle_model;
  /*----------*/

  int rows,cols;
  int iOffSet,jOffSet;

  double tempNormMeasureValue,tempNormCalcValue;

  double tempValueGap,tempDistancePartPower2;
  double tempGammaPower2;
  double localMinGammaPower2 = DBL_MAX;
  double tempGamma;
  double tempGAMMAPass;

  double distanceStandardPower2,doseGapStandardPower2;

  GridPoint tempMeasureNormPoint;

  int unPassCount = 0;

  int considerCount = 0;

  int measureFirstAlignmentRow,measureFirstAlignmentCol;
  int calcFirstAlignmentRow,calcFirstAlignmentCol;

  int rowSegments,colSegments;

  int correspondRowInCalc,correspondColInCalc;

  double calcRowGridSize,calcColGridSize;
  int searchRadioRow,searchRadioCol;

  bool innerIsbreak = false;
  bool outIsbreak = false;

  BestFive_Single tempBestFive_Single;


  vector<pair<double,BestFive_Single> > bestFivePoints;
  GridPoint tempNormPoint;
  pair<double,BestFive_Single> tempPair;
  tempNormPoint.reset();
  tempBestFive_Single.reset();
  for(int p=0;p<5;p++){
    tempPair.first = -1;
    tempPair.second = tempBestFive_Single;
    bestFivePoints.push_back(tempPair);
  } 


  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }
  handle_model = globalMem->getHandel_Model();

  measureDose = handledPairDose->getNormMeasureDoseHandled();
  if(NULL == measureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }
  calcDose = handledPairDose->getAbs_NormCalculateDoseHandled();
  if(NULL == calcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }

  measureDoseMatrix = measureDose->getDoseMatrix();

  //sysc the standardParam
  this->standardParam = MainFormTempValue.checkStandardParam;

  rows = measureDoseMatrix->getRowLength();
  cols = measureDoseMatrix->getColLength();


  measureFirstAlignmentRow = measureDose->getFirstAlignmentCentral()->row;
  measureFirstAlignmentCol = measureDose->getFirstAlignmentCentral()->col;

  calcFirstAlignmentRow = calcDose->getFirstAlignmentCentral()->row;
  calcFirstAlignmentCol = calcDose->getFirstAlignmentCentral()->col;

  rowSegments = measureDose->getSegments()[0];
  colSegments = measureDose->getSegments()[1];

  calcRowGridSize = measureDose->getGridSizes()[0]/rowSegments;
  calcColGridSize = measureDose->getGridSizes()[1]/colSegments;
  searchRadioRow = TrimFloat_Up(this->standardParam.distance/calcRowGridSize,0.02);
  searchRadioCol = TrimFloat_Up(this->standardParam.distance/calcColGridSize,0.02);
  
  distanceStandardPower2 = this->standardParam.distance*this->standardParam.distance;
  doseGapStandardPower2 = this->standardParam.percentDifference*this->standardParam.percentDifference;

  vector< pair<double,GridPoint> > presortResult =  presort(searchRadioRow,searchRadioCol,calcRowGridSize,calcColGridSize);
  
  innerIsbreak = false;
  outIsbreak = false;

  for(int j= 0;j<cols;j++){
    for(int i=0;i<rows;i++){
      //consider the detector point only
      if(true == MainFormTempValue.detectorArray.at(i,j,0)){
        //consider the point dose should larger than threshod
        if(measureDoseMatrix->at(i,j,0)>=this->standardParam.bestFiveDoseThreadhold){

          TryToDelete<HandledPairDose>(tempHandledPairDose);
          tempHandledPairDose = new HandledPairDose();

          *tempHandledPairDose = *handledPairDose;

          tempMeasureNormPoint.row = i;
          tempMeasureNormPoint.col = j;
          tempMeasureNormPoint.level = 0;

          tempHandledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),tempMeasureNormPoint,handle_model);

          tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();
          if(NULL == tempMeasureDose){
            RunningLog::writeLog("The measureDose is NULL;",__LINE__);
            return;
          }
          tempCalcDose = tempHandledPairDose->getAbs_NormCalculateDoseHandled();
          if(NULL == tempCalcDose){
            RunningLog::writeLog("The calcDose is NULL;",__LINE__);
            return;
          }

          tempMeasureDoseMatrix = tempMeasureDose->getDoseMatrix();
          tempCalcDoseMatrix = tempCalcDose->getDoseMatrix();

          outIsbreak = false;
          unPassCount = 0;
          considerCount = 0;

          for(int jSub= 0;jSub<cols;jSub++){
            for(int iSub= 0;iSub<rows;iSub++){

              correspondRowInCalc = (iSub-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
              correspondColInCalc = (jSub-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

              if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<tempCalcDoseMatrix->getRowLength()
                   &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<tempCalcDoseMatrix->getColLength()){

                tempNormMeasureValue = tempMeasureDoseMatrix->at(iSub,jSub,0);
                tempNormCalcValue = tempCalcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
                
                if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){
                  considerCount++;
                }
              }


            }
          }

          for(int jSub= 0;jSub<cols;jSub++){

            if(true == outIsbreak){
              break;
            }

            for(int iSub= 0;iSub<rows;iSub++){

              if(true == outIsbreak){
                break;
              }

              correspondRowInCalc = (iSub-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
              correspondColInCalc = (jSub-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

              if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<tempCalcDoseMatrix->getRowLength()
                   &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<tempCalcDoseMatrix->getColLength()){

                tempNormMeasureValue = tempMeasureDoseMatrix->at(iSub,jSub,0);
                tempNormCalcValue = tempCalcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
                
                if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){

                  localMinGammaPower2 = DBL_MAX;
                  innerIsbreak = false;

                  for(vector< pair<double,GridPoint> >::iterator iterat = presortResult.begin();iterat != presortResult.end();iterat++){

                    if(true==innerIsbreak){
                      break;
                    }

                    iOffSet = iterat->second.row;
                    jOffSet = iterat->second.col;


                    tempValueGap = tempMeasureDoseMatrix->at(iSub,jSub,0) - tempCalcDoseMatrix->at(iOffSet + correspondRowInCalc,
                                                                                                  jOffSet + correspondColInCalc,
                                                                                                  0);


                    tempDistancePartPower2 = iterat->first/distanceStandardPower2;

                    tempGammaPower2 = tempValueGap*tempValueGap/doseGapStandardPower2 + tempDistancePartPower2;

                    if(tempGammaPower2<localMinGammaPower2){
                      localMinGammaPower2 = tempGammaPower2;
                    }

                    //pre-sort work
                    if(tempDistancePartPower2>=localMinGammaPower2){
                      innerIsbreak = true;
                    }

                  }

                  tempGamma = sqrt(localMinGammaPower2);

                  if(tempGamma>1){
                    unPassCount++;
                  }

                  if(unPassCount>(1-bestFivePoints[0].first/100.0)*considerCount){
                    outIsbreak = true;
                  }


                }
              }

            }

          }


          tempGAMMAPass = 100 - 100*((double)unPassCount)/considerCount;
          
          if(tempGAMMAPass>bestFivePoints[0].first){
            tempPair.first = tempGAMMAPass;
            tempPair.second.normPoint = tempMeasureNormPoint;
            tempPair.second.totalPassPercent = tempGAMMAPass;
            tempPair.second.totalComparedCount = considerCount;
            tempPair.second.passedCount = considerCount - unPassCount;
            bestFivePoints[0] = tempPair;
          }

          quickSort<double,BestFive_Single>(bestFivePoints.begin(),0,bestFivePoints.size()-1);

        }

      }
    }
  }

  for(int p=0;p<5;p++){

    this->checkedRecord.getBestFiveResult()->bestFiveResult[p] = bestFivePoints[p].second;
  }

  globalMem = NULL;
  handledPairDose = NULL;
  measureDose = NULL;
  measureDoseMatrix = NULL;
  calcDose = NULL;

  TryToDelete<HandledPairDose>(tempHandledPairDose);
  tempHandledPairDose = NULL;
  tempMeasureDose = NULL;
  tempMeasureDoseMatrix = NULL;
  tempCalcDose = NULL;
  tempCalcDoseMatrix = NULL;

}

//-------------------------------Rel_BsetFive_Gamma-------------------------------------------
void DoseCheck::bestFive_Rel_GammaCheck(){
  
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  Dose* measureDose = NULL;
  MatrixData<double>* measureDoseMatrix = NULL;
  Dose* calcDose = NULL;

  /*Sub temp Values*/
  HandledPairDose* tempHandledPairDose = NULL;
  Dose* tempMeasureDose = NULL;
  MatrixData<double>* tempMeasureDoseMatrix = NULL;
  Dose* tempCalcDose = NULL;
  MatrixData<double>* tempCalcDoseMatrix = NULL;

  HANDLE_MODEL handle_model;
  /*----------*/

  int rows,cols;
  int iOffSet,jOffSet;


  double tempNormMeasureValue,tempNormCalcValue;
  double tempValueGap,tempDistancePartPower2;
  double tempGammaPower2;
  double localMinGammaPower2 = DBL_MAX;
  double tempGamma;
  double tempGAMMAPass;

  double distanceStandardPower2,doseGapStandardPower2;

  GridPoint tempMeasureNormPoint;

  int unPassCount = 0;

  int considerCount = 0;

  int measureFirstAlignmentRow,measureFirstAlignmentCol;
  int calcFirstAlignmentRow,calcFirstAlignmentCol;

  int rowSegments,colSegments;

  int correspondRowInCalc,correspondColInCalc;

  double calcRowGridSize,calcColGridSize;
  int searchRadioRow,searchRadioCol;

  bool innerIsbreak = false;
  bool outIsbreak = false;

  BestFive_Single tempBestFive_Single;


  vector<pair<double,BestFive_Single> > bestFivePoints;
  GridPoint tempNormPoint;
  pair<double,BestFive_Single> tempPair;
  tempNormPoint.reset();
  tempBestFive_Single.reset();
  for(int p=0;p<5;p++){
    tempPair.first = -1;
    tempPair.second = tempBestFive_Single;
    bestFivePoints.push_back(tempPair);
  } 


  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;",__LINE__);
    return;
  }
  handle_model = globalMem->getHandel_Model();
  
  measureDose = handledPairDose->getNormMeasureDoseHandled();
  if(NULL == measureDose){
    RunningLog::writeLog("The measureDose is NULL;",__LINE__);
    return;
  }
  calcDose = handledPairDose->getRel_NormCalculateDoseHandled();
  if(NULL == calcDose){
    RunningLog::writeLog("The calcDose is NULL;",__LINE__);
    return;
  }

  measureDoseMatrix = measureDose->getDoseMatrix();

  //sysc the standardParam
  this->standardParam = MainFormTempValue.checkStandardParam;

  rows = measureDoseMatrix->getRowLength();
  cols = measureDoseMatrix->getColLength();


  measureFirstAlignmentRow = measureDose->getFirstAlignmentCentral()->row;
  measureFirstAlignmentCol = measureDose->getFirstAlignmentCentral()->col;

  calcFirstAlignmentRow = calcDose->getFirstAlignmentCentral()->row;
  calcFirstAlignmentCol = calcDose->getFirstAlignmentCentral()->col;

  rowSegments = measureDose->getSegments()[0];
  colSegments = measureDose->getSegments()[1];

  calcRowGridSize = measureDose->getGridSizes()[0]/rowSegments;
  calcColGridSize = measureDose->getGridSizes()[1]/colSegments;
  searchRadioRow = TrimFloat_Up(this->standardParam.distance/calcRowGridSize,0.02);
  searchRadioCol = TrimFloat_Up(this->standardParam.distance/calcColGridSize,0.02);
  
  distanceStandardPower2 = this->standardParam.distance*this->standardParam.distance;
  doseGapStandardPower2 = this->standardParam.percentDifference*this->standardParam.percentDifference;

  vector< pair<double,GridPoint> > presortResult =  presort(searchRadioRow,searchRadioCol,calcRowGridSize,calcColGridSize);
  
  innerIsbreak = false;
  outIsbreak = false;

  for(int j= 0;j<cols;j++){
    for(int i=0;i<rows;i++){
      //consider the detector point only
      if(true == MainFormTempValue.detectorArray.at(i,j,0)){
        //consider the point dose should larger than threshod
        if(measureDoseMatrix->at(i,j,0)>=this->standardParam.bestFiveDoseThreadhold){

          TryToDelete<HandledPairDose>(tempHandledPairDose);
          tempHandledPairDose = new HandledPairDose();

          *tempHandledPairDose = *handledPairDose;

          tempMeasureNormPoint.row = i;
          tempMeasureNormPoint.col = j;
          tempMeasureNormPoint.level = 0;

          tempHandledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),tempMeasureNormPoint,handle_model);

          tempMeasureDose = tempHandledPairDose->getNormMeasureDoseHandled();
          if(NULL == tempMeasureDose){
            RunningLog::writeLog("The measureDose is NULL;",__LINE__);
            return;
          }
          tempCalcDose = tempHandledPairDose->getRel_NormCalculateDoseHandled();
          if(NULL == tempCalcDose){
            RunningLog::writeLog("The calcDose is NULL;",__LINE__);
            return;
          }

          tempMeasureDoseMatrix = tempMeasureDose->getDoseMatrix();
          tempCalcDoseMatrix = tempCalcDose->getDoseMatrix();

          outIsbreak = false;
          unPassCount = 0;
          considerCount = 0;

          for(int jSub= 0;jSub<cols;jSub++){
            for(int iSub= 0;iSub<rows;iSub++){

              correspondRowInCalc = (iSub-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
              correspondColInCalc = (jSub-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

              if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<tempCalcDoseMatrix->getRowLength()
                   &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<tempCalcDoseMatrix->getColLength()){

                tempNormMeasureValue = tempMeasureDoseMatrix->at(iSub,jSub,0);
                tempNormCalcValue = tempCalcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
                
                if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){
                  considerCount++;
                }
              }


            }
          }

          for(int jSub= 0;jSub<cols;jSub++){

            if(true == outIsbreak){
              break;
            }

            for(int iSub= 0;iSub<rows;iSub++){

              if(true == outIsbreak){
                break;
              }

              correspondRowInCalc = (iSub-measureFirstAlignmentRow)*rowSegments+calcFirstAlignmentRow;
              correspondColInCalc = (jSub-measureFirstAlignmentCol)*colSegments+calcFirstAlignmentCol;

              if( (correspondRowInCalc-searchRadioRow)>=0 && (correspondRowInCalc+searchRadioRow)<tempCalcDoseMatrix->getRowLength()
                   &&(correspondColInCalc-searchRadioCol)>=0 && (correspondColInCalc+searchRadioCol)<tempCalcDoseMatrix->getColLength()){

                tempNormMeasureValue = tempMeasureDoseMatrix->at(iSub,jSub,0);
                tempNormCalcValue = tempCalcDoseMatrix->at(correspondRowInCalc,correspondColInCalc,0);
                
                if(passedThreshold(tempNormMeasureValue,tempNormCalcValue,this->standardParam.threshold,handle_model)){

                  localMinGammaPower2 = DBL_MAX;
                  innerIsbreak = false;

                  for(vector< pair<double,GridPoint> >::iterator iterat = presortResult.begin();iterat != presortResult.end();iterat++){

                    if(true==innerIsbreak){
                      break;
                    }

                    iOffSet = iterat->second.row;
                    jOffSet = iterat->second.col;


                    tempValueGap = tempMeasureDoseMatrix->at(iSub,jSub,0) - tempCalcDoseMatrix->at(iOffSet + correspondRowInCalc,
                                                                                                  jOffSet + correspondColInCalc,
                                                                                                  0);


                    tempDistancePartPower2 = iterat->first/distanceStandardPower2;

                    tempGammaPower2 = tempValueGap*tempValueGap/doseGapStandardPower2 + tempDistancePartPower2;

                    if(tempGammaPower2<localMinGammaPower2){
                      localMinGammaPower2 = tempGammaPower2;
                    }

                    //pre-sort work
                    if(tempDistancePartPower2>=localMinGammaPower2){
                      innerIsbreak = true;
                    }

                  }

                  tempGamma = sqrt(localMinGammaPower2);

                  if(tempGamma>1){
                    unPassCount++;
                  }

                  if(unPassCount>(1-bestFivePoints[0].first/100.0)*considerCount){
                    outIsbreak = true;
                  }


                }
              }

            }

          }


          tempGAMMAPass = 100 - 100*((double)unPassCount)/considerCount;
          
          if(tempGAMMAPass>bestFivePoints[0].first){
            tempPair.first = tempGAMMAPass;
            tempPair.second.normPoint = tempMeasureNormPoint;
            tempPair.second.totalPassPercent = tempGAMMAPass;
            tempPair.second.totalComparedCount = considerCount;
            tempPair.second.passedCount = considerCount - unPassCount;
            bestFivePoints[0] = tempPair;
          }

          quickSort<double,BestFive_Single>(bestFivePoints.begin(),0,bestFivePoints.size()-1);

        }

      }
    }
  }

  for(int p=0;p<5;p++){

    this->checkedRecord.getBestFiveResult()->bestFiveResult[p] = bestFivePoints[p].second;
  }

  globalMem = NULL;
  handledPairDose = NULL;
  measureDose = NULL;
  measureDoseMatrix = NULL;
  calcDose = NULL;

  TryToDelete<HandledPairDose>(tempHandledPairDose);
  tempHandledPairDose = NULL;
  tempMeasureDose = NULL;
  tempMeasureDoseMatrix = NULL;
  tempCalcDose = NULL;
  tempCalcDoseMatrix = NULL;

}



//----------------------------------Pre sort-----------------------------------------------
vector< pair<double,GridPoint> > DoseCheck::presort(int rowRadius,int colRadius,double rowGridSize,double colGridSize){

  vector< pair<double,GridPoint> > result;
  pair<double,GridPoint> tempPair;
  double tempDistancePower2;
  GridPoint tempGridPoint;

  for(int j=-colRadius;j<=colRadius;j++){

    for(int i=-rowRadius;i<=rowRadius;i++){
      tempDistancePower2 = i*rowGridSize*i*rowGridSize + j*colGridSize*j*colGridSize;
      tempGridPoint.row = i;
      tempGridPoint.col = j;
      tempGridPoint.level = 0;

      tempPair.first = tempDistancePower2;
      tempPair.second = tempGridPoint;

      result.push_back(tempPair);
    }
  }

  //sort
  quickSort<double,GridPoint>(result.begin(),0,result.size()-1);


  return result;

}

void DoseCheck::reset(){
  this->checkedRecord.reset();
  this->standardParam.reset();
}

CheckedRecord* DoseCheck::getCheckedRecord(){
  return &this->checkedRecord;
}

CheckedRecord  DoseCheck::copyCheckedRecord(){
  return this->checkedRecord;
}


StandardParam* DoseCheck::getStandardParam(){
  return &this->standardParam;
}

StandardParam DoseCheck::copyStandardParam(){
  return this->standardParam;
}

void DoseCheck::setStandardParam(StandardParam& _standardParam){
  this->standardParam = _standardParam;
}

bool DoseCheck::getInnerPoint(int outX,int outY,int& innerX,int& innerY,int halfWidth){
  int absOutX = abs(outX);
  int absOutY = abs(outY);

  if( 0==outX && 0==outY){
    return false;
  }

  if(absOutX>absOutY){
    innerX = outX>0?(outX-1):(outX+1);
    innerY = outY;
  }else if(absOutX<absOutY){
    innerX = outX;
    innerY = outY>0?(outY-1):(outY+1);
  }else if(absOutX == absOutY){
    innerX = outX>0?(outX-1):(outX+1);
    innerY = outY>0?(outY-1):(outY+1);
  }

  if(abs(innerX)>halfWidth || abs(innerY)>halfWidth){
    return false;
  }
  
  return true;
  
}


void  DoseCheck::CalcIndices(int& rowSubIndex,int& colSubIndex){
  int tempValue;

  tempValue = colSubIndex;
  if (colSubIndex> 1 || rowSubIndex>1 )
  {
    if (rowSubIndex >= tempValue )
    {
      if (rowSubIndex <= tempValue)
      {
        colSubIndex = tempValue - 1;
        --rowSubIndex;
      }
      else
      {
        --rowSubIndex;
      }
    }
    else
    {
      colSubIndex = tempValue - 1;
    }
  }
  else
  {
    colSubIndex = 0;
    rowSubIndex = 0;
  }
}



//---------------------------------------------------------------------------
TDICheck::TDICheck(TDose *md,TDose *di,StandardParam theStandard)   //theChoose.NormType:0(default)  默认情况下，DICOM对齐之后，选择剂量最大值点作为归一化点（这与中期验收时选择DICOM中对齐后中心点剂量作为最大值的做法有所不同，主要由于测量平面中选取最大值作为归一化点(最大值为100%)，所以选择DICOM中对齐后中心点剂量作为最大值不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)）
{
  /*                                                                             //         1           按照用户所选的归一化点
  pmead = md;                                                                   //         2            BestFive
  pdi = di;
  M_RM = theStandard.distance;  //M_RM即用户设定的GAMA标准中的半径值
  M_DM = theStandard.dosegap; //M_DM即用户设定的GAMA标准中的百分误差
  M_TH = theStandard.th;  //用户设定的百分相对计量的百分阈值


//  if(m_DOSE)
//    deleteStack(m_DOSE);
  m_DOSE = new float[pmead->nData];

//  if(M_GAMA) delete[] M_GAMA;
  M_GAMA = new float[pmead->nData];  //gama因子

//  if(Dta) delete[] Dta;
  Dta = new float[pmead->nData];

//  if(DD) delete[] DD;
  DD = new float[pmead->nData];

//  if(M_DC) delete[] M_DC;
  M_DC = new float[pdi->nData];

  totaldet = 0;
  switch(theChoose.NormType)
  {
    case 0:        //（默认）默认情况下，DICOM对齐之后，选择剂量最大值点作为归一化点（这与中期验收时选择DICOM中对齐后中心点剂量作为最大值的做法有所不同，主要由于测量平面中选取最大值作为归一化点(最大值为100%)，所以选择DICOM中对齐后中心点剂量作为最大值不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)）
    {
        startDIJob(theChoose);
    }
    break;
    case 1:      //用户所选的点为归一化点
    {
      startDIJob(theChoose);
    }
    break;
    case 2:      //bestFive
    {
      if(best_five_checkResult) delete[]best_five_checkResult;
      best_five_checkResult = startDIJob_best5(theChoose);
    }
    break;
    default:
    break;
  }
  */
}

TDICheck::~TDICheck()
{
  if(m_DOSE)
  {
    delete[] m_DOSE;
  }
  if(M_DC) delete[] M_DC;
  if(M_GAMA) delete[] M_GAMA;
  if(Dta) delete[] Dta;
  if(DD) delete[] DD;
  /* 
  if(best_five_checkResult) delete[]best_five_checkResult;
  */
}

//void TDICheck::startDIJob()
//{
//  int i,j,ito,jto;
//  int dileft,diright,ditop,dibottom,xaorigin,yaorigin,xborigin,yborigin,xfirst,yfirst;
//  int M_gama,M_Dta,M_DD;
//  int thenum;   //测量数据总数
//  int ncalc;     //计算数据总数
//  float *ptm,*ptc;
//  dileft = pdi->cutverit[0];
//  diright = pdi->cutverit[1];
//  ditop = pdi->cuthoriz[0];
//  dibottom = pdi->cuthoriz[1];
//  xborigin = pdi->icenter;
//  yborigin = pdi->jcenter;
//  xfirst = pdi->ifirst;
//  yfirst = pdi->jfirst;
//  nnx = pmead->nx;
//  nny = pmead->ny;
//  thenum = pmead->nData;
//  ncalc = pdi->nData;
//  Nx = pdi->irange;
//  Ny = pdi->jrange;
//
//  ptm = pmead->NormDose;
//  ptc = pdi->NormDose;
//
//  if(nnx%2==1)     //找到中间点，以便将坐标向中间移动
//  {
//    xaorigin = (nnx-1)*0.5;   //22//对于探测器点数长和宽都为奇数的情况下（比如Mapcheck的45*45）（即axdir和aydir为偶数的情况(axdir=长-1，aydir=宽-1)），让每一个探测器
//                                   //都处于整数位置，就是说，对于中测45×45的情况，让探测器坐标为-22到22中的每一个整数位置，坐标原点刚好位于(0,0)的位置
//  }
//  else
//  {
//    xaorigin = nnx*0.5 - 1;  //19//对于探测器点数长和宽都为偶数的情况下(中测40×40的情况)（即axdir和aydir为奇数的情况(axdir=长-1，aydir=宽-1)），让每一个探测器
//                                   //都处于整数位置，就是说，对于中测40×40的情况，让探测器坐标为-20到19中的每一个整数位置，而让坐标原点位于(-0.5,-0.5)的位置，这样方便
//                                   //作图和数据处理，因为让探测器位于整数位置刚好对应于数组的位置；其实这只是图像上的处理，只是相对位置，其实这样设置也可以看做
//                                   //坐标原点位于(0 ,0)，各个探测器位于从-19.5到19.5中每个半整数位置；这只是图像显示上的便捷处理，不影响数据计算和处理
//  }
//
//  if(nny%2==0)     //找到中间点，以便将坐标向中间移动
//  {
//    yaorigin = (nny-1)*0.5;     //22//对于探测器点数长和宽都为奇数的情况下（比如Mapcheck的45*45）（即axdir和aydir为偶数的情况(axdir=长-1，aydir=宽-1)），让每一个探测器
//                                   //都处于整数位置，就是说，对于中测45×45的情况，让探测器坐标为-22到22中的每一个整数位置，坐标原点刚好位于(0,0)的位置
//  }
//  else
//  {
//    yaorigin = nny*0.5-1;  //19//对于探测器点数长和宽都为偶数的情况下(中测40×40的情况)（即axdir和aydir为奇数的情况(axdir=长-1，aydir=宽-1)），让每一个探测器
//                                   //都处于整数位置，就是说，对于中测40×40的情况，让探测器坐标为-20到19中的每一个整数位置，而让坐标原点位于(-0.5,-0.5)的位置，这样方便
//                                   //作图和数据处理，因为让探测器位于整数位置刚好对应于数组的位置；其实这只是图像上的处理，只是相对位置，其实这样设置也可以看做
//                                   //坐标原点位于(0 ,0)，各个探测器位于从-19.5到19.5中每个半整数位置；这只是图像显示上的便捷处理，不影响数据计算和处理
//  }
//
//
//
//
//  for(i=0;i<thenum;i++)      //做一次转换，防止(解决)析构时出现内存的多重释放问题
//  {
//    m_DOSE[i] = ptm[i];
//  }
//
//  for(i=0;i<ncalc;i++)
//  {
//    M_DC[i] = ptc[i];
//  }
//
//  for(j=0;j<nnx;j++)
//  {
//    for(i=0;i<nnx;i++)
//      isdetpass[j][i] = 0;
//  }
//
//  for(i=0;i<thenum;i++)
//  {
//    M_GAMA[i] = -100.0;
//    Dta[i] = -100.0;
//    DD[i] = -100.0;
//  }
//
//
//  for(j=0;j<nnx;j++)      //得知哪些探测器对应的点将会用于剂量验证
//  {
//    for(i=0;i<nnx;i++)
//    {
//      if((((i-xaorigin)*segments+xborigin)>=dileft)&&(((i-xaorigin)*segments+xborigin)<=diright)&&(((j-yaorigin)*segments+yborigin)>=ditop)&&(((j-yaorigin)*segments+yborigin)<=dibottom))
//      {
//        if((detector[j][i]==1)&&(M_DC[((j-yaorigin)*segments+yborigin)*Nx+(i-xaorigin)*segments+xborigin]>=M_TH))
//        {
//          isdetpass[j][i] = 1;    //表示该点探测器满足条件，将会被用来进行剂量验证
//          totaldet++;
//        }
//      }
//    }
//  }
//
//  int cc=0;
//  float TGama,TDta;
//  float tempgama,tempdta;
//  int mipos,mjpos;
//  float temp1,temp2;
//  for(j=0;j<nnx;j++)
//  {
//    for(i=0;i<nnx;i++)
//    {
//      mipos = (i-xaorigin)*segments+xfirst;
//      mjpos = (j-yaorigin)*segments+yfirst;
//      TGama = 1.0E+10;
//      TDta = 1.0E+10;
//      if(isdetpass[j][i]==1)
//      {
//        DD[cc] = fabs(m_DOSE[j*nnx+i] - M_DC[mjpos*Nx+mipos]);//DD值
//
//        if(m_DOSE[j*nnx+i] == M_DC[mjpos*Nx+mipos])
//        {
//          M_GAMA[cc] = 0.0;
//          Dta[cc] = 0.0;
//        }
//
//        else
//        {
//          for(jto=-10;jto<=10;jto++)              //搜索半径定为1cm
//          {
//            for(ito=-10;ito<=10;ito++)
//            {
//               temp1 = ito*ito + jto*jto;  //distance
//               temp2 =  m_DOSE[j*nnx+i] - M_DC[(mjpos+jto)*Nx+mipos+ito]; //dose gap
//
//               tempgama = sqrt(temp1/(M_RM*M_RM) + temp2*temp2/(M_DM*M_DM));   //这里(1)没用平方
//               tempdta = sqrt(temp1);                                                                      //(2)diff%没除100，这两点和startJob中不同
//
//               if(tempgama<=TGama)       //寻找最小gama值
//                 TGama = tempgama;
//
//               if(fabs(temp2)<M_DM&&tempdta<=TDta)    //寻找最小dta值
//                 TDta = tempdta;
//
//            }
//          }
//
//          M_GAMA[cc] = TGama;
//          Dta[cc]  = TDta;
//        }
//      }
//      cc++;
//    }
//  }
//
//
//}

//---------------------------------------------------------------------------
/*
void TDICheck::startDIJob(CheckChoose theChoose)
{
  //theChoose.checkType 为进行计算的选项
  //0,default 为Gamma
  //1 为DD
  //2 为DTA
  int i,j,ito,jto;
  int dileft,diright,ditop,dibottom,xaorigin,yaorigin,xborigin,yborigin,xfirst,yfirst;
  int M_gama,M_Dta,M_DD;
  float *ptm,*ptc;
  int thenum;   //测量数据总数
  int ncalc;     //计算数据总数
  dileft = pdi->cutverit[0];
  diright = pdi->cutverit[1];
  ditop = pdi->cuthoriz[0];
  dibottom = pdi->cuthoriz[1];
  xborigin = pdi->icenter;
  yborigin = pdi->jcenter;
  xfirst = pdi->ifirst;
  yfirst = pdi->jfirst;
  nnx = pmead->nx;
  nny = pmead->ny;
  thenum = pmead->nData;
  ncalc = pdi->nData;
  Nx = pdi->irange;
  Ny = pdi->jrange;
  float m_NormPoint_Dose;  //测量的归一化剂量
  float c_NormPoint_Dose;  //计算的归一化剂量

  if(nnx%2==1)     //找到中间点，以便将坐标向中间移动
  {
    xaorigin = (nnx-1)*0.5;   //22//对于探测器点数长和宽都为奇数的情况下（比如Mapcheck的45*45）（即axdir和aydir为偶数的情况(axdir=长-1，aydir=宽-1)），让每一个探测器
                                   //都处于整数位置，就是说，对于中测45×45的情况，让探测器坐标为-22到22中的每一个整数位置，坐标原点刚好位于(0,0)的位置
  }
  else
  {
    xaorigin = nnx*0.5 - 1;  //19//对于探测器点数长和宽都为偶数的情况下(中测40×40的情况)（即axdir和aydir为奇数的情况(axdir=长-1，aydir=宽-1)），让每一个探测器
                                   //都处于整数位置，就是说，对于中测40×40的情况，让探测器坐标为-20到19中的每一个整数位置，而让坐标原点位于(-0.5,-0.5)的位置，这样方便
                                   //作图和数据处理，因为让探测器位于整数位置刚好对应于数组的位置；其实这只是图像上的处理，只是相对位置，其实这样设置也可以看做
                                   //坐标原点位于(0 ,0)，各个探测器位于从-19.5到19.5中每个半整数位置；这只是图像显示上的便捷处理，不影响数据计算和处理
  }

  if(nny%2==1)     //找到中间点，以便将坐标向中间移动
  {
    yaorigin = (nny-1)*0.5;     //22//对于探测器点数长和宽都为奇数的情况下（比如Mapcheck的45*45）（即axdir和aydir为偶数的情况(axdir=长-1，aydir=宽-1)），让每一个探测器
                                   //都处于整数位置，就是说，对于中测45×45的情况，让探测器坐标为-22到22中的每一个整数位置，坐标原点刚好位于(0,0)的位置
  }
  else
  {
    yaorigin = nny*0.5-1;  //19//对于探测器点数长和宽都为偶数的情况下(中测40×40的情况)（即axdir和aydir为奇数的情况(axdir=长-1，aydir=宽-1)），让每一个探测器
                                   //都处于整数位置，就是说，对于中测40×40的情况，让探测器坐标为-20到19中的每一个整数位置，而让坐标原点位于(-0.5,-0.5)的位置，这样方便
                                   //作图和数据处理，因为让探测器位于整数位置刚好对应于数组的位置；其实这只是图像上的处理，只是相对位置，其实这样设置也可以看做
                                   //坐标原点位于(0 ,0)，各个探测器位于从-19.5到19.5中每个半整数位置；这只是图像显示上的便捷处理，不影响数据计算和处理
  }

  switch(theChoose.NormType)
  {
    case 0:          //(默认)默认情况下，DICOM对齐之后，选择剂量最大值点作为归一化点（这与中期验收时选择DICOM中对齐后中心点剂量作为最大值的做法有所不同，主要由于测量平面中选取最大值作为归一化点(最大值为100%)，所以选择DICOM中对齐后中心点剂量作为最大值不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)）
    {
      ptm = pmead->NormDose;
      ptc = pdi->NormDose;
      for(i=0;i<thenum;i++)      //做一次转换，防止(解决)析构时出现内存的多重释放问题
      {
        m_DOSE[i] = ptm[i];
      }

      for(i=0;i<ncalc;i++)
      {
        M_DC[i] = ptc[i];
      }
    }
    break;
    case 1:   //以用户所选的点为归一化点
    {
      ptm = pmead->DoseAbs;
      ptc = pdi->DoseAbs;
      m_NormPoint_Dose = ptm[theChoose.Point[0]*nnx + theChoose.Point[1]*nny];
      c_NormPoint_Dose = ptc[theChoose.Point[0]*segments*Nx + theChoose.Point[1]*segments*Ny];
      for(i=0;i<thenum;i++)      //做一次转换，防止(解决)析构时出现内存的多重释放问题
      {
        m_DOSE[i] = 100*ptm[i]/(m_NormPoint_Dose+0.0000001);
      }

      for(i=0;i<ncalc;i++)
      {
        M_DC[i] = 100*ptc[i]/(c_NormPoint_Dose+0.0000001);
      }
    }
    break;
    default:
    break;
  }


  for(j=0;j<nnx;j++)
  {
    for(i=0;i<nnx;i++)
      isdetpass[j][i] = 0;
  }

  for(i=0;i<thenum;i++)
  {
    M_GAMA[i] = -100.0;
    Dta[i] = -100.0;
    DD[i] = -100.0;
  }


  for(j=0;j<nnx;j++)      //得知哪些探测器对应的点将会用于剂量验证
  {
    for(i=0;i<nnx;i++)
    {
      if((((i-xaorigin)*segments+xborigin)>=dileft)&&(((i-xaorigin)*segments+xborigin)<=diright)&&(((j-yaorigin)*segments+yborigin)>=ditop)&&(((j-yaorigin)*segments+yborigin)<=dibottom))
      {
        if((detector[j][i]==1)&&(M_DC[((j-yaorigin)*segments+yborigin)*Nx+(i-xaorigin)*segments+xborigin]>=M_TH))
        {
          isdetpass[j][i] = 1;    //表示该点探测器满足条件，将会被用来进行剂量验证
          totaldet++;
        }
      }
    }
  }

  int cc=0;
  float TGama,TDta;
  float tempgama,tempdta;
  int mipos,mjpos;
  float temp1,temp2;
  for(j=0;j<nny;j++)
  {
    for(i=0;i<nnx;i++)
    {
      mipos = (i-xaorigin)*segments+xfirst;
      mjpos = (j-yaorigin)*segments+yfirst;
      TGama = 1.0E+10;
      TDta = 1.0E+10;
      if(isdetpass[j][i]==1)
      {
        DD[cc] = fabs(m_DOSE[j*nnx+i] - M_DC[mjpos*Nx+mipos]);//DD值

        if(m_DOSE[j*nnx+i] == M_DC[mjpos*Nx+mipos])
        {
          M_GAMA[cc] = 0.0;
          Dta[cc] = 0.0;
        }
        else
        {
          for(jto=-10;jto<=10;jto++)              //搜索半径定为1cm
          {
            for(ito=-10;ito<=10;ito++)
            {
               temp1 = ito*ito + jto*jto;  //distance
               temp2 =  m_DOSE[j*nnx+i] - M_DC[(mjpos+jto)*Nx+mipos+ito]; //dose gap

               tempgama = sqrt(temp1/(M_RM*M_RM) + temp2*temp2/(M_DM*M_DM));   //这里(1)没用平方
               tempdta = sqrt(temp1);                                         //(2)diff%没除100，这两点和startJob中不同

               if(tempgama<=TGama)       //寻找最小gama值
                 TGama = tempgama;

               if(fabs(temp2)<M_DM&&tempdta<=TDta)    //寻找最小dta值
                 TDta = tempdta;

            }
          }

          M_GAMA[cc] = TGama;
          Dta[cc]  = TDta;
        }
      }
      cc++;
    }
  }


}
*/

//---------------------------------------------------------------------------

/*
CheckResult* TDICheck::startDIJob_best5(CheckChoose theChoose)
{
   //计算出最佳Gamma通过率的5个点
   //checkType 为进行计算的选项
   //0,default 为Gamma
   //1 为DD
   //2 为DTA
  int i,j,ito,jto;
  int dileft,diright,ditop,dibottom,xaorigin,yaorigin,xborigin,yborigin,xfirst,yfirst;
  int M_gama,M_Dta,M_DD;
  int thenum;   //测量数据总数
  int ncalc;     //计算数据总数
  float *ptm,*ptc;
  dileft = pdi->cutverit[0];
  diright = pdi->cutverit[1];
  ditop = pdi->cuthoriz[0];
  dibottom = pdi->cuthoriz[1];
  xborigin = pdi->icenter;
  yborigin = pdi->jcenter;
  xfirst = pdi->ifirst;
  yfirst = pdi->jfirst;
  nnx = pmead->nx;
  nny = pmead->ny;
  thenum = pmead->nData;
  ncalc = pdi->nData;
  Nx = pdi->irange;
  Ny = pdi->jrange;
  float m_NormPoint_Dose;  //测量的归一化剂量
  float c_NormPoint_Dose;  //计算的归一化剂量

  if(nnx%2==1)     //找到中间点，以便将坐标向中间移动
  {
    xaorigin = (nnx-1)*0.5;   //22//对于探测器点数长和宽都为奇数的情况下（比如Mapcheck的45*45）（即axdir和aydir为偶数的情况(axdir=长-1，aydir=宽-1)），让每一个探测器
                                   //都处于整数位置，就是说，对于中测45×45的情况，让探测器坐标为-22到22中的每一个整数位置，坐标原点刚好位于(0,0)的位置
  }
  else
  {
    xaorigin = nnx*0.5 - 1;  //19//对于探测器点数长和宽都为偶数的情况下(中测40×40的情况)（即axdir和aydir为奇数的情况(axdir=长-1，aydir=宽-1)），让每一个探测器
                                   //都处于整数位置，就是说，对于中测40×40的情况，让探测器坐标为-20到19中的每一个整数位置，而让坐标原点位于(-0.5,-0.5)的位置，这样方便
                                   //作图和数据处理，因为让探测器位于整数位置刚好对应于数组的位置；其实这只是图像上的处理，只是相对位置，其实这样设置也可以看做
                                   //坐标原点位于(0 ,0)，各个探测器位于从-19.5到19.5中每个半整数位置；这只是图像显示上的便捷处理，不影响数据计算和处理
  }

  if(nny%2==0)     //找到中间点，以便将坐标向中间移动
  {
    yaorigin = (nny-1)*0.5;     //22//对于探测器点数长和宽都为奇数的情况下（比如Mapcheck的45*45）（即axdir和aydir为偶数的情况(axdir=长-1，aydir=宽-1)），让每一个探测器
                                   //都处于整数位置，就是说，对于中测45×45的情况，让探测器坐标为-22到22中的每一个整数位置，坐标原点刚好位于(0,0)的位置
  }
  else
  {
    yaorigin = nny*0.5-1;  //19//对于探测器点数长和宽都为偶数的情况下(中测40×40的情况)（即axdir和aydir为奇数的情况(axdir=长-1，aydir=宽-1)），让每一个探测器
                                   //都处于整数位置，就是说，对于中测40×40的情况，让探测器坐标为-20到19中的每一个整数位置，而让坐标原点位于(-0.5,-0.5)的位置，这样方便
                                   //作图和数据处理，因为让探测器位于整数位置刚好对应于数组的位置；其实这只是图像上的处理，只是相对位置，其实这样设置也可以看做
                                   //坐标原点位于(0 ,0)，各个探测器位于从-19.5到19.5中每个半整数位置；这只是图像显示上的便捷处理，不影响数据计算和处理
  }

  ptm = pmead->DoseAbs;
  ptc = pdi->DoseAbs;

  for(j=0;j<nny;j++)
  {
    for(i=0;i<nnx;i++)
      isdetpass[j][i] = 0;
  }

  for(j=0;j<nnx;j++)      //得知哪些探测器对应的点将会用于剂量验证
  {
    for(i=0;i<nnx;i++)
    {
      if((((i-xaorigin)*segments+xborigin)>=dileft)&&(((i-xaorigin)*segments+xborigin)<=diright)&&(((j-yaorigin)*segments+yborigin)>=ditop)&&(((j-yaorigin)*segments+yborigin)<=dibottom))
      {
        if((detector[j][i]==1)&&(M_DC[((j-yaorigin)*segments+yborigin)*Nx+(i-xaorigin)*segments+xborigin]>=M_TH))
        {
          isdetpass[j][i] = 1;    //表示该点探测器满足条件，将会被用来进行剂量验证
          totaldet++;
        }
      }
    }
  }

  CheckResult *checkResult = new CheckResult[5];
  for(int resultCount=0;resultCount<5;resultCount++)
  {
    checkResult[resultCount].GammaResult = -100;
    checkResult[resultCount].DtaResult = -100;
    checkResult[resultCount].DDResult = -100;
  }
  switch(theChoose.CheckType)
  {
    case 0:  //0 为DD
    {
      for(int roundj=0;roundj<nny;roundj++)
      {
        for(int roundi=0;roundi<nnx;roundi++)
        {
          //--------------------In the Round----------------------------------------------------
          m_NormPoint_Dose = ptm[roundi*nnx + roundj*nny];
          c_NormPoint_Dose = ptc[roundi*segments*Nx + roundj*segments*Ny];
          for(i=0;i<thenum;i++)      //做一次转换，防止(解决)析构时出现内存的多重释放问题
          {
            m_DOSE[i] = 100*ptm[i]/(m_NormPoint_Dose+0.0000001);
          }

          for(i=0;i<ncalc;i++)
          {
            M_DC[i] = 100*ptc[i]/(c_NormPoint_Dose+0.0000001);
          }

          for(i=0;i<thenum;i++)
          {
            DD[i] = -100.0;
          }

          int cc=0;
          int mipos,mjpos;
          for(j=0;j<nny;j++)
          {
            for(i=0;i<nnx;i++)
            {
              mipos = (i-xaorigin)*segments+xfirst;
              mjpos = (j-yaorigin)*segments+yfirst;
              if(isdetpass[j][i]==1)
              {
                DD[cc] = fabs(m_DOSE[j*nnx+i] - M_DC[mjpos*Nx+mipos]);//DD值
              }
              cc++;
            }
          }
          //---------------------------------------------------------------------------------
          cc=0;
          int ddpass=0;
          for(j=0;j<nny;j++)
          {
            for(i=0;i<nnx;i++)
            {
              if((DD[cc]<=diffp)&&(DD[cc]>-1.0))   //pass ,之所以要大于-1.0,是因为将没通过阈值的探测器点的三个值全设为-100.0
                ddpass++;
              cc++;
            }
          }
          float ddpercent = 100*(ddpass/(float)(totaldet));
          for(int resultCountThis=0;resultCountThis<5;resultCountThis++)
          {
            if(ddpercent>=checkResult[resultCountThis].DDResult)
            {
              checkResult[resultCountThis].DDResult = ddpercent;
              checkResult[resultCountThis].point[0] = i;
              checkResult[resultCountThis].point[1] = j;
            }
          }

        }
      }
    }break;
    case 1:  //1 为DTA
    {
      for(int roundj=0;roundj<nny;roundj++)
      {
        for(int roundi=0;roundi<nnx;roundi++)
        {
          //--------------------In the Round----------------------------------------------------
          m_NormPoint_Dose = ptm[roundi*nnx + roundj*nny];
          c_NormPoint_Dose = ptc[roundi*segments*Nx + roundj*segments*Ny];
          for(i=0;i<thenum;i++)      //做一次转换，防止(解决)析构时出现内存的多重释放问题
          {
            m_DOSE[i] = 100*ptm[i]/(m_NormPoint_Dose+0.0000001);
          }

          for(i=0;i<ncalc;i++)
          {
            M_DC[i] = 100*ptc[i]/(c_NormPoint_Dose+0.0000001);
          }

          for(i=0;i<thenum;i++)
          {
            Dta[i] = -100.0;
          }

          int cc=0;
          float TDta;
          float tempdta;
          int mipos,mjpos;
          float temp1;
          for(j=0;j<nny;j++)
          {
            for(i=0;i<nnx;i++)
            {
              mipos = (i-xaorigin)*segments+xfirst;
              mjpos = (j-yaorigin)*segments+yfirst;
              TDta = 1.0E+10;
              if(isdetpass[j][i]==1)
              {
                if(m_DOSE[j*nnx+i] == M_DC[mjpos*Nx+mipos])
                {
                  Dta[cc] = 0.0;
                }
                else
                {
                   for(jto=-10;jto<=10;jto++)              //搜索半径定为1cm
                   {
                     for(ito=-10;ito<=10;ito++)
                     {
                        temp1 = ito*ito + jto*jto;  //distance
                        tempdta = sqrt(temp1);

                        if(tempdta<=TDta)    //寻找最小dta值
                        {
                          TDta = tempdta;
                        }
                     }
                   }
                   Dta[cc]  = TDta;
                }
              }
              cc++;
            }
          }
          //---------------------------------------------------------------------------------
          cc=0;
          int dtapass=0;
          for(j=0;j<nny;j++)
          {
            for(i=0;i<nnx;i++)
            {
              if((Dta[cc]<=mm)&&(Dta[cc]>-1.0))   //pass ,之所以要大于-1.0,是因为将没通过阈值的探测器点的三个值全设为-100.0
                dtapass++;
              cc++;
            }
          }
          float dtapercent = 100*(dtapass/(float)(totaldet));
          for(int resultCountThis=0;resultCountThis<5;resultCountThis++)
          {
            if(dtapercent>=checkResult[resultCountThis].DtaResult)
            {
              checkResult[resultCountThis].DtaResult = dtapercent;
              checkResult[resultCountThis].point[0] = i;
              checkResult[resultCountThis].point[1] = j;
            }
          }


        }
      }
    }break;
    case 2:  //2 为Gamma
    default: //default 为Gamma
    {
      for(int roundj=0;roundj<nny;roundj++)
      {
        for(int roundi=0;roundi<nnx;roundi++)
        {
          //--------------------In the Round----------------------------------------------------
          m_NormPoint_Dose = ptm[roundi*nnx + roundj*nny];
          c_NormPoint_Dose = ptc[roundi*segments*Nx + roundj*segments*Ny];
          for(i=0;i<thenum;i++)      //做一次转换，防止(解决)析构时出现内存的多重释放问题
          {
            m_DOSE[i] = 100*ptm[i]/(m_NormPoint_Dose+0.0000001);
          }

          for(i=0;i<ncalc;i++)
          {
            M_DC[i] = 100*ptc[i]/(c_NormPoint_Dose+0.0000001);
          }

          for(i=0;i<thenum;i++)
          {
            M_GAMA[i] = -100.0;
          }

          int cc=0;
          float TGama;
          float tempgama;
          int mipos,mjpos;
          float temp1,temp2;
          for(j=0;j<nny;j++)
          {
            for(i=0;i<nnx;i++)
            {
              mipos = (i-xaorigin)*segments+xfirst;
              mjpos = (j-yaorigin)*segments+yfirst;
              TGama = 1.0E+10;
              if(isdetpass[j][i]==1)
              {
                if(m_DOSE[j*nnx+i] == M_DC[mjpos*Nx+mipos])
                {
                  M_GAMA[cc] = 0.0;
                }
                else
                {
                   for(jto=-10;jto<=10;jto++)              //搜索半径定为1cm
                   {
                     for(ito=-10;ito<=10;ito++)
                     {
                        temp1 = ito*ito + jto*jto;  //distance
                        temp2 =  m_DOSE[j*nnx+i] - M_DC[(mjpos+jto)*Nx+mipos+ito]; //dose gap

                        tempgama = sqrt(temp1/(M_RM*M_RM) + temp2*temp2/(M_DM*M_DM));   //这里(1)没用平方
                                                                                        //(2)diff%没除100，这两点和startJob中不同
                        if(tempgama<=TGama)       //寻找最小gama值
                        {
                          TGama = tempgama;
                        }
                     }
                   }
                   M_GAMA[cc] = TGama;
                }
              }
              cc++;
            }
          }
           //---------------------------------------------------------------------------------
          cc=0;
          int gammapass=0;
          for(j=0;j<nny;j++)
          {
            for(i=0;i<nnx;i++)
            {
              if((M_GAMA[cc]<=1)&&(M_GAMA[cc]>-1.0))   //pass ,之所以要大于-1.0,是因为将没通过阈值的探测器点的三个值全设为-100.0
                gammapass++;
              cc++;
            }
          }
          float gammapercent = 100*(gammapass/(float)(totaldet));
          for(int resultCountThis=0;resultCountThis<5;resultCountThis++)
          {
            if(gammapercent>=checkResult[resultCountThis].GammaResult)
            {
              checkResult[resultCountThis].GammaResult = gammapercent;
              checkResult[resultCountThis].point[0] = i;
              checkResult[resultCountThis].point[1] = j;
            }
          }
        }
      }
    }break;
  }

  return checkResult;

}
*/
//---------------------------------------------------------------------------
TDoseCheck::TDoseCheck(TDose *md,TDose *cd,TDoseConfig *cg,TDistance *setrcut,float a,float b,float th)
{
  pmd=md;
  pcd=cd;
  pcfg=cg;
  SetRCUT = setrcut;
  M_RM = a*a/100.0;  //M_RM即用户设定的GAMA标准中的半径值(单位cm)的平方
  M_DM = b*b/10000.0; //M_DM即用户设定的GAMA标准中的百分误差的平方

  m_x=new float[pmd->nData];
  m_y=new float[pmd->nData];
  //m_z=new float[pmd->nData];
  DOSE = new float[pmd->nData];
  m_DOSE=new float[pmd->nData];
  M_DC=new float[pmd->nData];
  M_GAMA = new float[pmd->nData];
  Dta = new float[pmd->nData];
  DD = new float[pmd->nData];
  M_RGAMA = new float[pmd->nData];//random
  RDta = new float[pmd->nData];   //random
  d = new float[SetRCUT->nn];
  x_M = new float[SetRCUT->nn];
  y_M = new float[SetRCUT->nn];
  Factor0 = new float[SetRCUT->nn];
  Factor2 = new float[SetRCUT->nn];
  Factor4 = new float[SetRCUT->nn];
  Factor6 = new float[SetRCUT->nn];
  m_Rtrack = new float[pmd->nData];   //random;
}
TDoseCheck::~TDoseCheck()
{
  if(m_x) delete[] m_x;
  if(m_y) delete[] m_y;
  //if(m_z) delete[] m_z;
  if(DOSE) delete[] DOSE; //(因为调用DoseCheck肯定会调用dose.cpp,所以没必要对pData重复的析构)
  if(m_DOSE) delete[] m_DOSE;
  if(M_DC) delete[] M_DC;
  if(M_GAMA) delete[] M_GAMA;
  if(M_RGAMA) delete[] M_RGAMA;
  if(d) delete[] d;
  if(Dta) delete[] Dta;
  if(RDta) delete[] RDta;
  if(DD) delete[] DD;
  if(x_M) delete[] x_M;
  if(y_M) delete[] y_M;
  if(Factor0) delete[] Factor0;
  if(Factor2) delete[] Factor2;
  if(Factor4) delete[] Factor4;
  if(Factor6) delete[] Factor6;
}

void TDoseCheck::StartJob()
{
  //1.读dos0.dat，已完成
  //2.读dos1.dat，已完成
  //3.读dosecomp.cfg,已完成
  //4.找最大值,已完成

//---5.赋值给m_x,m_y,m_z,m_DOSE----------------------------------------------
  int i,j,k;
  float x,y,z,temp;
  Nx = pmd->nx;         //探测器点数
  Ny = pmd->ny;
 // Nz = pmd->nz;
  NVP = 0;           //NVP从0到nData
  ddmin = 100000;
  dosemax0 = pmd->dosemax;
  dosemax1 = pcd->dosemax;
  if(dosemax0>=dosemax1)    //求两个文件的最大值
    dosemax2 = dosemax0;
  else
    dosemax2 = dosemax1;

  M_lenx0 = pcfg->lenx0;  //cfg文件第二行值
  M_leny0 = pcfg->leny0;
 // M_lenz0 = pcfg->lenz0;
  DOSE = pmd->DoseAbs;

  for(j=0;j<Ny;j++)
  {
    y = j*M_leny0;
    for(i=0;i<Nx;i++)
    {
      temp = DOSE[NVP]/dosemax2;
      m_x[NVP] = i*M_lenx0; //m_x[i]为每个探测器的x坐标值
      m_y[NVP] = y;

      m_DOSE[NVP] = temp; //m_DOSE值为从dose0文件中得
                            //到的剂量值与其中最大值的比值
      NVP++;
    }
  }
//---------------------------------------------------------------------------
   //6.SetD0  (不需要)
//---计算DoseDiffernece----------------------------------------------------
  M_DC = pcd->DoseAbs;

  for(i=0;i<NVP;i++)
  {
    if(DOSE[i]>=M_DC[i])
      DD[i] = (DOSE[i] - M_DC[i])/DOSE[i];
    else
      DD[i] = (M_DC[i] - DOSE[i])/DOSE[i];

    if(DD[i]<ddmin)
    {
      ddmin = DD[i];        //寻找最小DD值
    }
  }
//---7.赋值给M_DC-----------------------------------------------------------
  for(i=0;i<NVP;i++)
  {
    M_DC[i] /= dosemax2;
  }
//---8.SET_LEN--------------------------------------------------------------
  m_lenx = pcfg->lenx;              //对应于cfg文件中的第一行参数
  m_leny = pcfg->leny;
 // m_lenz = pcfg->lenz;

//---9.SET_LENM------------------------------------------------------------
  m_lenmx = pcfg->lenmx;             //对应于cfg文件中第三行的参数(0.05)
  m_lenmy = pcfg->lenmy;
 //m_lenmz = pcfg->lenmz;

//---10.SET_RCUT-----------------------------------------------------------
  M_RCUT = pcfg->RCUT;
//---11.SET_NSEL-----------------------------------------------------------
  m_maxn = pcfg->NSEL;              //对应于cfg文件中第五行的参数
//-------------------------------------------------------------------------
  m_lx = pcd->lx;
  m_hx = pcd->hx;
  m_ly = pcd->ly;
  m_hy = pcd->hy;
  // m_lz = pcd->lz;
  //m_hz = pcd->hz;
  //m_DC=M_DC
  float xmin = (m_lx-1)*m_lenx - 0.500*m_lenx;
  float xmax = (m_hx-1)*m_lenx + 0.500*m_lenx;
  float ymin = (m_ly-1)*m_leny - 0.500*m_leny;
  float ymax = (m_hy-1)*m_leny + 0.500*m_leny;
  //float zmin = (m_lz-1)*m_lenz - 0.500*m_lenz;
  //float zmax = (m_hz-1)*m_lenz + 0.500*m_lenz;

//12.SET_VOI(不需要)
//13.SET_DC(不需要)
//---14.DoCheck()------------------------------------------------------------
  int mn,ibx0,ibx1,iby0,iby1;
  dtamin = 100000;
  gamamin = 100000;

  float dx,dy,xm,ym,DM,p0,p2,p4,p6,TGAMA;

  if(NVP<m_maxn)  //探测器数量不是很大,做FullCheck
  {
    d = SetRCUT->distance;
    N = SetRCUT->nn;
    x_M = SetRCUT->x_rcut;
    y_M = SetRCUT->y_rcut;
    Factor0 = SetRCUT->factor0;
    Factor2 = SetRCUT->factor2;
    Factor4 = SetRCUT->factor4;
    Factor6 = SetRCUT->factor6;

    for(i=0;i<NVP;i++)
    {
      if(M_DC[i]==m_DOSE[i])
      {
        M_GAMA[i]=0.0;
        Dta[i]=0.0;
      }

      else
      {
        float d1 = 100.0;
        float TGama =1.0E+10;

        for(mn=0;mn<N;mn++)
        {
          if((d[mn]/M_RM)>TGama)
          break;

          dx=x_M[mn];
          dy=y_M[mn];
          ym = m_y[i]+dy;
          xm = m_x[i]+dx;

	  if(xm<xmin||xm>xmax||ym<ymin||ym>ymax)
	  {
            DM = 0.00;
	  }
	  else
	  {
	    ibx0 = floor((xm+0.00001)/m_lenx);
            ibx1 = ibx0+1;
            iby0 = floor((ym+0.00001)/m_leny);
            iby1 = iby0+1;

	    if(ibx0>=(m_lx-1)&&ibx0<=(m_hx-1)&&iby0>=(m_ly-1)&&iby0<=(m_hy-1))
              p0 = M_DC[ibx0+iby0*(m_hx-m_lx+1)];
	    else
	      p0 =0.0;

           if(ibx0>=(m_lx-1)&&ibx0<=(m_hx-1)&&iby1>=(m_ly-1)&&iby1<=(m_hy-1))
              p2 = M_DC[ibx0+iby1*(m_hx-m_lx+1)];
           else
              p2 = 0.0;

           if(ibx1>=(m_lx-1)&&ibx1<=(m_hx-1)&&iby0>=(m_ly-1)&&iby0<=(m_hy-1))
              p4 = M_DC[ibx1+iby0*(m_hx-m_lx+1)];
           else
              p4 = 0.0;

           if(ibx1>=(m_lx-1)&&ibx1<=(m_hx-1)&&iby1>=(m_ly-1)&&iby1<=(m_hy-1))
              p6 = M_DC[ibx1+iby1*(m_hx-m_lx+1)];
           else
              p6 = 0.0;

           DM = p0*Factor0[mn]+p2*Factor2[mn]+p4*Factor4[mn]+p6*Factor6[mn];
          }

          TGAMA= d[mn]/M_RM+ (DM - m_DOSE[i])*(DM - m_DOSE[i])/M_DM;

          if(TGAMA<TGama)
            TGama=TGAMA;
          if(fabs(m_DOSE[i]-DM)<0.03&&d[mn]<=d1)  //0.03就是软件中的%Diff
          {                                       //可以由用户自己绝对值的大小
            d1 = d[mn];
          }
        }
        M_GAMA[i] = sqrt(TGama);  //得到每个点的gama因子
        Dta[i] = d1;              //得到每点的DTA值

        if(M_GAMA[i]<gamamin)
        {
          gamamin = M_GAMA[i];      //寻找最小gama因子
        }
        if(Dta[i]<dtamin)          //寻找最小dta值
        {
          dtamin = Dta[i];
        }
      }
    }
  }

  else            //探测器数量很大时，做RandomCheck
  {
    int RR;
    float R;

    d = SetRCUT->distance;
    N = SetRCUT->nn;
    x_M = SetRCUT->x_rcut;
    y_M = SetRCUT->y_rcut;
    Factor0 = SetRCUT->factor0;
    Factor2 = SetRCUT->factor2;
    Factor4 = SetRCUT->factor4;
    Factor6 = SetRCUT->factor6;

    srand((unsigned) time(NULL));

    for(i=0;i<NVP;i++)
    {
      R = rand()/999999999.0;
      RR =(int)(R*m_maxn);
      float d1 = 100.0;
      float TGama =1.0E+10;
      if(M_DC[RR]==m_DOSE[RR])
      {
        M_RGAMA[RR] = 0;
        RDta[RR] = 0;
        m_Rtrack[i] = RR;
      }

      else
      {
        for(mn=0;mn<N;mn++)
        {
          if((d[mn]/M_RM)>TGama)
          break;

          dx=x_M[mn];
          dy=y_M[mn];
          ym = m_y[RR]+dy;
          xm = m_x[RR]+dx;

          if(xm<xmin||xm>xmax||ym<ymin||ym>ymax)
	  {
            DM = 0.00;
	  }
          else
	  {
	    ibx0 = floor((xm+0.00001)/m_lenx);
            ibx1 = ibx0+1;
            iby0 = floor((ym+0.00001)/m_leny);
            iby1 = iby0+1;

	    if(ibx0>=m_lx&&ibx0<=m_hx&&iby0>=m_ly&&iby0<=m_hy)
              p0 = M_DC[(ibx0-1)+(iby0-1)*(m_hx-m_lx+1)];
	    else
	      p0 =0.0;

            if(ibx0>=m_lx&&ibx0<=m_hx&&iby1>=m_ly&&iby1<=m_hy)
              p2 = M_DC[(ibx0-1)+(iby1-1)*(m_hx-m_lx+1)];
            else
              p2 = 0.0;

            if(ibx1>=m_lx&&ibx1<=m_hx&&iby0>=m_ly&&iby0<=m_hy)
              p4 = M_DC[(ibx1-1)+(iby0-1)*(m_hx-m_lx+1)];
            else
              p4 = 0.0;

            if(ibx1>=m_lx&&ibx1<=m_hx&&iby1>=m_ly&&iby1<=m_hy)
              p6 = M_DC[(ibx1-1)+(iby1-1)*(m_hx-m_lx+1)];
            else
              p6 = 0.0;

            DM = p0*Factor0[mn]+p2*Factor2[mn]+p4*Factor4[mn]+p6*Factor6[mn];
          }

          TGAMA= d[mn]/M_RM+ (DM - m_DOSE[RR])*(DM - m_DOSE[RR])/M_DM;

          if(TGAMA<TGama)
            TGama=TGAMA;
          if(fabs(m_DOSE[RR]-DM)<0.04&&d[mn]<=d1)
          {
            d1 = d[mn];
          }
        }
        M_RGAMA[i] = sqrt(TGama);  //得到每个随机点的gama因子
        RDta[i] = d1;              //得到每个随机点的DTA值
        m_Rtrack[i] = RR;          //每个随机点的位置

        if(M_GAMA[i]<gamamin)
        {
          gamamin = M_RGAMA[i];      //寻找最小gama因子
        }
        if(Dta[i]<dtamin)
        {
          dtamin = RDta[i];         //寻找最小dta值
        }

      }
    }
  }
}

void TDoseCheck::SaveGamaResult(char *file)      //输出Gama因子
{
  int I;
  if(NVP<m_maxn)
  {
    FILE *fp;
    if((fp=fopen(file,"w"))==NULL)
    {
      printf("cannot open file\n");
      exit(0);
    }
    for(I=0;I<NVP;I++)
    {
      fprintf(fp,"%f,%f,%f\n",m_x[I],M_GAMA[I],m_y[I]);
    }

    fclose(fp);
  }
  else
  {
    int tra;//用来得到随机检查时候的点
    FILE *fp;
    if((fp = fopen(file,"w"))==NULL)
    {
      printf("cannot open file\n");
      exit(0);
    }
    for(I=0;I<NVP;I++)
    {
      tra = m_Rtrack[I];
      fprintf(fp,"%f,%f,%f\n",m_x[tra],M_RGAMA[I],m_y[tra]);
    }
    fclose(fp);
  }
}

void TDoseCheck::SaveDtaResult(char *file)
{
  int I;
  if(NVP<m_maxn)
  {
    FILE *fp;
    if((fp=fopen(file,"w"))==NULL)
    {
      printf("cannot open file\n");
      exit(0);
    }
    for(I=0;I<NVP;I++)
    {
      fprintf(fp,"%f,%f,%f\n",m_x[I],Dta[I],m_y[I]);
    }

    fclose(fp);
  }
  else                     //random
  {
    int tra;
    FILE *fp;
    if((fp = fopen(file,"w"))==NULL)
    {
      printf("cannot open file\n");
      exit(0);
    }
    for(I=0;I<NVP;I++)
    {
      tra = m_Rtrack[I];
      fprintf(fp,"%f,%f,%f\n",m_x[tra],RDta[I],m_y[tra]);
    }
    fclose(fp);
  }
}

void TDoseCheck::SaveDdResult(char *file)
{
  int I;
  FILE *fp;
  if((fp=fopen(file,"w"))==NULL)
  {
    printf("cannot open file\n");
    exit(0);
  }
  for(I=0;I<NVP;I++)
  {
    fprintf(fp,"%f,%f,%f\n",m_x[I],DD[I],m_y[I]);
  }
  fclose(fp);
}
//-----------------------------------------------------------------------------
/*
void TDICheck::GetArrayinfo()
{
  int i,j;
  for(j=0;j<=44;j++)   //先全部设为0
  {
    for(i=0;i<=44;i++)
    {
      detectorinfo[i][j]=0;
    }
  }

  for(j=12;j<=32;j=j+2)
  {
    for(i=12;i<=32;i=i+2)
    {
      detectorinfo[i][j] = 1;
    }
  }

  for(j=13;j<=31;j=j+2)
  {
    for(i=13;i<=31;i=i+2)
    {
      detectorinfo[i][j] = 1;
    }
  }

  for(i=0;i<=44;i=i+2)
  {
    detectorinfo[i][22] = 1;
  }

  for(j=0;j<=44;j=j+2)
  {
    detectorinfo[22][j] = 1;
  }

  for(i=4;i<=40;i++)
  {
    detectorinfo[i][i] = 1;
    detectorinfo[44-i][i] = 1;
  }

  for(i=10;i<=34;i=i+4)
  {
    for(j=0;j<=44;j=j+4)
    {
      detectorinfo[i][j] = 1;
    }
  }

  for(i=8;i<=36;i=i+4)
  {
    for(j=2;j<=42;j=j+4)
    {
      detectorinfo[i][j] = 1;
    }
  }

  for(j=10;j<=34;j=j+4)
  {
    detectorinfo[0][j] = 1;
  }

  for(j=10;j<=34;j=j+4)
  {
    detectorinfo[44][j] = 1;
  }

  for(j=8;j<=36;j=j+4)
  {
    detectorinfo[2][j] = 1;
  }

  for(j=8;j<=36;j=j+4)
  {
    detectorinfo[42][j] = 1;
  }

  for(j=6;j<=38;j=j+4)
  {
    detectorinfo[4][j] = 1;
  }

  for(j=6;j<=38;j=j+4)
  {
    detectorinfo[40][j] = 1;
  }
  for(j=4;j<=40;j=j+4)
  {
    detectorinfo[6][j] = 1;
  }
  for(j=4;j<=40;j=j+4)
  {
    detectorinfo[38][j] = 1;
  }
}
*/
