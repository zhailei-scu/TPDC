#include "Paramter.h"

//---------------------------Class:FunctionButtonTransTag----------------------------
/*Constructor*/
FunctionButtonTransTag::FunctionButtonTransTag(){
  this->isPrimordial = false;
}
/*Destructor*/
FunctionButtonTransTag::~FunctionButtonTransTag(){
  this->isPrimordial = false;
}

void FunctionButtonTransTag::trans(){
  this->isPrimordial = (!this->isPrimordial);
}
bool FunctionButtonTransTag::status(){
  return this->isPrimordial;
}
void FunctionButtonTransTag::reset(){
  this->isPrimordial = false;
}
//---------------------------Class:MoveLine---------------------------------
/*Constructor*/
MoveLine::MoveLine(){
  this->xLinePos = 0;
  this->yLinePos = 0;
  this->movedInXDirection = false;
  this->movedInYDirection = false;
}
/*Destructor*/
MoveLine::~MoveLine(){

}
/*Other functions*/
int MoveLine::getXLinePos(){
  return this->xLinePos;
}
void MoveLine::xLinePosIncrease(){
  ++(this->xLinePos);
}
void MoveLine::xLinePosDecrease(){
  --(this->xLinePos);
}

void MoveLine::setXLinePos(int pos){
  this->xLinePos = pos;
}

int MoveLine::getYLinePos(){
  return this->yLinePos;
}
void MoveLine::yLinePosIncrease(){
  ++(this->yLinePos);
}
void MoveLine::yLinePosDecrease(){
  --(this->yLinePos);
}
void MoveLine::setYLinePos(int pos){
  this->yLinePos = pos;
}

bool MoveLine::ifMovedInXDirection(){
  return this->movedInXDirection;
}
void MoveLine::setMovedStatusInXDirection(){
  this->movedInXDirection = true;
  this->movedInYDirection = false;
}
void MoveLine::setUnMovedStatusInXDirection(){
  this->movedInXDirection = false;
}

bool MoveLine::ifMovedInYDirection(){
  return this->movedInYDirection;
}
void MoveLine::setMovedStatusInYDirection(){
  this->movedInYDirection = true;
  this->movedInXDirection = false;
}
void MoveLine::setUnMovedStatusInYDirection(){
  this->movedInYDirection = false;
}

void MoveLine::reset(){
  this->xLinePos = 0;
  this->yLinePos = 0;
  this->movedInXDirection = false;
  this->movedInYDirection = false;
}

//-----------------------Class:GraphsicTemporaryValues------------------
/*Constructor*/
GraphsicTemporaryValues::GraphsicTemporaryValues(){
  /*Basic values*/
  this->measureRowLength = 0;
  this->measureColLength = 0;
  this->measureHeightLength = 0;

  this->calcRowLength = 0;
  this->calcColLength = 0;
  this->calcHeightLength = 0;

  this->measureArrayShowCenter.reset();

  this->calcArrayShowCenter.reset();

  this->measureFirstAlignmentCenter.reset();

  this->calcFirstAlignmentCenter.reset();

  this->measureDoseCentral.reset();
  this->calcDoseCentral.reset();

  for(int i=0;i<3;i++){
    this->segments[i] = -1;
  }

  this->measureFileType = 0;

  this->measureTotalNum = 0;
  this->calcTotalNum = 0;

  this->measureXGridLineNum = 0;
  this->measureYGridLineNum = 0;
  this->calcXGridLineNum = 0;
  this->calcYGridLineNum = 0;

  this->cutBian.reset();
  this->cutBian.allocate(2,2,1);

  this->measureFilePath.clear();
  this->calcFilePath.clear();

  /*CheckedRecord*/
  this->checkedRecord.reset();
  this->checkStandardParam.reset();

  /*Dose Data*/
  this->NormMeasureDoseData.reset();
  this->measureDoseData.reset();
  this->NormCalcDoseData.reset();
  this->calcDoseData.reset();
  this->measureHotPointData.reset();
  this->calcHotPointData.reset();

  maxMeasurePoint.reset();
  minMeasurePoint.reset();
  maxCalcPoint.reset();
  minCalcPoint.reset();

  /*GAMMA,DTA,DD array*/
  this->storeGammaArray.reset();
  this->storeDTAArray.reset();
  this->storeDDArray.reset();


  /*Operation values*/
  this->moveLine.reset();
  this->detectorsShownTag.reset();

  /*Detector Array*/
  this->detectorArray.reset();
  /*data grid */
  this->measureDataShowTag.reset();
  this->calcDataShowTag.reset();

  /*2D/3D Trans*/
  this->measureDimensionTransTag.reset();
  this->calcDimensionTransTag.reset();

  /*GridLine*/
  this->measureGridLineTag.reset();
  this->calcGridLineTag.reset();

  this->doseType = DoseType(DOSE_RELATIVE);
  this->doseInterploated = false;


  //Note: the follow member will influence the handledPairDose
  this->operator_measureDoseCentral.reset();
  this->operator_calcDoseCentral.reset();

}

