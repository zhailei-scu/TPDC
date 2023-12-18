//---------------------------------------------------------------------------

#ifndef SmoothingH
#define SmoothingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include "RzRadGrp.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzChkLst.hpp"
#include "RzLstBox.hpp"
#include "RzSpnEdt.hpp"
#include <Buttons.hpp>
#include "RzRadChk.hpp"
//---------------------------------------------------------------------------
#include <vector>
#include <map>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
class TSmoothingForm : public TForm
{
__published:	// IDE-managed Components
        TRzBitBtn *RzBitBtnOK;
        TRzBitBtn *RzBitBtnClose;
        TRzRadioGroup *RzRadioGroupGauss;
        TRzRadioButton *Gauss3Orders;
        TRzRadioButton *Gauss5Orders;
        TRzRadioGroup *RzRadioGroupMedium;
        TRzRadioButton *Medium3Orders;
        TRzRadioButton *Medium5Orders;
        TRzRadioGroup *RzRadioGroupAverage;
        TRzRadioButton *Average3Orders;
        TRzRadioButton *Average5Orders;
        TRzBitBtn *RzBitBtnReset;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RzBitBtnCloseClick(TObject *Sender);
        void __fastcall RzBitBtnOKClick(TObject *Sender);
        void __fastcall RzBitBtnResetClick(TObject *Sender);
public:
       enum SmmothChoose{
         Gauss3OrdersChoosed = 10,
         Gauss5OrdersChoosed = 11,
         Medium3OrdersChoosed = 20,
         Medium5OrdersChoosed = 21,
         Average3OrdersChoosed = 30,
         Average5OrdersChoosed = 31,
       };
private:	// User declarations
        vector<TRzRadioButton*> RadioButtonList;
        map<TRzRadioButton*,SmmothChoose> RadioButtonChooseMap;

        void __fastcall startToSmooth(SmmothChoose choose);
public:		// User declarations
        __fastcall TSmoothingForm(TComponent* Owner);
        __fastcall ~TSmoothingForm();

        void __fastcall RadioButtonChecked(TObject *Sender);   //define the Checked action for each RadioButtons
};
//---------------------------------------------------------------------------
extern PACKAGE TSmoothingForm *SmoothingForm;
//---------------------------------------------------------------------------
#endif