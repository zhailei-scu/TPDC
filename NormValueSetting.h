//---------------------------------------------------------------------------
#pragma once
#ifndef NormValueSettingH
#define NormValueSettingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzRadChk.hpp"
#include "RzBckgnd.hpp"
#include "RzRadGrp.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzLabel.hpp"
//---------------------------------------------------------------------------
class TNormValueSetForm : public TForm
{
__published:	// IDE-managed Components
        TRzPanel *RzPanelNormValue;
        TRzCheckBox *RzCheckBoxMeasure;
        TRzCheckBox *RzCheckBoxCalculate;
        TRzSeparator *RzSeparatorNormValue;
        TRzRadioGroup *MeasureNormValueSetting;
        TRzSeparator *RzSeparator2;
        TRzBitBtn *RzBitBtnOK;
        TRzBitBtn *RzBitBtnCancel;
        TRzNumericEdit *EditMeasureNormValue;
        TRzLabel *RzLabelMeasure;
        TRzRadioGroup *CalcNormValueSetting;
        TRzLabel *RzLabelCalc;
        TRzNumericEdit *EditCalculateNormValue;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RzBitBtnCancelClick(TObject *Sender);
        void __fastcall RzCheckBoxMeasureMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall RzCheckBoxCalculateMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall RzBitBtnOKClick(TObject *Sender);
        void __fastcall MeasureNormValueSettingChanging(TObject *Sender,
          int NewIndex, bool &AllowChange);
        void __fastcall CalcNormValueSettingChanging(TObject *Sender,
          int NewIndex, bool &AllowChange);
private:	// User declarations
public:		// User declarations
        __fastcall TNormValueSetForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNormValueSetForm *NormValueSetForm;
//---------------------------------------------------------------------------
#endif
