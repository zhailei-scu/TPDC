//---------------------------------------------------------------------------
#include "HandledPairDose.h"
#include "LogFrame.h"
#include "GlobalData.h"
#include <math.h>
#include "Util.h"

//--------------------------------Class:HandledPairDose----------------------------
/*Constructor*/
HandledPairDose::HandledPairDose(){
  this->measureDoseHandled = NULL;
  this->calculateDoseHandled = NULL;

  this->NormMeasureDoseHandled = NULL;

  this->Abs_NormCalculateDoseHandled = NULL;
  this->Rel_NormCalculateDoseHandled = NULL;

  this->identify = Observer_Id(1);

  this->manualSpecialMeasureNormValue = false;
  this->manualSpecialCalcNormValue = false;

  this->normValueStr_measure = "";
  this->normValueStr_calculate = "";
}

/*Destructor*/
HandledPairDose::~HandledPairDose(){
  TryToDelete<Dose>(this->measureDoseHandled);
  this->measureDoseHandled = NULL;
  TryToDelete<Dose>(this->calculateDoseHandled);
  this->calculateDoseHandled = NULL;

  TryToDelete<Dose>(this->NormMeasureDoseHandled);
  this->NormMeasureDoseHandled = NULL;
  TryToDelete<Dose>(this->Abs_NormCalculateDoseHandled);
  this->Abs_NormCalculateDoseHandled = NULL;
  TryToDelete<Dose>(this->Rel_NormCalculateDoseHandled);
  this->Rel_NormCalculateDoseHandled = NULL;

  this->identify =  Observer_Id(0);

  this->manualSpecialMeasureNormValue = false;
  this->manualSpecialCalcNormValue = false;

  this->normValueStr_measure = "";
  this->normValueStr_calculate = "";
}

/*Copy Constructor*/
HandledPairDose::HandledPairDose(const HandledPairDose & r){

  if(NULL == &r){
    this->measureDoseHandled = NULL;
    this->calculateDoseHandled = NULL;
    this->NormMeasureDoseHandled = NULL;
    this->Abs_NormCalculateDoseHandled = NULL;
    this->Rel_NormCalculateDoseHandled = NULL;

    this->identify =  Observer_Id(0);

    this->manualSpecialMeasureNormValue = false;
    this->manualSpecialCalcNormValue = false;

    this->normValueStr_measure = "";
    this->normValueStr_calculate = "";

  }else{
    if(NULL != r.measureDoseHandled){
      this->measureDoseHandled = new Dose();
      *this->measureDoseHandled = *r.measureDoseHandled;
    }else{
      this->measureDoseHandled = NULL;
    }

    if(NULL != r.calculateDoseHandled){
      this->calculateDoseHandled = new Dose();
      *this->calculateDoseHandled = *r.calculateDoseHandled;
    }else{
      this->calculateDoseHandled = NULL;
    }

    if(NULL != r.NormMeasureDoseHandled){
      this->NormMeasureDoseHandled = new Dose();
      *this->NormMeasureDoseHandled = *r.NormMeasureDoseHandled;
    }else{
      this->NormMeasureDoseHandled = NULL;
    }

    if(NULL != r.Abs_NormCalculateDoseHandled){
      this->Abs_NormCalculateDoseHandled = new Dose();
      *this->Abs_NormCalculateDoseHandled = *r.Abs_NormCalculateDoseHandled;
    }else{
      this->Abs_NormCalculateDoseHandled = NULL;
    }

    if(NULL != r.Rel_NormCalculateDoseHandled){
      this->Rel_NormCalculateDoseHandled = new Dose();
      *this->Rel_NormCalculateDoseHandled = *r.Rel_NormCalculateDoseHandled;
    }else{
      this->Rel_NormCalculateDoseHandled = NULL;
    }

    this->identify = r.identify;

    this->manualSpecialMeasureNormValue = r.manualSpecialMeasureNormValue;
    this->manualSpecialCalcNormValue = r.manualSpecialCalcNormValue;

    this->normValueStr_measure = r.normValueStr_measure;
    this->normValueStr_calculate = r.normValueStr_calculate;

  }
}

/*Overload operator = */
HandledPairDose HandledPairDose::operator = (const HandledPairDose& r){
  TryToDelete<Dose>(this->measureDoseHandled);
  TryToDelete<Dose>(this->calculateDoseHandled);
  TryToDelete<Dose>(this->NormMeasureDoseHandled);
  TryToDelete<Dose>(this->Abs_NormCalculateDoseHandled);
  TryToDelete<Dose>(this->Rel_NormCalculateDoseHandled);

  if(NULL == &r){
    this->measureDoseHandled = NULL;
    this->calculateDoseHandled = NULL;
    this->NormMeasureDoseHandled = NULL;
    this->Abs_NormCalculateDoseHandled = NULL;
    this->Rel_NormCalculateDoseHandled = NULL;

    this->identify =  Observer_Id(0);

    this->manualSpecialMeasureNormValue = false;
    this->manualSpecialCalcNormValue = false;

    this->normValueStr_measure = "";
    this->normValueStr_calculate = "";

  }else{
    if(NULL != r.measureDoseHandled){
      this->measureDoseHandled = new Dose();
      *this->measureDoseHandled = *r.measureDoseHandled;
    }else{
      this->measureDoseHandled = NULL;
    }

    if(NULL != r.calculateDoseHandled){
      this->calculateDoseHandled = new Dose();
      *this->calculateDoseHandled = *r.calculateDoseHandled;
    }else{
      this->calculateDoseHandled = NULL;
    }

    if(NULL != r.NormMeasureDoseHandled){
      this->NormMeasureDoseHandled = new Dose();
      *this->NormMeasureDoseHandled = *r.NormMeasureDoseHandled;
    }else{
      this->NormMeasureDoseHandled = NULL;
    }

    if(NULL != r.Abs_NormCalculateDoseHandled){
      this->Abs_NormCalculateDoseHandled = new Dose();
      *this->Abs_NormCalculateDoseHandled = *r.Abs_NormCalculateDoseHandled;
    }else{
      this->Abs_NormCalculateDoseHandled = NULL;
    }

    if(NULL != r.Rel_NormCalculateDoseHandled){
      this->Rel_NormCalculateDoseHandled = new Dose();
      *this->Rel_NormCalculateDoseHandled = *r.Rel_NormCalculateDoseHandled;
    }else{
      this->Rel_NormCalculateDoseHandled = NULL;
    }

    this->identify = r.identify;

    this->manualSpecialMeasureNormValue = r.manualSpecialMeasureNormValue;
    this->manualSpecialCalcNormValue = r.manualSpecialCalcNormValue;

    this->normValueStr_measure = r.normValueStr_measure;
    this->normValueStr_calculate = r.normValueStr_calculate;

  }
  return *this;
}

/*Other basic functions*/

/*Functions*/
GridPoint HandledPairDose::getOffsetPoint(){
  return this->offsetPoint;
}

void HandledPairDose::setOffsetPoint(GridPoint _offsetPoint){
  this->offsetPoint = _offsetPoint;
}

PhysicalPoint* HandledPairDose::getNormlizationPosition_Measure(){  //Only get method
  return &this->NormlizationPosition_Measure;
}

PhysicalPoint* HandledPairDose::getNormlizationPosition_Calculate(){ //Only get method
  return &this->NormlizationPosition_Calculate;
}

PhysicalPoint HandledPairDose::copyNormlizationPosition_Measure(){
  return this->NormlizationPosition_Measure;
}

PhysicalPoint HandledPairDose::copyNormlizationPosition_Calculate(){
  return this->NormlizationPosition_Calculate;
}


NORMLIZE_TYPE HandledPairDose::getNormlize_Type(){           //Only get method
  return this->normlize_Type;
}



Dose* HandledPairDose::getMeasureDoseHandled(){
  return this->measureDoseHandled;
}
void HandledPairDose::setMeasureDoseHandled(Dose& r){
  TryToDelete<Dose>(this->measureDoseHandled);
  if(NULL == &r){
    this->measureDoseHandled = NULL;
  }else{
    this->measureDoseHandled = new Dose();
    *this->measureDoseHandled = r;
  }
}
Dose HandledPairDose::copyMeasureDoseHandled(){
  Dose result;

  if(NULL != this->measureDoseHandled){
    result = *this->measureDoseHandled;
  }
  return result;
}
void HandledPairDose::allocateMeasureDoseHandled(){
  TryToDelete<Dose>(this->measureDoseHandled);
  this->measureDoseHandled = new Dose();
}
void HandledPairDose::cleanMeasureDoseHandled(){
  TryToDelete<Dose>(this->measureDoseHandled);
  this->measureDoseHandled = NULL;
}


