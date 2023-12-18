//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzRadGrp"
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma resource "*.dfm"

#include "BestFive.h"
#include "doseshell.h"
#include "GlobalData.h"

TBestFiveForm *BestFiveForm;
//---------------------------------------------------------------------------
__fastcall TBestFiveForm::TBestFiveForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TBestFiveForm::FormCreate(TObject *Sender)
{
  //默认选择GAMMA为BestFive的比较方式
  this->RzRadioGroupBest5->Buttons[2]->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TBestFiveForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  //关闭时释放窗体所占内存
  Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TBestFiveForm::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
   CanClose = true;
}
//---------------------------------------------------------------------------
void __fastcall TBestFiveForm::RzBitBtnOKClick(TObject *Sender)
{
  GlobalMembers *globalMem = NULL;
  DoseCheck* doseCheck = NULL;
  
  if(MainFormTempValue.measureFilePath.empty()||
     MainFormTempValue.calcFilePath.empty()){
    string errStr = "验证之前必须先读入";
    errStr.append(MainFormTempValue.measureFilePath.empty()?"测量数据":"计划数据");
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

  if(true==this->RzRadioGroupBest5->Buttons[0]->Checked){        //ABS_BESTFIVE_DTA

    if(DoseType(DOSE_RELATIVE) == MainFormTempValue.doseType){
      MessageBox(this->Handle,"The relative dose can not be applied to absolute compare.","Warning!",MB_OK);
      return;
    }
    doseCheck->check(CHECKTYPE(ABS_BESTFIVE_DTA));
    *MainFormTempValue.checkedRecord.getBestFiveResult() = *doseCheck->getCheckedRecord()->getBestFiveResult();
    MainFormTempValue.checkedRecord.setCheckedStatus(true);
    MainFormTempValue.checkedRecord.setCheckType(ABS_BESTFIVE_DTA);
  }else if(true==this->RzRadioGroupBest5->Buttons[1]->Checked){  //ABS_BESTFIVE_GAMMA
    if(DoseType(DOSE_RELATIVE) == MainFormTempValue.doseType){
      MessageBox(this->Handle,"The relative dose can not be applied to absolute compare.","Warning!",MB_OK);
      return;
    }

    doseCheck->check(CHECKTYPE(ABS_BESTFIVE_GAMMA));
    *MainFormTempValue.checkedRecord.getBestFiveResult() = *doseCheck->getCheckedRecord()->getBestFiveResult();
    MainFormTempValue.checkedRecord.setCheckedStatus(true);
    MainFormTempValue.checkedRecord.setCheckType(ABS_BESTFIVE_GAMMA);
  }else if(true==this->RzRadioGroupBest5->Buttons[2]->Checked){  //REL_BESTFIVE_DTA

    doseCheck->check(CHECKTYPE(REL_BESTFIVE_DTA));
    *MainFormTempValue.checkedRecord.getBestFiveResult() = *doseCheck->getCheckedRecord()->getBestFiveResult();
    MainFormTempValue.checkedRecord.setCheckedStatus(true);
    MainFormTempValue.checkedRecord.setCheckType(REL_BESTFIVE_DTA);
  }else if(true==this->RzRadioGroupBest5->Buttons[3]->Checked){  //REL_BESTFIVE_GAMMA

    doseCheck->check(CHECKTYPE(REL_BESTFIVE_GAMMA));
    *MainFormTempValue.checkedRecord.getBestFiveResult() = *doseCheck->getCheckedRecord()->getBestFiveResult();
    MainFormTempValue.checkedRecord.setCheckedStatus(true);
    MainFormTempValue.checkedRecord.setCheckType(REL_BESTFIVE_GAMMA);
  }


  globalMem = NULL;
  doseCheck = NULL;

  FormMain->ShowBestFiveResult();
  
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TBestFiveForm::RzBitBtnCloseClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

