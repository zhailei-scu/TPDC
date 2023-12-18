//---------------------------------------------------------------------------
#include "DisplayPairDose.h"
#include "GlobalData.h"
#include "LogFrame.h"
//---------------------------------------------------------------------------
//-----------------------Class:DisplayPairDose----------------------------
/*Constructor*/
DisplayPairDose::DisplayPairDose(){
  this->measureDisplayDose = NULL;
  this->calcDisplayDose = NULL;

  this->NormMeasureDisplayDose = NULL;
  this->NormCalcDisplayDose = NULL;

  this->identify = Observer_Id(2);
}

/*Destructor*/
DisplayPairDose::~DisplayPairDose(){
  TryToDelete<Dose>(this->measureDisplayDose);
  this->measureDisplayDose = NULL;

  TryToDelete<Dose>(this->calcDisplayDose);
  this->calcDisplayDose = NULL;

  TryToDelete<Dose>(this->NormMeasureDisplayDose);
  this->NormMeasureDisplayDose = NULL;

  TryToDelete<Dose>(this->NormCalcDisplayDose);
  this->NormCalcDisplayDose = NULL;

  this->identify = Observer_Id(0); //Set to invalid
}

/*Copy Constructor*/
DisplayPairDose::DisplayPairDose(const DisplayPairDose& r){
  this->measureDisplayDose = NULL;
  this->calcDisplayDose = NULL;

  this->NormMeasureDisplayDose = NULL;
  this->NormCalcDisplayDose = NULL;

  this->identify = Observer_Id(0);
  
  if(NULL != &r){

    if(NULL!=r.measureDisplayDose){
      *this->measureDisplayDose = *r.measureDisplayDose;
    }else{
      this->measureDisplayDose = NULL;
    }

    if(NULL!=r.calcDisplayDose){
      *this->calcDisplayDose = *r.calcDisplayDose;
    }else{
      this->calcDisplayDose = NULL;
    }

    if(NULL!=r.NormMeasureDisplayDose){
      *this->NormMeasureDisplayDose = *r.NormMeasureDisplayDose;
    }else{
      this->NormMeasureDisplayDose = NULL;
    }

    if(NULL!=r.NormCalcDisplayDose){
      *this->NormCalcDisplayDose = *r.NormCalcDisplayDose;
    }else{
      this->NormCalcDisplayDose = NULL;
    }

    this->identify = r.identify;
  }

}

/*Overload operator = */
DisplayPairDose DisplayPairDose::operator = (const DisplayPairDose& r){
  TryToDelete<Dose>(this->measureDisplayDose);
  TryToDelete<Dose>(this->calcDisplayDose);
  TryToDelete<Dose>(this->NormMeasureDisplayDose);
  TryToDelete<Dose>(this->NormCalcDisplayDose);

  if(NULL == &r){
    this->measureDisplayDose = NULL;
    this->calcDisplayDose = NULL;

    this->NormMeasureDisplayDose = NULL;
    this->NormCalcDisplayDose = NULL;

    this->identify =Observer_Id(0);
  }else{
    if(NULL!=r.measureDisplayDose){
      *this->measureDisplayDose = *r.measureDisplayDose;
    }else{
      this->measureDisplayDose = NULL;
    }

    if(NULL!=r.calcDisplayDose){
      *this->calcDisplayDose = *r.calcDisplayDose;
    }else{
      this->calcDisplayDose = NULL;
    }

    if(NULL!=r.NormMeasureDisplayDose){
      *this->NormMeasureDisplayDose = *r.NormMeasureDisplayDose;
    }else{
      this->NormMeasureDisplayDose = NULL;
    }

    if(NULL!=r.NormCalcDisplayDose){
      *this->NormCalcDisplayDose = *r.NormCalcDisplayDose;
    }else{
      this->NormCalcDisplayDose = NULL;
    }

    this->identify = r.identify;
  }

  return *this;
}