Dose* HandledPairDose::getCalculateDoseHandled(){
  return this->calculateDoseHandled;
}
void HandledPairDose::setCalculateDoseHandled(Dose& r){
  TryToDelete<Dose>(this->calculateDoseHandled);
  if(NULL == &r){
    this->calculateDoseHandled = NULL;
  }else{
    this->calculateDoseHandled = new Dose();
    *this->calculateDoseHandled = r;
  }
}
Dose HandledPairDose::copyCalculateDoseHandled(){
  Dose result;

  if(NULL != this->calculateDoseHandled){
    result = *this->calculateDoseHandled;
  }
  return result;
}
void HandledPairDose::allocateCalculateDoseHandled(){
  TryToDelete<Dose>(this->calculateDoseHandled);
  this->calculateDoseHandled = new Dose();
}
void HandledPairDose::cleanCalculateDoseHandled(){
  TryToDelete<Dose>(this->calculateDoseHandled);
  this->calculateDoseHandled = NULL;
}


//Abs
Dose* HandledPairDose::getNormMeasureDoseHandled(){
  return this->NormMeasureDoseHandled;
}
void HandledPairDose::setNormMeasureDoseHandled(Dose& r){
  TryToDelete<Dose>(this->NormMeasureDoseHandled);
  if(NULL == &r){
    this->NormMeasureDoseHandled = NULL;
  }else{
    this->NormMeasureDoseHandled = new Dose();
    *this->NormMeasureDoseHandled = r;
  }
}
Dose HandledPairDose::copyNormMeasureDoseHandled(){
  Dose result;

  if(NULL != this->NormMeasureDoseHandled){
    result = *this->NormMeasureDoseHandled;
  }
  return result;
}
void HandledPairDose::allocateNormMeasureDoseHandled(){
  TryToDelete<Dose>(this->NormMeasureDoseHandled);
  this->NormMeasureDoseHandled = new Dose();
}
void HandledPairDose::cleanNormMeasureDoseHandled(){
  TryToDelete<Dose>(this->NormMeasureDoseHandled);
  this->NormMeasureDoseHandled = NULL;
}


Dose* HandledPairDose::getAbs_NormCalculateDoseHandled(){
  return this->Abs_NormCalculateDoseHandled;
}
void HandledPairDose::setAbs_NormCalculateDoseHandled(Dose& r){
  TryToDelete<Dose>(this->Abs_NormCalculateDoseHandled);
  if(NULL == &r){
    this->Abs_NormCalculateDoseHandled = NULL;
  }else{
    this->Abs_NormCalculateDoseHandled = new Dose();
    *this->Abs_NormCalculateDoseHandled = r;
  }
}
Dose HandledPairDose::copyAbs_NormCalculateDoseHandled(){
  Dose result;

  if(NULL != this->Abs_NormCalculateDoseHandled){
    result = *this->Abs_NormCalculateDoseHandled;
  }
  return result;
}
void HandledPairDose::allocateAbs_NormCalculateDoseHandled(){
  TryToDelete<Dose>(this->Abs_NormCalculateDoseHandled);
  this->Abs_NormCalculateDoseHandled = new Dose();
}
void HandledPairDose::cleanAbs_NormCalculateDoseHandled(){
  TryToDelete<Dose>(this->Abs_NormCalculateDoseHandled);
  this->Abs_NormCalculateDoseHandled = NULL;
}


//Rel
Dose* HandledPairDose::getRel_NormCalculateDoseHandled(){
  return this->Rel_NormCalculateDoseHandled;
}
void HandledPairDose::setRel_NormCalculateDoseHandled(Dose& r){
  TryToDelete<Dose>(this->Rel_NormCalculateDoseHandled);
  if(NULL == &r){
    this->Rel_NormCalculateDoseHandled = NULL;
  }else{
    this->Rel_NormCalculateDoseHandled = new Dose();
    *this->Rel_NormCalculateDoseHandled = r;
  }
}
Dose HandledPairDose::copyRel_NormCalculateDoseHandled(){
  Dose result;

  if(NULL != this->Rel_NormCalculateDoseHandled){
    result = *this->Rel_NormCalculateDoseHandled;
  }
  return result;
}
void HandledPairDose::allocateRel_NormCalculateDoseHandled(){
  TryToDelete<Dose>(this->Rel_NormCalculateDoseHandled);
  this->Rel_NormCalculateDoseHandled = new Dose();
}
void HandledPairDose::cleanRel_NormCalculateDoseHandled(){
  TryToDelete<Dose>(this->Rel_NormCalculateDoseHandled);
  this->Rel_NormCalculateDoseHandled = NULL;
}


bool HandledPairDose::getManualSpecialMeasureNormValue(){
  return this->manualSpecialMeasureNormValue;
}

bool HandledPairDose::getManualSpecialCalcNormValue(){
  return this->manualSpecialCalcNormValue;
}

string HandledPairDose::getNormValueStr_measure(){
  return this->normValueStr_measure;
}

string HandledPairDose::getNormValueStr_calculate(){
  return this->normValueStr_calculate;
}

