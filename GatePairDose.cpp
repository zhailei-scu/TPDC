//---------------------------------------------------------------------------
#include "GatePairDose.h"
#include "LogFrame.h"

//-------------------------------------------Class:Object----------------------------------------------
/*Constructor*/
GatePairDose::GatePairDose(){

  this->dosePair = NULL;
  this->angle.clear();

  vector<IObserver*>::iterator iterat = this->ObserverList.begin();
  for (; iterat != this->ObserverList.end();){
    /*Note: as the vector<IObserver*> ObserverList stored the point/reference of each Observer,
    so while realease the space of vector<IObserver*> ObserverList,don not use the operation "delete (*iterat)"
    to clean each point's space here,in this case the point's space should be realeased at the location
    where point's space is allocated. If had used the operation "delete (*iterat)", the point's space
    while be clean while the vector space is released,NOTE,while you want to release the point's space
    at where the point's space is allocated ,you would get an unreacherable error(multi released).
    To solved this issue,there are two ways: First,use the function "TryToDelete<class T>()" which is encapsulate by us and
    could avoid the program shut down while meet an unreacherable error(multi released); Second, as mentioned before,don not
    use the operation "delete (*iterat)" to clean each point's space here,in this case the point's space should
    be realeased at the location where point's space is allocated or use our implemented function "TryToDelete<class T>()"
    , we should hanve a convention about it.*/

    iterat = this->ObserverList.erase(iterat);
  }
}

/*Destructor*/
GatePairDose::~GatePairDose(){
  TryToDelete<DosePair>(this->dosePair);
  this->dosePair = NULL;
  this->angle.clear();
  vector<IObserver*>::iterator iterat = this->ObserverList.begin();
  for (; iterat != this->ObserverList.end();){
    /*Note: as the vector<IObserver*> ObserverList stored the point/reference of each Observer,
    so while realease the space of vector<IObserver*> ObserverList,don not use the operation "delete (*iterat)"
    to clean each point's space here,in this case the point's space should be realeased at the location
    where point's space is allocated. If had used the operation "delete (*iterat)", the point's space
    while be clean while the vector space is released,NOTE,while you want to release the point's space
    at where the point's space is allocated ,you would get an unreacherable error(multi released).
    To solved this issue,there are two ways: First,use the function "TryToDelete<class T>()" which is encapsulate by us and
    could avoid the program shut down while meet an unreacherable error(multi released); Second, as mentioned before,don not
    use the operation "delete (*iterat)" to clean each point's space here,in this case the point's space should
    be realeased at the location where point's space is allocated or use our implemented function "TryToDelete<class T>()"
    , we should hanve a convention about it.*/

    iterat = this->ObserverList.erase(iterat);
  }
  vector<IObserver*>().swap(this->ObserverList);
}

/*Copy Constructor*/
GatePairDose::GatePairDose(const GatePairDose& r){
  vector<IObserver*>().swap(this->ObserverList);
  this->dosePair = NULL;
  this->angle.clear();
  if(NULL != &r){

    this->angle = r.angle;
    this->ObserverList = vector<IObserver*>(r.ObserverList);
    TryToDelete<DosePair>(this->dosePair);
    if(NULL != r.dosePair){

      this->dosePair = new DosePair();
      *this->dosePair = *r.dosePair;
    }else{
      this->dosePair = NULL;
    }
  }



}

/*Overload operator = */
GatePairDose GatePairDose::operator = (const GatePairDose& r){

  TryToDelete<DosePair>(this->dosePair);
  if(NULL == &r){
     vector<IObserver*>().swap(this->ObserverList);
     this->dosePair = NULL;
     this->angle.clear();
  }else{

    this->angle = r.angle;
    this->ObserverList = vector<IObserver*>(r.ObserverList);

    if(NULL != r.dosePair){

      this->dosePair = new DosePair();
      *this->dosePair = *r.dosePair;
    }else{
      this->dosePair = NULL;
    }
  }

  return *this;
}


/*---Observer model functions--------------------------*/
void GatePairDose::Notify(Message_Notify message){
  vector<IObserver*>::iterator iterat = ObserverList.begin();
  for (; iterat != ObserverList.end();){

    //(*iterat)->update(message);
    if (SEHNotify((*iterat), message)){
      iterat++;
    }
    else{
      iterat = ObserverList.erase(iterat);
    }

  }
}

bool GatePairDose::SEHNotify(IObserver* observer, Message_Notify message){

  __try{
    observer->update(message);
    return true;
  }
  __except (EXCEPTION_EXECUTE_HANDLER){

    RunningLog::writeLog("The Observer is cleaned,the visiting is unreachable,Please allocate and assign a new Observer");
    return false;
  }
  return true;

}

void GatePairDose::AddObserver(IObserver *pObserver){
  vector<IObserver*>::iterator iterat = ObserverList.begin();
  for (; iterat != ObserverList.end(); iterat++){
    if (pObserver->identify == (*iterat)->identify){
      return;
    }
  }

  ObserverList.push_back(pObserver);
}

void GatePairDose::DeleteObserver(IObserver *pObserver){
  vector<IObserver*>::iterator iterat = ObserverList.begin();
  for (; iterat != ObserverList.end();){
    if (pObserver->identify == (*iterat)->identify){
      /*Note: as the vector<IObserver*> ObserverList stored the point/reference of each Observer,
      so while realease the space of vector<IObserver*> ObserverList,don not use the operation "delete (*iterat)"
      to clean each point's space here,in this case the point's space should be realeased at the location
      where point's space is allocated. If had used the operation "delete (*iterat)", the point's space
      while be clean while the vector space is released,NOTE,while you want to release the point's space
      at where the point's space is allocated ,you would get an unreacherable error(multi released).
      To solved this issue,there are two ways: First,use the function "TryToDelete<class T>()" which is encapsulate by us and
      could avoid the program shut down while meet an unreacherable error(multi released); Second, as mentioned before,don not
      use the operation "delete (*iterat)" to clean each point's space here,in this case the point's space should
      be realeased at the location where point's space is allocated or use our implemented function "TryToDelete<class T>()"
      , we should hanve a convention about it.*/

      iterat = ObserverList.erase(iterat);
    }
    else{
      iterat++;
    }
  }
}


/*------------------other functions--------------------------*/
DosePair* GatePairDose::getDosePair(){
  return this->dosePair;
}

void GatePairDose::setDosePair(DosePair& dosePair){
  TryToDelete<DosePair>(this->dosePair);
  if(NULL == &dosePair){
    this->dosePair = NULL;
  }else{
    this->dosePair = new DosePair();
    *this->dosePair = dosePair;
  }
}

DosePair GatePairDose::copyDosePair(){
  DosePair result;
  if(NULL != this->dosePair){
    result = *this->dosePair;
  }
  return result;
}

void GatePairDose::allocateDosePair(){
  TryToDelete<DosePair>(this->dosePair);
  this->dosePair = new DosePair();
}
void GatePairDose::cleanDosePair(){
  TryToDelete<DosePair>(this->dosePair);
  this->dosePair = NULL;
}
//-----------------------Angle---------------------------------------------
string* GatePairDose::getAngle(){
  return &this->angle;
}

string GatePairDose::copyAngle(){
  return this->angle;
}

void GatePairDose::setAngle(string _angle){
  this->angle = _angle;
}

