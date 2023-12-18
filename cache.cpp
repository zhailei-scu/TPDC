//---------------------------------------------------------------------------
#include "Cache.h"
#include "LogFrame.h"

//-----------Class:SingleDose--------------------------------------------------
///*Constructor*/
//SingleDose::SingleDose(){
//
//  /*Initialize the CriticalSection,which must be done before any thread trying to use the special CriticialSection*/
//  /*Note:it is a advance usage of InitializeCriticalSectionAndSpinCount and let its second param to 1,which can return "FALSE" while
//  getting some error in the time of initialize the CriticalSection.It is also the reason to use this function other than "InitializeCriticalSection()"*/
//  if (InitializeCriticalSectionAndSpinCount(&(this->g_cs_isReadedbyOthersNow), 1) &&
//      InitializeCriticalSectionAndSpinCount(&(this->g_cs_isModifing), 1)){
//
//    /*Release the CriticalSection while initialize the Class of Dose*/
//    if (!TryEnterCriticalSection(&(this->g_cs_isReadedbyOthersNow))){
//      /*While there are not exist any other thread is using the protected data,current thread
//      get access to visit the data,or the current thread would wait till get the access,note:
//      the process of waitting criticalSection only happend in the user modual and would not inner
//      the keneral,it is a good way to avoid the switching between keneral and user modual,which
//      can save lots of time.*/
//      EnterCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//      LeaveCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//    }
//    else{
//      LeaveCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//    }
//
//    if (!TryEnterCriticalSection(&(this->g_cs_isModifing))){
//      EnterCriticalSection(&(this->g_cs_isModifing));
//      this->doseData = NULL;
//      LeaveCriticalSection(&(this->g_cs_isModifing));
//    }
//    else{
//      LeaveCriticalSection(&(this->g_cs_isModifing));
//    }
//
//  }
//  else{
//    RunningLog::writeLog("临界区初始化失败" + __LINE__);
//  }
//}
//
//
///*Destructor*/
//SingleDose::~SingleDose(){
//  /*Make sure that the CriticalSection is not used by any thread before clear the memory of data*/
//  EnterCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//
//
//  EnterCriticalSection(&(this->g_cs_isModifing));
//
//  TryToDelete<Dose>(this->doseData);
//  this->doseData = NULL;
//
//  LeaveCriticalSection(&(this->g_cs_isModifing));
//
//  LeaveCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//
//  /*Delete the CriticalSection in the end of structure data*/
//  DeleteCriticalSection(&(this->g_cs_isModifing));
//  DeleteCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//
//}
//
///*Copy Constructor*/
//SingleDose::SingleDose(SingleDose& r){
//
//    if(NULL == &r){
//      EnterCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//      this->doseData = NULL;
//      LeaveCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//    }else{
//      EnterCriticalSection(&(r.g_cs_isModifing));
//
//      EnterCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//
//      TryToDelete<Dose>(this->doseData);
//      this->doseData = new Dose();
//      *this->doseData = *r.doseData;
//
//      LeaveCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//      LeaveCriticalSection(&(r.g_cs_isModifing));
//    }
//
//
//
//}
//
///* Overload the operator = */
//SingleDose SingleDose::operator = (SingleDose& r){
//
//  if(NULL == &r){
//    EnterCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//    TryToDelete<Dose>(this->doseData);
//    this->doseData = NULL;
//    LeaveCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//  }else{
//    EnterCriticalSection(&(r.g_cs_isModifing));
//
//    EnterCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//    TryToDelete<Dose>(this->doseData);
//
//    if(NULL == r.doseData){
//      this->doseData = NULL;
//    }else{
//      this->doseData = new Dose();
//      *this->doseData = *r.doseData;
//    }
//
//    LeaveCriticalSection(&(this->g_cs_isReadedbyOthersNow));
//    LeaveCriticalSection(&(r.g_cs_isModifing));
//  }
//
//  return *this;
//}
//
//Dose* SingleDose::getDose(){
//  Dose* result;
//  EnterCriticalSection(&(this->g_cs));
//  /*Copy the producted data*/
//  if (NULL == this->doseData){
//    result = NULL;
//  }
//  else{
//    result = new Dose();
//    *result = *this->doseData;
//  }
//
//  /*Leave the CriticalSection,which means that the protected data can be visit by other threads*/
//  LeaveCriticalSection(&(this->g_cs));
//
//}
//
//void SingleDose::setDose(Dose *doseData){
//
//  if (InitializeCriticalSectionAndSpinCount(&(this->g_cs), 1)){
//    EnterCriticalSection(&(this->g_cs));
//
//    if (NULL == &doseData){
//      this->doseData = NULL;
//    }
//    else{
//      TryToDelete<Dose>(this->doseData);
//      if (NULL == this->doseData){
//        this->doseData = new Dose();
//      }
//      *this->doseData = *doseData;
//    }
//
//    LeaveCriticalSection(&(this->g_cs));
//  }
//  else{
//    RunningLog::writeLog("临界区初始化失败" + __LINE__);
//  }
//}
//
//Dose copyDose();
//void allocateDose();
//void cleanDose();