/*---Observer model functions--------------------------*/
/*As a observer: GatePairDose-->HandledPairDose-----------*/
void HandledPairDose::update(Message_Notify message){
  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;
  DosePair* dosePair = NULL;
  Dose* measureDose = NULL;
  Dose* calcDose = NULL;
  MatrixData<double> *dosematrix = NULL;
  MatrixData<double> *tempMatrixData = NULL;
  HANDLE_MODEL handel_Model;
  
  int rows = 0;
  int cols = 0;

  float orginalCAX_X,orginalCAX_Y;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    return;
  }

  handel_Model = globalMem->getHandel_Model();
  
  gatePairDose = globalMem->getGatePairDose();
  if(NULL != gatePairDose){
    dosePair = gatePairDose->getDosePair();

    switch(message)
    {
      case Message_Notify(Update_measure_fromGatePair):
      {
        if(NULL != dosePair){
          measureDose = dosePair->getMeasureDose();

          if(NULL != measureDose){
            this->allocateMeasureDoseHandled();
            *this->measureDoseHandled = *measureDose;

            //Default:both rel and abs normlized
            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),handel_Model);
            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),handel_Model);

            this->Notify(Message_Notify(Update_measure_fromHandledPairDose));
          }

        }
      }
      break;
      case Message_Notify(Update_calculate_fromGatePair):
      {
        if(NULL != dosePair){
          calcDose = dosePair->getCalculateDose();

          if(NULL != calcDose){
            this->allocateCalculateDoseHandled();
            *this->calculateDoseHandled = *calcDose;

            this->alignmentAndSegments_Abs();

            //Default:both rel and abs normlized
            this->normlize(NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Abs),handel_Model);
            this->normlize(NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Rel),handel_Model);

            this->Notify(Message_Notify(Update_calculate_fromHandledPairDose));
          }

        }
      }
      break;

      case Message_Notify(Update_CAX_from_operator):
      {
         /*dose physic center*/

         if(NULL != this->measureDoseHandled && NULL!= this->NormMeasureDoseHandled){
             orginalCAX_X = this->measureDoseHandled->getDoseCentral()->x;
             orginalCAX_Y = this->measureDoseHandled->getDoseCentral()->y;

             if( (orginalCAX_X + MainFormTempValue.operator_measureDoseCentral.x) < 0 ||
                 (orginalCAX_X + MainFormTempValue.operator_measureDoseCentral.x) > (measureDoseHandled->getDoseMatrix()->getRowLength() - 1)*measureDoseHandled->getGridSizes()[0]){

               RunningLog::writeLog("The setted cax x is out of boundary.",__LINE__);
               return;
             }

             if( (orginalCAX_Y + MainFormTempValue.operator_measureDoseCentral.y) < 0 ||
                 (orginalCAX_Y + MainFormTempValue.operator_measureDoseCentral.y) > (measureDoseHandled->getDoseMatrix()->getColLength() - 1)*measureDoseHandled->getGridSizes()[1]){

               RunningLog::writeLog("The setted cax y is out of boundary.",__LINE__);
               return;
             }

             this->measureDoseHandled->getDoseCentral()->x = orginalCAX_X + MainFormTempValue.operator_measureDoseCentral.x;
             this->NormMeasureDoseHandled->getDoseCentral()->x = orginalCAX_X + MainFormTempValue.operator_measureDoseCentral.x;


             this->measureDoseHandled->getDoseCentral()->y = orginalCAX_Y + MainFormTempValue.operator_measureDoseCentral.y;
             this->NormMeasureDoseHandled->getDoseCentral()->y = orginalCAX_Y + MainFormTempValue.operator_measureDoseCentral.y;



             if(NULL != dosePair){
               calcDose = dosePair->getCalculateDose();

               if(NULL != calcDose){
                 this->allocateCalculateDoseHandled();
                 *this->calculateDoseHandled = *calcDose;

                 this->alignmentAndSegments_Abs();

                 //Default:both rel and abs normlized
                this->normlize(NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Abs),handel_Model);
                this->normlize(NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Rel),handel_Model);

               }

             }

             this->Notify(Message_Notify(Update_CAX_from_operator));
         }



      }
      break;

      case Message_Notify(Update_rotation):
      {

        if(NULL != this->measureDoseHandled){

          this->measureDoseHandled->sync_Write_Start();

          dosematrix = this->measureDoseHandled->getDoseMatrix();
          rows = dosematrix->getRowLength();
          cols = dosematrix->getColLength();
          tempMatrixData = new MatrixData<double>();

          tempMatrixData->allocate(rows,cols,1);

          for(int j = 0;j<cols;j++){
            for(int i = 0;i<rows;i++){
              tempMatrixData->modifyValue(j,rows-1-i,0,dosematrix->at(i,j,0));
            }
          }
            
          this->measureDoseHandled->unSync_setDoseMatrix(tempMatrixData);

          this->measureDoseHandled->sync_finish();
            
          calcDose = dosePair->getCalculateDose();

          if(NULL != calcDose){
            this->allocateCalculateDoseHandled();
            *this->calculateDoseHandled = *calcDose;

            this->alignmentAndSegments_Abs();

            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),handel_Model);
            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),handel_Model);

          }else{
            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),handel_Model);
            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),handel_Model);
          }

          this->Notify(Message_Notify(Update_measure_fromHandledPairDose));

          if(NULL != calcDose){
            this->Notify(Message_Notify(Update_calculate_fromHandledPairDose));
          }

          TryToDelete<MatrixData<double> >(tempMatrixData);
        }

        
      }
      break;

      case Message_Notify(Update_leftToRightChange):
      {
        if(NULL != this->measureDoseHandled){

          this->measureDoseHandled->sync_Write_Start();

          dosematrix = this->measureDoseHandled->getDoseMatrix();
          rows = dosematrix->getRowLength();
          cols = dosematrix->getColLength();
          tempMatrixData = new MatrixData<double>();

          tempMatrixData->allocate(rows,cols,1);

          for(int j = 0;j<cols;j++){
            for(int i = 0;i<rows;i++){
              tempMatrixData->modifyValue(rows-1-i,j,0,dosematrix->at(i,j,0));
            }
          }

          this->measureDoseHandled->unSync_setDoseMatrix(tempMatrixData);

          this->measureDoseHandled->sync_finish();
            
          calcDose = dosePair->getCalculateDose();

          if(NULL != calcDose){
            this->allocateCalculateDoseHandled();
            *this->calculateDoseHandled = *calcDose;

            this->alignmentAndSegments_Abs();

            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),handel_Model);
            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),handel_Model);

          }else{
            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),handel_Model);
            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),handel_Model);
          }

          this->Notify(Message_Notify(Update_measure_fromHandledPairDose));

          if(NULL != calcDose){
            this->Notify(Message_Notify(Update_calculate_fromHandledPairDose));
          }

          TryToDelete<MatrixData<double> >(tempMatrixData);
        }


      }
      break;


      case Message_Notify(Update_topToBottomChange):
      {
        if(NULL != this->measureDoseHandled){

          this->measureDoseHandled->sync_Write_Start();

          dosematrix = this->measureDoseHandled->getDoseMatrix();
          rows = dosematrix->getRowLength();
          cols = dosematrix->getColLength();
          tempMatrixData = new MatrixData<double>();

          tempMatrixData->allocate(rows,cols,1);

          for(int j = 0;j<cols;j++){
            for(int i = 0;i<rows;i++){
              tempMatrixData->modifyValue(i,cols - 1 - j,0,dosematrix->at(i,j,0));
            }
          }

          this->measureDoseHandled->unSync_setDoseMatrix(tempMatrixData);

          this->measureDoseHandled->sync_finish();
            
          calcDose = dosePair->getCalculateDose();

          if(NULL != calcDose){
            this->allocateCalculateDoseHandled();
            *this->calculateDoseHandled = *calcDose;

            this->alignmentAndSegments_Abs();

            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),handel_Model);
            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),handel_Model);

          }else{
            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs),handel_Model);
            this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel),handel_Model);
          }

          this->Notify(Message_Notify(Update_measure_fromHandledPairDose));

          if(NULL != calcDose){
            this->Notify(Message_Notify(Update_calculate_fromHandledPairDose));
          }

          TryToDelete<MatrixData<double> >(tempMatrixData);
        }

      }
      break;

      case Message_Notify(Update_Segments):
      {
        if(NULL != this->measureDoseHandled && NULL!= this->NormMeasureDoseHandled){
          if(NULL != dosePair){

            for(int i=0;i<3;i++){
              this->measureDoseHandled->getSegments()[i] = dosePair->getMeasureDose()->getSegments()[i];
              this->NormMeasureDoseHandled->getSegments()[i] = dosePair->getMeasureDose()->getSegments()[i];
            }

            calcDose = dosePair->getCalculateDose();

            if(NULL != calcDose){
              this->allocateCalculateDoseHandled();
              *this->calculateDoseHandled = *calcDose;

              this->alignmentAndSegments_Abs();

              this->normlize(NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Abs),handel_Model);
              this->normlize(NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Rel),handel_Model);

              //this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Abs));
              //this->normlize(NORMLIZE_TYPE(NORM_DOUBLE_Rel));
            }

          }

          this->Notify(Message_Notify(Update_Segments));
        }

      }
      break;

      default:
      {
        RunningLog::writeLog("The ObserverModel is unknown",__LINE__);
      }
      break;

    }
  }

  globalMem = NULL;
  gatePairDose = NULL;
  dosePair = NULL;
  measureDose = NULL;
  calcDose = NULL;
  dosematrix = NULL;
  tempMatrixData = NULL;
}


