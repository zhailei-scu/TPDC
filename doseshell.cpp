//---------------------------------------------------------------------------
#pragma hdrstop

#pragma package(smart_init)

#pragma link "TeeSurfa"
#pragma link "TeePageNumTool"
#pragma link "TeeTools"
#pragma link "TeeChartGrid"
#pragma link "TeeEdit"
#pragma link "TeeTransposeTool"
#pragma link "TeeDragPoint"
#pragma link "TeeGanttTool"
#pragma link "TeeSeriesRegion"
#pragma link "TeeFibonacci"
#pragma link "TeeSurfaceTool"
#pragma link "TeeComma"
#pragma link "TeeOpenGL"
#pragma link "TeeSubChart"
#pragma link "TeeHistogram"
#pragma link "CurvFitt"
#pragma link "TeePoin3"
#pragma link "TeeSpline"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzListVw"
#pragma link "RzGroupBar"
#pragma link "RzTray"
#pragma link "RzPathBar"
#pragma link "RzShellDialogs"
#pragma link "RzTabs"
#pragma link "RzBHints"
#pragma link "RzTreeVw"
#pragma link "StatChar"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma link "RzCommon"
#pragma link "RzSelDir"
#pragma resource "*.dfm"


#include <vcl.h>
#include <sstream>
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include "registry.hpp"

#include "time.h"
#include "Distance.h"
#include "Check.h"
#include "DoseConfig.h"
#include "doseshell.h"
#include "Paraset.h"
#include "Systemset.h"
#include "About.h"
#include "Changelevels.h"
#include "PrintSet.h"
#include "Smoothing.h"
#include "ShowBestFiveResult.h"
#include "NormPointSet.h"
#include "Angle.h"
#include "StaticsQuery.h"
#include "caxSetting.h"
#include "DTAWayChoose.h"
#include "DDStatistic.h"
#include "NormValueSetting.h"

#include "LogFrame.h"
#include "GlobalData.h"
#include "SegmentsSetting.h"
#include "ModelSetting.h"


//------------------------------------------------------------------------
TFormMain *FormMain;
//-------------------------------------------------------------------------
__fastcall TFormMain::~TFormMain(){   //析构函数

  this->temporaryValues.reset();                        
}

//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
  Application->OnMessage = Proc;
  FormMain->KeyPreview = true;
  this->temporaryValues.reset();

  seczoom[0] = 1;
  seczoom[1] = 1;
  seczoom[2] = 1;
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::RzToolButtonSegmentsClick(TObject *Sender)
{
  //
  TFormSegmentsSetting *formSegmentsSetting = new TFormSegmentsSetting(this);
  formSegmentsSetting->Parent = this;
  formSegmentsSetting->FormStyle = fsStayOnTop;
  formSegmentsSetting->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RzToolButtonNormPointSetClick(TObject *Sender)
{
  //
  SeriesMeasureNormPointX->Clear();
  SeriesMeasureNormPointY->Clear();

  SeriesCalcNormPointX->Clear();
  SeriesCalcNormPointY->Clear();


  TFormNormPointSet* formNormPointSet = new TFormNormPointSet(this);
  formNormPointSet->Parent = this;
  formNormPointSet->FormStyle = fsStayOnTop;
  formNormPointSet->Show();
}
//-------------------------------------------------------------------------
void __fastcall TFormMain::showNormPos(PhysicalPoint measureNormPos,PhysicalPoint calcNormPos){
  //
  SeriesMeasureNormPointX->Clear();
  SeriesMeasureNormPointY->Clear();

  SeriesCalcNormPointX->Clear();
  SeriesCalcNormPointY->Clear();

  double tempValue;
  PhysicalPoint measureNormGridPos,calcNromGridPos;

  measureNormGridPos.x = measureNormPos.x/this->temporaryValues.gridSize[0];
  measureNormGridPos.y = measureNormPos.y/this->temporaryValues.gridSize[1];

  calcNromGridPos.x = calcNormPos.x/(this->temporaryValues.gridSize[0]/this->temporaryValues.segments[0]);
  calcNromGridPos.y = calcNormPos.y/(this->temporaryValues.gridSize[1]/this->temporaryValues.segments[1]);

  for(int i=0;i<temporaryValues.measureRowLength;i++){
    tempValue = getDoseDataInAPosition(temporaryValues.NormMeasureDoseData,
                                       i,
                                       measureNormGridPos.y,
                                       0,
                                       INTEPOLATION_ALGORITHM(LINER),
                                       HANDLE_MODEL(ADAC)
                                       );

    SeriesMeasureNormPointX->AddXYZ(i-temporaryValues.measureArrayShowCenter.row,
                     tempValue,
                     measureNormGridPos.y - temporaryValues.measureArrayShowCenter.col,
                     "dot",
                     clRed);
  }

  for(int j=0;j<temporaryValues.measureColLength;j++){
    tempValue = getDoseDataInAPosition(temporaryValues.NormMeasureDoseData,
                                       measureNormGridPos.x,
                                       j,
                                       0,
                                       INTEPOLATION_ALGORITHM(LINER),
                                       HANDLE_MODEL(ADAC)
                                       );

    SeriesMeasureNormPointY->AddXYZ(measureNormGridPos.x -temporaryValues.measureArrayShowCenter.row,
                     tempValue,
                     j-temporaryValues.measureArrayShowCenter.col,
                     "dot",
                     clRed);
  }

  for(int i=temporaryValues.cutBian.at(0,0,0);i<=temporaryValues.cutBian.at(0,1,0);i++){
    tempValue = getDoseDataInAPosition(temporaryValues.NormCalcDoseData,
                                       i,
                                       calcNromGridPos.y,
                                       0,
                                       INTEPOLATION_ALGORITHM(LINER),
                                       HANDLE_MODEL(ADAC)
                                       );

    SeriesCalcNormPointX->AddXYZ(i-temporaryValues.calcArrayShowCenter.row,
                     tempValue,
                     calcNromGridPos.y -temporaryValues.calcArrayShowCenter.col,
                     "dot",
                     clRed);
  }

  for(int j=temporaryValues.cutBian.at(1,0,0);j<=temporaryValues.cutBian.at(1,1,0);j++){
    tempValue = getDoseDataInAPosition(temporaryValues.NormCalcDoseData,
                                       calcNromGridPos.x,
                                       j,
                                       0,
                                       INTEPOLATION_ALGORITHM(LINER),
                                       HANDLE_MODEL(ADAC)
                                       );

    SeriesCalcNormPointY->AddXYZ(calcNromGridPos.x-temporaryValues.calcArrayShowCenter.row,
                     tempValue,
                     j -temporaryValues.calcArrayShowCenter.col,
                     "dot",
                     clRed);
  }




}
//---------------------------------------------------------------------------
void __fastcall TFormMain::LogSettingClick(TObject *Sender)
{
  this->RzSelDirDialogSet->Execute();

  TRegistry *pReg = new TRegistry();
  
  pReg->RootKey = HKEY_CURRENT_USER; // 打开主键

  if(!pReg->KeyExists("Software\\TPDC")){
    pReg->CreateKey("Software\\TPDC");
  }else{
    pReg->OpenKey("Software\\TPDC",false);
  }

  pReg->WriteString("LogPath",RzSelDirDialogSet->Directory +  "OperationLog.txt");
  
  pReg->CloseKey();
  delete pReg;
  pReg = NULL;
}

//---------------------------------------------------------------
bool __fastcall TFormMain::RefreshMeasureDoseGraphicFromDisplayValue(){

  bool result;
  double tempValue;
  double doseCentralPosX,doseCentralPosY;

  GlobalMembers *globalMem = NULL;
  DisplayPairDose* displayPairDose = NULL;
  Dose* measureDisplayDose = NULL;
  Dose* normMeasureDisplayDose = NULL;

  MatrixData<double> *doseMatrix = NULL;
  double* dosePtr = NULL;

  //Reset the temporyValues
  temporaryValues.measureReset();

  //Clear Measure Graphic Chart
  ClearMeasureChart();

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    return false;
  }

  displayPairDose = globalMem->getDisplayPairDose();
  if(NULL == displayPairDose){
    RunningLog::writeLog("The DisplayPairDose is NULL;");
    return false;
  }

  //Abs MeasureDose
  measureDisplayDose = displayPairDose->getMeasureDisplayDose();
  if(NULL == measureDisplayDose){
    RunningLog::writeLog("The original MeasureDisplayDose is NULL;");
    return false;
  }

  temporaryValues.measureFirstAlignmentCenter = *measureDisplayDose->getFirstAlignmentCentral();

  measureDisplayDose->sync_Read_Start();

  temporaryValues.measureFirstAlignmentCenter = *measureDisplayDose->getFirstAlignmentCentral();

  for(int i=0;i<3;i++){
    temporaryValues.segments[i] = measureDisplayDose->getSegments()[i];
    temporaryValues.gridSize[i] = measureDisplayDose->getGridSizes()[i];
  }

  doseMatrix = measureDisplayDose->getDoseMatrix();
  if(NULL == doseMatrix){
    RunningLog::writeLog("The abs Measure dose Matrix is NULL;");
    return false;
  }
  if(NULL == doseMatrix->getData()){
    RunningLog::writeLog("The abs Measure dose data is NULL;");
    return false;
  }
  temporaryValues.measureRowLength = doseMatrix->getRowLength();
  temporaryValues.measureColLength = doseMatrix->getColLength();
  temporaryValues.measureHeightLength = doseMatrix->getHeightLength();
  temporaryValues.measureTotalNum = doseMatrix->getDataLength();
  temporaryValues.measureDoseData = *doseMatrix;

  temporaryValues.doseType = measureDisplayDose->sync_getDoseType();
  temporaryValues.doseInterploated = measureDisplayDose->sync_getDoseInterploated();

  temporaryValues.measureFileType = measureDisplayDose->sync_getFileType();     //Step:1

  SetDetectorsArray(temporaryValues.detectorArray,temporaryValues.measureFileType);//Step:2    //读取探测器阵列信息(这个要先进行)
  if(temporaryValues.measureFileType == FILETYPE(MapCHECKMeasureFileType) && false == temporaryValues.doseInterploated ){        //Step:3
    displayPairDose->MapCHECKMeasureBlineInterpolation();
  }

  temporaryValues.measureFilePath = measureDisplayDose->unSync_getFileName();

  measureDisplayDose->sync_finish();

  //norm MeasureDose
  normMeasureDisplayDose = displayPairDose->getNormMeasureDisplayDose();
  if(NULL == normMeasureDisplayDose){
    RunningLog::writeLog("The NormMeasureDisplayDose is NULL;");
    return false;
  }

  normMeasureDisplayDose->sync_Read_Start();

  doseMatrix = normMeasureDisplayDose->getDoseMatrix();
  if(NULL == doseMatrix){
    RunningLog::writeLog("The norm Measure dose Matrix is NULL;");
    return false;
  }
  if(NULL == doseMatrix->getData()){
    RunningLog::writeLog("The norm Measure dose data is NULL;");
    return false;
  }

  temporaryValues.measureDoseCentral = *normMeasureDisplayDose->getDoseCentral();

  temporaryValues.NormMeasureDoseData = *doseMatrix;

  temporaryValues.maxMeasurePoint = getMaxValuePoint(*doseMatrix);

  normMeasureDisplayDose->sync_finish();

  if(NULL == globalMem->getDoseCheck()){
    globalMem->allocateDoseCheck();
  }
  globalMem->getDoseCheck()->reset();

  //-------------------------------

  TeeOpenGLMeasure->Active = true;
  TeeOpenGLMeasure->TeePanel = ChartMeasure;

  ChartMeasure->MarginBottom = 0;
  ChartMeasure->MarginTop = 0;
  ChartMeasure->MarginLeft = 0;
  ChartMeasure->MarginRight = 0;
  ChartMeasure->BottomAxis->StartPosition = 50 - (temporaryValues.measureRowLength)*(25 + 25*((float)(ChartMeasure->Height))/ChartMeasure->Legend->Left)/(float)(temporaryValues.measureColLength);
  ChartMeasure->BottomAxis->EndPosition = 50 + (temporaryValues.measureRowLength)*(25 + 25*((float)(ChartMeasure->Height))/ChartMeasure->Legend->Left)/(float)(temporaryValues.measureColLength);

  seczoom[0] = 1;   //此时不存在剪切后放大修正的问题


  //find the central position in the dose plan(x-direction and y-direction)
  /*
  if(temporaryValues.measureRowLength%2==1){
    //对于探测器点数长和宽都为奇数的情况下（比如Mapcheck的45*45）,让每一个探测器都处于整数位置，
    //就是说，对于中测45×45的情况，让探测器坐标为-22到22中的每一个整数位置，坐标原点刚好位于(0,0)的位置,
    //选择原点为数组上的22（从0开始）
    temporaryValues.measureArrayShowCenter.row = (temporaryValues.measureRowLength-1)/2;
  }
  else{
    //对于探测器点数长和宽都为偶数的情况下，让每一个探测器都处于整数位置，
    //就是说，对于中测40×40的情况，让探测器坐标为-20到19中的每一个整数位置，而让坐标原点位于(0.5,0.5)的位置，这样方便
    //作图和数据处理，因为让探测器位于整数位置刚好对应于数组的位置；其实这只是图像上的处理，只是相对位置，其实这样设置也可以看做
    //坐标原点位于(0 ,0)，各个探测器位于从-19.5到19.5中每个半整数位置；这只是图像显示上的便捷处理，不影响数据计算和处理
    //选择原点为数组上的19(从0开始)
    temporaryValues.measureArrayShowCenter.row = temporaryValues.measureRowLength/2 - 1;
  }

  if(temporaryValues.measureColLength%2==1){
    temporaryValues.measureArrayShowCenter.col = (temporaryValues.measureColLength-1)/2;
  }
  else{
    temporaryValues.measureArrayShowCenter.col = temporaryValues.measureColLength/2 - 1;
  }
  */
  temporaryValues.measureArrayShowCenter.row = temporaryValues.measureRowLength/2;
  temporaryValues.measureArrayShowCenter.col = temporaryValues.measureColLength/2;

  temporaryValues.measureXGridLineNum = temporaryValues.measureRowLength;
  temporaryValues.measureYGridLineNum = temporaryValues.measureColLength;


  agridlinex.Length = temporaryValues.measureXGridLineNum;
  agridliney.Length = temporaryValues.measureYGridLineNum;

  for(int i=0;i<temporaryValues.measureXGridLineNum;i++){
    agridlinex[i] = new TPoint3DSeries(this);
    agridlinex[i]->ParentChart = ChartMeasure;
    agridlinex[i]->Pointer->Visible = false;
    agridlinex[i]->LinePen->Color = clWhite;
    agridlinex[i]->Clear();
    agridlinex[i]->Visible = true;
  }

  for(int j=0;j<temporaryValues.measureXGridLineNum;j++){
    agridliney[j] = new TPoint3DSeries(this);
    agridliney[j]->ParentChart = ChartMeasure;
    agridliney[j]->Pointer->Visible = false;
    agridliney[j]->LinePen->Color = clWhite;
    agridliney[j]->Clear();
    agridliney[j]->Visible = true;
  }

  for(int j=0;j<temporaryValues.measureColLength;j++){
    for(int i=0;i<temporaryValues.measureRowLength;i++){
      SeriesA->AddXYZ(i-temporaryValues.measureArrayShowCenter.row,
                      temporaryValues.NormMeasureDoseData.at(i,j,0),
                      j-temporaryValues.measureArrayShowCenter.col);

      SeriesASolid->AddXYZ(i-temporaryValues.measureArrayShowCenter.row,
                           temporaryValues.NormMeasureDoseData.at(i,j,0),
                           j-temporaryValues.measureArrayShowCenter.col);

    }
  }

  //The x-direction grid lines
  for(int j=0;j<temporaryValues.measureColLength;j++){
    for(int i=0;i<temporaryValues.measureRowLength;i++){
      agridlinex[j]->AddXYZ(i-temporaryValues.measureArrayShowCenter.row,
                            temporaryValues.NormMeasureDoseData.at(i,j,0),
                            j-temporaryValues.measureArrayShowCenter.col,"",clWhite);

    }
  }

  //The y-direction grid lines
  for(int i=0;i<temporaryValues.measureRowLength;i++){
    for(int j=0;j<temporaryValues.measureColLength;j++){
      agridliney[i]->AddXYZ(i-temporaryValues.measureArrayShowCenter.row,
                            temporaryValues.NormMeasureDoseData.at(i,j,0),
                            j-temporaryValues.measureArrayShowCenter.col,"",clWhite);
    }
  }

  doseCentralPosX = temporaryValues.measureDoseCentral.x/temporaryValues.gridSize[0];
  doseCentralPosY = temporaryValues.measureDoseCentral.y/temporaryValues.gridSize[1];
  
  for(int i=0;i<temporaryValues.measureRowLength;i++){
    tempValue = getDoseDataInAPosition(temporaryValues.NormMeasureDoseData,
                                       i,
                                       doseCentralPosY,
                                       0,
                                       INTEPOLATION_ALGORITHM(LINER),
                                       HANDLE_MODEL(ADAC)
                                       );
    SeriesAx->AddXYZ(i-temporaryValues.measureArrayShowCenter.row,
                     tempValue,
                     doseCentralPosY -temporaryValues.measureArrayShowCenter.col,
                     "",
                     clBlack);
  }

  for(int j=0;j<temporaryValues.measureColLength;j++){
    tempValue = getDoseDataInAPosition(temporaryValues.NormMeasureDoseData,
                                       doseCentralPosX,
                                       j,
                                       0,
                                       INTEPOLATION_ALGORITHM(LINER),
                                       HANDLE_MODEL(ADAC)
                                       );
    SeriesAy->AddXYZ(doseCentralPosX-temporaryValues.measureArrayShowCenter.row,
                     tempValue,
                     j -temporaryValues.measureArrayShowCenter.col,
                     "",
                     clBlack);
  }

  ChartMeasure->Enabled = true;

  ShowMeasurePath(temporaryValues.measureFilePath);



  globalMem = NULL;
  displayPairDose = NULL;
  measureDisplayDose = NULL;
  normMeasureDisplayDose = NULL;

  doseMatrix = NULL;
  dosePtr = NULL;

  /*Show base Info*/
  ShowBaseInfo();

  /*Show measure Hot Point Graphy*/
  RefreshMeasureHotPointDose();
  ShowMeasureHotPointGraphy();


  return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RzToolButtonRotationClick(TObject *Sender)
{
  //
  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;

  if(20==RzToolButtonRotation->ImageIndex) //Arrow Up
  {
    RzToolButtonRotation->ImageIndex = 22;
  }else if(22==RzToolButtonRotation->ImageIndex)  //Arrow Right
  {
    RzToolButtonRotation->ImageIndex = 24;
  }else if(24==RzToolButtonRotation->ImageIndex)  //Arrow Down
  {
    RzToolButtonRotation->ImageIndex = 18;
  }
  else if(18==RzToolButtonRotation->ImageIndex)  //Arrow Left
  {
    RzToolButtonRotation->ImageIndex = 20;
  }
  else{
    RzToolButtonRotation->ImageIndex = 20;
  }

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  gatePairDose = globalMem->getGatePairDose();
  if(NULL == gatePairDose){
    return;
  }

  if(false == this->temporaryValues.measureFilePath.empty()){
    gatePairDose->Notify(Message_Notify(Update_rotation));
    RefreshMeasureDoseGraphicFromDisplayValue();
  }

  if(false == this->temporaryValues.calcFilePath.empty()){
    RefreshCalculateDoseGraphicFromDisplayValue();
  }

  globalMem = NULL;
  gatePairDose = NULL;

}

//---------------------------------------------------------------------------
void __fastcall TFormMain::LeftToRightExcahngeClick(TObject *Sender)
{

  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  gatePairDose = globalMem->getGatePairDose();
  if(NULL == gatePairDose){
    return;
  }

  if(false == this->temporaryValues.measureFilePath.empty()){
    gatePairDose->Notify(Message_Notify(Update_leftToRightChange));
    RefreshMeasureDoseGraphicFromDisplayValue();
  }

  if(false == this->temporaryValues.calcFilePath.empty()){
    RefreshCalculateDoseGraphicFromDisplayValue();
  }

  globalMem = NULL;
  gatePairDose = NULL;
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::TopToButtomExcahngeClick(TObject *Sender)
{
  //
  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  gatePairDose = globalMem->getGatePairDose();
  if(NULL == gatePairDose){
    return;
  }

  if(false == this->temporaryValues.measureFilePath.empty()){
    gatePairDose->Notify(Message_Notify(Update_topToBottomChange));
    RefreshMeasureDoseGraphicFromDisplayValue();
  }

  if(false == this->temporaryValues.calcFilePath.empty()){
    RefreshCalculateDoseGraphicFromDisplayValue();
  }

  globalMem = NULL;
  gatePairDose = NULL;      
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::RzToolButtonCAXClick(TObject *Sender)
{
  if(!this->temporaryValues.measureFilePath.empty()){
    TFormCAX* formCAXSetting = new TFormCAX(this);
    formCAXSetting->RzBitBtnOK->OnClick = formCAXSetting->SetCAXAandFlushFromMemory;
    formCAXSetting->Parent = this;
    formCAXSetting->FormStyle = fsStayOnTop;
    formCAXSetting->Show();
  }

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RzButtomCompare_AbsClick(TObject *Sender)
{
  string errStr;
  GlobalMembers *globalMem = NULL;
  DoseCheck* doseCheck = NULL;

  int totalCompared,passedCount;
  double passedPercent;
  PhysicalPoint measureNormPos,calcNormPos;

  if(DoseType(DOSE_RELATIVE) == temporaryValues.doseType){
    MessageBox(this->Handle,"The relative dose can not be applied to absolute compare.","Warning!",MB_OK);
    return;
  }
  
  if(CheckBoxDTA_Abs->Checked==false&&CheckBoxDD_Abs->Checked==false&&CheckBoxGamma_Abs->Checked==false)
  {
    MessageBox(this->Handle,"请选择至少一项进行比较","Warning!",MB_OK);
    return;
  }
  
  if(this->temporaryValues.measureFilePath.empty()||
     this->temporaryValues.calcFilePath.empty())
  {
    errStr = "验证之前必须先读入";
    errStr.append(this->temporaryValues.measureFilePath.empty()?"测量数据":"计划数据");
    MessageBox(this->Handle,errStr.c_str(),"Warning!",MB_OK);
    return;
  }

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  doseCheck = globalMem->getDoseCheck();


  if(NULL == doseCheck){
    RunningLog::writeLog("The doseCheck is NULL;",__LINE__);
    return;
  }

  TreeResult->Items->Clear();
  TreeResult->Items->Add(TreeResult->GetNodeAt(0,0),"Check Result");
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\"),"Dose Difference");
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\"),"DTA");
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\"),"Gamma");

  if(true == CheckBoxDD_Abs->Checked)   //DD
  {
    doseCheck->check(CHECKTYPE(ABS_DD));

    *this->temporaryValues.checkedRecord.getSingleDDResult() = *doseCheck->getCheckedRecord()->getSingleDDResult();
    totalCompared = this->temporaryValues.checkedRecord.getSingleDDResult()->totalComparedCount;
    measureNormPos = this->temporaryValues.checkedRecord.getSingleDDResult()->normPosition_measure;
    calcNormPos = this->temporaryValues.checkedRecord.getSingleDDResult()->normPosition_calculate;


    TFormDDStatics *formDDStatics = new TFormDDStatics(this);
    formDDStatics->Parent = this;
    formDDStatics->FormStyle = fsStayOnTop;
    formDDStatics->Show();
  }

  
  if(true==CheckBoxDTA_Abs->Checked){    //DTA
     TFormDTAWayChoose* formDTAWayChoose = new TFormDTAWayChoose(this,true);
     formDTAWayChoose->Parent = this;
     formDTAWayChoose->FormStyle = fsStayOnTop;
     formDTAWayChoose->Show();
  }

  if(true==CheckBoxGamma_Abs->Checked){
    doseCheck->check(CHECKTYPE(ABS_GAMMA));

    *this->temporaryValues.checkedRecord.getSingleGammaResult() = *doseCheck->getCheckedRecord()->getSingleGammaResult();

    this->showGammaResult();
    
    this->temporaryValues.checkedRecord.setCheckedStatus(true);
    this->temporaryValues.checkedRecord.setCheckType(doseCheck->getCheckedRecord()->getCheckType());
  }


  globalMem = NULL;
  doseCheck = NULL;

  RzButtomCompare_Abs->Enabled = false;
  RzButtomCompare_Abs->Enabled = true;

  GroupBoxCompare->Enabled = false;
  GroupBoxCompare->Enabled = true;

  FormMain->KeyPreview = true;
  FormMain->SetFocus();
  
  Application->OnMessage = Proc;

}

//------------------------------------------------------------------------
void __fastcall TFormMain::RzButtomCompare_RelClick(TObject *Sender)
{
  string errStr;
  GlobalMembers *globalMem = NULL;
  DoseCheck* doseCheck = NULL;

  if(CheckBoxDTA_Rel->Checked==false&&CheckBoxGamma_Rel->Checked==false)
  {
    MessageBox(this->Handle,"请选择至少一项进行比较","Warning!",MB_OK);
    return;
  }
  
  if(this->temporaryValues.measureFilePath.empty()||
     this->temporaryValues.calcFilePath.empty())
  {
    errStr = "验证之前必须先读入";
    errStr.append(this->temporaryValues.measureFilePath.empty()?"测量数据":"计划数据");
    MessageBox(this->Handle,errStr.c_str(),"Warning!",MB_OK);
    return;
  }

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  doseCheck = globalMem->getDoseCheck();


  if(NULL == doseCheck){
    RunningLog::writeLog("The doseCheck is NULL;",__LINE__);
    return;
  }


  TreeResult->Items->Clear();
  TreeResult->Items->Add(TreeResult->GetNodeAt(0,0),"Check Result");
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\"),"DTA");
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\"),"Gamma");

  
  if(true==CheckBoxDTA_Rel->Checked){    //DTA
     TFormDTAWayChoose* formDTAWayChoose = new TFormDTAWayChoose(this,false);
     formDTAWayChoose->Parent = this;
     formDTAWayChoose->FormStyle = fsStayOnTop;
     formDTAWayChoose->Show();
  }

  if(true==CheckBoxGamma_Rel->Checked){
    doseCheck->check(CHECKTYPE(REL_GAMMA));

    *this->temporaryValues.checkedRecord.getSingleGammaResult() = *doseCheck->getCheckedRecord()->getSingleGammaResult();

    showGammaResult();

    this->temporaryValues.checkedRecord.setCheckedStatus(true);
    this->temporaryValues.checkedRecord.setCheckType(doseCheck->getCheckedRecord()->getCheckType());

  }


  globalMem = NULL;
  doseCheck = NULL;

  RzButtomCompare_Abs->Enabled = false;
  RzButtomCompare_Abs->Enabled = true;

  GroupBoxCompare->Enabled = false;
  GroupBoxCompare->Enabled = true;


  FormMain->KeyPreview = true;
  FormMain->SetFocus();
  
  Application->OnMessage = Proc;
     
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::showGammaResult(){

  int totalCompared,passedCount;
  double passedPercent;
  PhysicalPoint measureNormPos,calcNormPos;

  totalCompared = this->temporaryValues.checkedRecord.getSingleGammaResult()->totalComparedCount;
  passedCount = this->temporaryValues.checkedRecord.getSingleGammaResult()->passedCount;
  passedPercent = this->temporaryValues.checkedRecord.getSingleGammaResult()->totalPassPercent;
  
  measureNormPos = this->temporaryValues.checkedRecord.getSingleGammaResult()->normPosition_measure;
  calcNormPos = this->temporaryValues.checkedRecord.getSingleGammaResult()->normPosition_calculate;

  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Gamma"),"Total: " + AnsiString(totalCompared));
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Gamma"),"Pass: " + AnsiString(passedCount));
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Gamma"),"PassPercent: " + FormatFloat("0.00",passedPercent) + "%");


  if(false == this->temporaryValues.checkedRecord.getSingleGammaResult()->manualSelectMeasureNormValue){
    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Gamma"),
          "Measure Normlization PhysicalPosition:(" + FormatFloat("0.00",convertPositionToActualPosition(measureNormPos,this->temporaryValues.measureDoseCentral).x )
          + "mm," +  FormatFloat("0.00",convertPositionToActualPosition(measureNormPos,this->temporaryValues.measureDoseCentral).y) + "mm)");

    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Gamma"),
          "Measure Normlization GridPoint:(" + IntToStr(convertFromPhyPosToGridPoint(measureNormPos.x,this->temporaryValues.measureFirstAlignmentCenter.row,this->temporaryValues.gridSize[0]) ) +
          "," + IntToStr(convertFromPhyPosToGridPoint(measureNormPos.y,this->temporaryValues.measureFirstAlignmentCenter.col,this->temporaryValues.gridSize[1]) ) + ")" );
  }else{
    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Gamma"),
          AnsiString("Measure Normlization Value: ") + this->temporaryValues.checkedRecord.getSingleGammaResult()->normValue_measure.c_str() );
  }

  if(false == this->temporaryValues.checkedRecord.getSingleGammaResult()->manualSelectCalculateNormValue){
    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Gamma"),
          "Calculate Normlization PhysicalPosition:(" + FormatFloat("0.00",convertPositionToActualPosition(calcNormPos,this->temporaryValues.calcDoseCentral).x)
          + "mm," +  FormatFloat("0.00",convertPositionToActualPosition(calcNormPos,this->temporaryValues.calcDoseCentral).y) + "mm)");

    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Gamma"),
          "Calculate Normlization GridPoint:(" + IntToStr(convertFromPhyPosToGridPoint(calcNormPos.x,this->temporaryValues.calcFirstAlignmentCenter.row,this->temporaryValues.gridSize[0]/this->temporaryValues.segments[0]) ) +
          "," + IntToStr(convertFromPhyPosToGridPoint(calcNormPos.y,this->temporaryValues.calcFirstAlignmentCenter.col,this->temporaryValues.gridSize[1]/this->temporaryValues.segments[1]) ) + ")"  );
  }else{
    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Gamma"),
          AnsiString("Calculate Normlization Value: ") + this->temporaryValues.checkedRecord.getSingleGammaResult()->normValue_calculate.c_str() );
  }

  TreeResult->FullExpand();

  showNormPos(measureNormPos,calcNormPos);
}

