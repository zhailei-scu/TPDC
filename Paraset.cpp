//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "doseshell.h"
#include "Check.h"
#include "Paraset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzTabs"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzSpnEdt"
#pragma link "RzLabel"
#pragma link "RzEdit"
#pragma resource "*.dfm"
TFormparaset *Formparaset;
//---------------------------------------------------------------------------
__fastcall TFormparaset::TFormparaset(TComponent* Owner)
        : TForm(Owner)
{
  this->ClientHeight = FormMain->ClientHeight*0.4;
  this->ClientWidth =  FormMain->ClientWidth*0.4;

  this->DosePercentDifference->Value = MainFormTempValue.checkStandardParam.percentDifference;
  this->DistanceStandard->Value = MainFormTempValue.checkStandardParam.distance;

  this->DoseThreshold->Value = MainFormTempValue.checkStandardParam.threshold;

  this->BestFiveDoseThreshold->Value = MainFormTempValue.checkStandardParam.bestFiveDoseThreadhold;

  this->DtaAllowDoseUncertainty->Value = MainFormTempValue.checkStandardParam.doseUncertainty;

  this->AllowableMaxDoseGap->Value = MainFormTempValue.checkStandardParam.actualDosegap;
}
//---------------------------------------------------------------------------
void __fastcall TFormparaset::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree;      //ÊÍ·Å´°¿ÚÄÚ´æ
}
//---------------------------------------------------------------------------


void __fastcall TFormparaset::RzBitBtnCancelClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

void __fastcall TFormparaset::RzBitBtnOKClick(TObject *Sender)
{
  MainFormTempValue.checkStandardParam.percentDifference = this->DosePercentDifference->Value;
  MainFormTempValue.checkStandardParam.distance = this->DistanceStandard->Value;

  MainFormTempValue.checkStandardParam.threshold = this->DoseThreshold->Value;

  MainFormTempValue.checkStandardParam.bestFiveDoseThreadhold = this->BestFiveDoseThreshold->Value;

  MainFormTempValue.checkStandardParam.doseUncertainty = this->DtaAllowDoseUncertainty->Value;

  MainFormTempValue.checkStandardParam.actualDosegap = this->AllowableMaxDoseGap->Value;

  FormMain->ShowStandardAndTH();
  
  MessageBox(this->Handle,"The parameters is setted,which woluld be apply in next checking operation!","Warning!",MB_OK);

  Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormparaset::RzBitBtnResetClick(TObject *Sender)
{
  if(mrNo == MessageDlg("The parameters is setted,which woluld be apply in next checking operation!",
                         mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0)){
    return;
  }

  this->DosePercentDifference->Value = 3.0;
  this->DistanceStandard->Value = 3.0;
  this->DoseThreshold->Value = 10.0;
  this->BestFiveDoseThreshold->Value = 50.0;
  this->DtaAllowDoseUncertainty->Value = 2.5;

  this->AllowableMaxDoseGap->Value = 0.0;
}
//---------------------------------------------------------------------------