/*As a object: HandledPairDose-->DisplayPairDose-----------*/
void HandledPairDose::Notify(Message_Notify message){
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

bool HandledPairDose::SEHNotify(IObserver* observer, Message_Notify message){

  __try{
    observer->update(message);
    return true;
  }
  __except (EXCEPTION_EXECUTE_HANDLER){

    RunningLog::writeLog("The Observer is cleaned,the visiting is unreachable,Please allocate and assign a new Observer");
    return false;
  }

}

void HandledPairDose::AddObserver(IObserver *pObserver){
  vector<IObserver*>::iterator iterat = ObserverList.begin();
  for (; iterat != ObserverList.end(); iterat++){
    if (pObserver->identify == (*iterat)->identify){
      return;
    }
  }

  ObserverList.push_back(pObserver);
}

void HandledPairDose::DeleteObserver(IObserver *pObserver){
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

/*-----------Function:Normlization-----------------*/
//-----------default:Use the max dose point as the normlization point---
bool HandledPairDose::normlize(NORMLIZE_TYPE normlize_Type,HANDLE_MODEL handel_Model){
  GridPoint measureDosePoint,calcDosePoint;

  double MNormValue,PNormValue;
  
  switch(normlize_Type)
  {
    case NORMLIZE_TYPE(NORM_DOUBLE_Abs):
    {

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_Read_Start();
      }
      if(NULL != this->calculateDoseHandled){
        this->calculateDoseHandled->sync_Read_Start();
      }
      measureDosePoint = getMaxValuePoint(*this->measureDoseHandled->getDoseMatrix());
      MNormValue = (*this->measureDoseHandled->getDoseMatrix())[measureDosePoint];

      this->allocateNormMeasureDoseHandled();
      this->NormMeasureDoseHandled->sync_Write_Start();

      this->NormlizationPosition_Measure = convertFromGridPositionToPhyPosition(measureDosePoint,this->measureDoseHandled->getGridSizes());

      this->manualSpecialMeasureNormValue = false;
      this->normValueStr_measure = "";

      unSync_Normlize(this->measureDoseHandled,this->NormMeasureDoseHandled,MNormValue,handel_Model);
      this->NormMeasureDoseHandled->sync_finish();

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_finish();
      }

      if(NULL != this->calculateDoseHandled){
        this->allocateAbs_NormCalculateDoseHandled();
        this->Abs_NormCalculateDoseHandled->sync_Write_Start();
        calcDosePoint = getCorrespondingPointInCalcPlan_And_Adjust(this->measureDoseHandled,this->calculateDoseHandled,measureDosePoint);

        //this->NormlizationPoint_Calculate = calcDosePoint;
        this->NormlizationPosition_Calculate = convertFromGridPositionToPhyPosition(calcDosePoint,this->measureDoseHandled->getGridSizes(),this->measureDoseHandled->getSegments());

        this->manualSpecialCalcNormValue = false;
        this->normValueStr_calculate = "";

        PNormValue = MNormValue;
        
        unSync_Normlize(this->calculateDoseHandled,this->Abs_NormCalculateDoseHandled,PNormValue,handel_Model);
        this->Abs_NormCalculateDoseHandled->sync_finish();
      }


      if(NULL != this->calculateDoseHandled){
        this->calculateDoseHandled->sync_finish();
      }

    }
    break;

    case NORMLIZE_TYPE(NORM_DOUBLE_Rel):
    {
      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_Read_Start();
      }
      if(NULL != this->calculateDoseHandled){
        this->calculateDoseHandled->sync_Read_Start();
      }
      measureDosePoint = getMaxValuePoint(*this->measureDoseHandled->getDoseMatrix());

      this->allocateNormMeasureDoseHandled();
      this->NormMeasureDoseHandled->sync_Write_Start();


      this->NormlizationPosition_Measure = convertFromGridPositionToPhyPosition(measureDosePoint,this->measureDoseHandled->getGridSizes());

      this->manualSpecialMeasureNormValue = false;
      this->normValueStr_measure = "";

      MNormValue = (*this->measureDoseHandled->getDoseMatrix())[measureDosePoint];

      unSync_Normlize(this->measureDoseHandled,this->NormMeasureDoseHandled,MNormValue,handel_Model);
      this->NormMeasureDoseHandled->sync_finish();

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_finish();
      }

      if(NULL != this->calculateDoseHandled){
        this->allocateRel_NormCalculateDoseHandled();
        this->Rel_NormCalculateDoseHandled->sync_Write_Start();
        calcDosePoint = getCorrespondingPointInCalcPlan_And_Adjust(this->measureDoseHandled,this->calculateDoseHandled,measureDosePoint);

        this->NormlizationPosition_Calculate = convertFromGridPositionToPhyPosition(calcDosePoint,this->measureDoseHandled->getGridSizes(),this->measureDoseHandled->getSegments());

        this->manualSpecialCalcNormValue = false;
        this->normValueStr_calculate = "";

        PNormValue = (*this->calculateDoseHandled->getDoseMatrix())[calcDosePoint];

        unSync_Normlize(this->calculateDoseHandled,this->Rel_NormCalculateDoseHandled,PNormValue,handel_Model);
        this->Rel_NormCalculateDoseHandled->sync_finish();
      }


      if(NULL != this->calculateDoseHandled){
        this->calculateDoseHandled->sync_finish();
      }

    }
    break;


    case NORMLIZE_TYPE(NORM_SINGLE_MEASUREMENT_Abs_or_Rel):
    {

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_Read_Start();

        this->allocateNormMeasureDoseHandled();
        this->NormMeasureDoseHandled->sync_Write_Start();
        measureDosePoint = getMaxValuePoint(*this->measureDoseHandled->getDoseMatrix());

        this->NormlizationPosition_Measure = convertFromGridPositionToPhyPosition(measureDosePoint,this->measureDoseHandled->getGridSizes());

        this->manualSpecialMeasureNormValue = false;
        this->normValueStr_measure = "";

        MNormValue = (*this->measureDoseHandled->getDoseMatrix())[measureDosePoint];

        unSync_Normlize(this->measureDoseHandled,this->NormMeasureDoseHandled,MNormValue,handel_Model);

        this->NormMeasureDoseHandled->sync_finish();
        this->measureDoseHandled->sync_finish();
      }
    }
    break;
    
    case NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Abs):
    {
      if(NULL != this->measureDoseHandled && NULL != this->NormMeasureDoseHandled){

        this->NormMeasureDoseHandled->unSync_setBoundaryPoints(this->measureDoseHandled->getBoundaryPoints());
        this->NormMeasureDoseHandled->unSync_setGridSizes(this->measureDoseHandled->getGridSizes());
        this->NormMeasureDoseHandled->unSync_setSegments(this->measureDoseHandled->getSegments());
        this->NormMeasureDoseHandled->unSync_setDoseCentral(*(this->measureDoseHandled->getDoseCentral()));
        this->NormMeasureDoseHandled->unSync_setDoseUnit(this->measureDoseHandled->unSync_getDoseUnit());
        this->NormMeasureDoseHandled->unSync_setFileName(this->measureDoseHandled->unSync_getFileName());
        this->NormMeasureDoseHandled->unSync_setFileType(this->measureDoseHandled->unSync_getFileType());
        this->NormMeasureDoseHandled->unSync_setFirstAlignmentCentral(*(this->measureDoseHandled->getFirstAlignmentCentral()));


        //this->AbsMeasureDoseHandled->sync_Read_Start();
        measureDosePoint = getMaxValuePoint(*this->measureDoseHandled->getDoseMatrix());
        //this->AbsMeasureDoseHandled->sync_finish();
        MNormValue = (*this->measureDoseHandled->getDoseMatrix())[measureDosePoint];

        if(NULL != this->calculateDoseHandled){
          this->calculateDoseHandled->sync_Read_Start();

          calcDosePoint = getCorrespondingPointInCalcPlan_And_Adjust(this->measureDoseHandled,this->calculateDoseHandled,measureDosePoint);

          this->allocateAbs_NormCalculateDoseHandled();
          this->Abs_NormCalculateDoseHandled->sync_Write_Start();

          this->NormlizationPosition_Calculate = convertFromGridPositionToPhyPosition(calcDosePoint,this->measureDoseHandled->getGridSizes(),this->measureDoseHandled->getSegments());

          this->manualSpecialCalcNormValue = false;
          this->normValueStr_calculate = "";

          PNormValue = MNormValue;
          unSync_Normlize(this->calculateDoseHandled,this->Abs_NormCalculateDoseHandled,PNormValue,handel_Model);

          this->Abs_NormCalculateDoseHandled->sync_finish();
          this->calculateDoseHandled->sync_finish();
                              
        }
      }
    }
    break;

    case NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Rel):
    {
      if(NULL != this->measureDoseHandled && NULL != this->NormMeasureDoseHandled){
        this->NormMeasureDoseHandled->unSync_setBoundaryPoints(this->measureDoseHandled->getBoundaryPoints());
        this->NormMeasureDoseHandled->unSync_setGridSizes(this->measureDoseHandled->getGridSizes());
        this->NormMeasureDoseHandled->unSync_setSegments(this->measureDoseHandled->getSegments());
        this->NormMeasureDoseHandled->unSync_setDoseCentral(*(this->measureDoseHandled->getDoseCentral()));
        this->NormMeasureDoseHandled->unSync_setDoseUnit(this->measureDoseHandled->unSync_getDoseUnit());
        this->NormMeasureDoseHandled->unSync_setFileName(this->measureDoseHandled->unSync_getFileName());
        this->NormMeasureDoseHandled->unSync_setFileType(this->measureDoseHandled->unSync_getFileType());
        this->NormMeasureDoseHandled->unSync_setFirstAlignmentCentral(*(this->measureDoseHandled->getFirstAlignmentCentral()));

        //this->AbsMeasureDoseHandled->sync_Read_Start();
        measureDosePoint = getMaxValuePoint(*this->measureDoseHandled->getDoseMatrix());
        //this->AbsMeasureDoseHandled->sync_finish();
        MNormValue = (*this->measureDoseHandled->getDoseMatrix())[measureDosePoint];

        if(NULL != this->calculateDoseHandled){
          this->calculateDoseHandled->sync_Read_Start();

          calcDosePoint = getCorrespondingPointInCalcPlan_And_Adjust(this->measureDoseHandled,this->calculateDoseHandled,measureDosePoint);

          this->allocateRel_NormCalculateDoseHandled();
          this->Rel_NormCalculateDoseHandled->sync_Write_Start();

          this->NormlizationPosition_Calculate = convertFromGridPositionToPhyPosition(calcDosePoint,this->measureDoseHandled->getGridSizes(),this->measureDoseHandled->getSegments());

          this->manualSpecialCalcNormValue = false;
          this->normValueStr_calculate = "";

          PNormValue = (*this->calculateDoseHandled->getDoseMatrix())[calcDosePoint];

          unSync_Normlize(this->calculateDoseHandled,this->Rel_NormCalculateDoseHandled,PNormValue,handel_Model);

          this->Rel_NormCalculateDoseHandled->sync_finish();
          this->calculateDoseHandled->sync_finish();

        }
      }
    }
    break;

    default:
    break;
  }

  return true;
}

