//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NormPointSet.h"
#include "doseshell.h"
#include "handledPairDose.h"
#include "GlobalData.h"
#include "GatePairDose.h"
#include "Util.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzSpnEdt"
#pragma link "RzButton"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TFormNormPointSet *FormNormPointSet;
//---------------------------------------------------------------------------
__fastcall TFormNormPointSet::TFormNormPointSet(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormNormPointSet::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree;        
}
//---------------------------------------------------------------------------
void __fastcall TFormNormPointSet::RzBitBtnCancelClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TFormNormPointSet::RzBitBtnOKClick(TObject *Sender)
{
  //
  Hide();

  GlobalMembers *globalMem = NULL;
  HandledPairDose  *handledPairDose = NULL;
  GridPoint normPoint_gridLine;
  PhysicalPoint normPoint_physicPos;
  HANDLE_MODEL handel_Model;

  int xLineNum,yLineNum;
  double xPos,yPos;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    return;
  }
  handel_Model = globalMem->getHandel_Model();
  
  handledPairDose =  globalMem->getHandledPairDose();


  if(true == UseGridLineNum->Checked){
    xLineNum  = RzSpinEditGridLineX->Text.ToInt() + MainFormTempValue.measureFirstAlignmentCenter.row;
    yLineNum = RzSpinEditGridLineY->Text.ToInt() + MainFormTempValue.measureFirstAlignmentCenter.col;
    if( xLineNum>=0 && xLineNum<MainFormTempValue.measureRowLength &&
       yLineNum>=0 && yLineNum<MainFormTempValue.measureColLength){
      normPoint_gridLine.row = xLineNum;
      normPoint_gridLine.col = yLineNum;
      normPoint_gridLine.level = 0;
    }else{
      MessageBox(this->Handle,"Out of dose plan ","Warning!",MB_OK);
      return;
    }



    handledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),normPoint_gridLine,handel_Model);
    handledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),normPoint_gridLine,handel_Model);

    handledPairDose->Notify(Message_Notify(Update_measure_fromHandledPairDose));
    handledPairDose->Notify(Message_Notify(Update_calculate_fromHandledPairDose));

  }else if(UsePhysicalPos->Checked){

    xPos = (RzSpinEditPosX->Text.ToDouble() + MainFormTempValue.measureDoseCentral.x);
    yPos = RzSpinEditPosY->Text.ToDouble() + MainFormTempValue.measureDoseCentral.y;
    if( xPos>=0 && xPos<=(MainFormTempValue.measureRowLength-1)*MainFormTempValue.gridSize[0] &&
       yPos>=0 && yPos<=(MainFormTempValue.measureColLength-1)*MainFormTempValue.gridSize[1]){
      normPoint_physicPos.x = xPos;
      normPoint_physicPos.y = yPos;
      normPoint_physicPos.z = 0;
    }else{
      MessageBox(this->Handle,"Out of dose plan ","Warning!",MB_OK);
      return;
    }

    handledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),normPoint_physicPos);
    handledPairDose->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),normPoint_physicPos);

    handledPairDose->Notify(Message_Notify(Update_measure_fromHandledPairDose));
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
void __fastcall TFormNormPointSet::RzCheckBoxGridLineCenterClick(TObject *Sender)
{
  RzSpinEditGridLineX->Text = 0;
  RzSpinEditGridLineY->Text = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFormNormPointSet::UseGridLineNumClick(TObject *Sender)
{
  UsePhysicalPos->Checked = false;
  RzGroupBoxPos->Enabled = false;

  RzGroupBoxGridLine->Enabled = true;
  UseGridLineNum->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormNormPointSet::UsePhysicalPosClick(TObject *Sender)
{

  UseGridLineNum->Checked = false;
  RzGroupBoxGridLine->Enabled = false;

  UsePhysicalPos->Checked = true;
  RzGroupBoxPos->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormNormPointSet::RzCheckBoxPosCenterClick(
      TObject *Sender)
{
  RzSpinEditPosX->Text = 0.000;
  RzSpinEditPosY->Text = 0.000;        
}
//---------------------------------------------------------------------------

void __fastcall TFormNormPointSet::FormCreate(TObject *Sender)
{
  //
  PhysicalPoint measureNormPos,calcNormPos;
  
  measureNormPos = MainFormTempValue.checkedRecord.getSingleGammaResult()->normPosition_measure;
  calcNormPos = MainFormTempValue.checkedRecord.getSingleGammaResult()->normPosition_calculate;

  if(false == MainFormTempValue.checkedRecord.getSingleGammaResult()->manualSelectMeasureNormValue){

    RzSpinEditGridLineX->Value = convertFromPhyPosToGridPoint(measureNormPos.x,MainFormTempValue.measureFirstAlignmentCenter.row,MainFormTempValue.gridSize[0]);
    RzSpinEditGridLineY->Value = convertFromPhyPosToGridPoint(measureNormPos.y,MainFormTempValue.measureFirstAlignmentCenter.col,MainFormTempValue.gridSize[1]);
  
    RzSpinEditPosX->Value = convertPositionToActualPosition(measureNormPos,MainFormTempValue.measureDoseCentral).x;
    RzSpinEditPosY->Value = convertPositionToActualPosition(measureNormPos,MainFormTempValue.measureDoseCentral).y;
  }

}
//---------------------------------------------------------------------------

