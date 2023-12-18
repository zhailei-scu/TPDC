//---------------------------------------------------------------------------
#pragma once
#ifndef IObserveH
#define IObserveH

#include <vector>
#include <iostream>
#include "Util.h"

using namespace std;
//-------------------------------------------------------------------------
enum Message_Notify{
  Update_measure_fromGatePair = 1,
  Update_calculate_fromGatePair = 2,

  Update_measure_fromHandledPairDose = 3,
  Update_calculate_fromHandledPairDose = 4,

  Update_CAX_from_operator = 5,

  Update_rotation = 6,
  Update_leftToRightChange = 7,
  Update_topToBottomChange = 8,

  Update_Segments = 9,
};

enum Observer_Id{
  HANDLEPAIRDOSE = 1,
  DISPLAYPAIRDOSE = 2,
};
//-------------------------------------------Interface: IObserver----------------------------------------
class IObserver{
public:
  virtual ~IObserver() = 0;

  virtual void update(Message_Notify message) = 0;
  Observer_Id identify;
};
//-------------------------------------------Interface: IObject----------------------------------------
class IObject{
public:
  virtual ~IObject() = 0;

  virtual void Notify(Message_Notify message) = 0;
  virtual void AddObserver(IObserver *pObserver) = 0;
  virtual void DeleteObserver(IObserver *pObserver) = 0;

  virtual bool SEHNotify(IObserver* observer, Message_Notify message) = 0;
};
//---------------------------------------------------------------------------
#endif