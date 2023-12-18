//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
//---------------------------------------------------------------------
#pragma link "RzButton"
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------

void __fastcall TAboutBox::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree; //ÊÍ·ÅÄÚ´æ
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::RzBitBtn1Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