/*--------------------Basic Function-------------------------------*/
Dose* DisplayPairDose::getMeasureDisplayDose(){
  return this->measureDisplayDose;
}
void DisplayPairDose::setMeasureDisplayDose(Dose& r){
  TryToDelete<Dose>(this->measureDisplayDose);

  if(NULL == &measureDisplayDose){
    this->measureDisplayDose = NULL;
  }else{
    this->measureDisplayDose = new Dose();
    *this->measureDisplayDose = r;
  }
}
Dose DisplayPairDose::copyMeasureDisplayDose(){
  Dose result;
  if(NULL != this->measureDisplayDose){
    result = *this->measureDisplayDose;
  }
  return result;
}
void DisplayPairDose::allocateMeasureDisplayDose(){
  TryToDelete<Dose>(this->measureDisplayDose);
  this->measureDisplayDose = new Dose();
}
void DisplayPairDose::cleanMeasureDisplayDose(){
  TryToDelete<Dose>(this->measureDisplayDose);
  this->measureDisplayDose = NULL;
}

Dose* DisplayPairDose::getCalcDisplayDose(){
  return this->calcDisplayDose;
}
void DisplayPairDose::setCalcDisplayDose(Dose& r){
  TryToDelete<Dose>(this->calcDisplayDose);

  if(NULL == &calcDisplayDose){
    this->calcDisplayDose = NULL;
  }else{
    this->calcDisplayDose = new Dose();
    *this->calcDisplayDose = r;
  }
}
Dose DisplayPairDose::copyCalcDisplayDose(){
  Dose result;
  if(NULL != this->calcDisplayDose){
    result = *this->calcDisplayDose;
  }
  return result;
}
void DisplayPairDose::allocateCalcDisplayDose(){
  TryToDelete<Dose>(this->calcDisplayDose);
  this->calcDisplayDose = new Dose();
}
void DisplayPairDose::cleanCalcDisplayDose(){
  TryToDelete<Dose>(this->calcDisplayDose);
  this->calcDisplayDose = NULL;
}

Dose* DisplayPairDose::getNormMeasureDisplayDose(){
  return this->NormMeasureDisplayDose;
}
void DisplayPairDose::setNormMeasureDisplayDose(Dose& r){
  TryToDelete<Dose>(this->NormMeasureDisplayDose);

  if(NULL == &NormMeasureDisplayDose){
    this->NormMeasureDisplayDose = NULL;
  }else{
    this->NormMeasureDisplayDose = new Dose();
    *this->NormMeasureDisplayDose = r;
  }
}
Dose DisplayPairDose::copyNormMeasureDisplayDose(){
  Dose result;
  if(NULL != this->NormMeasureDisplayDose){
    result = *this->NormMeasureDisplayDose;
  }
  return result;
}
void DisplayPairDose::allocateNormMeasureDisplayDose(){
  TryToDelete<Dose>(this->NormMeasureDisplayDose);
  this->NormMeasureDisplayDose = new Dose();
}
void DisplayPairDose::cleanNormMeasureDisplayDose(){
  TryToDelete<Dose>(this->NormMeasureDisplayDose);
  this->NormMeasureDisplayDose = NULL;
}

Dose* DisplayPairDose::getNormCalcDisplayDose(){
  return this->NormCalcDisplayDose;
}
void DisplayPairDose::setNormCalcDisplayDose(Dose& r){
  TryToDelete<Dose>(this->NormCalcDisplayDose);

  if(NULL == &NormCalcDisplayDose){
    this->NormCalcDisplayDose = NULL;
  }else{
    this->NormCalcDisplayDose = new Dose();
    *this->NormCalcDisplayDose = r;
  }
}
Dose DisplayPairDose::copyNormCalcDisplayDose(){
  Dose result;
  if(NULL != this->NormCalcDisplayDose){
    result = *this->NormCalcDisplayDose;
  }
  return result;
}
void DisplayPairDose::allocateNormCalcDisplayDose(){
  TryToDelete<Dose>(this->NormCalcDisplayDose);
  this->NormCalcDisplayDose = new Dose();
}
void DisplayPairDose::cleanNormCalcDisplayDose(){
  TryToDelete<Dose>(this->NormCalcDisplayDose);
  this->NormCalcDisplayDose = NULL;
}

