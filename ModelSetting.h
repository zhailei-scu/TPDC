//---------------------------------------------------------------------------

#ifndef NormOptionH
#define NormOptionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include <ExtCtrls.hpp>
#include "RzBckgnd.hpp"
#include "RzEdit.hpp"
#include "RzRadGrp.hpp"
//---------------------------------------------------------------------------
class TModelSettingForm : public TForm
{
__published:	// IDE-managed Components
        TRzPanel *RzPanelNormValue;
        TRzSeparator *RzSeparator;
        TRzBitBtn *RzBitBtnOK;
        TRzBitBtn *RzBitBtnCancel;
        TRzMemo *RzMemoInfo;
        TRzRadioGroup *ModelGroup;
        void __fastcall RzBitBtnOKClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RzBitBtnCancelClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TModelSettingForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TModelSettingForm *ModelSettingForm;
//---------------------------------------------------------------------------
#endif
