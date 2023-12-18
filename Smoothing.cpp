//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Smoothing.h"
#include "doseshell.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzRadGrp"
#pragma link "RzButton"
#pragma link "RzChkLst"
#pragma link "RzLstBox"
#pragma link "RzSpnEdt"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TSmoothingForm *SmoothingForm;
//---------------------------------------------------------------------------
__fastcall TSmoothingForm::TSmoothingForm(TComponent* Owner)
        : TForm(Owner)
{
  this->ClientHeight = FormMain->ClientHeight*0.3;
  this->ClientWidth = FormMain->ClientWidth*0.2;
  this->Left = (FormMain->ClientWidth - this->ClientWidth)/2.0;
  this->Top = (FormMain->ClientHeight - this->ClientHeight)/2.0;

  RadioButtonList.clear();

  RadioButtonList.push_back(this->Gauss3Orders);
  RadioButtonList.push_back(this->Gauss5Orders);
  RadioButtonList.push_back(this->Medium3Orders);
  RadioButtonList.push_back(this->Medium5Orders);
  RadioButtonList.push_back(this->Average3Orders);
  RadioButtonList.push_back(this->Average5Orders);

  for(vector<TRzRadioButton*>::iterator iterat=RadioButtonList.begin();iterat != RadioButtonList.end();iterat++){
    (*iterat)->OnClick = RadioButtonChecked;
  }

  RadioButtonChooseMap.clear();

  RadioButtonChooseMap.insert(map<TRzRadioButton*,SmmothChoose>::value_type(this->Gauss3Orders,SmmothChoose(Gauss3OrdersChoosed)));
  RadioButtonChooseMap.insert(map<TRzRadioButton*,SmmothChoose>::value_type(this->Gauss5Orders,SmmothChoose(Gauss5OrdersChoosed)));
  RadioButtonChooseMap.insert(map<TRzRadioButton*,SmmothChoose>::value_type(this->Medium3Orders,SmmothChoose(Medium3OrdersChoosed)));
  RadioButtonChooseMap.insert(map<TRzRadioButton*,SmmothChoose>::value_type(this->Medium5Orders,SmmothChoose(Medium5OrdersChoosed)));
  RadioButtonChooseMap.insert(map<TRzRadioButton*,SmmothChoose>::value_type(this->Average3Orders,SmmothChoose(Average3OrdersChoosed)));
  RadioButtonChooseMap.insert(map<TRzRadioButton*,SmmothChoose>::value_type(this->Average5Orders,SmmothChoose(Average5OrdersChoosed)));
}
//-----------------------Destructor--------------------------------------
__fastcall TSmoothingForm::~TSmoothingForm(){
  RadioButtonList.clear();
  vector<TRzRadioButton*>().swap(RadioButtonList);

  RadioButtonChooseMap.clear();
  map<TRzRadioButton*,SmmothChoose>().swap(RadioButtonChooseMap);
}
//---------------------------------------------------------------------------
void __fastcall TSmoothingForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{

  Action = caFree; //ÊÍ·ÅÄÚ´æ
}
//---------------------------------------------------------------------------

void __fastcall TSmoothingForm::RzBitBtnCloseClick(TObject *Sender)
{
  Close();
}
//--------------define the Checked action for each RadioButtons---------------
void __fastcall TSmoothingForm::RadioButtonChecked(TObject *Sender){
  for(vector<TRzRadioButton*>::iterator iterat=RadioButtonList.begin();iterat != RadioButtonList.end();iterat++){
    if((*iterat) != Sender){
      if(true==(*iterat)->Checked){
        (*iterat)->Checked = false;
      }
    }
  }
}



void __fastcall TSmoothingForm::startToSmooth(SmmothChoose choose){
//  GlobalMembers *globalMem = NULL;
//  DisplayPairDose* displayPairDose = NULL;
//  Dose* measureDisplayDose = NULL;
//
//  MatrixData<double> *doseMatrix = NULL;
//  double* dosePtr = NULL;
//
//  globalMem = GlobalMembers::getInstance();
//  if(NULL == globalMem){
//    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
//    return;
//  }
//
//  displayPairDose = globalMem->getDisplayPairDose();
//  if(NULL == displayPairDose){
//    RunningLog::writeLog("The DisplayPairDose is NULL;",__LINE__);
//    return;
//  }
//
//
//  measureDisplayDose = displayPairDose->getNormMeasureDisplayDose();
//  if(NULL == displayPairDose->getNormMeasureDisplayDose()){
//    RunningLog::writeLog("The MeasureDisplayDose is NULL;",__LINE__);
//    return;
//  }
//
//
//  measureDisplayDose->sync_Write_Start();
//
//  doseMatrix = measureDisplayDose->getDoseMatrix();
//  if(NULL == doseMatrix){
//    RunningLog::writeLog("The Measure dose Matrix is NULL;",__LINE__);
//    measureDisplayDose->sync_finish();
//    return;
//  }
  if(NULL == &MainFormTempValue.NormMeasureDoseData){
    RunningLog::writeLog("The temp measure normlize dose is NULL",__LINE__);
    return;
  }

  switch(choose)
  {
    case SmmothChoose(Gauss3OrdersChoosed):
    {
      GaussianSmoothingOrderThree(&MainFormTempValue.NormMeasureDoseData);
    }
    break;
    case SmmothChoose(Gauss5OrdersChoosed):
    {
      GaussianSmoothingOrderFive(&MainFormTempValue.NormMeasureDoseData);
    }
    break;
    case SmmothChoose(Medium3OrdersChoosed):
    {
      midValueSmoothing(&MainFormTempValue.NormMeasureDoseData,3);
    }
    break;
    case SmmothChoose(Medium5OrdersChoosed):
    {
      midValueSmoothing(&MainFormTempValue.NormMeasureDoseData,5);
    }
    break;
    case SmmothChoose(Average3OrdersChoosed):
    {
      averageSmoothing(&MainFormTempValue.NormMeasureDoseData,3);
    }
    break;
    case SmmothChoose(Average5OrdersChoosed):
    {
      averageSmoothing(&MainFormTempValue.NormMeasureDoseData,5);
    }
    break;
    default:
    {
      RunningLog::writeLog("The smoothing type is unknown",__LINE__);
      return;
    }
    break;
  }

  FormMain->RefreshMeasureDoseGraphicFromTemporyValue();
}

//-----------------------------------------------------------------------------------
void __fastcall TSmoothingForm::RzBitBtnOKClick(TObject *Sender)
{
  this->Visible = false;
  Hide();

  for(vector<TRzRadioButton*>::iterator iterat=RadioButtonList.begin();iterat != RadioButtonList.end();iterat++){
    if((*iterat)->Checked){
      map<TRzRadioButton*,SmmothChoose>::iterator it = RadioButtonChooseMap.find((*iterat));
      startToSmooth(it->second);

      break;
    }
  }

  Close();

}

//---------------------------------------------------------------------------

void __fastcall TSmoothingForm::RzBitBtnResetClick(TObject *Sender)
{
  //
  Hide();
  FormMain->RefreshMeasureDoseGraphicFromDisplayValue();
  Close();
}
//---------------------------------------------------------------------------

