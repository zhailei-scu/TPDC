//Parameters

#pragma once

#ifndef ParamterH
#define ParamterH

#include "Util.h"
#include "dose.h"
#include "CheckRecord.h"
#include "HandledPairDose.h"

//---------------------------Class:FunctionButtonTransTag----------------------------
class FunctionButtonTransTag{
private:
  bool isPrimordial;
public:
  /*Constructor*/
  FunctionButtonTransTag();
  /*Destructor*/
  ~FunctionButtonTransTag();
private:
  /*ban the copy constructor and operation = */
  FunctionButtonTransTag(const FunctionButtonTransTag& r);
  FunctionButtonTransTag operator = (const FunctionButtonTransTag& r);

public:
  void trans();
  bool status();
  void reset();
};

//---------------------------Class:MoveLine---------------------------------
//used to record the moving profile line status
class MoveLine{
private:
  int xLinePos;         //record the moving line position (x-direction)
  int yLinePos;         //record the moving line position (y-direction)
  bool movedInXDirection;   //record whether the line has moved in x-direction
  bool movedInYDirection;   //record whether the line has moved in y-direction
public:
  /*Constructor*/
  MoveLine();
  /*Destructor*/
  ~MoveLine();
private:
  /*ban the copy constructor and operation = */
  MoveLine(const MoveLine& r);
  MoveLine operator = (const MoveLine& r);

public:
  int getXLinePos();
  void xLinePosIncrease();
  void xLinePosDecrease();
  void setXLinePos(int pos);

  int getYLinePos();
  void yLinePosIncrease();
  void yLinePosDecrease();
  void setYLinePos(int pos);

  bool ifMovedInXDirection();
  void setMovedStatusInXDirection();
  void setUnMovedStatusInXDirection();

  bool ifMovedInYDirection();
  void setMovedStatusInYDirection();
  void setUnMovedStatusInYDirection();

  void reset();
};

//-----------------------Class:GraphsicTemporaryValues------------------
class GraphsicTemporaryValues{
public:
  /*Basic values*/
  int measureRowLength;
  int measureColLength;
  int measureHeightLength;

  int calcRowLength;
  int calcColLength;
  int calcHeightLength;

  GridPoint measureArrayShowCenter;
  GridPoint calcArrayShowCenter;

  GridPoint measureFirstAlignmentCenter;
  GridPoint calcFirstAlignmentCenter;

  PhysicalPoint measureDoseCentral;
  PhysicalPoint calcDoseCentral;

//  PhysicalPoint measureGraphyOriginPos;
//  PhysicalPoint calcGraphyOriginPos;

  int segments[3];    //segments for grid density enhance
  double gridSize[3];

  MatrixData<bool> detectorArray;   //To record if the special point own a dector

  int measureTotalNum;
  int calcTotalNum;

  int measureXGridLineNum;     //The X direction grid lines number in measure graphic
  int measureYGridLineNum;     //The Y direction grid lines number in measure graphic
  int calcXGridLineNum;        //The X direction grid lines number in calculation graphic
  int calcYGridLineNum;        //The Y direction grid lines number in calculation graphic

  string measureFilePath;
  string calcFilePath;


  DoseType doseType;     //dose type, identify these dose as a relative/absolute dose distribution
  bool doseInterploated; //default:fasle we notify that in some case, check software would ouput some interploated dose(mapCHECK in some case)

public:
  MatrixData<int> cutBian;

  FILETYPE measureFileType;

public:
  CheckedRecord checkedRecord;
  StandardParam checkStandardParam;

public:
  MatrixData<double> NormMeasureDoseData; //store the Normlized Measure dose temporary for a faster responding while operating graphic
  MatrixData<double> measureDoseData;  //store the original Measure dose temporary for a faster responding while operating graphic
  MatrixData<double> NormCalcDoseData;    //store the  dose temporary for a faster responding while operating graphic
  MatrixData<double> calcDoseData;     //store the original calculate dose temporary for a faster responding while operating graphic

  MatrixData<double> measureHotPointData;
  MatrixData<double> calcHotPointData;

  GridPoint maxMeasurePoint;
  GridPoint minMeasurePoint;
  GridPoint maxCalcPoint;
  GridPoint minCalcPoint;

  MatrixData<double> storeGammaArray;     //store the Gamma Array temporary for a fast responding while operating graphic
  MatrixData<double> storeDTAArray;       //store the DTA Array temporary for a fast responding while operating graphic
  MatrixData<double> storeDDArray;        //store the DD Array temporary for a fast responding while operating graphic

public:
  /*Operation values*/
  FunctionButtonTransTag detectorsShownTag; //record whether the detectors are shown in graphic

  FunctionButtonTransTag measureDimensionTransTag;//record the 2D/3D Trans
  FunctionButtonTransTag calcDimensionTransTag;

  FunctionButtonTransTag measureDataShowTag;       //record whether the data grid is shown
  FunctionButtonTransTag calcDataShowTag;

  FunctionButtonTransTag measureGridLineTag; //record whether the grid line is shown
  FunctionButtonTransTag calcGridLineTag;


  MoveLine moveLine;                   //used to record the moving profile line status


public:
  //Note: the follow member will influence the handledPairDose
  PhysicalPoint operator_measureDoseCentral;
  PhysicalPoint operator_calcDoseCentral;
  
public:
  /*Constructor*/
  GraphsicTemporaryValues();
  /*Destructor*/
  ~GraphsicTemporaryValues();
private:
  /*ban the copy constructor and operation = */
  GraphsicTemporaryValues(const GraphsicTemporaryValues& r);
  GraphsicTemporaryValues operator = (const GraphsicTemporaryValues& r);

public:
  void reset();
  void measureReset();
  void calcReset();
};

//------------------------------------------------------------------
#endif