/*----as a observer,observe the HandledPairDose*/
void DisplayPairDose::update(Message_Notify message){
  GlobalMembers *globalMem = NULL;
  HandledPairDose* handledPairDose = NULL;

  Dose* measureAbsDose = NULL;
  Dose* measureNormDose = NULL;
  Dose* calcAbsDose = NULL;
  Dose* calcNormDose = NULL;

  //while the dose is relative ,display the relative normlization
  DoseType tempDoseType;

  globalMem = GlobalMembers::getInstance();
  if(NULL == globalMem){
    RunningLog::writeLog("The globalInstance is NULL;");
    return;
  }

  handledPairDose = globalMem->getHandledPairDose();
  if(NULL == handledPairDose){
    RunningLog::writeLog("The handledPairDose is NULL;");
    return;
  }



  if(NULL == handledPairDose->getMeasureDoseHandled()){
    RunningLog::writeLog("The measureDose is NULL;");
    return;
  }

  tempDoseType = handledPairDose->getMeasureDoseHandled()->sync_getDoseType();


  switch(message)
  {
    case Message_Notify(Update_measure_fromHandledPairDose):
    {
      TryToDelete<Dose>(this->measureDisplayDose);
      TryToDelete<Dose>(this->NormMeasureDisplayDose);

      this->measureDisplayDose = NULL;
      this->NormMeasureDisplayDose = NULL;

      measureAbsDose = handledPairDose->getMeasureDoseHandled();

      if(NULL != measureAbsDose){
        this->measureDisplayDose = new Dose();
        *this->measureDisplayDose = *measureAbsDose;
      }

      measureNormDose = handledPairDose->getNormMeasureDoseHandled();

      if(NULL != measureNormDose){
        this->NormMeasureDisplayDose = new Dose();
        *this->NormMeasureDisplayDose = *measureNormDose;
      }


    }
    break;
    case Message_Notify(Update_calculate_fromHandledPairDose):
    {
      TryToDelete<Dose>(this->calcDisplayDose);
      TryToDelete<Dose>(this->NormCalcDisplayDose);

      this->calcDisplayDose = NULL;
      this->NormCalcDisplayDose = NULL;


      calcAbsDose = handledPairDose->getCalculateDoseHandled();

      if(NULL != calcAbsDose){
        this->calcDisplayDose = new Dose();
        *this->calcDisplayDose = *calcAbsDose;
      }

      if(DoseType(DOSE_ABSOLUTE) == tempDoseType){
        calcNormDose = handledPairDose->getAbs_NormCalculateDoseHandled();
      }else{
        calcNormDose = handledPairDose->getRel_NormCalculateDoseHandled();
      }

      if(NULL != calcNormDose){
        this->NormCalcDisplayDose = new Dose();
        *this->NormCalcDisplayDose = *calcNormDose;
      }

    }
    break;

    case Message_Notify(Update_CAX_from_operator):
    {

      measureAbsDose = handledPairDose->getMeasureDoseHandled();

      if(NULL != measureAbsDose){
        *this->measureDisplayDose->getDoseCentral() =  *measureAbsDose->getDoseCentral();
      }

      measureNormDose = handledPairDose->getNormMeasureDoseHandled();

      if(NULL != measureNormDose){
        *this->NormMeasureDisplayDose->getDoseCentral() = *measureNormDose->getDoseCentral();
      }

      //update calculate dose data
      TryToDelete<Dose>(this->calcDisplayDose);
      TryToDelete<Dose>(this->NormCalcDisplayDose);

      this->calcDisplayDose = NULL;
      this->NormCalcDisplayDose = NULL;


      calcAbsDose = handledPairDose->getCalculateDoseHandled();

      if(NULL != calcAbsDose){
        this->calcDisplayDose = new Dose();
        *this->calcDisplayDose = *calcAbsDose;
      }

      if(DoseType(DOSE_ABSOLUTE) == tempDoseType){
          calcNormDose = handledPairDose->getAbs_NormCalculateDoseHandled();
      }else{
          calcNormDose = handledPairDose->getRel_NormCalculateDoseHandled();
      }

      if(NULL != calcNormDose){
        this->NormCalcDisplayDose = new Dose();
        *this->NormCalcDisplayDose = *calcNormDose;
      }
    }
    break;

    case Message_Notify(Update_Segments):
    {

      measureAbsDose = handledPairDose->getMeasureDoseHandled();

      if(NULL != measureAbsDose){

        for(int i=0;i<3;i++){
          this->measureDisplayDose->getSegments()[i] = measureAbsDose->getSegments()[i];
        }
      }

      measureNormDose = handledPairDose->getNormMeasureDoseHandled();

      if(NULL != measureNormDose){

        for(int i=0;i<3;i++){
          this->NormMeasureDisplayDose->getSegments()[i] = measureNormDose->getSegments()[i];
        }
      }

      //update calculate dose data
      TryToDelete<Dose>(this->calcDisplayDose);
      TryToDelete<Dose>(this->NormCalcDisplayDose);

      this->calcDisplayDose = NULL;
      this->NormCalcDisplayDose = NULL;


      calcAbsDose = handledPairDose->getCalculateDoseHandled();

      if(NULL != calcAbsDose){
        this->calcDisplayDose = new Dose();
        *this->calcDisplayDose = *calcAbsDose;
      }

      if(DoseType(DOSE_ABSOLUTE) == tempDoseType){
          calcNormDose = handledPairDose->getAbs_NormCalculateDoseHandled();
      }else{
          calcNormDose = handledPairDose->getRel_NormCalculateDoseHandled();
      }

      if(NULL != calcNormDose){
        this->NormCalcDisplayDose = new Dose();
        *this->NormCalcDisplayDose = *calcNormDose;
      }
    }
    break;
    
    default:
    {
      RunningLog::writeLog("The Observer is unknown",__LINE__);
    }
    break;

  }

  globalMem = NULL;
  handledPairDose = NULL;

  measureAbsDose = NULL;
  measureNormDose = NULL;
  calcAbsDose = NULL;
  calcNormDose = NULL;
}

