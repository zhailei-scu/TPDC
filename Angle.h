//---------------------------------------------------------------------------

#ifndef AngleH
#define AngleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <Mask.hpp>

#include "windows.h"
#include "Util.h"
//---------------------------------------------------------------------------
class TFormAngle : public TForm
{
__published:	// IDE-managed Components
        TRzPanel *PanelAngle;
        TRzMemo *RzMemoAngle;
        TRzEdit *RzEditAngle;
        TRzLabel *RzLabelAngle;
        TRzBitBtn *RzBitBtnOK;
        TRzBitBtn *RzBitBtnCancel;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RzBitBtnCancelClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
        FILETYPE fileType;
public:		// User declarations
        void __fastcall PersistVar(TObject *Sender);
        __fastcall TFormAngle(TComponent* Owner,FILETYPE fileType);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAngle *FormAngle;
//---------------------------------------------------------------------------
#endif
