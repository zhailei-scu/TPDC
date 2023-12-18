//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ShowBestFiveResult.h"
#include "doseshell.h"
#include "GlobalData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzEdit"
#pragma resource "*.dfm"
TBestFiveResultForm *BestFiveResultForm;
//---------------------------------------------------------------------------
__fastcall TBestFiveResultForm::TBestFiveResultForm(TComponent* Owner)
        : TForm(Owner)
{
}

__fastcall TBestFiveResultForm::~TBestFiveResultForm(){
  theRzMemos.erase(theRzMemos.begin(),theRzMemos.end());
  vector<TRzMemo*>().swap(theRzMemos);
}
//---------------------------------------------------------------------------
void __fastcall TBestFiveResultForm::FormCreate(TObject *Sender)
{
  this->Width = FormMain->ClientWidth*0.15;
  this->Height = FormMain->ClientHeight*0.43;

  theRzMemos.clear();

  for(int p=0;p<5;p++){
    theRzMemos.push_back(new TRzMemo(this));
    theRzMemos[p]->Parent = this;
    theRzMemos[p]->Show();
    theRzMemos[p]->Height = this->ClientHeight*0.2;
    theRzMemos[p]->Width = this->Width;
    theRzMemos[p]->Top = p*this->ClientHeight*0.2;
    theRzMemos[p]->ReadOnly = true;
    theRzMemos[p]->Color = clGradientActiveCaption;
    theRzMemos[p]->Cursor = crHandPoint;
    theRzMemos[p]->OnClick = BestFiveItemClick;
    theRzMemos[p]->Tag = p; //Use tag to record

  }
  ShowFiveResult();
}
//---------------------------------------------------------------------------
void __fastcall TBestFiveResultForm::ShowFiveResult(){
  BestFive_Single bestFive_Single;
  for(int p=0;p<5;p++){

    bestFive_Single = MainFormTempValue.checkedRecord.getBestFiveResult()->bestFiveResult[p];
    theRzMemos[p]->Lines->Add("Percent: " + FormatFloat("0.00",bestFive_Single.totalPassPercent));
    theRzMemos[p]->Lines->Add("Total: " + AnsiString(bestFive_Single.totalComparedCount)
                              + "   Passed: " + AnsiString(bestFive_Single.passedCount));
    theRzMemos[p]->Lines->Add("Normlization Point: (" + AnsiString(bestFive_Single.normPoint.row) + ","
                              + AnsiString(bestFive_Single.normPoint.col) + ")");
  }
}

void __fastcall TBestFiveResultForm::BestFiveItemClick(TObject *Sender){
  GlobalMembers *globalMem = NULL;
  DoseCheck* doseCheck = NULL;
  GridPoint normPoint;

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

  normPoint = MainFormTempValue.checkedRecord.getBestFiveResult()->bestFiveResult[((TRzMemo*)Sender)->Tag].normPoint;

  switch(MainFormTempValue.checkedRecord.getCheckType())
  {
    case CHECKTYPE(ABS_BESTFIVE_DTA):
    {
      doseCheck->check(CHECKTYPE(ABS_DTA_MidValueWay),normPoint);
      *MainFormTempValue.checkedRecord.getSingleDTAResult() = *doseCheck->getCheckedRecord()->getSingleDTAResult();
      MainFormTempValue.checkedRecord.setCheckedStatus(true);
      MainFormTempValue.checkedRecord.setCheckType(CHECKTYPE(ABS_DTA_MidValueWay));
    }
    break;

    case CHECKTYPE(ABS_BESTFIVE_GAMMA):
    {
      doseCheck->check(CHECKTYPE(ABS_GAMMA),normPoint);
      *MainFormTempValue.checkedRecord.getSingleGammaResult() = *doseCheck->getCheckedRecord()->getSingleGammaResult();
      MainFormTempValue.checkedRecord.setCheckedStatus(true);
      MainFormTempValue.checkedRecord.setCheckType(CHECKTYPE(ABS_GAMMA));
    }
    break;

    case CHECKTYPE(REL_BESTFIVE_DTA):
    {
      doseCheck->check(CHECKTYPE(REL_DTA_MidValueWay),normPoint);
      *MainFormTempValue.checkedRecord.getSingleDTAResult() = *doseCheck->getCheckedRecord()->getSingleDTAResult();
      MainFormTempValue.checkedRecord.setCheckedStatus(true);
      MainFormTempValue.checkedRecord.setCheckType(CHECKTYPE(REL_DTA_MidValueWay));
    }
    break;

    case CHECKTYPE(REL_BESTFIVE_GAMMA):
    {
      doseCheck->check(CHECKTYPE(REL_GAMMA),normPoint);
      *MainFormTempValue.checkedRecord.getSingleGammaResult() = *doseCheck->getCheckedRecord()->getSingleGammaResult();
      MainFormTempValue.checkedRecord.setCheckedStatus(true);
      MainFormTempValue.checkedRecord.setCheckType(CHECKTYPE(REL_GAMMA));
    }
    break;

    default:
    break;

  }

  FormMain->MemoResultShow();
  
  globalMem = NULL;
  doseCheck = NULL;

  Close();
}
