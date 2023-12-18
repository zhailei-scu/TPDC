//---------------------------------------------------------------------------

#ifndef SystemsetH
#define SystemsetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TFormsystemSet : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TBitBtn *BitBtnOK;
        TBitBtn *BitBtnCancel;
        TRzEdit *RzEditX;
        TRzEdit *RzEditY;
        TRzEdit *RzEditZ;
        TRzLabel *RzLabelX;
        TRzLabel *RzLabelY;
        TRzLabel *RzLabelZ;
        TRzLabel *RzLabelUnit1;
        TRzLabel *RzLabelUnit2;
        TRzLabel *RzLabelUnit3;
        void __fastcall BitBtnOKClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BitBtnCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormsystemSet(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormsystemSet *FormsystemSet;
//---------------------------------------------------------------------------
#endif