//--------------Class:DosePair---------------------------------------------
/*Constructor*/
DosePair::DosePair(){
  this->measureDose = NULL;
  this->calculateDose = NULL;
}

/*Destructor*/
DosePair::~DosePair(){
  TryToDelete<Dose>(this->measureDose);
  this->measureDose = NULL;

  TryToDelete<Dose>(this->calculateDose);
  this->calculateDose = NULL;
}

/*Copy Constructor*/
DosePair::DosePair(const DosePair& r){
  this->measureDose = NULL;
  this->calculateDose = NULL;
  if(NULL != &r){

    if (NULL != r.measureDose){
      this->measureDose = new Dose();
      *this->measureDose = *r.measureDose;
    }

    if (NULL != r.calculateDose){
      this->calculateDose = new Dose();
      *this->calculateDose = *r.calculateDose;
    }
  }

}

/*Overload operator = */
DosePair DosePair::operator = (const DosePair& r){
  TryToDelete<Dose>(this->measureDose);
  this->measureDose = NULL;
  
  TryToDelete<Dose>(this->calculateDose);

  this->calculateDose = NULL;

  if(NULL == &r){
    this->measureDose = NULL;
    this->calculateDose = NULL;
  }else{
    if (NULL != r.measureDose){
      this->measureDose = new Dose();
      *this->measureDose = *r.measureDose;
    }

    if (NULL != r.calculateDose){
      this->calculateDose = new Dose();
      *this->calculateDose = *r.calculateDose;
    }
  }

  return *this;

}


/*Set and Get*/
//-------------------------------------------------------
Dose* DosePair::getMeasureDose(){
  return this->measureDose;
}

void DosePair::setMeasureDose(Dose* measureDose){
  TryToDelete<Dose>(this->measureDose);

  if (NULL == measureDose){
    this->measureDose = NULL;
  }
  else{
    this->measureDose = new Dose();
    *this->measureDose = *measureDose;
  }
}

Dose DosePair::copyMeasureDose(){
  Dose result;

  if(NULL != this->measureDose){
    result = *this->measureDose;
  }

  return result;
}

void DosePair::allocateMeasureDose(){
  TryToDelete<Dose>(this->measureDose);
  this->measureDose = new Dose();
}

void DosePair::cleanMeasureDose(){
  TryToDelete<Dose>(this->measureDose);

  this->measureDose = NULL;
}


Dose* DosePair::getCalculateDose(){
  return this->calculateDose;
}

void DosePair::setCalculateDose(Dose* calculateDose){
  TryToDelete<Dose>(this->calculateDose);

  if (NULL == calculateDose){
    this->calculateDose = NULL;
  }
  else{
    this->calculateDose = new Dose();
    *this->calculateDose = *calculateDose;
  }
}

Dose DosePair::copyCalculateDose(){
   Dose result;
   if(NULL != this->calculateDose){
     result = *this->calculateDose;
   }

   return result;
}

void DosePair::allocateCalculateDose(){
  TryToDelete<Dose>(this->calculateDose);
  this->calculateDose = new Dose();
}

void DosePair::cleanCalculateDose(){
  TryToDelete<Dose>(this->calculateDose);
  this->calculateDose = NULL;
}


//--------------Class:PatientData------------------------------------------

/*Constructor*/
PatientData::PatientData(){
  this->baseInfo.reset();
  this->dataMap.clear();
}

/*Destructor*/
PatientData::~PatientData(){
  this->baseInfo.reset();
  this->dataMap.clear();
  map<string, DosePair>().swap(this->dataMap);

}

/*Copy Constructor*/
PatientData::PatientData(const PatientData& r){
  this->baseInfo.reset();
  this->dataMap.clear();

  if(NULL != &r){
    this->baseInfo = r.baseInfo;
    /*Notice: the operator = of map in stl had been achieved,"=" is suit for elements copying one-by-one between two maps*/
    this->dataMap = r.dataMap;  // use the "=" directly, which is overloaded by map and can copy the elements one by one
  }


}

/*Overload operator = */
PatientData PatientData::operator = (const PatientData& r){
  if(NULL == &r){
    this->baseInfo.reset();
    this->dataMap.clear();
  }else{
    this->baseInfo = r.baseInfo;
    /*Notice: the operator = of map in stl had been achieved,"=" is suit for elements copying one-by-one between two maps*/
    this->dataMap = r.dataMap;  // use the "=" directly, which is overloaded by map and can copy the elements one by one
  }

  return *this;
}

bool PatientData::setBaseInfo(PatientInfo* info){

  if (NULL == info){
    this->baseInfo.reset();
  }
  this->baseInfo = *info;
  	
  return true;
}

