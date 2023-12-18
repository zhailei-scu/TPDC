//---------------------------------------------------------------------------
#include "GlobalData.h"
#include "Cache.h"

//-----------------Class:GlobalMembers---------------------

/*----static members--------*/
//-------Singleton Model:Hungry model-------------
GlobalMembers* GlobalMembers::globalMembersInstance = new GlobalMembers();
//-------Garbo------------------------------------
GlobalMembers::CGarbo GlobalMembers::cGarboInstance;

/*GlobalMembers Constructor:Default*/
GlobalMembers::GlobalMembers(){
  this->patientInfo = new PatientInfo();
  this->gatePairDose = new GatePairDose();
  this->handledPairDose = new HandledPairDose();
  this->displayPairDose = new DisplayPairDose();

  this->doseCheck = new DoseCheck();

  this->handelModel = HANDLE_MODEL(ADAC);

  constructorObserverMode();
}

/*GlobalMembers Destructor*/
GlobalMembers::~GlobalMembers(){
  TryToDelete<PatientInfo>(this->patientInfo);
  this->patientInfo = NULL;

  TryToDelete<GatePairDose>(this->gatePairDose);
  this->gatePairDose = NULL;

  TryToDelete<HandledPairDose>(this->handledPairDose);
  this->handledPairDose = NULL;

  TryToDelete<DisplayPairDose>(this->displayPairDose);
  this->displayPairDose = NULL;

  TryToDelete<DoseCheck>(this->doseCheck);
  this->doseCheck = NULL;

  this->handelModel = HANDLE_MODEL(ADAC);
}

/*GlobalMembers::CGarbo Constructor*/
GlobalMembers::CGarbo::CGarbo(){
}

/*GlobalMembers::CGarbo Destructor*/
GlobalMembers::CGarbo::~CGarbo(){
  releaseInstance();
}

/*Basic Functions*/
GlobalMembers* GlobalMembers::getInstance(){
  if(NULL==globalMembersInstance){
    globalMembersInstance = new GlobalMembers();
  }
  return globalMembersInstance;
}

void GlobalMembers::releaseInstance(){
  TryToDelete<GlobalMembers>(globalMembersInstance);
  globalMembersInstance = NULL;
}

/*Other functions*/

/*Construct observer models between members*/
void GlobalMembers::constructorObserverMode(){
  if(NULL!=this->gatePairDose){
    if(NULL!=this->handledPairDose){
      this->gatePairDose->AddObserver(this->handledPairDose);

      if(NULL!=this->displayPairDose){
        //this->gatePairDose->AddObserver(this->displayPairDose);

        this->handledPairDose->AddObserver(this->displayPairDose);
      }
    }


  }

}

/*about member patientInfo*/
PatientInfo* GlobalMembers::getPatientInfo(){
  return this->patientInfo;
}

PatientInfo GlobalMembers::copyPatientInfo()throw(const char*){
  PatientInfo result;
  if(NULL!=this->patientInfo){
    result = *this->patientInfo;
  }
  return result;
}

void GlobalMembers::setPatientInfo(PatientInfo* _patientInfo)throw(const char*){
  TryToDelete<PatientInfo>(this->patientInfo);
  if(NULL==_patientInfo){
    this->patientInfo = NULL;
  }else{
    this->patientInfo = new PatientInfo();
    *this->patientInfo = *_patientInfo;
  }

}

void GlobalMembers::allocatePatientInfo(){
  TryToDelete<PatientInfo>(this->patientInfo);
  this->patientInfo =new PatientInfo();
}

void GlobalMembers::cleanPatientInfo(){
  TryToDelete<PatientInfo>(this->patientInfo);
  this->patientInfo = NULL;
}


 /*about member gatePairDose*/
GatePairDose* GlobalMembers::getGatePairDose(){
  return this->gatePairDose;
}

GatePairDose GlobalMembers::copyGatePairDose()throw(const char*){
  GatePairDose result;
  if(NULL!=this->gatePairDose){
    result = *this->gatePairDose;
  }

  return result;
}

void GlobalMembers::setGatePairDose(GatePairDose* _gatePairDose)throw(const char*){
  TryToDelete<GatePairDose>(this->gatePairDose);
  if(NULL==_gatePairDose){
    this->gatePairDose = NULL;
  }else{
    this->gatePairDose = new GatePairDose();
    *this->gatePairDose = *_gatePairDose;
  }

}

void GlobalMembers::allocateGatePairDose(){
  TryToDelete<GatePairDose>(this->gatePairDose);
  this->gatePairDose =new GatePairDose();
}

void GlobalMembers::cleanGatePairDose(){
  TryToDelete<GatePairDose>(this->gatePairDose);
  this->gatePairDose = NULL;
}


/*about member handledPairDose*/
HandledPairDose* GlobalMembers::getHandledPairDose(){
  return this->handledPairDose;
}

