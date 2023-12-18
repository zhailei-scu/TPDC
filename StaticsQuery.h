//---------------------------------------------------------------------------

#ifndef StaticsQueryH
#define StaticsQueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzRadGrp.hpp"
#include "RzLabel.hpp"
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class TFormStaticQuery : public TForm
{
__published:	// IDE-managed Components
        TRzPanel *RzPanelStaticQuery;
        TRzRadioGroup *RzRadioGroupStaticsType;
        TRzLabel *RzLabelStaticChoose;
        TRzBitBtn *RzBitBtnOK;
        TRzBitBtn *RzBitBtnCancel;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RzBitBtnCancelClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall RzBitBtnOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormStaticQuery(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormStaticQuery *FormStaticQuery;
//---------------------------------------------------------------------------
#endif