void __fastcall TFormMain::showDTAResult(){
  int totalCompared,passedCount;
  double passedPercent;
  PhysicalPoint measureNormPos,calcNormPos;

  totalCompared = this->temporaryValues.checkedRecord.getSingleDTAResult()->totalComparedCount;
  passedCount = this->temporaryValues.checkedRecord.getSingleDTAResult()->passedCount;
  passedPercent = this->temporaryValues.checkedRecord.getSingleDTAResult()->totalPassPercent;
  measureNormPos = this->temporaryValues.checkedRecord.getSingleDTAResult()->normPosition_measure;
  calcNormPos = this->temporaryValues.checkedRecord.getSingleDTAResult()->normPosition_calculate;

  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\DTA"),"Total: " + AnsiString(totalCompared));
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\DTA"),"Pass: " + AnsiString(passedCount));
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\DTA"),"PassPercent: " + FormatFloat("0.00",passedPercent) + "%");


  if(false == this->temporaryValues.checkedRecord.getSingleDTAResult()->manualSelectMeasureNormValue){
    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\DTA"),
          "Measure Normlization PhysicalPosition:(" + FormatFloat("0.00",convertPositionToActualPosition(measureNormPos,this->temporaryValues.measureDoseCentral).x )
          + "mm," +  FormatFloat("0.00",convertPositionToActualPosition(measureNormPos,this->temporaryValues.measureDoseCentral).y) + "mm)");

    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\DTA"),
          "Measure Normlization GridPoint:(" + IntToStr(convertFromPhyPosToGridPoint(measureNormPos.x,this->temporaryValues.measureFirstAlignmentCenter.row,this->temporaryValues.gridSize[0]) ) +
          "," + IntToStr(convertFromPhyPosToGridPoint(measureNormPos.y,this->temporaryValues.measureFirstAlignmentCenter.col,this->temporaryValues.gridSize[1]) ) + ")" );
  }else{
    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\DTA"),
          AnsiString("Measure Normlization Value: ") + this->temporaryValues.checkedRecord.getSingleDTAResult()->normValue_measure.c_str() );
  }

  if(false == this->temporaryValues.checkedRecord.getSingleDTAResult()->manualSelectCalculateNormValue){
    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\DTA"),
          "Calculate Normlization PhysicalPosition:(" + FormatFloat("0.00",convertPositionToActualPosition(calcNormPos,this->temporaryValues.calcDoseCentral).x)
          + "mm," +  FormatFloat("0.00",convertPositionToActualPosition(calcNormPos,this->temporaryValues.calcDoseCentral).y) + "mm)");

    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\DTA"),
          "Calculate Normlization GridPoint:(" + IntToStr(convertFromPhyPosToGridPoint(calcNormPos.x,this->temporaryValues.calcFirstAlignmentCenter.row,this->temporaryValues.gridSize[0]/this->temporaryValues.segments[0]) ) +
          "," + IntToStr(convertFromPhyPosToGridPoint(calcNormPos.y,this->temporaryValues.calcFirstAlignmentCenter.col,this->temporaryValues.gridSize[1]/this->temporaryValues.segments[1]) ) + ")"  );
  }else{
    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\DTA"),
          AnsiString("Calculate Normlization Value: ") + this->temporaryValues.checkedRecord.getSingleDTAResult()->normValue_calculate.c_str() );
  }



  TreeResult->FullExpand();

  showNormPos(measureNormPos,calcNormPos);
}

void __fastcall TFormMain::showDDResult(){
   int totalCompared,passedCount;
  double passedPercent;
  PhysicalPoint measureNormPos,calcNormPos;


  totalCompared = this->temporaryValues.checkedRecord.getSingleDDResult()->totalComparedCount;
  passedCount = this->temporaryValues.checkedRecord.getSingleDDResult()->passedCount;
  passedPercent = this->temporaryValues.checkedRecord.getSingleDDResult()->totalPassPercent;
  measureNormPos = this->temporaryValues.checkedRecord.getSingleDDResult()->normPosition_measure;
  calcNormPos = this->temporaryValues.checkedRecord.getSingleDDResult()->normPosition_calculate;
      
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Dose Difference"),"Total: " + AnsiString(totalCompared));
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Dose Difference"),"Pass: " + AnsiString(passedCount));
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Dose Difference"),"PassPercent: " + FormatFloat("0.00",passedPercent) + "%");

  if(false == this->temporaryValues.checkedRecord.getSingleDDResult()->manualSelectMeasureNormValue){
    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Dose Difference"),
          "Measure Normlization PhysicalPosition:(" + FormatFloat("0.00",convertPositionToActualPosition(measureNormPos,this->temporaryValues.measureDoseCentral).x )
          + "mm," +  FormatFloat("0.00",convertPositionToActualPosition(measureNormPos,this->temporaryValues.measureDoseCentral).y) + "mm)");

    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Dose Difference"),
          "Measure Normlization GridPoint:(" + IntToStr(convertFromPhyPosToGridPoint(measureNormPos.x,this->temporaryValues.measureFirstAlignmentCenter.row,this->temporaryValues.gridSize[0]) ) +
          "," + IntToStr(convertFromPhyPosToGridPoint(measureNormPos.y,this->temporaryValues.measureFirstAlignmentCenter.col,this->temporaryValues.gridSize[1]) ) + ")" );
  }else{
    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Dose Difference"),
          AnsiString("Measure Normlization Value: ") + this->temporaryValues.checkedRecord.getSingleDDResult()->normValue_measure.c_str() );
  }

  if(false == this->temporaryValues.checkedRecord.getSingleDDResult()->manualSelectCalculateNormValue){
    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Dose Difference"),
          "Calculate Normlization PhysicalPosition:(" + FormatFloat("0.00",convertPositionToActualPosition(calcNormPos,this->temporaryValues.calcDoseCentral).x)
          + "mm," +  FormatFloat("0.00",convertPositionToActualPosition(calcNormPos,this->temporaryValues.calcDoseCentral).y) + "mm)");

    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Dose Difference"),
          "Calculate Normlization GridPoint:(" + IntToStr(convertFromPhyPosToGridPoint(calcNormPos.x,this->temporaryValues.calcFirstAlignmentCenter.row,this->temporaryValues.gridSize[0]/this->temporaryValues.segments[0]) ) +
          "," + IntToStr(convertFromPhyPosToGridPoint(calcNormPos.y,this->temporaryValues.calcFirstAlignmentCenter.col,this->temporaryValues.gridSize[1]/this->temporaryValues.segments[1]) ) + ")"  );
  }else{
    TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\Dose Difference"),
          AnsiString("Calculate Normlization Value: ") + this->temporaryValues.checkedRecord.getSingleDDResult()->normValue_calculate.c_str() );
  }
  
  TreeResult->FullExpand();

  showNormPos(measureNormPos,calcNormPos);
}

//----------------------------------------------------------------
void __fastcall TFormMain::ShowMeasurePath(string path){
  //Memo

  this->RzMemoMeasureFile->Clear();
  this->RzMemoMeasureFile->Lines->Add(path.c_str());

  //PathBar
  this->RzFilePathBarMeasure->Items->Clear();

  this->RzFilePathBarMeasure->Items->Add();
  this->RzFilePathBarMeasure->Items->Items[this->RzFilePathBarMeasure->Items->Count-1]->Caption ="Measure";

  this->RzFilePathBarMeasure->Separator = ">";
  char* pstr = NULL;
  const char *split = "\\";
  pstr = strtok(path.begin(),split);

  while(NULL != pstr){
    this->RzFilePathBarMeasure->Items->Add();
    this->RzFilePathBarMeasure->Items->Items[this->RzFilePathBarMeasure->Items->Count-1]->Caption =pstr;
    pstr = strtok(NULL,split);
  }
  pstr = NULL;
}

void __fastcall TFormMain::ShowCalcPath(string path){

  this->RzMemoCalculateFile->Clear();
  this->RzMemoCalculateFile->Lines->Add(path.c_str());

  //PathBar
  this->RzPathBarCalc->Items->Clear();

  this->RzPathBarCalc->Items->Add();
  this->RzPathBarCalc->Items->Items[this->RzPathBarCalc->Items->Count-1]->Caption ="Calculation";

  this->RzPathBarCalc->Separator = ">";
  char* pstr = NULL;
  const char *split = "\\";
  pstr = strtok(path.begin(),split);

  while(NULL != pstr){
    this->RzPathBarCalc->Items->Add();
    this->RzPathBarCalc->Items->Items[this->RzPathBarCalc->Items->Count-1]->Caption =pstr;
    pstr = strtok(NULL,split);
  }
  pstr = NULL;
}


//--------------------------------------------------------------------------
void __fastcall TFormMain::ChartMeasureMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
   int templeft,templeftadd,temptop,temptopadd;
   double Xvalue = -100000,Yvalue = -100000;
   int thecenterXone,thecenterZone; //Chart中心对应网格/数组的哪一行
   double doseCentralPosY;
   float tempValue;
   float tempAbsDoseValue;
   
   if(false == temporaryValues.measureFilePath.empty())
   {
     if(true == temporaryValues.measureDimensionTransTag.status())   //只有2D情况下有鼠标取值的功能
     {
       TPoint pp;
       pp = ChartMeasure->GetCursorPos();

       //----------------------------
       int centerz;
       if(ChartMeasure->ClientHeight%2==1){
         centerz = (ChartMeasure->ClientHeight+1)/2;
       }else{
         centerz = (ChartMeasure->ClientHeight)/2;
       }

       doseCentralPosY = temporaryValues.measureDoseCentral.y/temporaryValues.gridSize[1];


       for(int j=SeriesA->MinXValue();j<=SeriesA->MaxXValue()-1;j++)
       {
         templeft = (SeriesA->CalcXPosValue(j) - ChartMeasure->Canvas->XCenter)*ChartMeasure->View3DOptions->Zoom/100.0 + ChartMeasure->Canvas->XCenter + 0.5;
         templeftadd = (SeriesA->CalcXPosValue(j+1) - ChartMeasure->Canvas->XCenter)*ChartMeasure->View3DOptions->Zoom/100.0 + ChartMeasure->Canvas->XCenter + 0.5;

         if(pp.x>=templeft&&pp.x<=templeftadd)
         {
           Xvalue = j  + (pp.x - templeft)/(double)(templeftadd - templeft);
           break;
         }
       }


       for(int i=SeriesA->MinZValue();i<=SeriesA->MaxZValue()-1;i++)
       {
         temptop =  (-ChartMeasure->DepthAxis->CalcPosValue(doseCentralPosY -temporaryValues.measureArrayShowCenter.col)+ChartMeasure->DepthAxis->CalcPosValue(-i))*ChartMeasure->View3DOptions->Zoom/100.0 +centerz + 0.5;
         temptopadd =  (-ChartMeasure->DepthAxis->CalcPosValue(doseCentralPosY -temporaryValues.measureArrayShowCenter.col)+ ChartMeasure->DepthAxis->CalcPosValue(-i-1) )*ChartMeasure->View3DOptions->Zoom/100.0 +centerz + 0.5;

         if(pp.y>=temptopadd&&pp.y<=temptop)
         {
           Yvalue = i  + (temptop - pp.y)/(double)(temptop - temptopadd);
           break;
         }
       }

       tempValue =  GettheValueByCoordinate(Xvalue,Yvalue,temporaryValues.measureFileType,&temporaryValues.NormMeasureDoseData);
       tempAbsDoseValue =  GettheValueByCoordinate(Xvalue,Yvalue,temporaryValues.measureFileType,&temporaryValues.measureDoseData);
       MemoDynamicInfo->Clear();

       if(Xvalue>=SeriesA->MinXValue() && Xvalue<=SeriesA->MaxXValue() && Yvalue>=SeriesA->MinZValue() && Yvalue<=SeriesA->MaxZValue()){
         MemoDynamicInfo->Lines->Add("DoseValue(%): " + FormatFloat("0.00",tempValue));
         MemoDynamicInfo->Lines->Add("");
         MemoDynamicInfo->Lines->Add("Absoulate Dose: " + FormatFloat("0.00",tempAbsDoseValue));
       }else{
         MemoDynamicInfo->Lines->Add("DoseValue(%): " + AnsiString("NAN"));
         MemoDynamicInfo->Lines->Add("");
         MemoDynamicInfo->Lines->Add("Absoulate Dose: " + AnsiString("NAN"));
       }

       if(Xvalue>=SeriesA->MinXValue() && Xvalue<=SeriesA->MaxXValue()){
         StatusBar1->Panels->Items[0]->Text = "X:" + FormatFloat("0.00",Xvalue*temporaryValues.gridSize[0]/10.0) + " (cm)";
       }else{
         StatusBar1->Panels->Items[0]->Text = "X: Out of Boundary";
       }

       if(Yvalue>=SeriesA->MinZValue() && Yvalue<=SeriesA->MaxZValue()){
         StatusBar1->Panels->Items[1]->Text = "Y:" + FormatFloat("0.00",Yvalue*temporaryValues.gridSize[1]/10.0) + " (cm)";
       }else{
         StatusBar1->Panels->Items[1]->Text = "Y: Out of Boundary";
       }
       StatusBar1->Panels->Items[2]->Text = "x:" + AnsiString(pp.x) + " (pixel)";
       StatusBar1->Panels->Items[3]->Text = "y:" + AnsiString(pp.y) + " (pixel)";
       //-----------------------------


     }
   }
   
}

//-------------------------------------------------------------------------
bool __fastcall TFormMain::caxSetting(FILETYPE fileType){
  TFormCAX* formCAXSetting = new TFormCAX(this,fileType);
  formCAXSetting->RzBitBtnOK->OnClick = formCAXSetting->SetCAXAandShowFirst;
  formCAXSetting->Parent = this;
  formCAXSetting->FormStyle = fsStayOnTop;
  formCAXSetting->Show();
}
//---------------------------------------------------------------------------
/*Set detectors Array*/
bool __fastcall TFormMain::SetDetectorsArray(MatrixData<bool>& dectorArray,FILETYPE fileType){
  bool result = false;
  int i,j,k;

  dectorArray.reset();
  switch(fileType){

    case FILETYPE(ZCMeasureFileType): //zhongCe 40*40
    {
      dectorArray.allocate(40,40,1);
      for(int k=0;k<1;k++){
        for(int j=0;j<40;j++){
          for(int i=0;i<40;i++){
            dectorArray.modifyValue(i,j,k,true);
          }

        }
      }
      result = true;
    }
    break;

    case FILETYPE(MapCHECKMeasureFileType): //MapCheck
    {
      dectorArray.allocate(45,45,1);
      //Default are 0
      for(k=0;k<1;k++){
        for(j=0;j<45;j++){
          for(i=0;i<45;i++){
            dectorArray.modifyValue(i,j,k,false);
          }
        }

        for(j=12;j<33;j=j+2){
          for(i=12;i<33;i=i+2){
            dectorArray.modifyValue(i,j,k,true);
          }
        }

        for(j=13;j<32;j=j+2){
          for(i=13;i<32;i=i+2){
            dectorArray.modifyValue(i,j,k,true);
          }
        }

        for(i=0;i<45;i=i+2){
          j = 22;
          dectorArray.modifyValue(i,j,k,true);
        }

        for(j=0;j<45;j=j+2){
          i = 22;
          dectorArray.modifyValue(i,j,k,true);
        }

        for(j=4;j<41;j++){
          i = j;
          dectorArray.modifyValue(i,j,k,true);

          i = 44 - j;
          dectorArray.modifyValue(i,j,k,true);
        }

        for(i=10;i<35;i=i+4){
          for(j=0;j<45;j=j+4){
            dectorArray.modifyValue(i,j,k,true);
          }
        }

        for(i=8;i<37;i=i+4){
          for(j=2;j<43;j=j+4){
            dectorArray.modifyValue(i,j,k,true);
          }
        }

        for(j=10;j<35;j=j+4){
          i = 0;
          dectorArray.modifyValue(i,j,k,true);
        }

        for(j=10;j<35;j=j+4){
          i = 44;
          dectorArray.modifyValue(i,j,k,true);
        }

        for(j=8;j<37;j=j+4){
          i = 2;
          dectorArray.modifyValue(i,j,k,true);
        }

        for(j=8;j<37;j=j+4){
          i = 42;
          dectorArray.modifyValue(i,j,k,true);
        }

        for(j=6;j<39;j=j+4){
          i = 4;
          dectorArray.modifyValue(i,j,k,true);
        }

        for(j=6;j<39;j=j+4){
          i = 40;
          dectorArray.modifyValue(i,j,k,true);
        }

        for(j=4;j<41;j=j+4){
          i = 6;
          dectorArray.modifyValue(i,j,k,true);
        }

        for(j=4;j<41;j=j+4){
          i = 38;
          dectorArray.modifyValue(i,j,k,true);
        }

      }
      result = true;
    }
    break;

    case FILETYPE(MatrixMeasureFileType):
    {
      dectorArray.allocate(temporaryValues.measureRowLength,temporaryValues.measureColLength,1);
      for(int k=0;k<1;k++){
        for(int j=0;j<temporaryValues.measureColLength;j++){
          for(int i=0;i<temporaryValues.measureRowLength;i++){
            dectorArray.modifyValue(i,j,k,true);
          }

        }
      }

      //four boundary point set to invalid---Iba-Matrix
      dectorArray.modifyValue(0,0,0,false);
      dectorArray.modifyValue(temporaryValues.measureRowLength-1,0,0,false);
      dectorArray.modifyValue(0,temporaryValues.measureColLength-1,0,false);
      dectorArray.modifyValue(temporaryValues.measureRowLength-1,temporaryValues.measureColLength-1,0,false);
      result = true;
      
    }
    break;

    default:
    {
      RunningLog::writeLog("The detector type is unknown",__LINE__);
      result = false;
    }
    break;
  }

  return result;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ChartCalculateMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{

   int templeft,templeftadd,temptop,temptopadd;
   double Xvalue,Yvalue;
   int thecenterXone,thecenterZone; //Chart中心对应网格/数组的哪一行
   if(false == temporaryValues.calcFilePath.empty())
   {
     if(true == temporaryValues.calcDimensionTransTag.status())   //只有2D情况下有鼠标取值的功能
     {
       TPoint pp;
       pp = ChartCalculate->GetCursorPos();


       //----------------------------
       int centerz;
       if(ChartCalculate->ClientHeight%2==1){
         centerz = (ChartCalculate->ClientHeight+1)/2;
       }else{
         centerz = (ChartCalculate->ClientHeight)/2;
       }


       //在DICOM数据中依然以segment之后的小网格(1mm或1.2mm)作为鼠标响应时的插值数据框架
       //而不是以GUI上显示的segment外部的大网格(5mm或7.2mm)为框架
       //因为TeeChart在作图时总是让图显示成按照Chart的中心位置对称，所以需要确定
       //Chart的中心对应于网格（数组）上的哪一行/列，从而让该行的位置和centerz/Chart->Canvas->XCenter
       //对应，从而可以以该行/列为基准，确定图上的每点坐标和该点对应网格(数组)上的坐标位置
       //thecenterXone = (bcutxbian[0] + bcutxbian[1])/2 - bicenter;
       //由于对于X的处理和下面所述的对Z的处理不一样，其并没有认为j=0对应于Chart的中心(Chart2->Canvas->XCenter)(但是Z方向无法使用Chart2->Canvas->ZCenter)
       //而是实事求是的给出了每个网格坐标所对应的像素值，所以并不需要thecenterXone修正，但是
       //，Z方向的处理则需要thecenterZone来处理

       for(int j=SeriesB->MinXValue();j<=SeriesB->MaxXValue()-1;j++)
       {
         templeft = (SeriesB->CalcXPosValue(j) - ChartCalculate->Canvas->XCenter)*ChartCalculate->View3DOptions->Zoom/100.0 + ChartCalculate->Canvas->XCenter + 0.5;
         templeftadd = (SeriesB->CalcXPosValue(j+1) - ChartCalculate->Canvas->XCenter)*ChartCalculate->View3DOptions->Zoom/100.0 + ChartCalculate->Canvas->XCenter + 0.5;

         if(pp.x>=templeft&&pp.x<=templeftadd)
         {
           Xvalue = j  + (pp.x - templeft)/(double)(templeftadd - templeft);
           break;
         }
       }


       //因为TeeChart在作图时总是让图显示成按照Chart的中心位置对称，所以需要确定
       //Chart的中心对应于网格（数组）上的哪一行/列，从而让该行的位置和centerz/Chart->Canvas->XCenter
       //对应，从而可以以该行/列为基准，确定图上的每点坐标和该点对应网格(数组)上的坐标位置

       thecenterZone = (temporaryValues.cutBian.at(1,0,0) + temporaryValues.cutBian.at(1,1,0))/2.0 - temporaryValues.calcFirstAlignmentCenter.col;
       //之所以加上thecenterZone，是因为使用如下方法判断每个位置对应的坐标值时，我们认为
       //(-Chart2->DepthAxis->CalcPosValue(thecenterZone)+Chart2->DepthAxis->CalcPosValue(-i))*Chart2->View3DOptions->Zoom/100.0 +centerz + 0.5;来
       //正确的获取坐标为i的网格线在Chart中的位置，但事实并非如此，如上所述，由于i=0不一定是Chart的中心(centerz处)，也就是说i=0时的position不一定在centerz处
       //所以必须要加上thecenterZone来确定centerz所对应的网格坐标
       for(int i=SeriesB->MinZValue();i<=SeriesB->MaxZValue()-1;i++)
       {
         temptop =  (-ChartCalculate->DepthAxis->CalcPosValue(-thecenterZone)+ChartCalculate->DepthAxis->CalcPosValue(-i))*ChartCalculate->View3DOptions->Zoom/100.0 +centerz + 0.5;
         temptopadd =  (-ChartCalculate->DepthAxis->CalcPosValue(-thecenterZone)+ ChartCalculate->DepthAxis->CalcPosValue(-i-1) )*ChartCalculate->View3DOptions->Zoom/100.0 +centerz + 0.5;

         if(pp.y>=temptopadd&&pp.y<=temptop)
         {
           Yvalue = i  + (temptop - pp.y)/(double)(temptop - temptopadd);
           break;
         }

       }
       float tempValue =  GettheValueByCoordinate(Xvalue,Yvalue,FILETYPE(DICOMCalcFileType),&temporaryValues.NormCalcDoseData);
       float tempAbsDoseValue =  GettheValueByCoordinate(Xvalue,Yvalue,FILETYPE(DICOMCalcFileType),&temporaryValues.calcDoseData);
       MemoDynamicInfo->Clear();

       if(Xvalue>=SeriesB->MinXValue() && Xvalue<=SeriesB->MaxXValue() && Yvalue>=SeriesB->MinZValue() && Yvalue<=SeriesB->MaxZValue()){
         MemoDynamicInfo->Lines->Add("DoseValue(%): " + FormatFloat("0.00",tempValue));
         MemoDynamicInfo->Lines->Add("");
         MemoDynamicInfo->Lines->Add("Absoulate Dose: " + FormatFloat("0.00",tempAbsDoseValue));
       }else{
         MemoDynamicInfo->Lines->Add("DoseValue(%): " + AnsiString("NAN"));
         MemoDynamicInfo->Lines->Add("");
         MemoDynamicInfo->Lines->Add("Absoulate Dose: " + AnsiString("NAN"));
       }

       if(Xvalue>=SeriesB->MinXValue() && Xvalue<=SeriesB->MaxXValue()){
         StatusBar1->Panels->Items[0]->Text = "X:" + FormatFloat("0.00",Xvalue*(temporaryValues.gridSize[0]/temporaryValues.segments[0])/10.0) + " (cm)";
       }else{
         StatusBar1->Panels->Items[0]->Text = "X: Out of Boundary";
       }

       if(Yvalue>=SeriesB->MinZValue() && Yvalue<=SeriesB->MaxZValue()){
         StatusBar1->Panels->Items[1]->Text = "Y:" + FormatFloat("0.00",Yvalue*(temporaryValues.gridSize[1]/temporaryValues.segments[1])/10.0) + " (cm)";
       }else{
         StatusBar1->Panels->Items[1]->Text = "Y: Out of Boundary";
       }
       StatusBar1->Panels->Items[2]->Text = "x:" + AnsiString(pp.x) + " (pixel)";
       StatusBar1->Panels->Items[3]->Text = "y:" + AnsiString(pp.y) + " (pixel)";
     }
   }
  
}


//--------------------------按照位置取值--------------------------------------------
double __fastcall TFormMain::GettheValueByCoordinate(double XValue,double ZValue,FILETYPE filetype,MatrixData<double>* matrix)
{
  
  int leftX,rightX,topZ,bottomZ;
  double restoreXValue = XValue;
  double restoreZValue = ZValue;
  XValue = 0;
  ZValue = 0;

  int rowAjust,colAjust;
  double thevalue;
  switch(filetype)
  {
    case FILETYPE(ZCMeasureFileType):
    case FILETYPE(MapCHECKMeasureFileType):
    case FILETYPE(MatrixMeasureFileType):
    {
      if(NULL == matrix || matrix->isEmpty())
        return (-1);

      if(temporaryValues.measureRowLength%2==0){
        rowAjust = 0;
      }else{
        rowAjust = 1;
      }

      if(temporaryValues.measureColLength%2==0){
        colAjust = 0;
      }else{
        colAjust = 1;
      }

      if(restoreXValue<0)
         XValue = max<double>(restoreXValue,temporaryValues.measureArrayShowCenter.row + rowAjust -temporaryValues.measureRowLength);       //Boundary
      else
         XValue = min<double>(restoreXValue,temporaryValues.measureRowLength - 1 - temporaryValues.measureArrayShowCenter.row);

       if(restoreZValue<0)
         ZValue = max<double>(restoreZValue,temporaryValues.measureArrayShowCenter.col + colAjust -temporaryValues.measureColLength);
       else
         ZValue = min<double>(restoreZValue,temporaryValues.measureColLength - 1 - temporaryValues.measureArrayShowCenter.col);

       if(XValue>0)
       {
         leftX = min<double>(temporaryValues.measureRowLength - 1 - temporaryValues.measureArrayShowCenter.row - rowAjust,(int)XValue);
         rightX =min<double>((int)XValue + 1,temporaryValues.measureRowLength - 1 - temporaryValues.measureArrayShowCenter.row);
       }
       else
       {
         leftX = max<double>(temporaryValues.measureArrayShowCenter.row + rowAjust -temporaryValues.measureRowLength,(int)XValue - 1);
         rightX = max<double>((int)XValue,temporaryValues.measureArrayShowCenter.row + rowAjust -temporaryValues.measureRowLength);
       }

       if(ZValue>0)
       {
         bottomZ = min<double>(temporaryValues.measureColLength - 1 - temporaryValues.measureArrayShowCenter.col,(int)ZValue);
         topZ = min<double>((int)ZValue + 1,temporaryValues.measureColLength - 1 - temporaryValues.measureArrayShowCenter.col);
       }
       else
       {
         bottomZ = max<double>(temporaryValues.measureArrayShowCenter.col + colAjust - temporaryValues.measureColLength,(int)ZValue - 1);
         topZ = max<double>((int)ZValue,temporaryValues.measureArrayShowCenter.col + colAjust - temporaryValues.measureColLength);
       }

       thevalue = (topZ-ZValue)*(rightX-XValue)*matrix->at(leftX+temporaryValues.measureArrayShowCenter.row,temporaryValues.measureArrayShowCenter.col+bottomZ,0)
                  + (ZValue - bottomZ)*(rightX-XValue)*matrix->at(leftX+temporaryValues.measureArrayShowCenter.row,temporaryValues.measureArrayShowCenter.col+topZ,0)
                 + (topZ - ZValue)*(XValue - leftX)*matrix->at(rightX+temporaryValues.measureArrayShowCenter.row,temporaryValues.measureArrayShowCenter.col+bottomZ,0)
                 + (ZValue - bottomZ)*(XValue - leftX)*matrix->at(rightX+temporaryValues.measureArrayShowCenter.row,temporaryValues.measureArrayShowCenter.col+topZ,0);

       if(fabs(XValue-(int)XValue)<0.0001&&fabs(ZValue-(int)ZValue)<0.0001)
       {
        if(XValue>=0&&ZValue>=0)
        {
          thevalue = matrix->at((int)XValue+temporaryValues.measureArrayShowCenter.row,temporaryValues.measureArrayShowCenter.col+(int)ZValue,0);
        }
        else if(XValue>=0&&ZValue<0)
        {
          thevalue = matrix->at((int)XValue+temporaryValues.measureArrayShowCenter.row,temporaryValues.measureArrayShowCenter.col+(int)ZValue-1,0);
        }
        else if(XValue<0&&ZValue>=0)
        {
          thevalue = matrix->at((int)XValue+temporaryValues.measureArrayShowCenter.row-1,temporaryValues.measureArrayShowCenter.col+(int)ZValue,0);
        }
        else if(XValue<0&&ZValue<0)
        {
          thevalue = matrix->at((int)XValue+temporaryValues.measureArrayShowCenter.row-1,temporaryValues.measureArrayShowCenter.col+(int)ZValue-1,0);
        }

       }
      

    }
    break;
    
    case FILETYPE(DICOMCalcFileType):  //DICOM
    {
       if(NULL == matrix || matrix->isEmpty())
        return (-1);


       if(restoreXValue<0)
         XValue = max<double>(restoreXValue,temporaryValues.calcFirstAlignmentCenter.row-(temporaryValues.calcRowLength - 1 -1));       //Boundary
       else
         XValue = min<double>(restoreXValue,temporaryValues.calcRowLength - 1 -1-temporaryValues.calcFirstAlignmentCenter.row);

       if(restoreZValue<0)
         ZValue = max<double>(restoreZValue,temporaryValues.calcFirstAlignmentCenter.col-(temporaryValues.calcColLength - 1-1));
       else
         ZValue = min<double>(restoreZValue,temporaryValues.calcColLength - 1 -1-temporaryValues.calcFirstAlignmentCenter.col);


       if(XValue>0)
       {
         leftX = min<double>(temporaryValues.calcRowLength - 1 -1-temporaryValues.calcFirstAlignmentCenter.row,(int)XValue);
         rightX =min<double>((int)XValue + 1,temporaryValues.calcRowLength - 1-1-temporaryValues.calcFirstAlignmentCenter.row);
       }
       else
       {
         leftX = max<double>(temporaryValues.calcFirstAlignmentCenter.row-(restoreXValue,temporaryValues.calcRowLength - 1-1),(int)XValue - 1);
         rightX = max<double>((int)XValue,temporaryValues.calcFirstAlignmentCenter.row-(restoreXValue,temporaryValues.calcRowLength - 1-1));
       }
       
       if(ZValue>0)
       {
         bottomZ = min<double>(temporaryValues.calcColLength-1-temporaryValues.calcFirstAlignmentCenter.col,(int)ZValue);
         topZ =min<double>((int)ZValue + 1,temporaryValues.calcColLength-1-temporaryValues.calcFirstAlignmentCenter.col);
       }
       else
       {
         bottomZ = max<double>(temporaryValues.calcFirstAlignmentCenter.col-(temporaryValues.calcColLength-1),(int)ZValue - 1);
         topZ = max<double>((int)ZValue,temporaryValues.calcFirstAlignmentCenter.col-(temporaryValues.calcColLength-1));
       }
       thevalue = ((topZ-ZValue)*(rightX-XValue)*matrix->at(leftX+temporaryValues.calcFirstAlignmentCenter.row,temporaryValues.calcFirstAlignmentCenter.col+bottomZ,0)
                + (ZValue - bottomZ)*(rightX-XValue)*matrix->at(leftX+temporaryValues.calcFirstAlignmentCenter.row,temporaryValues.calcFirstAlignmentCenter.col+topZ,0)
                + (topZ - ZValue)*(XValue - leftX)*matrix->at(rightX+temporaryValues.calcFirstAlignmentCenter.row,temporaryValues.calcFirstAlignmentCenter.col+bottomZ,0)
                + (ZValue - bottomZ)*(XValue - leftX)*matrix->at(rightX+temporaryValues.calcFirstAlignmentCenter.row,temporaryValues.calcFirstAlignmentCenter.col+topZ,0));

       if(fabs(XValue-(int)XValue)<0.0001&&fabs(ZValue-(int)ZValue)<0.0001){
         if(XValue>=0&&ZValue>=0)
         {
           thevalue = matrix->at((int)XValue+temporaryValues.calcFirstAlignmentCenter.row,temporaryValues.calcFirstAlignmentCenter.col+(int)ZValue,0);
         }
         else if(XValue>=0&&ZValue<0)
         {
           thevalue = matrix->at((int)XValue+temporaryValues.calcFirstAlignmentCenter.row,temporaryValues.calcFirstAlignmentCenter.col+(int)ZValue-1,0);
         }
         else if(XValue<0&&ZValue>=0)
         {
           thevalue = matrix->at((int)XValue+temporaryValues.calcFirstAlignmentCenter.row-1,temporaryValues.calcFirstAlignmentCenter.col+(int)ZValue,0);
         }
         else if(XValue<0&&ZValue<0)
         {
           thevalue = matrix->at((int)XValue+temporaryValues.calcFirstAlignmentCenter.row-1,temporaryValues.calcFirstAlignmentCenter.col+(int)ZValue-1,0);
         }


       }

    }
    break;

    default:
      break;



  }

  return thevalue;
}


//---------------------------------------------------------------------------
void __fastcall TFormMain::StringGridMeasureDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
  int idx,width;
  AnsiString str;
  TRect rc;

  if(ACol==0||ARow==0) return;

  width=2;
  str=StringGridMeasure->Cells[ACol][ARow];
  if(true == temporaryValues.detectorArray.at(ACol-1,ARow-1,0))
  {
    //背景
    StringGridMeasure->Canvas->Brush->Color=(TColor)RGB(153,204,51);
    StringGridMeasure->Canvas->FillRect(Rect);


    //文本
    rc=Rect;
    rc.left+=width;
    rc.top+=width;
    rc.right-=width;
    rc.bottom-=width;
    StringGridMeasure->Canvas->Font->Color=clBlack;
    StringGridMeasure->Canvas->TextRect(rc,rc.left+width,rc.top+width,str);

    //边框
    StringGridMeasure->Canvas->Pen->Color=clGreen;
    StringGridMeasure->Canvas->Pen->Width=2;
    StringGridMeasure->Canvas->MoveTo(rc.left,rc.top);
    StringGridMeasure->Canvas->LineTo(rc.left,rc.bottom);
    StringGridMeasure->Canvas->LineTo(rc.right,rc.bottom);
    StringGridMeasure->Canvas->LineTo(rc.right,rc.top);
    StringGridMeasure->Canvas->LineTo(rc.left,rc.top);
  }

}


