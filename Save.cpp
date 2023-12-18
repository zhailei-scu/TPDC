//---------------------------------------------------------------------------
#include "Save.h"
#include "doseshell.h"
#include "GatePairDose.h"
#include "GlobalData.h"
#include <process.h>
#include <windows.h>
//-----------------------Class:SavingInformation----------------------------
/*Constructor*/
SavingInformation::SavingInformation(){
  this->patientInfo = NULL;
  this->checkedRecord = NULL;
  this->savingDose = NULL;
  this->path.clear();

}
/*Destructor*/
SavingInformation::~SavingInformation(){
  TryToDelete<PatientInfo>(this->patientInfo);
  this->patientInfo = NULL;
  TryToDelete<CheckedRecord>(checkedRecord);
  this->checkedRecord = NULL;
  TryToDelete< MatrixData<float> >(this->savingDose);
  this->savingDose = NULL;

  this->path.clear();
  string().swap(this->path);
}

/*Copy Constructor*/
SavingInformation::SavingInformation(const SavingInformation& r){
  this->patientInfo = NULL;
  
  if(NULL != r.patientInfo){
    this->patientInfo = new PatientInfo();
    *this->patientInfo = *r.patientInfo;
  }

  this->checkedRecord = NULL;
  if(NULL != r.checkedRecord){
    this->checkedRecord = new CheckedRecord();
    *this->checkedRecord = *r.checkedRecord;
  }

  this->savingDose = NULL;
  if(NULL!=r.savingDose){
    this->savingDose = new MatrixData<float>();
    *this->savingDose = *r.savingDose;
  }

  this->path = r.path;
}

/*Overload operator = */
SavingInformation SavingInformation::operator = (const SavingInformation& r){

  if(NULL==r.patientInfo){
    this->patientInfo = NULL;
  }else{
    TryToDelete<PatientInfo>(this->patientInfo);
    this->patientInfo = new PatientInfo();
    *this->patientInfo = *r.patientInfo;
  }

  if(NULL==r.checkedRecord){
    this->checkedRecord = NULL;
  }else{
    TryToDelete<CheckedRecord>(checkedRecord);
    this->checkedRecord = new CheckedRecord();
    *this->checkedRecord = *r.checkedRecord;
  }

  if(NULL==r.savingDose){
    this->savingDose = NULL;
  }else{
    TryToDelete< MatrixData<float> >(this->savingDose);
    this->savingDose = new MatrixData<float>();
    *this->savingDose = *r.savingDose;
  }

  this->path = r.path;
  
  return *this;
}



//-----------------------Class:SaveFile-------------------------------------
/*----static members--------*/
//-------Singleton Model:Hungry model-------------
SaveFile* SaveFile::saveFileInstance = new SaveFile();
//-------Garbo------------------------------------
SaveFile::SaveFileGarbo SaveFile::saveFileGarboInstance;

/*SaveFile::Constructor*/
SaveFile::SaveFile(){
  this->saveFileInstance = NULL;
  this->threadMap.clear();
}

/*SaveFile::Destructor*/
SaveFile::~SaveFile(){
  map<unsigned,SavingInformation>::iterator itera=threadMap.begin();
  while(itera != threadMap.end()){
    threadMap.erase(itera++);
  }
  
  map<unsigned,SavingInformation>().swap(threadMap);

}


/*SaveFile::SaveFileGarbo Constructor*/
SaveFile::SaveFileGarbo::SaveFileGarbo(){
}

/*SaveFile::SaveFileGarbo Destructor*/
SaveFile::SaveFileGarbo::~SaveFileGarbo(){
  releaseInstance();
}

void SaveFile::releaseInstance(){
  TryToDelete<SaveFile>(saveFileInstance);
  saveFileInstance = NULL;
}

void SaveFile::save(SavingInformation savingInformation){
  unsigned threadId;

  HANDLE handle = (HANDLE)_beginthreadex(NULL,0,SaveFileThread,NULL,CREATE_SUSPENDED,&threadId);

  saveFileInstance->threadMap.insert(map<unsigned,SavingInformation>::value_type(threadId,savingInformation));
  ResumeThread(handle);

  /*CLose the Handle after the thread was creating, this would not affect
  the running of thread and could avoid the leak of handle,it is a great
  habit.*/
  CloseHandle(handle);
}

