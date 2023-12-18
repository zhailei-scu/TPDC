//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "doseshell.h"
#include "Changelevels.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGRID"
#pragma resource "*.dfm"
TFormLevels *FormLevels;
//---------------------------------------------------------------------------
__fastcall TFormLevels::TFormLevels(TComponent* Owner,TContourSeries* theSeries)
        : TForm(Owner)
{
  tempSeries = theSeries;
}
//---------------------------------------------------------------------------
__fastcall TFormLevels::~TFormLevels()
{

 thePanel.erase(thePanel.begin(),thePanel.end());
 colorLabel.erase(colorLabel.begin(),colorLabel.end());
 leveldata.erase(leveldata.begin(),leveldata.end());
 theButton.erase(theButton.begin(),theButton.end());
 thedelete.erase(thedelete.begin(),thedelete.end());

 //ʹ��һ���յ�ַ��ԭ�еĿؼ��������н������Ӷ�ʵ���ڴ����ȫ�ͷ�
 vector<TPanel*>().swap(thePanel);
 vector<TLabel*>().swap(colorLabel);
 vector<TEdit*>().swap(leveldata);
 vector<TCheckBox*>().swap(thedelete);
 vector<TButton*>().swap(theButton);

}
//---------------------------------------------------------------------------
void __fastcall TFormLevels::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree;  //�رղ��ͷ��ڴ�
}
//---------------------------------------------------------------------------
void __fastcall TFormLevels::FormCreate(TObject *Sender)
{
//
  this->ClientHeight = FormMain->ClientHeight*0.35;
  this->ClientWidth = FormMain->ClientWidth *0.085;
  this->AutoScroll = false;

  this->HeaderControl1->Sections->Items[0]->Width = 0.3*this->ClientWidth;
  this->HeaderControl1->Sections->Items[1]->Width = 0.4*this->ClientWidth;
  this->HeaderControl1->Sections->Items[2]->Width = 0.3*this->ClientWidth;


  InitialTheVcl();  //��ʼ��Vcl�ؼ�
}
//---------------------------------------------------------------------------
void __fastcall TFormLevels::MyClick(TObject *Sender)
{
  //
  ColorDialog1->Execute();
  //��Senderʵ���������������Label������ɫ�ı�
  TLabel *temp = new TLabel(this);
  temp = (TLabel*)Sender;   //����ת��
  temp->Color = ColorDialog1->Color;  //��������Label����ɫ�ı�
}
//---------------------------------------------------------------------------
void __fastcall TFormLevels::quedingClick(TObject *Sender)
{
  //
  int choose = MessageDlg("ȷ��������ز���?",mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0);

  if(choose == mrNo)
    return;

  int thesize = thePanel.size();
  int i;

  float tempnum;

  for(i=0;i<thesize;i++){

    if(StrToFloat(leveldata[i]->Text.c_str())>100.001){
      MessageBox(this->Handle,"��ֵ���ܴ���100","Warning!",MB_OK);
      return;
    }
  }

  //........................ʹSeries��������Ӧ�仯...................
  tempSeries->_shexian_ClearAllLevel();
  vector<TPanel*>::iterator iteratPanel =  thePanel.begin();
  vector<TEdit*>::iterator  iteratLeveldata = leveldata.begin();
  vector<TLabel*>::iterator iteratColorLabel = colorLabel.begin();
  while(iteratPanel != thePanel.end()){
    tempSeries->_shexian_AddLevel(StrToFloat(((TEdit*)(*iteratLeveldata))->Text.c_str()),((TLabel*)(*iteratColorLabel))->Color);

    iteratLeveldata++;
    iteratColorLabel++;
    iteratPanel++;
  }

  Close();

}
//---------------------------------------------------------------------------
void __fastcall TFormLevels::tianjiaClick(TObject *Sender)
{
  //
  thePanel.push_back(new TPanel(this));
  thePanel[thePanel.size()-1]->Parent = this;
  thePanel[thePanel.size()-1]->Show();
  thePanel[thePanel.size()-1]->Height = panelHeight;
  thePanel[thePanel.size()-1]->Top = this->HeaderControl1->ClientHeight+(thePanel.size()-1)*thePanel[thePanel.size()-1]->Height;
  thePanel[thePanel.size()-1]->Width = this->ClientWidth;
  thePanel[thePanel.size()-1]->BevelOuter = bvLowered;
  thePanel[thePanel.size()-1]->BevelInner = bvRaised;

  //��̬��ɫLabel
  colorLabel.push_back(new TLabel(this));
  colorLabel[colorLabel.size()-1]->Parent = thePanel[thePanel.size()-1];
  colorLabel[colorLabel.size()-1]->Color = clHotLight;  //����ӵ�Ԥ����ɫΪclHotLight
  colorLabel[colorLabel.size()-1]->Show();
  colorLabel[colorLabel.size()-1]->Height = thePanel[thePanel.size()-1]->Height*0.6;
  colorLabel[colorLabel.size()-1]->Width = colorLabel[colorLabel.size()-1]->Height;
  colorLabel[colorLabel.size()-1]->Top = (thePanel[thePanel.size()-1]->Height - colorLabel[colorLabel.size()-1]->Height)/2.0;
  colorLabel[colorLabel.size()-1]->Left = (this->HeaderControl1->Sections->Items[0]->Width - colorLabel[colorLabel.size()-1]->Width)/2.0;
  colorLabel[colorLabel.size()-1]->OnClick = MyClick;  //����̬�����OnClick�¼�ת��Ϊ�Զ����MyClick�¼����������⴦��

  //ɾ������
  thedelete.push_back(new TCheckBox(this));
  thedelete[thedelete.size()-1]->Parent = thePanel[thePanel.size()-1];
  thedelete[thedelete.size()-1]->Show();
  thedelete[thedelete.size()-1]->Height = 0.5*thePanel[thePanel.size()-1]->Height;
  thedelete[thedelete.size()-1]->Width = thedelete[thedelete.size()-1]->Height;
  thedelete[thedelete.size()-1]->Top = (thePanel[thePanel.size()-1]->Height - thedelete[thedelete.size()-1]->Height)/2.0;
  thedelete[thedelete.size()-1]->Left = this->HeaderControl1->Sections->Items[0]->Width + this->HeaderControl1->Sections->Items[1]->Width + (this->HeaderControl1->Sections->Items[2]->Width - thedelete[thedelete.size()-1]->Width)/2.0;
  thedelete[thedelete.size()-1]->ShowHint = true;
  thedelete[thedelete.size()-1]->Hint = "ɾ��";
  thedelete[thedelete.size()-1]->Checked = false;


  //�ȸ��ߵ���ֵ
  leveldata.push_back(new TEdit(this));
  leveldata[leveldata.size()-1]->Parent = thePanel[thePanel.size()-1];
  leveldata[leveldata.size()-1]->Show();
  leveldata[leveldata.size()-1]->Font->Size = 8;
  leveldata[leveldata.size()-1]->Height = thePanel[thePanel.size()-1]->Height*0.95;
  leveldata[leveldata.size()-1]->Width = 2*leveldata[thedelete.size()-1]->Height;
  leveldata[leveldata.size()-1]->Top = (thePanel[thePanel.size()-1]->Height - leveldata[leveldata.size()-1]->Height)/2.0;
  leveldata[leveldata.size()-1]->Left = this->HeaderControl1->Sections->Items[0]->Width + (this->HeaderControl1->Sections->Items[1]->Width - leveldata[leveldata.size()-1]->Width)/2.0;
  //Ԥ����ֵ
  leveldata[leveldata.size()-1]->Text = "500";


  //�������
  Formjustify();

}
//--------------------------------------------------------------------------
void __fastcall TFormLevels::shanchuClick(TObject *Sender)
{
  //����������ò��ˣ�ֻ��������ϼ򵥵ķ�����ɾ������
  int i,j,k,z;
  i= thedelete.size();  //�����Ĳ���֮ǰ�ĳߴ�
  k=-1;                  //�������������
  int choose =MessageDlg("ȷ��������ز���?",mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0);

  if(choose == mrNo)
    return;

  for(j=0;j<i;j++)
  {
    k++;
    if(k>=thedelete.size())
    {
      break;
    }

    if(thedelete[k]->Checked == true)
    {
      thedelete[k]->Free();    //ɾ���ؼ�
      thedelete.erase(thedelete.begin()+k);  //ɾ��vector�����еĿռ�
      colorLabel[k]->Free();
      colorLabel.erase(colorLabel.begin()+k);
      leveldata[k]->Free();
      leveldata.erase(leveldata.begin()+k);
      thePanel[k]->Free();
      thePanel.erase(thePanel.begin()+k);
      k--;        //ɾ��֮�������ĳߴ�仯������Ҫ��1
    }
  }

  //ɾ��֮������������Ҫ���µ���
  Formjustify();


}

