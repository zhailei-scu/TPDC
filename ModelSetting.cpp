//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ModelSetting.h"
#include "HandledPairDose.h"
#include "GlobalData.h"
#include "LogFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzRadChk"
#pragma link "RzBckgnd"
#pragma link "RzEdit"
#pragma link "RzRadGrp"
#pragma resource "*.dfm"
TModelSettingForm *ModelSettingForm;
//---------------------------------------------------------------------------
__fastcall TModelSettingForm::TModelSettingForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TModelSettingForm::RzBitBtnOKClick(TObject *Sender)
{
  GlobalMembers *globalMem = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    MessageBox(this->Handle,"Please read dose first.","Warning!",MB_OK);
    return;
  }

  if(true == ModelGroup->Buttons[0]->Checked){

    globalMem->setHandel_Model(HANDLE_MODEL(ADAC));    //ADAC Model

  }else if(true == ModelGroup->Buttons[1]->Checked){

    globalMem->setHandel_Model(HANDLE_MODEL(SNDAC));  //SNDAC Model

  }

  globalMem = NULL;

  Close();
}
//---------------------------------------------------------------------------

void __fastcall TModelSettingForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TModelSettingForm::RzBitBtnCancelClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

void __fastcall TModelSettingForm::FormCreate(TObject *Sender)
{
  GlobalMembers *globalMem = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    MessageBox(this->Handle,"Please read dose first.","Warning!",MB_OK);
    return;
  }

  if(globalMem->getHandel_Model() == HANDLE_MODEL(ADAC) ){

    ModelGroup->Buttons[0]->Checked = true;            //ADAC Model
    
  }else if(globalMem->getHandel_Model() == HANDLE_MODEL(SNDAC)){

    ModelGroup->Buttons[1]->Checked = true;      //SNDAC Model
  }

  globalMem = NULL;

}
//---------------------------------------------------------------------------

