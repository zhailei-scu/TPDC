//---------------------------------------------------------------------------

#ifndef caxSettingH
#define caxSettingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include "RzLabel.hpp"
#include "RzButton.hpp"
#include "doseshell.h"
#include "Util.h"
//---------------------------------------------------------------------------
class TFormCAX : public TForm
{
__published:	// IDE-managed Components
        TRzPanel *RzPanelCAX;
        TRzMemo *RzMemo1;
        TRzGroupBox *RzGroupBoxCAX;
        TRzSpinEdit *RzSpinEditCAX_X;
        TRzSpinEdit *RzSpinEditCAX_Y;
        TRzLabel *RzLabelCAX_X;
        TRzLabel *RzLabelCAX_Y;
        TRzBitBtn *RzBitBtnOK;
        TRzBitBtn *RzBitBtnCancel;
        TRzBitBtn *RzBitBtnReset;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RzBitBtnCancelClick(TObject *Sender);
        void __fastcall RzBitBtnResetClick(TObject *Sender);
private:	// User declarations
        FILETYPE fileType;
public:		// User declarations
        __fastcall TFormCAX(TComponent* Owner);
        __fastcall TFormCAX(TComponent* Owner,FILETYPE fileType);
        void __fastcall SetCAXAandShowFirst(TObject* Sender);
        void __fastcall SetCAXAandFlushFromMemory(TObject* Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCAX *FormCAX;
//---------------------------------------------------------------------------
#endif