bool HandledPairDose::normlize(NORMLIZE_TYPE normlize_Type,GridPoint _normPoint,HANDLE_MODEL handel_Model){

  double MNormValue,PNormValue;
  GridPoint correspondCalcPoint;
  switch(normlize_Type)
  {
    case NORMLIZE_TYPE(NORM_DOUBLE_Abs):
    {

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_Read_Start();
      }
      if(NULL != this->calculateDoseHandled){
        this->calculateDoseHandled->sync_Read_Start();
      }
      MNormValue = (*this->measureDoseHandled->getDoseMatrix())[_normPoint];

      this->allocateNormMeasureDoseHandled();
      this->NormMeasureDoseHandled->sync_Write_Start();


      this->NormlizationPosition_Measure = convertFromGridPositionToPhyPosition(_normPoint,this->measureDoseHandled->getGridSizes());

      this->manualSpecialMeasureNormValue = false;
      this->normValueStr_measure = "";

      unSync_Normlize(this->measureDoseHandled,this->NormMeasureDoseHandled,MNormValue,handel_Model);
      this->NormMeasureDoseHandled->sync_finish();

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_finish();
      }

      if(NULL != this->calculateDoseHandled){
        this->allocateAbs_NormCalculateDoseHandled();
        this->Abs_NormCalculateDoseHandled->sync_Write_Start();
        correspondCalcPoint = getCorrespondingPointInCalcPlan_And_Adjust(this->measureDoseHandled,this->calculateDoseHandled,_normPoint);

        this->NormlizationPosition_Calculate = convertFromGridPositionToPhyPosition(correspondCalcPoint,this->measureDoseHandled->getGridSizes(),this->measureDoseHandled->getSegments());

        this->manualSpecialCalcNormValue = false;
        this->normValueStr_calculate = "";

        PNormValue = MNormValue;
        unSync_Normlize(this->calculateDoseHandled,this->Abs_NormCalculateDoseHandled,PNormValue,handel_Model);
        this->Abs_NormCalculateDoseHandled->sync_finish();
      }


      if(NULL != this->calculateDoseHandled){
        this->calculateDoseHandled->sync_finish();
      }

    }
    break;

    case NORMLIZE_TYPE(NORM_DOUBLE_Rel):
    {

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_Read_Start();
      }
      if(NULL != this->calculateDoseHandled){
        this->calculateDoseHandled->sync_Read_Start();
      }

      this->allocateNormMeasureDoseHandled();
      this->NormMeasureDoseHandled->sync_Write_Start();


      this->NormlizationPosition_Measure = convertFromGridPositionToPhyPosition(_normPoint,this->measureDoseHandled->getGridSizes());

      this->manualSpecialMeasureNormValue = false;
      this->normValueStr_measure = "";

      MNormValue = (*this->measureDoseHandled->getDoseMatrix())[_normPoint];
      
      unSync_Normlize(this->measureDoseHandled,this->NormMeasureDoseHandled,MNormValue,handel_Model);
      this->NormMeasureDoseHandled->sync_finish();

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_finish();
      }

      if(NULL != this->calculateDoseHandled){
        this->allocateRel_NormCalculateDoseHandled();
        this->Rel_NormCalculateDoseHandled->sync_Write_Start();
        correspondCalcPoint = getCorrespondingPointInCalcPlan_And_Adjust(this->measureDoseHandled,this->calculateDoseHandled,_normPoint);

        this->NormlizationPosition_Calculate = convertFromGridPositionToPhyPosition(correspondCalcPoint,this->measureDoseHandled->getGridSizes(),this->measureDoseHandled->getSegments());

        this->manualSpecialCalcNormValue = false;
        this->normValueStr_calculate = "";

        PNormValue = (*this->calculateDoseHandled->getDoseMatrix())[correspondCalcPoint];

        unSync_Normlize(this->calculateDoseHandled,this->Rel_NormCalculateDoseHandled,PNormValue,handel_Model);
        this->Rel_NormCalculateDoseHandled->sync_finish();
      }


      if(NULL != this->calculateDoseHandled){
        this->calculateDoseHandled->sync_finish();
      }

    }
    break;


    case NORMLIZE_TYPE(NORM_SINGLE_MEASUREMENT_Abs_or_Rel):
    {

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_Read_Start();

        this->allocateNormMeasureDoseHandled();
        this->NormMeasureDoseHandled->sync_Write_Start();

        this->NormlizationPosition_Measure = convertFromGridPositionToPhyPosition(_normPoint,this->measureDoseHandled->getGridSizes());

        this->manualSpecialMeasureNormValue = false;
        this->normValueStr_measure = "";

        MNormValue = (*this->measureDoseHandled->getDoseMatrix())[_normPoint];
        unSync_Normlize(this->measureDoseHandled,this->NormMeasureDoseHandled,MNormValue,handel_Model);

        this->NormMeasureDoseHandled->sync_finish();
        this->measureDoseHandled->sync_finish();
      }
    }
    break;
    
    case NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Abs):
    {
      if(NULL != this->measureDoseHandled && NULL != this->NormMeasureDoseHandled){

        this->NormMeasureDoseHandled->unSync_setBoundaryPoints(this->measureDoseHandled->getBoundaryPoints());
        this->NormMeasureDoseHandled->unSync_setGridSizes(this->measureDoseHandled->getGridSizes());
        this->NormMeasureDoseHandled->unSync_setSegments(this->measureDoseHandled->getSegments());
        this->NormMeasureDoseHandled->unSync_setDoseCentral(*(this->measureDoseHandled->getDoseCentral()));
        this->NormMeasureDoseHandled->unSync_setDoseUnit(this->measureDoseHandled->unSync_getDoseUnit());
        this->NormMeasureDoseHandled->unSync_setFileName(this->measureDoseHandled->unSync_getFileName());
        this->NormMeasureDoseHandled->unSync_setFileType(this->measureDoseHandled->unSync_getFileType());
        this->NormMeasureDoseHandled->unSync_setFirstAlignmentCentral(*(this->measureDoseHandled->getFirstAlignmentCentral()));

        MNormValue = (*this->measureDoseHandled->getDoseMatrix())[_normPoint];

        if(NULL != this->calculateDoseHandled){
          this->calculateDoseHandled->sync_Read_Start();

          correspondCalcPoint = getCorrespondingPointInCalcPlan_And_Adjust(this->measureDoseHandled,this->calculateDoseHandled,_normPoint);

          this->allocateAbs_NormCalculateDoseHandled();
          this->Abs_NormCalculateDoseHandled->sync_Write_Start();

          this->NormlizationPosition_Calculate = convertFromGridPositionToPhyPosition(correspondCalcPoint,this->measureDoseHandled->getGridSizes(),this->measureDoseHandled->getSegments());

          this->manualSpecialCalcNormValue = false;
          this->normValueStr_calculate = "";

          PNormValue = MNormValue;
          unSync_Normlize(this->calculateDoseHandled,this->Abs_NormCalculateDoseHandled,PNormValue,handel_Model);

          this->Abs_NormCalculateDoseHandled->sync_finish();
          this->calculateDoseHandled->sync_finish();                       
        }
      }
    }
    break;

    case NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Rel):
    {
      if(NULL != this->measureDoseHandled && NULL != this->NormMeasureDoseHandled){

        this->NormMeasureDoseHandled->unSync_setBoundaryPoints(this->measureDoseHandled->getBoundaryPoints());
        this->NormMeasureDoseHandled->unSync_setGridSizes(this->measureDoseHandled->getGridSizes());
        this->NormMeasureDoseHandled->unSync_setSegments(this->measureDoseHandled->getSegments());
        this->NormMeasureDoseHandled->unSync_setDoseCentral(*(this->measureDoseHandled->getDoseCentral()));
        this->NormMeasureDoseHandled->unSync_setDoseUnit(this->measureDoseHandled->unSync_getDoseUnit());
        this->NormMeasureDoseHandled->unSync_setFileName(this->measureDoseHandled->unSync_getFileName());
        this->NormMeasureDoseHandled->unSync_setFileType(this->measureDoseHandled->unSync_getFileType());
        this->NormMeasureDoseHandled->unSync_setFirstAlignmentCentral(*(this->measureDoseHandled->getFirstAlignmentCentral()));

        MNormValue = (*this->measureDoseHandled->getDoseMatrix())[_normPoint];

        if(NULL != this->calculateDoseHandled){
          this->calculateDoseHandled->sync_Read_Start();

          correspondCalcPoint = getCorrespondingPointInCalcPlan_And_Adjust(this->measureDoseHandled,this->calculateDoseHandled,_normPoint);

          this->allocateRel_NormCalculateDoseHandled();
          this->Rel_NormCalculateDoseHandled->sync_Write_Start();

          this->NormlizationPosition_Calculate = convertFromGridPositionToPhyPosition(correspondCalcPoint,this->measureDoseHandled->getGridSizes(),this->measureDoseHandled->getSegments());

          this->manualSpecialCalcNormValue = false;
          this->normValueStr_calculate = "";

          PNormValue = (*this->calculateDoseHandled->getDoseMatrix())[correspondCalcPoint];

          unSync_Normlize(this->calculateDoseHandled,this->Rel_NormCalculateDoseHandled,PNormValue,handel_Model);

          this->Rel_NormCalculateDoseHandled->sync_finish();
          this->calculateDoseHandled->sync_finish();                       
        }
      }
    }
    break;

    default:
    break;
  }

  return true;

}