HandledPairDose GlobalMembers::copyHandledPairDose()throw(const char*){
  HandledPairDose result;
  if(NULL!=this->handledPairDose){
    result = *this->handledPairDose;
  }

  return result;
}

void GlobalMembers::setHandledPairDose(HandledPairDose* _handledPairDose)throw(const char*){
  TryToDelete<HandledPairDose>(this->handledPairDose);
  if(NULL==_handledPairDose){
    this->handledPairDose = NULL;
  }else{
    this->handledPairDose = new HandledPairDose();
    *this->handledPairDose = *_handledPairDose;
  }

}

void GlobalMembers::allocateHandledPairDose(){
  TryToDelete<HandledPairDose>(this->handledPairDose);
  this->handledPairDose =new HandledPairDose();
}

void GlobalMembers::cleanHandledPairDose(){
  TryToDelete<HandledPairDose>(this->handledPairDose);
  this->handledPairDose = NULL;
}


/*about member displayPairDose*/
DisplayPairDose* GlobalMembers::getDisplayPairDose(){
  return this->displayPairDose;
}

DisplayPairDose GlobalMembers::copyDisplayPairDose()throw(const char*){
  DisplayPairDose result;
  if(NULL!=this->displayPairDose){
    result = *this->displayPairDose;
  }
  return result;
}

void GlobalMembers::setDisplayPairDose(DisplayPairDose* _displayPairDose)throw(const char*){
  TryToDelete<DisplayPairDose>(this->displayPairDose);
  if(NULL==_displayPairDose){
    this->displayPairDose = NULL;
  }else{
  this->displayPairDose = new DisplayPairDose();
    *this->displayPairDose = *_displayPairDose;
  }

}

void GlobalMembers::allocateDisplayPairDose(){
  TryToDelete<DisplayPairDose>(this->displayPairDose);
  this->displayPairDose =new DisplayPairDose();
}

void GlobalMembers::cleanDisplayPairDose(){
  TryToDelete<DisplayPairDose>(this->displayPairDose);
  this->displayPairDose = NULL;
}

/*about member doseCheck*/
DoseCheck* GlobalMembers::getDoseCheck(){
  return this->doseCheck;
}

DoseCheck GlobalMembers::copyDoseCheck(){
  DoseCheck result;
  if(NULL != this->doseCheck){
    result = *this->doseCheck;
  }
  return result;
}

void GlobalMembers::setDoseCheck(DoseCheck* _doseCheck){
  TryToDelete<DoseCheck>(this->doseCheck);
  if(NULL==_doseCheck){
    this->doseCheck = NULL;
  }else{
  this->doseCheck = new DoseCheck();
    *this->doseCheck = *_doseCheck;
  }
}

void GlobalMembers::allocateDoseCheck(){
  TryToDelete<DoseCheck>(this->doseCheck);
  this->doseCheck = new DoseCheck();
}

void GlobalMembers::cleanDoseCheck(){
  TryToDelete<DoseCheck>(this->doseCheck);
  this->doseCheck = NULL;
}

void GlobalMembers::initialDoseCheck(){
  TryToDelete<DoseCheck>(this->doseCheck);
  this->doseCheck = new DoseCheck();
}


HANDLE_MODEL GlobalMembers::getHandel_Model(){
  return this->handelModel;
}

void GlobalMembers::setHandel_Model(HANDLE_MODEL model){
  this->handelModel = model; 
}

/*Case Cache*/
void GlobalMembers::flushToCache(){
  Cache* cacheInstance = NULL;
  deque<PatientData>* theCacheDque = NULL;
  
  PatientData currentPatientData;

  bool patientExist = false;

  cacheInstance = Cache::getCacheInstance();
  if(NULL == cacheInstance){
    RunningLog::writeLog("The Cache is NULL",__LINE__);
    return;
  }

  theCacheDque = cacheInstance->getPatientDateDque();

  if(NULL == theCacheDque){
    RunningLog::writeLog("The Cache Dque is NULL",__LINE__);
    return;
  }

  for(deque<PatientData>::iterator itera = theCacheDque->begin();itera != theCacheDque->end();itera++){
    if(itera->getBaseInfo()->patientId == this->patientInfo->patientId){
      //the patient has already exit
      patientExist = true;

      /*add or update the angle dosePair*/
      if(0 == itera->getDataMap()->count(this->gatePairDose->copyAngle())){
        itera->getDataMap()->insert(map<string,DosePair>::value_type(this->gatePairDose->copyAngle(),*this->gatePairDose->getDosePair()));
      }else{
        itera->getDataMap()->erase(this->gatePairDose->copyAngle());
        itera->getDataMap()->insert(map<string,DosePair>::value_type(this->gatePairDose->copyAngle(),*this->gatePairDose->getDosePair()));
      }
      
      break;

    }
  }

  if(false == patientExist){
    currentPatientData.setBaseInfo(this->patientInfo);
    currentPatientData.addOneAngleDosePair(this->getGatePairDose()->copyAngle(),this->getGatePairDose()->getDosePair());

    cacheInstance->add(&currentPatientData);
  }

  cacheInstance = NULL;
  theCacheDque = NULL;
}

