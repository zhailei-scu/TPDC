//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DDStatistic.h"
#include "GlobalData.h"
#include "doseshell.h"
#include "Util.h"
#include <sstream>
#include <map>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma link "RzRadGrp"
#pragma link "RzButton"
#pragma link "RzLabel"
#pragma resource "*.dfm"
TFormDDStatics *FormDDStatics;


using namespace std;
//---------------------------------------------------------------------------
__fastcall TFormDDStatics::TFormDDStatics(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormDDStatics::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree;        
}
//---------------------------------------------------------------------------
void __fastcall TFormDDStatics::RzBitBtnOKClick(TObject *Sender)
{
   //
   Hide();

  ostringstream os;
  double range = this->maxDoseDoseDifference - this->minDoseDoseDifference;
  double eachRange;
  int rank;
  double threshold1 = RzNumericEditStart->Text.ToDouble();
  double threshold2 = RzNumericEditEnd->Text.ToDouble();
  int threshold1Count = 0;
  int threshold2Count = 0;
  int threshold3Count = 0;
  int tempCount = 0;
  int tempTotalCount = 0;
  MatrixData<double> matirx = MainFormTempValue.checkedRecord.getSingleDDResult()->everyPointResults;
  map<int,int> countMap;
  map<int,int>::iterator itera;

  os.str("");
  os<<"Total: " <<this->totalCount;
  FormMain->TreeResult->Items->AddChild(FormMain->TreeResult->NodeFromPath("Check Result\\Dose Difference"),os.str().c_str());

  os.str("");
  os<<"Pass: "<<this->passCount;
  FormMain->TreeResult->Items->AddChild(FormMain->TreeResult->NodeFromPath("Check Result\\Dose Difference"),os.str().c_str());

  os.str("");
  os<<"PassPercent: "<<FormatFloat("0.00",this->passedPercent).c_str()<<"%";
  FormMain->TreeResult->Items->AddChild(FormMain->TreeResult->NodeFromPath("Check Result\\Dose Difference"),os.str().c_str());


  if(RzRadioGroupDD->Buttons[0]->Checked){
    eachRange = range/10.0;
    for(int j=0;j<matirx.getColLength();j++){
      for(int i=0;i<matirx.getRowLength();i++){

        if( matirx.at(i,j,0)>-8888){
           rank = floor((matirx.at(i,j,0) - this->minDoseDoseDifference)/eachRange);

           if(countMap.count(rank)>0){
             itera = countMap.find(rank);
             tempCount = itera->second;
             countMap.erase(rank);
             countMap.insert(map<int,int>::value_type(rank,++tempCount));
           }else if(0 == countMap.count(rank)){
             countMap.insert(map<int,int>::value_type(rank,1));
           }
        }
      }
    }

    for(int i=0;i<9;i++){
      itera = countMap.find(i);
      tempCount = itera->second;
      tempTotalCount = tempTotalCount + tempCount;
      os.str("");
      os<<(this->minDoseDoseDifference + i*eachRange)<<" cGy To "<<(this->minDoseDoseDifference + (i+1)*eachRange)<<" cGy : "<<tempCount<<"("<<100*tempCount/(float)this->totalCount<<"%)";
      FormMain->TreeResult->Items->AddChild(FormMain->TreeResult->NodeFromPath("Check Result\\Dose Difference"),os.str().c_str());
    }

    /*Last one range*/
    os.str("");
    os<<(this->minDoseDoseDifference + 9*eachRange)<<" cGy To "<<this->maxDoseDoseDifference<<" cGy : "<<(totalCount - tempTotalCount)<<"("<<100*(totalCount - tempTotalCount)/(float)this->totalCount<<"%)";
    FormMain->TreeResult->Items->AddChild(FormMain->TreeResult->NodeFromPath("Check Result\\Dose Difference"),os.str().c_str());

  }else if(RzRadioGroupDD->Buttons[1]->Checked){
    for(int j=0;j<matirx.getColLength();j++){
      for(int i=0;i<matirx.getRowLength();i++){

        if( matirx.at(i,j,0)>-8888){
           if(matirx.at(i,j,0)>=this->minDoseDoseDifference && matirx.at(i,j,0)<threshold1){
             threshold1Count++;
           }

           if(matirx.at(i,j,0)>=threshold1 && matirx.at(i,j,0)<threshold2){
             threshold2Count++;
           }

           if(matirx.at(i,j,0)>=threshold2){
             threshold3Count++;
           }

        }
      }
    }


    os.str("");
    os<<this->minDoseDoseDifference<<" cGy To "<<threshold1<<" cGy : "<<threshold1Count<<"("<<100*threshold1Count/(float)this->totalCount<<"%)";
    FormMain->TreeResult->Items->AddChild(FormMain->TreeResult->NodeFromPath("Check Result\\Dose Difference"),os.str().c_str());

    os.str("");
    os<<threshold1<<" cGy To "<<threshold2<<" cGy : "<<threshold2Count<<"("<<100*threshold2Count/(float)this->totalCount<<"%)";
    FormMain->TreeResult->Items->AddChild(FormMain->TreeResult->NodeFromPath("Check Result\\Dose Difference"),os.str().c_str());

    os.str("");
    os<<threshold2<<" cGy To "<<this->maxDoseDoseDifference<<" cGy : "<<threshold3Count<<"("<<100*threshold3Count/(float)this->totalCount<<"%)";
    FormMain->TreeResult->Items->AddChild(FormMain->TreeResult->NodeFromPath("Check Result\\Dose Difference"),os.str().c_str());

  }
}
//---------------------------------------------------------------------------
void __fastcall TFormDDStatics::FormCreate(TObject *Sender)
{
  //

  ostringstream os;
  int totalCompared = MainFormTempValue.checkedRecord.getSingleDDResult()->totalComparedCount;

  os<<"Total Count: "<<totalCompared;
  RzMemoDD->Lines->Add(os.str().c_str());

  os.str("");

  double theMaxDoseDoseDifference = getMaxValue(MainFormTempValue.checkedRecord.getSingleDDResult()->everyPointResults);
  double theMinDoseDoseDifference = getMinValue(MainFormTempValue.checkedRecord.getSingleDDResult()->everyPointResults,-888888);


  this->maxDoseDoseDifference = theMaxDoseDoseDifference;
  this->minDoseDoseDifference = theMinDoseDoseDifference;
  this->totalCount = totalCompared;
  this->passCount = MainFormTempValue.checkedRecord.getSingleDDResult()->passedCount;
  this->passedPercent = MainFormTempValue.checkedRecord.getSingleDDResult()->totalPassPercent;
  os<<"From: "<<theMinDoseDoseDifference<<"cGy To: "<<theMaxDoseDoseDifference<<"cGy";
  RzMemoDD->Lines->Add(os.str().c_str());

}
//---------------------------------------------------------------------------
