//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "StaticsQuery.h"
#include "doseshell.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzRadGrp"
#pragma link "RzLabel"
#pragma link "RzButton"
#pragma resource "*.dfm"
TFormStaticQuery *FormStaticQuery;
//---------------------------------------------------------------------------
__fastcall TFormStaticQuery::TFormStaticQuery(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormStaticQuery::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TFormStaticQuery::RzBitBtnCancelClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TFormStaticQuery::FormCreate(TObject *Sender)
{
  this->RzRadioGroupStaticsType->Buttons[0]->Checked = true;        
}
//---------------------------------------------------------------------------
void __fastcall TFormStaticQuery::RzBitBtnOKClick(TObject *Sender)
{
  Hide();
  if(true==this->RzRadioGroupStaticsType->Buttons[0]->Checked){  //measurement dose analysis
    FormMain->showMeasureDoseStatic();
  }else if(true==this->RzRadioGroupStaticsType->Buttons[1]->Checked){  //calculate dose analysis
    FormMain->showCalculateDoseStatic();
  }else if(true==this->RzRadioGroupStaticsType->Buttons[2]->Checked){  //check result analysis
    MessageBox(this->Handle,"If there are multi-checkType selected,the default prior order is GAMMA>DTA>DD","Warning!",MB_OK);
    FormMain->showCheckResultStatic();
  }

  Close();        
}
//---------------------------------------------------------------------------