void GlobalMembers::flushMeasureToCache(){
  Cache* CacheInstance = NULL;
  deque<PatientData>* theCacheDque = NULL;
  
  PatientData currentPatientData;

  bool patientExist = false;

  CacheInstance = Cache::getCacheInstance();
  if(NULL == CacheInstance){
    RunningLog::writeLog("The Cache is NULL",__LINE__);
    return;
  }

  theCacheDque = CacheInstance->getPatientDateDque();

  if(NULL == theCacheDque){
    RunningLog::writeLog("The Cache Dque is NULL",__LINE__);
    return;
  }

  for(deque<PatientData>::iterator itera = theCacheDque->begin();itera != theCacheDque->end();itera++){
    if(itera->getBaseInfo()->patientId == this->patientInfo->patientId){
      //the patient has already exit
      patientExist = true;

      
      if(0 == itera->getDataMap()->count(this->gatePairDose->copyAngle())){    //The angle not exist
        itera->getDataMap()->insert(map<string,DosePair>::value_type(this->gatePairDose->copyAngle(),*this->gatePairDose->getDosePair()));
      }else{      //The angle has already existed
        map<string,DosePair>::iterator pairIterar = itera->getDataMap()->find(this->gatePairDose->copyAngle());
        pairIterar->second.setMeasureDose(this->gatePairDose->getDosePair()->getMeasureDose());
      }

      break;

    }
  }

  if(false == patientExist){
    currentPatientData.setBaseInfo(this->patientInfo);
    currentPatientData.addOneAngleDosePair(this->getGatePairDose()->copyAngle(),this->getGatePairDose()->getDosePair());

    CacheInstance->add(&currentPatientData);
  }

  CacheInstance = NULL;
  theCacheDque = NULL;
}

void GlobalMembers::flushCalculateToCache(){
  Cache* cacheInst = NULL;
  deque<PatientData>* theCacheDque = NULL;

  bool patientExist = false;

  cacheInst = Cache::getCacheInstance();
  if(NULL == cacheInst){
    RunningLog::writeLog("The Cache is NULL",__LINE__);
    return;
  }

  theCacheDque = cacheInst->getPatientDateDque();

  if(NULL == theCacheDque){
    RunningLog::writeLog("The Cache Dque is NULL",__LINE__);
    return;
  }

  for(deque<PatientData>::iterator itera = theCacheDque->begin();itera != theCacheDque->end();itera++){
    if(itera->getBaseInfo()->patientId == this->patientInfo->patientId){
      //the patient has already exit
      patientExist = true;

      if(0 != itera->getDataMap()->count(this->gatePairDose->copyAngle())){     //The angle already exist
        map<string,DosePair>::iterator pairIterar = itera->getDataMap()->find(this->gatePairDose->copyAngle());
        pairIterar->second.setCalculateDose(this->gatePairDose->getDosePair()->getCalculateDose());
      }

      break;

    }
  }

  if(false == patientExist){
    RunningLog::writeLog("Please load the patient Info and measure file first!",__LINE__);
  }

  cacheInst = NULL;
  theCacheDque = NULL;
}

void GlobalMembers::flushFromCache(int index,string angle){
  Cache* instanceOfCache = NULL;
  deque<PatientData>* theCacheDque = NULL;

  instanceOfCache = Cache::getCacheInstance();
  if(NULL == instanceOfCache){
    RunningLog::writeLog("The Cache is NULL",__LINE__);
    return;
  }

  theCacheDque = instanceOfCache->getPatientDateDque();

  if(NULL == theCacheDque){
    RunningLog::writeLog("The Cache Dque is NULL",__LINE__);
    return;
  }

  if(index>=theCacheDque->size()){
    RunningLog::writeLog("The cache index is out of boundary",__LINE__);
    return;
  }


  if(0==theCacheDque->at(index).getDataMap()->count(angle)){
    RunningLog::writeLog("Can not find special angle data",__LINE__);
    return;
  }

  map<string,DosePair>::iterator pairIterar = theCacheDque->at(index).getDataMap()->find(angle);

  this->patientInfo->reset();
  //patientInfo
  *this->patientInfo = *theCacheDque->at(index).getBaseInfo();

  //gatepaireDose

  //angle
  this->gatePairDose->setAngle(angle);
  //DosePair
  this->gatePairDose->setDosePair(pairIterar->second);


  //Notify
  this->gatePairDose->Notify(Message_Notify(Update_measure_fromGatePair));
  this->gatePairDose->Notify(Message_Notify(Update_calculate_fromGatePair));
  
  instanceOfCache = NULL;
  theCacheDque = NULL;
}
