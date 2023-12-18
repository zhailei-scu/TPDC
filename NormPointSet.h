//---------------------------------------------------------------------------

#ifndef NormPointSetH
#define NormPointSetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include "RzButton.hpp"
#include "RzRadChk.hpp"
//---------------------------------------------------------------------------
class TFormNormPointSet : public TForm
{
__published:	// IDE-managed Components
        TRzPanel *RzPanelNormPoint;
        TRzLabel *RzLabelCaption;
        TRzBitBtn *RzBitBtnOK;
        TRzBitBtn *RzBitBtnCancel;
        TRzGroupBox *RzGroupBoxGridLine;
        TRzLabel *RzLabelGridLineY;
        TRzLabel *RzLabelGridLineX;
        TRzCheckBox *RzCheckBoxGridLineCenter;
        TRzSpinEdit *RzSpinEditGridLineY;
        TRzSpinEdit *RzSpinEditGridLineX;
        TRzGroupBox *RzGroupBoxPos;
        TRzLabel *RzLabelPosY;
        TRzLabel *RzLabelPosX;
        TRzSpinEdit *RzSpinEditPosX;
        TRzSpinEdit *RzSpinEditPosY;
        TRzCheckBox *RzCheckBoxPosCenter;
        TRzRadioButton *UseGridLineNum;
        TRzRadioButton *UsePhysicalPos;
        TRzGroupBox *RzGroupBoxOtherSetting;
        TRzCheckBox *RzCheckBoxOmniProModel;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RzBitBtnCancelClick(TObject *Sender);
        void __fastcall RzBitBtnOKClick(TObject *Sender);
        void __fastcall RzCheckBoxGridLineCenterClick(TObject *Sender);
        void __fastcall UseGridLineNumClick(TObject *Sender);
        void __fastcall UsePhysicalPosClick(TObject *Sender);
        void __fastcall RzCheckBoxPosCenterClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormNormPointSet(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormNormPointSet *FormNormPointSet;
//---------------------------------------------------------------------------
#endif