//----------------MapCHECK measure dose Graph  Operation------------------
//---------------------------------Public Functions--------------------------
void DisplayPairDose::MapCHECKMeasureBlineInterpolation(){   //双线性插值
  this->MapCHECKMeasureBlineInterpolation(this->getMeasureDisplayDose());
  this->MapCHECKMeasureBlineInterpolation(this->getNormMeasureDisplayDose());
}
void DisplayPairDose::MapCHECKMeasureInterpolationX(){  //作x方向插值
  this->MapCHECKMeasureInterpolationX(this->getMeasureDisplayDose());
  this->MapCHECKMeasureInterpolationX(this->getNormMeasureDisplayDose());
}
void DisplayPairDose::MapCHECKMeasureInterpolationY(){  //作y方向插值
  this->MapCHECKMeasureInterpolationY(this->getMeasureDisplayDose());
  this->MapCHECKMeasureInterpolationY(this->getNormMeasureDisplayDose());
}
//---------------------------------Private Functions-------------------------

void DisplayPairDose::MapCHECKMeasureBlineInterpolation(Dose *dose){
  vector<int> positiveSlopeSeries;
  vector<int> negativeSlopeSeries;
  MatrixData<int> neighbors;
  int x0,x1,x2,x3,y0,y1,y2,y3;
  float dpostive0,dpostive1,dpostive2,dpostive3;
  float dnegative0,dnegative1,dnegative2,dnegative3;

  if(NULL == dose){
    RunningLog::writeLog("The MeasureDisplayDose is NULL while MapCHECKMeasureBlineInterpolation",__LINE__);
    return;
  }

  if(FILETYPE(MapCHECKMeasureFileType) != dose->sync_getFileType()){
    return;
  }

  dose->sync_Write_Start();

  MatrixData<double>* matrixData = dose->getDoseMatrix();


  if(NULL == matrixData || matrixData->isEmpty()){
    RunningLog::writeLog("The doseMatrix is NULL while MapCHECKMeasureBlineInterpolation",__LINE__);

    dose->sync_finish();

    return;
  }

  double tempValue;

  for(int i=-34;i<35;i=i+4)
  {
    positiveSlopeSeries.push_back(i);
  }

  for(int i=10;i<79;i=i+4)
  {
    negativeSlopeSeries.push_back(i);
  }


  for(int j=0;j<45;j++)
  {
    for(int i=0;i<45;i++)
    {
      //if(detector[i][j] != 1)
      if(false == MainFormTempValue.detectorArray.at(i,j,0))
      {
         if(true == FindFourBasePoints(i,j,positiveSlopeSeries,negativeSlopeSeries,neighbors))
         {
           //x0 = neighbors[0][0];
           x0 = neighbors.at(0,0,0);

           //y0 = neighbors[0][1];
           y0 = neighbors.at(0,1,0);

           //x1 = neighbors[1][0];
           x1 = neighbors.at(1,0,0);

           //y1 = neighbors[1][1];
           y1 = neighbors.at(1,1,0);

           //x2 = neighbors[2][0];
           x2 = neighbors.at(2,0,0);

           //y2 = neighbors[2][1];
           y2 = neighbors.at(2,1,0);

           //x3 = neighbors[3][0];
           x3 = neighbors.at(3,0,0);

           //y3 = neighbors[3][1];
           y3 = neighbors.at(3,1,0);


           if(i>=13 && i<=31 && j>=13 && j<=31)
           {
             //NormDose[j*45+i] = (NormDose[y0*45+x0] + NormDose[y1*45+x1] + NormDose[y2*45+x2] + NormDose[y3*45+x3])/4.0;
             tempValue = (matrixData->at(x0,y0,0) + matrixData->at(x1,y1,0) +
                          matrixData->at(x2,y2,0) + matrixData->at(x3,y3,0))/4.0;
             matrixData->modifyValue(i,j,0,tempValue);
           }
           else
           {
             dpostive0 = abs(i-j-(x0 - y0))/sqrt(2);
             dnegative0 = abs(i+j-(x0 + y0))/sqrt(2);

             dpostive1 = abs(i-j-(x1 - y1))/sqrt(2);
             dnegative1 = abs(i+j-(x1 + y1))/sqrt(2);

             dpostive2 = abs(i-j-(x2 - y2))/sqrt(2);
             dnegative2 = abs(i+j-(x2 + y2))/sqrt(2);

             dpostive3 = abs(i-j-(x3 - y3))/sqrt(2);
             dnegative3 = abs(i+j-(x3 + y3))/sqrt(2);

//             NormDose[j*45+i] = ((2*sqrt(2) - dpostive0)*(2*sqrt(2) - dnegative0)*NormDose[y0*45+x0] +
//                                (2*sqrt(2) - dpostive1)*(2*sqrt(2) - dnegative1)*NormDose[y1*45+x1] +
//                              (2*sqrt(2) - dpostive2)*(2*sqrt(2) - dnegative2)*NormDose[y2*45+x2] +
//                              (2*sqrt(2) - dpostive3)*(2*sqrt(2) - dnegative3)*NormDose[y3*45+x3])/8.0;
             tempValue = ((2*sqrt(2) - dpostive0)*(2*sqrt(2) - dnegative0)*matrixData->at(x0,y0,0) +
                          (2*sqrt(2) - dpostive1)*(2*sqrt(2) - dnegative1)*matrixData->at(x1,y1,0) +
                          (2*sqrt(2) - dpostive2)*(2*sqrt(2) - dnegative2)*matrixData->at(x2,y2,0) +
                          (2*sqrt(2) - dpostive3)*(2*sqrt(2) - dnegative3)*matrixData->at(x3,y3,0))/8.0;
             matrixData->modifyValue(i,j,0,tempValue);

           }

         }

      }
    }
  }



  dose->sync_finish();

  dose = NULL;
  matrixData = NULL;

}