//---------------------------------------------------------------------------
void __fastcall TFormMain::ComboBoxDataChange(TObject *Sender)
{

  switch(ComboBoxData->ItemIndex)
  {
    case 0: //Normalize
    {
      if(false == temporaryValues.measureFilePath.empty() &&
         false == temporaryValues.NormMeasureDoseData.isEmpty()){
         
         for(int j=0;j<temporaryValues.measureColLength;j++){
           for(int i=0;i<temporaryValues.measureRowLength;i++){
             StringGridMeasure->Cells[i+1][j+1] = FormatFloat("0.0000",temporaryValues.NormMeasureDoseData.at(i,j,0));
           }
         }
      }

      if(false == temporaryValues.calcFilePath.empty() &&
         false == temporaryValues.NormCalcDoseData.isEmpty()){

         for(int j=temporaryValues.cutBian.at(1,0,0);j<=temporaryValues.cutBian.at(1,1,0);j++){
           for(int i=temporaryValues.cutBian.at(0,0,0);i<=temporaryValues.cutBian.at(0,1,0);i++){
             StringGridCalculate->Cells[i- temporaryValues.cutBian.at(0,0,0) + 1][j - temporaryValues.cutBian.at(1,0,0) + 1]
               = FormatFloat("0.0000",temporaryValues.NormCalcDoseData.at(i,j,0));
           }
         }
      }

    }
    break;
    case 1:  //AbsDose
    {
       if(false == temporaryValues.measureFilePath.empty() &&
         false == temporaryValues.measureDoseData.isEmpty()){

         for(int j=0;j<temporaryValues.measureColLength;j++){
           for(int i=0;i<temporaryValues.measureRowLength;i++){
             StringGridMeasure->Cells[i+1][j+1] = FormatFloat("0.0000",temporaryValues.measureDoseData.at(i,j,0));
           }
         }
      }

      if(false == temporaryValues.calcFilePath.empty() &&
        false == temporaryValues.calcDoseData.isEmpty()){

        for(int j=temporaryValues.cutBian.at(1,0,0);j<=temporaryValues.cutBian.at(1,1,0);j++){
           for(int i=temporaryValues.cutBian.at(0,0,0);i<=temporaryValues.cutBian.at(0,1,0);i++){
             StringGridCalculate->Cells[i- temporaryValues.cutBian.at(0,0,0) + 1][j - temporaryValues.cutBian.at(1,0,0) + 1]
               = FormatFloat("0.0000",temporaryValues.calcDoseData.at(i,j,0));
           }
         }
      }

    }
    break;

    default:
    break;
  }
  ComboBoxData->Enabled = false;
  ComboBoxData->Enabled = true;
}

//----------------------RefreshMeasureHotPointDose--------------------------
void __fastcall TFormMain::RefreshMeasureHotPointDose(){
  if(true == temporaryValues.measureFilePath.empty()
    ||  temporaryValues.NormMeasureDoseData.isEmpty()){
    return;
  }

  temporaryValues.measureHotPointData = temporaryValues.NormMeasureDoseData;
  GaussianSmoothingOrderThree(&temporaryValues.measureHotPointData);
  
}

void __fastcall TFormMain::ShowMeasureHotPointGraphy(){

  SeriesMeasureHotPoint->Clear();

  if(true == temporaryValues.measureFilePath.empty()
    || temporaryValues.measureHotPointData.isEmpty()){
    return;
  }
    SeriesMeasureHotPoint->Visible = true;
  //---------------------------Hot Point ---------------------------
  for(int j=0;j<temporaryValues.measureColLength;j++){
    for(int i=0;i<temporaryValues.measureRowLength;i++){
        SeriesMeasureHotPoint->AddXYZ(i-temporaryValues.measureArrayShowCenter.row,
                           temporaryValues.measureHotPointData.at(i,j,0),
                           j-temporaryValues.measureArrayShowCenter.col);

    }
  }

  this->ChartMeasureHotPoint->LeftAxis->StartPosition = 0;
  this->ChartMeasureHotPoint->LeftAxis->EndPosition = 0; //通过将所有点压缩到底面来实现向2D转化
  this->ChartMeasureHotPoint->View3DOptions->Rotation = 0; //通过将Chart旋转到一个固定角度，使网
  this->ChartMeasureHotPoint->View3DOptions->Elevation = 270;  //格和轴有2D效果
}

void __fastcall TFormMain::RefreshCalcHotPointDose(){
   if(true == temporaryValues.calcFilePath.empty()
    ||  temporaryValues.NormCalcDoseData.isEmpty()){
    return;
  }

  temporaryValues.calcHotPointData = temporaryValues.NormCalcDoseData;
  //GaussianSmoothingOrderThree(&temporaryValues.measureHotPointData);
}

void __fastcall TFormMain::ShowCalcHotPointGraphy(){


  if(true == temporaryValues.calcFilePath.empty()
    || temporaryValues.calcHotPointData.isEmpty()){
    return;
  }

  SeriesCalcHotPoint->Clear();

  ChartCalcHotPoint->BottomAxis->StartPosition = 50 - (temporaryValues.cutBian.at(0,1,0) - temporaryValues.cutBian.at(0,0,0))*50/(float)(temporaryValues.cutBian.at(1,1,0) - temporaryValues.cutBian.at(1,0,0));
  ChartCalcHotPoint->BottomAxis->EndPosition = 50 + (temporaryValues.cutBian.at(0,1,0) - temporaryValues.cutBian.at(0,0,0))*50/(float)(temporaryValues.cutBian.at(1,1,0) - temporaryValues.cutBian.at(1,0,0));



  
  SeriesCalcHotPoint->Visible = true;
  //---------------------------Hot Point ---------------------------
  for(int j=temporaryValues.cutBian.at(1,0,0);j<=temporaryValues.cutBian.at(1,1,0);j++){
    for(int i=temporaryValues.cutBian.at(0,0,0);i<=temporaryValues.cutBian.at(0,1,0);i++){
      SeriesCalcHotPoint->AddXYZ(i-temporaryValues.calcArrayShowCenter.row,
                      temporaryValues.calcHotPointData.at(i,j,0),
                      j-temporaryValues.calcArrayShowCenter.col);
    }
  }

  this->ChartCalcHotPoint->LeftAxis->StartPosition = 0;
  this->ChartCalcHotPoint->LeftAxis->EndPosition = 0; //通过将所有点压缩到底面来实现向2D转化
  this->ChartCalcHotPoint->View3DOptions->Rotation = 0; //通过将Chart旋转到一个固定角度，使网
  this->ChartCalcHotPoint->View3DOptions->Elevation = 270;  //格和轴有2D效果
}


//---------------------------------------------------------------------------

void __fastcall TFormMain::RzPageControlProfileAndStaticPageChange(
      TObject *Sender)
{
  //
  if(RzPageControlProfileAndStatic->ActivePageIndex == 1)
  {
    TFormStaticQuery* newStaticQueryForm = new TFormStaticQuery(this);
    newStaticQueryForm->Parent = this;
    newStaticQueryForm->FormStyle = fsStayOnTop;
    newStaticQueryForm->Show();
  }
}

void __fastcall TFormMain::showMeasureDoseStatic(){
  if(true == this->temporaryValues.measureFilePath.empty()
     || true==this->temporaryValues.NormMeasureDoseData.isEmpty()){
     return;
  }
  this->SeriesStatics->Clear();
  map<double,int> staticResult = statistic(temporaryValues.NormMeasureDoseData.getData(),temporaryValues.NormMeasureDoseData.getDataLength(),1);

  for(map<double,int>::iterator itera = staticResult.begin();itera != staticResult.end();itera++){
    if(itera->first>temporaryValues.checkStandardParam.threshold){
      this->SeriesStatics->AddXY(itera->first,itera->second,FormatFloat("0.0",itera->first),clBlue);
    }
  }
  staticResult.clear();
  map<double,int>().swap(staticResult);
}
void __fastcall TFormMain::showCalculateDoseStatic(){
  if(true == this->temporaryValues.calcFilePath.empty()
     || true==this->temporaryValues.NormCalcDoseData.isEmpty()){
     return;
  }
  this->SeriesStatics->Clear();
  map<double,int> staticResult = statistic(temporaryValues.NormCalcDoseData.getData(),temporaryValues.NormCalcDoseData.getDataLength(),1);

  for(map<double,int>::iterator itera = staticResult.begin();itera != staticResult.end();itera++){
    if(itera->first>temporaryValues.checkStandardParam.threshold){
      this->SeriesStatics->AddXY(itera->first,itera->second,FormatFloat("0.0",itera->first),clBlue);
    }
  }

  staticResult.clear();
  map<double,int>().swap(staticResult);
}
void __fastcall TFormMain::showCheckResultStatic(){
  if(false == temporaryValues.checkedRecord.getCheckedStatus()){
    return;
  }
  switch(temporaryValues.checkedRecord.getCheckType())
  {
    case CHECKTYPE(ABS_GAMMA):
    case CHECKTYPE(REL_GAMMA):
    {
      if(NULL == temporaryValues.checkedRecord.getSingleGammaResult()
        ||true==temporaryValues.checkedRecord.getSingleGammaResult()->everyPointResults.isEmpty())
      {
        return;
      }
      this->SeriesStatics->Clear();
      map<double,int> staticResult = statisticForCheckResult(temporaryValues.checkedRecord.getSingleGammaResult()->everyPointResults.getData()
                                               ,temporaryValues.checkedRecord.getSingleGammaResult()->everyPointResults.getDataLength(),1);

      for(map<double,int>::iterator itera = staticResult.begin();itera != staticResult.end();itera++){
        double itfirs = itera->first;
        int cc = itera->second;
        if(itera->first>0.1 && itera->first<1.1){
          this->SeriesStatics->AddXY(itera->first,itera->second,FormatFloat("0.00",itera->first),clBlue);
        }
      }

      staticResult.clear();
      map<double,int>().swap(staticResult);
    }
    break;

    case CHECKTYPE(ABS_DTA_FloatWay):
    case CHECKTYPE(ABS_DTA_MidValueWay):
    case CHECKTYPE(ABS_DTA_SamePositionWay):
    case CHECKTYPE(REL_DTA_FloatWay):
    case CHECKTYPE(REL_DTA_MidValueWay):
    case CHECKTYPE(REL_DTA_SamePositionWay):
    {
      if(NULL == temporaryValues.checkedRecord.getSingleDTAResult()
        ||true==temporaryValues.checkedRecord.getSingleDTAResult()->everyPointResults.isEmpty())
      {
        return;
      }
      this->SeriesStatics->Clear();
      map<double,int> staticResult = statisticForCheckResult(temporaryValues.checkedRecord.getSingleDTAResult()->everyPointResults.getData()
                                               ,temporaryValues.checkedRecord.getSingleDTAResult()->everyPointResults.getDataLength(),1);

      for(map<double,int>::iterator itera = staticResult.begin();itera != staticResult.end();itera++){
        if(itera->first>0.1 && itera->first<3){
          this->SeriesStatics->AddXY(itera->first,itera->second,FormatFloat("0.00",itera->first),clBlue);
        }
      }

      staticResult.clear();
      map<double,int>().swap(staticResult);
      
    }
    break;

    case CHECKTYPE(ABS_DD):
    {
      if(NULL == temporaryValues.checkedRecord.getSingleDDResult()
        ||true==temporaryValues.checkedRecord.getSingleDDResult()->everyPointResults.isEmpty())
      {
        return;
      }
      this->SeriesStatics->Clear();
      map<double,int> staticResult = statisticForCheckResult(temporaryValues.checkedRecord.getSingleDDResult()->everyPointResults.getData()
                                               ,temporaryValues.checkedRecord.getSingleDDResult()->everyPointResults.getDataLength(),1);

      for(map<double,int>::iterator itera = staticResult.begin();itera != staticResult.end();itera++){
        if(itera->first>0.1 && itera->first<3){
          this->SeriesStatics->AddXY(itera->first,itera->second,FormatFloat("0.00",itera->first),clBlue);
        }
      }

      staticResult.clear();
      map<double,int>().swap(staticResult);
      
    }
    break;

    default:
    break;
  }
}


//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
  MainFormLayout();
  ShowStandardAndTH();
}
//---------------------------------------------------------------------------
//第一幅图读入中测测量数据
void __fastcall TFormMain::OpenZCdoseClick(TObject *Sender)
{
  RunningLog::writeLog("OpenZCdoseClick...");

  patientInformationSetting(FILETYPE(ZCMeasureFileType));

}
void __fastcall TFormMain::ShowMeasureDialog(FILETYPE fileType){

  bool status =false;
  ChartMeasure->Enabled = false;
  switch(fileType)
  {
    case FILETYPE(ZCMeasureFileType):
    {
      OpenDialogMeasure->FilterIndex = 1;      //限制中测数据的格式为".dat"
    }
    break;

    case FILETYPE(MapCHECKMeasureFileType):
    {
     OpenDialogMeasure->FilterIndex = 2;      //限制Mapcheck数据的格式为".txt"
    }
    break;

    case FILETYPE(MatrixMeasureFileType):
    {
      OpenDialogMeasure->FilterIndex = 3;    //限制Matrix数据的格式为".txt"
    }
    break;
  }
  if(OpenDialogMeasure->Execute())
  {
    string fileName;

    resetSomeOnceOpen_ChangeVar();

    fileName = OpenDialogMeasure->FileName.c_str();
    status = this->readDoseFromFile(fileName,fileType);
    this->RefreshMeasureDoseGraphicFromDisplayValue();

    ShowPatientCache();
  }

  if(false==status){

    MessageBox(this->Handle,"Open measure file failed","Warning!",MB_OK);
    return;
  }
}
//------------------------------------------------------------------
//打开MapCheck格式的测量数据(真正的MapCheck数据，不是自己转换的)
void __fastcall TFormMain::OpenMapCHECKdoseClick(TObject *Sender)
{
  RunningLog::writeLog("OpenMapCHECKdoseClick...");

  patientInformationSetting(FILETYPE(MapCHECKMeasureFileType));
}

//---------------------------------------------------------------------------
//第一幅图读入Matrix测量数据
void __fastcall TFormMain::OpenMatrixDoseClick(TObject *Sender)
{
  RunningLog::writeLog("OpenMatrixDoseClick...");

  patientInformationSetting(FILETYPE(MatrixMeasureFileType));
}

//-----------------------------------------------------------------------
void __fastcall TFormMain::Open_Plan_DICOMClick(TObject *Sender)
{
  bool status = false;
  if(temporaryValues.measureFilePath.empty() || 0==temporaryValues.measureFilePath.length()){
    MessageBox(this->Handle,"请读入测量数据以获取硬件信息","Warning!",MB_OK);
    return;
  }
  
  RunningLog::writeLog("Open_Plan_DICOMClick...");

  OpenDialogCalculate->FilterIndex = 1;      //限制DICOM数据的格式为".dcm"
  if(OpenDialogCalculate->Execute())
  {
    string fileName;
    fileName = OpenDialogCalculate->FileName.c_str();

    status = this->readDoseFromFile(fileName,FILETYPE(DICOMCalcFileType));
    this->RefreshCalculateDoseGraphicFromDisplayValue();

    ShowPatientCache();
  }

   if(false == status){
    MessageBox(this->Handle,"打开文件失败!","Warning!",MB_OK);
    return;
  }
  
}
//--------------------------------------------------------------------------------
bool __fastcall TFormMain::readDoseFromFile(string filename,FILETYPE fileType){

  bool result = false;
  
  switch(fileType)
  {
    case FILETYPE(ZCMeasureFileType):
      result = this->readZCMeasureDoseFromFile(filename);
      break;

    case FILETYPE(MapCHECKMeasureFileType):
      result = this->readMapCHECKMeasureDoseFromFile(filename);
      break;

    case FILETYPE(MatrixMeasureFileType):
      result = this->readMatrixMeasureDoseFromFile(filename);
      break;

    case FILETYPE(DICOMCalcFileType):
      result = this->readDICOMCalcDoseFromFile(filename);
      break;

    case FILETYPE(SCUCalcFileType):
      result = this->readSCUCalcDoseFromFile(filename);
      break;
    default:
      result = false;
      break;
  }

  return result;
}
//-------------------------------------------------------------------------

bool TFormMain::readZCMeasureDoseFromFile(string filename){
  bool result = false;
  
  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;
  DosePair* dosePair = NULL;
  Dose* dose = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    return false;
  }

  globalMem->setHandel_Model(HANDLE_MODEL(ADAC));    //ADAC Model

  if(NULL == globalMem->getGatePairDose()){
    globalMem->allocateGatePairDose();
  }
  gatePairDose = globalMem->getGatePairDose();

  if(NULL == gatePairDose->getDosePair()){
    gatePairDose->allocateDosePair();
  }
  dosePair = gatePairDose->getDosePair();

  if(NULL != dosePair->getMeasureDose()){
    dosePair->cleanMeasureDose();
  }
  dosePair->allocateMeasureDose();
  dose = dosePair->getMeasureDose();

  if((result=dose->loadDoseFile(filename,FILETYPE(ZCMeasureFileType)))==true){
     gatePairDose->Notify(Message_Notify(Update_measure_fromGatePair));

     //Flush to cache
    globalMem->flushMeasureToCache();
  }



  globalMem = NULL;
  gatePairDose = NULL;
  dosePair = NULL;
  dose = NULL;

  return result;
}

bool TFormMain::readMapCHECKMeasureDoseFromFile(string filename){

  bool result = false;

  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;
  DosePair* dosePair = NULL;
  Dose* dose = NULL;



  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    return false;
  }

  globalMem->setHandel_Model(HANDLE_MODEL(ADAC));    //ADAC Model

  if(NULL == globalMem->getGatePairDose()){
    globalMem->allocateGatePairDose();
  }
  gatePairDose = globalMem->getGatePairDose();

  if(NULL == gatePairDose->getDosePair()){
    gatePairDose->allocateDosePair();
  }
  dosePair = gatePairDose->getDosePair();

  if(NULL != dosePair->getMeasureDose()){
    dosePair->cleanMeasureDose();
  }
  dosePair->allocateMeasureDose();
  dose = dosePair->getMeasureDose();

  if((result=dose->loadDoseFile(filename,FILETYPE(MapCHECKMeasureFileType)))==true){
     gatePairDose->Notify(Message_Notify(Update_measure_fromGatePair));
     
     //Flush to cache
     globalMem->flushMeasureToCache();
  }

  globalMem = NULL;
  gatePairDose = NULL;
  dosePair = NULL;
  dose = NULL;
  
  return result;

}

bool TFormMain::readMatrixMeasureDoseFromFile(string filename){

  bool result = false;

  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;
  DosePair* dosePair = NULL;
  Dose* dose = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return false;
  }

  globalMem->setHandel_Model(HANDLE_MODEL(SNDAC));    //SNDAC Model

  if(NULL == globalMem->getGatePairDose()){
    globalMem->allocateGatePairDose();
  }
  gatePairDose = globalMem->getGatePairDose();

  if(NULL == gatePairDose->getDosePair()){
    gatePairDose->allocateDosePair();
  }
  dosePair = gatePairDose->getDosePair();

  if(NULL != dosePair->getMeasureDose()){
    dosePair->cleanMeasureDose();
  }
  dosePair->allocateMeasureDose();
  dose = dosePair->getMeasureDose();

  if((result=dose->loadDoseFile(filename,FILETYPE(MatrixMeasureFileType)))==true){
     gatePairDose->Notify(Message_Notify(Update_measure_fromGatePair));

     //Flush to cache
     globalMem->flushMeasureToCache();
  }

  globalMem = NULL;
  gatePairDose = NULL;
  dosePair = NULL;
  dose = NULL;
  
  return result;
}

bool TFormMain::readDICOMCalcDoseFromFile(string filename){
  bool result = false;

  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;
  DosePair* dosePair = NULL;
  Dose* dose = NULL;



  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    return false;
  }

  if(NULL == globalMem->getGatePairDose()){
    globalMem->allocateGatePairDose();
  }
  gatePairDose = globalMem->getGatePairDose();

  if(NULL == gatePairDose->getDosePair()){
    gatePairDose->allocateDosePair();
  }
  dosePair = gatePairDose->getDosePair();

  if(NULL != dosePair->getCalculateDose()){
    dosePair->cleanCalculateDose();
  }
  dosePair->allocateCalculateDose();
  dose = dosePair->getCalculateDose();

  if((result=dose->loadDoseFile(filename,FILETYPE(DICOMCalcFileType)))==true){
     gatePairDose->Notify(Message_Notify(Update_calculate_fromGatePair));

     //Flush to cache
     globalMem->flushCalculateToCache();
  }

  globalMem = NULL;
  gatePairDose = NULL;
  dosePair = NULL;
  dose = NULL;
  
  return result;
}

bool TFormMain::readSCUCalcDoseFromFile(string filename){

  bool result = false;

  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;
  DosePair* dosePair = NULL;
  Dose* dose = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    return false;
  }

  if(NULL == globalMem->getGatePairDose()){
    globalMem->allocateGatePairDose();
  }
  gatePairDose = globalMem->getGatePairDose();

  if(NULL == gatePairDose->getDosePair()){
    gatePairDose->allocateDosePair();
  }
  dosePair = gatePairDose->getDosePair();

  if(NULL != dosePair->getCalculateDose()){
    dosePair->cleanCalculateDose();
  }
  dosePair->allocateCalculateDose();
  dose = dosePair->getCalculateDose();

  if((result=dose->loadDoseFile(filename,FILETYPE(SCUCalcFileType)))==true){
     gatePairDose->Notify(Message_Notify(Update_calculate_fromGatePair));
     
     //Flush to cache
     globalMem->flushCalculateToCache();
  }

  globalMem = NULL;
  gatePairDose = NULL;
  dosePair = NULL;
  dose = NULL;
  
  return result;
}

void __fastcall TFormMain::ClearMeasureChart(){

  //Reset the Chart
  SeriesA->Clear();
  SeriesASolid->Clear();
  SeriesAx->Clear();
  SeriesAy->Clear();
  SeriesAm->Clear();
  SeriesBm->Clear();
  SeriesASolid->Visible = false;
  SeriesA->ShowInLegend = true;
  
  ProMeaSeries->Clear();
  ProCauSeries->Clear();
  ShowProSeries->Clear();
  this->ChartCompare->BottomAxis->Minimum = 0;
  this->ChartCompare->BottomAxis->Maximum = 0;
  this->ChartCompare->BottomAxis->Title->Caption = "None";
  this->ChartCompare->LeftAxis->Maximum = 100;
  this->SpeedButton3DMeasure->Caption="2D";

  //Clean the grid line (x-direction) before refreshing the graphic
  if(agridlinex.Length){
    for(int j=0;j<agridlinex.Length;j++){
      delete agridlinex[j];
    }
  }

  //Clean the grid line (y-direction) before refreshing the graphic
  if(agridliney.Length){
    for(int i=0;i<agridliney.Length;i++){
      delete agridliney[i];
    }
  }
  FormMain->KeyPreview = true;
  
}