//----------------------------------Norm: PhysicalPoint-------------------------------
bool HandledPairDose::normlize(NORMLIZE_TYPE normlize_Type,PhysicalPoint _normPoint){
  GlobalMembers *globalMem = NULL;
  GatePairDose *gatePairDose = NULL;
  DosePair* dosePair = NULL;

  HANDLE_MODEL handle_model;

  PhysicalPoint calcDoseCentral;

  double MNormValue,PNormValue;
  PhysicalPoint correspondCalcPhysicalPoint;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return false;
  }

  handle_model = globalMem->getHandel_Model();
  
  gatePairDose = globalMem->getGatePairDose();
  if(NULL == gatePairDose){
    RunningLog::writeLog("The gatePairDose is NULL;",__LINE__);
    return false;
  }

  dosePair = gatePairDose->getDosePair();
  if(NULL == dosePair){
    RunningLog::writeLog("The dosePair is NULL;",__LINE__);
    return false;
  }

  switch(normlize_Type)
  {
    case NORMLIZE_TYPE(NORM_DOUBLE_Abs):
    {

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_Read_Start();
      }
      if(NULL != this->calculateDoseHandled){
        this->calculateDoseHandled->sync_Read_Start();
      }
      MNormValue = getNormDoseDataInAPosition( *(this->measureDoseHandled->getDoseMatrix()),_normPoint,this->measureDoseHandled->getGridSizes(),handle_model);

      this->allocateNormMeasureDoseHandled();
      this->NormMeasureDoseHandled->sync_Write_Start();

      this->NormlizationPosition_Measure = _normPoint;

      this->manualSpecialMeasureNormValue = false;
      this->normValueStr_measure = "";

      unSync_Normlize(this->measureDoseHandled,this->NormMeasureDoseHandled,MNormValue,handle_model);
      this->NormMeasureDoseHandled->sync_finish();

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_finish();
      }

      if(NULL != this->calculateDoseHandled){
        this->allocateAbs_NormCalculateDoseHandled();
        this->Abs_NormCalculateDoseHandled->sync_Write_Start();

        correspondCalcPhysicalPoint =  getCorrespondingPhysicalPointInCalcPlan(this->measureDoseHandled,this->calculateDoseHandled,_normPoint);

        this->NormlizationPosition_Calculate = correspondCalcPhysicalPoint;

        this->manualSpecialCalcNormValue = false;
        this->normValueStr_calculate = "";

        PNormValue = MNormValue;
        unSync_Normlize(this->calculateDoseHandled,this->Abs_NormCalculateDoseHandled,PNormValue,handle_model);
        this->Abs_NormCalculateDoseHandled->sync_finish();
      }


      if(NULL != this->calculateDoseHandled){
        this->calculateDoseHandled->sync_finish();
      }

    }
    break;

    case NORMLIZE_TYPE(NORM_DOUBLE_Rel):
    {
      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_Read_Start();
      }
      if(NULL != this->calculateDoseHandled){
        this->calculateDoseHandled->sync_Read_Start();
      }

      this->allocateNormMeasureDoseHandled();
      this->NormMeasureDoseHandled->sync_Write_Start();

      MNormValue = getNormDoseDataInAPosition( *(this->measureDoseHandled->getDoseMatrix()),_normPoint,this->measureDoseHandled->getGridSizes(),handle_model);

      this->NormlizationPosition_Measure = _normPoint;

      this->manualSpecialMeasureNormValue = false;
      this->normValueStr_measure = "";

      unSync_Normlize(this->measureDoseHandled,this->NormMeasureDoseHandled,MNormValue,handle_model);
      this->NormMeasureDoseHandled->sync_finish();

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_finish();
      }

      if(NULL != this->calculateDoseHandled){
        this->allocateRel_NormCalculateDoseHandled();
        this->Rel_NormCalculateDoseHandled->sync_Write_Start();

        correspondCalcPhysicalPoint =  getCorrespondingPhysicalPointInCalcPlan(this->measureDoseHandled,this->calculateDoseHandled,_normPoint);

        this->NormlizationPosition_Calculate = correspondCalcPhysicalPoint;

        if(NULL != dosePair->getCalculateDose())
        {
          calcDoseCentral = *(dosePair->getCalculateDose()->getDoseCentral());

          PNormValue = getNormDoseDataInAPosition( *(this->calculateDoseHandled->getDoseMatrix()),
                                                correspondCalcPhysicalPoint,
                                                *(this->measureDoseHandled->getDoseCentral()),
                                                calcDoseCentral,
                                                this->measureDoseHandled->getGridSizes(),
                                                this->measureDoseHandled->getSegments(),
                                                handle_model);
        }


        this->manualSpecialCalcNormValue = false;
        this->normValueStr_calculate = "";

        unSync_Normlize(this->calculateDoseHandled,this->Rel_NormCalculateDoseHandled,PNormValue,handle_model);
        this->Rel_NormCalculateDoseHandled->sync_finish();
      }


      if(NULL != this->calculateDoseHandled){
        this->calculateDoseHandled->sync_finish();
      }

    }
    break;


    case NORMLIZE_TYPE(NORM_SINGLE_MEASUREMENT_Abs_or_Rel):
    {

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_Read_Start();

        this->allocateNormMeasureDoseHandled();
        this->NormMeasureDoseHandled->sync_Write_Start();

        this->NormlizationPosition_Measure = _normPoint;

        this->manualSpecialMeasureNormValue = false;
        this->normValueStr_measure = "";

        MNormValue = getNormDoseDataInAPosition( *(this->measureDoseHandled->getDoseMatrix()),_normPoint,this->measureDoseHandled->getGridSizes(),handle_model);
        unSync_Normlize(this->measureDoseHandled,this->NormMeasureDoseHandled,MNormValue,handle_model);

        this->NormMeasureDoseHandled->sync_finish();
        this->measureDoseHandled->sync_finish();
      }
    }
    break;
    
    case NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Abs):
    {
      if(NULL != this->measureDoseHandled && NULL != this->NormMeasureDoseHandled){

        this->NormMeasureDoseHandled->unSync_setBoundaryPoints(this->measureDoseHandled->getBoundaryPoints());
        this->NormMeasureDoseHandled->unSync_setGridSizes(this->measureDoseHandled->getGridSizes());
        this->NormMeasureDoseHandled->unSync_setSegments(this->measureDoseHandled->getSegments());
        this->NormMeasureDoseHandled->unSync_setDoseCentral(*(this->measureDoseHandled->getDoseCentral()));
        this->NormMeasureDoseHandled->unSync_setDoseUnit(this->measureDoseHandled->unSync_getDoseUnit());
        this->NormMeasureDoseHandled->unSync_setFileName(this->measureDoseHandled->unSync_getFileName());
        this->NormMeasureDoseHandled->unSync_setFileType(this->measureDoseHandled->unSync_getFileType());
        this->NormMeasureDoseHandled->unSync_setFirstAlignmentCentral(*(this->measureDoseHandled->getFirstAlignmentCentral()));

        MNormValue = getNormDoseDataInAPosition( *(this->measureDoseHandled->getDoseMatrix()),_normPoint,this->measureDoseHandled->getGridSizes(),handle_model);

        if(NULL != this->calculateDoseHandled){
          this->calculateDoseHandled->sync_Read_Start();

          this->allocateAbs_NormCalculateDoseHandled();
          this->Abs_NormCalculateDoseHandled->sync_Write_Start();

          correspondCalcPhysicalPoint =  getCorrespondingPhysicalPointInCalcPlan(this->measureDoseHandled,this->calculateDoseHandled,_normPoint);
          this->NormlizationPosition_Calculate = correspondCalcPhysicalPoint;

          this->manualSpecialCalcNormValue = false;
          this->normValueStr_calculate = "";
          
          PNormValue = MNormValue;
          unSync_Normlize(this->calculateDoseHandled,this->Abs_NormCalculateDoseHandled,PNormValue,handle_model);

          this->Abs_NormCalculateDoseHandled->sync_finish();
          this->calculateDoseHandled->sync_finish();                       
        }
      }
    }
    break;

    case NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Rel):
    {
      if(NULL != this->measureDoseHandled && NULL != this->NormMeasureDoseHandled){

        this->NormMeasureDoseHandled->unSync_setBoundaryPoints(this->measureDoseHandled->getBoundaryPoints());
        this->NormMeasureDoseHandled->unSync_setGridSizes(this->measureDoseHandled->getGridSizes());
        this->NormMeasureDoseHandled->unSync_setSegments(this->measureDoseHandled->getSegments());
        this->NormMeasureDoseHandled->unSync_setDoseCentral(*(this->measureDoseHandled->getDoseCentral()));
        this->NormMeasureDoseHandled->unSync_setDoseUnit(this->measureDoseHandled->unSync_getDoseUnit());
        this->NormMeasureDoseHandled->unSync_setFileName(this->measureDoseHandled->unSync_getFileName());
        this->NormMeasureDoseHandled->unSync_setFileType(this->measureDoseHandled->unSync_getFileType());
        this->NormMeasureDoseHandled->unSync_setFirstAlignmentCentral(*(this->measureDoseHandled->getFirstAlignmentCentral()));

        MNormValue = getNormDoseDataInAPosition( *(this->measureDoseHandled->getDoseMatrix()),_normPoint,this->measureDoseHandled->getGridSizes(),handle_model);
        
        if(NULL != this->calculateDoseHandled){
          this->calculateDoseHandled->sync_Read_Start();

          correspondCalcPhysicalPoint =  getCorrespondingPhysicalPointInCalcPlan(this->measureDoseHandled,this->calculateDoseHandled,_normPoint);

          this->allocateRel_NormCalculateDoseHandled();
          this->Rel_NormCalculateDoseHandled->sync_Write_Start();

          this->NormlizationPosition_Calculate = correspondCalcPhysicalPoint;

          this->manualSpecialCalcNormValue = false;
          this->normValueStr_calculate = "";

          if(NULL != dosePair->getCalculateDose())
          {
            calcDoseCentral = *(dosePair->getCalculateDose()->getDoseCentral());

            PNormValue = getNormDoseDataInAPosition( *(this->calculateDoseHandled->getDoseMatrix()),
                                                correspondCalcPhysicalPoint,
                                                *(this->measureDoseHandled->getDoseCentral()),
                                                calcDoseCentral,
                                                this->measureDoseHandled->getGridSizes(),
                                                this->measureDoseHandled->getSegments(),
                                                handle_model);
          }

          unSync_Normlize(this->calculateDoseHandled,this->Rel_NormCalculateDoseHandled,PNormValue,handle_model);
          this->Rel_NormCalculateDoseHandled->sync_finish();
          this->calculateDoseHandled->sync_finish();                       
        }
      }
    }
    break;

    default:
    break;
  }


  globalMem = NULL;
  gatePairDose = NULL;
  dosePair = NULL;

  return true;

}