//-------------------双线性插值之前需要找到待插值点的四个基准点-------------------------
inline bool DisplayPairDose::FindFourBasePoints(int x,int y,std::vector<int> positiveSlopeSeries,std::vector<int> negativeSlopeSeries,MatrixData<int>& result)
{
  int neighborPointNum = 4; //four neighborhood points for bilinear interpolation

  result.allocate(4,2,1);

  int negativeSlopeCutpoint,positiveSlopeCutpoint; //y axis Cutpoint for +1 and -1 slop
  int negativeSlopeNeighbor[2] = {-100,-100}; //The two most close line of (x + y = m) in the specical point's up/down
  int positiveSlopeNeighbor[2] = {-100,-100}; //The two most close line of (x - y = m) in the specical point's up/down
  if(x>12 && x<32 && y>12 && y<32)    //MapCHECK内部的一个密集20乘20探测器阵列
  {
    //result[0][0] = x - 1;
    result.modifyValue(0,0,0,x - 1);

    //result[0][1] = y;
    result.modifyValue(0,1,0,y);

    //result[1][0] = x + 1;
    result.modifyValue(1,0,0,x + 1);

    //result[1][1] = y;
    result.modifyValue(1,1,0,y);

    //result[2][0] = x;
    result.modifyValue(2,0,0,x);

    //result[2][1] = y - 1;
    result.modifyValue(2,1,0,y - 1);

    //result[3][0] = x;
    result.modifyValue(3,0,0,x);

    //result[3][1] = y + 1;
    result.modifyValue(3,1,0,y + 1);
  }
  else
  {
     negativeSlopeCutpoint = y + x;
     positiveSlopeCutpoint = y - x;
     neighbor(negativeSlopeCutpoint,negativeSlopeSeries,0,negativeSlopeSeries.size()-1,negativeSlopeNeighbor);
     neighbor(positiveSlopeCutpoint,positiveSlopeSeries,0,positiveSlopeSeries.size()-1,positiveSlopeNeighbor);

     if(negativeSlopeNeighbor[0] != -100 && negativeSlopeNeighbor[1] != -100 && positiveSlopeNeighbor[0] != -100  && positiveSlopeNeighbor[1] != -100)
     {
       //result[0][0] = (negativeSlopeNeighbor[0] - positiveSlopeNeighbor[0])/2; //x0
       result.modifyValue(0,0,0,(negativeSlopeNeighbor[0] - positiveSlopeNeighbor[0])/2);//x0

       //result[0][1] = (negativeSlopeNeighbor[0] + positiveSlopeNeighbor[0])/2; //y0
       result.modifyValue(0,1,0,(negativeSlopeNeighbor[0] + positiveSlopeNeighbor[0])/2);//y0

       //result[1][0] = (negativeSlopeNeighbor[0] - positiveSlopeNeighbor[1])/2; //x1
       result.modifyValue(1,0,0,(negativeSlopeNeighbor[0] - positiveSlopeNeighbor[1])/2);//x1

       //result[1][1] = (negativeSlopeNeighbor[0] + positiveSlopeNeighbor[1])/2; //y1
       result.modifyValue(1,1,0,(negativeSlopeNeighbor[0] + positiveSlopeNeighbor[1])/2);//y1

       //result[2][0] = (negativeSlopeNeighbor[1] - positiveSlopeNeighbor[0])/2; //x2
       result.modifyValue(2,0,0,(negativeSlopeNeighbor[1] - positiveSlopeNeighbor[0])/2);//x2

       //result[2][1] = (negativeSlopeNeighbor[1] + positiveSlopeNeighbor[0])/2; //y2
       result.modifyValue(2,1,0,(negativeSlopeNeighbor[1] + positiveSlopeNeighbor[0])/2);//y2

       //result[3][0] = (negativeSlopeNeighbor[1] - positiveSlopeNeighbor[1])/2; //x3
       result.modifyValue(3,0,0,(negativeSlopeNeighbor[1] - positiveSlopeNeighbor[1])/2);//x3

       //result[3][1] = (negativeSlopeNeighbor[1] + positiveSlopeNeighbor[1])/2; //y3
       result.modifyValue(3,1,0,(negativeSlopeNeighbor[1] + positiveSlopeNeighbor[1])/2);//y3

     }
     else  //not find a rhombus
     {
       result.reset();
       return false;
     }

  }


  for(int i=0;i<neighborPointNum;i++){
    if(result.at(i,0,0)<0 || result.at(i,0,0)>=45 ||
       result.at(i,1,0)<0 || result.at(i,1,0)>=45){
      result.reset();
      return false;
    }
  }


  return true;
}

