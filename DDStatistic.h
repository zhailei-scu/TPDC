//---------------------------------------------------------------------------

#ifndef DDStatisticH
#define DDStatisticH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzEdit.hpp"
#include "RzPanel.hpp"
#include "RzRadGrp.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TFormDDStatics : public TForm
{
__published:	// IDE-managed Components
        TRzPanel *RzPanelDD;
        TRzMemo *RzMemoDD;
        TRzRadioGroup *RzRadioGroupDD;
        TRzBitBtn *RzBitBtnOK;
        TRzBitBtn *RzBitBtnCAncel;
        TRzNumericEdit *RzNumericEditStart;
        TRzNumericEdit *RzNumericEditEnd;
        TRzLabel *RzLabel1;
        TRzLabel *RzLabel2;
        TRzLabel *RzLabel3;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RzBitBtnOKClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
       double maxDoseDoseDifference;
       double minDoseDoseDifference;
       int totalCount;
       int passCount;
       double passedPercent;
        __fastcall TFormDDStatics(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDDStatics *FormDDStatics;
//---------------------------------------------------------------------------
#endif