//--------------------------�����ļ��߳�----------------------------
unsigned __stdcall SaveFileThread(LPVOID pvParam){
  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;
  DosePair *dosePair = NULL;
  Dose* measureDisplayDose = NULL;
  Dose* calculateDose = NULL;
  MatrixData<double> *doseMatrix = NULL;

  unsigned threadId = GetCurrentThreadId();
  
  if(SaveFile::saveFileInstance->threadMap.count(threadId)<=0){
    throw "The thread disapperd";
  }
  SavingInformation saveInfo = SaveFile::saveFileInstance->threadMap[threadId];

  FILE *fp;
  if(saveInfo.path.empty()){
    throw "Saving file path is NULL";
  }
  fp = fopen(saveInfo.path.c_str(),"w");
  if(NULL == fp){
    throw "The path is gone...";
  }

  if(NULL == saveInfo.patientInfo){
    throw "Patient Info can not be null";
  }

  fprintf(fp,"ID ��");
  fprintf(fp,saveInfo.patientInfo->patientId.c_str());
  fprintf(fp,"\n");
  fprintf(fp,"Name ��");
  fprintf(fp,saveInfo.patientInfo->patientName.c_str());
  fprintf(fp,"\n");
  fprintf(fp,"Gender ��");
  string gender = saveInfo.patientInfo->patientGender>-1?(saveInfo.patientInfo->patientGender==0?"Male":"Female"):"";
  fprintf(fp,gender.c_str());
  fprintf(fp,"\n");
  fprintf(fp,"Age ��");
  fprintf(fp,saveInfo.patientInfo->patientAge.c_str());
  fprintf(fp,"\n");
  fprintf(fp,"Treatment Part ��");
  fprintf(fp,saveInfo.patientInfo->treatedPart.c_str());
  fprintf(fp,"\n");


  fprintf(fp,"---------------------------------------------------------------------\n");

  if(false==MainFormTempValue.checkedRecord.getCheckedStatus()){
    fprintf(fp,"δ����������֤\n");
  }else{
     if(MainFormTempValue.checkedRecord.getSingleGammaResult()->totalPassPercent>=0)   //�Ǹ���ʾ���Ǿ�����֤�Ľ��
     {
       fprintf(fp,"Gammaͨ���ʣ�");
       fprintf(fp,"%12.4f",MainFormTempValue.checkedRecord.getSingleGammaResult()->totalPassPercent);
       fprintf(fp,"\n");
     }
     else
     {
       fprintf(fp,"NOTE��GAMMAδ������֤���������֤����...\n");
     }

    if(MainFormTempValue.checkedRecord.getSingleDTAResult()->totalPassPercent>=0)   //�Ǹ���ʾ���Ǿ�����֤�Ľ��
     {
       fprintf(fp,"DTAͨ���ʣ�");
       fprintf(fp,"%12.4f",MainFormTempValue.checkedRecord.getSingleDTAResult()->totalPassPercent);
       fprintf(fp,"\n");
     }
     else
     {
       fprintf(fp,"NOTE��DTAδ������֤���������֤����...\n");
     }

    if(MainFormTempValue.checkedRecord.getSingleDDResult()->totalPassPercent>=0)   //�Ǹ���ʾ���Ǿ�����֤�Ľ��
     {
       fprintf(fp,"Gammaͨ���ʣ�");
       fprintf(fp,"%12.4f",MainFormTempValue.checkedRecord.getSingleDDResult()->totalPassPercent);
       fprintf(fp,"\n");
     }
     else
     {
       fprintf(fp,"NOTE��DDδ������֤���������֤����...\n");
     }
     fprintf(fp,"---------------------------------------------------------------------\n");
  }

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    return false;
  }
  
  gatePairDose = globalMem->getGatePairDose();
  if(NULL == gatePairDose){
    RunningLog::writeLog("The gatePairDose is NULL;");
    return false;
  }

  dosePair =  gatePairDose->getDosePair();
  if(NULL == dosePair){
    RunningLog::writeLog("The dosePair is NULL;");
    return false;
  }

  measureDisplayDose = dosePair->getMeasureDose();
  if(NULL == measureDisplayDose){
    RunningLog::writeLog("The measureDisplayDose is NULL;");
    return false;
  }

  doseMatrix = measureDisplayDose->getDoseMatrix();

  fprintf(fp,"--------------------------��������-----------------------------\n");

  if(NULL != doseMatrix && false == doseMatrix->isEmpty()){
    for(int j=0;j<doseMatrix->getColLength();j++){
      for(int i=0;i<doseMatrix->getRowLength();i++){
        fprintf(fp,"%12.4f",doseMatrix->at(i,j,0));
      }
      fprintf(fp,"\n");
    }
  }else{
    fprintf(fp,"NOTE��δ���������������...\n");
  }

  calculateDose =  dosePair->getCalculateDose();
  if(NULL == calculateDose){
    RunningLog::writeLog("The calculateDose is NULL;");
    return false;
  }

  fprintf(fp,"--------------------------�ƻ�����-----------------------------\n");

  doseMatrix = calculateDose->getDoseMatrix();
  if(NULL != doseMatrix && false == doseMatrix->isEmpty()){
    for(int j=0;j<doseMatrix->getColLength();j++){
      for(int i=0;i<doseMatrix->getRowLength();i++){
        fprintf(fp,"%12.4f",doseMatrix->at(i,j,0));
      }
      fprintf(fp,"\n");
    }
  }else{
    fprintf(fp,"NOTE��δ����ƻ���������...\n");
  }


  fclose(fp);


  globalMem = NULL;
  gatePairDose = NULL;
  dosePair = NULL;
  measureDisplayDose = NULL;
  calculateDose = NULL;
  doseMatrix = NULL;

  SaveFile::saveFileInstance->threadMap.erase(threadId);

  return 0;
}
