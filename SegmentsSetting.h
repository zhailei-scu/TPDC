//---------------------------------------------------------------------------

#ifndef SegmentsSettingH
#define SegmentsSettingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzEdit.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzLabel.hpp"
#include "RzSpnEdt.hpp"
#include "RzButton.hpp"
#include "RzRadChk.hpp"
//---------------------------------------------------------------------------
class TFormSegmentsSetting : public TForm
{
__published:	// IDE-managed Components
        TRzPanel *RzPanelSegments;
        TRzMemo *RzMemoSegments;
        TRzSpinner *RzSpinnerSegments;
        TRzLabel *RzLabelSegments;
        TRzBitBtn *RzBitBtnOK;
        TRzBitBtn *RzBitBtnClose;
        TRzCheckBox *Recommendatory;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RzBitBtnCloseClick(TObject *Sender);
        void __fastcall RzBitBtnOKClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall RecommendatoryClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormSegmentsSetting(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSegmentsSetting *FormSegmentsSetting;
//---------------------------------------------------------------------------
#endif