/*Destructor*/
GraphsicTemporaryValues::~GraphsicTemporaryValues(){
  /*Basic values*/
  this->measureRowLength = 0;
  this->measureColLength = 0;
  this->measureHeightLength = 0;

  this->calcRowLength = 0;
  this->calcColLength = 0;
  this->calcHeightLength = 0;

 this->measureArrayShowCenter.reset();

  this->calcArrayShowCenter.reset();

  this->measureFirstAlignmentCenter.reset();

  this->calcFirstAlignmentCenter.reset();

  this->measureDoseCentral.reset();
  this->calcDoseCentral.reset();

  for(int i=0;i<3;i++){
    this->segments[i] = -1;
    this->gridSize[i] = -1;
  }

  this->measureFileType = 0;

  this->measureTotalNum = 0;
  this->calcTotalNum = 0;

  this->measureXGridLineNum = 0;
  this->measureYGridLineNum = 0;
  this->calcXGridLineNum = 0;
  this->calcYGridLineNum = 0;

  this->cutBian.reset();

  this->measureFilePath.clear();
  this->calcFilePath.clear();

  /*CheckedRecord*/
  this->checkedRecord.reset();
  this->checkStandardParam.reset();

  /*Dose Data*/
  this->NormMeasureDoseData.reset();
  this->measureDoseData.reset();
  this->NormCalcDoseData.reset();
  this->calcDoseData.reset();
  this->measureHotPointData.reset();
  this->calcHotPointData.reset();

  maxMeasurePoint.reset();
  minMeasurePoint.reset();
  maxCalcPoint.reset();
  minCalcPoint.reset();

  /*GAMMA,DTA,DD Array*/
  this->storeGammaArray.reset();
  this->storeDTAArray.reset();
  this->storeDDArray.reset();

  /*Dector Array*/
  this->detectorArray.reset();
  /*data grid */
  this->measureDataShowTag.reset();
  this->calcDataShowTag.reset();

  /*2D/3D Trans*/
  this->measureDimensionTransTag.reset();
  this->calcDimensionTransTag.reset();

  /*GridLine*/
  this->measureGridLineTag.reset();
  this->calcGridLineTag.reset();

  /*Operation values*/
  this->moveLine.reset();
  this->detectorsShownTag.reset();


  this->doseType = DoseType(DOSE_RELATIVE);
  this->doseInterploated = false;


  //Note: the follow member will influence the handledPairDose
  this->operator_measureDoseCentral.reset();
  this->operator_calcDoseCentral.reset();
}

