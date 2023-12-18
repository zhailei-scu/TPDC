//---------------------------------------------------------------------------

#ifndef BestFiveH
#define BestFiveH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "doseshell.h"
#include "RzPanel.hpp"
#include "RzRadGrp.hpp"
#include "RzButton.hpp"
#include "RzEdit.hpp"
//---------------------------------------------------------------------------
class TBestFiveForm : public TForm
{
__published:	// IDE-managed Components
        TRzRadioGroup *RzRadioGroupBest5;
        TRzMemo *RzMemoWords;
        TRzBitBtn *RzBitBtnOK;
        TRzBitBtn *RzBitBtnClose;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall RzBitBtnOKClick(TObject *Sender);
        void __fastcall RzBitBtnCloseClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TBestFiveForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBestFiveForm *BestFiveForm;
//---------------------------------------------------------------------------
#endif