bool HandledPairDose::normlize_PercentValue(NORMLIZE_TYPE normlize_Type,double normlizeValue_Percente,HANDLE_MODEL handel_Model){  // %
  double normValue;
  GridPoint maxDosePoint;
  ostringstream os;
  os.str("");
  
  switch(normlize_Type)
  {
    case NORMLIZE_TYPE(NORM_SINGLE_MEASUREMENT_Abs_or_Rel):
    {

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_Read_Start();

        this->allocateNormMeasureDoseHandled();
        this->NormMeasureDoseHandled->sync_Write_Start();

        this->manualSpecialMeasureNormValue = true;
        os<<normlizeValue_Percente<<"%";

        this->normValueStr_measure = os.str();

        maxDosePoint = getMaxValuePoint(*this->measureDoseHandled->getDoseMatrix());
        normValue = (normlizeValue_Percente/100.0)*(*this->measureDoseHandled->getDoseMatrix())[maxDosePoint];

        unSync_Normlize(this->measureDoseHandled,this->NormMeasureDoseHandled,normValue,handel_Model);

        this->NormMeasureDoseHandled->sync_finish();
        this->measureDoseHandled->sync_finish();
      }
    }
    break;

    case NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Abs):
    {
      if(NULL != this->measureDoseHandled && NULL != this->NormMeasureDoseHandled){

        this->NormMeasureDoseHandled->unSync_setBoundaryPoints(this->measureDoseHandled->getBoundaryPoints());
        this->NormMeasureDoseHandled->unSync_setGridSizes(this->measureDoseHandled->getGridSizes());
        this->NormMeasureDoseHandled->unSync_setSegments(this->measureDoseHandled->getSegments());
        this->NormMeasureDoseHandled->unSync_setDoseCentral(*(this->measureDoseHandled->getDoseCentral()));
        this->NormMeasureDoseHandled->unSync_setDoseUnit(this->measureDoseHandled->unSync_getDoseUnit());
        this->NormMeasureDoseHandled->unSync_setFileName(this->measureDoseHandled->unSync_getFileName());
        this->NormMeasureDoseHandled->unSync_setFileType(this->measureDoseHandled->unSync_getFileType());
        this->NormMeasureDoseHandled->unSync_setFirstAlignmentCentral(*(this->measureDoseHandled->getFirstAlignmentCentral()));


        if(NULL != this->calculateDoseHandled){
          this->calculateDoseHandled->sync_Read_Start();

          this->allocateAbs_NormCalculateDoseHandled();
          this->Abs_NormCalculateDoseHandled->sync_Write_Start();

          this->manualSpecialCalcNormValue = true;

          os<<normlizeValue_Percente<<"%";

          this->normValueStr_calculate = os.str();

          maxDosePoint = getMaxValuePoint(*this->calculateDoseHandled->getDoseMatrix());
          normValue = (normlizeValue_Percente/100.0)*(*this->calculateDoseHandled->getDoseMatrix())[maxDosePoint];
          
          unSync_Normlize(this->calculateDoseHandled,this->Abs_NormCalculateDoseHandled,normValue,handel_Model);

          this->Abs_NormCalculateDoseHandled->sync_finish();
          this->calculateDoseHandled->sync_finish();                       
        }
      }
    }
    break;

    case NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Rel):
    {
      if(NULL != this->measureDoseHandled && NULL != this->NormMeasureDoseHandled){

        this->NormMeasureDoseHandled->unSync_setBoundaryPoints(this->measureDoseHandled->getBoundaryPoints());
        this->NormMeasureDoseHandled->unSync_setGridSizes(this->measureDoseHandled->getGridSizes());
        this->NormMeasureDoseHandled->unSync_setSegments(this->measureDoseHandled->getSegments());
        this->NormMeasureDoseHandled->unSync_setDoseCentral(*(this->measureDoseHandled->getDoseCentral()));
        this->NormMeasureDoseHandled->unSync_setDoseUnit(this->measureDoseHandled->unSync_getDoseUnit());
        this->NormMeasureDoseHandled->unSync_setFileName(this->measureDoseHandled->unSync_getFileName());
        this->NormMeasureDoseHandled->unSync_setFileType(this->measureDoseHandled->unSync_getFileType());
        this->NormMeasureDoseHandled->unSync_setFirstAlignmentCentral(*(this->measureDoseHandled->getFirstAlignmentCentral()));


        if(NULL != this->calculateDoseHandled){
          this->calculateDoseHandled->sync_Read_Start();

          this->allocateRel_NormCalculateDoseHandled();
          this->Rel_NormCalculateDoseHandled->sync_Write_Start();

          this->manualSpecialCalcNormValue = true;

          os<<normlizeValue_Percente<<"%";

          this->normValueStr_calculate = os.str();

          maxDosePoint = getMaxValuePoint(*this->calculateDoseHandled->getDoseMatrix());
          normValue = (normlizeValue_Percente/100.0)*(*this->calculateDoseHandled->getDoseMatrix())[maxDosePoint];
          
          unSync_Normlize(this->calculateDoseHandled,this->Rel_NormCalculateDoseHandled,normValue,handel_Model);

          this->Rel_NormCalculateDoseHandled->sync_finish();
          this->calculateDoseHandled->sync_finish();                       
        }
      }
    }
    break;

    default:
    break;
  }

  return true;
}

bool HandledPairDose::normlize_ActualValue(NORMLIZE_TYPE normlize_Type,double normlizeValue,HANDLE_MODEL handel_Model){

  ostringstream os;
  os.str("");
  
  switch(normlize_Type)
  {
    case NORMLIZE_TYPE(NORM_SINGLE_MEASUREMENT_Abs_or_Rel):
    {

      if(NULL != this->measureDoseHandled){
        this->measureDoseHandled->sync_Read_Start();

        this->allocateNormMeasureDoseHandled();
        this->NormMeasureDoseHandled->sync_Write_Start();

        this->manualSpecialMeasureNormValue = true;

        os<<normlizeValue<<"cGy";

        this->normValueStr_measure = os.str();
        
        unSync_Normlize(this->measureDoseHandled,this->NormMeasureDoseHandled,normlizeValue,handel_Model);

        this->NormMeasureDoseHandled->sync_finish();
        this->measureDoseHandled->sync_finish();
      }
    }
    break;

    case NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Abs):
    {
      if(NULL != this->measureDoseHandled && NULL != this->NormMeasureDoseHandled){

        
        this->NormMeasureDoseHandled->unSync_setBoundaryPoints(this->measureDoseHandled->getBoundaryPoints());
        this->NormMeasureDoseHandled->unSync_setGridSizes(this->measureDoseHandled->getGridSizes());
        this->NormMeasureDoseHandled->unSync_setSegments(this->measureDoseHandled->getSegments());
        this->NormMeasureDoseHandled->unSync_setDoseCentral(*(this->measureDoseHandled->getDoseCentral()));
        this->NormMeasureDoseHandled->unSync_setDoseUnit(this->measureDoseHandled->unSync_getDoseUnit());
        this->NormMeasureDoseHandled->unSync_setFileName(this->measureDoseHandled->unSync_getFileName());
        this->NormMeasureDoseHandled->unSync_setFileType(this->measureDoseHandled->unSync_getFileType());
        this->NormMeasureDoseHandled->unSync_setFirstAlignmentCentral(*(this->measureDoseHandled->getFirstAlignmentCentral()));


        if(NULL != this->calculateDoseHandled){
          this->calculateDoseHandled->sync_Read_Start();

          this->allocateAbs_NormCalculateDoseHandled();
          this->Abs_NormCalculateDoseHandled->sync_Write_Start();

          this->manualSpecialCalcNormValue = true;

          os<<normlizeValue<<"cGy";

          this->normValueStr_calculate = os.str();
          
          unSync_Normlize(this->calculateDoseHandled,this->Abs_NormCalculateDoseHandled,normlizeValue,handel_Model);

          this->Abs_NormCalculateDoseHandled->sync_finish();
          this->calculateDoseHandled->sync_finish();                       
        }
      }
    }
    break;

    case NORMLIZE_TYPE(NORM_SINGLE_CALCULATION_Rel):
    {
      if(NULL != this->measureDoseHandled && NULL != this->NormMeasureDoseHandled){

        this->NormMeasureDoseHandled->unSync_setBoundaryPoints(this->measureDoseHandled->getBoundaryPoints());
        this->NormMeasureDoseHandled->unSync_setGridSizes(this->measureDoseHandled->getGridSizes());
        this->NormMeasureDoseHandled->unSync_setSegments(this->measureDoseHandled->getSegments());
        this->NormMeasureDoseHandled->unSync_setDoseCentral(*(this->measureDoseHandled->getDoseCentral()));
        this->NormMeasureDoseHandled->unSync_setDoseUnit(this->measureDoseHandled->unSync_getDoseUnit());
        this->NormMeasureDoseHandled->unSync_setFileName(this->measureDoseHandled->unSync_getFileName());
        this->NormMeasureDoseHandled->unSync_setFileType(this->measureDoseHandled->unSync_getFileType());
        this->NormMeasureDoseHandled->unSync_setFirstAlignmentCentral(*(this->measureDoseHandled->getFirstAlignmentCentral()));


        if(NULL != this->calculateDoseHandled){
          this->calculateDoseHandled->sync_Read_Start();

          this->allocateRel_NormCalculateDoseHandled();
          this->Rel_NormCalculateDoseHandled->sync_Write_Start();

          this->manualSpecialCalcNormValue = true;

          os<<normlizeValue<<"cGy";

          this->normValueStr_calculate = os.str();
          
          unSync_Normlize(this->calculateDoseHandled,this->Rel_NormCalculateDoseHandled,normlizeValue,handel_Model);

          this->Rel_NormCalculateDoseHandled->sync_finish();
          this->calculateDoseHandled->sync_finish();                       
        }
      }
    }
    break;

    default:
    break;
  }

  return true;
  

}


