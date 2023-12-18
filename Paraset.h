//---------------------------------------------------------------------------

#ifndef ParasetH
#define ParasetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzTabs.hpp"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include "RzSpnEdt.hpp"
#include <Buttons.hpp>
#include "RzLabel.hpp"
#include <Graphics.hpp>
#include "RzEdit.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TFormparaset : public TForm
{
__published:	// IDE-managed Components
        TRzBitBtn *RzBitBtnOK;
        TRzPanel *RzPanelStandard;
        TRzBitBtn *RzBitBtnCancel;
        TRzBitBtn *RzBitBtnApply;
        TRzBitBtn *RzBitBtnReset;
        TRzPageControl *TableStandard;
        TRzTabSheet *TableDistanceAndDosePercentDifference;
        TRzLabel *RzLabelDosePercentDifference;
        TRzLabel *RzLabelDistanceStandard;
        TImage *ImageGammaShow;
        TRzSpinEdit *DosePercentDifference;
        TRzSpinEdit *DistanceStandard;
        TRzTabSheet *TableDoseUncertainty;
        TRzLabel *RzLabelDtaAllowDoseUncertainty;
        TImage *ImageDTAAllowDoseDifference;
        TRzSpinEdit *DtaAllowDoseUncertainty;
        TRzTabSheet *TabSheet1;
        TRzTabSheet *TableBest5Standard;
        TRzLabel *RzLabelBestFiveDoseThreshold;
        TImage *ImageBestFiveDoseThreshold;
        TRzLabel *RzLabelDetails;
        TRzSpinEdit *BestFiveDoseThreshold;
        TRzTabSheet *Threshold;
        TRzLabel *RzLabelDoseThreshold;
        TImage *ImageDoseThreshold;
        TRzLabel *RzLabelDoseThresholdGap;
        TRzSpinEdit *DoseThreshold;
        TRzTabSheet *TableDoseGap;
        TRzSpinEdit *AllowableMaxDoseGap;
        TRzLabel *RzLabeAllowDoseGapComment;
        TRzLabel *RzLabelDoseGap;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RzBitBtnCancelClick(TObject *Sender);
        void __fastcall RzBitBtnOKClick(TObject *Sender);
        void __fastcall RzBitBtnResetClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormparaset(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormparaset *Formparaset;
//---------------------------------------------------------------------------
#endif