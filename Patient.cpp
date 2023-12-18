//---------------------------------------------------------------------------
#include "Patient.h"
#include "windows.h"
//--------------------PatientInfo---------------------------------------
/*Construct*/
PatientInfo::PatientInfo(){

  this->patientName.clear();
  this->patientId.clear();
  this->patientAge.clear();
  this->treatedPart.clear();
  this->patientGender = -1;
}

/*Destructor*/
PatientInfo::~PatientInfo(){

  this->patientName.clear();
  string().swap(this->patientName);

  this->patientId.clear();
  string().swap(this->patientId);

  this->patientAge.clear();
  string().swap(this->patientAge);

  this->treatedPart.clear();
  string().swap(this->treatedPart);

  this->patientGender = -1;

}

/*Copy Constructor*/
PatientInfo::PatientInfo(const PatientInfo& r){

  if(NULL != &r){
    this->patientName = r.patientName;
    this->patientId = r.patientId;
    this->patientAge = r.patientAge;
    this->treatedPart = r.treatedPart;

    this->patientGender = r.patientGender;

  }else{
    this->patientName.clear();
    string().swap(this->patientName);

    this->patientId.clear();
    string().swap(this->patientId);

    this->patientAge.clear();
    string().swap(this->patientAge);

    this->treatedPart.clear();
    string().swap(this->treatedPart);

    this->patientGender = -1;
  }


}

 /*Overload operator = */
PatientInfo PatientInfo::operator = (const PatientInfo& r){

  if(NULL != &r){
    this->patientName = r.patientName;
    this->patientId = r.patientId;
    this->patientAge = r.patientAge;
    this->treatedPart = r.treatedPart;

    this->patientGender = r.patientGender;

  }else{
    this->patientName.clear();
    string().swap(this->patientName);

    this->patientId.clear();
    string().swap(this->patientId);

    this->patientAge.clear();
    string().swap(this->patientAge);

    this->treatedPart.clear();
    string().swap(this->treatedPart);

    this->patientGender = -1;
  }

  return *this;

}

void PatientInfo::reset(){
  this->patientName.clear();
  string().swap(this->patientName);

  this->patientId.clear();
  string().swap(this->patientId);

  this->patientAge.clear();
  string().swap(this->patientAge);

  this->treatedPart.clear();
  string().swap(this->treatedPart);

  this->patientGender = -1;
}
