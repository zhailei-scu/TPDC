//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DTAWayChoose.h"
#include "doseshell.h"
#include "GlobalData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzRadGrp"
#pragma link "RzButton"
#pragma link "RzLabel"
#pragma resource "*.dfm"
TFormDTAWayChoose *FormDTAWayChoose;
//---------------------------------------------------------------------------
__fastcall TFormDTAWayChoose::TFormDTAWayChoose(TComponent* Owner,bool absoulte)
        : TForm(Owner)
{
  this->abosulteCheck = absoulte;
}
//---------------------------------------------------------------------------
void __fastcall TFormDTAWayChoose::RzBitBtnOKClick(TObject *Sender)
{
  Hide();

  GlobalMembers *globalMem = NULL;
  DoseCheck* doseCheck = NULL;

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

  if(true == this->abosulteCheck){
    if(RzRadioGroupDTA->Buttons[0]->Checked){
      doseCheck->check(CHECKTYPE(ABS_DTA_FloatWay));
    }else if(RzRadioGroupDTA->Buttons[1]->Checked){
      doseCheck->check(CHECKTYPE(ABS_DTA_MidValueWay));
    }else if(RzRadioGroupDTA->Buttons[2]->Checked){
      doseCheck->check(CHECKTYPE(ABS_DTA_SamePositionWay));
    }
  }else{
    if(RzRadioGroupDTA->Buttons[0]->Checked){
      doseCheck->check(CHECKTYPE(REL_DTA_FloatWay));
    }else if(RzRadioGroupDTA->Buttons[1]->Checked){
      doseCheck->check(CHECKTYPE(REL_DTA_MidValueWay));
    }else if(RzRadioGroupDTA->Buttons[2]->Checked){
      doseCheck->check(CHECKTYPE(REL_DTA_SamePositionWay));
    }
  }



  *MainFormTempValue.checkedRecord.getSingleDTAResult() = *doseCheck->getCheckedRecord()->getSingleDTAResult();

  FormMain->showDTAResult();  

  MainFormTempValue.checkedRecord.setCheckedStatus(true);
  MainFormTempValue.checkedRecord.setCheckType(doseCheck->getCheckedRecord()->getCheckType());

  globalMem = NULL;
  doseCheck = NULL;

  Close();
}
//---------------------------------------------------------------------------
