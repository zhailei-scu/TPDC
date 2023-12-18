//---------------------------------------------------------------------------

#ifndef ChangelevelsH
#define ChangelevelsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CGRID.h"
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <CustomizeDlg.hpp>
#include <ComCtrls.hpp>
#include <vector>
#include <list>
#include <windows.h>
using namespace std;
//--------------------------------------------------------------------------
class TFormLevels : public TForm
{
__published:	// IDE-managed Components
        TColorDialog *ColorDialog1;
        THeaderControl *HeaderControl1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall MyClick(TObject *Sender);  //����̬�����OnClick�¼�ת��Ϊ�Զ����MyClick�¼����������⴦��
        void __fastcall quedingClick(TObject *Sender); //ȷ��
        void __fastcall tianjiaClick(TObject *Sender); //���
        void __fastcall shanchuClick(TObject *Sender); //ɾ��

        void __fastcall InitialTheVcl();
        void __fastcall Formjustify(); //�������
        void __fastcall ReSort();    //���������¼


private:	// User declarations
        TContourSeries* tempSeries;  //��¼�ȸ���Levels��������Ӧ��Series
        float panelHeight; //ÿ��Panel�ĸ߶�
        float bottomHeight; //���������һ��Panel������ײ��ĸ߶�
public:		// User declarations

        vector<TPanel*> thePanel;  //��̬�ؼ�
        vector<TLabel*> colorLabel;
        vector<TEdit*> leveldata;
        vector<TCheckBox*> thedelete;
        vector<TButton*> theButton;


        __fastcall TFormLevels(TComponent* Owner,TContourSeries* theSeries);//theSeries:��Ӧ����һ��Series������
        __fastcall ~TFormLevels();  //������������д����Ȼ�����޷��ͷ�
};
//---------------------------------------------------------------------------

//��������ṹ�壬һ����¼��ֵ��һ����¼��Ӧ����ɫ��һ����¼�Ƿ�ѡ��
struct tosort{
  float thevalue;
  TColor thecolor;
  bool thechecked;
};

void QuickSort(tosort *tst,int low,int high);  //������


extern PACKAGE TFormLevels *FormLevels;
//---------------------------------------------------------------------------
#endif