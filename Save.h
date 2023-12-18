//---------------------------------------------------------------------------
#pragma once

#ifndef SaveH
#define SaveH

#include "Patient.h"
#include "Util.h"
#include <map>
#include <windows.h>
#include <string>
#include "CheckRecord.h"

using namespace std;


//---------------------------Class:SaveFile--------------------------------

class SavingInformation{
public:
  /*Constructor*/
  SavingInformation();
  /*Destructor*/
  ~SavingInformation();

  /*Copy Constructor*/
  SavingInformation(const SavingInformation& r);
  /*Overload operator = */
  SavingInformation operator = (const SavingInformation& r);

public:
  PatientInfo* patientInfo;

  CheckedRecord* checkedRecord;

  MatrixData<float>* savingDose;
  string path;
};


/*A singleton model(Hungry model) for global operation vars*/
class SaveFile{
private:
  SaveFile();

  SaveFile(const SaveFile& r);

  /*Overload operator = (forbidden)*/
  SaveFile operator = (const SaveFile &r);

  /*Static Member: To store the only one object in software,and
  this object is used to collect all the global vars which are wished
  to stay during the software lifttime.*/
  static SaveFile* saveFileInstance;

  /*To recycle to allocated memory of instance*/
  class SaveFileGarbo{
  public:
    /*SaveFile::SaveFileGarbo Constructor*/
    SaveFileGarbo();

    /*SaveFile::SaveFileGarbo Destructor*/
    ~SaveFileGarbo();
  };

  /*The static object:cGarboInstance,while software shut down,this Destructor
  of CGarbo is invoked to recycle the memory in class GlobalMembers (for the
  static member of globalMembersInstance) */
  static SaveFileGarbo saveFileGarboInstance;
public:
  ~SaveFile();

private:
  map<unsigned,SavingInformation> threadMap;    //(dwThreadId,SavingInfo)


public:
  static void save(SavingInformation savingInformation);
  static void releaseInstance();


public:
  friend unsigned __stdcall SaveFileThread(LPVOID pvParam);
};

//---------------------------------------------------------------------------
#endif