void GraphsicTemporaryValues::reset(){
  /*Basic values*/
  this->measureRowLength = 0;
  this->measureColLength = 0;
  this->measureHeightLength = 0;

  this->calcRowLength = 0;
  this->calcColLength = 0;
  this->calcHeightLength = 0;

  this->measureArrayShowCenter.reset();

  this->calcArrayShowCenter.reset();

  this->measureFirstAlignmentCenter.reset();

  this->calcFirstAlignmentCenter.reset();

  this->measureDoseCentral.reset();
  this->calcDoseCentral.reset();

  for(int i=0;i<3;i++){
    this->segments[i] = -1;
    this->gridSize[i] = -1;
  }

  this->measureFileType = 0;

  this->cutBian.reset();
  this->cutBian.allocate(2,2,1);

  this->measureTotalNum = 0;
  this->calcTotalNum = 0;

  this->measureXGridLineNum = 0;
  this->measureYGridLineNum = 0;
  this->calcXGridLineNum = 0;
  this->calcYGridLineNum = 0;

  this->measureFilePath.clear();
  this->calcFilePath.clear();

  /*CheckedRecord*/
  this->checkedRecord.reset();
  this->checkStandardParam.reset();

  /*Dose Data*/
  this->NormMeasureDoseData.reset();
  this->measureDoseData.reset();
  this->NormCalcDoseData.reset();
  this->calcDoseData.reset();
  this->measureHotPointData.reset();
  this->calcHotPointData.reset();

  maxMeasurePoint.reset();
  minMeasurePoint.reset();
  maxCalcPoint.reset();
  minCalcPoint.reset();

   /*GAMMA,DTA,DD Array*/
  this->storeGammaArray.reset();
  this->storeDTAArray.reset();
  this->storeDDArray.reset();

  /*Dector Array*/
  this->detectorArray.reset();
  /*data grid */
  this->measureDataShowTag.reset();
  this->calcDataShowTag.reset();

  /*Operation values*/
  this->moveLine.reset();
  this->detectorsShownTag.reset();

  /*2D/3D Trans*/
  this->measureDimensionTransTag.reset();
  this->calcDimensionTransTag.reset();

  /*GridLine*/
  this->measureGridLineTag.reset();
  this->calcGridLineTag.reset();

  this->doseType = DoseType(DOSE_RELATIVE);
  this->doseInterploated = false;

  //Note: the follow member will influence the handledPairDose
  this->operator_measureDoseCentral.reset();
  this->operator_calcDoseCentral.reset();
}

void GraphsicTemporaryValues::measureReset(){
  /*Basic values*/
  this->measureRowLength = 0;
  this->measureColLength = 0;
  this->measureHeightLength = 0;

  this->measureArrayShowCenter.reset();

  this->measureFirstAlignmentCenter.reset();

  this->measureDoseCentral.reset();



  for(int i=0;i<3;i++){
    this->segments[i] = -1;
    this->gridSize[i] = -1;
  }

  this->measureFileType = 0;

  this->measureTotalNum = 0;

  this->measureXGridLineNum = 0;
  this->measureYGridLineNum = 0;

  this->measureFilePath.clear();

  /*CheckedRecord*/
  this->checkedRecord.reset();
  //this->checkStandardParam.reset();

  /*Dose Data*/
  this->NormMeasureDoseData.reset();
  this->measureDoseData.reset();
  this->measureHotPointData.reset();

  maxMeasurePoint.reset();
  minMeasurePoint.reset();

   /*GAMMA,DTA,DD Array*/
  this->storeGammaArray.reset();
  this->storeDTAArray.reset();
  this->storeDDArray.reset();

  /*Dector Array*/
  this->detectorArray.reset();
  /*data grid */
  this->measureDataShowTag.reset();

  /*Operation values*/
  this->moveLine.reset();
  this->detectorsShownTag.reset();

  /*2D/3D Trans*/
  this->measureDimensionTransTag.reset();

  /*GridLine*/
  this->measureGridLineTag.reset();

  this->doseType = DoseType(DOSE_RELATIVE);
  this->doseInterploated = false;

  //Note: the follow member will influence the handledPairDose
  this->operator_measureDoseCentral.reset();
}

void GraphsicTemporaryValues::calcReset(){
  /*Basic values*/
  this->calcRowLength = 0;
  this->calcColLength = 0;
  this->calcHeightLength = 0;

  this->calcArrayShowCenter.reset();

  this->calcFirstAlignmentCenter.reset();

  this->calcDoseCentral.reset();

//  this->calcGraphyOriginPos.reset();

  this->calcTotalNum = 0;

  this->calcXGridLineNum = 0;
  this->calcYGridLineNum = 0;

  this->cutBian.reset();

  this->calcFilePath.clear();

  /*CheckedRecord*/
  this->checkedRecord.reset();
  //this->checkStandardParam.reset();

  /*Dose Data*/
  this->NormCalcDoseData.reset();
  this->calcDoseData.reset();
  this->calcHotPointData.reset();

  maxCalcPoint.reset();
  minCalcPoint.reset();

   /*GAMMA,DTA,DD Array*/
  this->storeGammaArray.reset();
  this->storeDTAArray.reset();
  this->storeDDArray.reset();

  /*Operation values*/
  this->moveLine.reset();
  this->detectorsShownTag.reset();

  /*data grid */
  this->calcDataShowTag.reset();

  /*2D/3D Trans*/
  this->calcDimensionTransTag.reset();

  /*GridLine*/
  this->calcGridLineTag.reset();

  //Note: the follow member will influence the handledPairDose
  this->operator_calcDoseCentral.reset();

}
