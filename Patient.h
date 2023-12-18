//---------------------------------------------------------------------------
#pragma once
#ifndef PatientH
#define PatientH

#include <string>

using namespace std;
//---------------------------------------------------------------------------

class PatientInfo{
public:
  string patientName;
  string patientId;
  string patientAge;
  string treatedPart;
  int patientGender;    //0:male;1:female;-1:default

public:
  /*Construct*/
  PatientInfo();

  /*Destructor*/
  ~PatientInfo();

  /*Copy Constructor*/
  PatientInfo(const PatientInfo& r);

  /*Overload operator = */
  PatientInfo operator = (const PatientInfo& r);

  void reset();

};


//---------------------------------------------------------------------------
#endif