//----------------------------------------------------------------------------
//在众多斜率为1和-1的探测器排列线簇中找到待插值点所最相邻的两个斜探测器线(探测器刚好在这两个斜探测器线之间)
inline void DisplayPairDose::neighbor(int num,vector<int> Series,int start,int end,int* result)
{
  int middle = (start + end)/2;

  if(start==end)
  {
    return;
  }

  if(Series.at(start)<=num && Series.at(end)>num)
  {
    if((end-start)==1)
    {
      result[0] = Series.at(start);
      result[1] = Series.at(end);
      return;
    }
    else
    {
      neighbor(num,Series,start,middle,result);
      neighbor(num,Series,middle,end,result);
    }

  }
  else
  {
    return;
  }
}

//---------------------------------------------------------------------------
void DisplayPairDose::MapCHECKMeasureInterpolationX(Dose *dose)
{
  if(NULL == dose){
    RunningLog::writeLog("The dose is NULL while MapCHECKMeasureBlineInterpolation",__LINE__);
    return;
  }

  if(FILETYPE(MapCHECKMeasureFileType) != dose->sync_getFileType()){
    RunningLog::writeLog("The MapCHECKMeasureBlineInterpolation meethod is not suti for this fileType",__LINE__);
    return;
  }

  dose->sync_Write_Start();

  MatrixData<double>* matrixData = dose->getDoseMatrix();

  if(NULL == matrixData || matrixData->isEmpty()){
    RunningLog::writeLog("The doseMatrix is NULL while MapCHECKMeasureBlineInterpolation",__LINE__);

    dose->sync_finish();

    return;
  }

  double tempValue;

  int firstDetectorPos; //用来记录每一行第一个探测器的位置

  for(int j=0;j<45;j++)     //沿横(行)向插值
  {
    firstDetectorPos = 0;
    for(int pos=0;pos<45;pos++)    //寻找每一行第一个探测器的位置
    {
      //if(detector[j][k]==1)
      if(true == MainFormTempValue.detectorArray.at(j,pos,0))
      {
        firstDetectorPos = pos;
        break;
      }
    }

    for(int i=0;i<firstDetectorPos;i++)    //每行开始到第一个探测器的每个点
    {
      //NormDose[j*45+i] = (NormDose[j*45+firstDetectorPos])*(float(i)/firstDetectorPos);
      //DoseAbs[j*45+i] = (DoseAbs[j*45+firstDetectorPos])*(float(i)/firstDetectorPos);
      tempValue = (matrixData->at(firstDetectorPos,j,0))*(float(i)/firstDetectorPos);
      matrixData->modifyValue(i,j,0,tempValue);
    }

    for(int i=45-firstDetectorPos;i<45;i++)   //每行最后一个探测器到第45个点
    {
      //NormDose[j*45+i]= (NormDose[j*45+44-firstDetectorPos])*(float(44-i)/firstDetectorPos);
      //DoseAbs[j*45+i]= (DoseAbs[j*45+44-firstDetectorPos])*(float(44-i)/firstDetectorPos);
      tempValue = (matrixData->at(44-firstDetectorPos,j,0))*(float(44-i)/firstDetectorPos);
      matrixData->modifyValue(i,j,0,tempValue);
    }

    for(int i=firstDetectorPos;i<45;i++)  //每行第一个探测器和最后一个探测器
    {                                    //的中间没有探测器的点
      //if(detector[j][i]==1)
      if(true==MainFormTempValue.detectorArray.at(j,i,0))
      {
        for(int iL=i+1;iL<45;iL++)
        {
          //if(detector[j][ii]==1)
          if(true == MainFormTempValue.detectorArray.at(j,iL,0))
          {
            for(int iArr=i+1;iArr<=iL-1;iArr++)
            {
              //NormDose[j*45+iArr] = NormDose[j*45+i] + (iArr-i)*(NormDose[j*45+iL]-NormDose[j*45+i])/float(iL-i);
              //DoseAbs[j*45+iArr] = DoseAbs[j*45+i] + (iArr-i)*(DoseAbs[j*45+iL]-DoseAbs[j*45+i])/float(iL-i);
              tempValue = matrixData->at(i,j,0) + (iArr-i)*(matrixData->at(iL,j,0) - matrixData->at(i,j,0))/float(iL-i);
              matrixData->modifyValue(iArr,j,0,tempValue);
            }
            break;
          }
        }
      }
    }
  }

  dose->sync_finish();

  dose = NULL;
  matrixData = NULL;

}
//----------------------------------------------------------------------------
void DisplayPairDose::MapCHECKMeasureInterpolationY(Dose *dose)
{
  if(NULL == dose){
    RunningLog::writeLog("The dose is NULL while MapCHECKMeasureBlineInterpolation",__LINE__);
    return;
  }

  if(FILETYPE(MapCHECKMeasureFileType) != dose->sync_getFileType()){
    RunningLog::writeLog("The MapCHECKMeasureBlineInterpolation meethod is not suti for this fileType",__LINE__);
    return;
  }

  dose->sync_Write_Start();

  MatrixData<double>* matrixData = dose->getDoseMatrix();

  if(NULL == matrixData || matrixData->isEmpty()){
    RunningLog::writeLog("The doseMatrix is NULL while MapCHECKMeasureBlineInterpolation",__LINE__);

    dose->sync_finish();

    return;
  }

  double tempValue;

  int firstDetectorPos; //用来记录每一列第一个探测器的位置

  for(int i=0;i<45;i++)     //沿纵向插值
  {
    firstDetectorPos = 0;
    for(int pos=0;pos<45;pos++)    //寻找每一列第一个探测器的位置
    {
      //if(detector[k][i]==1)
      if(true == MainFormTempValue.detectorArray.at(pos,i,0))
      {
        firstDetectorPos = pos;
        break;
      }
    }

    for(int j=0;j<firstDetectorPos;j++)    //每列开始到第一个探测器的每个点
    {
      //NormDose[j*45+i] = (NormDose[firstDetectorPos*45+i])*(j/float(firstDetectorPos));
      //DoseAbs[j*45+i] = (DoseAbs[firstDetectorPos*45+i])*(j/float(firstDetectorPos));
      tempValue = (matrixData->at(i,firstDetectorPos,0))*(float(j)/firstDetectorPos);
      matrixData->modifyValue(i,j,0,tempValue);
    }

    for(int j=45-firstDetectorPos;j<45;j++)   //每列最后一个探测器到第45个点
    {
      //NormDose[j*45+i]= (NormDose[(44-firstDetectorPos)*45+i])*(44-j)/float(firstDetectorPos);
      //DoseAbs[j*45+i]= (DoseAbs[(44-firstDetectorPos)*45+i])*(44-j)/float(firstDetectorPos);
      tempValue = (matrixData->at(i,44-firstDetectorPos,0))*(float(44-j)/firstDetectorPos);
      matrixData->modifyValue(i,j,0,tempValue);
    }

    for(int j=firstDetectorPos;j<45;j++)  //每列第一个探测器和最后一个探测器
    {                                    //的中间没有探测器的点
      //if(detector[j][i]==1)
      if(true == MainFormTempValue.detectorArray.at(j,i,0))
      {
        for(int jL=j+1;jL<45;jL++)
        {
          //if(detector[jj][i]==1)
          if(true == MainFormTempValue.detectorArray.at(jL,i,0))
          {
            for(int jArr=j+1;jArr<=jL-1;jArr++)
            {
              //NormDose[jArr*45+i] = NormDose[j*45+i] + (jArr-j)*(NormDose[jL*45+i]-NormDose[j*45+i])/float(jL-j);
              //DoseAbs[jArr*45+i] = DoseAbs[j*45+i] + (jArr-j)*(DoseAbs[jL*45+i]-DoseAbs[j*45+i])/float(jL-j);
              tempValue = matrixData->at(i,j,0) + (jArr-j)*(matrixData->at(i,jArr,0) - matrixData->at(i,j,0))/float(jArr-j);
              matrixData->modifyValue(i,jArr,0,tempValue);
            }
            break;
          }
        }
      }
    }
  }

  dose->sync_finish();

  dose = NULL;
  matrixData = NULL;
}


