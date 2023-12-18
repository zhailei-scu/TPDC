//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Info.h"
#include "process.h"
#include <windows.h>
#include "stdlib.h"
#include "doseshell.h"
#include "PrintSet.h"
#include "Save.h"
#include "GlobalData.h"
#include "GatePairDose.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzBckgnd"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TInfoForm *InfoForm;
//---------------------------------------------------------------------------
__fastcall TInfoForm::TInfoForm(TComponent* Owner)  //Default Constructor
          : TForm(Owner)
{
   this->ButtonYes->OnClick = this->PersistenVar;
}
//---------------------------------------------------------------------------
__fastcall TInfoForm::TInfoForm(TComponent* Owner,FILETYPE fileType)
        : TForm(Owner)
{
   this->fileType = fileType;
   this->ButtonYes->OnClick = this->PersistenVarAndSetAngle;
}
//---------------------------------------------------------------------------
__fastcall TInfoForm::~TInfoForm(){

}
//---------------------------------------------------------------------------
void __fastcall TInfoForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TInfoForm::ButtonCancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TInfoForm::ButtonResetClick(TObject *Sender)
{
  GlobalMembers *globalMem = NULL;
  PatientInfo *patientInfo = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  patientInfo = globalMem->getPatientInfo();
  if(NULL == patientInfo){
    RunningLog::writeLog("The patientInfo is NULL;",__LINE__);
    return;
  }

  this->EditName->Text = patientInfo->patientName.c_str();
  this->GenderComboBox->ItemIndex = patientInfo->patientGender;
  this->EditAge->Text = patientInfo->patientAge.c_str();
  this->EditId->Text = patientInfo->patientId.c_str();
  this->EditPart->Text = patientInfo->treatedPart.c_str();

  globalMem = NULL;
  patientInfo = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TInfoForm::FormCreate(TObject *Sender)
{
  GlobalMembers *globalMem = NULL;
  PatientInfo *patientInfo = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }


  if(NULL == globalMem->getPatientInfo()){
     globalMem->allocatePatientInfo();
  }
  patientInfo = globalMem->getPatientInfo();

  this->EditName->Text = patientInfo->patientName.c_str();
  this->GenderComboBox->ItemIndex = patientInfo->patientGender;
  this->EditAge->Text = patientInfo->patientAge.c_str();
  this->EditId->Text = patientInfo->patientId.c_str();
  this->EditPart->Text = patientInfo->treatedPart.c_str();

  globalMem = NULL;
  patientInfo = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TInfoForm::ToSave(TObject *Sender){
  SavingInformation* savingInfo = new SavingInformation();

  savingInfo->patientInfo = new PatientInfo();

  //patientName = this->EditName->Text;
  savingInfo->patientInfo->patientName = this->EditName->Text.c_str();

  //patientGender = this->GenderComboBox->ItemIndex;
  savingInfo->patientInfo->patientGender = this->GenderComboBox->ItemIndex;

  //patientAge = this->EditAge->Text;
  savingInfo->patientInfo->patientAge = this->EditAge->Text.c_str();

  //patientId = this->EditId->Text;
  savingInfo->patientInfo->patientId = this->EditId->Text.c_str();

  //treatedPart = this->EditPart->Text;
  savingInfo->patientInfo->treatedPart = this->EditPart->Text.c_str();

  this->Hide();

  if(this->SaveDialog1->Execute()){
    savingInfo->path = this->SaveDialog1->FileName.c_str();

    SaveFile::save(*savingInfo);
  }

  TryToDelete<SavingInformation>(savingInfo);

  Close();

}

//--------------------------------------------------------------------------
void __fastcall TInfoForm::ToPrint(TObject *Sender){


   Persist();

   FormMain->ShowBaseInfo();

   TPrintForm *PrintForm = new TPrintForm(Application);
   PrintForm->Parent = this->Parent;
   PrintForm->FormStyle = fsStayOnTop;
   PrintForm->Show();

   Hide();
   PrintForm->QuickRep1->Preview();

   Close();

}

//---------------------关闭之前保存变量---------------------------
void __fastcall TInfoForm::PersistenVar(TObject *Sender)
{
  Persist();
  
  Close();
}


//------------关闭前保存变量并且打开角度设置窗体，再从角度设置窗体退出时打开文件-----------------
void __fastcall TInfoForm::PersistenVarAndSetAngle(TObject *Sender)
{
  Persist();

  FormMain->angleSetting(this->fileType);
  Close();
}

void __fastcall TInfoForm::Persist(){
  GlobalMembers *globalMem = NULL;
  PatientInfo *patientInfo = NULL;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return;
  }

  if(NULL == globalMem->getPatientInfo()){
     globalMem->allocatePatientInfo();
  }
  patientInfo = globalMem->getPatientInfo();

  if(this->EditName->Text.IsEmpty()){
    MessageBox(this->Handle,"The name cannot be NULL","Warning!",MB_OK);
    this->EditName->Text = patientInfo->patientName.c_str();
    return;
  }

  if(this->EditAge->Text.IsEmpty()){
    MessageBox(this->Handle,"The age cannot be NULL","Warning!",MB_OK);
    this->EditAge->Text = patientInfo->patientAge.c_str();
    return;
  }

  if(this->EditId->Text.IsEmpty()){
    MessageBox(this->Handle,"The Patient ID cannot be NULL","Warning!",MB_OK);
    this->EditId->Text = patientInfo->patientId.c_str();
    return; 
  }

  if(this->EditPart->Text.IsEmpty()){
    MessageBox(this->Handle,"The treatment Part cannot be NULL","Warning!",MB_OK);
    this->EditPart->Text = patientInfo->treatedPart.c_str();
    return;
  }
  
  patientInfo->patientName = this->EditName->Text.c_str();
  patientInfo->patientGender = this->GenderComboBox->ItemIndex;
  patientInfo->patientAge = this->EditAge->Text.c_str();
  patientInfo->patientId = this->EditId->Text.c_str();
  patientInfo->treatedPart = this->EditPart->Text.c_str();

  globalMem = NULL;
  patientInfo = NULL;
}




