//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SegmentsSetting.h"
#include "doseshell.h"
#include "GlobalData.h"
#include "GatePairDose.h"
#include "Util.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma link "RzLabel"
#pragma link "RzSpnEdt"
#pragma link "RzButton"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TFormSegmentsSetting *FormSegmentsSetting;
//---------------------------------------------------------------------------
__fastcall TFormSegmentsSetting::TFormSegmentsSetting(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSegmentsSetting::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree;        
}
//---------------------------------------------------------------------------

void __fastcall TFormSegmentsSetting::RzBitBtnCloseClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

void __fastcall TFormSegmentsSetting::RzBitBtnOKClick(TObject *Sender)
{
  int segmentsNum[3];

  GlobalMembers *globalMem = NULL;
  GatePairDose  *gatePairDose = NULL;
  HandledPairDose *handledPairDose = NULL;

  Hide();

  for(int i=0;i<3;i++){
    segmentsNum[i] = RzSpinnerSegments->Value;
  }

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    return;
  }

  gatePairDose = globalMem->getGatePairDose();
  if(NULL == gatePairDose){
    RunningLog::writeLog("The gatePairDose is NULL;");
    return;
  }

  gatePairDose->getDosePair()->getMeasureDose()->sync_setSegments(segmentsNum);
  gatePairDose->Notify(Update_Segments);
  //handledPairDose =  globalMem->getHandledPairDose();

  //handledPairDose->update();

  globalMem = NULL;
  gatePairDose = NULL;

  FormMain->RefreshMeasureDoseGraphicFromDisplayValue();


  if(!MainFormTempValue.calcFilePath.empty()){
    FormMain->RefreshCalculateDoseGraphicFromDisplayValue();
  }

  
  Close();        
}
//---------------------------------------------------------------------------

void __fastcall TFormSegmentsSetting::FormCreate(TObject *Sender)
{
  RzSpinnerSegments->Value = MainFormTempValue.segments[0];
}
//---------------------------------------------------------------------------

void __fastcall TFormSegmentsSetting::RecommendatoryClick(TObject *Sender)
{
  RzSpinnerSegments->Value = getGridSegments(MainFormTempValue.gridSize[0]);
}
//---------------------------------------------------------------------------

