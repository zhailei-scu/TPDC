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
        void __fastcall MyClick(TObject *Sender);  //将动态数组的OnClick事件转化为自定义的MyClick事件，进行特殊处理
        void __fastcall quedingClick(TObject *Sender); //确定
        void __fastcall tianjiaClick(TObject *Sender); //添加
        void __fastcall shanchuClick(TObject *Sender); //删除

        void __fastcall InitialTheVcl();
        void __fastcall Formjustify(); //窗体调整
        void __fastcall ReSort();    //重新排序记录


private:	// User declarations
        TContourSeries* tempSeries;  //记录等高线Levels操作所对应的Series
        float panelHeight; //每个Panel的高度
        float bottomHeight; //窗体中最后一个Panel到窗体底部的高度
public:		// User declarations

        vector<TPanel*> thePanel;  //动态控件
        vector<TLabel*> colorLabel;
        vector<TEdit*> leveldata;
        vector<TCheckBox*> thedelete;
        vector<TButton*> theButton;


        __fastcall TFormLevels(TComponent* Owner,TContourSeries* theSeries);//theSeries:对应于哪一个Series被操作
        __fastcall ~TFormLevels();  //析构函数必须写，不然容器无法释放
};
//---------------------------------------------------------------------------

//定义这个结构体，一个记录数值，一个记录对应的颜色，一个记录是否被选中
struct tosort{
  float thevalue;
  TColor thecolor;
  bool thechecked;
};

void QuickSort(tosort *tst,int low,int high);  //快排序


extern PACKAGE TFormLevels *FormLevels;
//---------------------------------------------------------------------------
#endif