void __fastcall TFormMain::ClearCalcChart(){

  //Reset the Chart
  SeriesB->Clear();
  SeriesBSolid->Clear();
  SeriesBx->Clear();
  SeriesBy->Clear();
  SeriesAm->Clear();
  SeriesBm->Clear();
  SeriesBSolid->Visible = false;
  SeriesB->ShowInLegend = true;

  ProMeaSeries->Clear();
  ProCauSeries->Clear();
  ShowProSeries->Clear();
  this->ChartCompare->BottomAxis->Minimum = 0;
  this->ChartCompare->BottomAxis->Maximum = 0;
  this->ChartCompare->BottomAxis->Title->Caption = "None";
  this->ChartCompare->LeftAxis->Maximum = 100;
  this->SpeedButton3DCalculate->Caption="2D";

  //Clean the grid line (x-direction) before refreshing the graphic
  if(bgridlinex.Length){
    for(int j=0;j<bgridlinex.Length;j++){
      delete bgridlinex[j];
    }
  }

  //Clean the grid line (y-direction) before refreshing the graphic
  if(bgridliney.Length){
    for(int i=0;i<bgridliney.Length;i++){
      delete bgridliney[i];
    }
  }

  FormMain->KeyPreview = true;

}
//-------------------------------------------------------------------
bool __fastcall TFormMain::RefreshMeasureDoseGraphicFromTemporyValue(){
  bool result;

  double tempValue;
  double doseCentralPosX,doseCentralPosY;
  
  //Clear Measure Graphic Chart
  ClearMeasureChart();

  //-------------------------------

  TeeOpenGLMeasure->Active = true;
  TeeOpenGLMeasure->TeePanel = ChartMeasure;

  ChartMeasure->MarginBottom = 0;
  ChartMeasure->MarginTop = 0;
  ChartMeasure->MarginLeft = 0;
  ChartMeasure->MarginRight = 0;
  ChartMeasure->BottomAxis->StartPosition = 50 - (temporaryValues.measureRowLength)*(25 + 25*((float)(ChartMeasure->Height))/ChartMeasure->Legend->Left)/(float)(temporaryValues.measureColLength);
  ChartMeasure->BottomAxis->EndPosition = 50 + (temporaryValues.measureRowLength)*(25 + 25*((float)(ChartMeasure->Height))/ChartMeasure->Legend->Left)/(float)(temporaryValues.measureColLength);

  seczoom[0] = 1;   //此时不存在剪切后放大修正的问题


  for(int i=0;i<temporaryValues.measureXGridLineNum;i++){
    agridlinex[i] = new TPoint3DSeries(this);
    agridlinex[i]->ParentChart = ChartMeasure;
    agridlinex[i]->Pointer->Visible = false;
    agridlinex[i]->LinePen->Color = clWhite;
    agridlinex[i]->Clear();
    agridlinex[i]->Visible = true;
  }

  for(int j=0;j<temporaryValues.measureXGridLineNum;j++){
    agridliney[j] = new TPoint3DSeries(this);
    agridliney[j]->ParentChart = ChartMeasure;
    agridliney[j]->Pointer->Visible = false;
    agridliney[j]->LinePen->Color = clWhite;
    agridliney[j]->Clear();
    agridliney[j]->Visible = true;
  }

  for(int j=0;j<temporaryValues.measureColLength;j++){
    for(int i=0;i<temporaryValues.measureRowLength;i++){
      SeriesA->AddXYZ(i-temporaryValues.measureArrayShowCenter.row,
                      temporaryValues.NormMeasureDoseData.at(i,j,0),
                      j-temporaryValues.measureArrayShowCenter.col);

      SeriesASolid->AddXYZ(i-temporaryValues.measureArrayShowCenter.row,
                           temporaryValues.NormMeasureDoseData.at(i,j,0),
                           j-temporaryValues.measureArrayShowCenter.col);

    }
  }

  //The x-direction grid lines
  for(int j=0;j<temporaryValues.measureColLength;j++){
    for(int i=0;i<temporaryValues.measureRowLength;i++){
      agridlinex[j]->AddXYZ(i-temporaryValues.measureArrayShowCenter.row,
                            temporaryValues.NormMeasureDoseData.at(i,j,0),
                            j-temporaryValues.measureArrayShowCenter.col,"",clWhite);

    }
  }

  //The y-direction grid lines
  for(int i=0;i<temporaryValues.measureRowLength;i++){
    for(int j=0;j<temporaryValues.measureColLength;j++){
      agridliney[i]->AddXYZ(i-temporaryValues.measureArrayShowCenter.row,
                            temporaryValues.NormMeasureDoseData.at(i,j,0),
                            j-temporaryValues.measureArrayShowCenter.col,"",clWhite);
    }
  }

  doseCentralPosX = temporaryValues.measureDoseCentral.x/temporaryValues.gridSize[0];
  doseCentralPosY = temporaryValues.measureDoseCentral.y/temporaryValues.gridSize[1];
  
  for(int i=0;i<temporaryValues.measureRowLength;i++){
    tempValue = getDoseDataInAPosition(temporaryValues.NormMeasureDoseData,
                                       i,
                                       doseCentralPosY,
                                       0,
                                       INTEPOLATION_ALGORITHM(LINER),
                                       HANDLE_MODEL(ADAC)
                                       );
    SeriesAx->AddXYZ(i-temporaryValues.measureArrayShowCenter.row,
                     tempValue,
                     doseCentralPosY -temporaryValues.measureArrayShowCenter.col,
                     "",
                     clBlack);
  }

  for(int j=0;j<temporaryValues.measureColLength;j++){
    tempValue = getDoseDataInAPosition(temporaryValues.NormMeasureDoseData,
                                       doseCentralPosX,
                                       j,
                                       0,
                                       INTEPOLATION_ALGORITHM(LINER),
                                       HANDLE_MODEL(ADAC)
                                       );
    SeriesAy->AddXYZ(doseCentralPosX-temporaryValues.measureArrayShowCenter.row,
                     tempValue,
                     j -temporaryValues.measureArrayShowCenter.col,
                     "",
                     clBlack);
  }

  ChartMeasure->Enabled = true;

  return true;
}
//----------------------------------------------------------------
bool __fastcall TFormMain::RefreshCalculateDoseGraphicFromDisplayValue(){

  bool result;

  double tempValue;
  double doseCentralPosX,doseCentralPosY;

  GlobalMembers* globalMem = NULL;
  DisplayPairDose* displayPairDose = NULL;
  Dose* calcDisplayDose = NULL;
  Dose* normCalcDisplayDose = NULL;

  int ist,iend;
  int jst,jend;
  int coutlinex = 0,coutliney = 0;

  //Reset the temporyValues
  temporaryValues.calcReset();

  //Clear calc Graphic Chart
  ClearCalcChart();

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return false;
  }

  displayPairDose = globalMem->getDisplayPairDose();
  if(NULL == displayPairDose){
    RunningLog::writeLog("The DisplayPairDose is NULL;",__LINE__);
    return false;
  }

  //orginal data
  calcDisplayDose = displayPairDose->getCalcDisplayDose();
  if(NULL == calcDisplayDose){
    RunningLog::writeLog("The original calc DisplayDose is NULL;",__LINE__);
    return false;
  }

  calcDisplayDose->sync_Read_Start();

  temporaryValues.calcFirstAlignmentCenter = *calcDisplayDose->getFirstAlignmentCentral();

  if(NULL == calcDisplayDose->getDoseMatrix()){
    RunningLog::writeLog("The origianl clac dose Matrix is NULL;",__LINE__);
    return false;
  }
  if(NULL == calcDisplayDose->getDoseMatrix()->getData()){
    RunningLog::writeLog("The abs calc dose data is NULL;",__LINE__);
    return false;
  }
  temporaryValues.calcRowLength = calcDisplayDose->getDoseMatrix()->getRowLength();
  temporaryValues.calcColLength = calcDisplayDose->getDoseMatrix()->getColLength();
  temporaryValues.calcHeightLength = calcDisplayDose->getDoseMatrix()->getHeightLength();
  temporaryValues.calcTotalNum = calcDisplayDose->getDoseMatrix()->getDataLength();
  temporaryValues.calcDoseData = *calcDisplayDose->getDoseMatrix();

  temporaryValues.calcFilePath = calcDisplayDose->unSync_getFileName();

  calcDisplayDose->sync_finish();

  //norm calc Dose
  normCalcDisplayDose = displayPairDose->getNormCalcDisplayDose();
  if(NULL == normCalcDisplayDose){
    RunningLog::writeLog("The NormCalcDisplayDose is NULL;",__LINE__);
    return false;
  }

  normCalcDisplayDose->sync_Read_Start();

  if(NULL == normCalcDisplayDose->getDoseMatrix()){
    RunningLog::writeLog("The norm calc dose Matrix is NULL;",__LINE__);
    return false;
  }
  if(NULL == normCalcDisplayDose->getDoseMatrix()->getData()){
    RunningLog::writeLog("The norm calc dose data is NULL;",__LINE__);
    return false;
  }
  temporaryValues.calcDoseCentral = *normCalcDisplayDose->getDoseCentral();
  
  temporaryValues.NormCalcDoseData = *normCalcDisplayDose->getDoseMatrix();

  temporaryValues.maxCalcPoint = getMaxValuePoint(*normCalcDisplayDose->getDoseMatrix());
  
  normCalcDisplayDose->sync_finish();

  if(NULL == globalMem->getDoseCheck()){
    globalMem->allocateDoseCheck();
  }
  globalMem->getDoseCheck()->reset();

  //-------------------------------
  matrixDataDataCutoff(temporaryValues.NormCalcDoseData,temporaryValues.cutBian,0.01);
  //-------------------------------

  seczoom[1] = 0.95*Min((temporaryValues.cutBian.at(0,1,0) - temporaryValues.cutBian.at(0,0,0))/((float)(temporaryValues.calcRowLength-1)),
                        (temporaryValues.cutBian.at(1,1,0) - temporaryValues.cutBian.at(1,0,0))/((float)(temporaryValues.calcColLength-1)));
  ChartCalculate->View3DOptions->Zoom = 0.83*100*504.0/float(PanelCalculate->Width);

  TeeOpenGLCalculate->Active = true;
  TeeOpenGLCalculate->TeePanel = ChartCalculate;

  ChartCalculate->MarginBottom = 0;
  ChartCalculate->MarginTop = 0;
  ChartCalculate->MarginLeft = 0;
  ChartCalculate->MarginRight = 0;
  ChartCalculate->BottomAxis->StartPosition = 50 - (temporaryValues.cutBian.at(0,1,0) - temporaryValues.cutBian.at(0,0,0))*(25 + 25*((float)(ChartCalculate->Height))/ChartCalculate->Legend->Left)/(float)(temporaryValues.cutBian.at(1,1,0) - temporaryValues.cutBian.at(1,0,0));
  ChartCalculate->BottomAxis->EndPosition = 50 + (temporaryValues.cutBian.at(0,1,0) - temporaryValues.cutBian.at(0,0,0))*(25 + 25*((float)(ChartCalculate->Height))/ChartCalculate->Legend->Left)/(float)(temporaryValues.cutBian.at(1,1,0) - temporaryValues.cutBian.at(1,0,0));

  temporaryValues.calcYGridLineNum = (temporaryValues.calcFirstAlignmentCenter.row - temporaryValues.cutBian.at(0,0,0))/temporaryValues.segments[0]
                                     + (temporaryValues.cutBian.at(0,1,0) - temporaryValues.calcFirstAlignmentCenter.row)/temporaryValues.segments[0] + 1; //平行于x方向的网格线的数目
  temporaryValues.calcXGridLineNum = (temporaryValues.calcFirstAlignmentCenter.col - temporaryValues.cutBian.at(1,0,0))/temporaryValues.segments[1]
                                     + (temporaryValues.cutBian.at(1,1,0) - temporaryValues.calcFirstAlignmentCenter.col)/temporaryValues.segments[1] + 1; //平行于x方向的网格线的数目

  bgridlinex.Length = temporaryValues.calcXGridLineNum;
  bgridliney.Length = temporaryValues.calcYGridLineNum;

  for(int i=0;i<temporaryValues.calcXGridLineNum;i++){
    bgridlinex[i] = new TPoint3DSeries(this);
    bgridlinex[i]->ParentChart = this->ChartCalculate;
    bgridlinex[i]->Pointer->Visible = false;
    bgridlinex[i]->LinePen->Color = clWhite;
    bgridlinex[i]->Clear();
    bgridlinex[i]->Visible = true;
  }

  for(int j=0;j<temporaryValues.calcYGridLineNum;j++){
    bgridliney[j] = new TPoint3DSeries(this);
    bgridliney[j]->ParentChart = this->ChartCalculate;
    bgridliney[j]->Pointer->Visible = false;
    bgridliney[j]->LinePen->Color = clWhite;
    bgridliney[j]->Clear();
    bgridliney[j]->Visible = true;
  }

  /*
  if(0 == (temporaryValues.cutBian.at(0,1,0) + temporaryValues.cutBian.at(0,0,0))%2 ){
    temporaryValues.calcArrayShowCenter.row =
        (temporaryValues.cutBian.at(0,1,0) + temporaryValues.cutBian.at(0,0,0))/2;
  }else{
    temporaryValues.calcArrayShowCenter.row =
        (temporaryValues.cutBian.at(0,1,0) + temporaryValues.cutBian.at(0,0,0) - 1)/2;
  }

  if(0 == (temporaryValues.cutBian.at(1,1,0) + temporaryValues.cutBian.at(1,0,0))%2 ){
    temporaryValues.calcArrayShowCenter.col =
        (temporaryValues.cutBian.at(1,1,0) + temporaryValues.cutBian.at(1,0,0))/2;
  }else{
    temporaryValues.calcArrayShowCenter.col =
        (temporaryValues.cutBian.at(1,1,0) + temporaryValues.cutBian.at(1,0,0) - 1)/2;
  }
  */
  temporaryValues.calcArrayShowCenter.row =
        (temporaryValues.cutBian.at(0,1,0) + temporaryValues.cutBian.at(0,0,0))/2;
  temporaryValues.calcArrayShowCenter.col =
        (temporaryValues.cutBian.at(1,1,0) + temporaryValues.cutBian.at(1,0,0))/2;


  for(int j=temporaryValues.cutBian.at(1,0,0);j<=temporaryValues.cutBian.at(1,1,0);j++){
    for(int i=temporaryValues.cutBian.at(0,0,0);i<=temporaryValues.cutBian.at(0,1,0);i++){
      SeriesB->AddXYZ(i-temporaryValues.calcArrayShowCenter.row,
                      temporaryValues.NormCalcDoseData.at(i,j,0),
                      j-temporaryValues.calcArrayShowCenter.col);
      SeriesBSolid->AddXYZ(i-temporaryValues.calcArrayShowCenter.row,
                           temporaryValues.NormCalcDoseData.at(i,j,0),
                           j-temporaryValues.calcArrayShowCenter.col);
    }
  }

  jst = temporaryValues.cutBian.at(1,0,0)
       + (temporaryValues.calcFirstAlignmentCenter.col -temporaryValues.cutBian.at(1,0,0))%temporaryValues.segments[1];
  jend = temporaryValues.cutBian.at(1,1,0)
        - (temporaryValues.cutBian.at(1,1,0) - temporaryValues.calcFirstAlignmentCenter.col)%temporaryValues.segments[1];
  coutlinex = 0;

  for(int j=jst;j<=jend;j=j+temporaryValues.segments[1]){
    for(int i=temporaryValues.cutBian.at(0,0,0);i<=temporaryValues.cutBian.at(0,1,0);i++){
      bgridlinex[coutlinex]->AddXYZ(i-temporaryValues.calcArrayShowCenter.row,
                                     temporaryValues.NormCalcDoseData.at(i,j,0),
                                     j-temporaryValues.calcArrayShowCenter.col,"",clWhite);
    }
    coutlinex++;
  }

  ist = temporaryValues.cutBian.at(0,0,0)
       + (temporaryValues.calcFirstAlignmentCenter.row -temporaryValues.cutBian.at(0,0,0))%temporaryValues.segments[0];
  iend = temporaryValues.cutBian.at(0,1,0)
        - (temporaryValues.cutBian.at(0,1,0) - temporaryValues.calcFirstAlignmentCenter.row)%temporaryValues.segments[0];
  coutliney = 0;


  for(int i=ist;i<=iend;i=i+temporaryValues.segments[0]){
    for(int j=temporaryValues.cutBian.at(1,0,0);j<=temporaryValues.cutBian.at(1,1,0);j++){
      bgridliney[coutliney]->AddXYZ(i-temporaryValues.calcArrayShowCenter.row,
                                     temporaryValues.NormCalcDoseData.at(i,j,0),
                                     j-temporaryValues.calcArrayShowCenter.col,"",clWhite);
    }
    coutliney++;
  }

  doseCentralPosX = temporaryValues.calcDoseCentral.x/(temporaryValues.gridSize[0]/temporaryValues.segments[0]);
  doseCentralPosY = temporaryValues.calcDoseCentral.y/(temporaryValues.gridSize[1]/temporaryValues.segments[1]);

  for(int i=temporaryValues.cutBian.at(0,0,0);i<=temporaryValues.cutBian.at(0,1,0);i++){
    tempValue = getDoseDataInAPosition(temporaryValues.NormCalcDoseData,
                                       i,
                                       doseCentralPosY,
                                       0,
                                       INTEPOLATION_ALGORITHM(LINER),
                                       HANDLE_MODEL(ADAC)
                                       );
    SeriesBx->AddXYZ(i-temporaryValues.calcArrayShowCenter.row,
                     tempValue,
                     doseCentralPosY -temporaryValues.calcArrayShowCenter.col,
                     "",
                     clBlack);
  }

  for(int j=temporaryValues.cutBian.at(1,0,0);j<=temporaryValues.cutBian.at(1,1,0);j++){
    tempValue = getDoseDataInAPosition(temporaryValues.NormCalcDoseData,
                                       doseCentralPosX,
                                       j,
                                       0,
                                       INTEPOLATION_ALGORITHM(LINER),
                                       HANDLE_MODEL(ADAC)
                                       );
    SeriesBy->AddXYZ(doseCentralPosX-temporaryValues.calcArrayShowCenter.row,
                     tempValue,
                     j -temporaryValues.calcArrayShowCenter.col,
                     "",
                     clBlack);
  }

  ChartCalculate->Enabled = true;

  ShowCalcPath(temporaryValues.calcFilePath);

  globalMem = NULL;
  displayPairDose = NULL;
  calcDisplayDose = NULL;
  normCalcDisplayDose = NULL;


  //---Hot point graphy-------------------------
  RefreshCalcHotPointDose();
  ShowCalcHotPointGraphy();
  
  return true;
}

bool __fastcall TFormMain::RefreshCalculateDoseGraphicFromTemporyValue(){
   return true;
}

void __fastcall TFormMain::InitialCompareChart(const char* bottomAxisTitle){
  double maxPercent;
  if(temporaryValues.NormCalcDoseData.isEmpty() || temporaryValues.calcFilePath.empty()){
    maxPercent = temporaryValues.NormMeasureDoseData[temporaryValues.maxMeasurePoint];
  }else{
    maxPercent = max<double>(temporaryValues.NormMeasureDoseData[temporaryValues.maxMeasurePoint],
                             temporaryValues.NormCalcDoseData[temporaryValues.maxCalcPoint]);
  }

  InitialCompareChart(temporaryValues.measureRowLength,
                      temporaryValues.measureDoseCentral.x,
                      temporaryValues.gridSize[0],
                      maxPercent,
                      bottomAxisTitle);
  
}

