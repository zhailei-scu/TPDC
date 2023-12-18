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

        fscanf(fp,",",NULL); //�в��������и�","��
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
bool TDose::LoadDIDose(char *file, float hardwarepixel)  //��DICOM�ļ����ļ���,Ӳ����̽������������ش�С��
{
  //ӳ���������������
  frame=0,row=0,col=0;     //��ά����,����������
  int i,j,num,numb;
  bool isbreak; //��Ϊ���ѭ���жϵı��
  double* pdata;
  double piexlspace[2],origin[3];
  double posrow,poscol;  //posrowΪ��ƽ���ϸ�����ԭ����ƽ���ԭ��(0,0)��i�����ϲ��˶�����(��һ��Ϊ�������п���Ϊ0.5,1.5��)
                         //poscolΪ��ƽ���ϸ�����ԭ����ƽ���ԭ��(0,0)��j�����ϲ��˶�����(��һ��Ϊ�������п���Ϊ0.5,1.5��)

  double d1,d2,d3,d4;
  double a,b,c,d;
  int normpoint;//���������ĵ�
  double normdata;  //��һ������ֵ

  opennew(file);
  pdata = ReadDatanew(frame,row,col);  //��DICOM�ļ��ж�ֵ����ȡ��frame,row��col��ֵ
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

  origin[0] = -piexlspace[0]*(row-1)/2.0; //֮ǰһֱ��Ϊ�ȼ������ĵ㣨�������ĵ��ԭ��(0,0)��
  origin[1] = -piexlspace[1]*(col-1)/2.0; //ΪDICOM�ӿ��е�ReadOrigin�����������ݣ�������ʵ�ϣ�MapCheck
  origin[2] = 0;                         //��ΪĬ�ϵĵȼ������ĵ�(0,0)����DICOM�ļ���������

  switch(measureFileType)
  {
    case 0:  //��DICOM���ݶ�Ӧ�Ĳ�������Ϊ�в�Ĳ������ݣ���ô���ĵ㴦û��̽�����㣬������ʱҪ�����ĵ����һ��̽�����㿪ʼ����(1/2)gridsize
    {
      segments = 6; ////��ʱDICOM����ϸ��Ϊ6��(7.2mm/6=1.2mm)
      recordsegments = segments;

      float originnew[2];
      originnew[0] = origin[0] + hardwarepixel/2.0;  //��DICOM�ļ����ģ���ǰ1/2��hardwarepixelΪ��ʱ�ĵ�һ�������
      originnew[1] = origin[1] + hardwarepixel/2.0;  //ע��origin[]Ϊ��������+1/2��hardwarepixel�൱����ǰ1/2��hardwarepixel
      irange = 1+ segments*(floor(((row-1)*piexlspace[0]+originnew[0])/hardwarepixel)+ floor(-originnew[0]/hardwarepixel)); //ע��origin[]Ϊ��ֵ
      jrange = 1+ segments*(floor(((col-1)*piexlspace[1]+originnew[1])/hardwarepixel)+ floor(-originnew[1]/hardwarepixel)); //ע��origin[]Ϊ��ֵ

      nData = irange*jrange;

      ifirst =  segments*floor((-originnew[0])/hardwarepixel);  //����ͼ�����Ķ�������·���һ�������̽�������Ӧ����ӳ���
      jfirst =  segments*floor((-originnew[1])/hardwarepixel);  //��������ϵ�е�λ��(��0����)

      icenter =  ifirst + 3;
      jcenter =  jfirst + 3;  //ӳ��֮�����������е�(0,0)�����������������е��к���(��0����)(ֻΪ��ͼ�ã�����ʱ������Ȼ��ifirst��jfirst)


      //icenter =  segments*floor((-originnew[0])/hardwarepixel);
      //jcenter =  segments*floor((-originnew[1])/hardwarepixel);//ӳ��֮�����������е�(0,0)�����������������е��к���(��0����)

      DoseAbs = new float[nData];
      NormDose = new float[nData];

      numb = 0;

      for(j=0;j<jrange;j++)
      {
        poscol = (-originnew[1]-(jfirst-j)*(hardwarepixel/segments))/piexlspace[1];

        for(i=0;i<irange;i++)
        {
           //posrowΪ��ƽ���ϸ�����ԭ����ƽ���ԭ��(0,0)��i�����ϲ��˶�����(��һ��Ϊ�������п���Ϊ0.5,1.5��)
          posrow = (-originnew[0] - (ifirst -i)*(hardwarepixel/segments))/piexlspace[0];

          d1 = posrow -floor(posrow);
          d2 = poscol -floor(poscol);
          d3 = 1 - d2;
          d4 = 1 - d1;
          a = pdata[col*(int)floor(poscol) + (int)floor(posrow)];
          b = pdata[col*(int)floor(poscol) + (int)ceil(posrow)];
          c = pdata[col*(int)ceil(poscol) + (int)floor(posrow)];
          d = pdata[col*(int)ceil(poscol) + (int)ceil(posrow)];

          DoseAbs[numb] = ((a*d4 + b*d1)*d3 + (c*d4 + d*d1)*d2)*100;  //������ӳ�䵽����������
          //pDIDose[numb] = (a*d4 + c*d1)*d3 + (b*d4 + d*d1)*d2;
          numb++;

        }
      }

      normpoint =jfirst*irange + ifirst;   // �ȼ������ĵ�

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
      //normdata = pDIDose[normpoint]; //��������ʱ��������ѡȡDICOM�ж�������ĵ������Ϊ���ֵ���������ڲ���ƽ����ѡȡ���ֵ��Ϊ��һ����(���ֵΪ100%)��������������̫��ѧ(����˵DICOM���ĵ㴦��ֵΪ���ֵ��10%����ô���������Ϊ��һ���ĵ㣬��ôDICOMƽ�����кܶ����Լ����ᳬ��100%�����ֵ����Լ�����ﵽ1000%��������Ϊ����������ƽ���һ���Ľ��������󣬲����޴����)

      //Ĭ������£�DICOM����֮��ѡ��������ֵ����Ϊ��һ���㣨������������ʱѡ��DICOM�ж�������ĵ������Ϊ���ֵ������������ͬ����Ҫ���ڲ���ƽ����ѡȡ���ֵ��Ϊ��һ����(���ֵΪ100%)������ѡ��DICOM�ж�������ĵ������Ϊ���ֵ��̫��ѧ(����˵DICOM���ĵ㴦��ֵΪ���ֵ��10%����ô���������Ϊ��һ���ĵ㣬��ôDICOMƽ�����кܶ����Լ����ᳬ��100%�����ֵ����Լ�����ﵽ1000%��������Ϊ����������ƽ���һ���Ľ��������󣬲����޴����)��
      num = 0;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          NormDose[num] = 100*DoseAbs[num]/normdata; //ת��Ϊ�ٷ���Լ���
          num++;
        }
      }


      //�Ҽ���ȥ��0.000000֮����½�
      num = 0;
      isbreak = false;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[num]>0.01)
          {
            cuthoriz[0] = j+4;  //�ҵ�0.01֮���������ƶ�4����Ϊ�±߽�
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


      //�Ҽ���ȥ��0.000000֮����Ͻ�
      isbreak = false;
      for(j=jrange-1;j>=0;j--)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[j*irange+i]>0.01)
          {
            cuthoriz[1] = j-4;  //�ҵ�0.01֮���������ƶ�4����Ϊ�±߽�(��ν����������������ı��еķ���)
            isbreak = true;
            break;
          }
        }


        if(isbreak == true)
        {
          break;
        }
      }


      //�Ҽ���ȥ��0.000000֮�����߽�
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

      //�Ҽ���ȥ��0.000000֮����ұ߽�
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

    case 1:  //��DICOM���ݶ�Ӧ�Ĳ�������ΪMapCHECK��ʽ�������ݣ����ڶ�Ӧ�Ĳ����������ĵ�պ�Ϊ��֪��(��̽����)�����Դ����ĵ㿪ʼ�������
    {
      segments = 5;  //��ʱ��DICOM����ϸ��Ϊ5��(5mm/5=1mm)
      recordsegments = segments;

      irange = 1+ segments*(floor(((row-1)*piexlspace[0]+origin[0])/hardwarepixel)+ floor(-origin[0]/hardwarepixel)); //ע��origin[]Ϊ��ֵ
      jrange = 1+ segments*(floor(((col-1)*piexlspace[1]+origin[1])/hardwarepixel)+ floor(-origin[1]/hardwarepixel)); //ע��origin[]Ϊ��ֵ

      nData = irange*jrange;

      ifirst =  segments*floor((-origin[0])/hardwarepixel);
      jfirst =  segments*floor((-origin[1])/hardwarepixel);

      icenter =  segments*floor((-origin[0])/hardwarepixel);
      jcenter =  segments*floor((-origin[1])/hardwarepixel);//ӳ��֮�����������е�(0,0)�����������������е��к���

      DoseAbs = new float[nData];
      NormDose = new float[nData];

      numb = 0;

      for(j=0;j<jrange;j++)
      {
        poscol = (-origin[1]-(jfirst-j)*(hardwarepixel/segments))/piexlspace[1];

        for(i=0;i<irange;i++)
        {
          //posrowΪ��ƽ���ϸ�����ԭ����ƽ���ԭ��(0,0)��i�����ϲ��˶�����(��һ��Ϊ�������п���Ϊ0.5,1.5��)
          posrow = (-origin[0] - (ifirst -i)*(hardwarepixel/segments))/piexlspace[0];

          d1 = posrow -floor(posrow);
          d2 = poscol -floor(poscol);
          d3 = 1 - d2;
          d4 = 1 - d1;
          a = pdata[col*(int)floor(poscol) + (int)floor(posrow)];
          b = pdata[col*(int)floor(poscol) + (int)ceil(posrow)];
          c = pdata[col*(int)ceil(poscol) + (int)floor(posrow)];
          d = pdata[col*(int)ceil(poscol) + (int)ceil(posrow)];

          DoseAbs[numb] = ((a*d4 + b*d1)*d3 + (c*d4 + d*d1)*d2)*100;  //������ӳ�䵽����������
          //pDIDose[numb] = (a*d4 + c*d1)*d3 + (b*d4 + d*d1)*d2;
          numb++;

        }
      }

      normpoint =jfirst*irange + ifirst;   // �ȼ������ĵ�


      //��Ĭ�ϣ�Ĭ������£�DICOM����֮��ѡ��������ֵ����Ϊ��һ���㣨������������ʱѡ��DICOM�ж�������ĵ������Ϊ���ֵ������������ͬ����Ҫ���ڲ���ƽ����ѡȡ���ֵ��Ϊ��һ����(���ֵΪ100%)������ѡ��DICOM�ж�������ĵ������Ϊ���ֵ��̫��ѧ(����˵DICOM���ĵ㴦��ֵΪ���ֵ��10%����ô���������Ϊ��һ���ĵ㣬��ôDICOMƽ�����кܶ����Լ����ᳬ��100%�����ֵ����Լ�����ﵽ1000%��������Ϊ����������ƽ���һ���Ľ��������󣬲����޴����)��
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
      //normdata = DoseAbs[normpoint]; //��������ʱ��������ѡȡDICOM�ж�������ĵ������Ϊ���ֵ���������ڲ���ƽ����ѡȡ���ֵ��Ϊ��һ����(���ֵΪ100%)��������������̫��ѧ(����˵DICOM���ĵ㴦��ֵΪ���ֵ��10%����ô���������Ϊ��һ���ĵ㣬��ôDICOMƽ�����кܶ����Լ����ᳬ��100%�����ֵ����Լ�����ﵽ1000%��������Ϊ����������ƽ���һ���Ľ��������󣬲����޴����)

      //Ĭ������£�DICOM����֮��ѡ��������ֵ����Ϊ��һ���㣨������������ʱѡ��DICOM�ж�������ĵ������Ϊ���ֵ������������ͬ����Ҫ���ڲ���ƽ����ѡȡ���ֵ��Ϊ��һ����(���ֵΪ100%)������ѡ��DICOM�ж�������ĵ������Ϊ���ֵ��̫��ѧ(����˵DICOM���ĵ㴦��ֵΪ���ֵ��10%����ô���������Ϊ��һ���ĵ㣬��ôDICOMƽ�����кܶ����Լ����ᳬ��100%�����ֵ����Լ�����ﵽ1000%��������Ϊ����������ƽ���һ���Ľ��������󣬲����޴����)��
      num = 0;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          NormDose[num] = 100*DoseAbs[num]/normdata; //ת��Ϊ�ٷ���Լ���
          num++;
        }
      }


      //�Ҽ���ȥ��0.000000֮����½�
      num = 0;
      isbreak = false;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[num]>0.01)
          {
            cuthoriz[0] = j+4;  //�ҵ�0.01֮���������ƶ�4����Ϊ�±߽�
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


      //�Ҽ���ȥ��0.000000֮����Ͻ�
      isbreak = false;
      for(j=jrange-1;j>=0;j--)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[j*irange+i]>0.01)
          {
            cuthoriz[1] = j-4;  //�ҵ�0.01֮���������ƶ�4����Ϊ�±߽�(��ν����������������ı��еķ���)
            isbreak = true;
            break;
          }
        }


        if(isbreak == true)
        {
          break;
        }
      }


      //�Ҽ���ȥ��0.000000֮�����߽�
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

      //�Ҽ���ȥ��0.000000֮����ұ߽�
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

    case 2:  //Matrix��������
    {
      //segments = ; //δ���
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
  tempDoseArray = ReadDatanew(heights,rows,cols);  //��DICOM�ļ��ж�ֵ����ȡ��frame,row��col��ֵ
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
 // GetArray(ftype); //�ȵõ�̽����������Ϣ
  NormDose=NULL;
  DoseAbs=NULL;


  dosemax=0.0;

  //FileType=ftype; //0��ʾMapCheck�������и�ʽ��1��ʾDICOM���ļ���ʽ,2��ʾ�в����ݸ�ʽ��3��ʾMatrix���ݸ�ʽ

  switch(ftype)
  {
    case 0:             //�в�����
    {
      LoadZCDose(file);
    }
    break;

    case 1:            //MapCheck����
    {
      LoadMapCHECKDose(file);
      //Interpolationx(ftype);
      //Interpolationy(ftype);
      BlineInterp();
    }
    break;

    case 3:             //Matrix����
    {
      LoadMatrixDose(file);
    }
    break;

    case 11:              //DICOM��ʽ�ļ�������
    {
      LoadDIDose(file,gridsize);
    }
    break;

    case 12:            //SCU��ʽ�ļ�������
    {
      //δ���
    }
    break;

    default:
      break;
  }

  */
}

