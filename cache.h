/*-------------------------------------------------------------------------
This Unit include the Cache of the software,which is used to store the dose and other information
for different patients.
-------------------------------------------------------------------------*/
#pragma once

#ifndef CacheH
#define CacheH

#include <map>
#include <deque>
#include <string.h>
#include "dose.h"
#include "Patient.h"
#include "windows.h"
//---------------------------------------------------------------------------
using namespace std;

//class SingleDose{
//
//private:
//  CRITICAL_SECTION  g_cs_isReadedbyOthersNow;
//  CRITICAL_SECTION  g_cs_isModifing;
//  CRITICAL_SECTION g_cs;
//  Dose* doseData;
//
//public:
//  /*Constructor*/
//  SingleDose();
//  /*Destructor*/
//  ~SingleDose();
//
//  /*Copy Constructor*/
//  SingleDose(SingleDose& r);
//
//  /* Overload the operator = */
//  SingleDose operator = (SingleDose& r);
//
//  /*Get and Set*/
//
//  Dose* getDose();
//  void setDose(Dose* doseData);
//  void allocateDose();
//  void cleanDose();
//};

class DosePair{

private:

  Dose* measureDose;
  Dose* calculateDose;

public:
  /*Constructor*/
  DosePair();
  /*Destructor*/
  ~DosePair();

  /*Copy Constructor*/
  DosePair(const DosePair& r);

  /*Overload operator = */
  DosePair operator = (const DosePair& r);

  Dose* getMeasureDose();
  void setMeasureDose(Dose* measureDose);
  Dose copyMeasureDose();
  void allocateMeasureDose();
  void cleanMeasureDose();

  Dose* getCalculateDose();
  void setCalculateDose(Dose* calculateDose);
  Dose copyCalculateDose();
  void allocateCalculateDose();
  void cleanCalculateDose();
};


class PatientData{

private:
  PatientInfo baseInfo;
  map<string,DosePair> dataMap;  //(angle,doseSet)pair

public:
  /*Constructor*/
  PatientData();

  /*Destructor*/
  ~PatientData();

  /*Copy Constructor*/
  PatientData(const PatientData& r);

  /*Overload operator = */
  PatientData operator = (const PatientData& r);

public:
  bool setBaseInfo(PatientInfo* info);
  PatientInfo* getBaseInfo();
  bool upDateBaseInfo(PatientInfo* info);
  PatientInfo copyBaseInfo();

  bool addOneAngleDosePair(string angle,DosePair* dosePair);
  DosePair* getOneAngleDosePair(string angle);
  bool removeOneAngleDoseData(string angle);
  bool updateOneAngleDoseData(string angle,DosePair* dosePair);
  
  map<string,DosePair>* getDataMap();
  map<string,DosePair> copyDataMap();
};



//-------------------------Class:Cache------------------------
//-------------------------SingleInstance-------------------
class Cache{
private:
  /*Constructor*/
  Cache();

  /*Copy Constructor(forbidden)*/
  Cache(const Cache &r);

  /*Copy Constructor(forbidden)*/
  Cache operator=(const Cache &r);

  /*Static Member: To store the only one object in software:Cache*/
  static Cache *cacheInstance;

  /*To recycle to allocated memory of instance*/
  class CacheGarbo{
  public:
    /*Cache::CacheGarbo Constructor*/
    CacheGarbo();

    /*Cache::CacheGarbo Destructor*/
    ~CacheGarbo();
  };

  /*The static object:cacheGarboInstance,while software shut down,this Destructor
  of CacheGarbo is invoked to recycle the memory in class Cache (for the
  static member of cache) */
  static CacheGarbo cacheGarboInstance;

public:
  /*The only way to get the cache*/
  static Cache* getCacheInstance();

  /*Release the cache*/
  static void removeCacheInstance();

  /*Destructor*/
  virtual ~Cache();

private:
  deque<PatientData> globalCache;

public:
  bool add(PatientData* data);
  bool remove(int index);
  bool removeLast();
  PatientData* find(int index);
  PatientData* findLast();
  PatientData copy(int index);
  PatientData copyLast();
  
  bool update(int index,PatientData* newData);
  bool updataLast(PatientData* newData);

  int getPatientCounts();

  deque<PatientData>* getPatientDateDque();

  bool removeAll();
};

//---------------------------------------------------------------------------
#endif