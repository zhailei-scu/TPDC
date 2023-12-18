//---------------------------------------------------------------------------
#include "stdio.h"
#include "dose.h"
#include "math.h"
#include "limits.h"
#include "doseshell.h"
#include <fstream>
#include "regexp.h"
#include <string>
#include "LogFrame.h"

using namespace std;

//------------Dose:Constructor:default-------------------
Dose::Dose(){
  this->doseMatrix = NULL;
  this->fileName = "";
  string().swap(this->fileName);
  this->doseUnit = "";
  string().swap(this->doseUnit);
  this->doseCentral.reset();
  this->firstAlignmentCentral.reset();
  this->doseType = -1;
}

//-----------------Dose::Destructor--------------------------
Dose::~Dose(){

  /*Write Lock*/
  this->rwLock.WriteLock();

  TryToDelete< MatrixData<double> >(this->doseMatrix);
  this->doseMatrix = NULL;
  this->fileName = "";
  string().swap(this->fileName);
  this->doseUnit = "";
  string().swap(this->doseUnit);

  this->doseCentral.reset();
  this->firstAlignmentCentral.reset();

  this->doseType = -1;

  this->doseInterploated = false;
  /*Write unLock*/
  this->rwLock.Unlock();
}

//-----------Dose:CopyConstructor------------------------
Dose::Dose(Dose& r){

  /*set a write lock for "this"*/
  this->rwLock.WriteLock();

  this->doseMatrix = NULL;
  this->fileName = "";
  string().swap(this->fileName);
  this->doseUnit = "";
  string().swap(this->doseUnit);

  this->doseCentral.reset();
  this->firstAlignmentCentral.reset();

  this->doseType = -1;

  this->doseInterploated = false;

  if(NULL != &r){

    /*set a read lock for r*/
    r.rwLock.ReadLock();

    if (NULL == r.doseMatrix){
      this->doseMatrix = NULL;
    }
    else{
      this->doseMatrix = new MatrixData<double>();
      *this->doseMatrix = *r.doseMatrix;
    }

    this->fileName = r.fileName;

    this->doseUnit = r.doseUnit;

    this->fileType = r.fileType;

    for(int i=0;i<3;i++){
      this->gridSizes[i] = r.gridSizes[i];
    }

    for(int i=0;i<3;i++){
      this->segments[i] = r.segments[i];
    }

    for(int i=0;i<8;i++){
      this->boundaryPoints[i] = r.boundaryPoints[i];
    }

    this->doseCentral = r.doseCentral;
    this->firstAlignmentCentral = r.firstAlignmentCentral;

    this->doseType = r.doseType;

    this->doseInterploated = r.doseInterploated;

    /*release a read lock for r*/
    r.rwLock.Unlock();
  }

  /*release a write lock for "this"*/
  this->rwLock.Unlock();

}

//----------------Dose::Overload operator--------------------
Dose Dose::operator = (Dose& r){

  /*set a write lock for "this"*/
  this->rwLock.WriteLock();

  TryToDelete< MatrixData<double> >(this->doseMatrix);

  if(NULL == &r){

    this->doseMatrix = NULL;
    this->fileName = "";
    string().swap(this->fileName);
    this->doseUnit = "";
    string().swap(this->doseUnit);

    this->doseType = -1;

    this->doseInterploated = false;

  }else{

    /*set a read lock for r*/
    r.rwLock.ReadLock();

    if (NULL == r.doseMatrix){
      this->doseMatrix = NULL;
    }
    else{
      this->doseMatrix = new MatrixData<double>();
      *this->doseMatrix = *r.doseMatrix;
    }

    this->fileName = r.fileName;

    this->doseUnit = r.doseUnit;

    this->fileType = r.fileType;

    for(int i=0;i<3;i++){
      this->gridSizes[i] = r.gridSizes[i];
    }

    for(int i=0;i<3;i++){
      this->segments[i] = r.segments[i];
    }

    for(int i=0;i<8;i++){
      this->boundaryPoints[i] = r.boundaryPoints[i];
    }

    this->doseCentral = r.doseCentral;
    this->firstAlignmentCentral = r.firstAlignmentCentral;

    this->doseType = r.doseType;

    this->doseInterploated = r.doseInterploated;

    /*release a read lock for r*/
    r.rwLock.Unlock();
  }

  /*release a write lock for "this"*/
  this->rwLock.Unlock();

  return *this;
}

//-----------------Dose::Set and Get: read/write unSafe----------------------
void Dose::unSync_setDoseMatrix( MatrixData<double>* _doseMatrix){

  TryToDelete<MatrixData<double> >(this->doseMatrix);
  if(NULL==_doseMatrix){
    this->doseMatrix = NULL;
  }else{
    this->doseMatrix = new MatrixData<double>();
    *this->doseMatrix = *_doseMatrix;
  }
}

MatrixData<double> Dose::unSync_copyDoseMatrix()throw(const char*){

  MatrixData<double> result;
  if(NULL == this->doseMatrix){
    RunningLog::writeLog("The doseMatrix is NULL" + __LINE__);
  }

  result = *this->doseMatrix;

  return result;
}

void Dose::unSync_allocateMatrix(int _rows,int _cols,int _heights){
  TryToDelete<MatrixData<double> >(this->doseMatrix);
  this->doseMatrix = new MatrixData<double>(_rows,_cols,_heights);
}

void Dose::unSync_clearnMatrix(){
  TryToDelete<MatrixData<double> >(this->doseMatrix);
  this->doseMatrix = NULL;
}

string Dose::unSync_getFileName(){
  return this->fileName;
}
void Dose::unSync_setFileName(string fileName){
  this->fileName = fileName;
}

FILETYPE Dose::unSync_getFileType(){
  return this->fileType;
}

void Dose::unSync_setFileType(FILETYPE fileType){
  this->fileType = fileType;
}

string Dose::unSync_getDoseUnit(){
  return this->doseUnit;
}

void Dose::unSync_setDoseUnit(string doseUnit){
  this->doseUnit = doseUnit;
}

void Dose::unSync_copyGridSizes(double resultGridSizes[3]){

  for(int i=0;i<3;i++){
    resultGridSizes[i] = this->gridSizes[i];
  }
}

void Dose::unSync_setGridSizes(double gridSize[3]){

  for(int i=0;i<3;i++){
    this->gridSizes[i] = gridSize[i];
  }

}

void Dose::unSync_upDateGridSizes(double gridSize[3]){
  double floatVerbStand = 0.02;

  for(int i=0;i<3;i++){
    this->gridSizes[i] = gridSize[i];
  }

   /*Segments*/
  for(int i=0;i<2;i++){
    this->segments[i] = getGridSegments(this->gridSizes[i]);
  }

  /*dose physic center*/
  if(NULL != this->getDoseMatrix()){
    this->doseCentral.x = (this->doseMatrix->getRowLength()-1)*this->gridSizes[0]/2.0;
    this->doseCentral.y = (this->doseMatrix->getColLength()-1)*this->gridSizes[1]/2.0;
  }

  //first alignment central
  //first alignment central
  if(this->fileType != FILETYPE(DICOMCalcFileType)){
    this->firstAlignmentCentral.row = TrimFloat_Down(this->doseCentral.x/this->gridSizes[0],floatVerbStand);
    this->firstAlignmentCentral.col = TrimFloat_Down(this->doseCentral.y/this->gridSizes[1],floatVerbStand);
  }

}

void Dose::unSync_copySegments(int resultSegments[3]){
  for(int i=0;i<3;i++){
    resultSegments[i] = this->segments[i];
  }
}
void Dose::unSync_setSegments(int _segments[3]){
  for(int i=0;i<3;i++){
    this->segments[i] = _segments[i];
  }
}

PhysicalPoint* Dose::getDoseCentral(){
  return &(this->doseCentral);
}
void Dose::unSync_setDoseCentral(PhysicalPoint doseCentral){
  this->doseCentral = doseCentral;
}

GridPoint* Dose::getFirstAlignmentCentral(){
  return &(this->firstAlignmentCentral);
}
void Dose::unSync_setFirstAlignmentCentral(GridPoint firstAlignmentCentral){
  this->firstAlignmentCentral = firstAlignmentCentral;
}

void Dose::unSync_copyBoundaryPoints(GridPoint resultBoundaryPoints[8]){

  for(int i=0;i<8;i++){
    resultBoundaryPoints[i] = this->boundaryPoints[i];
  }
}

void Dose::unSync_setBoundaryPoints(GridPoint boundaryPoints[8]){
  for(int i=0;i<8;i++){
    this->boundaryPoints[i] = boundaryPoints[i];
  }
}


DoseType Dose::unSync_getDoseType(){       //Only get method
  return this->doseType;
}

bool Dose::unSync_getDoseInterploated(){   //Only get method
  return this->doseInterploated;
}

//-----------------Dose::Set and Get: read/write safe----------------------
/*Get and Set*/
MatrixData<double>* Dose::getDoseMatrix(){
  return this->doseMatrix;
}

void Dose::sync_setDoseMatrix( MatrixData<double>* _doseMatrix){
  /*set a writer lock for "this"*/
  this->rwLock.WriteLock();

  this->unSync_setDoseMatrix(_doseMatrix);

  /*release a writer lock for "this"*/
  this->rwLock.Unlock();
}

MatrixData<double> Dose::sync_copyDoseMatrix()throw(const char*){
  /*set a reader lock for "this"*/
  this->rwLock.ReadLock();

  MatrixData<double> result;

  result = this->unSync_copyDoseMatrix();

  /*release a reader lock for "this"*/
  this->rwLock.Unlock();

  return result;
}

void Dose::sync_allocateMatrix(int _rows,int _cols,int _heights){
  /*set a writer lock for "this"*/
  this->rwLock.WriteLock();

  this->unSync_allocateMatrix(_rows,_cols,_heights);

  /*release a writer lock for "this"*/
  this->rwLock.Unlock();
}

void Dose::sync_clearnMatrix(){
  /*set a writer lock for "this"*/
  this->rwLock.WriteLock();

  this->unSync_clearnMatrix();

  /*release a writer lock for "this"*/
  this->rwLock.Unlock();
}

string Dose::sync_getFileName(){
  /*set a reader lock for "this"*/
  this->rwLock.ReadLock();

  string result = this->unSync_getFileName();

  /*release a reader lock for "this"*/
  this->rwLock.Unlock();

  return result;
}

void Dose::sync_setFileName(string fileName){
  /*set a writer lock for "this"*/
  this->rwLock.WriteLock();

  this->unSync_setFileName(fileName);

   /*release a writer lock for "this"*/
  this->rwLock.Unlock();
}

FILETYPE Dose::sync_getFileType(){
  /*set a reader lock for "this"*/
  this->rwLock.ReadLock();

  FILETYPE result = this->unSync_getFileType();

  /*release a reader lock for "this"*/
  this->rwLock.Unlock();

  return result;
}

void Dose::sync_setFileType(FILETYPE fileType){
  /*set a writer lock for "this"*/
  this->rwLock.WriteLock();

  this->unSync_setFileType(fileType);

  /*release a writer lock for "this"*/
  this->rwLock.Unlock();
}

string Dose::sync_getDoseUnit(){
  /*set a reader lock for "this"*/
  this->rwLock.ReadLock();

  string result =  this->unSync_getDoseUnit();

  /*release a reader locker for "this"*/
  this->rwLock.Unlock();

  return result;
}

void Dose::sync_setDoseUnit(string doseUnit){
  /*set a writer lock for "this"*/
  this->rwLock.WriteLock();

  this->unSync_setDoseUnit(doseUnit);

  /*release a writer lock for "this"*/
  this->rwLock.Unlock();
}

double* Dose::getGridSizes(){
  return this->gridSizes;
}


void Dose::sync_copyGridSizes(double resultGridSizes[3]){
  /*set a reader lock for "this"*/
  this->rwLock.ReadLock();

  this->unSync_copyGridSizes(resultGridSizes);

  /*release a reader locker for "this"*/
  this->rwLock.Unlock();
}

void Dose::sync_setGridSizes(double gridSizes[3]){
  /*set a writer lock for "this"*/
  this->rwLock.WriteLock();

  this->unSync_setGridSizes(gridSizes);

  /*release a writer lock for "this"*/
  this->rwLock.Unlock();
}

void Dose::sync_upDateGridSizes(double gridSizes[3]){
   /*set a writer lock for "this"*/
  this->rwLock.WriteLock();

  this->unSync_upDateGridSizes(gridSizes);

  /*release a writer lock for "this"*/
  this->rwLock.Unlock();
}


int* Dose::getSegments(){
  return this->segments;
}
void Dose::sync_copySegments(int resultSegments[3]){
  /*set a reader lock for "this"*/
  this->rwLock.ReadLock();

  this->unSync_copySegments(resultSegments);

  /*release a reader locker for "this"*/
  this->rwLock.Unlock();
}
void Dose::sync_setSegments(int segments[3]){
  /*set a writer lock for "this"*/
  this->rwLock.WriteLock();

  this->unSync_setSegments(segments);

  /*release a writer lock for "this"*/
  this->rwLock.Unlock();
}

void Dose::sync_setDoseCentral(PhysicalPoint doseCentral){
  /*set a writer lock for "this"*/
  this->rwLock.WriteLock();

  this->unSync_setDoseCentral(doseCentral);

  /*release a writer lock for "this"*/
  this->rwLock.Unlock();
}


void Dose::sync_setFirstAlignmentCentral(GridPoint firstAlignmentCentral){
  /*set a writer lock for "this"*/
  this->rwLock.WriteLock();

  this->unSync_setFirstAlignmentCentral(firstAlignmentCentral);

  /*release a writer lock for "this"*/
  this->rwLock.Unlock();
}