//---------------------------------------------------------------
bool TDose::LoadDIDose(char *file, float hardwarepixel)  //��DICOM�ļ����ļ���,Ӳ����̽������������ش�С��
{
   /*
  //ӳ���������������

  frame=0,row=0,col=0;     //��ά����,����������
  int i,j,num,numb;
  bool isbreak; //��Ϊ���ѭ���жϵı��
  double* pdata;
  double piexlspace[2],origin[3];
  double posrow,poscol;  //posrowΪ��ƽ���ϸ�����ԭ����ƽ���ԭ��(0,0)��i�����ϲ��˶�����(��һ��Ϊ�������п���Ϊ0.5,1.5��)
                         //poscolΪ��ƽ���ϸ�����ԭ����ƽ���ԭ��(0,0)��j�����ϲ��˶�����(��һ��Ϊ�������п���Ϊ0.5,1.5��)

  double d1,d2,d3,d4;
  double a,b,c,d;
  int normpoint;//���������ĵ�
  double normdata;  //��һ������ֵ

  opennew(file);
  pdata = ReadDatanew(frame,row,col);  //��DICOM�ļ��ж�ֵ����ȡ��frame,row��col��ֵ
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

  origin[0] = -piexlspace[0]*(row-1)/2.0; //֮ǰһֱ��Ϊ�ȼ������ĵ㣨�������ĵ��ԭ��(0,0)��
  origin[1] = -piexlspace[1]*(col-1)/2.0; //ΪDICOM�ӿ��е�ReadOrigin�����������ݣ�������ʵ�ϣ�MapCheck
  origin[2] = 0;                         //��ΪĬ�ϵĵȼ������ĵ�(0,0)����DICOM�ļ���������


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
    case 0:  //��DICOM���ݶ�Ӧ�Ĳ�������Ϊ�в�Ĳ������ݣ���ô���ĵ㴦û��̽�����㣬������ʱҪ�����ĵ����һ��̽�����㿪ʼ����(1/2)gridsize
    {
      segments = 6; ////��ʱDICOM����ϸ��Ϊ6��(7.2mm/6=1.2mm)
      recordsegments = segments;

      float originnew[2];
      originnew[0] = origin[0] + hardwarepixel/2.0;  //��DICOM�ļ����ģ���ǰ1/2��hardwarepixelΪ��ʱ�ĵ�һ�������
      originnew[1] = origin[1] + hardwarepixel/2.0;  //ע��origin[]Ϊ��������+1/2��hardwarepixel�൱����ǰ1/2��hardwarepixel
      irange = 1+ segments*(floor(((row-1)*piexlspace[0]+originnew[0])/hardwarepixel)+ floor(-originnew[0]/hardwarepixel)); //ע��origin[]Ϊ��ֵ
      jrange = 1+ segments*(floor(((col-1)*piexlspace[1]+originnew[1])/hardwarepixel)+ floor(-originnew[1]/hardwarepixel)); //ע��origin[]Ϊ��ֵ

      nData = irange*jrange;

      ifirst =  segments*floor((-originnew[0])/hardwarepixel);  //����ͼ�����Ķ�������·���һ�������̽�������Ӧ����ӳ���
      jfirst =  segments*floor((-originnew[1])/hardwarepixel);  //��������ϵ�е�λ��(��0����)

      icenter =  ifirst + 3;
      jcenter =  jfirst + 3;  //ӳ��֮�����������е�(0,0)�����������������е��к���(��0����)(ֻΪ��ͼ�ã�����ʱ������Ȼ��ifirst��jfirst)


      //icenter =  segments*floor((-originnew[0])/hardwarepixel);
      //jcenter =  segments*floor((-originnew[1])/hardwarepixel);//ӳ��֮�����������е�(0,0)�����������������е��к���(��0����)

      DoseAbs = new float[nData];
      NormDose = new float[nData];

      numb = 0;

      for(j=0;j<jrange;j++)
      {
        poscol = (-originnew[1]-(jfirst-j)*(hardwarepixel/segments))/piexlspace[1];

        for(i=0;i<irange;i++)
        {
           //posrowΪ��ƽ���ϸ�����ԭ����ƽ���ԭ��(0,0)��i�����ϲ��˶�����(��һ��Ϊ�������п���Ϊ0.5,1.5��)
          posrow = (-originnew[0] - (ifirst -i)*(hardwarepixel/segments))/piexlspace[0];

          d1 = posrow -floor(posrow);
          d2 = poscol -floor(poscol);
          d3 = 1 - d2;
          d4 = 1 - d1;
          a = pdata[col*(int)floor(poscol) + (int)floor(posrow)];
          b = pdata[col*(int)floor(poscol) + (int)ceil(posrow)];
          c = pdata[col*(int)ceil(poscol) + (int)floor(posrow)];
          d = pdata[col*(int)ceil(poscol) + (int)ceil(posrow)];

          DoseAbs[numb] = ((a*d4 + b*d1)*d3 + (c*d4 + d*d1)*d2)*100;  //������ӳ�䵽����������
          //pDIDose[numb] = (a*d4 + c*d1)*d3 + (b*d4 + d*d1)*d2;
          numb++;

        }
      }

      normpoint =jfirst*irange + ifirst;   // �ȼ������ĵ�

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
      //normdata = pDIDose[normpoint]; //��������ʱ��������ѡȡDICOM�ж�������ĵ������Ϊ���ֵ���������ڲ���ƽ����ѡȡ���ֵ��Ϊ��һ����(���ֵΪ100%)��������������̫��ѧ(����˵DICOM���ĵ㴦��ֵΪ���ֵ��10%����ô���������Ϊ��һ���ĵ㣬��ôDICOMƽ�����кܶ����Լ����ᳬ��100%�����ֵ����Լ�����ﵽ1000%��������Ϊ����������ƽ���һ���Ľ��������󣬲����޴����)

      //Ĭ������£�DICOM����֮��ѡ��������ֵ����Ϊ��һ���㣨������������ʱѡ��DICOM�ж�������ĵ������Ϊ���ֵ������������ͬ����Ҫ���ڲ���ƽ����ѡȡ���ֵ��Ϊ��һ����(���ֵΪ100%)������ѡ��DICOM�ж�������ĵ������Ϊ���ֵ��̫��ѧ(����˵DICOM���ĵ㴦��ֵΪ���ֵ��10%����ô���������Ϊ��һ���ĵ㣬��ôDICOMƽ�����кܶ����Լ����ᳬ��100%�����ֵ����Լ�����ﵽ1000%��������Ϊ����������ƽ���һ���Ľ��������󣬲����޴����)��
      num = 0;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          NormDose[num] = 100*DoseAbs[num]/normdata; //ת��Ϊ�ٷ���Լ���
          num++;
        }
      }


      //�Ҽ���ȥ��0.000000֮����½�
      num = 0;
      isbreak = false;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[num]>0.01)
          {
            cuthoriz[0] = j+4;  //�ҵ�0.01֮���������ƶ�4����Ϊ�±߽�
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


      //�Ҽ���ȥ��0.000000֮����Ͻ�
      isbreak = false;
      for(j=jrange-1;j>=0;j--)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[j*irange+i]>0.01)
          {
            cuthoriz[1] = j-4;  //�ҵ�0.01֮���������ƶ�4����Ϊ�±߽�(��ν����������������ı��еķ���)
            isbreak = true;
            break;
          }
        }


        if(isbreak == true)
        {
          break;
        }
      }


      //�Ҽ���ȥ��0.000000֮�����߽�
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

      //�Ҽ���ȥ��0.000000֮����ұ߽�
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

    case 1:  //��DICOM���ݶ�Ӧ�Ĳ�������ΪMapCHECK��ʽ�������ݣ����ڶ�Ӧ�Ĳ����������ĵ�պ�Ϊ��֪��(��̽����)�����Դ����ĵ㿪ʼ�������
    {
      segments = 5;  //��ʱ��DICOM����ϸ��Ϊ5��(5mm/5=1mm)
      recordsegments = segments;

      irange = 1+ segments*(floor(((row-1)*piexlspace[0]+origin[0])/hardwarepixel)+ floor(-origin[0]/hardwarepixel)); //ע��origin[]Ϊ��ֵ
      jrange = 1+ segments*(floor(((col-1)*piexlspace[1]+origin[1])/hardwarepixel)+ floor(-origin[1]/hardwarepixel)); //ע��origin[]Ϊ��ֵ

      nData = irange*jrange;

      ifirst =  segments*floor((-origin[0])/hardwarepixel);
      jfirst =  segments*floor((-origin[1])/hardwarepixel);

      icenter =  segments*floor((-origin[0])/hardwarepixel);
      jcenter =  segments*floor((-origin[1])/hardwarepixel);//ӳ��֮�����������е�(0,0)�����������������е��к���

      DoseAbs = new float[nData];
      NormDose = new float[nData];

      numb = 0;

      for(j=0;j<jrange;j++)
      {
        poscol = (-origin[1]-(jfirst-j)*(hardwarepixel/segments))/piexlspace[1];

        for(i=0;i<irange;i++)
        {
          //posrowΪ��ƽ���ϸ�����ԭ����ƽ���ԭ��(0,0)��i�����ϲ��˶�����(��һ��Ϊ�������п���Ϊ0.5,1.5��)
          posrow = (-origin[0] - (ifirst -i)*(hardwarepixel/segments))/piexlspace[0];

          d1 = posrow -floor(posrow);
          d2 = poscol -floor(poscol);
          d3 = 1 - d2;
          d4 = 1 - d1;
          a = pdata[col*(int)floor(poscol) + (int)floor(posrow)];
          b = pdata[col*(int)floor(poscol) + (int)ceil(posrow)];
          c = pdata[col*(int)ceil(poscol) + (int)floor(posrow)];
          d = pdata[col*(int)ceil(poscol) + (int)ceil(posrow)];

          DoseAbs[numb] = ((a*d4 + b*d1)*d3 + (c*d4 + d*d1)*d2)*100;  //������ӳ�䵽����������
          //pDIDose[numb] = (a*d4 + c*d1)*d3 + (b*d4 + d*d1)*d2;
          numb++;

        }
      }

      normpoint =jfirst*irange + ifirst;   // �ȼ������ĵ�


      //��Ĭ�ϣ�Ĭ������£�DICOM����֮��ѡ��������ֵ����Ϊ��һ���㣨������������ʱѡ��DICOM�ж�������ĵ������Ϊ���ֵ������������ͬ����Ҫ���ڲ���ƽ����ѡȡ���ֵ��Ϊ��һ����(���ֵΪ100%)������ѡ��DICOM�ж�������ĵ������Ϊ���ֵ��̫��ѧ(����˵DICOM���ĵ㴦��ֵΪ���ֵ��10%����ô���������Ϊ��һ���ĵ㣬��ôDICOMƽ�����кܶ����Լ����ᳬ��100%�����ֵ����Լ�����ﵽ1000%��������Ϊ����������ƽ���һ���Ľ��������󣬲����޴����)��
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
      //normdata = DoseAbs[normpoint]; //��������ʱ��������ѡȡDICOM�ж�������ĵ������Ϊ���ֵ���������ڲ���ƽ����ѡȡ���ֵ��Ϊ��һ����(���ֵΪ100%)��������������̫��ѧ(����˵DICOM���ĵ㴦��ֵΪ���ֵ��10%����ô���������Ϊ��һ���ĵ㣬��ôDICOMƽ�����кܶ����Լ����ᳬ��100%�����ֵ����Լ�����ﵽ1000%��������Ϊ����������ƽ���һ���Ľ��������󣬲����޴����)

      //Ĭ������£�DICOM����֮��ѡ��������ֵ����Ϊ��һ���㣨������������ʱѡ��DICOM�ж�������ĵ������Ϊ���ֵ������������ͬ����Ҫ���ڲ���ƽ����ѡȡ���ֵ��Ϊ��һ����(���ֵΪ100%)������ѡ��DICOM�ж�������ĵ������Ϊ���ֵ��̫��ѧ(����˵DICOM���ĵ㴦��ֵΪ���ֵ��10%����ô���������Ϊ��һ���ĵ㣬��ôDICOMƽ�����кܶ����Լ����ᳬ��100%�����ֵ����Լ�����ﵽ1000%��������Ϊ����������ƽ���һ���Ľ��������󣬲����޴����)��
      num = 0;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          NormDose[num] = 100*DoseAbs[num]/normdata; //ת��Ϊ�ٷ���Լ���
          num++;
        }
      }


      //�Ҽ���ȥ��0.000000֮����½�
      num = 0;
      isbreak = false;
      for(j=0;j<jrange;j++)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[num]>0.01)
          {
            cuthoriz[0] = j+4;  //�ҵ�0.01֮���������ƶ�4����Ϊ�±߽�
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


      //�Ҽ���ȥ��0.000000֮����Ͻ�
      isbreak = false;
      for(j=jrange-1;j>=0;j--)
      {
        for(i=0;i<irange;i++)
        {
          if(NormDose[j*irange+i]>0.01)
          {
            cuthoriz[1] = j-4;  //�ҵ�0.01֮���������ƶ�4����Ϊ�±߽�(��ν����������������ı��еķ���)
            isbreak = true;
            break;
          }
        }


        if(isbreak == true)
        {
          break;
        }
      }


      //�Ҽ���ȥ��0.000000֮�����߽�
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

      //�Ҽ���ȥ��0.000000֮����ұ߽�
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

    case 2:  //Matrix��������
    {
      //segments = ; //δ���
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
bool TDose::LoadDIDose(char *file)    //��DICOM�ļ�������ʱ���Ϊ1mm
{

  /*   //ֻ��ԭʼֵ����ӳ���������������
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
  //ӳ���������������
  frame=0,col=0,row=0;
  int i,j,num,numb;
  bool isbreak; //��Ϊ���ѭ���жϵı��
  double* pdata;
  double piexlspace[2],origin[3],npoint[3];
  double posrow,poscol;

  double d1,d2,d3,d4;
  double a,b,c,d;
  int normpoint;//���ĵ�(���ﵱ����һ����)
  double normdata;  //��һ������ֵ

  opennew(file);
  pdata = ReadDatanew(frame,row,col);  //��DICOM�ļ��ж�ֵ
  ReadPixelSpacenew(piexlspace);

  ReadNormaPointnew(npoint);
  ReadDoseGridScalingnew();

  theunits = ReadDoseUnitsnew();

  origin[0] = -piexlspace[0]*(row-1)/2.0; //֮ǰһֱ��Ϊ�ȼ������ĵ㣨�������ĵ��ԭ��(0,0)��
  origin[1] = -piexlspace[1]*(col-1)/2.0; //ΪDICOM�ӿ��е�ReadOrigin�����������ݣ�������ʵ�ϣ�MapCheck
  origin[2] = 0;

  theunits = ReadDoseUnitsnew();

  irange = floor(row*piexlspace[1]);
  jrange = floor(col*piexlspace[0]);

  nData = irange*jrange;

  icenter = floor(-origin[1]) + 1;
  jcenter = floor(-origin[0]) + 1;//ӳ��֮�����������е�(0,0)�����������������е��к���

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

      pDIDose[numb] = ((a*d4 + c*d1)*d3 + (b*d4 + d*d1)*d2)*100;  //������ӳ�䵽����������
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


  //�Ҽ���ȥ��0.000000֮����Ͻ�
  num = 0;
  isbreak = false;
  for(i=0;i<irange;i++)
  {
    for(j=0;j<jrange;j++)
    {
      if(NormDI[num]>0.01)
      {
        cuthoriz[0] = i;  //�ҵ�0.01֮���������ƶ�4����Ϊ�ϱ߽�
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


  //�Ҽ���ȥ��0.000000֮����½�
  isbreak = false;
  for(i=irange-1;i>=0;i--)
  {
    for(j=0;j<jrange;j++)
    {
      if(NormDI[i*jrange+j]>0.01)
      {
        cuthoriz[1] = i;  //�ҵ�0.01֮���������ƶ�4����Ϊ�±߽�(��ν����������������ı��еķ���)
        isbreak = true;
        break;
      }
    }


    if(isbreak == true)
    {
      break;
    }
  }

  //�Ҽ���ȥ��0.000000֮�����߽�
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

  //�Ҽ���ȥ��0.000000֮����ұ߽�
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
  nz=1;      //��ǰֻ����һ����Ƭ������
  nData=nx*ny*nz;

  //�����ʼ���ڴ�
  DoseAbs = new float[nData];
  NormDose = new float[nData];
  for(i=0;i<nData;i++)
    DoseAbs[i] = 0.0;
  for(i=0;i<nData;i++)
    NormDose[i] = 0.0;

  //������
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
        fscanf(fp,",",&dot); //�в��������и�","��
        if(dosemax<*ptr)    //�����ֵ
          dosemax=*ptr;
        if((dosemin>*ptr)&&(*ptr!=0))    //����Сֵ
          dosemin = *ptr;
        ptr++;
      }
    }
  }

  for(i=0;i<nData;i++)      //�ٷ���Լ���
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

  //���ļ�ͷ
  fscanf(fp,"%d%d%d%d%d%d",&lx,&hx,&ly,&hy,&lz,&hz);
  nx=hx-lx+1;
  ny=hy-ly+1;
  nz=1;      //��ǰֻ����һ����Ƭ������
  nData=nx*ny*nz;

  //�����ʼ���ڴ�
  DoseAbs = new float[nData];
  NormDose = new float[nData];
  for(i=0;i<nData;i++)
    DoseAbs[i]=0.0;
  for(i=0;i<nData;i++)
    NormDose[i] = 0.0;

  //������
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
        if(dosemax<*ptr)    //�����ֵ
          dosemax=*ptr;
        if((dosemin>*ptr)&&(*ptr!=0))    //����Сֵ
          dosemin = *ptr;
        ptr++;
      }
    }
  }

  for(i=0;i<nData;i++)      //�ٷ���Լ���
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
  TRegexp exp_Rows("^Rows:");     //ʹ��������ʽƥ������
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
  nz = 1;     //MapCECK��ʽ�Ĳ�������ֻ��һ��
  nData=nx*ny*nz;

  //�����ʼ���ڴ�
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

  for(i=0;i<nData;i++){   //�ٷ���Լ���
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
//    case 3:       //Matrix���ݸ�ʽ
//    {
//      //���ļ�ͷ
//      fscanf(fp,"%d%d%d%d%d%d",&lx,&hx,&ly,&hy,&lz,&hz);
//      nx=hx-lx+1;
//      ny=hy-ly+1;
//      nz=1;      //��ǰֻ����һ����Ƭ������
//      nData=nx*ny*nz;
//
//      //�����ʼ���ڴ�
//      DoseAbs = new float[nData];
//      NormDose = new float[nData];
//      for(i=0;i<nData;i++)
//        DoseAbs[i]=0.0;
//      for(i=0;i<nData;i++)
//        DoseAbs[i] = 0.0;
//      for(i=0;i<nData;i++)
//        NormDose[i] = 0.0;
//
//      //������
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
//            if(dosemax<*ptr)    //�����ֵ
//              dosemax=*ptr;
//            if((dosemin>*ptr)&&(*ptr!=0))    //����Сֵ
//              dosemin = *ptr;
//            ptr++;
//          }
//        }
//       }
//
//    for(i=0;i<nData;i++)      //�ٷ���Լ���
//      NormDose[i] = (DoseAbs[i]/dosemax)*100;
//    }
//    break;
//
//    case 2:   //�в����ݸ�ʽ
//    {
//      char dot;
//      nx=40;
//      ny=40;
//      nz=1;      //��ǰֻ����һ����Ƭ������
//      nData=nx*ny*nz;
//
//      //�����ʼ���ڴ�
//      DoseAbs = new float[nData];
//      NormDose = new float[nData];
//      for(i=0;i<nData;i++)
//        DoseAbs[i] = 0.0;
//      for(i=0;i<nData;i++)
//        NormDose[i] = 0.0;
//
//      //������
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
//            fscanf(fp,",",&dot); //�в��������и�","��
//            if(dosemax<*ptr)    //�����ֵ
//              dosemax=*ptr;
//            if((dosemin>*ptr)&&(*ptr!=0))    //����Сֵ
//              dosemin = *ptr;
//            ptr++;
//          }
//        }
//       }
//
//    for(i=0;i<nData;i++)      //�ٷ���Լ���
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

  int firstdet; //������¼ÿһ�е�һ��̽������λ��
  int i,j,k,ii,jj,arr;

  for(j=0;j<=44;j++)     //�غ�(��)���ֵ
  {
    firstdet = 0;
    for(k=0;k<=44;k++)    //Ѱ��ÿһ�е�һ��̽������λ��
    {
      //if(detector[j][k]==1)
      if(true == MainFormTempValue.detectorArray.at(j,k,0))
      {
        firstdet = k;
        break;
      }
    }

    for(i=0;i<firstdet;i++)    //ÿ�п�ʼ����һ��̽������ÿ����
    {
      NormDose[j*45+i] = (NormDose[j*45+firstdet])*(float(i)/firstdet);
      DoseAbs[j*45+i] = (DoseAbs[j*45+firstdet])*(float(i)/firstdet);
    }

    for(i=45-firstdet;i<45;i++)   //ÿ�����һ��̽��������45����
    {
      NormDose[j*45+i]= (NormDose[j*45+44-firstdet])*(float(44-i)/firstdet);
      DoseAbs[j*45+i]= (DoseAbs[j*45+44-firstdet])*(float(44-i)/firstdet);
    }

    for(i=firstdet;i<=44;i++)  //ÿ�е�һ��̽���������һ��̽����
    {                                    //���м�û��̽�����ĵ�
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

  int firstdet; //������¼ÿһ�е�һ��̽������λ��
  int i,j,k,ii,jj,arr;

  for(i=0;i<=44;i++)     //�������ֵ
  {
    firstdet = 0;
    for(k=0;k<=44;k++)    //Ѱ��ÿһ�е�һ��̽������λ��
    {
      //if(detector[k][i]==1)
      if(true == MainFormTempValue.detectorArray.at(k,i,0))
      {
        firstdet = k;
        break;
      }
    }

    for(j=0;j<firstdet;j++)    //ÿ�п�ʼ����һ��̽������ÿ����
    {
      NormDose[j*45+i] = (NormDose[firstdet*45+i])*(j/float(firstdet));
      DoseAbs[j*45+i] = (DoseAbs[firstdet*45+i])*(j/float(firstdet));
    }

    for(j=45-firstdet;j<45;j++)   //ÿ�����һ��̽��������45����
    {
      NormDose[j*45+i]= (NormDose[(44-firstdet)*45+i])*(44-j)/float(firstdet);
      DoseAbs[j*45+i]= (DoseAbs[(44-firstdet)*45+i])*(44-j)/float(firstdet);
    }

    for(j=firstdet;j<=44;j++)  //ÿ�е�һ��̽���������һ��̽����
    {                                    //���м�û��̽�����ĵ�
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

//---------------------------˫���Բ�ֵ------------------------------------
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

//-------------------˫���Բ�ֵ֮ǰ��Ҫ�ҵ�����ֵ����ĸ���׼��-------------------------
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
  if(x>=13 && x<=31 && y>=13 && y<=31)    //MapCHECK�ڲ���һ���ܼ�20��20̽��������
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
//���ڶ�б��Ϊ1��-1��̽���������ߴ����ҵ�����ֵ���������ڵ�����б̽������(̽�����պ���������б̽������֮��)
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
//-----------------------����ͼ�ξ����˫���Բ�ֵ-------------
