//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PrintSet.h"
#include "doseshell.h"
#include "GlobalData.h"
#include "Cache.h"
#include <sstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TeeSurfa"
#pragma link "RzPanel"
#pragma link "RzSplit"
#pragma resource "*.dfm"

using namespace std;


TPrintForm *PrintForm;
//---------------------------------------------------------------------------
__fastcall TPrintForm::TPrintForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TPrintForm::FormCreate(TObject *Sender)
{
  QRChartMeasureContour->Chart->Top = 0;
  QRChartMeasureContour->Chart->Left = 0;
  QRChartMeasureContour->Chart->Height = QRChartMeasureContour->Height;
  QRChartMeasureContour->Chart->Width = QRChartMeasureContour->Width;
  QRChartMeasureContour->Chart->Legend->Left = QRChartMeasureContour->Width - QRChartMeasureContour->Chart->Legend->Width;

  QRChartCalcContour->Chart->Top = 0;
  QRChartCalcContour->Chart->Left = 0;
  QRChartCalcContour->Chart->Height = QRChartCalcContour->Height;
  QRChartCalcContour->Chart->Width = QRChartCalcContour->Width;
  QRChartCalcContour->Chart->Legend->Left = QRChartCalcContour->Width - QRChartCalcContour->Chart->Legend->Width;

  GlobalMembers *globalMem = NULL;
  PatientInfo *patientInfo = NULL;

  ostringstream os;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  patientInfo = globalMem->getPatientInfo();
  if(NULL == patientInfo){
    RunningLog::writeLog("The patientInfo is NULL;",__LINE__);
    return;
  }

  os.clear();
  os.str("");
  os<<"ID: "<<patientInfo->patientId;
  QRLabelId->Caption = os.str().c_str();

  os.clear();
  os.str("");
  os<<"Name："<<patientInfo->patientName;
  QRLabelName->Caption = os.str().c_str();


  os.clear();
  os.str("");
  os<<"Gender: "<<(patientInfo->patientGender>-1?(patientInfo->patientGender==0?"Male":"Female"):"");
  this->QRLabelGender->Caption = os.str().c_str();


  os.clear();
  os.str("");
  os<<"Age: "<<patientInfo->patientAge;
  QRLabelAge->Caption = os.str().c_str();


  os.clear();
  os.str("");
  os<<"Treated Part: "<<patientInfo->treatedPart;
  QRLabelPart->Caption = os.str().c_str();

  if(MainFormTempValue.checkedRecord.getSingleGammaResult()->totalPassPercent>=0) {
    os.clear();
    os.str("");
    os<<"%GAMMA pass percent："<< FormatFloat("0.00",MainFormTempValue.checkedRecord.getSingleGammaResult()->totalPassPercent).c_str();
    QRLabelGAMMA->Caption = os.str().c_str();
  }else{
    QRLabelGAMMA->Caption = "GAMMA 尚未验证";
  }

  if(MainFormTempValue.checkedRecord.getSingleDTAResult()->totalPassPercent>=0) {
    os.clear();
    os.str("");
    os<<"%DTA pass percent："<< FormatFloat("0.00",MainFormTempValue.checkedRecord.getSingleDTAResult()->totalPassPercent).c_str();
    QRLabelDTA->Caption = os.str().c_str();
  }else{
    QRLabelDTA->Caption = "DTA 尚未验证";
  }

  if(MainFormTempValue.checkedRecord.getSingleDDResult()->totalPassPercent>=0) {
    os.clear();
    os.str("");
    os<<"%DD pass percent："<< FormatFloat("0.00",MainFormTempValue.checkedRecord.getSingleDDResult()->totalPassPercent).c_str();
    QRLabelDD->Caption = os.str().c_str();
  }else{
    QRLabelDD->Caption = "DD 尚未验证";
  }
  
  os.clear();
  os.str("");
  
  globalMem = NULL;
  patientInfo = NULL;

  ShowMeasureGraphy();
  ShowCalcGraphy();
}
//---------------------------------------------------------------------------
void __fastcall TPrintForm::ShowMeasureGraphy(){

  SeriesPrintMeasureContour->Clear();
  SeriesPrintMeasureHotPoint->Clear();
  if(false==MainFormTempValue.measureFilePath.empty()){

    //Measure Contour
    QRChartMeasureContour->Chart->MarginBottom = 0;
    QRChartMeasureContour->Chart->MarginTop = 0;
    QRChartMeasureContour->Chart->MarginLeft = 0;
    QRChartMeasureContour->Chart->MarginRight = 0;
    QRChartMeasureContour->Chart->BottomAxis->StartPosition = 50 - (MainFormTempValue.measureRowLength)*(25 + 25*((float)(QRChartMeasureContour->Chart->Height))/QRChartMeasureContour->Chart->Legend->Left)/(float)(MainFormTempValue.measureColLength);
    QRChartMeasureContour->Chart->BottomAxis->EndPosition = 50 + (MainFormTempValue.measureRowLength)*(25 + 25*((float)(QRChartMeasureContour->Chart->Height))/QRChartMeasureContour->Chart->Legend->Left)/(float)(MainFormTempValue.measureColLength);

    for(int j=0;j<MainFormTempValue.measureColLength;j++){
      for(int i=0;i<MainFormTempValue.measureRowLength;i++){
        SeriesPrintMeasureContour->AddXYZ(i-MainFormTempValue.measureArrayShowCenter.row,
                                     MainFormTempValue.NormMeasureDoseData.at(i,j,0),
                                     j-MainFormTempValue.measureArrayShowCenter.col);
      }
    }
    
    QRChartMeasureContour->Chart->LeftAxis->StartPosition = 0;
    QRChartMeasureContour->Chart->LeftAxis->EndPosition = 0; //通过将所有点压缩到底面来实现向2D转化
    QRChartMeasureContour->Chart->View3DOptions->Rotation = 0; //通过将Chart旋转到一个固定角度，使网
    QRChartMeasureContour->Chart->View3DOptions->Elevation = 270;  //格和轴有2D效果
    SeriesPrintMeasureContour->YPositionLevel = false;
    SeriesPrintMeasureContour->Visible = true;


    //Measure HotPoint
    for(int j=0;j<MainFormTempValue.measureColLength;j++){
      for(int i=0;i<MainFormTempValue.measureRowLength;i++){
        SeriesPrintMeasureHotPoint->AddXYZ(i-MainFormTempValue.measureArrayShowCenter.row,
                           MainFormTempValue.measureHotPointData.at(i,j,0),
                           j-MainFormTempValue.measureArrayShowCenter.col);

      }
    }

    QRChartPrintMeasureHotPoint->Chart->LeftAxis->StartPosition = 0;
    QRChartPrintMeasureHotPoint->Chart->LeftAxis->EndPosition = 0; //通过将所有点压缩到底面来实现向2D转化
    QRChartPrintMeasureHotPoint->Chart->View3DOptions->Rotation = 0; //通过将Chart旋转到一个固定角度，使网
    QRChartPrintMeasureHotPoint->Chart->View3DOptions->Elevation = 270;  //格和轴有2D效果

    SeriesPrintMeasureHotPoint->Visible = true;
  }
}

