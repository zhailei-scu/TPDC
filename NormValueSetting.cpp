//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NormValueSetting.h"
#include "doseshell.h"
#include "GlobalData.h"
#include "dose.h"
#include "HandledPairDose.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzRadChk"
#pragma link "RzBckgnd"
#pragma link "RzRadGrp"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma resource "*.dfm"
TNormValueSetForm *NormValueSetForm;
//---------------------------------------------------------------------------
__fastcall TNormValueSetForm::TNormValueSetForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TNormValueSetForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree;        
}
//---------------------------------------------------------------------------

void __fastcall TNormValueSetForm::RzBitBtnCancelClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TNormValueSetForm::RzCheckBoxMeasureMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
  if(RzCheckBoxMeasure->Checked){
    RzCheckBoxMeasure->Checked = true;
    MeasureNormValueSetting->Enabled = false;
  }else{
    RzCheckBoxMeasure->Checked = false;
    MeasureNormValueSetting->Enabled = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TNormValueSetForm::RzCheckBoxCalculateMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
  if(RzCheckBoxCalculate->Checked){
    RzCheckBoxCalculate->Checked = true;
    CalcNormValueSetting->Enabled = false;
  }else{
    RzCheckBoxCalculate->Checked = false;
    CalcNormValueSetting->Enabled = true;
  }      
}
//---------------------------------------------------------------------------
void __fastcall TNormValueSetForm::RzBitBtnOKClick(TObject *Sender)
{
  Hide();


  GlobalMembers *globalMem = NULL;
  HandledPairDose  *handledPairDose = NULL;

  double normValue;
  HANDLE_MODEL handel_Model;
  
  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    return;
  }
  handel_Model = globalMem->getHandel_Model();
  handledPairDose =  globalMem->getHandledPairDose();

  if(RzCheckBoxMeasure->Checked){

    normValue = EditMeasureNormValue->Text.ToDouble();

    if(MeasureNormValueSetting->Buttons[0]->Checked){
      handledPairDose->normlize_ActualValue(NORMLIZE_TYPE(NORM_SINGLE_MEASUREMENT_Abs_or_Rel),normValue,handel_Model);
    }else if(MeasureNormValueSetting->Buttons[1]->Checked){
      handledPairDose->normlize_PercentValue(NORMLIZE_TYPE(NORM_SINGLE_MEASUREMENT_Abs_or_Rel),normValue,handel_Model);
    }

    handledPairDose->Notify(Message_Notify(Update_measure_fromHandledPairDose));
  }


  if(RzCheckBoxCalculate->Checked){

    normValue = EditCalculateNormValue->Text.ToDouble();

    if(CalcNormValueSetting->Buttons[0]->Checked){
      handledPairDose->normlize_ActualValue(NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Abs),normValue,handel_Model);
      handledPairDose->normlize_ActualValue(NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Rel),normValue,handel_Model);
    }else if(CalcNormValueSetting->Buttons[1]->Checked){
      handledPairDose->normlize_PercentValue(NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Abs),normValue,handel_Model);
      handledPairDose->normlize_PercentValue(NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Rel),normValue,handel_Model);
    }

    handledPairDose->Notify(Message_Notify(Update_calculate_fromHandledPairDose));
  }

  globalMem = NULL;
  handledPairDose = NULL;

  FormMain->RefreshMeasureDoseGraphicFromDisplayValue();

  if(!MainFormTempValue.calcFilePath.empty()){
    FormMain->RefreshCalculateDoseGraphicFromDisplayValue();
  }

  Close();
}
//---------------------------------------------------------------------------

void __fastcall TNormValueSetForm::MeasureNormValueSettingChanging(
      TObject *Sender, int NewIndex, bool &AllowChange)
{
  if(MeasureNormValueSetting->Buttons[0]->Checked){
    RzLabelMeasure->Caption = "cGy";

    if(DoseType(DOSE_RELATIVE) == MainFormTempValue.doseType){
      MessageBox(this->Handle,"The relative dose can not be applied to absolute compare.","Warning!",MB_OK);
      MeasureNormValueSetting->Buttons[1]->Checked = true;
      return;
    }



  }else if(MeasureNormValueSetting->Buttons[1]->Checked){
    RzLabelMeasure->Caption = "%";
  }
}
//---------------------------------------------------------------------------

void __fastcall TNormValueSetForm::CalcNormValueSettingChanging(
      TObject *Sender, int NewIndex, bool &AllowChange)
{
  if(CalcNormValueSetting->Buttons[0]->Checked){
    RzLabelCalc->Caption = "cGy";

    if(DoseType(DOSE_RELATIVE) == MainFormTempValue.doseType){
      MessageBox(this->Handle,"The relative dose can not be applied to absolute compare.","Warning!",MB_OK);
      CalcNormValueSetting->Buttons[1]->Checked = true;
      return;
    }
  }else if(CalcNormValueSetting->Buttons[1]->Checked){
    RzLabelCalc->Caption = "%";
  }
}
//---------------------------------------------------------------------------