GridPoint* Dose::getBoundaryPoints(){
  return this->boundaryPoints;
}

void Dose::sync_copyBoundaryPoints(GridPoint resultBoundaryPoints[8]){
  /*set a reader lock for "this"*/
  this->rwLock.ReadLock();

  for(int i=0;i<8;i++){
    resultBoundaryPoints[i] = this->boundaryPoints[i];
  }

  /*release a reader locker for "this"*/
  this->rwLock.Unlock();
}
void Dose::sync_setBoundaryPoints(GridPoint boundaryPoints[8]){
  /*set a writer lock for "this"*/
  this->rwLock.WriteLock();

  this->unSync_setBoundaryPoints(boundaryPoints);

  /*release a writer lock for "this"*/
  this->rwLock.Unlock();
}

DoseType Dose::sync_getDoseType(){     //Only get method
  DoseType result = -1;

  /*set a reader lock for "this"*/
  this->rwLock.ReadLock();

  result =  this->unSync_getDoseType();

  /*release a reader locker for "this"*/
  this->rwLock.Unlock();

  return result;
}

bool Dose::sync_getDoseInterploated(){   //Only get method
  bool result = false;

  /*set a reader lock for "this"*/
  this->rwLock.ReadLock();
  
  result = this->unSync_getDoseInterploated();

  /*release a reader locker for "this"*/
  this->rwLock.Unlock();

  return result;
}


void Dose::sync_Read_Start(){
  /*set a reader lock for "this"*/
  this->rwLock.ReadLock();
}

void Dose::sync_Write_Start(){
  /*set a reader lock for "this"*/
  this->rwLock.ReadLock();
}

void Dose::sync_finish(){
  /*release a reader/writer locker for "this"*/
  this->rwLock.Unlock();
}

//--------------------Dose::Functions,public------------------------
bool Dose::loadDoseFile(string fileName,FILETYPE fileType)throw (const char*){
  bool result = false;
  if(fileName.empty() || 0==fileName.length()){
    RunningLog::writeLog("The input file can not be NULL",__LINE__);
    return result;
  }
  if(0==fileType){
    RunningLog::writeLog("The type of input file are unspecial", __LINE__);
    return result;
  }

  this->sync_setFileName(fileName);
  this->sync_setFileType(fileType);
  result = loadDoseFile();

  return result;
}

/*Overload*/
bool Dose::loadDoseFile()throw (const char*){
  bool result = false;
  if(0==this->fileName.length()){
    RunningLog::writeLog("The input file can not be NULL" , __LINE__);
    return false;
  }
  if(0==this->fileType){
    RunningLog::writeLog("The type of input file are unspecial" , __LINE__);
    return false;
  }

  switch(this->fileType)
  {
    case FILETYPE(ZCMeasureFileType):
    {
      result = loadZCMeasureFile();
    }
    break;

    case FILETYPE(MapCHECKMeasureFileType):
    {
      result = loadMapCHECKMeasureFile();
    }
    break;

    case FILETYPE(MatrixMeasureFileType):
    {
      result = loadMatrixMeasureDoseFile();
    }
    break;

    case FILETYPE(DICOMCalcFileType):
    {
      result = loadDICOMCalcFile();
    }
    break;

    case FILETYPE(SCUCalcFileType):
    {
      result = loadSCUCalcFile();
    }
    break;

    default:
    {
      result =  false;
    }
    break;
  }

  return result;
}


bool Dose::SaveDose(){

  // TODO

  return true;
}