bool PatientData::upDateBaseInfo(PatientInfo* info){
  if (NULL == info){
    return false;
  }
  this->baseInfo.reset();
  return this->setBaseInfo(info);
}

PatientInfo* PatientData::getBaseInfo(){
  return &this->baseInfo;
}

PatientInfo PatientData::copyBaseInfo(){
  return this->baseInfo;
}


bool PatientData::addOneAngleDosePair(string angle, DosePair* dosePair){

  if (0 == this->dataMap.count(angle)){
    this->dataMap.insert(map<string,DosePair>::value_type(angle,*dosePair));
  }
  else{
    cout << "已存在相应的角度数据" << endl;
    return false;
  }
  return true;
}

DosePair* PatientData::getOneAngleDosePair(string angle){

  if (0 == this->dataMap.count(angle)){
    cout << "不存在相应角度的数据..." << endl;
    return NULL;
  }

  map<string, DosePair>::iterator it = this->dataMap.find(angle);
  return &it->second;

}
bool PatientData::removeOneAngleDoseData(string angle){

  if (0 != this->dataMap.count(angle)){
    this->dataMap.erase(angle);
    return true;
  }
  else{
    cout << "不存在相应角度的数据..." << endl;
    return false;
  }
}

bool PatientData::updateOneAngleDoseData(string angle, DosePair* dosePair){

  if (0 == this->dataMap.count(angle)){
    cout << "不存在相应角度的数据..." << endl;
    return false;
  }
  this->dataMap.erase(angle);
  return addOneAngleDosePair(angle, dosePair);
}

map<string,DosePair>* PatientData::getDataMap(){
  return &this->dataMap;
}

map<string,DosePair> PatientData::copyDataMap(){
  return this->dataMap;
}


//-------------Cache-----------------------------------------
/*----static members--------*/
//-------Singleton Model:Hungry model-------------
Cache* Cache::cacheInstance = new Cache();
//-------Garbo------------------------------------
Cache::CacheGarbo Cache::cacheGarboInstance; 

/*Constructor*/
Cache::Cache(void){
  this->globalCache.clear();
}

/*Destructor*/
Cache::~Cache(){
  this->globalCache.clear();
  deque<PatientData>().swap(this->globalCache);
}

/*GlobalMembers::CGarbo Constructor*/
Cache::CacheGarbo::CacheGarbo(){
}

/*GlobalMembers::CGarbo Destructor*/
Cache::CacheGarbo::~CacheGarbo(){
  removeCacheInstance();
}

/*Basic Functions*/
Cache* Cache::getCacheInstance(){
  if(NULL==cacheInstance){
    cacheInstance = new Cache();
  }
  return cacheInstance;
}

void Cache::removeCacheInstance(){
  TryToDelete<Cache>(cacheInstance);
  cacheInstance = NULL;
}


/*Other functions*/
bool Cache::add(PatientData* data){
  if (NULL == data){
    return false;
  }
  this->globalCache.push_back(*data);
  return true;
}

bool Cache::remove(int index){
  if (index >= this->globalCache.size()){
    return false;
  }
  this->globalCache.erase(this->globalCache.begin() + index);
  return true;
}

bool  Cache::removeLast(){
  if(true==this->globalCache.empty()){
    return false;
  }
  this->globalCache.pop_back();
  return true;
}


PatientData* Cache::find(int index){
  if (index >= this->globalCache.size()){
    cout << "队列访问越界..." << endl;
    return NULL;
  }

  return &this->globalCache.at(index);
}

PatientData* Cache::findLast(){
  if(true==this->globalCache.empty()){
    return NULL;
  }
  return &this->globalCache.back();
}


PatientData Cache::copy(int index){
  PatientData result;
  if (index >= this->globalCache.size()){
    cout << "队列访问越界..." << endl;
    return result;
  }
  result = this->globalCache.at(index);
  
  return result;
}
PatientData Cache::copyLast(){
  PatientData  result;
  if(true==this->globalCache.empty()){
    return result;
  }
  result = this->globalCache.back();

  return result;
}

bool Cache::update(int index, PatientData* newData){
  if (index >= this->globalCache.size()){
    cout << "队列访问越界..." << endl;
    return false;
  }
  else{
    this->globalCache.erase(this->globalCache.begin() + index);

    if (NULL == newData){
      return false;
    }
    else{
      this->globalCache.insert(this->globalCache.begin() + index, *newData);
    }
  }
  return true;
}

bool Cache::updataLast(PatientData* newData){
  if(NULL == newData){
    return false;
  }
  if(true==this->globalCache.empty()){
    return false;
  }
  this->globalCache.pop_back();
  this->globalCache.push_back(*newData);

  return true;
  
}

bool Cache::removeAll(){

  this->globalCache.clear();
  return true;

}

int Cache::getPatientCounts(){
  return this->globalCache.size();
}

deque<PatientData>* Cache::getPatientDateDque(){
  return &this->globalCache;
}