//----------------------�������--------------------------------------------
void __fastcall TFormLevels::Formjustify()
{
  int i;
  int sizevector = thePanel.size();

  if(sizevector==0)
    return;

  ReSort();

  for(i=0;i<sizevector;i++)
  {
    thePanel[i]->Height= panelHeight;

    thePanel[i]->Top = this->HeaderControl1->ClientHeight+i*thePanel[i]->Height;
  }
  this->ClientHeight = this->HeaderControl1->Height + sizevector*panelHeight + bottomHeight;

  for(i=0;i<3;i++)
  {
    theButton[i]->Top = this->HeaderControl1->Height + sizevector*panelHeight +  (bottomHeight - theButton[i]->Height)/2.0;
  }
}
//----------------------��ʼ���ؼ�------------------------------------------
void __fastcall TFormLevels::InitialTheVcl()
{
  //
  panelHeight = this->ClientHeight*0.08;
  bottomHeight = this->ClientHeight*0.1;

  thePanel.clear();
  colorLabel.clear();
  leveldata.clear();
  thedelete.clear();
  theButton.clear();

  int i;
  int thesize = tempSeries->NumLevels;

  if(thesize!=0)
  {
     for(i=0;i<thesize;i++)
     {
       thePanel.push_back(new TPanel(this));
       thePanel[i]->Parent = this;
       thePanel[i]->Show();
       thePanel[i]->Height = panelHeight;
       thePanel[i]->Top = this->HeaderControl1->ClientHeight+i*thePanel[i]->Height;
       thePanel[i]->Width = this->ClientWidth;
       thePanel[i]->BevelOuter = bvLowered;
       thePanel[i]->BevelInner = bvRaised;

       //��̬��ɫLabel
       colorLabel.push_back(new TLabel(this));
       colorLabel[i]->Parent = thePanel[i];
       colorLabel[i]->Color = tempSeries->_shexian_GetLevelsCollection()->_shexian_GetTheLevel(i)->Color;
       colorLabel[i]->Show();
       colorLabel[i]->Height = thePanel[i]->Height*0.6;
       colorLabel[i]->Width = colorLabel[i]->Height;
       colorLabel[i]->Top = (thePanel[i]->Height - colorLabel[i]->Height)/2.0;
       colorLabel[i]->Left = (this->HeaderControl1->Sections->Items[0]->Width - colorLabel[i]->Width)/2.0;
       colorLabel[i]->OnClick = MyClick;  //����̬�����OnClick�¼�ת��Ϊ�Զ����MyClick�¼����������⴦��

       //�ȸ��ߵ���ֵ
        leveldata.push_back(new TEdit(this));
        leveldata[i]->Parent = thePanel[i];
        leveldata[i]->Show();
        leveldata[i]->Font->Size = 8;
        leveldata[i]->Height = thePanel[i]->Height*0.95;
        leveldata[i]->Width = 2*leveldata[i]->Height;
        leveldata[i]->Top = (thePanel[i]->Height - leveldata[i]->Height)/2.0;
        leveldata[i]->Left = this->HeaderControl1->Sections->Items[0]->Width + (this->HeaderControl1->Sections->Items[1]->Width - leveldata[i]->Width)/2.0;
        leveldata[i]->Text = tempSeries->_shexian_GetLevelsCollection()->_shexian_GetTheLevel(i)->UpToValue;

       //ɾ������
        thedelete.push_back(new TCheckBox(this));
        thedelete[i]->Parent = thePanel[i];
        thedelete[i]->Show();
        thedelete[i]->Height = 0.5*thePanel[i]->Height;
        thedelete[i]->Width = thedelete[i]->Height;
        thedelete[i]->Top = (thePanel[i]->Height - thedelete[i]->Height)/2.0;
        thedelete[i]->Left = this->HeaderControl1->Sections->Items[0]->Width + this->HeaderControl1->Sections->Items[1]->Width + (this->HeaderControl1->Sections->Items[2]->Width - thedelete[i]->Width)/2.0;
        thedelete[i]->ShowHint = true;
        thedelete[i]->Hint = "ɾ��";
        thedelete[i]->Checked = false;
     }

     for(i=0;i<3;i++)
     {
       theButton.push_back(new TButton(this));
       theButton[i]->Parent = this;
       theButton[i]->Show();
       theButton[i]->Height = bottomHeight*0.7;
       theButton[i]->Top = thePanel[thesize-1]->Top + thePanel[thesize-1]->Height + (bottomHeight - theButton[i]->Height)/2.0;
       theButton[i]->Width = this->ClientWidth*0.3;
       theButton[i]->Left = i*this->ClientWidth*0.3 + (i+1)*(this->ClientWidth - 3*theButton[i]->Width)/4.0;
      }

     theButton[0]->Caption = "ȷ��";
     theButton[1]->Caption = "���";
     theButton[2]->Caption = "ɾ��";

     theButton[0]->OnClick = quedingClick;
     theButton[1]->OnClick = tianjiaClick;
     theButton[2]->OnClick = shanchuClick;

     Formjustify();
  }
  else
  {
    for(i=0;i<3;i++)
    {
       theButton.push_back(new TButton(this));
       theButton[i]->Parent = this;
       theButton[i]->Show();
       theButton[i]->Height = this->ClientHeight*0.08;
       theButton[i]->Top = this->ClientHeight - theButton[i]->Height;
       theButton[i]->Width = this->ClientWidth*0.3;
       theButton[i]->Left = i*this->ClientWidth*0.3 + (i+1)*(this->ClientWidth - 3*theButton[i]->Width)/4.0;
      }

     theButton[0]->Caption = "ȷ��";
     theButton[1]->Caption = "���";
     theButton[2]->Caption = "ɾ��";

     theButton[0]->OnClick = quedingClick;
     theButton[1]->OnClick = tianjiaClick;
     theButton[2]->OnClick = shanchuClick;
  }

}