//------------------Dose::Function,private-------------------------
/*read measurement file*/
bool Dose::loadMapCHECKMeasureFile()throw (const char*){
  MatrixData<double>* tempDoseMatrix = NULL;

  double floatVerbStand = 0.02;
  bool specialExpExists = false;
  
  double dosePerCount = 0.0000000;

  int match_Result = 0;   //indicated matching results
  size_t length = 0;     //get the matching chars length
  size_t position = 0;   //begining of the matching position in each line
                         //row number,if finding more,error
  int rows = -1;        //row number
  int cols = -1;        //col number
  int heights = 0;

  int lineCount = 0;  //count the lines in files

  double tempDoseCentralX,tempDoseCentralY;

  int cax_x = 23;
  int cax_y = 23;

  string tempStr;
  double tempDoseValue;

  ifstream in;
  in.open(this->fileName.c_str(),ios::in);   //std::ios
  if(!in.is_open()){
    RunningLog::writeLog("Failed to get file stream",__LINE__);
    return false;
  }

  TRegexp exp_CheckFile("^1175 MapCHECK");
  TRegexp exp_Factor("^Dose per Count:");
  TRegexp exp_Rows("^Rows:");     //match the number of rows in the file iostream
  TRegexp exp_Cols("^Cols:");     //match the number of cols in the file iostream
  TRegexp exp_CAX_X("CAX X:");
  TRegexp exp_CAX_Y("CAX Y:");
  //TRegexp exp_DataLabel("^Dose Interpolated");
  TRegexp exp_DataLabelCorrectedCounts("^Corrected Counts");  //match the corrected dose and which is our interested dose
  TRegexp exp_DataLabelInterpolatedDose("^Dose Interpolated");

  //initial
  this->doseType = DoseType(DOSE_ABSOLUTE);
  this->doseInterploated = false;

  specialExpExists = false;
  while(getline(in,tempStr)){    //std::getline()
    lineCount++;

    if(exp_CheckFile.find(tempStr.begin(),&length,position) != -1){
      specialExpExists = true;
      break;
    }
  }
  if(lineCount>10 || specialExpExists ==false){
      in.close();
      tempDoseMatrix = NULL;
      return false;
  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin

  while(getline(in,tempStr)){    //std::getline()
    if( (match_Result=exp_Factor.find(tempStr.begin(),&length,position)) != -1){
      tempStr = tempStr.substr(match_Result+length,tempStr.length());
      dosePerCount = atof(trimStringFrontAndBack(tempStr).c_str());
      break;
    }
  }
  if(dosePerCount>=0.000001){
    this->doseType = DoseType(DOSE_ABSOLUTE);
  }else{
    this->doseType = DoseType(DOSE_RELATIVE);
  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin

  specialExpExists = false;
  while(getline(in,tempStr)){    //std::getline()

    if( (match_Result=exp_Rows.find(tempStr.begin(),&length,position)) != -1){  //found sign of "Rows:"

      if(length<1000){
        tempStr = tempStr.substr(match_Result+length,tempStr.length());
        rows = atoi(trimStringFrontAndBack(tempStr).c_str());
        specialExpExists = true;
      }
      break;
    }

  }
  if(specialExpExists ==false){
    RunningLog::writeLog("Rows number not existed,the MapCHECK file map be not standard or integal" + __LINE__);
    in.close();
    tempDoseMatrix = NULL;
    return false;
  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin


  specialExpExists = false;
  while(getline(in,tempStr)){    //std::getline()

    if( (match_Result=exp_Cols.find(tempStr.begin(),&length,position)) != -1){  //found sign of "Cols:"

      if(length<1000){
        tempStr = tempStr.substr(match_Result+length,tempStr.length());
        cols = atoi(trimStringFrontAndBack(tempStr).c_str());
        specialExpExists = true;
      }
      break;
    }

  }
  if(specialExpExists ==false){
    RunningLog::writeLog("Cols number not existed,the MapCHECK file map be not standard or integal" + __LINE__);
    in.close();
    tempDoseMatrix = NULL;
    return false;
  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin


  while(getline(in,tempStr)){    //std::getline()

    if( (match_Result=exp_CAX_X.find(tempStr.begin(),&length,position)) != -1){  //found sign of "CAX X:"

      if(length<1000){
        tempStr = tempStr.substr(match_Result+length,tempStr.length());
        cax_x = atoi(trimStringFrontAndBack(tempStr).c_str());
      }
      break;
    }

  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin

  while(getline(in,tempStr)){    //std::getline()

    if( (match_Result=exp_CAX_Y.find(tempStr.begin(),&length,position)) != -1){  //found sign of "CAX Y:"

      if(length<1000){
        tempStr = tempStr.substr(match_Result+length,tempStr.length());
        cax_y = atoi(trimStringFrontAndBack(tempStr).c_str());
      }
      break;
    }

  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin

  
  heights = 1;


  if(rows*cols*heights<=0){
    RunningLog::writeLog("There are no dose data in this file" + __LINE__);
    return false;
  }
  /*Set the eight boundary points*/
  GridPoint boundary[8];

  boundary[0].row = 0;
  boundary[0].col = 0;
  boundary[0].level = 0;

  boundary[1].row = 0;
  boundary[1].col = cols-1;
  boundary[1].level = 0;

  boundary[2].row = rows-1;
  boundary[2].col = 0;
  boundary[2].level = 0;

  boundary[3].row = rows-1;
  boundary[3].col = cols-1;
  boundary[3].level = 0;

  boundary[4].row = 0;
  boundary[4].col = 0;
  boundary[4].level = heights - 1;

  boundary[5].row = 0;
  boundary[5].col = cols-1;
  boundary[5].level = heights - 1;

  boundary[6].row = rows-1;
  boundary[6].col = 0;
  boundary[6].level = heights - 1;

  boundary[7].row = rows-1;
  boundary[7].col = cols-1;
  boundary[7].level = heights - 1;

  this->sync_setBoundaryPoints(boundary);

  /*GridSizes*/
  this->gridSizes[0] = 5.0;
  this->gridSizes[1] = 5.0;

  /*Segments*/
  for(int i=0;i<2;i++){
    this->segments[i] = getGridSegments(this->gridSizes[i]);
  }

  /*dose physic center*/
  tempDoseCentralX = (cax_x-1)*this->gridSizes[0] + MainFormTempValue.operator_measureDoseCentral.x;
  tempDoseCentralY = (cax_y-1)*this->gridSizes[1] + MainFormTempValue.operator_measureDoseCentral.y;

  if(tempDoseCentralX<0 || tempDoseCentralX>((rows-1)*this->gridSizes[0])){

    RunningLog::writeLog("The cax x is out of boundary",__LINE__);
    return false;
  }
  if(tempDoseCentralY<0 || tempDoseCentralY>((cols-1)*this->gridSizes[1])){

    RunningLog::writeLog("The cax y is out of boundary",__LINE__);
    return false;
  }
  this->doseCentral.x = tempDoseCentralX;
  this->doseCentral.y = tempDoseCentralY;

  //first alignment central
  //first alignment central
  this->firstAlignmentCentral.row = TrimFloat_Down(this->doseCentral.x/this->gridSizes[0],floatVerbStand);
  this->firstAlignmentCentral.col = TrimFloat_Down(this->doseCentral.y/this->gridSizes[1],floatVerbStand);


  /*Read data*/
  this->unSync_allocateMatrix(rows,cols,heights);
  tempDoseMatrix = this->getDoseMatrix();

  specialExpExists = false;
  while(getline(in,tempStr)){    //std::getline()

    if(exp_DataLabelInterpolatedDose.find(tempStr.begin(),&length,position) != -1){
      specialExpExists = true;
      this->doseInterploated = true;
      getline(in,tempStr);   //a invalid string"Ycm ROW"

       for(int j=0;j<cols;j++){

          in>>tempDoseValue;     //two invalid numbers
          in>>tempDoseValue;

          for(int i=0;i<rows;i++){
             in>>tempDoseValue;
             tempDoseMatrix->modifyValue(i,cols-1-j,0,tempDoseValue);
             //tempDoseMatrix->modifyValue(i,j,0,tempDoseValue);
          }
       }

       break;  //finish the dose reading
    }
  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin


  if(false == specialExpExists){

    while(getline(in,tempStr)){

      if(exp_DataLabelCorrectedCounts.find(tempStr.begin(),&length,position) != -1){

         getline(in,tempStr);   //a invalid string"Ycm ROW"

         if(DoseType(DOSE_RELATIVE) == this->doseType){    //relative dose
           for(int j=0;j<cols;j++){

             in>>tempDoseValue;     //two invalid numbers
             in>>tempDoseValue;

             for(int i=0;i<rows;i++){
               in>>tempDoseValue;
               tempDoseMatrix->modifyValue(i,cols-1-j,0,tempDoseValue);
               //tempDoseMatrix->modifyValue(i,j,0,tempDoseValue);
             }
           }

         }else if(DoseType(DOSE_ABSOLUTE) == this->doseType){   //abs dose

           for(int j=0;j<cols;j++){

             in>>tempDoseValue;     //two invalid numbers
             in>>tempDoseValue;

             for(int i=0;i<rows;i++){
               in>>tempDoseValue;
               //tempDoseValue = tempDoseValue*dosePerCount;
               tempDoseMatrix->modifyValue(i,cols-1-j,0,tempDoseValue);
               tempDoseMatrix->modifyValue(i,j,0,tempDoseValue);
             }
           }
         }


         break;  //finish the dose reading
      }

    }
  }


  in.close();

  tempDoseMatrix = NULL;

  return true;
}

bool Dose::loadZCMeasureFile()throw (const char*){

  int rows = 40;
  int cols = 40;
  int heights = 1;
  double* tempDoseArray = NULL;
  MatrixData<double>* tempDoseMatrix = NULL;
  double *ptr = NULL;
  double floatVerbStand = 0.02;

  double maxDose = -DBL_MAX;
  double minDose = DBL_MAX;

  double tempDoseCentralX,tempDoseCentralY;

  FILE *fp=fopen(this->fileName.c_str(),"r");
  if(NULL==fp)
  {
    RunningLog::writeLog("read file error" , __LINE__);
    return false;
  }

  if(rows*cols*heights<=0){
    RunningLog::writeLog("There are no dose data in this file" , __LINE__);
    return false;
  }

  this->doseType = DoseType(DOSE_ABSOLUTE);

  this->doseInterploated = false;


  /*Set the eight boundary points*/
  GridPoint boundary[8];

  boundary[0].row = 0;
  boundary[0].col = 0;
  boundary[0].level = 0;

  boundary[1].row = 0;
  boundary[1].col = cols-1;
  boundary[1].level = 0;

  boundary[2].row = rows-1;
  boundary[2].col = 0;
  boundary[2].level = 0;

  boundary[3].row = rows-1;
  boundary[3].col = cols-1;
  boundary[3].level = 0;

  boundary[4].row = 0;
  boundary[4].col = 0;
  boundary[4].level = heights - 1;

  boundary[5].row = 0;
  boundary[5].col = cols-1;
  boundary[5].level = heights - 1;

  boundary[6].row = rows-1;
  boundary[6].col = 0;
  boundary[6].level = heights - 1;

  boundary[7].row = rows-1;
  boundary[7].col = cols-1;
  boundary[7].level = heights - 1;
  this->sync_setBoundaryPoints(boundary);

  /*Set gridSizes*/
  this->gridSizes[0] = 7.2;
  this->gridSizes[1] = 7.2;

  /*Segments*/
  for(int i=0;i<2;i++){
    this->segments[i] = getGridSegments(this->gridSizes[i]);
  }

  /*dose physic center*/
  tempDoseCentralX = (rows-1)*this->gridSizes[0]/2.0 + MainFormTempValue.operator_measureDoseCentral.x;
  tempDoseCentralY = (cols-1)*this->gridSizes[1]/2.0 + MainFormTempValue.operator_measureDoseCentral.y;

  if(tempDoseCentralX<0 || tempDoseCentralX>((rows-1)*this->gridSizes[0])){

    RunningLog::writeLog("The cax x is out of boundary",__LINE__);
    return false;
  }
  if(tempDoseCentralY<0 || tempDoseCentralY>((cols-1)*this->gridSizes[1])){

    RunningLog::writeLog("The cax y is out of boundary",__LINE__);
    return false;
  }
  this->doseCentral.x = tempDoseCentralX;
  this->doseCentral.y = tempDoseCentralY;


  //first alignment central
  this->firstAlignmentCentral.row = TrimFloat_Down(this->doseCentral.x/this->gridSizes[0],floatVerbStand);
  this->firstAlignmentCentral.col = TrimFloat_Down(this->doseCentral.y/this->gridSizes[1],floatVerbStand);

  //read data
  tempDoseArray = new double[rows*cols*heights];
  ptr = tempDoseArray;

  for(int k=0;k<heights;k++)
  {
    //fscanf(fp,"%f",&zNo);
    for(int j=0;j<cols;j++)
    {
      for(int i=0;i<rows;i++)
      {
        fscanf(fp,"%lf",ptr);

        fscanf(fp,",",NULL); //中测数据中有个","号
        ptr++;
      }
    }
  }

  tempDoseMatrix = new MatrixData<double>();
  tempDoseMatrix->setData(rows,cols,heights,tempDoseArray);

  this->sync_setDoseMatrix(tempDoseMatrix);

  fclose(fp);

  TryToDeleteArray<double>(tempDoseArray);
  tempDoseArray = NULL;

  TryToDelete<MatrixData<double> >(tempDoseMatrix);
  tempDoseMatrix = NULL;

  ptr = NULL;

  return true;
}

bool Dose::loadMatrixMeasureDoseFile()throw (const char*){
  MatrixData<double>* tempDoseMatrix = NULL;
  double floatVerbStand = 0.02;

  double *xPos = NULL;
  double *yPos = NULL;

  ostringstream os;
  os.str("");
  
  ifstream in;
  in.open(this->fileName.c_str(),ios::in);   //std::ios
  if(!in.is_open()){
    RunningLog::writeLog("Failed to get file stream",__LINE__);
    return false;
  }

  //1
  TRegexp exp_CheckFileHead("^<opimrtascii>");                                              //necessary
  //2
  TRegexp exp_CheckFileBody("^<asciiheader>");                                               //necessary
  //3
  TRegexp exp_Separator("^Separator:");    //define the spearator between datas              //Opt,default: [Tab]
  string separator = "[TAB]";
  //4
  TRegexp exp_DataType("^Data Type:");
  DoseType doseType = DoseType(DOSE_RELATIVE);
  //5
  TRegexp exp_DataFactor("^Data Factor:"); //data factor: result = value*Data Factor         //Opt,default: 1.0
  double dataFactor = 1.0;
  //6
  TRegexp exp_Unit("^Data Unit:");         //dose unit                                       //Opt, Gy(abs),1/10%(relative)
  string doseUnit = "Gy";
  double doseUnitTransMulti = 100;    //Gy->cGy:100  mGy->cGy:0.1 uGy->cGy:0.0001 
  //7
  TRegexp exp_LengthUnit("^Length Unit:"); //Length unit                                     //Opt: default:mm
  string lengthUnit = "mm";
  double lengthUnitTransMulti = 1;  //um->mm:0.1 cm->mm:10  m->mm:100
  //8
  TRegexp exp_Plan("^Plane:");             //plan                                            //Opt: default XY
  string plan = "XY";
  //9
  TRegexp exp_Cols1("^No. of Columns:");     //match the number of cols in the file iostream //necessary
  TRegexp exp_Cols2("^Columns:");                                                             //or
  //10
  TRegexp exp_Rows1("^No. of Rows:");     //match the number of rowss in the file iostream   //necessary
  TRegexp exp_Rows2("^Rows:");                                                               //or
  //11
  TRegexp exp_Spaceing("Spacing:");     //match the number of rowss in the file iostream   //Opt: default:defind by X[mm],Y[mm] or 1mm
  double _gridSize[3];
  GridPoint boundary[8];

  int match_Result = 0;   //indicated matching results
  size_t length = 0;     //get the matching chars length
  size_t position = 0;   //begining of the matching position in each line
  char rowsNum[10];      //to store the matched chars(the number of the rows)
  char colsNum[10];      //to store the matched chars(the number of the cols)
  int verify = 0;        //a sign to verify the potential error while the process of matching:we can only get one col number and one
                         //row number,if finding more,error
  int rows = -1;        //row number
  int cols = -1;        //col number
  int heights = -1;
  double tempDoseCentralX,tempDoseCentralY; 

  bool status = false;

  //Initial
  this->doseType = DoseType(DOSE_ABSOLUTE);
  this->doseInterploated = false;


  //some temp values
  string spaceForSeparator;
  bool space = false;
  bool voidSplit = false;
  bool labX = false;
  bool labY = false;
  string invalidStr;
  string xLabel,yLabel;
  int tempStrPos;
  string tempStr;
  double tempInvalued;
  double tempReadValue;

  //1
  status = false;
  while(!in.eof()){
    getline(in,tempStr);
    if(exp_CheckFileHead.find(tempStr.begin(),&length,position)!=-1){
      status = true;
      break;
    }
  }
  if(false == status){
    in.close();
    tempDoseMatrix = NULL;
    return false;
  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin

  //2
  status = false;
  while(!in.eof()){
    getline(in,tempStr);
    if(exp_CheckFileBody.find(tempStr.begin(),&length,position)!=-1){
      status = true;
      break;
    }
  }
  if(false == status){
    in.close();
    tempDoseMatrix = NULL;
    return false;
  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin 

  //3
  while(!in.eof()){
    getline(in,tempStr);
    if( (match_Result=exp_Separator.find(tempStr.begin(),&length,position))!=-1){   //opt is setted

      if(length<1000){
        tempStr = tempStr.substr(match_Result+length,tempStr.length());
        separator = "";
        separator = trimStringFrontAndBack(tempStr);
      }
      break;
    }

  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin

   //4
  while(!in.eof()){
    getline(in,tempStr);
    if( (match_Result=exp_DataType.find(tempStr.begin(),&length,position))!=-1){   //opt is setted

      if(length<1000){
        tempStr = tempStr.substr(match_Result+length,tempStr.length());
        tempStr = trimStringFrontAndBack(tempStr);
        if(true == strHeadAgreeWithCompareStr(tempStr,"Abs. Dose")
          || true == strHeadAgreeWithCompareStr(tempStr,"Absolute") ){
          this->doseType = DoseType(DOSE_ABSOLUTE);
        }else if(true == strHeadAgreeWithCompareStr(tempStr,"Rel. Dose")
          || true == strHeadAgreeWithCompareStr(tempStr,"Relative") ){
          this->doseType = DoseType(DOSE_RELATIVE);
        }

      }
      break;
    }

  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin

  //5
  while(!in.eof()){
    getline(in,tempStr);
    if( (match_Result=exp_DataFactor.find(tempStr.begin(),&length,position))!=-1){   //opt is setted

      tempStr = tempStr.substr(match_Result+length,tempStr.length());
      dataFactor = atof(trimStringFrontAndBack(tempStr).c_str());

      break;
    }

  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin

  //6
  while(!in.eof()){
    getline(in,tempStr);
    if( (match_Result=exp_Unit.find(tempStr.begin(),&length,position))!=-1){   //opt is setted
      tempStr = tempStr.substr(match_Result+length,tempStr.length());
      doseUnit = trimStringFrontAndBack(tempStr);

      break;
    }

  }
  if(DoseType(DOSE_ABSOLUTE) == this->doseType){
    if(true==strHeadAgreeWithCompareStr(doseUnit,"cGy")){
      doseUnitTransMulti = 1;
    }else if(true==strHeadAgreeWithCompareStr(doseUnit,"mGy")){
      doseUnitTransMulti = 0.1;
    }else if(true==strHeadAgreeWithCompareStr(doseUnit,"uGy")){
      doseUnitTransMulti = 0.0001;
    }else if(true==strHeadAgreeWithCompareStr(doseUnit,"Gy")){
      doseUnitTransMulti = 100;
    }

    if(true==strHeadAgreeWithCompareStr(doseUnit,"1/10%")){  //not compatible
      in.close();
      tempDoseMatrix = NULL;
      return false;
    }
    
  }else if(DoseType(DOSE_RELATIVE) == this->doseType){
    doseUnitTransMulti = 1.0;
  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin

  //7
  while(!in.eof()){
    getline(in,tempStr);
    if( (match_Result=exp_LengthUnit.find(tempStr.begin(),&length,position))!=-1){   //opt is setted
      tempStr = tempStr.substr(match_Result+length,tempStr.length());
      lengthUnit = trimStringFrontAndBack(tempStr);
      break;
    }

  }
  if(true==strHeadAgreeWithCompareStr(lengthUnit,"mm")){
    lengthUnitTransMulti = 1;
  }else if(true==strHeadAgreeWithCompareStr(lengthUnit,"um")){
    lengthUnitTransMulti = 0.100;
  }else if(true==strHeadAgreeWithCompareStr(lengthUnit,"cm")){
    lengthUnitTransMulti = 10;
  }else if(true==strHeadAgreeWithCompareStr(lengthUnit,"dm")){
    lengthUnitTransMulti = 100;
  }else if(true==strHeadAgreeWithCompareStr(lengthUnit,"m")){
    lengthUnitTransMulti = 1000;
  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin


  //8
  while(!in.eof()){
    getline(in,tempStr);
    if( (match_Result=exp_Plan.find(tempStr.begin(),&length,position))!=-1){   //opt is setted
      tempStr = tempStr.substr(match_Result+length,tempStr.length());
      plan = trimStringFrontAndBack(tempStr);


      if(plan.length()!=2){
        in.close();
        tempDoseMatrix = NULL;
        return false;
      }
      break;
    }


  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin

  //9
  status = false;
  while(!in.eof()){
    getline(in,tempStr);
    if( (match_Result=exp_Cols1.find(tempStr.begin(),&length,position))!=-1 ||
       (match_Result=exp_Cols2.find(tempStr.begin(),&length,position))!=-1){   //opt is setted
        tempStr = tempStr.substr(match_Result+length,tempStr.length());
        cols = atoi(trimStringFrontAndBack(tempStr).c_str());

        status = true;
        break;
    }
  }
  if(false == status){
    in.close();
    tempDoseMatrix = NULL;
    return false;
  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin

  //10
  status = false;
  while(!in.eof()){
    getline(in,tempStr);
    if( (match_Result=exp_Rows1.find(tempStr.begin(),&length,position))!=-1 ||
       (match_Result=exp_Rows2.find(tempStr.begin(),&length,position))!=-1){   //opt is setted
        tempStr = tempStr.substr(match_Result+length,tempStr.length());
        rows = atoi(trimStringFrontAndBack(tempStr).c_str());

        status = true;
        break;

    }
  }
  if(false == status){
    in.close();
    tempDoseMatrix = NULL;
    return false;
  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin


  //11
  while(!in.eof()){
    getline(in,tempStr);
    if( (match_Result=exp_Spaceing.find(tempStr.begin(),&length,position))!=-1){   //opt is setted

      tempStr = tempStr.substr(match_Result+length,tempStr.length());

      if(length<1000){
        _gridSize[0] = lengthUnitTransMulti*atof(trimStringFrontAndBack(tempStr).c_str());
        _gridSize[1] = lengthUnitTransMulti*atof(trimStringFrontAndBack(tempStr).c_str());
        _gridSize[2] = -1;
      }

      space = true;
      break;
    }

  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin

  if(separator == "[TAB]" || separator == "[CR]" || separator == "[LF]" || separator == "[CR][LF]"){
    voidSplit = true;
  }else{
    voidSplit = false;
  }

  /*
  string spaceForSeparator;
  //11
  bool labX = false;
  os.str("");
  os<<plan.at(0)<<"["<<lengthUnit<<"]";
  string xLabel = os.str();                                 //match the X grid         //Opt: defined by "Plan"
  double posX1=0.0,posX2=0.0;
  int findPos;
  while(!in.eof()){
    getline(in,tempStr);
    if( true == strHeadAgreeWithCompareStr(trimStringFront(tempStr),xLabel)){   //opt is setted
      tempStr = tempStr.substr(xLabel.length(),tempStr.length());
      tempStr = trimStringFrontAndBack(tempStr);

      if(true==voidSplit){
        findPos = tempStr.find_first_of(" ");

        if(findPos>0){
          posX1 = atof(tempStr.substr(0,findPos).c_str());
          tempStr = trimStringFrontAndBack(tempStr.substr(findPos,tempStr.length()));
        }else if(findPos==0){
          RunningLog::writeLog("trim function get an error",__LINE__);
          return false;
        }else{
          RunningLog::writeLog("Too few parameters",__LINE__);
          return false;
        }

        findPos = tempStr.find_first_of(" ");

        if(findPos>0){
          posX2 = atof(tempStr.substr(0,findPos).c_str());
        }else if(findPos==0){
          RunningLog::writeLog("trim function get an error",__LINE__);
          return false;
        }else{
          posX2 = atof(tempStr.c_str());
        }


      }else{
        findPos = tempStr.find_first_of(" ");

        if(findPos>0){
          tempStr = trimStringFrontAndBack(tempStr.substr(findPos,tempStr.length()));
        }else if(findPos==0){
          RunningLog::writeLog("trim function get an error",__LINE__);
          return false;
        }else{
          RunningLog::writeLog("Too few parameters",__LINE__);
          return false;
        }

        findPos = tempStr.find_first_of(" ");

        if(findPos>0){
          posX1 = atof(tempStr.substr(0,findPos).c_str());
          tempStr = trimStringFrontAndBack(tempStr.substr(findPos,tempStr.length()));
        }else if(findPos==0){
          RunningLog::writeLog("trim function get an error",__LINE__);
          return false;
        }else{
          RunningLog::writeLog("Too few parameters",__LINE__);
          return false;
        }

        findPos = tempStr.find_first_of(" ");

        if(findPos>0){
          tempStr = trimStringFrontAndBack(tempStr.substr(findPos,tempStr.length()));
        }else if(findPos==0){
          RunningLog::writeLog("trim function get an error",__LINE__);
          return false;
        }else{
          RunningLog::writeLog("Too few parameters",__LINE__);
          return false;
        }

        findPos = tempStr.find_first_of(" ");

        if(findPos>0){
          posX2 = atof(tempStr.substr(0,findPos).c_str());
        }else if(findPos==0){
          RunningLog::writeLog("trim function get an error",__LINE__);
          return false;
        }else{
          posX2 = atof(tempStr.c_str());
        }

      }

      _gridSize[0] = lengthUnitTransMulti*fabs(posX2 - posX1);
      labX = true;

      break;
    }

  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin


  bool labY = false;
  os.str("");
  string yLabel;
  os<<plan.at(1)<<"["<<lengthUnit<<"]";
  yLabel = os.str();   //match the Y grid          //if X is not exist--Opt,if X is defined ,necessary
  double posY1=0.0,posY2=0.0;
  while(!in.eof()){
    getline(in,tempStr);
    if( true == strHeadAgreeWithCompareStr(trimStringFront(tempStr),yLabel)){   //opt is setted
      in>>posY1;
      getline(in,tempStr);
      in>>posY2;

      _gridSize[1] = lengthUnitTransMulti*fabs(posY2 - posY1);
      labY = true;

      break;
    }

  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begins
  */

  //------------------------------------------
  /*Read Position*/
  xPos = new double[rows];
  yPos = new double[cols];

  //11
  labX = false;
  os.str("");
  os<<plan.at(0)<<"["<<lengthUnit<<"]";
  xLabel = os.str();                                 //match the X grid         //Opt: defined by "Plan"
  while(!in.eof()){
    getline(in,tempStr);
    if( true == strHeadAgreeWithCompareStr(trimStringFront(tempStr),xLabel)){   //opt is setted
      tempStr = tempStr.substr(xLabel.length(),tempStr.length());
      tempStr = trimStringFrontAndBack(tempStr);
      
      for(int i=0;i<rows;i++){
        tempStrPos = tempStr.find_first_of(" ");

  
        xPos[i] = atof(tempStr.substr(0,tempStrPos).c_str());
        
        tempStr = tempStr.substr(tempStrPos+1,tempStr.length());

        tempStr = trimStringFrontAndBack(tempStr);
      }

      _gridSize[0] = lengthUnitTransMulti*fabs(xPos[rows-1] - xPos[0])/(rows-1);

      labX = true;

      break;
    }

  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin

  labY = false;
  os.str("");
  os<<plan.at(1)<<"["<<lengthUnit<<"]";
  yLabel = os.str();   //match the Y grid          //if X is not exist--Opt,if X is defined ,necessary
  while(!in.eof()){
    getline(in,tempStr);
    if( true == strHeadAgreeWithCompareStr(trimStringFront(tempStr),yLabel)){   //opt is setted

      for(int j=0;j<cols;j++){
        in>>yPos[j];

        getline(in,tempStr);
      }

      _gridSize[1] = lengthUnitTransMulti*(yPos[cols-1] - yPos[0])/(cols-1);

      labY = true;
      break;
    }

  }
  in.clear();   //must clear first
  in.seekg(0, ios::beg); // redirection to begin
  //------------------------------------------

  if(labX != labY || false==labX ){
    in.close();
    tempDoseMatrix = NULL;
    return false;
  }

  heights = 1;
  if(rows*cols*heights<=0){
    RunningLog::writeLog("There are no dose data in this file" + __LINE__);
    return false;
  }

  /*Read data*/
  this->unSync_allocateMatrix(rows,cols,heights);
  tempDoseMatrix = this->getDoseMatrix();

  if(true == labY){     //have "Y[mm]"
  
    while(!in.eof()){
      getline(in,tempStr);
      if(true == strHeadAgreeWithCompareStr(trimStringFront(tempStr),yLabel)){   //find the position

        if(true==voidSplit){

          for(int j=0;j<cols;j++){

            in>>tempInvalued;     //invalid -- col position

            for(int i=0;i<rows;i++){
              in>>tempReadValue;
              tempReadValue = tempReadValue*dataFactor*doseUnitTransMulti;
              //tempDoseArray[(cols-1-j)*cols + i] = tempReadValue;
             //tempDoseMatrix->modifyValue(i,cols-1-j,0,tempReadValue);
             tempDoseMatrix->modifyValue(i,j,0,tempReadValue);
            }
          }
          break;  //finish the dose reading

        }else{
          for(int j=0;j<cols;j++){

            in>>tempInvalued;     //invalid -- col position
            in>>spaceForSeparator;
            for(int i=0;i<rows;i++){
              in>>tempReadValue;
              tempReadValue = tempReadValue*dataFactor*doseUnitTransMulti;
              //tempDoseArray[(cols-1-j)*cols + i] = tempReadValue;
             //tempDoseMatrix->modifyValue(i,cols-1-j,0,tempReadValue);
             tempDoseMatrix->modifyValue(i,j,0,tempReadValue);
              
              in>>spaceForSeparator;
            }
          }
          break;  //finish the dose reading


        }

      }
      
    }
  }


  /*Set the eight boundary points*/
  boundary[0].row = 0;
  boundary[0].col = 0;
  boundary[0].level = 0;

  boundary[1].row = 0;
  boundary[1].col = cols-1;
  boundary[1].level = 0;

  boundary[2].row = rows-1;
  boundary[2].col = 0;
  boundary[2].level = 0;

  boundary[3].row = rows-1;
  boundary[3].col = cols-1;
  boundary[3].level = 0;

  boundary[4].row = 0;
  boundary[4].col = 0;
  boundary[4].level = heights - 1;

  boundary[5].row = 0;
  boundary[5].col = cols-1;
  boundary[5].level = heights - 1;

  boundary[6].row = rows-1;
  boundary[6].col = 0;
  boundary[6].level = heights - 1;

  boundary[7].row = rows-1;
  boundary[7].col = cols-1;
  boundary[7].level = heights - 1;

  this->sync_setBoundaryPoints(boundary);

  /*GridSizes*/
  this->gridSizes[0] = _gridSize[0];
  this->gridSizes[1] = _gridSize[1];

  /*Segments*/
  for(int i=0;i<2;i++){
    this->segments[i] = getGridSegments(this->gridSizes[i]);
  }

  /*dose physic center) (Note: the IBA-Matrix data is exported by matrix software,while the data is
                          exported,the data grid size and the rows/cols may by modify,so the output file is not same as the
                          original binary data inner IBA-matrix software)*/


  tempDoseCentralX = lengthUnitTransMulti*fabs(xPos[0]) + MainFormTempValue.operator_measureDoseCentral.x;
  tempDoseCentralY = lengthUnitTransMulti*fabs(yPos[0]) + MainFormTempValue.operator_measureDoseCentral.y;

  this->doseCentral.x = tempDoseCentralX;
  this->doseCentral.y = tempDoseCentralY;


  //first alignment central
  //first alignment central
  this->firstAlignmentCentral.row = TrimFloat_Down(this->doseCentral.x/this->gridSizes[0],floatVerbStand);
  this->firstAlignmentCentral.col = TrimFloat_Down(this->doseCentral.y/this->gridSizes[1],floatVerbStand);

  //this->sync_setDoseMatrix(tempDoseMatrix);

  in.close();

  tempDoseMatrix = NULL;

  if(NULL != xPos){
    TryToDeleteArray<double>(xPos);
    xPos = NULL;
  }

  if(NULL != yPos){
    TryToDeleteArray<double>(yPos);
    yPos = NULL;
  }

  return true;
}

/*
bool TDose::LoadDIDose(char *file, float hardwarepixel)  //读DICOM文件（文件名,硬件上探测器间隔（像素大小）
{
  //映射物理坐标的做法
  frame=0,row=0,col=0;     //三维层数,行数和列数
  int i,j,num,numb;
  bool isbreak; //作为外层循环中断的标记
  double* pdata;
  double piexlspace[2],origin[3];
  double posrow,poscol;  //posrow为新平面上各点与原数据平面的原点(0,0)在i方向上差了多少列(不一定为整数，有可能为0.5,1.5列)
                         //poscol为新平面上各点与原数据平面的原点(0,0)在j方向上差了多少行(不一定为整数，有可能为0.5,1.5行)

  double d1,d2,d3,d4;
  double a,b,c,d;
  int normpoint;//对齐后的中心点
  double normdata;  //归一化剂量值

  opennew(file);
  pdata = ReadDatanew(frame,row,col);  //从DICOM文件中读值，并取得frame,row和col的值
  ReadPixelSpacenew(piexlspace);


  dosemax = -1;
  dosemin = 1000000;
  for(i=0;i<row;i++)
  {
    for(j=0;j<col;j++)
    {
      if(pdata[i*col+j]>=dosemax)
        dosemax = pdata[i*col+j];
      if(pdata[i*col+j]<=dosemin)
        dosemin = pdata[i*col+j];
    }
  }

  theunits = ReadDoseUnitsnew();

  origin[0] = -piexlspace[0]*(row-1)/2.0; //之前一直以为等剂量中心点（束轴中心点或原点(0,0)）
  origin[1] = -piexlspace[1]*(col-1)/2.0; //为DICOM接口中的ReadOrigin所读出的数据，但是事实上，MapCheck
  origin[2] = 0;                         //认为默认的等剂量中心点(0,0)就是DICOM文件的正中心

  switch(measureFileType)
  {
    case 0:  //该DICOM数据对应的测量数据为中测的测量数据，那么中心点处没有探测器点，所以这时要从中心点外第一个探测器点开始对齐(1/2)gridsize
    {
      segments = 6; ////此时DICOM网格细分为6份(7.2mm/6=1.2mm)
      recordsegments = segments;

      float originnew[2];
      originnew[0] = origin[0] + hardwarepixel/2.0;  //以DICOM文件中心，往前1/2个hardwarepixel为此时的第一个对齐点
      originnew[1] = origin[1] + hardwarepixel/2.0;  //注意origin[]为负，所以+1/2个hardwarepixel相当于往前1/2个hardwarepixel
      irange = 1+ segments*(floor(((row-1)*piexlspace[0]+originnew[0])/hardwarepixel)+ floor(-originnew[0]/hardwarepixel)); //注意origin[]为负值
      jrange = 1+ segments*(floor(((col-1)*piexlspace[1]+originnew[1])/hardwarepixel)+ floor(-originnew[1]/hardwarepixel)); //注意origin[]为负值

      nData = irange*jrange;

      ifirst =  segments*floor((-originnew[0])/hardwarepixel);  //按照图像中心对齐后，左下方第一个正真和探测器点对应点在映射后
      jfirst =  segments*floor((-originnew[1])/hardwarepixel);  //物理坐标系中的位置(从0算起)

      icenter =  ifirst + 3;
      jcenter =  jfirst + 3;  //映射之后物理坐标中的(0,0)点在物理坐标数组中的行和列(从0算起)(只为作图用，计算时对齐任然用ifirst和jfirst)


      //icenter =  segments*floor((-originnew[0])/hardwarepixel);
      //jcenter =  segments*floor((-originnew[1])/hardwarepixel);//映射之后物理坐标中的(0,0)点在物理坐标数组中的行和列(从0算起)

      DoseAbs = new float[nData];
      NormDose = new float[nData];

      numb = 0;

      for(j=0;j<jrange;j++)
      {
        poscol = (-originnew[1]-(jfirst-j)*(hardwarepixel/segments))/piexlspace[1];

        for(i=0;i<irange;i++)
        {
           //posrow为新平面上各点与原数据平面的原点(0,0)在i方向上差了多少列(不一定为整数，有可能为0.5,1.5列)
          posrow = (-originnew[0] - (ifirst -i)*(hardwarepixel/segments))/piexlspace[0];

          d1 = posrow -floor(posrow);
          d2 = poscol -floor(poscol);
          d3 = 1 - d2;
          d4 = 1 - d1;
          a = pdata[col*(int)floor(poscol) + (int)floor(posrow)];
          b = pdata[col*(int)floor(poscol) + (int)ceil(posrow)];
          c = pdata[col*(int)ceil(poscol) + (int)floor(posrow)];
          d = pdata[col*(int)ceil(poscol) + (int)ceil(posrow)];

          DoseAbs[numb] = ((a*d4 + b*d1)*d3 + (c*d4 + d*d1)*d2)*100;  //将数据映射到物理坐标上
          //pDIDose[numb] = (a*d4 + c*d1)*d3 + (b*d4 + d*d1)*d2;
          numb++;

        }
      }

      normpoint =jfirst*irange + ifirst;   // 等剂量中心点

      num = 0;

      normdata= -100;
      for(i=0;i<irange;i++)
      {
        for(j=0;j<jrange;j++)
        {
          if(DoseAbs[num]>normdata)
            normdata = DoseAbs[num];
          num++;
        }
      }
      //normdata = pDIDose[normpoint]; //中期验收时的做法即选取DICOM中对齐后中心点剂量作为最大值，但是由于测量平面中选取最大值作为归一化点(最大值为100%)，所以这样做不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)

      //默认情况下，DICOM对齐之后，选择剂量最大值点作为归一化点（这与中期验收时选择DICOM中对齐后中心点剂量作为最大值的做法有所不同，主要由于测量平面中选取最大值作为归一化点(最大值为100%)，所以选择DICOM中对齐后中心点剂量作为最大值不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)）
      num = 0;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          NormDose[num] = 100*DoseAbs[num]/normdata; //转换为百分相对剂量
          num++;
        }
      }


      //找剪切去掉0.000000之后的下界
      num = 0;
      isbreak = false;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[num]>0.01)
          {
            cuthoriz[0] = j+4;  //找到0.01之后再向下移动4行作为下边界
            isbreak = true;
            break;
          }
          num++;
        }


        if(isbreak == true)
        {
          break;
        }
      }


      //找剪切去掉0.000000之后的上界
      isbreak = false;
      for(j=jrange-1;j>=0;j--)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[j*irange+i]>0.01)
          {
            cuthoriz[1] = j-4;  //找到0.01之后再向上移动4行作为下边界(所谓的上下左右是输出文本中的方向)
            isbreak = true;
            break;
          }
        }


        if(isbreak == true)
        {
          break;
        }
      }


      //找剪切去掉0.000000之后的左边界
      isbreak = false;
      for(i=0;i<irange;i++)
      {
        for(j=0;j<jrange;j++)
        {
          if(NormDose[j*irange+i]>0.01)
          {
            cutverit[0] = i+2;
            isbreak = true;
            break;
          }
        }

        if(isbreak == true)
        {
          break;
        }
      }

      //找剪切去掉0.000000之后的右边界
      isbreak = false;
      for(i=irange-1;i>=0;i--)
      {
        for(j=0;j<jrange;j++)
        {
          if(NormDose[j*jrange+i]>0.01)
          {
            cutverit[1] = i-2;
            isbreak = true;
            break;
          }
        }

        if(isbreak == true)
        {
          break;
        }
      }

      delete pdata;
      return true;
    }
    break;

    case 1:  //该DICOM数据对应的测量数据为MapCHECK格式测量数据，由于对应的测量数据中心点刚好为已知点(有探测器)，所以从中心点开始往外对齐
    {
      segments = 5;  //此时将DICOM网格细分为5份(5mm/5=1mm)
      recordsegments = segments;

      irange = 1+ segments*(floor(((row-1)*piexlspace[0]+origin[0])/hardwarepixel)+ floor(-origin[0]/hardwarepixel)); //注意origin[]为负值
      jrange = 1+ segments*(floor(((col-1)*piexlspace[1]+origin[1])/hardwarepixel)+ floor(-origin[1]/hardwarepixel)); //注意origin[]为负值

      nData = irange*jrange;

      ifirst =  segments*floor((-origin[0])/hardwarepixel);
      jfirst =  segments*floor((-origin[1])/hardwarepixel);

      icenter =  segments*floor((-origin[0])/hardwarepixel);
      jcenter =  segments*floor((-origin[1])/hardwarepixel);//映射之后物理坐标中的(0,0)点在物理坐标数组中的行和列

      DoseAbs = new float[nData];
      NormDose = new float[nData];

      numb = 0;

      for(j=0;j<jrange;j++)
      {
        poscol = (-origin[1]-(jfirst-j)*(hardwarepixel/segments))/piexlspace[1];

        for(i=0;i<irange;i++)
        {
          //posrow为新平面上各点与原数据平面的原点(0,0)在i方向上差了多少列(不一定为整数，有可能为0.5,1.5列)
          posrow = (-origin[0] - (ifirst -i)*(hardwarepixel/segments))/piexlspace[0];

          d1 = posrow -floor(posrow);
          d2 = poscol -floor(poscol);
          d3 = 1 - d2;
          d4 = 1 - d1;
          a = pdata[col*(int)floor(poscol) + (int)floor(posrow)];
          b = pdata[col*(int)floor(poscol) + (int)ceil(posrow)];
          c = pdata[col*(int)ceil(poscol) + (int)floor(posrow)];
          d = pdata[col*(int)ceil(poscol) + (int)ceil(posrow)];

          DoseAbs[numb] = ((a*d4 + b*d1)*d3 + (c*d4 + d*d1)*d2)*100;  //将数据映射到物理坐标上
          //pDIDose[numb] = (a*d4 + c*d1)*d3 + (b*d4 + d*d1)*d2;
          numb++;

        }
      }

      normpoint =jfirst*irange + ifirst;   // 等剂量中心点


      //（默认）默认情况下，DICOM对齐之后，选择剂量最大值点作为归一化点（这与中期验收时选择DICOM中对齐后中心点剂量作为最大值的做法有所不同，主要由于测量平面中选取最大值作为归一化点(最大值为100%)，所以选择DICOM中对齐后中心点剂量作为最大值不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)）
      num = 0;

      normdata= -100;
      for(i=0;i<irange;i++)
      {
        for(j=0;j<jrange;j++)
        {
          if(DoseAbs[num]>normdata)
            normdata = DoseAbs[num];
          num++;
        }
      }
      //normdata = DoseAbs[normpoint]; //中期验收时的做法即选取DICOM中对齐后中心点剂量作为最大值，但是由于测量平面中选取最大值作为归一化点(最大值为100%)，所以这样做不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)

      //默认情况下，DICOM对齐之后，选择剂量最大值点作为归一化点（这与中期验收时选择DICOM中对齐后中心点剂量作为最大值的做法有所不同，主要由于测量平面中选取最大值作为归一化点(最大值为100%)，所以选择DICOM中对齐后中心点剂量作为最大值不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)）
      num = 0;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          NormDose[num] = 100*DoseAbs[num]/normdata; //转换为百分相对剂量
          num++;
        }
      }


      //找剪切去掉0.000000之后的下界
      num = 0;
      isbreak = false;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[num]>0.01)
          {
            cuthoriz[0] = j+4;  //找到0.01之后再向下移动4行作为下边界
            isbreak = true;
            break;
          }
          num++;
        }


        if(isbreak == true)
        {
          break;
        }
      }


      //找剪切去掉0.000000之后的上界
      isbreak = false;
      for(j=jrange-1;j>=0;j--)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[j*irange+i]>0.01)
          {
            cuthoriz[1] = j-4;  //找到0.01之后再向上移动4行作为下边界(所谓的上下左右是输出文本中的方向)
            isbreak = true;
            break;
          }
        }


        if(isbreak == true)
        {
          break;
        }
      }


      //找剪切去掉0.000000之后的左边界
      isbreak = false;
      for(i=0;i<irange;i++)
      {
        for(j=0;j<jrange;j++)
        {
          if(NormDose[j*irange+i]>0.01)
          {
            cutverit[0] = i+2;
            isbreak = true;
            break;
          }
        }

        if(isbreak == true)
        {
          break;
        }
      }

      //找剪切去掉0.000000之后的右边界
      isbreak = false;
      for(i=irange-1;i>=0;i--)
      {
        for(j=0;j<jrange;j++)
        {
          if(NormDose[j*jrange+i]>0.01)
          {
            cutverit[1] = i-2;
            isbreak = true;
            break;
          }
        }

        if(isbreak == true)
        {
          break;
        }
      }

      delete pdata;
      return true;
    }
    break;

    case 2:  //Matrix测量数据
    {
      //segments = ; //未完成
      recordsegments = segments;
    }
    break;

    default:
    {
      MessageDlg("The number out of region",mtInformation,TMsgDlgButtons()<<mbOK,0);
    }
    break;
  }

  return false;
}
*/
/*read DICOM calculated file*/
bool Dose::loadDICOMCalcFile()throw (const char*){

  int rows = 0,cols = 0,heights = 0;
  double* tempDoseArray = NULL;
  MatrixData<double>* tempDoseMatrix = NULL;
  double *ptr = NULL;

  double piexlspace[2],origin[3];
  AnsiString ansiDoseUnits;
  string doseUnits;
  double doseUnitTransMulti = 100;
  int count = 0;

  double maxDose = -DBL_MAX;
  double minDose = DBL_MAX;

  opennew(this->fileName.c_str());
  tempDoseArray = ReadDatanew(heights,rows,cols);  //从DICOM文件中读值，并取得frame,row和col的值
  heights = 1;

  ptr = tempDoseArray;

  ReadPixelSpacenew(piexlspace);

  this->gridSizes[0] = fabs(piexlspace[0]);
  this->gridSizes[1] = fabs(piexlspace[1]);

  /*dose physic center*/
  double originPos[3];
  ReadOrgPointnew(originPos);


  this->doseCentral.x = (rows-1)*this->gridSizes[0]/2.0;
  this->doseCentral.y = (cols-1)*this->gridSizes[1]/2.0;

  ansiDoseUnits = ReadDoseUnitsnew();

  ansiDoseUnits = ansiDoseUnits.LowerCase();
  doseUnits = ansiDoseUnits.c_str();
  
  if(true==strHeadAgreeWithCompareStr(doseUnits,"gy")){
      doseUnitTransMulti = 100;
  }else if(true==strHeadAgreeWithCompareStr(doseUnits,"cgy")){
      doseUnitTransMulti = 1;
  }else if(true==strHeadAgreeWithCompareStr(doseUnits,"mgy")){
      doseUnitTransMulti = 0.1;
  }else if(true==strHeadAgreeWithCompareStr(doseUnits,"ugy")){
      doseUnitTransMulti = 0.0001;
  }
  

  count = rows*cols*heights;
  if(count<=0){
    RunningLog::writeLog("There are no dose data in this file" + __LINE__);
    return false;
  }

  tempDoseMatrix = new MatrixData<double>();
  tempDoseMatrix->allocate(rows,cols,heights);

  for(int j=0;j<cols;j++){
    for(int i=0;i<rows;i++){
      //tempDoseMatrix->modifyValue(i,j,0,(*ptr)*doseUnitTransMulti);
      tempDoseMatrix->modifyValue(i,cols -1 - j,0,(*ptr)*doseUnitTransMulti);
      ptr++;
    }
  }

  this->sync_setDoseMatrix(tempDoseMatrix);

  /*Set the eight boundary points*/
  GridPoint boundary[8];

  boundary[0].row = 0;
  boundary[0].col = 0;
  boundary[0].level = 0;

  boundary[1].row = 0;
  boundary[1].col = cols-1;
  boundary[1].level = 0;

  boundary[2].row = rows-1;
  boundary[2].col = 0;
  boundary[2].level = 0;

  boundary[3].row = rows-1;
  boundary[3].col = cols-1;
  boundary[3].level = 0;

  boundary[4].row = 0;
  boundary[4].col = 0;
  boundary[4].level = heights - 1;

  boundary[5].row = 0;
  boundary[5].col = cols-1;
  boundary[5].level = heights - 1;

  boundary[6].row = rows-1;
  boundary[6].col = 0;
  boundary[6].level = heights - 1;

  boundary[7].row = rows-1;
  boundary[7].col = cols-1;
  boundary[7].level = heights - 1;
  this->sync_setBoundaryPoints(boundary);

  TryToDeleteArray<double>(tempDoseArray);
  tempDoseArray = NULL;

  TryToDelete<MatrixData<double> >(tempDoseMatrix);
  tempDoseMatrix = NULL;

  ptr = NULL;
  
  closenew(this->fileName.c_str());
  return true;
}
bool Dose::loadSCUCalcFile()throw (const char*){
  return true;
}










//-------------------------Old one--------------------

/*Destructor*/
TDose::~TDose()
{
  if(NormDose)
  {
    delete[] NormDose;
  }

  if(DoseAbs)
  {
    delete[] DoseAbs;
  }
}

//------------TDose:Constructor:Vars--------------------
TDose::TDose(char *file,int ftype)
{
 /*
 // GetArray(ftype); //先得到探测器阵列信息
  NormDose=NULL;
  DoseAbs=NULL;


  dosemax=0.0;

  //FileType=ftype; //0表示MapCheck数据排列格式，1表示DICOM的文件格式,2表示中测数据格式，3表示Matrix数据格式

  switch(ftype)
  {
    case 0:             //中测数据
    {
      LoadZCDose(file);
    }
    break;

    case 1:            //MapCheck数据
    {
      LoadMapCHECKDose(file);
      //Interpolationx(ftype);
      //Interpolationy(ftype);
      BlineInterp();
    }
    break;

    case 3:             //Matrix数据
    {
      LoadMatrixDose(file);
    }
    break;

    case 11:              //DICOM格式的计算数据
    {
      LoadDIDose(file,gridsize);
    }
    break;

    case 12:            //SCU格式的计算数据
    {
      //未完成
    }
    break;

    default:
      break;
  }

  */
}

//---------------------------------------------------------------
bool TDose::LoadDIDose(char *file, float hardwarepixel)  //读DICOM文件（文件名,硬件上探测器间隔（像素大小）
{
   /*
  //映射物理坐标的做法

  frame=0,row=0,col=0;     //三维层数,行数和列数
  int i,j,num,numb;
  bool isbreak; //作为外层循环中断的标记
  double* pdata;
  double piexlspace[2],origin[3];
  double posrow,poscol;  //posrow为新平面上各点与原数据平面的原点(0,0)在i方向上差了多少列(不一定为整数，有可能为0.5,1.5列)
                         //poscol为新平面上各点与原数据平面的原点(0,0)在j方向上差了多少行(不一定为整数，有可能为0.5,1.5行)

  double d1,d2,d3,d4;
  double a,b,c,d;
  int normpoint;//对齐后的中心点
  double normdata;  //归一化剂量值

  opennew(file);
  pdata = ReadDatanew(frame,row,col);  //从DICOM文件中读值，并取得frame,row和col的值
  ReadPixelSpacenew(piexlspace);


  dosemax = -1;
  dosemin = 1000000;
  for(i=0;i<row;i++)
  {
    for(j=0;j<col;j++)
    {
      if(pdata[i*col+j]>=dosemax)
        dosemax = pdata[i*col+j];
      if(pdata[i*col+j]<=dosemin)
        dosemin = pdata[i*col+j];
    }
  }

  theunits = ReadDoseUnitsnew();

  origin[0] = -piexlspace[0]*(row-1)/2.0; //之前一直以为等剂量中心点（束轴中心点或原点(0,0)）
  origin[1] = -piexlspace[1]*(col-1)/2.0; //为DICOM接口中的ReadOrigin所读出的数据，但是事实上，MapCheck
  origin[2] = 0;                         //认为默认的等剂量中心点(0,0)就是DICOM文件的正中心


//  if(measureFileType == )
//  {
//    segments = 6;
//  }
//  else if(gridsizebyMapcheck==true)
//  {
//    segments = 5;
//  }
//  else if(gridsizebyother == true)
//  {
//    int trynum;
//    for(trynum=1;;trynum++)
//    {
//      if(hardwarepixel/trynum<0.6)
//      {
//         segments = trynum+1;
//         break;
//      }
//    }
//  }
  switch(measureFileType)
  {
    case 0:  //该DICOM数据对应的测量数据为中测的测量数据，那么中心点处没有探测器点，所以这时要从中心点外第一个探测器点开始对齐(1/2)gridsize
    {
      segments = 6; ////此时DICOM网格细分为6份(7.2mm/6=1.2mm)
      recordsegments = segments;

      float originnew[2];
      originnew[0] = origin[0] + hardwarepixel/2.0;  //以DICOM文件中心，往前1/2个hardwarepixel为此时的第一个对齐点
      originnew[1] = origin[1] + hardwarepixel/2.0;  //注意origin[]为负，所以+1/2个hardwarepixel相当于往前1/2个hardwarepixel
      irange = 1+ segments*(floor(((row-1)*piexlspace[0]+originnew[0])/hardwarepixel)+ floor(-originnew[0]/hardwarepixel)); //注意origin[]为负值
      jrange = 1+ segments*(floor(((col-1)*piexlspace[1]+originnew[1])/hardwarepixel)+ floor(-originnew[1]/hardwarepixel)); //注意origin[]为负值

      nData = irange*jrange;

      ifirst =  segments*floor((-originnew[0])/hardwarepixel);  //按照图像中心对齐后，左下方第一个正真和探测器点对应点在映射后
      jfirst =  segments*floor((-originnew[1])/hardwarepixel);  //物理坐标系中的位置(从0算起)

      icenter =  ifirst + 3;
      jcenter =  jfirst + 3;  //映射之后物理坐标中的(0,0)点在物理坐标数组中的行和列(从0算起)(只为作图用，计算时对齐任然用ifirst和jfirst)


      //icenter =  segments*floor((-originnew[0])/hardwarepixel);
      //jcenter =  segments*floor((-originnew[1])/hardwarepixel);//映射之后物理坐标中的(0,0)点在物理坐标数组中的行和列(从0算起)

      DoseAbs = new float[nData];
      NormDose = new float[nData];

      numb = 0;

      for(j=0;j<jrange;j++)
      {
        poscol = (-originnew[1]-(jfirst-j)*(hardwarepixel/segments))/piexlspace[1];

        for(i=0;i<irange;i++)
        {
           //posrow为新平面上各点与原数据平面的原点(0,0)在i方向上差了多少列(不一定为整数，有可能为0.5,1.5列)
          posrow = (-originnew[0] - (ifirst -i)*(hardwarepixel/segments))/piexlspace[0];

          d1 = posrow -floor(posrow);
          d2 = poscol -floor(poscol);
          d3 = 1 - d2;
          d4 = 1 - d1;
          a = pdata[col*(int)floor(poscol) + (int)floor(posrow)];
          b = pdata[col*(int)floor(poscol) + (int)ceil(posrow)];
          c = pdata[col*(int)ceil(poscol) + (int)floor(posrow)];
          d = pdata[col*(int)ceil(poscol) + (int)ceil(posrow)];

          DoseAbs[numb] = ((a*d4 + b*d1)*d3 + (c*d4 + d*d1)*d2)*100;  //将数据映射到物理坐标上
          //pDIDose[numb] = (a*d4 + c*d1)*d3 + (b*d4 + d*d1)*d2;
          numb++;

        }
      }

      normpoint =jfirst*irange + ifirst;   // 等剂量中心点

      num = 0;

      normdata= -100;
      for(i=0;i<irange;i++)
      {
        for(j=0;j<jrange;j++)
        {
          if(DoseAbs[num]>normdata)
            normdata = DoseAbs[num];
          num++;
        }
      }
      //normdata = pDIDose[normpoint]; //中期验收时的做法即选取DICOM中对齐后中心点剂量作为最大值，但是由于测量平面中选取最大值作为归一化点(最大值为100%)，所以这样做不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)

      //默认情况下，DICOM对齐之后，选择剂量最大值点作为归一化点（这与中期验收时选择DICOM中对齐后中心点剂量作为最大值的做法有所不同，主要由于测量平面中选取最大值作为归一化点(最大值为100%)，所以选择DICOM中对齐后中心点剂量作为最大值不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)）
      num = 0;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          NormDose[num] = 100*DoseAbs[num]/normdata; //转换为百分相对剂量
          num++;
        }
      }


      //找剪切去掉0.000000之后的下界
      num = 0;
      isbreak = false;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[num]>0.01)
          {
            cuthoriz[0] = j+4;  //找到0.01之后再向下移动4行作为下边界
            isbreak = true;
            break;
          }
          num++;
        }


        if(isbreak == true)
        {
          break;
        }
      }


      //找剪切去掉0.000000之后的上界
      isbreak = false;
      for(j=jrange-1;j>=0;j--)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[j*irange+i]>0.01)
          {
            cuthoriz[1] = j-4;  //找到0.01之后再向上移动4行作为下边界(所谓的上下左右是输出文本中的方向)
            isbreak = true;
            break;
          }
        }


        if(isbreak == true)
        {
          break;
        }
      }


      //找剪切去掉0.000000之后的左边界
      isbreak = false;
      for(i=0;i<irange;i++)
      {
        for(j=0;j<jrange;j++)
        {
          if(NormDose[j*irange+i]>0.01)
          {
            cutverit[0] = i+2;
            isbreak = true;
            break;
          }
        }

        if(isbreak == true)
        {
          break;
        }
      }

      //找剪切去掉0.000000之后的右边界
      isbreak = false;
      for(i=irange-1;i>=0;i--)
      {
        for(j=0;j<jrange;j++)
        {
          if(NormDose[j*jrange+i]>0.01)
          {
            cutverit[1] = i-2;
            isbreak = true;
            break;
          }
        }

        if(isbreak == true)
        {
          break;
        }
      }

      delete pdata;
      return true;
    }
    break;

    case 1:  //该DICOM数据对应的测量数据为MapCHECK格式测量数据，由于对应的测量数据中心点刚好为已知点(有探测器)，所以从中心点开始往外对齐
    {
      segments = 5;  //此时将DICOM网格细分为5份(5mm/5=1mm)
      recordsegments = segments;

      irange = 1+ segments*(floor(((row-1)*piexlspace[0]+origin[0])/hardwarepixel)+ floor(-origin[0]/hardwarepixel)); //注意origin[]为负值
      jrange = 1+ segments*(floor(((col-1)*piexlspace[1]+origin[1])/hardwarepixel)+ floor(-origin[1]/hardwarepixel)); //注意origin[]为负值

      nData = irange*jrange;

      ifirst =  segments*floor((-origin[0])/hardwarepixel);
      jfirst =  segments*floor((-origin[1])/hardwarepixel);

      icenter =  segments*floor((-origin[0])/hardwarepixel);
      jcenter =  segments*floor((-origin[1])/hardwarepixel);//映射之后物理坐标中的(0,0)点在物理坐标数组中的行和列

      DoseAbs = new float[nData];
      NormDose = new float[nData];

      numb = 0;

      for(j=0;j<jrange;j++)
      {
        poscol = (-origin[1]-(jfirst-j)*(hardwarepixel/segments))/piexlspace[1];

        for(i=0;i<irange;i++)
        {
          //posrow为新平面上各点与原数据平面的原点(0,0)在i方向上差了多少列(不一定为整数，有可能为0.5,1.5列)
          posrow = (-origin[0] - (ifirst -i)*(hardwarepixel/segments))/piexlspace[0];

          d1 = posrow -floor(posrow);
          d2 = poscol -floor(poscol);
          d3 = 1 - d2;
          d4 = 1 - d1;
          a = pdata[col*(int)floor(poscol) + (int)floor(posrow)];
          b = pdata[col*(int)floor(poscol) + (int)ceil(posrow)];
          c = pdata[col*(int)ceil(poscol) + (int)floor(posrow)];
          d = pdata[col*(int)ceil(poscol) + (int)ceil(posrow)];

          DoseAbs[numb] = ((a*d4 + b*d1)*d3 + (c*d4 + d*d1)*d2)*100;  //将数据映射到物理坐标上
          //pDIDose[numb] = (a*d4 + c*d1)*d3 + (b*d4 + d*d1)*d2;
          numb++;

        }
      }

      normpoint =jfirst*irange + ifirst;   // 等剂量中心点


      //（默认）默认情况下，DICOM对齐之后，选择剂量最大值点作为归一化点（这与中期验收时选择DICOM中对齐后中心点剂量作为最大值的做法有所不同，主要由于测量平面中选取最大值作为归一化点(最大值为100%)，所以选择DICOM中对齐后中心点剂量作为最大值不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)）
      num = 0;

      normdata= -100;
      for(i=0;i<irange;i++)
      {
        for(j=0;j<jrange;j++)
        {
          if(DoseAbs[num]>normdata)
            normdata = DoseAbs[num];
          num++;
        }
      }
      //normdata = DoseAbs[normpoint]; //中期验收时的做法即选取DICOM中对齐后中心点剂量作为最大值，但是由于测量平面中选取最大值作为归一化点(最大值为100%)，所以这样做不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)

      //默认情况下，DICOM对齐之后，选择剂量最大值点作为归一化点（这与中期验收时选择DICOM中对齐后中心点剂量作为最大值的做法有所不同，主要由于测量平面中选取最大值作为归一化点(最大值为100%)，所以选择DICOM中对齐后中心点剂量作为最大值不太科学(比如说DICOM中心点处的值为最大值的10%，那么若以这个点为归一化的点，那么DICOM平面上有很多点相对剂量会超过100%，最大值处相对剂量会达到1000%，这样人为的造成与测量平面归一化的结果差异过大，产生巨大误差)）
      num = 0;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          NormDose[num] = 100*DoseAbs[num]/normdata; //转换为百分相对剂量
          num++;
        }
      }


      //找剪切去掉0.000000之后的下界
      num = 0;
      isbreak = false;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[num]>0.01)
          {
            cuthoriz[0] = j+4;  //找到0.01之后再向下移动4行作为下边界
            isbreak = true;
            break;
          }
          num++;
        }


        if(isbreak == true)
        {
          break;
        }
      }


      //找剪切去掉0.000000之后的上界
      isbreak = false;
      for(j=jrange-1;j>=0;j--)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[j*irange+i]>0.01)
          {
            cuthoriz[1] = j-4;  //找到0.01之后再向上移动4行作为下边界(所谓的上下左右是输出文本中的方向)
            isbreak = true;
            break;
          }
        }


        if(isbreak == true)
        {
          break;
        }
      }


      //找剪切去掉0.000000之后的左边界
      isbreak = false;
      for(i=0;i<irange;i++)
      {
        for(j=0;j<jrange;j++)
        {
          if(NormDose[j*irange+i]>0.01)
          {
            cutverit[0] = i+2;
            isbreak = true;
            break;
          }
        }

        if(isbreak == true)
        {
          break;
        }
      }

      //找剪切去掉0.000000之后的右边界
      isbreak = false;
      for(i=irange-1;i>=0;i--)
      {
        for(j=0;j<jrange;j++)
        {
          if(NormDose[j*jrange+i]>0.01)
          {
            cutverit[1] = i-2;
            isbreak = true;
            break;
          }
        }

        if(isbreak == true)
        {
          break;
        }
      }

      delete pdata;
      return true;
    }
    break;

    case 2:  //Matrix测量数据
    {
      //segments = ; //未完成
      recordsegments = segments;
    }
    break;

    default:
    {
      MessageDlg("The number out of region",mtInformation,TMsgDlgButtons()<<mbOK,0);
    }
    break;
  }

  return false;
  */
  return true;
}
//---------------------------------------------------------------
bool TDose::LoadDIDose(char *file)    //读DICOM文件，对齐时间距为1mm
{

  /*   //只读原始值，不映射物理坐标的做法
  col=0;
  row=0;
  int i,j,num;
  double *tempdose;

  opennew(file);
  tempdose = ReadDatanew(row,col);
  nData = row*col;

  pDIDose = new float[nData];
  NormDI = new float[nData];

  for(i=0;i<nData;i++)
  {
    pDIDose[i] = tempdose[i];

    if(dosemax<=tempdose[i])
      dosemax = tempdose[i];
  }

  for(i=0;i<nData;i++)
  {
    NormDI[i] = (pDIDose[i]/dosemax)*100;
  }


  //ReadPixelSpacenew(piexlspace);
  //ReadOrgPointnew(origin);
  delete tempdose;

  return true;
  */

  /*
  //映射物理坐标的做法
  frame=0,col=0,row=0;
  int i,j,num,numb;
  bool isbreak; //作为外层循环中断的标记
  double* pdata;
  double piexlspace[2],origin[3],npoint[3];
  double posrow,poscol;

  double d1,d2,d3,d4;
  double a,b,c,d;
  int normpoint;//中心点(这里当做归一化点)
  double normdata;  //归一化剂量值

  opennew(file);
  pdata = ReadDatanew(frame,row,col);  //从DICOM文件中读值
  ReadPixelSpacenew(piexlspace);

  ReadNormaPointnew(npoint);
  ReadDoseGridScalingnew();

  theunits = ReadDoseUnitsnew();

  origin[0] = -piexlspace[0]*(row-1)/2.0; //之前一直以为等剂量中心点（束轴中心点或原点(0,0)）
  origin[1] = -piexlspace[1]*(col-1)/2.0; //为DICOM接口中的ReadOrigin所读出的数据，但是事实上，MapCheck
  origin[2] = 0;

  theunits = ReadDoseUnitsnew();

  irange = floor(row*piexlspace[1]);
  jrange = floor(col*piexlspace[0]);

  nData = irange*jrange;

  icenter = floor(-origin[1]) + 1;
  jcenter = floor(-origin[0]) + 1;//映射之后物理坐标中的(0,0)点在物理坐标数组中的行和列

  pDIDose = new float[irange*jrange];
  NormDI = new float[irange*jrange];

  numb = 0;

  for(i=0;i<irange;i++)
  {
    if(i==0)
      posrow = 0.0;
    else
      posrow = (-origin[0] - (jcenter -i))/piexlspace[1];
    for(j=0;j<jrange;j++)
    {
      if(j==0)
        poscol = 0.0;
      else
        poscol = (-origin[1]+j - icenter)/piexlspace[0];

      d1 = posrow -floor(posrow);
      d2 = poscol -floor(poscol);
      d3 = 1 - d2;
      d4 = 1 - d1;
      a = pdata[col*(int)floor(posrow) + (int)floor(poscol)];
      b = pdata[col*(int)floor(posrow) + (int)ceil(poscol)];
      c = pdata[col*(int)ceil(posrow) + (int)floor(poscol)];
      d = pdata[col*(int)ceil(posrow) + (int)ceil(poscol)];

      pDIDose[numb] = ((a*d4 + c*d1)*d3 + (b*d4 + d*d1)*d2)*100;  //将数据映射到物理坐标上
      //pDIDose[numb] = (a*d4 + c*d1)*d3 + (b*d4 + d*d1)*d2;
      numb++;

    }
  }

  normpoint =icenter*irange + jcenter;
  normdata = pDIDose[normpoint];

  num = 0;
  for(i=0;i<irange;i++)
  {
    for(j=0;j<jrange;j++)
    {
      NormDI[num] = 100*pDIDose[num]/normdata;
      num++;
    }
  }


  //找剪切去掉0.000000之后的上界
  num = 0;
  isbreak = false;
  for(i=0;i<irange;i++)
  {
    for(j=0;j<jrange;j++)
    {
      if(NormDI[num]>0.01)
      {
        cuthoriz[0] = i;  //找到0.01之后再向下移动4行作为上边界
        isbreak = true;
        break;
      }
      num++;
    }


    if(isbreak == true)
    {
      break;
    }
  }


  //找剪切去掉0.000000之后的下界
  isbreak = false;
  for(i=irange-1;i>=0;i--)
  {
    for(j=0;j<jrange;j++)
    {
      if(NormDI[i*jrange+j]>0.01)
      {
        cuthoriz[1] = i;  //找到0.01之后再向上移动4行作为下边界(所谓的上下左右是输出文本中的方向)
        isbreak = true;
        break;
      }
    }


    if(isbreak == true)
    {
      break;
    }
  }

  //找剪切去掉0.000000之后的左边界
  isbreak = false;
  for(j=0;j<jrange;j++)
  {
    for(i=0;i<jrange;i++)
    {
      if(NormDI[i*jrange+j]>0.01)
      {
        cutverit[0] = j;
        isbreak = true;
        break;
      }
    }

    if(isbreak == true)
    {
      break;
    }
  }

  //找剪切去掉0.000000之后的右边界
  isbreak = false;
  for(j=jrange-1;j>=0;j--)
  {
    for(i=0;i<jrange;i++)
    {
      if(NormDI[i*jrange+j]>0.01)
      {
        cutverit[1] = j;
        isbreak = true;
        break;
      }
    }

    if(isbreak == true)
    {
      break;
    }
  }

  delete pdata;
  return true;
  */
  return true;
}
//---------------------------------------------------------------
bool TDose::LoadZCDose(char *file)
{
  int i,j,k;
  float zNo,*ptr,*ptrzc;

  FILE *fp=fopen(file,"r");
  if(fp==NULL)
  {
    printf("read file error\n");
    return false;
  }


  char dot;
  nx=40;
  ny=40;
  nz=1;      //暂前只读第一个切片的数据
  nData=nx*ny*nz;

  //分配初始化内存
  DoseAbs = new float[nData];
  NormDose = new float[nData];
  for(i=0;i<nData;i++)
    DoseAbs[i] = 0.0;
  for(i=0;i<nData;i++)
    NormDose[i] = 0.0;

  //读数据
  ptr=DoseAbs;
  dosemax=0.0;
  dosemin = 10000.0;
  for(k=0;k<nz;k++)
  {
    fscanf(fp,"%f",&zNo);
    for(j=0;j<ny;j++)
    {
      for(i=0;i<nx;i++)
      {
        fscanf(fp,"%f",ptr);
        fscanf(fp,",",&dot); //中测数据中有个","号
        if(dosemax<*ptr)    //找最大值
          dosemax=*ptr;
        if((dosemin>*ptr)&&(*ptr!=0))    //找最小值
          dosemin = *ptr;
        ptr++;
      }
    }
  }

  for(i=0;i<nData;i++)      //百分相对剂量
    NormDose[i] = (DoseAbs[i]/dosemax)*100;


  fclose(fp);
  return true;
}

//---------------------------------------------------------------
bool TDose::LoadMatrixDose(char *file)
{
  int i,j,k;
  float zNo,*ptr,*ptrzc;

  FILE *fp=fopen(file,"r");
  if(fp==NULL)
  {
    printf("read file error\n");
    return false;
  }

  //读文件头
  fscanf(fp,"%d%d%d%d%d%d",&lx,&hx,&ly,&hy,&lz,&hz);
  nx=hx-lx+1;
  ny=hy-ly+1;
  nz=1;      //暂前只读第一个切片的数据
  nData=nx*ny*nz;

  //分配初始化内存
  DoseAbs = new float[nData];
  NormDose = new float[nData];
  for(i=0;i<nData;i++)
    DoseAbs[i]=0.0;
  for(i=0;i<nData;i++)
    NormDose[i] = 0.0;

  //读数据
  ptr=DoseAbs;
  dosemax=0.0;
  dosemin = 10000.0;
  for(k=0;k<nz;k++)
  {
    fscanf(fp,"%f",&zNo);
    for(j=0;j<ny;j++)
    {
      for(i=0;i<nx;i++)
      {
        fscanf(fp,"%f",ptr);
        if(dosemax<*ptr)    //找最大值
          dosemax=*ptr;
        if((dosemin>*ptr)&&(*ptr!=0))    //找最小值
          dosemin = *ptr;
        ptr++;
      }
    }
  }

  for(i=0;i<nData;i++)      //百分相对剂量
    NormDose[i] = (DoseAbs[i]/dosemax)*100;


  fclose(fp);
  return true;
}

//-----------------------------------------------------------------
bool TDose::LoadMapCHECKDose(char *file)
{
  //
  int i,j;
  float tempData;
  int totalN = 0;

  ifstream in;
  in.open(file,ios::in);   //std::ios
  if(!in.is_open()){
    return false;
  }

  string tempStr;
  TRegexp exp_Rows("^Rows:");     //使用正则表达式匹配行数
  TRegexp exp_Cols("^Cols:");
  TRegexp exp_num ("[1-9][0-9]*");
  TRegexp exp_DataLabel("^Corrected Counts");
  int match_Result = 0;
  size_t length = 0;
  size_t position = 0;
  char rowsNum[10];
  char colsNum[10];
  int verify = 0;
  int rows = -1;
  int cols = -1;

  while(getline(in,tempStr)){    //std::getline()
    if(exp_Rows.find(tempStr.begin(),&length,position) != -1){  //found sign of "Rows:"

      if( (match_Result=exp_num.find(tempStr.begin(),&length,position)) != -1){ //found numbers

        if(length<1000){
          memcpy(rowsNum,tempStr.begin()+match_Result,length);
          rows = atoi(rowsNum);
          verify++;
        }
      }
    }

    if(exp_Cols.find(tempStr.begin(),&length,position) != -1){  //found sign of "Cows:"

      if( (match_Result=exp_num.find(tempStr.begin(),&length,position)) != -1){ //found numbers

        if(length<1000){
          memcpy(colsNum,tempStr.begin()+match_Result,length);
          cols = atoi(colsNum);
          verify++;
        }
      }
    }

    if(verify>=2){
      break;
    }

  }

  if(verify<2){
    return false;
  }
  hx = rows;
  lx = 1;
  hy = cols;
  ly = 1;

  nx = hx - lx + 1;
  ny = hy - ly + 1;
  nz = 1;     //MapCECK格式的测量数据只有一层
  nData=nx*ny*nz;

  //分配初始化内存
  DoseAbs = new float[nData];
  NormDose = new float[nData];

  //Initialize
  for(i=0;i<nData;i++){
    DoseAbs[i] = 0.0;
    NormDose[i] = 0.0;
  }
  dosemax = -10000000;
  dosemin = 10000000;


  while(getline(in,tempStr)){

    if(exp_DataLabel.find(tempStr.begin(),&length,position) != -1){

       getline(in,tempStr);   //a invalid string"Ycm ROW"

       for(i=0;i<rows;i++){

          in>>tempData;     //two invalid numbers
          in>>tempData;

          for(j=0;j<cols;j++){

             in>>tempData;
             DoseAbs[totalN] = tempData;

             if(dosemin>tempData)
               dosemin = tempData;
             if(dosemax<tempData)
               dosemax = tempData;

             totalN++;
          }
       }

       break;  //finish the dose reading
    }

  }

  for(i=0;i<nData;i++){   //百分相对剂量
    NormDose[i] = (DoseAbs[i]/dosemax)*100;
  }

  in.close();
  return true;
}

//--------------------------------------------------------------------
//void TDose::ReadDose(FILE *fp,int filetype)
//{
//  int i,j,k;
//  float zNo,*ptr,*ptrzc;
//
//  switch(filetype)
//  {
//    case 3:       //Matrix数据格式
//    {
//      //读文件头
//      fscanf(fp,"%d%d%d%d%d%d",&lx,&hx,&ly,&hy,&lz,&hz);
//      nx=hx-lx+1;
//      ny=hy-ly+1;
//      nz=1;      //暂前只读第一个切片的数据
//      nData=nx*ny*nz;
//
//      //分配初始化内存
//      DoseAbs = new float[nData];
//      NormDose = new float[nData];
//      for(i=0;i<nData;i++)
//        DoseAbs[i]=0.0;
//      for(i=0;i<nData;i++)
//        DoseAbs[i] = 0.0;
//      for(i=0;i<nData;i++)
//        NormDose[i] = 0.0;
//
//      //读数据
//      ptr=DoseAbs;
//      dosemax=0.0;
//      dosemin = 10000.0;
//      for(k=0;k<nz;k++)
//      {
//        fscanf(fp,"%f",&zNo);
//        for(j=0;j<ny;j++)
//        {
//          for(i=0;i<nx;i++)
//          {
//            fscanf(fp,"%f",ptr);
//            if(dosemax<*ptr)    //找最大值
//              dosemax=*ptr;
//            if((dosemin>*ptr)&&(*ptr!=0))    //找最小值
//              dosemin = *ptr;
//            ptr++;
//          }
//        }
//       }
//
//    for(i=0;i<nData;i++)      //百分相对剂量
//      NormDose[i] = (DoseAbs[i]/dosemax)*100;
//    }
//    break;
//
//    case 2:   //中测数据格式
//    {
//      char dot;
//      nx=40;
//      ny=40;
//      nz=1;      //暂前只读第一个切片的数据
//      nData=nx*ny*nz;
//
//      //分配初始化内存
//      DoseAbs = new float[nData];
//      NormDose = new float[nData];
//      for(i=0;i<nData;i++)
//        DoseAbs[i] = 0.0;
//      for(i=0;i<nData;i++)
//        NormDose[i] = 0.0;
//
//      //读数据
//      ptr=DoseAbs;
//      dosemax=0.0;
//      dosemin = 10000.0;
//      for(k=0;k<nz;k++)
//      {
//        fscanf(fp,"%f",&zNo);
//        for(j=0;j<ny;j++)
//        {
//          for(i=0;i<nx;i++)
//          {
//            fscanf(fp,"%f",ptr);
//            fscanf(fp,",",&dot); //中测数据中有个","号
//            if(dosemax<*ptr)    //找最大值
//              dosemax=*ptr;
//            if((dosemin>*ptr)&&(*ptr!=0))    //找最小值
//              dosemin = *ptr;
//            ptr++;
//          }
//        }
//       }
//
//    for(i=0;i<nData;i++)      //百分相对剂量
//      NormDose[i] = (DoseAbs[i]/dosemax)*100;
//    }
//    break;
//
//    default:
//     break;
//  }
//}

//------------------------------------------------------------------------

void TDose::SaveDose(char *file)
{
  FILE *fp;
  int i,j,k;
  float zNo,*ptr;

  fp=fopen(file,"w");
  if(fp==NULL)
    return;

  fprintf(fp,"%-5d%-5d%-5d%-5d%-5d%-5d\n",lx,hx,ly,hy,lz,hz);
  ptr=DoseAbs;
  for(k=0;k<nz;k++)
  {
    zNo=k-(hz-lz)/2;
    fprintf(fp,"%-12.0f\n",zNo);
    for(j=0;j<ny;j++)
    {
      for(i=0;i<nx;i++)
      {
        fprintf(fp,"%12.4f",*ptr);
        ptr++;
      }
      fprintf(fp,"\n");
    }
  }
  fclose(fp);
}
//---------------------------------------------------------------------------
void TDose::Interpolationx(int fftype)
{
  if(fftype!=1)
    return;

  int firstdet; //用来记录每一行第一个探测器的位置
  int i,j,k,ii,jj,arr;

  for(j=0;j<=44;j++)     //沿横(行)向插值
  {
    firstdet = 0;
    for(k=0;k<=44;k++)    //寻找每一行第一个探测器的位置
    {
      //if(detector[j][k]==1)
      if(true == MainFormTempValue.detectorArray.at(j,k,0))
      {
        firstdet = k;
        break;
      }
    }

    for(i=0;i<firstdet;i++)    //每行开始到第一个探测器的每个点
    {
      NormDose[j*45+i] = (NormDose[j*45+firstdet])*(float(i)/firstdet);
      DoseAbs[j*45+i] = (DoseAbs[j*45+firstdet])*(float(i)/firstdet);
    }

    for(i=45-firstdet;i<45;i++)   //每行最后一个探测器到第45个点
    {
      NormDose[j*45+i]= (NormDose[j*45+44-firstdet])*(float(44-i)/firstdet);
      DoseAbs[j*45+i]= (DoseAbs[j*45+44-firstdet])*(float(44-i)/firstdet);
    }

    for(i=firstdet;i<=44;i++)  //每行第一个探测器和最后一个探测器
    {                                    //的中间没有探测器的点
      //if(detector[j][i]==1)
      if(true==MainFormTempValue.detectorArray.at(j,i,0))
      {
        for(ii=i+1;ii<=44;ii++)
        {
          //if(detector[j][ii]==1)
          if(true == MainFormTempValue.detectorArray.at(j,ii,0))
          {
            for(arr=i+1;arr<=ii-1;arr++)
            {
              NormDose[j*45+arr] = NormDose[j*45+i] + (arr-i)*(NormDose[j*45+ii]-NormDose[j*45+i])/float(ii-i);
              DoseAbs[j*45+arr] = DoseAbs[j*45+i] + (arr-i)*(DoseAbs[j*45+ii]-DoseAbs[j*45+i])/float(ii-i);
            }
            break;
          }
        }
      }
    }
  }

}

//-------------------------------------------------------------------------- -
/*void TDose::Interpolationy()
{
  int i,j,k,jj,arr;
  int firstnozero;

  for(i=0;i<=44;i++)
  {
    for(j=0;j<=44;j++)
    {
      if(Dosekind[j*45+i]>0.01)
      {
        for(jj=j+1;jj<=44;jj++)
        {
          if(Dosekind[jj*45+i]>0.01)
          {
            for(arr=j+1;arr<=jj-1;arr++)
            {
              Dosekind[arr*45+i] = Dosekind[j*45+i] + (arr-j)*(Dosekind[jj*45+i]-Dosekind[j*45+i])/float(jj-j);
            }
            break;
          }
        }
      }
    }
  }
} */
//----------------------------------------------------------------------------
void TDose::Interpolationy(int fftype)
{
  if(fftype != 1)
    return;

  int firstdet; //用来记录每一行第一个探测器的位置
  int i,j,k,ii,jj,arr;

  for(i=0;i<=44;i++)     //沿纵向插值
  {
    firstdet = 0;
    for(k=0;k<=44;k++)    //寻找每一列第一个探测器的位置
    {
      //if(detector[k][i]==1)
      if(true == MainFormTempValue.detectorArray.at(k,i,0))
      {
        firstdet = k;
        break;
      }
    }

    for(j=0;j<firstdet;j++)    //每列开始到第一个探测器的每个点
    {
      NormDose[j*45+i] = (NormDose[firstdet*45+i])*(j/float(firstdet));
      DoseAbs[j*45+i] = (DoseAbs[firstdet*45+i])*(j/float(firstdet));
    }

    for(j=45-firstdet;j<45;j++)   //每列最后一个探测器到第45个点
    {
      NormDose[j*45+i]= (NormDose[(44-firstdet)*45+i])*(44-j)/float(firstdet);
      DoseAbs[j*45+i]= (DoseAbs[(44-firstdet)*45+i])*(44-j)/float(firstdet);
    }

    for(j=firstdet;j<=44;j++)  //每列第一个探测器和最后一个探测器
    {                                    //的中间没有探测器的点
      //if(detector[j][i]==1)
      if(true == MainFormTempValue.detectorArray.at(j,i,0))
      {
        for(jj=j+1;jj<=44;jj++)
        {
          //if(detector[jj][i]==1)
          if(true == MainFormTempValue.detectorArray.at(jj,i,0))
          {
            for(arr=j+1;arr<=jj-1;arr++)
            {
              NormDose[arr*45+i] = NormDose[j*45+i] + (arr-j)*(NormDose[jj*45+i]-NormDose[j*45+i])/float(jj-j);
              DoseAbs[arr*45+i] = DoseAbs[j*45+i] + (arr-j)*(DoseAbs[jj*45+i]-DoseAbs[j*45+i])/float(jj-j);
            }
            break;
          }
        }
      }
    }
  }
}

//---------------------------双线性插值------------------------------------
void TDose::BlineInterp()
{
  vector<int> positiveSlopeSeries;
  vector<int> negativeSlopeSeries;
  int** neighbors;
  int x0,x1,x2,x3,y0,y1,y2,y3;
  float dpostive0,dpostive1,dpostive2,dpostive3;
  float dnegative0,dnegative1,dnegative2,dnegative3;

  for(int i=-34;i<=34;i=i+4)
  {
    positiveSlopeSeries.push_back(i);
  }

  for(int i=10;i<=78;i=i+4)
  {
    negativeSlopeSeries.push_back(i);
  }

  for(int j=0;j<=44;j++)
  {
    for(int i=0;i<=44;i++)
    {
      //if(detector[i][j] != 1)
      if(false == MainFormTempValue.detectorArray.at(i,j,0))
      {
         neighbors = FindFourBasePoints(i,j,positiveSlopeSeries,negativeSlopeSeries);

         if(NULL!=neighbors)
         {
           x0 = neighbors[0][0];
           y0 = neighbors[0][1];
           x1 = neighbors[1][0];
           y1 = neighbors[1][1];
           x2 = neighbors[2][0];
           y2 = neighbors[2][1];
           x3 = neighbors[3][0];
           y3 = neighbors[3][1];

             if(i>=13 && i<=31 && j>=13 && j<=31)
             {
               NormDose[j*45+i] = (NormDose[y0*45+x0] + NormDose[y1*45+x1] + NormDose[y2*45+x2] + NormDose[y3*45+x3])/4.0;
               DoseAbs[j*45+i] = (DoseAbs[y0*45+x0] + DoseAbs[y1*45+x1] + DoseAbs[y2*45+x2] + DoseAbs[y3*45+x3])/4.0;
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

               NormDose[j*45+i] = ((2*sqrt(2) - dpostive0)*(2*sqrt(2) - dnegative0)*NormDose[y0*45+x0] +
                                (2*sqrt(2) - dpostive1)*(2*sqrt(2) - dnegative1)*NormDose[y1*45+x1] +
                              (2*sqrt(2) - dpostive2)*(2*sqrt(2) - dnegative2)*NormDose[y2*45+x2] +
                              (2*sqrt(2) - dpostive3)*(2*sqrt(2) - dnegative3)*NormDose[y3*45+x3])/8.0;

               DoseAbs[j*45+i] = ((2*sqrt(2) - dpostive0)*(2*sqrt(2) - dnegative0)*DoseAbs[y0*45+x0] +
                             (2*sqrt(2) - dpostive1)*(2*sqrt(2) - dnegative1)*DoseAbs[y1*45+x1] +
                             (2*sqrt(2) - dpostive2)*(2*sqrt(2) - dnegative2)*DoseAbs[y2*45+x2] +
                             (2*sqrt(2) - dpostive3)*(2*sqrt(2) - dnegative3)*DoseAbs[y3*45+x3])/8.0;

             }

         }

      }

    }
  }


}

//-------------------双线性插值之前需要找到待插值点的四个基准点-------------------------
inline int** TDose::FindFourBasePoints(int x,int y,vector<int> positiveSlopeSeries,vector<int> negativeSlopeSeries)
{
  int neighborPointNum = 4; //four neighborhood points for bilinear interpolation
  int dimension = 2;        //dimension: x,y
  int** result = new int*[neighborPointNum];

  for(int i=0;i<neighborPointNum;i++)
  {
    result[i] = new int[dimension];

    //initial
    for(int j=0;j<dimension;j++)
    {
      result[i][j] = -1;   //default:-1
    }
  }

  int negativeSlopeIntercept,positiveSlopeIntercept;
  int negativeSlopeNeighbor[2] = {-100,-100};
  int positiveSlopeNeighbor[2] = {-100,-100};
  if(x>=13 && x<=31 && y>=13 && y<=31)    //MapCHECK内部的一个密集20乘20探测器阵列
  {
    result[0][0] = x - 1;
    result[0][1] = y;
    result[1][0] = x + 1;
    result[1][1] = y;
    result[2][0] = x;
    result[2][1] = y - 1;
    result[3][0] = x;
    result[3][1] = y + 1;
  }
  else
  {
     negativeSlopeIntercept = y + x;
     positiveSlopeIntercept = y - x;
     neighbor(negativeSlopeIntercept,negativeSlopeSeries,0,negativeSlopeSeries.size()-1,negativeSlopeNeighbor);
     neighbor(positiveSlopeIntercept,positiveSlopeSeries,0,positiveSlopeSeries.size()-1,positiveSlopeNeighbor);

     if(negativeSlopeNeighbor[0] != -100 && negativeSlopeNeighbor[1] != -100 && positiveSlopeNeighbor[0] != -100  && positiveSlopeNeighbor[1] != -100)
     {
       result[0][0] = (negativeSlopeNeighbor[0] - positiveSlopeNeighbor[0])/2; //x0
       result[0][1] = (negativeSlopeNeighbor[0] + positiveSlopeNeighbor[0])/2; //y0

       result[1][0] = (negativeSlopeNeighbor[0] - positiveSlopeNeighbor[1])/2; //x1
       result[1][1] = (negativeSlopeNeighbor[0] + positiveSlopeNeighbor[1])/2; //y1

       result[2][0] = (negativeSlopeNeighbor[1] - positiveSlopeNeighbor[0])/2; //x2
       result[2][1] = (negativeSlopeNeighbor[1] + positiveSlopeNeighbor[0])/2; //y2

       result[3][0] = (negativeSlopeNeighbor[1] - positiveSlopeNeighbor[1])/2; //x3
       result[3][1] = (negativeSlopeNeighbor[1] + positiveSlopeNeighbor[1])/2; //y3

     }
     else  //not find a rhombus
     {
       return NULL;
     }

  }

  for(int i=0;i<neighborPointNum;i++)
  {
    for(int j=0;j<dimension;j++)
    {
      if(result[i][j]<0 || result[i][j]>=45)
      {
        return NULL;
      }
    }
  }

  return result;
}

//----------------------------------------------------------------------------
//在众多斜率为1和-1的探测器排列线簇中找到待插值点所最相邻的两个斜探测器线(探测器刚好在这两个斜探测器线之间)
inline void TDose::neighbor(int num,vector<int> Series,int start,int end,int* result)
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

//-------------------------------------------------------------
//-----------------------规律图形矩阵的双线性插值-------------