void __fastcall TFormMain::InitialCompareChart(int gridLineNums,double doseCentral,double gridsize,double maxPercent,const char* bottomAxisTitle){

  this->ChartCompare->BottomAxis->Minimum = doseCentral - (gridLineNums - 1)*gridsize;
  this->ChartCompare->BottomAxis->Maximum = (gridLineNums - 1)*gridsize - doseCentral;
  this->ChartCompare->BottomAxis->Increment = 1;
  this->ChartCompare->BottomAxis->Title->Caption = bottomAxisTitle;

  this->ChartCompare->LeftAxis->Maximum = maxPercent;
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::MainFormLayout(){
  int i;
  ChartMeasure->AllowZoom = false;
  ChartCalculate->AllowZoom = false;
  ChartCompare->AllowZoom = false;
  /*
  TDeviceMode lpDevMode;    //定义一个TDeviceMode结构体用来储存EnumDisplaySettings函数的返回结果
  EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&lpDevMode); //(API函数)用来得到显示设备的参数
  Form1->Width = lpDevMode.dmPelsWidth;
  Form1->Height = lpDevMode.dmPelsHeight;
  */
  TRect Rect1;
  SystemParametersInfo(SPI_GETWORKAREA,0,&Rect1,0);//(API函数)用来得到窗体除工具栏
                                                   //之外的工作区域，结果放在Rect1中
  FormMain->Top = 0;
  FormMain->Left = 0;
  FormMain->Width = Rect1.Width();
  FormMain->Height = Rect1.Height();

  RzGroupBarCache->Left = 0;
  RzGroupBarCache->Width = FormMain->ClientWidth*0.1;

  PanelMeasure->Left = RzGroupBarCache->Width + 2;
  PanelMeasure->Width = (FormMain->ClientWidth - RzGroupBarCache->Width)/2.0;


  PanelCalculate->Left = RzGroupBarCache->Width + 2;
  PanelCalculate->Width = (FormMain->ClientWidth - RzGroupBarCache->Width)/2.0;

  PanelShowAndOperation->Left = PanelMeasure->Left + PanelMeasure->Width;
  PanelShowAndOperation->Width = FormMain->ClientWidth - PanelShowAndOperation->Left-1;

  RzGroupBarCache->Top = RzToolbar1->Top + RzToolbar1->Height + 2;
  RzGroupBarCache->Height = FormMain->ClientHeight - PanelMeasure->Top;

  PanelMeasure->Top = RzToolbar1->Top + RzToolbar1->Height + 2;
  PanelMeasure->Height = (FormMain->ClientHeight - PanelMeasure->Top)/2.0 - 2;
  PanelCalculate->Top = PanelMeasure->Top + PanelMeasure->Height + 2;
  PanelCalculate->Height = PanelMeasure->Height;

  PanelShowAndOperation->Top = RzToolbar1->Top + RzToolbar1->Height + 2;
  PanelShowAndOperation->Height = FormMain->ClientHeight - PanelShowAndOperation->Top;

  //-------------------------------PanelShowAndOperation-------------------------
  PanelShowAndOperationLayout();
  //-------------------------------ChartLayout-----------------------------------
  measureChartLayout();
  calcChartLayout();
  //------------------右上角面板设置---------------------------------------------
  SetRightTopPanel();
}

void __fastcall TFormMain::measureChartLayout(){
  //由于在Chart1图像为2D时设置了TeeOpenGL1->Active = false，所以2D时无法放大，所以需要采用别的方法
  //在进行判断时判断放大之后Panel1放大了多少倍，从而将Chart1进行等比放大
  //因此需要对非放大状态下的高度/宽度需要进行记录
  //StoreHeight = PanelMeasure->Height; //将放大之前的高度和宽度进行存储
  //StoreWidth = PanelMeasure->Width;

  ChartMeasure->View3DOptions->Zoom = 0.83*100*504.0/float(PanelMeasure->Width);

  SeriesA->ShowInLegend = false;

  ChartMeasure->LeftAxis->StartPosition = 20;
  ChartMeasure->LeftAxis->EndPosition = 80;

  //------------PanelTool的按钮设置----------------
  SeperateHeight = 4;
  ButtonsWidth = FormMain->ClientWidth*0.0165;
  ButtonsHeight = ButtonsWidth;


  //------------PanelTool1的按钮设置----------------
  PanelToolMeasure->Width = ButtonsWidth*1.3;

  ButtonFlushMeasureToCache->Width = ButtonsWidth;
  ButtonFlushMeasureToCache->Height = ButtonsHeight;
  ButtonFlushMeasureToCache->Left = (PanelToolMeasure->ClientWidth - ButtonFlushMeasureToCache->Width)/2.0;
  ButtonFlushMeasureToCache->Top = PanelToolMeasure->Height - ButtonFlushMeasureToCache->Height - SeperateHeight;

  SpeedButtonTransforMeasure->Width = ButtonsWidth;
  SpeedButtonTransforMeasure->Height = ButtonsHeight;
  SpeedButtonTransforMeasure->Left = (PanelToolMeasure->ClientWidth - SpeedButtonTransforMeasure->Width)/2.0;
  SpeedButtonTransforMeasure->Top = ButtonFlushMeasureToCache->Top - SeperateHeight - SpeedButtonTransforMeasure->Height;

  SpeedButton3DMeasure->Width = ButtonsWidth;
  SpeedButton3DMeasure->Height = ButtonsHeight;
  SpeedButton3DMeasure->Left = (PanelToolMeasure->ClientWidth - SpeedButton3DMeasure->Width)/2.0;
  SpeedButton3DMeasure->Top = SpeedButtonTransforMeasure->Top - SeperateHeight - SpeedButton3DMeasure->Height;

  SpeedButtonDetMeasure->Width = ButtonsWidth;
  SpeedButtonDetMeasure->Height = ButtonsHeight;
  SpeedButtonDetMeasure->Left = (PanelToolMeasure->ClientWidth - SpeedButtonDetMeasure->Width)/2.0;
  SpeedButtonDetMeasure->Top = SpeedButton3DMeasure->Top - SeperateHeight - SpeedButtonDetMeasure->Height;

  SpeedButtonLevelsSetMeasure->Width = ButtonsWidth;
  SpeedButtonLevelsSetMeasure->Height = ButtonsHeight;
  SpeedButtonLevelsSetMeasure->Left = (PanelToolMeasure->ClientWidth - SpeedButtonLevelsSetMeasure->Width)/2.0;
  SpeedButtonLevelsSetMeasure->Top = SpeedButtonDetMeasure->Top - SeperateHeight - SpeedButtonLevelsSetMeasure->Height;

  SpeedButtonGridMeasure->Width = ButtonsWidth;
  SpeedButtonGridMeasure->Height = ButtonsHeight;
  SpeedButtonGridMeasure->Left = (PanelToolMeasure->ClientWidth - SpeedButtonGridMeasure->Width)/2.0;
  SpeedButtonGridMeasure->Top = SpeedButtonLevelsSetMeasure->Top - SeperateHeight - SpeedButtonGridMeasure->Height;

}
void __fastcall TFormMain::calcChartLayout(){
  ChartCalculate->View3DOptions->Zoom = 0.83*100*504.0/float(PanelCalculate->Width);

  SeriesB->ShowInLegend = false;

  ChartCalculate->LeftAxis->StartPosition = 20;
  ChartCalculate->LeftAxis->EndPosition = 80;

  //------------PanelTool的按钮设置----------------
  SeperateHeight = 4;
  ButtonsWidth = FormMain->ClientWidth*0.0165;
  ButtonsHeight = ButtonsWidth;

  //------------PanelTool2的按钮设置----------------
  PanelToolCalculate->Width = ButtonsWidth*1.3;

  ButtonFlushCalcToCache->Width = ButtonsWidth;
  ButtonFlushCalcToCache->Height = ButtonsHeight;
  ButtonFlushCalcToCache->Left = (PanelToolCalculate->ClientWidth - ButtonFlushCalcToCache->Width)/2.0;
  ButtonFlushCalcToCache->Top = PanelToolCalculate->Height - ButtonFlushCalcToCache->Height - SeperateHeight;

  SpeedButtonTransforCalculate->Width = ButtonsWidth;
  SpeedButtonTransforCalculate->Height = ButtonsHeight;
  SpeedButtonTransforCalculate->Left = (PanelToolCalculate->ClientWidth - SpeedButtonTransforCalculate->Width)/2.0;
  SpeedButtonTransforCalculate->Top = ButtonFlushCalcToCache->Top - SeperateHeight - SpeedButtonTransforCalculate->Height;

  SpeedButton3DCalculate->Width = ButtonsWidth;
  SpeedButton3DCalculate->Height = ButtonsHeight;
  SpeedButton3DCalculate->Left = (PanelToolCalculate->ClientWidth - SpeedButton3DCalculate->Width)/2.0;
  SpeedButton3DCalculate->Top = SpeedButtonTransforCalculate->Top - SeperateHeight - SpeedButton3DCalculate->Height;

  SpeedButtonDetCalculate->Width = ButtonsWidth;
  SpeedButtonDetCalculate->Height = ButtonsHeight;
  SpeedButtonDetCalculate->Left = (PanelToolCalculate->ClientWidth - SpeedButtonDetCalculate->Width)/2.0;
  SpeedButtonDetCalculate->Top = SpeedButton3DCalculate->Top - SeperateHeight - SpeedButtonDetCalculate->Height;

  SpeedButtonLevelsSetCalculate->Width = ButtonsWidth;
  SpeedButtonLevelsSetCalculate->Height = ButtonsHeight;
  SpeedButtonLevelsSetCalculate->Left = (PanelToolCalculate->ClientWidth - SpeedButtonLevelsSetCalculate->Width)/2.0;
  SpeedButtonLevelsSetCalculate->Top = SpeedButtonDetCalculate->Top - SeperateHeight - SpeedButtonLevelsSetCalculate->Height;

  SpeedButtonGridCalculate->Width = ButtonsWidth;
  SpeedButtonGridCalculate->Height = ButtonsHeight;
  SpeedButtonGridCalculate->Left = (PanelToolCalculate->ClientWidth - SpeedButtonGridCalculate->Width)/2.0;
  SpeedButtonGridCalculate->Top = SpeedButtonLevelsSetCalculate->Top - SeperateHeight - SpeedButtonGridCalculate->Height;
}

void __fastcall TFormMain::PanelShowAndOperationLayout(){
  RzPageControlOperatAndCompare->Top = 0;
  RzPageControlOperatAndCompare->Height = PanelShowAndOperation->Height*0.48;
  RzPageControlOperatAndCompare->Left = 0;
  RzPageControlOperatAndCompare->Width = PanelShowAndOperation->Width;

  RzPageControlProfileAndStatic->Top = RzPageControlOperatAndCompare->Height;
  RzPageControlProfileAndStatic->Height = PanelShowAndOperation->Height*0.48;
  RzPageControlProfileAndStatic->Left = 0;
  RzPageControlProfileAndStatic->Width = PanelShowAndOperation->Width;

  StatusBar1->Align = alBottom;
  StatusBar1->Height = PanelShowAndOperation->Height*0.04;
}

//------------------右上角面板设置---------------------------------------------
void __fastcall TFormMain::SetRightTopPanel()
{
  //----------------下拉菜单值设定------------------------------------------------
  ComboBoxData->Items->Clear();
  ComboBoxData->Items->Add(AnsiString("Normalized"));
  ComboBoxData->Items->Add(AnsiString("AbsDose"));   //对DataType下拉菜单进行设定

  ComboBoxGraph->Items->Clear();
  ComboBoxGraph->Items->Add(AnsiString("Hotpoint")); //对GraphType的下拉菜单进行设定
  ComboBoxGraph->Items->Add(AnsiString("Normal"));

  //----------------------------------------GroupBoxTypeChange-------------------------------
  GroupBoxTypeChange->Left = 3;
  GroupBoxTypeChange->Top = 3;
  GroupBoxTypeChange->Width = RzPanelOperation->Width*0.3;
  GroupBoxTypeChange->Height = RzPanelOperation->Height*0.18;

  ComboBoxGraph->Height = (GroupBoxTypeChange->ClientWidth-abs(GroupBoxTypeChange->Font->Height))*0.5;
  ComboBoxGraph->Top = 1.4*abs(GroupBoxTypeChange->Font->Height) + (GroupBoxTypeChange->Height- abs(GroupBoxTypeChange->Font->Height) - ComboBoxGraph->Height)/2.0;
  ComboBoxGraph->Width = GroupBoxTypeChange->Width*0.45;
  ComboBoxGraph->Left =  GroupBoxTypeChange->Left + GroupBoxTypeChange->Width*0.03;

  ComboBoxData->Height = (GroupBoxTypeChange->ClientWidth - abs(GroupBoxTypeChange->Font->Height))*0.5;
  ComboBoxData->Top = 1.4*abs(GroupBoxTypeChange->Font->Height) + (GroupBoxTypeChange->Height- abs(GroupBoxTypeChange->Font->Height) - ComboBoxData->Height)/2.0;
  ComboBoxData->Width = GroupBoxTypeChange->Width*0.45;
  ComboBoxData->Left =  GroupBoxTypeChange->Left + ComboBoxGraph->Left + ComboBoxGraph->Width + GroupBoxTypeChange->Width*0.03;

  //--------------------------------------GroupBoxStandard-----------------------------------
  GroupBoxStandard->Left =3;
  GroupBoxStandard->Top = GroupBoxTypeChange->Top + GroupBoxTypeChange->Height + 10;
  GroupBoxStandard->Width = RzPanelOperation->Width*0.3;
  GroupBoxStandard->Height =  RzPanelOperation->Height*0.3;

  EditTH->Height = (GroupBoxStandard->Height - abs(GroupBoxStandard->Font->Height) )*0.18;
  EditTH->Top = 1.4*abs(GroupBoxStandard->Font->Height) + (GroupBoxStandard->Height - abs(GroupBoxStandard->Font->Height) - 3*EditTH->Height)/4.0;
  LabelThreshold->Height = EditTH->Height;
  LabelThreshold->Top = EditTH->Top;
  LabelThreshold->Width = GroupBoxStandard->Width*0.45;
  EditTH->Width = GroupBoxStandard->Width*0.4;
  LabelThreshold->Left = (GroupBoxStandard->Width - LabelThreshold->Width - EditTH->Width)/3.0;
  EditTH->Left = LabelThreshold->Left + LabelThreshold->Width+(GroupBoxStandard->Width - LabelThreshold->Width - EditTH->Width)/3.0;


  EditDoseGap->Height =(GroupBoxStandard->Height - abs(GroupBoxStandard->Font->Height) )*0.18;
  EditDoseGap->Top = EditTH->Top +  EditTH->Height + (GroupBoxStandard->Height - abs(GroupBoxStandard->Font->Height) - 3*EditDoseGap->Height)/4.0;
  LabelDoseGap->Height = EditDoseGap->Height;
  LabelDoseGap->Top = EditDoseGap->Top;
  LabelDoseGap->Width = GroupBoxStandard->Width*0.45;
  EditDoseGap->Width = GroupBoxStandard->Width*0.4;
  LabelDoseGap->Left = (GroupBoxStandard->Width - LabelDoseGap->Width - EditDoseGap->Width)/3.0;
  EditDoseGap->Left = LabelDoseGap->Left + LabelDoseGap->Width+(GroupBoxStandard->Width - LabelDoseGap->Width - EditDoseGap->Width)/3.0;

  EditDistance->Height =(GroupBoxStandard->Height - abs(GroupBoxStandard->Font->Height) )*0.18;
  EditDistance->Top = EditDoseGap->Top +  EditDoseGap->Height + (GroupBoxStandard->Height - abs(GroupBoxStandard->Font->Height) - 3*EditDoseGap->Height)/4.0;
  LabelDistance->Height = EditDistance->Height;
  LabelDistance->Top = EditDistance->Top;
  LabelDistance->Width = GroupBoxStandard->Width*0.45;
  EditDistance->Width = GroupBoxStandard->Width*0.4;
  LabelDistance->Left = (GroupBoxStandard->Width - LabelDistance->Width - EditDistance->Width)/3.0;
  EditDistance->Left = LabelDistance->Left + LabelDistance->Width+(GroupBoxStandard->Width - LabelDistance->Width - EditDistance->Width)/3.0;

  //--------------------------------------GroupBoxCompare-----------------------------------
  GroupBoxCompare->Left = 3;
  GroupBoxCompare->Top = GroupBoxStandard->Top + GroupBoxStandard->Height + 10;
  GroupBoxCompare->Width = RzPanelOperation->Width*0.3;
  GroupBoxCompare->Height =  RzPanelOperation->Height*0.3;

  //Abs

  CheckBoxDD_Abs->Top = (GroupBoxCompare->Height - GroupBoxCompare->TabHeight - 3*CheckBoxDD_Abs->Height)/4.0;
  CheckBoxDTA_Abs->Top = CheckBoxDD_Abs->Top + CheckBoxDD_Abs->Height + (GroupBoxCompare->Height - GroupBoxCompare->TabHeight - 3*CheckBoxDD_Abs->Height)/4.0;
  CheckBoxGamma_Abs->Top = CheckBoxDTA_Abs->Top + CheckBoxDTA_Abs->Height + (GroupBoxCompare->Height - GroupBoxCompare->TabHeight - 3*CheckBoxDD_Abs->Height)/4.0;

  RzButtomCompare_Abs->Height = 0.28*(GroupBoxCompare->Height - GroupBoxCompare->TabHeight);
  RzButtomCompare_Abs->Top = (GroupBoxCompare->Height - GroupBoxCompare->TabHeight - RzButtomCompare_Abs->Height)/2.0;

  CheckBoxDD_Abs->Width = GroupBoxCompare->Width*0.4;
  CheckBoxDTA_Abs->Width = GroupBoxCompare->Width*0.4;
  CheckBoxGamma_Abs->Width = GroupBoxCompare->Width*0.4;
  RzButtomCompare_Abs->Width = GroupBoxCompare->Width*0.5;
  CheckBoxDD_Abs->Left = (GroupBoxCompare->Width - CheckBoxDD_Abs->Width - RzButtomCompare_Abs->Width)/3.0;
  CheckBoxDTA_Abs->Left = (GroupBoxCompare->Width - CheckBoxDTA_Abs->Width - RzButtomCompare_Abs->Width)/3.0;
  CheckBoxGamma_Abs->Left = (GroupBoxCompare->Width - CheckBoxGamma_Abs->Width - RzButtomCompare_Abs->Width)/3.0;

  RzButtomCompare_Abs->Left = CheckBoxDD_Abs->Left + CheckBoxDD_Abs->Width + (GroupBoxCompare->Width - CheckBoxDD_Abs->Width - RzButtomCompare_Abs->Width)/3.0;


  //Relative
  CheckBoxDTA_Rel->Top = (GroupBoxCompare->Height - GroupBoxCompare->TabHeight - 2*CheckBoxDTA_Rel->Height)/3.0;
  CheckBoxGamma_Rel->Top = CheckBoxGamma_Rel->Top + CheckBoxGamma_Rel->Height + (GroupBoxCompare->Height - GroupBoxCompare->TabHeight - 2*CheckBoxDTA_Rel->Height)/3.0;

  RzButtomCompare_Rel->Height = 0.28*(GroupBoxCompare->Height - GroupBoxCompare->TabHeight);
  RzButtomCompare_Rel->Top = (GroupBoxCompare->Height - GroupBoxCompare->TabHeight - RzButtomCompare_Rel->Height)/2.0;

  CheckBoxDTA_Rel->Width = GroupBoxCompare->Width*0.4;
  CheckBoxGamma_Rel->Width = GroupBoxCompare->Width*0.4;
  RzButtomCompare_Rel->Width = GroupBoxCompare->Width*0.5;
  CheckBoxDTA_Rel->Left = (GroupBoxCompare->Width - CheckBoxDTA_Rel->Width - RzButtomCompare_Rel->Width)/3.0;
  CheckBoxGamma_Rel->Left = (GroupBoxCompare->Width - CheckBoxGamma_Rel->Width - RzButtomCompare_Rel->Width)/3.0;

  RzButtomCompare_Rel->Left = CheckBoxDTA_Rel->Left + CheckBoxDTA_Rel->Width + (GroupBoxCompare->Width - CheckBoxDTA_Rel->Width - RzButtomCompare_Rel->Width)/3.0;

  //-------------------------------------Other Buttons-------------------------------------
  GroupBoxOther->Top = GroupBoxCompare->Top +  GroupBoxCompare->Height + 3;
  GroupBoxOther->Left = GroupBoxCompare->Left;
  GroupBoxOther->Width = GroupBoxCompare->Width;
  GroupBoxOther->Height = RzPanelOperation->Height - GroupBoxOther->Top - 6;
  SetInfoBtn->Width = GroupBoxOther->Width*0.4;
  ButtonBest5->Width = GroupBoxOther->Width*0.4;
  SetInfoBtn->Left = (GroupBoxOther->Width - 2*SetInfoBtn->Width)/3.0;
  ButtonBest5->Left = SetInfoBtn->Left + SetInfoBtn->Width + (GroupBoxOther->Width - 2*SetInfoBtn->Width)/3.0;
  SetInfoBtn->Height = GroupBoxOther->Height*0.5;
  ButtonBest5->Height = GroupBoxOther->Height*0.5;
  SetInfoBtn->Top = (GroupBoxOther->Height - SetInfoBtn->Height)/2.0;
  ButtonBest5->Top = SetInfoBtn->Top;
  //-----------------------------MemoResults值设定-------------------------------------------
  TreeResult->Top = 3;
  TreeResult->Left = GroupBoxTypeChange->Left + GroupBoxTypeChange->Width + 5;
  TreeResult->Height = RzPanelOperation->Height*0.75;
  TreeResult->Width = RzPanelOperation->Width*0.36;

  TreeResult->Items->Clear();
  TreeResult->Items->Add(TreeResult->GetNodeAt(0,0),"Check Result");
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\"),"Dose Difference");
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\"),"DTA");
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\"),"Gamma");

  TreeResult->FullExpand();

  //------------------------------MemoDynamicInfo值设定---------------------------------------
  MemoDynamicInfo->Top = TreeResult->Top + TreeResult->Height + 5;
  MemoDynamicInfo->Left = TreeResult->Left;
  MemoDynamicInfo->Height = RzPanelOperation->Height*0.2;
  MemoDynamicInfo->Width = TreeResult->Width;


  //-------------------------------MemoPatientInfo------------------------------------------
  MemoPatientInfo->Top = 3;
  MemoPatientInfo->Left = MemoDynamicInfo->Left + MemoDynamicInfo->Width + 5;
  MemoPatientInfo->Height = RzPanelOperation->Height*0.5;
  MemoPatientInfo->Width = RzPanelOperation->Width - MemoPatientInfo->Left - 5;
  
  MemoPatientInfo->Items->Clear();
  MemoPatientInfo->Items->Add(MemoPatientInfo->GetNodeAt(0,0),"Patient Informations");
  MemoPatientInfo->Items->AddChild(MemoPatientInfo->NodeFromPath("Patient Informations\\"),"ID");
  MemoPatientInfo->Items->AddChild(MemoPatientInfo->NodeFromPath("Patient Informations\\"),"Name");
  MemoPatientInfo->Items->AddChild(MemoPatientInfo->NodeFromPath("Patient Informations\\"),"Angle");
  MemoPatientInfo->Items->AddChild(MemoPatientInfo->NodeFromPath("Patient Informations\\"),"Gender");
  MemoPatientInfo->Items->AddChild(MemoPatientInfo->NodeFromPath("Patient Informations\\"),"Part");
  MemoPatientInfo->FullExpand();

  //------------------------------MemoFilePath----------------------------------------------
  RzMemoMeasureFile->Color = clMoneyGreen;
  RzMemoMeasureFile->Left = MemoPatientInfo->Left;
  RzMemoMeasureFile->Width = MemoPatientInfo->Width;
  RzMemoMeasureFile->Height = 0.7*(RzPanelOperation->Height -  MemoPatientInfo->Height)/2.0;
  RzMemoMeasureFile->Top = MemoPatientInfo->Top + MemoPatientInfo->Height + 7;

  RzMemoCalculateFile->Color = clMoneyGreen;
  RzMemoCalculateFile->Left = MemoPatientInfo->Left;
  RzMemoCalculateFile->Width = RzMemoMeasureFile->Width;
  RzMemoCalculateFile->Height = RzMemoMeasureFile->Height;
  RzMemoCalculateFile->Top = RzMemoMeasureFile->Top + RzMemoMeasureFile->Height + 7;
  //Compare HotPoint Graphy
  ChartMeasureHotPoint->Width = RzPanelHotPoint->Width/2.0;
  ChartCalcHotPoint->Width = RzPanelHotPoint->Width/2.0;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RadioButton1Click(TObject *Sender)  //对第一个图形的相关工具进行设定
{
//  if(TransTag[0]%2==1)  //判断SpeedButtonTrans的状态
//    SpeedButtonTrans->Caption = "图";
//  else
//    SpeedButtonTrans->Caption = "表";
//
//  if(DimTag[0]%2==1)   //判断SpeedButton3D的状态
//    SpeedButton3D->Caption = "3D";
//  else
//    SpeedButton3D->Caption = "2D";
//
//  if(GraphTag[0] == 0)   //判断ComboBoxGraph的状态
//    ComboBoxGraph->Text = "Hotpoint";
//  else if(GraphTag[0] == 1)
//    ComboBoxGraph->Text = "Normal";
//  else
//    ComboBoxGraph->Text = "GraphType";
//
//
//  ComboBoxData->Items->Clear();
//  ComboBoxData->Items->Add(AnsiString("Dose"));   //对DataType下拉菜单进行设定
//  ComboBoxData->Items->Add(AnsiString("Raw"));
//  ComboBoxData->Items->Add(AnsiString("Offset"));
//  ComboBoxData->Items->Add(AnsiString("Normalized"));
//  ComboBoxData->Items->Add(AnsiString("Corrected"));
//  ComboBoxData->Items->Add(AnsiString("Calibration"));
//
//  ComboBoxGraph->Items->Clear();
//  ComboBoxGraph->Items->Add(AnsiString("Hotpoint")); //对GraphType的下拉菜单进行设定
//  ComboBoxGraph->Items->Add(AnsiString("Normal"));
//
//  RadioButton1->Enabled = false;     //去焦点化
//  RadioButton1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RadioButton2Click(TObject *Sender)  //对第二个图形的相关工具进行设定
{
//  if(TransTag[1]%2==1)  //判断SpeedButtonTrans的状态
//    SpeedButtonTrans->Caption = "图";
//  else
//    SpeedButtonTrans->Caption = "表";
//
//  if(DimTag[1]%2==1) //判断SpeedButton3D的状态
//    SpeedButton3D->Caption = "3D";
//  else
//    SpeedButton3D->Caption = "2D";
//
//  if(GraphTag[1] == 0)   //判断ComboBoxGraph的状态
//    ComboBoxGraph->Text = "Hotpoint";
//  else if(GraphTag[1] == 1)
//    ComboBoxGraph->Text = "Normal";
//  else
//    ComboBoxGraph->Text = "GraphType";
//
//  ComboBoxData->Items->Clear();        //对DataType下拉菜单进行设定
//  ComboBoxData->Items->Add(AnsiString("Dose"));
//  ComboBoxData->Items->Add(AnsiString("Normalized"));
//
//  ComboBoxGraph->Items->Clear();      //对GraphType的下拉菜单进行设定
//  ComboBoxGraph->Items->Add(AnsiString("Hotpoint"));
//  ComboBoxGraph->Items->Add(AnsiString("Normal"));
//
//  RadioButton2->Enabled = false;    //去焦点
//  RadioButton2->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RadioButton3Click(TObject *Sender) //对第三个图形的相关工具进行设定
{
//  if(TransTag[2]%2==1)  //判断SpeedButtonTrans的状态
//    SpeedButtonTrans->Caption = "图";
//  else
//    SpeedButtonTrans->Caption = "表";
//
//  if(DimTag[2]%2==1)    //判断SpeedButton3D的状态
//    SpeedButton3D->Caption = "3D";
//  else
//    SpeedButton3D->Caption = "2D";
//
//  if(GraphTag[2] == 0)   //判断ComboBoxGraph的状态
//    ComboBoxGraph->Text = "Hotpoint";
//  else if(GraphTag[2] == 1)
//    ComboBoxGraph->Text = "Normal";
//  else
//    ComboBoxGraph->Text = "GraphType";
//
//  ComboBoxData->Items->Clear();        //对DataType下拉菜单进行设定
//  ComboBoxData->Items->Add(AnsiString("Dose"));
//  ComboBoxData->Items->Add(AnsiString("Normalized"));
//
//  ComboBoxGraph->Items->Clear();      //对GraphType的下拉菜单进行设定
//  ComboBoxGraph->Items->Add(AnsiString("Hotpoint"));
//  ComboBoxGraph->Items->Add(AnsiString("Normal"));
//
//  RadioButton3->Enabled = false;    //去焦点
//  RadioButton3->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonTransforMeasureClick(TObject *Sender)
{

  if(!temporaryValues.measureFilePath.empty() && !temporaryValues.NormMeasureDoseData.isEmpty()){

    if(false==temporaryValues.measureDataShowTag.status()){
      SpeedButtonTransforMeasure->Caption = "G";
      StringGridMeasure->Visible = true;
      ChartMeasure->Visible = false;
    }
    else{
      SpeedButtonTransforMeasure->Caption = "T";
      StringGridMeasure->Visible = false;
      ChartMeasure->Visible = true;
    }

    StringGridMeasure->Top = ChartMeasure->Top;
    StringGridMeasure->Width = ChartMeasure->Width;

    StringGridMeasure->RowCount = temporaryValues.measureColLength + 1;
    StringGridMeasure->ColCount = temporaryValues.measureRowLength + 1; //设置StringGrid的行数和列数
  
    //设置行和列的坐标:0行，0列
    //Cells[ACol][ARow]
    for(int i=0;i<temporaryValues.measureRowLength;i++){
      StringGridMeasure->Cells[i+1][0] = FormatFloat("0.000",i*temporaryValues.gridSize[0] - temporaryValues.measureDoseCentral.x);
    }

    for(int j=0;j<temporaryValues.measureColLength;j++){
      StringGridMeasure->Cells[0][j+1] = FormatFloat("0.000",j*temporaryValues.gridSize[1] - temporaryValues.measureDoseCentral.y);
    }


    for(int j=0;j<temporaryValues.measureColLength;j++){
      for(int i=0;i<temporaryValues.measureRowLength;i++){
        StringGridMeasure->Cells[i+1][j+1] = FormatFloat("0.0000",temporaryValues.NormMeasureDoseData.at(i,j,0));
      }
    }


    temporaryValues.measureDataShowTag.trans();

  }

}



string __fastcall TFormMain::getTreeViewPathTrim(string path,char split){
   int lastPos = path.find_last_of(split);
   path = path.substr(0,lastPos);
   lastPos = path.find_last_of(split);
   return path.substr(lastPos+1,path.length()-1);
}

string __fastcall TFormMain::getAngleFromTreeViewPath(string path){
   string subStr = getTreeViewPathTrim(path,'\\');
   string minus = "Angle:";
   return subStr.erase(0,minus.length());
}

void __fastcall TFormMain::groupsClick(TObject* Sender){
  TRzTreeView* treeView = (TRzTreeView*)Sender;
  int index = treeView->Tag;
  
  TTreeNode *node = treeView->Items->GetFirstNode();
  while(NULL != node){
    if(node->Selected){
      if(getTreeViewPathTrim(treeView->PathFromNode(node).c_str(),'\\') == "Measure" ||
         getTreeViewPathTrim(treeView->PathFromNode(node).c_str(),'\\') == "Calculate"){

        flushFromCache(index,getAngleFromTreeViewPath(treeView->PathFromNode(node->Parent).c_str()));
      }
      break;
    }
    node = node->GetNext();
  }

}

void __fastcall TFormMain::flushFromCache(int index,string angle){
  int choose = MessageDlg("Are you sure to use cache data to overload the current data?",mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0);

  if( mrNo == choose){
    return;
  }

  GlobalMembers* globalMem = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  globalMem->flushFromCache(index,angle);

  /*Refresh the current display dose*/
  RefreshMeasureDoseGraphicFromDisplayValue();

  RefreshCalculateDoseGraphicFromDisplayValue();

  globalMem = NULL;
}

//---------------------Show Cache------------------------------------------
void __fastcall TFormMain::ShowPatientCache(){
  //Clean groups before show the news
  cleanGroupBars();

  Cache* theCacheInstance = NULL;
  deque<PatientData>* theCacheDque = NULL;

  ostringstream os;
  os.str("");

  int count = 0;

  theCacheInstance = Cache::getCacheInstance();
  if(NULL == theCacheInstance){
    RunningLog::writeLog("The Cache is NULL",__LINE__);
    return;
  }

  theCacheDque = theCacheInstance->getPatientDateDque();

  if(NULL == theCacheDque){
    RunningLog::writeLog("The Cache Dque is NULL",__LINE__);
    return;
  }

  for(deque<PatientData>::iterator itera = theCacheDque->begin();itera != theCacheDque->end();itera++){
    os.str(""); //clean os
    
    this->groupDeque.push_back(new TRzGroup(this));
    this->groupDeque.back()->Parent = this->RzGroupBarCache;
    this->groupDeque.back()->Show();

    //no-meaning:just use these Items to adjust(expand) the groupBar windows
    this->groupDeque.back()->Items->Add();
    this->groupDeque.back()->Items->Add();
    this->groupDeque.back()->Items->Add();
    this->groupDeque.back()->Items->Add();

    this->groupDeque.back()->CanClose = true;
    os<<"ID:"<<itera->getBaseInfo()->patientId;
    this->groupDeque.back()->Caption = os.str().c_str();
    os.str(""); //clean os

    this->treeViewInGroupDeque.push_back(new TRzTreeView(this));
    this->treeViewInGroupDeque.back()->Parent = this->groupDeque.back();
    this->treeViewInGroupDeque.back()->Align = alClient;
    this->treeViewInGroupDeque.back()->Font->Name = "Times New Roman";
    this->treeViewInGroupDeque.back()->Color = clMoneyGreen;
    this->treeViewInGroupDeque.back()->FrameStyle = fsFlat;
    this->treeViewInGroupDeque.back()->Tag = count;

    this->treeViewInGroupDeque.back()->OnDblClick = groupsClick; //Register the DbClick event
    
    this->treeViewInGroupDeque.back()->FrameVisible = true;
    this->treeViewInGroupDeque.back()->ReadOnly = true;
    this->treeViewInGroupDeque.back()->Font;

    RzGroupBarCache->AddGroup(this->groupDeque.back());

    this->treeViewInGroupDeque.back()->Items->Add(this->treeViewInGroupDeque.back()->GetNodeAt(0,0),itera->getBaseInfo()->patientName.c_str());

    for(map<string,DosePair>::iterator anglePairMapIterat = itera->getDataMap()->begin();anglePairMapIterat != itera->getDataMap()->end();anglePairMapIterat++){
      os.str("");

      os<<"Angle:"<<anglePairMapIterat->first;
      this->treeViewInGroupDeque.back()->Items->AddChild(this->treeViewInGroupDeque.back()->NodeFromPath(itera->getBaseInfo()->patientName.c_str()),os.str().c_str());

      //no-meaning:just use these Items to adjust(expand) the groupBar windows
      this->groupDeque.back()->Items->Add();

      os.str("");

      os<<itera->getBaseInfo()->patientName<<"\\"<<"Angle:"<<anglePairMapIterat->first<<"\\";
      if(NULL != anglePairMapIterat->second.getMeasureDose()){
        this->treeViewInGroupDeque.back()->Items->AddChild(this->treeViewInGroupDeque.back()->NodeFromPath(os.str().c_str()),"Measure");
      }

      if(NULL != anglePairMapIterat->second.getCalculateDose()){
        this->treeViewInGroupDeque.back()->Items->AddChild(this->treeViewInGroupDeque.back()->NodeFromPath(os.str().c_str()),"Calculate");
      }
      
    }

    this->treeViewInGroupDeque.back()->FullExpand();

    count++;
  }

  theCacheInstance = NULL;
  theCacheDque = NULL;

}
//--------------------------------清除GroupCacheBar-------------------------------------
void __fastcall TFormMain::cleanGroupBars(){
   for(deque<TRzTreeView*>::iterator iterat = this->treeViewInGroupDeque.begin();iterat != this->treeViewInGroupDeque.end();){
     //(*iterat)->Free(); //Note: Do not delete this before the correlate group was deleted.!!!!!
     iterat = this->treeViewInGroupDeque.erase(iterat);
   }

  for(deque<TRzGroup*>::iterator iterat = this->groupDeque.begin();iterat != this->groupDeque.end();){
    (*iterat)->Free();
    iterat = this->groupDeque.erase(iterat);
  }

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonTransforCalculateClick(TObject *Sender)
{
  if(!temporaryValues.calcFilePath.empty() && !temporaryValues.NormCalcDoseData.isEmpty()){

    if(false==temporaryValues.calcDataShowTag.status()){
      SpeedButtonTransforCalculate->Caption = "G";
      StringGridCalculate->Visible = true;
      ChartCalculate->Visible = false;
    }
    else{
      SpeedButtonTransforCalculate->Caption = "T";
      StringGridCalculate->Visible = false;
      ChartCalculate->Visible = true;
    }

    StringGridCalculate->Top = ChartCalculate->Top;
    StringGridCalculate->Width = ChartCalculate->Width;

    StringGridCalculate->RowCount = temporaryValues.cutBian.at(1,1,0) - temporaryValues.cutBian.at(1,0,0) + 1 + 1;
    StringGridCalculate->ColCount = temporaryValues.cutBian.at(0,1,0) - temporaryValues.cutBian.at(0,0,0) + 1 + 1; //设置StringGrid的行数和列数

    //设置行和列的坐标:0行，0列
    //Cells[ACol][ARow]


    for(int i=temporaryValues.cutBian.at(0,0,0);i<=temporaryValues.cutBian.at(0,1,0);i++){
      StringGridCalculate->Cells[i- temporaryValues.cutBian.at(0,0,0) + 1][0] = FormatFloat("0.0000",i*temporaryValues.gridSize[0]/temporaryValues.segments[0] - temporaryValues.calcDoseCentral.x);
    }


    for(int j=temporaryValues.cutBian.at(1,0,0);j<=temporaryValues.cutBian.at(1,1,0);j++){
      StringGridCalculate->Cells[0][j - temporaryValues.cutBian.at(1,0,0) + 1] = FormatFloat("0.0000",j*temporaryValues.gridSize[1]/temporaryValues.segments[1] - temporaryValues.calcDoseCentral.y);
    }



    for(int j=temporaryValues.cutBian.at(1,0,0);j<=temporaryValues.cutBian.at(1,1,0);j++){
      for(int i=temporaryValues.cutBian.at(0,0,0);i<=temporaryValues.cutBian.at(0,1,0);i++){
        StringGridCalculate->Cells[i- temporaryValues.cutBian.at(0,0,0) + 1][j - temporaryValues.cutBian.at(1,0,0) + 1]
             = FormatFloat("0.0000",temporaryValues.NormCalcDoseData.at(i,j,0));
      }
    }

    temporaryValues.calcDataShowTag.trans();

  }

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EditTHButtonClick(TObject *Sender,
      TSpinButtonType Button)
{
  EditTH->ShowHint = true;
  SetStandardAndTH();
  EditTH->Enabled = false;
  EditTH->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EditTHChange(TObject *Sender)
{
  SetStandardAndTH();
  EditTH->Enabled = false;
  EditTH->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::EditTHEnter(TObject *Sender)
{
  EditTH->ShowHint = true;        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EditDoseGapButtonClick(TObject *Sender,
      TSpinButtonType Button)
{
  EditDoseGap->ShowHint = true;
  SetStandardAndTH();
  EditDoseGap->Enabled = false;
  EditDoseGap->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::EditDoseGapChange(TObject *Sender)
{
  SetStandardAndTH();
  EditDoseGap->Enabled = false;
  EditDoseGap->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::EditDoseGapEnter(TObject *Sender)
{
  EditDoseGap->ShowHint = true;        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EditDistanceButtonClick(TObject *Sender,
      TSpinButtonType Button)
{
  EditDistance->ShowHint = true;
  SetStandardAndTH();
  EditDistance->Enabled = false;
  EditDistance->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::EditDistanceChange(TObject *Sender)
{
  SetStandardAndTH();
  EditDistance->Enabled = false;
  EditDistance->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::EditDistanceEnter(TObject *Sender)
{
  EditDistance->ShowHint = true;        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SpeedButton3DClick(TObject *Sender)
{
//  int i,j,tt;
//
//  if(RadioButton1->Checked == true&&filename1!="")
//  {
//    Chart1->DoubleBuffered = true;
//    DimTag[0]++;   //用DimTag[0]来记录第一个图对应的SpeedButton3D被点击的状态
//    if(DimTag[0]%2==1)    //对应2D图形
//    {
//      TeeOpenGL1->Active = false;
//      for(j=0;j<alinenumx;j++)
//      {
//        agridlinex[j]->LinePen->Color = clSilver;
//      }
//
//      for(i=0;i<alinenumy;i++)
//      {
//        agridliney[i]->LinePen->Color = clSilver;
//      }
//
//
//      SpeedButton3D->Caption = "3D";
//      Chart1->LeftAxis->StartPosition = 0;
//      Chart1->LeftAxis->EndPosition = 0; //通过将所有点压缩到底面来实现向2D转化
//      SeriesA->YPositionLevel = false;
//      Chart1->View3DOptions->Rotation = 0; //通过将Chart旋转到一个固定角度，使网
//      Chart1->View3DOptions->Elevation = 270;  //格和轴有2D效果
//      RotateTool1->Active = false;   //2D时设为不可旋转
//      DetTag[0] = 0;  //从3D转向2D时，将探测器按钮SpeedButtonDet状态置零
//
//      //由于在图像为2D时设置了TeeOpenGL1->Active = false，所以2D时无法放大，所以需要采用别的方法
//      //需要判断放大之后Panel1放大了多少倍，从而将Chart1进行等比放大
//      //为了在放大状态下进行2D/3D转换时能保持正常，需要进行放大倍数的2D/3D切换
//
//      //取宽/高放大倍数中较小者作为Chart放大倍数的修正
//      float thezoom = min<float>(Panel1->Height/StoreHeight,Panel1->Width/StoreWidth);
//      //进行thezoom修正
//      Chart1->View3DOptions->Zoom = thezoom*0.83*100*504.0/float(Panel1->Width);
//    }
//    else
//    {
//      Chart1->DoubleBuffered = true;     //在有探测器(Label)的情况下，由2D向3D转化之前必须要双缓冲DoubleBuffer，否则会黑屏
//      TeeOpenGL1->Active = true;
//      for(j=0;j<alinenumx;j++)
//      {
//        agridlinex[j]->LinePen->Color = clWhite;
//      }
//
//      for(i=0;i<alinenumy;i++)
//      {
//        agridliney[i]->LinePen->Color = clWhite;
//      }
//
//
//      SpeedButton3D->Caption = "2D";
//      SeriesA->YPositionLevel = true;
//      RotateTool1->Active = true;
//      Chart1->LeftAxis->StartPosition = 20; //恢复成3D(同时向上向下20，对称压缩成60%)
//      Chart1->LeftAxis->EndPosition = 80 ;
//
//
//      //由于在图像为3D时设置了TeeOpenGL1->Active = true，Chart可以正常放大，因此只需要
//      //Chart1的进行正常的放大就可以了
//      //为了在放大状态下进行2D/3D转换时能保持正常，需要进行放大倍数的2D/3D切换
//
//      //3D时进行thezoom还原
//      Chart1->View3DOptions->Zoom = 0.83*100*504.0/float(Panel1->Width);
//
//    }
//  }
//
//  if(RadioButton2->Checked == true&&filename2!="")
//  {
//    DimTag[1]++;   //用DimTag[1]来记录第二个图对应的SpeedButton3D被点击的状态
//    if(DimTag[1]%2==1)    //对应2D图形
//    {
//      for(j=0;j<blinenumx;j++)
//      {
//        bgridlinex[j]->LinePen->Color = clSilver;
//      }
//
//      for(i=0;i<blinenumy;i++)
//      {
//        bgridliney[i]->LinePen->Color = clSilver;
//      }
//
//      TeeOpenGL2->Active = false;
//      SpeedButton3D->Caption = "3D";
//      Chart2->LeftAxis->StartPosition = 0;
//      Chart2->LeftAxis->EndPosition = 0; //通过将所有点压缩到底面来实现向2D转化
//      SeriesB->YPositionLevel = false;
//      Chart2->View3DOptions->Rotation = 0; //通过将Chart旋转到一个固定角度，使网
//      Chart2->View3DOptions->Elevation = 270;  //格和轴有2D效果
//      RotateTool2->Active = false;   //2D时设为不可旋转
//      DetTag[1] = 0;  //从3D转向2D时，将探测器按钮SpeedButtonDet状态置零
//    }
//    else
//    {
//      for(j=0;j<blinenumx;j++)
//      {
//        bgridlinex[j]->LinePen->Color = clWhite;
//      }
//
//      for(i=0;i<blinenumy;i++)
//      {
//        bgridliney[i]->LinePen->Color = clWhite;
//      }
//
//      TeeOpenGL2->Active = true;
//      SpeedButton3D->Caption = "2D";
//      SeriesB->YPositionLevel = true;
//      RotateTool2->Active = true;
//      Chart2->LeftAxis->StartPosition = 20;
//      Chart2->LeftAxis->EndPosition = 80;  //恢复成3D(同时向上向下20，对称压缩成60%)
//    }
//  }
//
//  if(RadioButton3->Checked == true&&cstatue==1)
//  {
//    DimTag[2]++;   //用DimTag[2]来记录第三个图对应的SpeedButton3D被点击的状态
//    if(DimTag[2]%2==1)    //对应2D图形
//    {
//      for(j=0;j<alinenumx;j++)
//      {
//        //cgridlinex[j]->LinePen->Color = clSilver;
//      }
//
//      for(i=0;i<alinenumy;i++)
//      {
//        //cgridliney[i]->LinePen->Color = clSilver;
//      }
//
//      //TeeOpenGL3->Active = false;
//      SpeedButton3D->Caption = "3D";
//      //Chart3->LeftAxis->StartPosition = 0;
//      //Chart3->LeftAxis->EndPosition = 0; //通过将所有点压缩到底面来实现向2D转化
////      SeriesCa->YPositionLevel = false;
////      SeriesCb->YPositionLevel = false;  //用YPositionLevel来进行等高图的2D/3D转换
////      Chart3->View3DOptions->Rotation = 0; //通过将Chart旋转到一个固定角度，使网
////      Chart3->View3DOptions->Elevation = 270;  //格和轴有2D效果
////      RotateTool3->Active = false;   //2D时设为不可旋转
//      DetTag[2] = 0;  //从3D转向2D时，将探测器按钮SpeedButtonDet状态置零
//    }
//    else
//    {
//      for(j=0;j<alinenumx;j++)
//      {
////        cgridlinex[j]->LinePen->Color = clWhite;
//      }
//
//      for(i=0;i<alinenumy;i++)
//      {
////        cgridliney[i]->LinePen->Color = clWhite;
//      }
//
////      TeeOpenGL3->Active = true;
//      SpeedButton3D->Caption = "2D";
////      SeriesCa->YPositionLevel = true;
////      SeriesCb->YPositionLevel = true;
////      RotateTool3->Active = true;
////      Chart3->LeftAxis->StartPosition = 20;
////      Chart3->LeftAxis->EndPosition = 80;  //恢复成3D(同时向上向下20，对称压缩成60%)
//    }
//  }
}
//--------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButton3DMeasureClick(TObject *Sender)
{
  if(!temporaryValues.measureFilePath.empty())
  {
    
    if(false==temporaryValues.measureDimensionTransTag.status())    //对应2D图形
    {
      TeeOpenGLMeasure->Active = false;
      for(int j=0;j<agridlinex.Length;j++)
      {
        agridlinex[j]->LinePen->Color = clSilver;
      }

      for(int i=0;i<agridliney.Length;i++)
      {
        agridliney[i]->LinePen->Color = clSilver;
      }


      SpeedButton3DMeasure->Caption = "3D";
      ChartMeasure->LeftAxis->StartPosition = 0;
      ChartMeasure->LeftAxis->EndPosition = 0; //通过将所有点压缩到底面来实现向2D转化
      SeriesA->YPositionLevel = false;
      ChartMeasure->View3DOptions->Rotation = 0; //通过将Chart旋转到一个固定角度，使网
      ChartMeasure->View3DOptions->Elevation = 270;  //格和轴有2D效果
      RotateTool1->Active = false;   //2D时设为不可旋转
      temporaryValues.detectorsShownTag.reset();  //从3D转向2D时，将探测器按钮SpeedButtonDet状态置零

      //由于在图像为2D时设置了TeeOpenGL1->Active = false，所以2D时无法放大，所以需要采用别的方法
      //需要判断放大之后Panel1放大了多少倍，从而将Chart1进行等比放大
      //为了在放大状态下进行2D/3D转换时能保持正常，需要进行放大倍数的2D/3D切换


      //进行thezoom修正
      ChartMeasure->View3DOptions->Zoom = 0.83*100*504.0/float(PanelMeasure->Width);
      temporaryValues.measureDimensionTransTag.trans();;
    }
    else
    {
      TeeOpenGLMeasure->Active = true;
      for(int j=0;j<agridlinex.Length;j++)
      {
        agridlinex[j]->LinePen->Color = clWhite;
      }

      for(int i=0;i<agridliney.Length;i++)
      {
        agridliney[i]->LinePen->Color = clWhite;
      }


      SpeedButton3DMeasure->Caption = "2D";
      SeriesA->YPositionLevel = true;
      RotateTool1->Active = true;
      ChartMeasure->LeftAxis->StartPosition = 20; //恢复成3D(同时向上向下20，对称压缩成60%)
      ChartMeasure->LeftAxis->EndPosition = 80 ;

      //由于在图像为3D时设置了TeeOpenGL1->Active = true，Chart可以正常放大，因此只需要
      //Chart1的进行正常的放大就可以了
      //为了在放大状态下进行2D/3D转换时能保持正常，需要进行放大倍数的2D/3D切换

      //3D时进行thezoom还原
      ChartMeasure->View3DOptions->Zoom = 0.83*100*504.0/float(PanelMeasure->Width);
      temporaryValues.measureDimensionTransTag.trans();

    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButton3DCalculateClick(TObject *Sender)
{

  if(!temporaryValues.calcFilePath.empty())
  {
    
    if(false==temporaryValues.calcDimensionTransTag.status())    //对应2D图形
    {
      for(int j=0;j<bgridlinex.Length;j++)
      {
        bgridlinex[j]->LinePen->Color = clSilver;
      }

      for(int i=0;i<bgridliney.Length;i++)
      {
        bgridliney[i]->LinePen->Color = clSilver;
      }

      TeeOpenGLCalculate->Active = false;
      SpeedButton3DCalculate->Caption = "3D";
      ChartCalculate->LeftAxis->StartPosition = 0;
      ChartCalculate->LeftAxis->EndPosition = 0; //通过将所有点压缩到底面来实现向2D转化
      SeriesB->YPositionLevel = false;
      ChartCalculate->View3DOptions->Rotation = 0; //通过将Chart旋转到一个固定角度，使网
      ChartCalculate->View3DOptions->Elevation = 270;  //格和轴有2D效果
      RotateTool2->Active = false;   //2D时设为不可旋转
      temporaryValues.detectorsShownTag.reset();  //从3D转向2D时，将探测器按钮SpeedButtonDet状态置零

      temporaryValues.calcDimensionTransTag.trans();
    }
    else
    {
      for(int j=0;j<bgridlinex.Length;j++)
      {
        bgridlinex[j]->LinePen->Color = clWhite;
      }

      for(int i=0;i<bgridliney.Length;i++)
      {
        bgridliney[i]->LinePen->Color = clWhite;
      }

      TeeOpenGLCalculate->Active = true;
      SpeedButton3DCalculate->Caption = "2D";
      SeriesB->YPositionLevel = true;
      RotateTool2->Active = true;
      ChartCalculate->LeftAxis->StartPosition = 20;
      ChartCalculate->LeftAxis->EndPosition = 80;  //恢复成3D(同时向上向下20，对称压缩成60%)

      temporaryValues.calcDimensionTransTag.trans();
    }
  }

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonDetClick(TObject *Sender)
{
//  int i,j,er,ii,jj;
//
//  Chart1->DoubleBuffered = true;
//
//  if(RadioButton1->Checked==true&&filename1!=""&&DimTag[0]%2==1)  //第一幅图且有图且2D情况才有探测器的显示
//  {
//    DetTag[0]++;    //用DetTag[0]来记录第一个图对应的SpeedButtonDet被点击的状态
//
//    if(DetTag[0]%2==1)  //对应显示
//    { /*
//      SeriesADet->Clear();
//      for(j=0;j<=aydir;j++)
//      {
//        for(i=0;i<=axdir;i++)
//        {
//          if(detector[j][i]==1)
//            SeriesADet->AddXYZ(axorigin-i-1,0,j-ayorigin+1);
//        }
//      }
//
//      SeriesADet->Pointer->HorizSize = 3;  //设置格点的长和高
//      SeriesADet->Pointer->VertSize = 1;
//      SeriesADet->DepthSize = 0.3; //DepthSize是按照DepthAxis的尺度为单位，设定格点的深度
//
//      */
//
//
//      int centerz;
//      if(Chart1->ClientHeight%2==1){
//        centerz = (Chart1->ClientHeight+1)/2;
//      }else{
//       centerz = (Chart1->ClientHeight)/2;
//      }
//
//      switch(recordfiletype)
//      {
//        case 0:  //MapCheck类型
//        {
//          jj=0;
//          for(i=SeriesA->MinXValue();i<=SeriesA->MaxXValue();i++)
//          {
//            ii=0;
//            for(j=SeriesA->MinZValue();j<=SeriesA->MaxZValue();j++)
//            {
//
//
//              if(detector[ii][jj]==1)
//              {
//                TheDector[ii][jj]->Left = (SeriesA->CalcXPosValue(i) - Chart1->Canvas->XCenter)*Chart1->View3DOptions->Zoom/100.0 + Chart1->Canvas->XCenter + 0.5-1;
//                TheDector[ii][jj]->Top =  (Chart1->DepthAxis->CalcPosValue(-j) - Chart1->DepthAxis->CalcPosValue(0) )*Chart1->View3DOptions->Zoom/100.0 +centerz + 0.5-1;
//
//
//                TheDector[ii][jj]->Show();
//
//                TheDector[ii][jj]->OnClick = DetClicked;
//                TheDector[ii][jj]->Visible = true;
//              }
//              ii++;
//            }
//            jj++;
//          }
//
//        }
//        break;
//
//        case 2:      //中测数据类型
//        {
//          jj=0;
//          for(i=SeriesA->MinXValue();i<=SeriesA->MaxXValue();i++)
//          {
//            ii=0;
//            for(j=SeriesA->MinZValue();j<=SeriesA->MaxZValue();j++)
//            {
//
//
//              if(detector[ii][jj]==1)
//              {
//                TheDector[ii][jj]->Left = (SeriesA->CalcXPosValue(i) - Chart1->Canvas->XCenter)*Chart1->View3DOptions->Zoom/100.0 + Chart1->Canvas->XCenter + 0.5-1;
//                TheDector[ii][jj]->Top =  (Chart1->DepthAxis->CalcPosValue(-j) - Chart1->DepthAxis->CalcPosValue(-0.5) )*Chart1->View3DOptions->Zoom/100.0 +centerz + 0.5-1;
//
//                TheDector[ii][jj]->Show();
//                TheDector[ii][jj]->Color = clGreen;
//
//                TheDector[ii][jj]->OnClick = DetClicked;
//                TheDector[ii][jj]->Visible = true;
//
//              }
//              ii++;
//            }
//            jj++;
//          }
//
//        }
//        break;
//
//        default:
//          break;
//      }
//    }
//    else
//    {
//       jj=0;
//       for(j=SeriesA->MinXValue();j<=SeriesA->MaxXValue();j++)
//       {
//        ii=0;
//        for(i=SeriesA->MinZValue();i<=SeriesA->MaxZValue();i++)
//        {
//            if(detector[ii][jj]==1){
//
//              TheDector[ii][jj]->Visible = false;
//              TheDector[ii][jj]->Hide();
//           }
//           ii++;
//         }
//         jj++;
//
//       }
//
//    }
//  }
//
//  if(RadioButton2->Checked==true&&filename2!=""&&DimTag[1]%2==1)  //第二幅图且有图且2D情况才有探测器的显示
//  {
//    /*
//    DetTag[1]++;    //用DetTag[1]来记录第二个图对应的SpeedButtonDet被点击的状态
//
//    if(DetTag[1]%2==1)  //对应显示
//    {
//      SeriesBDet->Clear();
//      for(j=0;j<=ydir;j++)
//      {
//        for(i=0;i<=xdir;i++)
//        {
//          if(detector[j][i]==1)
//            SeriesBDet->AddXYZ(i+1-axorigin,0,j-ayorigin+1);
//        }
//      }
//
//      SeriesBDet->Pointer->HorizSize = 3;  //设置格点的长和高
//      SeriesBDet->Pointer->VertSize = 1;
//      SeriesBDet->DepthSize = 0.3; //DepthSize是按照DepthAxis的尺度为单位，设定格点的深度
//    }
//    else
//    {
//      SeriesBDet->Clear();
//    } */
//  }
//
//  if(RadioButton3->Checked==true&&cstatue==1&&DimTag[2]%2==1)  //第三幅图且有图且2D情况才有探测器的显示
//  {
//    /*
//    DetTag[2]++;    //用DetTag[2]来记录第三个图对应的SpeedButtonDet被点击的状态
//
//    if(DetTag[2]%2==1)  //对应显示
//    {
//      SeriesCDet->Clear();
//      for(j=0;j<=ydir;j++)
//      {
//        for(i=0;i<=xdir;i++)
//        {
//          if(detector[j][i]==1)
//            SeriesCDet->AddXYZ(i+1-axorigin,0,j-ayorigin+1);
//        }
//      }
//
//      SeriesCDet->Pointer->HorizSize = 3;  //设置格点的长和高
//      SeriesCDet->Pointer->VertSize = 1;
//      SeriesCDet->DepthSize = 0.3; //DepthSize是按照DepthAxis的尺度为单位，设定格点的深度
//    }
//    else
//    {
//      SeriesCDet->Clear();
//    }*/
//  }

}
//--------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonDetMeasureClick(TObject *Sender)
{
  int ii,jj;
  int centerz;
  int aleft,atop;
  double centerXOffSet;
  double centerYOffSet;
  if(!temporaryValues.measureFilePath.empty()&&true==temporaryValues.measureDimensionTransTag.status())  //第一幅图有图，且为2D状态
  {
    if(false==temporaryValues.detectorsShownTag.status())
    {
      temporaryValues.detectorsShownTag.trans();

      if(ChartMeasure->ClientHeight%2==1){
        centerz = (ChartMeasure->ClientHeight+1)/2;
      }else{
       centerz = (ChartMeasure->ClientHeight)/2;
      }

      centerXOffSet = temporaryValues.measureArrayShowCenter.row - (temporaryValues.measureRowLength-1)/2.0;
      centerYOffSet = temporaryValues.measureArrayShowCenter.col - (temporaryValues.measureColLength-1)/2.0 ;

      ChartMeasure->Canvas->Brush->Color = clGreen;  //探测器颜色设为绿色

      jj=0;
      for(int i=SeriesA->MinXValue();i<=SeriesA->MaxXValue();i++)
      {
        ii=0;
        for(int j=SeriesA->MinZValue();j<=SeriesA->MaxZValue();j++)
        {
          if(true==temporaryValues.detectorArray.at(ii,jj,0))
          {
            aleft = (SeriesA->CalcXPosValue(i) - ChartMeasure->Canvas->XCenter)*ChartMeasure->View3DOptions->Zoom/100.0 + ChartMeasure->Canvas->XCenter + 0.5-1;
            atop = (ChartMeasure->DepthAxis->CalcPosValue(-j) - ChartMeasure->DepthAxis->CalcPosValue(centerYOffSet) )*ChartMeasure->View3DOptions->Zoom/100.0 +centerz + 0.5-1;

            TRect rect(aleft,atop,aleft+3,atop+3);
            ChartMeasure->Canvas->FillRect(rect);
          }
          ii++;
        }
        jj++;
      }

    }
    else
    {
      ChartMeasure->Refresh();      //只要Refresh()一下，在Chart的Canvas上画的矩形都会消失

      temporaryValues.detectorsShownTag.trans();

    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonDetCalculateClick(TObject *Sender)
{
  //
  SpeedButtonDetMeasure->Click();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonGridClick(TObject *Sender)
{
//  int i,j;
//  if(RadioButton1->Checked == true&&filename1!="")
//  {
//    LineTag[0]++;   //用LineTag[0]来记录第一个图对应的SpeedButtonGrid被点击的状态
//    if(LineTag[0]%2==1) //不显示网格
//    {
//      for(i=0;i<alinenumy;i++)
//      {
//        agridliney[i]->Visible = false;
//      }
//
//      for(j=0;j<alinenumx;j++)
//      {
//        agridlinex[j]->Visible = false;
//      }
//    }
//    else
//    {
//      for(i=0;i<alinenumy;i++)
//      {
//        agridliney[i]->Visible = true;
//      }
//
//      for(j=0;j<alinenumx;j++)
//      {
//        agridlinex[j]->Visible = true;
//      }
//    }
//  }
//
//  if(RadioButton2->Checked == true&&filename2!="")
//  {
//    LineTag[1]++;   //用LineTag[1]来记录第二个图对应的SpeedButtonGrid被点击的状态
//    if(LineTag[1]%2==1) //不显示网格
//    {
//      for(i=0;i<blinenumy;i++)
//      {
//        bgridliney[i]->Visible = false;
//      }
//
//      for(j=0;j<blinenumx;j++)
//      {
//        bgridlinex[j]->Visible = false;
//      }
//    }
//    else
//    {
//      for(i=0;i<blinenumy;i++)
//      {
//        bgridliney[i]->Visible = true;
//      }
//
//      for(j=0;j<blinenumx;j++)
//      {
//        bgridlinex[j]->Visible = true;
//      }
//    }
//  }
//
//  if(RadioButton3->Checked == true&&cstatue==1)
//  {
//    LineTag[2]++;   //用LineTag[2]来记录第三个图对应的SpeedButtonGrid被点击的状态
//    if(LineTag[2]%2==1) //不显示网格
//    {
//      for(i=0;i<alinenumy;i++)
//      {
////        cgridliney[i]->Visible = false;
//      }
//
//      for(j=0;j<alinenumx;j++)
//      {
////        cgridlinex[j]->Visible = false;
//      }
//    }
//
//    else
//    {
//      for(i=0;i<alinenumy;i++)
//      {
////        cgridliney[i]->Visible = true;
//      }
//
//      for(j=0;j<alinenumx;j++)
//      {
////        cgridlinex[j]->Visible = true;
//      }
//    }
//  }
}

//--------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonGridMeasureClick(TObject *Sender)
{
  if(!temporaryValues.measureFilePath.empty())
  {
    if(false==temporaryValues.measureGridLineTag.status()) //不显示网格
    {
      for(int i=0;i<agridliney.Length;i++)
      {
        agridliney[i]->Visible = false;
      }

      for(int j=0;j<agridlinex.Length;j++)
      {
        agridlinex[j]->Visible = false;
      }

      temporaryValues.measureGridLineTag.trans();
    }
    else
    {
      for(int i=0;i<agridliney.Length;i++)
      {
        agridliney[i]->Visible = true;
      }

      for(int j=0;j<agridlinex.Length;j++)
      {
        agridlinex[j]->Visible = true;
      }

      temporaryValues.measureGridLineTag.trans();
    }
  }
 
}
//--------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonGridCalculateClick(TObject *Sender)
{
  if(!temporaryValues.calcFilePath.empty())
  {
    if(false==temporaryValues.calcGridLineTag.status()) //不显示网格
    {
      for(int i=0;i<bgridliney.Length;i++)
      {
        bgridliney[i]->Visible = false;
      }

      for(int j=0;j<bgridlinex.Length;j++)
      {
        bgridlinex[j]->Visible = false;
      }

      temporaryValues.calcGridLineTag.trans();
    }
    else
    {
      for(int i=0;i<bgridliney.Length;i++)
      {
        bgridliney[i]->Visible = true;
      }

      for(int j=0;j<bgridlinex.Length;j++)
      {
        bgridlinex[j]->Visible = true;
      }

      temporaryValues.calcGridLineTag.trans();
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ComboBoxGraphChange(TObject *Sender)
{
  if(!temporaryValues.measureFilePath.empty())
  {
    if(ComboBoxGraph->ItemIndex == 0) //灰度图
    {
      if(false==temporaryValues.measureDimensionTransTag.status())  //默认灰度图只在2D情况下显示
      {
        SpeedButton3DMeasure->Click();
      }

      SeriesASolid->Visible = true;
      SeriesASolid->Pen->Visible = false;
      SeriesA->Visible = false;

      for(int i=0;i<agridliney.Length;i++)
      {
        agridliney[i]->Visible = false;
      }

      for(int j=0;j<agridlinex.Length;j++)
      {
        agridlinex[j]->Visible = false;
      }

      SeriesAx->Visible = false;
      SeriesAy->Visible = false;

      SeriesA->ShowInLegend = false;
      SeriesASolid->ShowInLegend = false;


    }
    else
    {
      SeriesASolid->Visible = false;
      SeriesA->Visible = true;

      for(int i=0;i<agridliney.Length;i++)
      {
        agridliney[i]->Visible = true;
      }

      for(int j=0;j<agridlinex.Length;j++)
      {
        agridlinex[j]->Visible = true;
      }

      SeriesAx->Visible = true;
      SeriesAy->Visible = true;

      SeriesA->ShowInLegend = true;
      SeriesASolid->ShowInLegend = false;
    }
  }

  if(!temporaryValues.calcFilePath.empty())
  {
    if(ComboBoxGraph->ItemIndex == 0) //灰度图
    {
      if(false==temporaryValues.calcDimensionTransTag.status())  //默认灰度图只在2D情况下显示
      {
        SpeedButton3DCalculate->Click();
      }

      SeriesBSolid->Visible = true;
      SeriesBSolid->Pen->Visible = false;
      SeriesB->Visible = false;

      for(int i=0;i<bgridliney.Length;i++)
      {
        bgridliney[i]->Visible = false;
      }

      for(int j=0;j<bgridlinex.Length;j++)
      {
        bgridlinex[j]->Visible = false;
      }

      SeriesBx->Visible = false;
      SeriesBy->Visible = false;

      SeriesB->ShowInLegend = false;
      SeriesBSolid->ShowInLegend = false;
    }
    else
    {
      SeriesBSolid->Visible = false;
      SeriesB->Visible = true;

      for(int i=0;i<bgridliney.Length;i++)
      {
        bgridliney[i]->Visible = true;
      }

      for(int j=0;j<bgridlinex.Length;j++)
      {
        bgridlinex[j]->Visible = true;
      }

      SeriesBx->Visible = true;
      SeriesBy->Visible = true;

      SeriesB->ShowInLegend = true;
      SeriesBSolid->ShowInLegend = false;
    }
  }
  ComboBoxGraph->Enabled = false;
  ComboBoxGraph->Enabled = true;
  
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonZoomoutClick(TObject *Sender)
{
//  if(RadioButton1->Checked == true)
//  {
//    //由于在图像为2D时设置了TeeOpenGL1->Active = false，所以2D时无法放大，所以需要采用别的方法
//    //这里判断放大之后Panel1放大了多少倍，从而将Chart1进行等比放大
//    Panel1->Top = ToolBar1->Height + 2;
//    Panel1->Left = 0;
//    Panel1->Height = Form1->ClientHeight - ToolBar1->Height;
//    Panel1->Width  = Form1->ClientWidth;
//
//    //取宽/高放大倍数中较小者作为Chart放大倍数的修正
//    float thezoom = min<float>(Panel1->Height/StoreHeight,Panel1->Width/StoreWidth);
//
//    if(DimTag[0]%2==1) //2D状态放大时需要进行thezoom修正
//      Chart1->View3DOptions->Zoom = thezoom*0.83*100*504.0/float(Panel1->Width);
//    else   //3D时只需要正常的放大就可以了
//      Chart1->View3DOptions->Zoom = 0.83*100*504.0/float(Panel1->Width);
//    Panel1->Visible = true;
//    Panel2->Visible = false;
////    Panel3->Visible = false;
//    Panel4->Visible = false;
//
//    PanelTool->Top = Form1->ClientHeight - PanelTool->Height - 4;
//    PanelTool->Left = Form1->ClientWidth - PanelTool->Width - 4;
//    RadioButton1->Visible = false;
//    RadioButton2->Visible = false;
//    RadioButton3->Visible = false;
//    RadioButton4->Visible = false;
//
//    SpeedButtonZoomout->Visible = false;
//    SpeedButtonZoomin->Visible = true;
//    //隐藏PanelTool的外轮廓
//    PanelTool->BevelOuter = bvNone;   //4个图时为bvRaise;
//    PanelTool->BorderStyle = bsNone; //4个图时为bsSingle
//
//    StringGridA->Top = Chart1->Top;
//    StringGridA->Height = PanelTool->Top - Panel1->Top;
//    StringGridA->Width = Panel1->Width;
//  }
//
//  if(RadioButton2->Checked == true)
//  {
//    Panel2->Top = ToolBar1->Height + 2;
//    Panel2->Left = 0;
//    Panel2->Height = Form1->ClientHeight - ToolBar1->Height  ;
//    Panel2->Width  = Form1->ClientWidth;
//
//    Chart2->View3DOptions->Zoom = 0.83*100*504.0/float(Panel2->Width);
//    Panel1->Visible = false;
//    Panel2->Visible = true;
////    Panel3->Visible = false;
//    Panel4->Visible = false;
//
//    PanelTool->Top = Form1->ClientHeight - PanelTool->Height - 4;
//    PanelTool->Left = Form1->ClientWidth - PanelTool->Width - 4;
//    RadioButton1->Visible = false;
//    RadioButton2->Visible = false;
//    RadioButton3->Visible = false;
//    RadioButton4->Visible = false;
//
//    SpeedButtonZoomout->Visible = false;
//    SpeedButtonZoomin->Visible = true;
//    //隐藏PanelTool的外轮廓
//    PanelTool->BevelOuter = bvNone;   //4个图时为bvRaise;
//    PanelTool->BorderStyle = bsNone; //4个图时为bsSingle
//
//    StringGridB->DoubleBuffered = true;
//
//    StringGridB->Top = Chart2->Top;
//    StringGridB->Height = PanelTool->Top - Panel2->Top;
//    StringGridB->Width = Panel2->Width;
//  }
//
//  if(RadioButton3->Checked == true)
//  {
////    Panel3->Top = ToolBar1->Height + 2;
////    Panel3->Left = 0;
////    Panel3->Height = Form1->ClientHeight - ToolBar1->Height  ;
////    Panel3->Width  = Form1->ClientWidth;
//
////    Chart3->View3DOptions->Zoom = 0.83*100*504.0/float(Panel3->Width);
//    Panel1->Visible = false;
//    Panel2->Visible = false;
////    Panel3->Visible = true;
//    Panel4->Visible = false;
//
//    PanelTool->Top = Form1->ClientHeight - PanelTool->Height - 4;
//    PanelTool->Left = Form1->ClientWidth - PanelTool->Width - 4;
//    RadioButton1->Visible = false;
//    RadioButton2->Visible = false;
////    RadioButton3->Visible = false;
//    RadioButton4->Visible = false;
//
//    SpeedButtonZoomout->Visible = false;
//    SpeedButtonZoomin->Visible = true;
//    //隐藏PanelTool的外轮廓
//    PanelTool->BevelOuter = bvNone;   //4个图时为bvRaise;
//    PanelTool->BorderStyle = bsNone; //4个图时为bsSingle
//
////    StringGridC->Top = Chart3->Top;
////    StringGridC->Height = PanelTool->Top - Panel3->Top-ToolBar1->Height;
////    StringGridC->Width = Panel3->Width;
//  }
//
//  if(RadioButton4->Checked == true)
//  {
//    Panel4->Top = ToolBar1->Height + 2;
//    Panel4->Left = 0;
//    Panel4->Height = Form1->ClientHeight - ToolBar1->Height  ;
//    Panel4->Width  = Form1->ClientWidth;
//
//
//    Panel1->Visible = false;
//    Panel2->Visible = false;
////    Panel3->Visible = false;
//    Panel4->Visible = true;
//
//    PanelTool->Visible = false;
//
//    SpeedButtonZoomin1->Visible = true;
//    SpeedButtonZoomin1->Top = ToolBar1->Height + 5;
//    SpeedButtonZoomin1->Left = Panel4->Width - 50;
//  }
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonZoomoutMeasureClick(TObject *Sender)
{
  //
  //由于在图像为2D时设置了TeeOpenGL1->Active = false，所以2D时无法放大，所以需要采用别的方法
    //这里判断放大之后Panel1放大了多少倍，从而将Chart1进行等比放大
    PanelMeasure->Top = RzToolbar1->Height + 2;
    PanelMeasure->Left = 0;
    PanelMeasure->Height = FormMain->ClientHeight - RzToolbar1->Height;
    PanelMeasure->Width  = FormMain->ClientWidth;

    if(false==temporaryValues.measureDimensionTransTag.status()) //2D状态放大时需要进行thezoom修正
      ChartMeasure->View3DOptions->Zoom = 0.83*100*504.0/float(PanelMeasure->Width);
    else   //3D时只需要正常的放大就可以了
      ChartMeasure->View3DOptions->Zoom = 0.83*100*504.0/float(PanelMeasure->Width);
    PanelMeasure->Visible = true;
    PanelCalculate->Visible = false;
    PanelCompare->Visible = false;


    //------------PanelTool1的按钮设置----------------
    PanelToolMeasure->Width = ButtonsWidth*1.3;

    ButtonFlushMeasureToCache->Width = ButtonsWidth;
    ButtonFlushMeasureToCache->Height = ButtonsHeight;
    ButtonFlushMeasureToCache->Left = (PanelToolMeasure->ClientWidth - ButtonFlushMeasureToCache->Width)/2.0;
    ButtonFlushMeasureToCache->Top = PanelToolMeasure->Height - ButtonFlushMeasureToCache->Height - SeperateHeight;

    SpeedButtonTransforMeasure->Width = ButtonsWidth;
    SpeedButtonTransforMeasure->Height = ButtonsHeight;
    SpeedButtonTransforMeasure->Left = (PanelToolMeasure->ClientWidth - SpeedButtonTransforMeasure->Width)/2.0;
    SpeedButtonTransforMeasure->Top = ButtonFlushMeasureToCache->Top - SeperateHeight - SpeedButtonTransforMeasure->Height;

    SpeedButton3DMeasure->Width = ButtonsWidth;
    SpeedButton3DMeasure->Height = ButtonsHeight;
    SpeedButton3DMeasure->Left = (PanelToolMeasure->ClientWidth - SpeedButton3DMeasure->Width)/2.0;
    SpeedButton3DMeasure->Top = SpeedButtonTransforMeasure->Top - SeperateHeight - SpeedButton3DMeasure->Height;

    SpeedButtonDetMeasure->Width = ButtonsWidth;
    SpeedButtonDetMeasure->Height = ButtonsHeight;
    SpeedButtonDetMeasure->Left = (PanelToolMeasure->ClientWidth - SpeedButtonDetMeasure->Width)/2.0;
    SpeedButtonDetMeasure->Top = SpeedButton3DMeasure->Top - SeperateHeight - SpeedButtonDetMeasure->Height;

    SpeedButtonLevelsSetMeasure->Width = ButtonsWidth;
    SpeedButtonLevelsSetMeasure->Height = ButtonsHeight;
    SpeedButtonLevelsSetMeasure->Left = (PanelToolMeasure->ClientWidth - SpeedButtonLevelsSetMeasure->Width)/2.0;
    SpeedButtonLevelsSetMeasure->Top = SpeedButtonDetMeasure->Top - SeperateHeight - SpeedButtonLevelsSetMeasure->Height;

    SpeedButtonGridMeasure->Width = ButtonsWidth;
    SpeedButtonGridMeasure->Height = ButtonsHeight;
    SpeedButtonGridMeasure->Left = (PanelToolMeasure->ClientWidth - SpeedButtonGridMeasure->Width)/2.0;
    SpeedButtonGridMeasure->Top = SpeedButtonLevelsSetMeasure->Top - SeperateHeight - SpeedButtonGridMeasure->Height;

    //-------------------------------------------------------------------------

//    SpeedButtonZoomout->Visible = false;
//    SpeedButtonZoomin->Visible = true;


    StringGridMeasure->Top = ChartMeasure->Top;
//    StringGridA->Height = PanelTool->Top - Panel1->Top;
    StringGridMeasure->Width = PanelMeasure->Width;
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonZoomoutCalculateClick(TObject *Sender)
{
  //
    PanelCalculate->Top = RzToolbar1->Height + 2;
    PanelCalculate->Left = 0;
    PanelCalculate->Height = FormMain->ClientHeight - RzToolbar1->Height  ;
    PanelCalculate->Width  = FormMain->ClientWidth;

    ChartCalculate->View3DOptions->Zoom = 0.83*100*504.0/float(PanelCalculate->Width);
    PanelMeasure->Visible = false;
    PanelCalculate->Visible = true;
//    Panel3->Visible = false;
    PanelCompare->Visible = false;

    //------------PanelTool1的按钮设置----------------
    PanelToolCalculate->Width = ButtonsWidth*1.3;

    ButtonFlushCalcToCache->Width = ButtonsWidth;
    ButtonFlushCalcToCache->Height = ButtonsHeight;
    ButtonFlushCalcToCache->Left = (PanelToolCalculate->ClientWidth - ButtonFlushCalcToCache->Width)/2.0;
    ButtonFlushCalcToCache->Top = PanelToolCalculate->Height - ButtonFlushCalcToCache->Height - SeperateHeight;

    SpeedButtonTransforCalculate->Width = ButtonsWidth;
    SpeedButtonTransforCalculate->Height = ButtonsHeight;
    SpeedButtonTransforCalculate->Left = (PanelToolCalculate->ClientWidth - SpeedButtonTransforCalculate->Width)/2.0;
    SpeedButtonTransforCalculate->Top = ButtonFlushCalcToCache->Top - SeperateHeight - SpeedButtonTransforCalculate->Height;

    SpeedButton3DCalculate->Width = ButtonsWidth;
    SpeedButton3DCalculate->Height = ButtonsHeight;
    SpeedButton3DCalculate->Left = (PanelToolCalculate->ClientWidth - SpeedButton3DCalculate->Width)/2.0;
    SpeedButton3DCalculate->Top = SpeedButtonTransforCalculate->Top - SeperateHeight - SpeedButton3DCalculate->Height;

    SpeedButtonDetCalculate->Width = ButtonsWidth;
    SpeedButtonDetCalculate->Height = ButtonsHeight;
    SpeedButtonDetCalculate->Left = (PanelToolCalculate->ClientWidth - SpeedButtonDetCalculate->Width)/2.0;
    SpeedButtonDetCalculate->Top = SpeedButton3DCalculate->Top - SeperateHeight - SpeedButtonDetCalculate->Height;

    SpeedButtonLevelsSetCalculate->Width = ButtonsWidth;
    SpeedButtonLevelsSetCalculate->Height = ButtonsHeight;
    SpeedButtonLevelsSetCalculate->Left = (PanelToolCalculate->ClientWidth - SpeedButtonLevelsSetCalculate->Width)/2.0;
    SpeedButtonLevelsSetCalculate->Top = SpeedButtonDetCalculate->Top - SeperateHeight - SpeedButtonLevelsSetCalculate->Height;

    SpeedButtonGridCalculate->Width = ButtonsWidth;
    SpeedButtonGridCalculate->Height = ButtonsHeight;
    SpeedButtonGridCalculate->Left = (PanelToolCalculate->ClientWidth - SpeedButtonGridCalculate->Width)/2.0;
    SpeedButtonGridCalculate->Top = SpeedButtonLevelsSetCalculate->Top - SeperateHeight - SpeedButtonGridCalculate->Height;

    //-------------------------------------------------------------------------

    StringGridCalculate->DoubleBuffered = true;

    StringGridCalculate->Top = ChartCalculate->Top;
//    StringGridB->Height = PanelTool->Top - Panel2->Top;
    StringGridCalculate->Width = PanelCalculate->Width;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonZoominClick(TObject *Sender)
{
  ChartMeasure->AllowZoom = false;
  ChartCalculate->AllowZoom = false;
//  Chart3->AllowZoom = false;

  TRect Rect1;
  SystemParametersInfo(SPI_GETWORKAREA,0,&Rect1,0);//(API函数)用来得到窗体除工具栏
                                                   //之外的工作区域，结果放在Rect1中
  FormMain->Width = Rect1.Width();
  FormMain->Height = Rect1.Height();

  PanelMeasure->Top = RzToolbar1->Height + 2;
  PanelCalculate->Top = RzToolbar1->Height + 2;

  PanelMeasure->Height = (FormMain->ClientHeight - PanelMeasure->Top)/2.0 - 2;
  PanelCalculate->Height = (FormMain->ClientHeight - PanelCalculate->Top)/2.0 - 2;
//  Panel3->Height = (Form1->ClientHeight - Panel1->Top)/2.0 - 2;
  PanelCompare->Height = (FormMain->ClientHeight - PanelCalculate->Top)/2.0 - 2;

//  Panel3->Top = Panel1->Top + Panel1->Height + 2;
  PanelCompare->Top = PanelCalculate->Top + PanelCalculate->Height + 2;

  PanelMeasure->Width = (FormMain->ClientWidth - 2)/2.0;
  PanelCalculate->Width = (FormMain->ClientWidth - 2)/2.0;
//  Panel3->Width = (Form1->ClientWidth - 2)/2.0;
  PanelCompare->Width = (FormMain->ClientWidth - 2)/2.0;

  PanelMeasure->Left = 0;
  PanelCalculate->Left = PanelMeasure->Width + 2;
//  Panel3->Left = 0;
  PanelCompare->Left = PanelCalculate->Width + 2;

  PanelMeasure->Visible = true;
  PanelCalculate->Visible = true;
//  Panel3->Visible = true;
  PanelCompare->Visible = true;

//  PanelTool->Top = Panel1->Top + Panel1->Height*0.9;
//  PanelTool->Left = Panel1->Width*0.84;
//  PanelTool->Height = Panel1->Height*0.2;
//  PanelTool->Width = Panel1->Width*0.32;

//  RadioButton1->Left =  2;
//  RadioButton1->Top = 2;
//
//  RadioButton2->Left = PanelTool->Width - 22; //17+2=19
//  RadioButton2->Top = 2;
//
//  RadioButton3->Left = 2;
//  RadioButton3->Top = PanelTool->Height - 22;
//
//  RadioButton4->Left = PanelTool->Width - 22;
//  RadioButton4->Top = PanelTool->Height - 22;
//
//  RadioButton1->Visible = true;
//  RadioButton2->Visible = true;
//  RadioButton3->Visible = true;
//  RadioButton4->Visible = true;
//
//  PanelTool->Visible = true;

  //显示PanelTool的外轮廓
//  PanelTool->BevelOuter = bvRaised;   //1个图时为bvNone;
//  PanelTool->BorderStyle = bsSingle; //1个图时为bsNone

//  GroupBox1->Top = (PanelTool->Height - GroupBox1->Height)/2.0 - 1;
//  GroupBox1->Left = (PanelTool->Width - 38- GroupBox1->Width)/2.0 + 16;  //38 = 17*2+2*2

  ChartMeasure->View3DOptions->Zoom = 0.83*100*504.0/float(PanelMeasure->Width);
  ChartCalculate->View3DOptions->Zoom = 0.83*100*504.0/float(PanelCalculate->Width);
//  Chart3->View3DOptions->Zoom = 0.83*100*504.0/float(Panel3->Width);

//  SpeedButtonZoomin->Visible = false;
//  SpeedButtonZoomin1->Visible = false;
//  SpeedButtonZoomout->Visible = true;

  StringGridMeasure->Top = ChartMeasure->Top;
//  StringGridA->Height =PanelTool->Top - Panel1->Top;
  StringGridMeasure->Width = ChartMeasure->Width;

  StringGridCalculate->Top = ChartCalculate->Top;
//  StringGridB->Height = PanelTool->Top - Panel2->Top;
  StringGridCalculate->Width = ChartCalculate->Width;

//  StringGridC->Top = PanelTool->Top + PanelTool->Height - Panel3->Top;
//  StringGridC->Height = Panel3->Height -StringGridC->Top;
//  StringGridC->Width = Chart3->Width;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonZoomin1Click(TObject *Sender)
{
  ChartMeasure->AllowZoom = false;
  ChartCalculate->AllowZoom = false;
//  Chart3->AllowZoom = false;

  TRect Rect1;
  SystemParametersInfo(SPI_GETWORKAREA,0,&Rect1,0);//(API函数)用来得到窗体除工具栏
                                                   //之外的工作区域，结果放在Rect1中
  FormMain->Width = Rect1.Width();
  FormMain->Height = Rect1.Height();

  PanelMeasure->Top = RzToolbar1->Height + 2;
  PanelCalculate->Top = RzToolbar1->Height + 2;

  PanelMeasure->Height = (FormMain->ClientHeight - PanelMeasure->Top)/2.0 - 2;
  PanelCalculate->Height = (FormMain->ClientHeight - PanelCalculate->Top)/2.0 - 2;
//  Panel3->Height = (Form1->ClientHeight - Panel1->Top)/2.0 - 2;
  PanelCompare->Height = (FormMain->ClientHeight - PanelCalculate->Top)/2.0 - 2;

//  Panel3->Top = Panel1->Top + Panel1->Height + 2;
  PanelCompare->Top = PanelCalculate->Top + PanelCalculate->Height + 2;

  PanelMeasure->Width = (FormMain->ClientWidth - 2)/2.0;
  PanelCalculate->Width = (FormMain->ClientWidth - 2)/2.0;
//  Panel3->Width = (Form1->ClientWidth - 2)/2.0;
  PanelCompare->Width = (FormMain->ClientWidth - 2)/2.0;

  PanelMeasure->Left = 0;
  PanelCalculate->Left = PanelMeasure->Width + 2;
//  Panel3->Left = 0;
  PanelCompare->Left = PanelCalculate->Width + 2;

  PanelMeasure->Visible = true;
  PanelCalculate->Visible = true;
//  Panel3->Visible = true;
  PanelCompare->Visible = true;

//  PanelTool->Top = Panel1->Top + Panel1->Height*0.9;
//  PanelTool->Left = Panel1->Width*0.84;
//  PanelTool->Height = Panel1->Height*0.2;
//  PanelTool->Width = Panel1->Width*0.32;

//  RadioButton1->Left =  2;
//  RadioButton1->Top = 2;
//
//  RadioButton2->Left = PanelTool->Width - 22; //17+2=19
//  RadioButton2->Top = 2;
//
//  RadioButton3->Left = 2;
//  RadioButton3->Top = PanelTool->Height - 22;
//
//  RadioButton4->Left = PanelTool->Width - 22;
//  RadioButton4->Top = PanelTool->Height - 22;
//
//  RadioButton1->Visible = true;
//  RadioButton2->Visible = true;
//  RadioButton3->Visible = true;
//  RadioButton4->Visible = true;
//
//  PanelTool->Visible = true;

  //显示PanelTool的外轮廓
//  PanelTool->BevelOuter = bvRaised;   //1个图时为bvNone;
//  PanelTool->BorderStyle = bsSingle; //1个图时为bsNone

//  GroupBox1->Top = (PanelTool->Height - GroupBox1->Height)/2.0 - 1;
//  GroupBox1->Left = (PanelTool->Width - 38- GroupBox1->Width)/2.0 + 16;  //38 = 17*2+2*2

  ChartMeasure->View3DOptions->Zoom = 0.83*100*504.0/float(PanelMeasure->Width);
  ChartCalculate->View3DOptions->Zoom = 0.83*100*504.0/float(PanelCalculate->Width);
//  Chart3->View3DOptions->Zoom = 0.83*100*504.0/float(Panel3->Width);

//  SpeedButtonZoomin->Visible = false;
//  SpeedButtonZoomout->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::standsetClick(TObject *Sender)
{
  TFormparaset *child;

  child = new TFormparaset(this);
  child->FormStyle = fsStayOnTop;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolButtonsettingClick(TObject *Sender)
{
  standset->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolButton1Click(TObject *Sender)
{
  Open_Plan_DICOM->Click();
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::N1Click(TObject *Sender)
{
  TAboutBox *AboutBox;
  AboutBox = new TAboutBox(this);
  AboutBox->FormStyle = fsStayOnTop;
  AboutBox->Show();
}
//------------------调出系统设置窗口-------------------------------------------------
void __fastcall TFormMain::SystemSetClick(TObject *Sender)
{
  TFormsystemSet *systemchild;

  systemchild = new TFormsystemSet(this);
  systemchild->FormStyle = fsStayOnTop;
  systemchild->ClientHeight = FormMain->ClientHeight*0.3;
  systemchild->ClientWidth = FormMain->ClientWidth*0.2;
}

//-----------------------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonLevelsSetMeasureClick(TObject *Sender)
{
  TFormLevels* formlevel = new TFormLevels(this,SeriesA);


  formlevel->FormStyle = fsStayOnTop;

  formlevel->Show();
}

//-----------------------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonLevelsSetCalculateClick(TObject *Sender)
{
  TFormLevels* formlevel = new TFormLevels(this,SeriesB);


  formlevel->FormStyle = fsStayOnTop;

  formlevel->Show();
}
//---------------------------自定义的探测器Click事件---------------------------------------
/*
void __fastcall TForm1::DetClicked(TObject *Sender)
{
  int i,j,ii,jj;

  TLabel *thetempLabel = new TLabel(Chart1);
  thetempLabel = (TLabel*)Sender;

  //Label4->Caption = thetempLabel->Left+1;
  //Label5->Caption = thetempLabel->Top +1;

  int centerz;
  if(Chart1->ClientHeight%2==1){
    centerz = (Chart1->ClientHeight+1)/2;
  }else{
    centerz = (Chart1->ClientHeight)/2;
  }

  ii=0;
  for(j=SeriesA->MinZValue();j<=SeriesA->MaxZValue();j++)
  {
    jj=0;
    for(i=SeriesA->MinXValue();i<=SeriesA->MaxXValue();i++)
    {
      if(detector[ii][jj]==1)
      {
        if((thetempLabel->Left == TheDector[ii][jj]->Left)&&(thetempLabel->Top == TheDector[ii][jj]->Top))
        {
          //Label1->Caption = storedose0[ii*(axdir+1)+jj];

          //Label3->Caption = thetempLabel->Left;
          //Label4->Caption = thetempLabel->Top;
        }

      }
      jj++;
    }
   ii++;

  }

}
*/


//---------------------------------------------------------------------------
void __fastcall TFormMain::SaveToFileClick(TObject *Sender)
{
  //先显示信息设置界面
  TInfoForm *infoForm = new TInfoForm(this);
  infoForm->Parent = this;
  infoForm->FormStyle = fsStayOnTop;
  infoForm->ButtonYes->OnClick = infoForm->ToSave;   //为这种情景下定制保存功能
  infoForm->Show();

}

//------------------------展示StandardAndTH的值----------------------------
void __fastcall TFormMain::ShowStandardAndTH()
{
  EditTH->Text = this->temporaryValues.checkStandardParam.threshold;
  EditDoseGap->Text = this->temporaryValues.checkStandardParam.percentDifference;
  EditDistance->Text = this->temporaryValues.checkStandardParam.distance;
}

void __fastcall TFormMain::SetStandardAndTH(){
  if(EditTH->Text != ""){
    this->temporaryValues.checkStandardParam.threshold = EditTH->Text.ToDouble();
  }else{
    EditTH->Text = this->temporaryValues.checkStandardParam.threshold;
  }

  if(EditDoseGap->Text != ""){
    this->temporaryValues.checkStandardParam.percentDifference = EditDoseGap->Text.ToDouble();
  }else{
    EditDoseGap->Text = this->temporaryValues.checkStandardParam.percentDifference;
  }

  if(EditDistance->Text != ""){
    this->temporaryValues.checkStandardParam.distance = EditDistance->Text.ToDouble();
  }else{
    EditDistance->Text = this->temporaryValues.checkStandardParam.distance;
  }

}

//---------------------------------------------------------------------------
//------------------------展示PatientInfo窗口的信息----------------
void __fastcall TFormMain::ShowBaseInfo()
{
  GlobalMembers *globalMem = NULL;
  PatientInfo *patientInfo = NULL;
  GatePairDose *gatePairDose = NULL;
  ostringstream osItemsName;
  ostringstream osPath;
  
  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  patientInfo = globalMem->getPatientInfo();
  if(NULL == patientInfo){
     return;
  }

  gatePairDose = globalMem->getGatePairDose();
  if(NULL == gatePairDose){
    return;
  }

  osItemsName.str("");
  osPath.str("");
  osItemsName<<"Patient Informations";
  MemoPatientInfo->Items->Clear();
  MemoPatientInfo->Items->Add(MemoPatientInfo->GetNodeAt(0,0),osItemsName.str().c_str());
  
  osItemsName.str("");
  osPath.str("");
  osItemsName<<"ID: "<<patientInfo->patientId;
  osPath<<"Patient Informations\\";
  MemoPatientInfo->Items->AddChild(MemoPatientInfo->NodeFromPath(osPath.str().c_str()),osItemsName.str().c_str());

  osItemsName.str("");
  osPath.str("");
  osItemsName<<"Name: "<<patientInfo->patientName;
  osPath<<"Patient Informations\\";
  MemoPatientInfo->Items->AddChild(MemoPatientInfo->NodeFromPath(osPath.str().c_str()),osItemsName.str().c_str());

  osItemsName.str("");
  osPath.str("");
  osItemsName<<"Angle: "<<gatePairDose->copyAngle();
  osPath<<"Patient Informations\\";
  MemoPatientInfo->Items->AddChild(MemoPatientInfo->NodeFromPath(osPath.str().c_str()),osItemsName.str().c_str());

  osItemsName.str("");
  osPath.str("");
  osItemsName<<"Gender: "<<(patientInfo->patientGender==0?"Male":"Female");
  osPath<<"Patient Informations\\";
  MemoPatientInfo->Items->AddChild(MemoPatientInfo->NodeFromPath(osPath.str().c_str()),osItemsName.str().c_str());

  osItemsName.str("");
  osPath.str("");
  osItemsName<<"Age: "<<patientInfo->patientAge;
  osPath<<"Patient Informations\\";
  MemoPatientInfo->Items->AddChild(MemoPatientInfo->NodeFromPath(osPath.str().c_str()),osItemsName.str().c_str());

  osItemsName.str("");
  osPath.str("");
  osItemsName<<"Part: "<<patientInfo->treatedPart;
  osPath<<"Patient Informations\\";
  MemoPatientInfo->Items->AddChild(MemoPatientInfo->NodeFromPath(osPath.str().c_str()),osItemsName.str().c_str());


  globalMem = NULL;
  patientInfo = NULL;
  gatePairDose = NULL;

  MemoPatientInfo->FullExpand();
}


void __fastcall TFormMain::resetSomeOnceOpen_ChangeVar(){
   this->RzToolButtonRotation->ImageIndex = 20;

   temporaryValues.operator_measureDoseCentral.x = 0.0;
   temporaryValues.operator_measureDoseCentral.y = 0.0;
}


//---------------------------------------------------------------------------
bool __fastcall TFormMain::patientInformationSetting(FILETYPE fileType){

  TInfoForm *infoForm = new TInfoForm(this,fileType);
  infoForm->Parent = this;
  infoForm->FormStyle = fsStayOnTop;
  infoForm->Show();


  return true;
}

bool __fastcall TFormMain::patientInformationSetting(){

  TInfoForm *infoForm = new TInfoForm(this);
  infoForm->Parent = this;
  infoForm->FormStyle = fsStayOnTop;
  infoForm->Show();

  return true;
}
//--------------------------------------------------------------------
bool __fastcall TFormMain::angleSetting(FILETYPE fileType){

  TFormAngle *formAngle = new TFormAngle(this,fileType);
  formAngle->RzBitBtnOK->OnClick = formAngle->PersistVar;
  formAngle->Parent = this;
  formAngle->FormStyle = fsStayOnTop;
  formAngle->Show();

  return true;
}

//-------------------------------------------------------------------------
void __fastcall TFormMain::SetInfoBtnClick(TObject *Sender)
{
  patientInformationSetting();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonBest5Click(TObject *Sender)
{
  //
  TBestFiveForm *tBestFiveForm = new TBestFiveForm(this);
  tBestFiveForm->FormStyle = fsStayOnTop;
  tBestFiveForm->Parent = this;
  tBestFiveForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::LeftGroupBarItemsClicked(TObject *Sender){
  MessageBox(this->Handle,"Need To Something!","Warning!",MB_OK);
}


void __fastcall TFormMain::ToolBar_OpenZCdoseClick(TObject *Sender)
{
  OpenZCdose->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolBar_OpenMapCHECKdoseClick(TObject *Sender)
{
  OpenMapCHECKdose->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolBar_OpenMatrixDoseClick(TObject *Sender)
{
  OpenMatrixDose->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolBar_Open_Plan_DICOMClick(TObject *Sender)
{
  Open_Plan_DICOM->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToolBar_Open_Plan_SCUClick(TObject *Sender)
{
  Open_Plan_SCU->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Open_Plan_SCUClick(TObject *Sender)
{
  //未完成
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RzToolButtonSaveClick(TObject *Sender)
{
  SaveToFile->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RzToolButtonSystemSetClick(TObject *Sender)
{
  SystemSet->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RzToolButtonPrintClick(TObject *Sender)
{
  PrintCurrent->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RzToolButtonExistClick(TObject *Sender)
{
  if(mrYes==MessageDlg("确定退出程序么?",mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0))
  {
    Close();
  }else{
    return;
  }
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::RzToolButtonAboutClick(TObject *Sender)
{
  N1->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SmoothSetClick(TObject *Sender)
{
  //
  TSmoothingForm *smoothingForm = new TSmoothingForm(this);
  smoothingForm->Parent = this;
  smoothingForm->FormStyle = fsStayOnTop;
  smoothingForm->Show();
}
//--------------------------------------------------------------------------
void TFormMain::upDataGridSize(double gridSize[3]){
  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;
  DosePair* dosePair = NULL;
  Dose* dose = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  if(NULL == globalMem->getGatePairDose()){
    RunningLog::writeLog("The getGatePairDose is NULL;",__LINE__);
    return;
  }
  gatePairDose = globalMem->getGatePairDose();

  if(NULL == gatePairDose->getDosePair()){
    RunningLog::writeLog("The dosePair is NULL;",__LINE__);
    return;
  }
  dosePair = gatePairDose->getDosePair();

  if(NULL == dosePair->getMeasureDose()){
    RunningLog::writeLog("The MeasureDose is NULL;",__LINE__);
    return;
  }
  dose = dosePair->getMeasureDose();

  dose->sync_upDateGridSizes(gridSize);
  gatePairDose->Notify(Message_Notify(Update_measure_fromGatePair));

  RefreshMeasureDoseGraphicFromDisplayValue();
  RefreshCalculateDoseGraphicFromDisplayValue();

  globalMem = NULL;
  gatePairDose = NULL;
  dosePair = NULL;
  dose = NULL;
}


//----------------------------------------------------------------
void __fastcall TFormMain::Proc(TMsg &msg,bool &Handled){
  if(msg.message == WM_KEYDOWN){
    moveAndDrwaProfile(msg.wParam);
  }
}

//------------------------------------------------------------------------
void __fastcall TFormMain::moveAndDrwaProfile(int keyboardCode){

  switch(keyboardCode)
  {
    case 38: //Key_Up
    {
      if(temporaryValues.measureFilePath.empty() || 0==temporaryValues.measureFilePath.length()){
         return;
      }

      InitialCompareChart("X(mm)");

      if(temporaryValues.calcFilePath.empty() || 0==temporaryValues.calcFilePath.length()){
        if((temporaryValues.moveLine.getXLinePos()+1)>(temporaryValues.measureColLength - 1 - temporaryValues.measureFirstAlignmentCenter.col) ){

          temporaryValues.moveLine.setXLinePos(temporaryValues.measureColLength - 1 - temporaryValues.measureFirstAlignmentCenter.col);
        }
        else{
          temporaryValues.moveLine.xLinePosIncrease();
        }
        moveMeasureXProfile();
        drawMeasureXProfile();
      }else{

        if((temporaryValues.moveLine.getXLinePos()+1)>(temporaryValues.measureColLength - 1 - temporaryValues.measureFirstAlignmentCenter.col)
          ||(temporaryValues.moveLine.getXLinePos()+1)>(temporaryValues.cutBian.at(1,1,0) - temporaryValues.calcFirstAlignmentCenter.col)/temporaryValues.segments[1] ){

          temporaryValues.moveLine.setXLinePos(min<int>(temporaryValues.measureColLength - 1 - temporaryValues.measureFirstAlignmentCenter.col,
                                                        (temporaryValues.cutBian.at(1,1,0) - temporaryValues.calcFirstAlignmentCenter.col)/temporaryValues.segments[1]) );
        }
        else{
          temporaryValues.moveLine.xLinePosIncrease();
        }

        moveMeasureXProfile();
        drawMeasureXProfile();
        moveCalcXProfile();
        drawCalcXProfile();
      }

    }
    break;
    case 40: //key_Down
    {
      if(temporaryValues.measureFilePath.empty() || 0==temporaryValues.measureFilePath.length()){
         return;
      }

      InitialCompareChart("X(mm)");

      if(temporaryValues.calcFilePath.empty() || 0==temporaryValues.calcFilePath.length()){
        if((temporaryValues.moveLine.getXLinePos()-1)<(-temporaryValues.measureFirstAlignmentCenter.col)){

          temporaryValues.moveLine.setXLinePos(-temporaryValues.measureFirstAlignmentCenter.col);
        }
        else{
          temporaryValues.moveLine.xLinePosDecrease();
        }
        moveMeasureXProfile();
        drawMeasureXProfile();
      }else{

        if((temporaryValues.moveLine.getXLinePos()-1)<(-temporaryValues.measureFirstAlignmentCenter.col)
            ||(temporaryValues.moveLine.getXLinePos()-1)<(temporaryValues.cutBian.at(1,0,0) - temporaryValues.calcFirstAlignmentCenter.col)/temporaryValues.segments[1] ){
          
          temporaryValues.moveLine.setXLinePos(max<int>(-temporaryValues.measureFirstAlignmentCenter.col,
                                                        (temporaryValues.cutBian.at(1,0,0) - temporaryValues.calcFirstAlignmentCenter.col)/temporaryValues.segments[1] ));
        }
        else{
          temporaryValues.moveLine.xLinePosDecrease();
        }

        moveMeasureXProfile();
        drawMeasureXProfile();
        moveCalcXProfile();
        drawCalcXProfile();
      }

    }
    break;
    case 37: //Key_Left
    {
      if(temporaryValues.measureFilePath.empty() || 0==temporaryValues.measureFilePath.length()){
         return;
      }

      InitialCompareChart("Y(mm)");

      if(temporaryValues.calcFilePath.empty() || 0==temporaryValues.calcFilePath.length()){
        if((temporaryValues.moveLine.getYLinePos()-1)<(-temporaryValues.measureFirstAlignmentCenter.row)){

          temporaryValues.moveLine.setYLinePos(-temporaryValues.measureFirstAlignmentCenter.row);
        }
        else{
          temporaryValues.moveLine.yLinePosDecrease();
        }
        moveMeasureYProfile();
        drawMeasureYProfile();
      }else{

        if((temporaryValues.moveLine.getYLinePos()-1)<(-temporaryValues.measureFirstAlignmentCenter.row)
            ||(temporaryValues.moveLine.getYLinePos()-1)<(temporaryValues.cutBian.at(0,0,0) - temporaryValues.calcFirstAlignmentCenter.row)/temporaryValues.segments[0] ){
          
          temporaryValues.moveLine.setYLinePos(max<int>(-temporaryValues.measureFirstAlignmentCenter.row,
                                                        (temporaryValues.cutBian.at(0,0,0) - temporaryValues.calcFirstAlignmentCenter.row)/temporaryValues.segments[0] ));
        }
        else{
          temporaryValues.moveLine.yLinePosDecrease();
        }

        moveMeasureYProfile();
        drawMeasureYProfile();
        moveCalcYProfile();
        drawCalcYProfile();
      }

    }
    break;
    case 39: //Key_Right
    {
      if(temporaryValues.measureFilePath.empty() || 0==temporaryValues.measureFilePath.length()){
         return;
      }

      InitialCompareChart("Y(mm)");

      if(temporaryValues.calcFilePath.empty() || 0==temporaryValues.calcFilePath.length()){
        if((temporaryValues.moveLine.getYLinePos()+1)>(temporaryValues.measureRowLength - 1 - temporaryValues.measureFirstAlignmentCenter.row) ){

          temporaryValues.moveLine.setYLinePos(temporaryValues.measureRowLength - 1 - temporaryValues.measureFirstAlignmentCenter.row);
        }
        else{
          temporaryValues.moveLine.yLinePosIncrease();
        }
        moveMeasureYProfile();
        drawMeasureYProfile();
      }else{

        if((temporaryValues.moveLine.getYLinePos()+1)>(temporaryValues.measureRowLength - 1 - temporaryValues.measureFirstAlignmentCenter.row)
          ||(temporaryValues.moveLine.getYLinePos()+1)>(temporaryValues.cutBian.at(0,1,0) - temporaryValues.calcFirstAlignmentCenter.row)/temporaryValues.segments[0] ){

          temporaryValues.moveLine.setYLinePos(min<int>(temporaryValues.measureRowLength - 1 - temporaryValues.measureFirstAlignmentCenter.row,
                                                        (temporaryValues.cutBian.at(0,1,0) - temporaryValues.calcFirstAlignmentCenter.row)/temporaryValues.segments[0]) );
        }
        else{
          temporaryValues.moveLine.yLinePosIncrease();
        }

        moveMeasureYProfile();
        drawMeasureYProfile();
        moveCalcYProfile();
        drawCalcYProfile();
      }
    }
    break;
    default:
    break;
  }
}


void __fastcall TFormMain::drawMeasureXProfile(){
  double tempMeasureDoseValue =0.0;
  double tempCalcDoseValue = -1;

  ProMeaSeries->Clear();

  int xLinePos = temporaryValues.moveLine.getXLinePos();
  int tempXPosInCalcPlan;
  if(true==temporaryValues.checkedRecord.getCheckedStatus()){

    for(int i=0;i<temporaryValues.measureRowLength;i++){
      if(true==temporaryValues.detectorArray.at(i,xLinePos+temporaryValues.measureFirstAlignmentCenter.col,0)){
        tempMeasureDoseValue = temporaryValues.NormMeasureDoseData.at(i,xLinePos+temporaryValues.measureFirstAlignmentCenter.col,0);
        tempXPosInCalcPlan = temporaryValues.calcFirstAlignmentCenter.row - (temporaryValues.measureFirstAlignmentCenter.row - i)*temporaryValues.segments[0];
        if( tempXPosInCalcPlan>=temporaryValues.cutBian.at(0,0,0) && tempXPosInCalcPlan<=temporaryValues.cutBian.at(0,1,0)){
          tempCalcDoseValue = temporaryValues.NormCalcDoseData.at(tempXPosInCalcPlan,xLinePos*temporaryValues.segments[1] + temporaryValues.calcFirstAlignmentCenter.col,0);
        }


        //Show prior order:GAMMA>DTA>DD
        switch(temporaryValues.checkedRecord.getCheckType())        //对DD,DTA,GAMA三种情况哪些点未通过要判断,并且判断
        {                                                        //未通过的状态,测量值大于计算值(Red)还是测量值小于计算值(Blue)
          case CHECKTYPE(ABS_GAMMA):     //GAMMA
          case CHECKTYPE(REL_GAMMA):
          {
            if(temporaryValues.checkedRecord.getSingleGammaResult()->everyPointResults.at(i,
                         xLinePos+temporaryValues.measureFirstAlignmentCenter.col,
                         0)<=1 || tempMeasureDoseValue<=temporaryValues.checkStandardParam.threshold)  //Gamma通过的点，或者由于低于阈值而没被比较的点设为黄色
            {
              ProMeaSeries->AddXY(i*temporaryValues.gridSize[0] - temporaryValues.measureDoseCentral.x,
                                  tempMeasureDoseValue,
                                  "",
                                  clYellow);
            }
            else if(tempMeasureDoseValue<=tempCalcDoseValue || tempCalcDoseValue<0)  //未通过但是测量值小于计算值(Blue)
            {
              ProMeaSeries->AddXY(i*temporaryValues.gridSize[0] - temporaryValues.measureDoseCentral.x,
                                  tempMeasureDoseValue,
                                  "",
                                  clBlue);
            }
            else                        //未通过但是测量值大于计算值(Red)
            {
              ProMeaSeries->AddXY(i*temporaryValues.gridSize[0] - temporaryValues.measureDoseCentral.x,
                                  tempMeasureDoseValue,
                                  "",
                                  clRed);
            }

          }
          break;

          case CHECKTYPE(ABS_DTA_FloatWay):
          case CHECKTYPE(ABS_DTA_MidValueWay):
          case CHECKTYPE(ABS_DTA_SamePositionWay):
          case CHECKTYPE(REL_DTA_FloatWay):
          case CHECKTYPE(REL_DTA_MidValueWay):
          case CHECKTYPE(REL_DTA_SamePositionWay):
              {
            if(temporaryValues.checkedRecord.getSingleDTAResult()->everyPointResults.at(i,
                         xLinePos+temporaryValues.measureFirstAlignmentCenter.col,
                         0)>0 || tempMeasureDoseValue<=temporaryValues.checkStandardParam.threshold)  //DTA通过的点，或者由于低于阈值而没被比较的点设为黄色
            {
              ProMeaSeries->AddXY(i*temporaryValues.gridSize[0] - temporaryValues.measureDoseCentral.x,
                                  tempMeasureDoseValue,
                                  "",
                                  clYellow);
            }
            else if(tempMeasureDoseValue<=tempCalcDoseValue || tempCalcDoseValue<0)  //未通过但是测量值小于计算值(Blue)
            {
              ProMeaSeries->AddXY(i*temporaryValues.gridSize[0] - temporaryValues.measureDoseCentral.x,
                                  tempMeasureDoseValue,
                                  "",
                                  clBlue);
            }
            else                        //未通过但是测量值大于计算值(Red)
            {
              ProMeaSeries->AddXY(i*temporaryValues.gridSize[0] - temporaryValues.measureDoseCentral.x,
                                  tempMeasureDoseValue,
                                  "",
                                  clRed);
            }
          }
          break;

          case CHECKTYPE(ABS_DD):     //DD
          {                       //DD通过的点，或者由于低于阈值而没被比较的点设为黄色
            if(temporaryValues.checkedRecord.getSingleDDResult()->everyPointResults.at(i,
                         xLinePos+temporaryValues.measureFirstAlignmentCenter.col,
                         0)<=temporaryValues.checkStandardParam.percentDifference || tempMeasureDoseValue<=temporaryValues.checkStandardParam.threshold)
            {
              ProMeaSeries->AddXY(i*temporaryValues.gridSize[0] - temporaryValues.measureDoseCentral.x,
                                  tempMeasureDoseValue,
                                  "",
                                  clYellow);
            }
            else if(tempMeasureDoseValue<=tempCalcDoseValue || tempCalcDoseValue<0)  //未通过但是测量值小于计算值(Blue)
            {
              ProMeaSeries->AddXY(i*temporaryValues.gridSize[0] - temporaryValues.measureDoseCentral.x,
                                  tempMeasureDoseValue,
                                  "",
                                  clBlue);
            }
            else                        //未通过但是测量值大于计算值(Red)
            {
              ProMeaSeries->AddXY(i*temporaryValues.gridSize[0] - temporaryValues.measureDoseCentral.x,
                                  tempMeasureDoseValue,
                                  "",
                                  clRed);
            }

          }
          break;

          default:
          break;
        }
      }
    }


  }
  else{

    for(int i=0;i<temporaryValues.measureRowLength;i++){
      if(true==temporaryValues.detectorArray.at(i,xLinePos+temporaryValues.measureFirstAlignmentCenter.col,0)){

        ProMeaSeries->AddXY(i*temporaryValues.gridSize[0] - temporaryValues.measureDoseCentral.x,
                            temporaryValues.NormMeasureDoseData.at(i,xLinePos+temporaryValues.measureFirstAlignmentCenter.col,0),
                            "",
                            clYellow);
      }
    }
  }
}

void __fastcall TFormMain::drawCalcXProfile(){
  ProCauSeries->Clear();
  ShowProSeries->Clear();      //ShowProSeries用来使用smoothing函数来显示ProCauSeries

  int xLinePos = temporaryValues.moveLine.getXLinePos();

  //计算值(曲线)，不需要判断
  for(int i=temporaryValues.cutBian.at(0,0,0);i<=temporaryValues.cutBian.at(0,1,0);i++)
  {
    ProCauSeries->AddXY(i*temporaryValues.gridSize[0]/temporaryValues.segments[0] - temporaryValues.calcDoseCentral.x,
                        temporaryValues.NormCalcDoseData.at(i,xLinePos*temporaryValues.segments[1] + temporaryValues.calcFirstAlignmentCenter.col,0),
                        "",
                        clBlack);
  }
  TeeFunction1->AddPoints(ProCauSeries); //一定要加上
  ProCauSeries->Visible = false;
}

void __fastcall TFormMain::drawMeasureYProfile(){
  double tempMeasureDoseValue = 0.0;
  double tempCalcDoseValue = -1.0;
  int tempYPosInCalcPlan;
  ProMeaSeries->Clear();

  int yLinePos = temporaryValues.moveLine.getYLinePos();
  
  if(true==temporaryValues.checkedRecord.getCheckedStatus()){

    for(int j=0;j<temporaryValues.measureColLength;j++){

      if(true==temporaryValues.detectorArray.at(yLinePos+temporaryValues.measureFirstAlignmentCenter.row,j,0)){
        tempMeasureDoseValue = temporaryValues.NormMeasureDoseData.at(yLinePos+temporaryValues.measureFirstAlignmentCenter.row,j,0);

        tempYPosInCalcPlan = temporaryValues.calcFirstAlignmentCenter.col - (temporaryValues.measureFirstAlignmentCenter.col - j)*temporaryValues.segments[1];
        if( tempYPosInCalcPlan>=temporaryValues.cutBian.at(0,0,0) && tempYPosInCalcPlan<=temporaryValues.cutBian.at(0,1,0)){
          tempCalcDoseValue = temporaryValues.NormCalcDoseData.at(yLinePos*temporaryValues.segments[0] + temporaryValues.calcFirstAlignmentCenter.row,tempYPosInCalcPlan,0);
        }

        //Show prior order:GAMMA>DTA>DD
        switch(temporaryValues.checkedRecord.getCheckType())        //对DD,DTA,GAMA三种情况哪些点未通过要判断,并且判断
        {                                                          //未通过的状态,测量值大于计算值(Red)还是测量值小于计算值(Blue)
          case CHECKTYPE(ABS_GAMMA): //GAMMA
          case CHECKTYPE(REL_GAMMA):
          {
            if(temporaryValues.checkedRecord.getSingleGammaResult()->everyPointResults.at(yLinePos+temporaryValues.measureFirstAlignmentCenter.row,
                                                                    j,0)<=1 ||
              tempMeasureDoseValue<=temporaryValues.checkStandardParam.threshold)  //Gamma通过的点，或者由于低于阈值而没被比较的点设为黄色
            {
              ProMeaSeries->AddXY(j*temporaryValues.gridSize[1] - temporaryValues.measureDoseCentral.y,
                            tempMeasureDoseValue,
                            "",
                            clYellow);
            }
            else if(tempMeasureDoseValue<=tempCalcDoseValue || tempCalcDoseValue<0)  //未通过但是测量值小于计算值(Blue)
            {
              ProMeaSeries->AddXY(j*temporaryValues.gridSize[1] - temporaryValues.measureDoseCentral.y,
                            tempMeasureDoseValue,
                            "",
                            clBlue);
            }
            else                        //未通过但是测量值大于计算值(Red)
            {
              ProMeaSeries->AddXY(j*temporaryValues.gridSize[1] - temporaryValues.measureDoseCentral.y,
                            tempMeasureDoseValue,
                            "",
                            clRed);
            }

          }
          break;
          
          case CHECKTYPE(ABS_DTA_FloatWay):
          case CHECKTYPE(ABS_DTA_MidValueWay):
          case CHECKTYPE(ABS_DTA_SamePositionWay):
          case CHECKTYPE(REL_DTA_FloatWay):
          case CHECKTYPE(REL_DTA_MidValueWay):
          case CHECKTYPE(REL_DTA_SamePositionWay):
          {
            if(temporaryValues.checkedRecord.getSingleDTAResult()->everyPointResults.at(yLinePos+temporaryValues.measureFirstAlignmentCenter.row,
                                       j,0)>0 ||
              tempMeasureDoseValue<=temporaryValues.checkStandardParam.threshold)  //DTA通过的点，或者由于低于阈值而没被比较的点设为黄色
            {
              ProMeaSeries->AddXY(j*temporaryValues.gridSize[1] - temporaryValues.measureDoseCentral.y,
                            tempMeasureDoseValue,
                            "",
                            clYellow);
            }
            else if(tempMeasureDoseValue<=tempCalcDoseValue || tempCalcDoseValue<0)  //未通过但是测量值小于计算值(Blue)
            {
              ProMeaSeries->AddXY(j*temporaryValues.gridSize[1] - temporaryValues.measureDoseCentral.y,
                            tempMeasureDoseValue,
                            "",
                            clBlue);
            }
            else                        //未通过但是测量值大于计算值(Red)
            {
              ProMeaSeries->AddXY(j*temporaryValues.gridSize[1] - temporaryValues.measureDoseCentral.y,
                            tempMeasureDoseValue,
                            "",
                            clRed);
            }
          }
          break;

          case CHECKTYPE(ABS_DD):     //DD
          {                                         //DD通过的点，或者由于低于阈值而没被比较的点设为黄色
            if(temporaryValues.checkedRecord.getSingleDDResult()->everyPointResults.at(yLinePos+temporaryValues.measureFirstAlignmentCenter.row,
                                          j,0)<=temporaryValues.checkStandardParam.percentDifference ||
              tempMeasureDoseValue<=temporaryValues.checkStandardParam.threshold)
            {
              ProMeaSeries->AddXY(j*temporaryValues.gridSize[1] - temporaryValues.measureDoseCentral.y,
                            tempMeasureDoseValue,
                            "",
                            clYellow);
            }
            else if(tempMeasureDoseValue<=tempCalcDoseValue || tempCalcDoseValue<0)  //未通过但是测量值小于计算值(Blue)
            {
              ProMeaSeries->AddXY(j*temporaryValues.gridSize[1] - temporaryValues.measureDoseCentral.y,
                            tempMeasureDoseValue,
                            "",
                            clBlue);
            }
            else                        //未通过但是测量值大于计算值(Red)
            {
              ProMeaSeries->AddXY(j*temporaryValues.gridSize[1] - temporaryValues.measureDoseCentral.y,
                            tempMeasureDoseValue,
                            "",
                            clRed);
            }

          }
          break;

          default:
          break;
        }
      }
    }


  }
  else{
    for(int j=0;j<temporaryValues.measureColLength;j++){

      if(true==temporaryValues.detectorArray.at(yLinePos+temporaryValues.measureFirstAlignmentCenter.row,j,0)){

        ProMeaSeries->AddXY(j*temporaryValues.gridSize[1] - temporaryValues.measureDoseCentral.y,
                            temporaryValues.NormMeasureDoseData.at(yLinePos+temporaryValues.measureFirstAlignmentCenter.row,j,0),
                            "",
                            clYellow);
      }
    }
  }

}

void __fastcall TFormMain::drawCalcYProfile(){
  ProCauSeries->Clear();
  ShowProSeries->Clear();      //ShowProSeries用来使用smoothing函数来显示ProCauSeries

  int yLinePos = temporaryValues.moveLine.getYLinePos();

  //计算值(曲线)，不需要判断
  for(int j=temporaryValues.cutBian.at(1,0,0);j<=temporaryValues.cutBian.at(1,1,0);j++)
  {
    ProCauSeries->AddXY(j*temporaryValues.gridSize[1]/temporaryValues.segments[1] - temporaryValues.calcDoseCentral.y,
                        temporaryValues.NormCalcDoseData.at(yLinePos*temporaryValues.segments[0] + temporaryValues.calcFirstAlignmentCenter.row,j,0),
                        "",
                        clBlack);
  }
  TeeFunction1->AddPoints(ProCauSeries); //一定要加上
  ProCauSeries->Visible = false;
}



void __fastcall TFormMain::moveMeasureXProfile(){
  SeriesAm->Clear();
  int xLinePos = temporaryValues.moveLine.getXLinePos();
  
  for(int i=0;i<temporaryValues.measureRowLength;i++){
    SeriesAm->AddXYZ(i-temporaryValues.measureArrayShowCenter.row,
                     temporaryValues.NormMeasureDoseData.at(i,xLinePos+temporaryValues.measureFirstAlignmentCenter.col,0),
                     xLinePos+temporaryValues.measureFirstAlignmentCenter.col - temporaryValues.measureArrayShowCenter.col,
                     "",
                     clBlack);
  }
}

void __fastcall TFormMain::moveCalcXProfile(){
  SeriesBm->Clear();

  int xLinPos = temporaryValues.moveLine.getXLinePos();

  for(int i = temporaryValues.cutBian.at(0,0,0);i<=temporaryValues.cutBian.at(0,1,0);i++){
    SeriesBm->AddXYZ(i-temporaryValues.calcArrayShowCenter.row,
                     temporaryValues.NormCalcDoseData.at(i,xLinPos*temporaryValues.segments[1] + temporaryValues.calcFirstAlignmentCenter.col,0),
                     xLinPos*temporaryValues.segments[1] + temporaryValues.calcFirstAlignmentCenter.col - temporaryValues.calcArrayShowCenter.col,
                     "",
                     clBlack);
  }
  
}

void __fastcall TFormMain::moveMeasureYProfile(){
  SeriesAm->Clear();
  int yLinePos = temporaryValues.moveLine.getYLinePos();
  for(int j=0;j<temporaryValues.measureColLength;j++)
  {
    SeriesAm->AddXYZ(yLinePos + temporaryValues.measureFirstAlignmentCenter.row - temporaryValues.measureArrayShowCenter.row,
                     temporaryValues.NormMeasureDoseData.at(yLinePos + temporaryValues.measureFirstAlignmentCenter.row,j,0) ,
                     j-temporaryValues.measureArrayShowCenter.col,
                     "",
                     clBlack);
  }
}

void __fastcall TFormMain::moveCalcYProfile(){
  SeriesBm->Clear();

  int yLinPos = temporaryValues.moveLine.getYLinePos();

  for(int j = temporaryValues.cutBian.at(1,0,0);j<=temporaryValues.cutBian.at(1,1,0);j++){
    SeriesBm->AddXYZ(yLinPos*temporaryValues.segments[0] + temporaryValues.calcFirstAlignmentCenter.row - temporaryValues.calcArrayShowCenter.row,
                     temporaryValues.NormCalcDoseData.at(yLinPos*temporaryValues.segments[0] + temporaryValues.calcFirstAlignmentCenter.row,j,0),
                     j-temporaryValues.calcArrayShowCenter.col,
                     "",
                     clBlack);
  }
}
//------------------------------------------------------------------------------

void __fastcall TFormMain::MemoResultShow(){
  int totalCompared,passedCount;
  double passedPercent;
  GridPoint measureNormPoint,calcNormPoint;

  TreeResult->Items->Clear();
  TreeResult->Items->Add(TreeResult->GetNodeAt(0,0),"Check Result");
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\"),"Dose Difference");
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\"),"DTA");
  TreeResult->Items->AddChild(TreeResult->NodeFromPath("Check Result\\"),"Gamma");

  switch(temporaryValues.checkedRecord.getCheckType())
  {
    case CHECKTYPE(ABS_DD):
    {
      showDDResult();
    }
    break;

    case CHECKTYPE(ABS_DTA_FloatWay):
    case CHECKTYPE(ABS_DTA_MidValueWay):
    case CHECKTYPE(ABS_DTA_SamePositionWay):
    case CHECKTYPE(REL_DTA_FloatWay):
    case CHECKTYPE(REL_DTA_MidValueWay):
    case CHECKTYPE(REL_DTA_SamePositionWay):
    {
      showDTAResult();
    }
    break;

    case CHECKTYPE(ABS_GAMMA):
    case CHECKTYPE(REL_GAMMA):
    {
      showGammaResult();
    }
    break;

    default:
    break;
    
  }


}

//---------------------------------------------------------------------------
void __fastcall TFormMain::ShowBestFiveResult(){
  TBestFiveResultForm* bestFiveResultForm = new TBestFiveResultForm(this);
  bestFiveResultForm->FormStyle = fsStayOnTop;
  bestFiveResultForm->Parent = this;
  bestFiveResultForm->Show();
}


//---------------------------------------------------------------------------

void __fastcall TFormMain::FlushTowDataToCacheClick(TObject *Sender)
{
  GlobalMembers *globalMem = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  if(!this->temporaryValues.measureFilePath.empty() &&
     !this->temporaryValues.calcFilePath.empty()){

     int choose = MessageDlg("Flush the current tow datas to Cache?",mtInformation,TMsgDlgButtons()<<mbYes<<mbNo,0);

     if(choose == mrYes){
       //flush the two datas to cache
       globalMem->flushToCache();
     }

  }

  globalMem = NULL;        
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::ButtonFlushMeasureToCacheClick(TObject *Sender)
{
  GlobalMembers *globalMem = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  if(!this->temporaryValues.measureFilePath.empty()){
    //flush to cache
    globalMem->flushMeasureToCache();
  }

  globalMem = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonFlushCalcToCacheClick(TObject *Sender)
{
  GlobalMembers *globalMem = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  if(!this->temporaryValues.calcFilePath.empty()){
    //flush to cache
    globalMem->flushCalculateToCache();
  }

  globalMem = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RzToolButtonRefreshLeftGroupBarsClick(TObject *Sender)
{
  ShowPatientCache();
}

//---------------------------------------------------------------------------


void __fastcall TFormMain::PrintCurrentClick(TObject *Sender)
{
  //打印之前先确定基本信息已经录入
  TInfoForm *infoForm = new TInfoForm(this);
  infoForm->Parent = this;
  infoForm->FormStyle = fsStayOnTop;
  infoForm->ButtonYes->OnClick = infoForm->ToPrint;
  infoForm->Show();        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ChangeInformation1Click(TObject *Sender)
{
  patientInformationSetting();                 
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SaveToCacheClick(TObject *Sender)
{
  FlushTowDataToCache->Click();        
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RzToolButtonNormPointSettingClick(TObject *Sender)
{
  RzToolButtonNormPointSet->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::setMesureheightClick(TObject *Sender)
{
  SpeedButtonLevelsSetMeasure->Click();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::setCalcheightClick(TObject *Sender)
{
  SpeedButtonLevelsSetCalculate->Click();
}

//---------------------------------------------------------------------------



void __fastcall TFormMain::RzToolButtonNormValueSettingClick(
      TObject *Sender)
{
  //
  TNormValueSetForm* NormValueSetForm = new TNormValueSetForm(this);
  NormValueSetForm->Parent = this;
  NormValueSetForm->Show();
  NormValueSetForm->FormStyle = fsStayOnTop;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::User1Click(TObject *Sender)
{
  //
  ShellExecute(Handle,"Open","TPDC_Manual.pdf",NULL,NULL,SW_SHOWNORMAL);

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ModelSettingClick(TObject *Sender)
{
  //
  TModelSettingForm *ModelSetting = new TModelSettingForm(this);
  ModelSetting->Parent = this;
  ModelSetting->Show();
  ModelSetting->FormStyle = fsStayOnTop;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormShow(TObject *Sender)
{
//  TModelSettingForm *ModelSetting = new TModelSettingForm(this);
//  ModelSetting->Parent = this;
//  ModelSetting->Show();
//  ModelSetting->FormStyle = fsStayOnTop;        
}
//---------------------------------------------------------------------------