bool HandledPairDose::unSync_Normlize(Dose* sourceDose,Dose* destinct,double normlizeValue,HANDLE_MODEL handel_Model){
  double* sourcePtr = NULL;
  MatrixData<double>* sourceMatrixdose  = NULL;
  double* destinctPtr = NULL;
  int rows,cols;
  int decimal = 3;
  int tempSourcePowInt;

  if(NULL == sourceDose){
    RunningLog::writeLog("The handled sourceDose(Abs Dose) can not be null",__LINE__);
    return false;
  }

  if(NULL == sourceDose){
    RunningLog::writeLog("The handled destinct(Norm Dose) can not be null",__LINE__);
    return false;
  }

  sourceMatrixdose = sourceDose->getDoseMatrix();
  if(NULL == sourceMatrixdose){
    RunningLog::writeLog("The matrixDose is NULL",__LINE__);
    return false;
  }

  destinct->unSync_setBoundaryPoints(sourceDose->getBoundaryPoints());
  destinct->unSync_setGridSizes(sourceDose->getGridSizes());
  destinct->unSync_setSegments(sourceDose->getSegments());
  destinct->unSync_setDoseCentral(*sourceDose->getDoseCentral());
  destinct->unSync_setDoseUnit(sourceDose->unSync_getDoseUnit());
  destinct->unSync_setFileName(sourceDose->unSync_getFileName());
  destinct->unSync_setFileType(sourceDose->unSync_getFileType());
  destinct->unSync_setFirstAlignmentCentral(*sourceDose->getFirstAlignmentCentral());

  destinct->unSync_allocateMatrix(sourceMatrixdose->getRowLength(),
                                  sourceMatrixdose->getColLength(),
                                  sourceMatrixdose->getHeightLength());
  destinctPtr = destinct->getDoseMatrix()->getData();

  sourcePtr = sourceMatrixdose->getData();
  rows = sourceMatrixdose->getRowLength();
  cols = sourceMatrixdose->getColLength();


  switch(handel_Model)
  {
    case HANDLE_MODEL(SNDAC):
    {
      for(int j=0;j<cols;j++){
        for(int i=0;i<rows;i++){
          tempSourcePowInt = doubleToAroundPowInt(*sourcePtr,decimal);

          (*destinctPtr) = doubleTrim( ((tempSourcePowInt*100.0)/normlizeValue)/pow(10,decimal),decimal);
    
          sourcePtr++;
          destinctPtr++;
        }
      }
    }
    break;
    
    case HANDLE_MODEL(ADAC):
    default:
    {
      for(int j=0;j<cols;j++){
        for(int i=0;i<rows;i++){
          (*destinctPtr) = (*sourcePtr)/normlizeValue;
          //normliazetion
          (*destinctPtr)*=100.0;    //%
    
          sourcePtr++;
          destinctPtr++;
        }
      }
    }
    break;
  }
  


  sourceMatrixdose = NULL;
  sourcePtr = NULL;
  destinctPtr = NULL;

  return true;
}

/*----------Function:alignment----------------*/
bool HandledPairDose::alignmentAndSegments_Abs(){
  Dose* measureDose = NULL;
  Dose* calcDose = NULL;
  GlobalMembers *globalMem = NULL;
  HANDLE_MODEL handle_model;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;",__LINE__);
    return false;
  }

  handle_model = globalMem->getHandel_Model();

  measureDose = this->measureDoseHandled;
  if(NULL==measureDose){
    RunningLog::writeLog("The measureDoseHandled is NULL",__LINE__);
    return false;
  }
  if(NULL==measureDose->getDoseMatrix()){
    RunningLog::writeLog("The measureDoseHandled DoseMatrix is NULL",__LINE__);
    return false;
  }
  calcDose = this->calculateDoseHandled;
  if(NULL==calcDose){
    RunningLog::writeLog("The calculateDoseHandled is NULL",__LINE__);
    return false;
  }
  if(NULL==calcDose->getDoseMatrix()){
    RunningLog::writeLog("The calculateDoseHandled DoseMatrix is NULL",__LINE__);
    return false;
  }

  alignmentAndSegment(measureDose->getDoseMatrix(),
                     measureDose->getGridSizes(),
                     *measureDose->getDoseCentral(),
                     *measureDose->getFirstAlignmentCentral(),
                     calcDose->getDoseMatrix(),
                     calcDose->getGridSizes(),
                     *calcDose->getDoseCentral(),
                     *calcDose->getFirstAlignmentCentral(),
                     measureDose->getSegments(),
                     handle_model);

  globalMem = NULL;
  measureDose = NULL;
  calcDose = NULL;
  return true;
}

GridPoint HandledPairDose::getCorrespondingPointInCalcPlan_And_Adjust(Dose* measure,Dose* calc,GridPoint point){
  GridPoint result;
  
  //GridPoint maxValuePoint;

  if(NULL == measure || NULL == calc){
    RunningLog::writeLog("The measure or calculate dose should not be NULL",__LINE__);
    return result;
  }
  
  result.row = (point.row - measure->getFirstAlignmentCentral()->row)*measure->getSegments()[0]
     + calc->getFirstAlignmentCentral()->row;

  result.col = (point.col - measure->getFirstAlignmentCentral()->col)*measure->getSegments()[1]
     + calc->getFirstAlignmentCentral()->col;


  result.level = 0;

  /*
  maxValuePoint = getMaxValuePoint(*calc->getDoseMatrix());
  if(result.row<0 || result.row > calc->getDoseMatrix()->getRowLength() ||
     result.col<0 || result.col > calc->getDoseMatrix()->getColLength() ||
     (*calc->getDoseMatrix())[result]/(float)(*calc->getDoseMatrix())[maxValuePoint]<0.9){
     result = maxValuePoint;
  }
  */
  return result;
}

GridPoint HandledPairDose::getCorrespondingPointInCalcPlan(Dose* measure,Dose* calc,GridPoint point){
  GridPoint result;

  if(NULL == measure || NULL == calc){
    RunningLog::writeLog("The measure or calculate dose should not be NULL",__LINE__);
    return result;
  }


  result.row = (point.row - measure->getFirstAlignmentCentral()->row)*measure->getSegments()[0]
     + calc->getFirstAlignmentCentral()->row;

  result.col = (point.col - measure->getFirstAlignmentCentral()->col)*measure->getSegments()[1]
     + calc->getFirstAlignmentCentral()->col;


  result.level = 0;


  return result;
}

PhysicalPoint HandledPairDose::getCorrespondingPhysicalPointInCalcPlan(Dose* measure,Dose* calc,PhysicalPoint point){
  PhysicalPoint result;

  if(NULL == measure || NULL == calc){
    RunningLog::writeLog("The measure or calculate dose should not be NULL",__LINE__);
    return result;
  }


  result.x =  point.x - measure->getDoseCentral()->x + calc->getDoseCentral()->x;
  result.y =  point.y - measure->getDoseCentral()->y + calc->getDoseCentral()->y;
  result.z =  -1;

  if(result.x<0 || result.x>(measure->getGridSizes()[0]/measure->getSegments()[0]) ||
     result.y<0 || result.y>(measure->getGridSizes()[1]/measure->getSegments()[1]) ){
     RunningLog::writeLog("The choose point out of boundary",__LINE__);
     return result;
  }
  
  return result;
}







