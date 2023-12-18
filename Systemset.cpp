//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Systemset.h"
#include "doseshell.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma resource "*.dfm"
TFormsystemSet *FormsystemSet;
//---------------------------------------------------------------------------
__fastcall TFormsystemSet::TFormsystemSet(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TFormsystemSet::BitBtnOKClick(TObject *Sender)
{
   //������ѡ�ύ���
   this->Hide();

   double gridSize[3];

   gridSize[0] = atof(this->RzEditX->Text.c_str());
   gridSize[1] = atof(this->RzEditY->Text.c_str());
   gridSize[2] = atof(this->RzEditZ->Text.c_str());

   if( fabs(gridSize[0] - MainFormTempValue.gridSize[0])>0.02 ||
       fabs(gridSize[1] - MainFormTempValue.gridSize[1])>0.02){

     FormMain->upDataGridSize(gridSize);
   }

   Close();

}
//---------------------------------------------------------------------------
void __fastcall TFormsystemSet::FormCreate(TObject *Sender)
{
   RzEditX->Text = FormatFloat("0.00",MainFormTempValue.gridSize[0]);
   RzEditY->Text = FormatFloat("0.00",MainFormTempValue.gridSize[1]);
   RzEditZ->Text = FormatFloat("0.00",MainFormTempValue.gridSize[2]);
}
//---------------------------------------------------------------------------

void __fastcall TFormsystemSet::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree; //�ͷŴ����ڴ�
}
//---------------------------------------------------------------------------

void __fastcall TFormsystemSet::BitBtnCancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
