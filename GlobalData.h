//---------------------------------------------------------------------------
#pragma once

#ifndef GlobalDataH
#define GlobalDataH

#include "dose.h"
#include "Patient.h"
#include "GatePairDose.h"
#include "HandledPairDose.h"
#include "DisplayPairDose.h"
#include "Paramter.h"
#include "Check.h"

//----------------------------------------------------------------------------
/*A singleton model(Hungry model) for global operation vars*/
class GlobalMembers{
private:
  /*Constructor*/
  GlobalMembers();

  /*Copy Constructor(forbidden)*/
  GlobalMembers(const GlobalMembers &r);

  /*Overload operator = (forbidden)*/
  GlobalMembers operator = (const GlobalMembers &r);

  /*Static Member: To store the only one object in software,and
  this object is used to collect all the global vars which are wished
  to stay during the software lifttime.For instance:dosePair,doseDisplay...*/
  static GlobalMembers* globalMembersInstance;

  /*To recycle to allocated memory of instance*/
  class CGarbo{
  public:
    /*GlobalMembers::CGarbo Constructor*/
    CGarbo();

    /*GlobalMembers::CGarbo Destructor*/
    ~CGarbo();
  };

  /*The static object:cGarboInstance,while software shut down,this Destructor
  of CGarbo is invoked to recycle the memory in class GlobalMembers (for the
  static member of globalMembersInstance) */
  static CGarbo cGarboInstance;

public:
  /*Destructor*/
  virtual ~GlobalMembers();

public:
  /*The only way to get the globalMembersInstance*/
  static GlobalMembers* getInstance();
  /*Release the memory of globalMembersInstance*/
  static void releaseInstance();

private:
  PatientInfo* patientInfo;
  GatePairDose* gatePairDose;
  HandledPairDose* handledPairDose;
  DisplayPairDose* displayPairDose;
  DoseCheck* doseCheck;

  HANDLE_MODEL handelModel;

public:
  void constructorObserverMode();
public:
  PatientInfo* getPatientInfo();
  PatientInfo copyPatientInfo()throw(const char*);
  void setPatientInfo(PatientInfo* _patientInfo)throw(const char*);
  void allocatePatientInfo();
  void cleanPatientInfo();

  GatePairDose* getGatePairDose();
  GatePairDose copyGatePairDose()throw(const char*);
  void setGatePairDose(GatePairDose* _gatePairDose)throw(const char*);
  void allocateGatePairDose();
  void cleanGatePairDose();

  HandledPairDose* getHandledPairDose();
  HandledPairDose copyHandledPairDose()throw(const char*);
  void setHandledPairDose(HandledPairDose* _handledPairDose)throw(const char*);
  void allocateHandledPairDose();
  void cleanHandledPairDose();

  DisplayPairDose* getDisplayPairDose();
  DisplayPairDose copyDisplayPairDose()throw(const char*);
  void setDisplayPairDose(DisplayPairDose* _displayPairDose)throw(const char*);
  void allocateDisplayPairDose();
  void cleanDisplayPairDose();

  DoseCheck* getDoseCheck();
  DoseCheck copyDoseCheck();
  void setDoseCheck(DoseCheck* _doseCheck);
  void allocateDoseCheck();
  void cleanDoseCheck();
  void initialDoseCheck();

  HANDLE_MODEL getHandel_Model();
  void setHandel_Model(HANDLE_MODEL model);

public:
  /*Case Cache*/
  void flushToCache();
  void flushMeasureToCache();
  void flushCalculateToCache();

  void flushFromCache(int index,string angle);
};
//----------------------------------------------------------------------------
#endif