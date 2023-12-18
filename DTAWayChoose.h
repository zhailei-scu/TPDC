//---------------------------------------------------------------------------

#ifndef DTAWayChooseH
#define DTAWayChooseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include "RzRadGrp.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzLabel.hpp"
//---------------------------------------------------------------------------
class TFormDTAWayChoose : public TForm
{
__published:	// IDE-managed Components
        TRzPanel *RzPanelDTA;
        TRzRadioGroup *RzRadioGroupDTA;
        TRzLabel *RzLabelDTA;
        TRzBitBtn *RzBitBtnOK;
        TRzBitBtn *RzBitBtnCancel;
        void __fastcall RzBitBtnOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
       bool abosulteCheck;
        __fastcall TFormDTAWayChoose(TComponent* Owner,bool absoulte);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDTAWayChoose *FormDTAWayChoose;
//---------------------------------------------------------------------------
#endif
