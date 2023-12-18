//---------------------------------------------------------------------------
#pragma once
#ifndef GatePairDoseH
#define GatePairDoseH

#include "Cache.h"
#include "IObserve.h"
//-------------------------Class:GatePairDose------------------------------------
/*This class is used to keep a object while the software is running,the object is kept in
the GlobalMembers,as a member in the class GlobalMembers. This class:GatePairDose is used
to read the origin dose data from dosefile or cache,at the same time, it is the obserable
object in the Observer model:

                                             HandledPairDose
                                              /      |
                                             /       |
                                            /        |
                           (notify message)/         |
                                          /          |
                              GatePairDose           |(notify message)
                                                     |
                                                     |
                                                     |
                                                     |
                                              DisplayPairDose          */

//-------------------------------------------------------------------------------
class GatePairDose:public IObject{

private:
  string angle;
  DosePair* dosePair;

public:
  /*Constructor*/
  GatePairDose();
  /*Destructor*/
  ~GatePairDose();

  /*Copy Constructor*/
  GatePairDose(const GatePairDose& r);

  /*Overload operator = */
  GatePairDose operator = (const GatePairDose& r);

  void Notify(Message_Notify message);
  void AddObserver(IObserver *pObserver);
  void DeleteObserver(IObserver *pObserver);

private:
  vector<IObserver*> ObserverList;
  virtual bool SEHNotify(IObserver* observer, Message_Notify message);

public:
  DosePair* getDosePair();
  void setDosePair(DosePair& dosePair);
  DosePair copyDosePair();
  void allocateDosePair();
  void cleanDosePair();

  string* getAngle();
  string copyAngle();
  void setAngle(string _angle);
};
//---------------------------------------------------------------------------
#endif