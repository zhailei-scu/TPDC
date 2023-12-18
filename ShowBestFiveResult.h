//---------------------------------------------------------------------------

#ifndef ShowBestFiveResultH
#define ShowBestFiveResultH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzEdit.hpp"
#include "doseshell.h"
#include <vector>

using namespace std;

//---------------------------------------------------------------------------
class TBestFiveResultForm : public TForm
{
__published:	// IDE-managed Components
  void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TBestFiveResultForm(TComponent* Owner);
  void __fastcall ShowFiveResult();

  __fastcall ~TBestFiveResultForm();
public:
  vector<TRzMemo*> theRzMemos;

  void __fastcall BestFiveItemClick(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TBestFiveResultForm *BestFiveResultForm;
//---------------------------------------------------------------------------
#endif