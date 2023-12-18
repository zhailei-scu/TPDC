//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "caxSetting.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma link "RzLabel"
#pragma link "RzButton"
#pragma resource "*.dfm"
#include "doseshell.h"
#include "GlobalData.h"
#include "GatePairDose.h"
#include "Cache.h"
TFormCAX *FormCAX;
//---------------------------------------------------------------------------
__fastcall TFormCAX::TFormCAX(TComponent* Owner)
        : TForm(Owner)
{
  this->RzSpinEditCAX_X->Text = MainFormTempValue.operator_measureDoseCentral.x;
  this->RzSpinEditCAX_Y->Text = MainFormTempValue.operator_measureDoseCentral.y;
}

__fastcall TFormCAX::TFormCAX(TComponent* Owner,FILETYPE fileType)
       : TForm(Owner)
{
  this->fileType = fileType;
  
  this->RzSpinEditCAX_X->Text = "0.00";
  this->RzSpinEditCAX_Y->Text = "0.00";
}
//---------------------------------------------------------------------------
void __fastcall TFormCAX::SetCAXAandShowFirst(TObject* Sender){

  Hide();

  string cax_X,cax_Y;
  
  if(RzSpinEditCAX_X->Text.IsEmpty()){
    MessageBox(this->Handle,"The cax x cannot be NULL","Warning!",MB_OK);
    RzSpinEditCAX_X->Text = "0";
    return;
  }
  cax_X = RzSpinEditCAX_X->Text.c_str();

  if(RzSpinEditCAX_Y->Text.IsEmpty()){
    MessageBox(this->Handle,"The cax y cannot be NULL","Warning!",MB_OK);
    RzSpinEditCAX_Y->Text = "0";
    return;
  }
  cax_Y = RzSpinEditCAX_Y->Text.c_str();

  MainFormTempValue.operator_measureDoseCentral.x = atof(cax_X.c_str());  //as a temp store,and the MainFormTempValue.measureDoseCentral will be refresh later
  MainFormTempValue.operator_measureDoseCentral.y = atof(cax_X.c_str());

  FormMain->ShowMeasureDialog(this->fileType);

  Close();
}
void __fastcall TFormCAX::SetCAXAandFlushFromMemory(TObject* Sender){

  Hide();

  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;

  if(RzSpinEditCAX_X->Text.IsEmpty()){
    MessageBox(this->Handle,"The cax x cannot be NULL","Warning!",MB_OK);
    RzSpinEditCAX_X->Text = "0";
    return;
  }

  if(RzSpinEditCAX_Y->Text.IsEmpty()){
    MessageBox(this->Handle,"The cax y cannot be NULL","Warning!",MB_OK);
    RzSpinEditCAX_Y->Text = "0";
    return;
  }

  MainFormTempValue.operator_measureDoseCentral.x = atof(RzSpinEditCAX_X->Text.c_str());  //as a temp store,and the MainFormTempValue.measureDoseCentral will be refresh later
  MainFormTempValue.operator_measureDoseCentral.y = atof(RzSpinEditCAX_Y->Text.c_str());

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    return;
  }

  gatePairDose = globalMem->getGatePairDose();
  if(NULL == gatePairDose){
    return;
  }

  gatePairDose->Notify(Message_Notify(Update_CAX_from_operator));

  globalMem = NULL;
  gatePairDose = NULL;

  FormMain->RefreshMeasureDoseGraphicFromDisplayValue();


  if(!MainFormTempValue.calcFilePath.empty()){
    FormMain->RefreshCalculateDoseGraphicFromDisplayValue();
  }
  
  Close();
}

void __fastcall TFormCAX::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;        
}
//---------------------------------------------------------------------------


void __fastcall TFormCAX::RzBitBtnCancelClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

void __fastcall TFormCAX::RzBitBtnResetClick(TObject *Sender)
{
  this->RzSpinEditCAX_X->Text = MainFormTempValue.operator_measureDoseCentral.x;
  this->RzSpinEditCAX_Y->Text = MainFormTempValue.operator_measureDoseCentral.y;
}
//---------------------------------------------------------------------------





