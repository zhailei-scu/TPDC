//---------------------------------------------------------------------------

#ifndef InfoH
#define InfoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include "RzBckgnd.hpp"
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <string>

#include "Util.h"

using namespace std;

//---------------------------------------------------------------------------
class TInfoForm : public TForm
{
__published:	// IDE-managed Components
        TSaveDialog *SaveDialog1;
        TRzGroupBox *RzGroupBox1;
        TRzSeparator *RzSeparator1;
        TRzLabel *LabelID;
        TRzEdit *EditId;
        TRzSeparator *RzSeparator2;
        TRzLabel *LabelName;
        TRzEdit *EditName;
        TRzSeparator *RzSeparator3;
        TRzLabel *LabelAge;
        TRzNumericEdit *EditAge;
        TRzSeparator *RzSeparator4;
        TRzLabel *LabelGender;
        TRzComboBox *GenderComboBox;
        TRzLabel *LabelTreatPart;
        TRzSeparator *RzSeparator5;
        TRzEdit *EditPart;
        TRzBitBtn *ButtonYes;
        TRzBitBtn *ButtonReset;
        TRzBitBtn *ButtonCancel;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ButtonCancelClick(TObject *Sender);
        void __fastcall ButtonResetClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);


        void __fastcall ToSave(TObject *Sender); //为“确定”按钮定制保存功能
        void __fastcall ToPrint(TObject *Sender); //为“确定”按钮定制打印功能
private:	// User declarations
        FILETYPE fileType;
        void __fastcall PersistenVar(TObject *Sender);
        void __fastcall PersistenVarAndSetAngle(TObject *Sender);
public:		// User declarations
        __fastcall TInfoForm(TComponent* Owner);  //Default;
        __fastcall TInfoForm(TComponent* Owner,FILETYPE fileType);
private: 
         void __fastcall Persist();

        __fastcall ~TInfoForm();  //析构函数
};

//---------------------------------------------------------------------------
extern PACKAGE TInfoForm *InfoForm;
//---------------------------------------------------------------------------
#endif