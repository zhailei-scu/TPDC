//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Angle.h"
#include "GlobalData.h"
#include "GatePairDose.h"
#include "doseshell.h"
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma resource "*.dfm"

using namespace std;

TFormAngle *FormAngle;
//---------------------------------------------------------------------------
__fastcall TFormAngle::TFormAngle(TComponent* Owner,FILETYPE fileType)
        : TForm(Owner)
{
  this->fileType = fileType; 
}
//---------------------------------------------------------------------------
void __fastcall TFormAngle::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TFormAngle::RzBitBtnCancelClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TFormAngle::FormCreate(TObject *Sender)
{
  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  if(NULL == globalMem->getGatePairDose()){
    globalMem->allocateGatePairDose();
  }
  gatePairDose = globalMem->getGatePairDose();

  this->RzEditAngle->Text = gatePairDose->copyAngle().c_str();

  globalMem = NULL;
  gatePairDose = NULL;


}
//---------------------------------------------------------------------------
void __fastcall TFormAngle::PersistVar(TObject *Sender){
  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;

  string angle;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    return;
  }

  if(NULL == globalMem->getGatePairDose()){
    globalMem->allocateGatePairDose();
  }
  gatePairDose = globalMem->getGatePairDose();

  
  if(RzEditAngle->Text.IsEmpty()){
    MessageBox(this->Handle,"The angle cannot be NULL","Warning!",MB_OK);
    RzEditAngle->Text = "0";
    return;
  }
  angle = RzEditAngle->Text.c_str();
  
  gatePairDose->setAngle(angle);

  globalMem = NULL;
  gatePairDose = NULL;

  Hide();

  FormMain->caxSetting(this->fileType);
  
  Close();
}