void __fastcall TPrintForm::ShowCalcGraphy(){
  //
  SeriesPrintCalcContour->Clear();
  SeriesPrintCalcHotPoint->Clear();
  if(false==MainFormTempValue.calcFilePath.empty()){

    //Calculate Contour
    QRChartCalcContour->Chart->MarginBottom = 0;
    QRChartCalcContour->Chart->MarginTop = 0;
    QRChartCalcContour->Chart->MarginLeft = 0;
    QRChartCalcContour->Chart->MarginRight = 0;
    QRChartCalcContour->Chart->BottomAxis->StartPosition = 50 - (MainFormTempValue.cutBian.at(0,1,0) - MainFormTempValue.cutBian.at(0,0,0))*(25 + 25*((float)(QRChartCalcContour->Chart->Height))/QRChartCalcContour->Chart->Legend->Left)/(float)(MainFormTempValue.cutBian.at(1,1,0) - MainFormTempValue.cutBian.at(1,0,0));
    QRChartCalcContour->Chart->BottomAxis->EndPosition = 50 + (MainFormTempValue.cutBian.at(0,1,0) - MainFormTempValue.cutBian.at(0,0,0))*(25 + 25*((float)(QRChartCalcContour->Chart->Height))/QRChartCalcContour->Chart->Legend->Left)/(float)(MainFormTempValue.cutBian.at(1,1,0) - MainFormTempValue.cutBian.at(1,0,0));


    for(int j=MainFormTempValue.cutBian.at(1,0,0);j<=MainFormTempValue.cutBian.at(1,1,0);j++){
      for(int i=MainFormTempValue.cutBian.at(0,0,0);i<=MainFormTempValue.cutBian.at(0,1,0);i++){
        SeriesPrintCalcContour->AddXYZ(i-MainFormTempValue.calcArrayShowCenter.row,
                      MainFormTempValue.NormCalcDoseData.at(i,j,0),
                      j-MainFormTempValue.calcArrayShowCenter.col);
      }
    }
    SeriesPrintCalcContour->YPositionLevel = false;
    SeriesPrintCalcContour->Visible = true;


    //Calculate HotPoint
    QRChartPrintCalcHotPoint->Chart->BottomAxis->StartPosition = 50 - (MainFormTempValue.cutBian.at(0,1,0) - MainFormTempValue.cutBian.at(0,0,0))*50/(float)(MainFormTempValue.cutBian.at(1,1,0) - MainFormTempValue.cutBian.at(1,0,0));
    QRChartPrintCalcHotPoint->Chart->BottomAxis->EndPosition = 50 + (MainFormTempValue.cutBian.at(0,1,0) - MainFormTempValue.cutBian.at(0,0,0))*50/(float)(MainFormTempValue.cutBian.at(1,1,0) - MainFormTempValue.cutBian.at(1,0,0));

    for(int j=MainFormTempValue.cutBian.at(1,0,0);j<=MainFormTempValue.cutBian.at(1,1,0);j++){
      for(int i=MainFormTempValue.cutBian.at(0,0,0);i<=MainFormTempValue.cutBian.at(0,1,0);i++){
        SeriesPrintCalcHotPoint->AddXYZ(i-MainFormTempValue.calcArrayShowCenter.row,
                                        MainFormTempValue.calcHotPointData.at(i,j,0),
                                        j-MainFormTempValue.calcArrayShowCenter.col);
      }
    }

    SeriesPrintCalcHotPoint->Visible = true;
  }
}

void __fastcall TPrintForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TPrintForm::QuickRep1AfterPreview(TObject *Sender)
{
   //Preview模态窗口现实之后，立刻关闭Print主窗口，
   //而且在触发打印时也不显示主窗口，也就是说Print主窗口只起支撑作用，自始至终显示的
   //都是PreView模态窗口
   Close();
}
//---------------------------------------------------------------------------