//-----------------------��������--------------------------------------
void __fastcall TFormLevels::ReSort(){

  int thesize;
  thesize= thePanel.size();

  struct tosort *ToSort;

  ToSort = new tosort[thesize];

  int i;

  for(i=0;i<thesize;i++){
    ToSort[i].thevalue = StrToFloat(leveldata[i]->Text.c_str());
    ToSort[i].thecolor = colorLabel[i]->Color;
    ToSort[i].thechecked = thedelete[i]->Checked;
  }


  QuickSort(ToSort,0,thesize-1);   //���ÿ��������㷨


  for(i=0;i<thesize;i++){
    leveldata[i]->Text = ToSort[i].thevalue;
    leveldata[i]->Parent = thePanel[i];
    colorLabel[i]->Color = ToSort[i].thecolor;
    colorLabel[i]->Parent = thePanel[i];
    thedelete[i]->Checked = ToSort[i].thechecked;
    thedelete[i]->Parent = thePanel[i];
  }
}


//-----------------------�������㷨---------------------------------------
void QuickSort(tosort *tst,int low,int high){
  int first = low;
  int last = high;

  if(low>high)
    return;

  float keydat = tst[first].thevalue;
  TColor keycolor = tst[first].thecolor;
  bool keychecked = tst[first].thechecked;

  while(first<last){
    while(first<last&&tst[last].thevalue>=keydat){
      --last;
    }
    tst[first].thevalue = tst[last].thevalue;
    tst[first].thecolor = tst[last].thecolor;
    tst[first].thechecked = tst[last].thechecked;

    while(first<last&&tst[first].thevalue<=keydat){
      ++first;
    }
    tst[last].thevalue = tst[first].thevalue;
    tst[last].thecolor = tst[first].thecolor;
    tst[last].thechecked = tst[first].thechecked;
  }

  tst[first].thevalue = keydat;
  tst[first].thecolor = keycolor;
  tst[first].thechecked = keychecked;

  QuickSort(tst,low,first-1);
  QuickSort(tst,first+1,high);

}
