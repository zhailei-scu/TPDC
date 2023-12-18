#include "Util.h"
#include "LogFrame.h"
#include "regexp.h"
#include "registry.hpp"
#include <math.h>
//------------------------Class:RWLockImpl------------------------------------
RWLockImpl::RWLockImpl(){
  this->readers_count = 0;
  this->writers_count = 0;
  this->count_writersWaiting = 0;

  this->variableMutex = CreateMutex(NULL, FALSE, NULL);
  if (NULL == this->variableMutex){
    RunningLog::writeLog("cannot create reader/writer lock" + __LINE__);
  }

  readEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
  if (NULL == this->readEvent){
    RunningLog::writeLog("cannot create reader/writer lock" + __LINE__);
  }

  writeEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
  if (NULL == this->writeEvent){
    RunningLog::writeLog("cannot create reader/writer lock" + __LINE__);
  }
}                                            

RWLockImpl::~RWLockImpl(){
  CloseHandle(this->variableMutex);
  CloseHandle(this->readEvent);
  CloseHandle(this->writeEvent);

  this->readers_count = 0;
  this->writers_count = 0;
  this->count_writersWaiting = 0;
}

inline void RWLockImpl::AddWriter(){
  switch (WaitForSingleObject(this->variableMutex,INFINITE))
  {
    case WAIT_OBJECT_0:
    {
      if (++this->count_writersWaiting == 1){
        ResetEvent(this->readEvent);
      }
      ReleaseMutex(this->variableMutex);
    }
    break;
    default:
    {
      RunningLog::writeLog("cannot lock reader/writer lock" + __LINE__);
    }
    break;
  }
}

inline void RWLockImpl::RemoveWriter(){
  switch (WaitForSingleObject(this->variableMutex,INFINITE))
  {
    case WAIT_OBJECT_0:
    {
      if (--this->count_writersWaiting == 0 && 0 == this->writers_count){
        SetEvent(this->readEvent);
      }
      ReleaseMutex(this->variableMutex);
    }
    break;
    default:
    {
      RunningLog::writeLog("cannot lock reader/writer lock" + __LINE__);
    }
    break;
  }
}

void RWLockImpl::ReadLockImpl(){
  HANDLE h[2];
  h[0] = this->variableMutex;
  h[1] = this->readEvent;
  switch (WaitForMultipleObjects(2, h, TRUE, INFINITE))
  {
    case WAIT_OBJECT_0:
    {
      ++this->readers_count;
      ResetEvent(this->writeEvent);
      ReleaseMutex(this->variableMutex);
      assert(this->writers_count == 0);
    }
    break;
    default:
    {
      RunningLog::writeLog("cannot lock reader/writer lock" + __LINE__);
    }
    break;
  }
}

bool RWLockImpl::TryReadLockImpl()
{
  for (;;){
    if (0 != this->writers_count || 0!= this->count_writersWaiting ){
      return false;
    }

    DWORD result = TryReadLockOnce();
    switch(result)
    {
      case WAIT_OBJECT_0:
      case WAIT_OBJECT_0 + 1:
      {
        return true;
      }
      break;
      case WAIT_TIMEOUT:{
        continue;
      }
      break;
      default:
      {
        RunningLog::writeLog("cannot lock reader/writer lock" + __LINE__);
      }
      break;
    }
  }
}

void RWLockImpl::WriteLockImpl(){
  AddWriter();
  HANDLE h[2];
  h[0] = this->variableMutex;
  h[1] = this->writeEvent;
  switch (WaitForMultipleObjects(2,h,TRUE,INFINITE))
  {
    case WAIT_OBJECT_0:
    {
      --this->count_writersWaiting;
      ++this->readers_count;
      ++this->writers_count;
      ResetEvent(this->readEvent);
      ResetEvent(this->writeEvent);
      ReleaseMutex(this->variableMutex);
      assert(this->writers_count == 1);
    }
    break;
    default:
    {
      RemoveWriter();
      RunningLog::writeLog("cannot lock reader/writer lock" ,__LINE__);
    }
    break;
  }

}

bool RWLockImpl::TryWriteLockImpl(){
  AddWriter();
  HANDLE h[2];
  h[0] = this->variableMutex;
  h[1] = this->writeEvent;
  switch (WaitForMultipleObjects(2,h,TRUE,1))
  {
    case WAIT_OBJECT_0:
    {
      --this->count_writersWaiting;
      ++this->readers_count;
      ++this->writers_count;
      ResetEvent(this->readEvent);
      ResetEvent(this->writeEvent);
      ReleaseMutex(this->variableMutex);
      assert(this->writers_count == 1);
      return true;
    }
    break;

    case WAIT_TIMEOUT:
    {
      RemoveWriter();
    }
    break;
    default:
    {
      RemoveWriter();
      RunningLog::writeLog("cannot lock reader/writer lock", __LINE__);
    }
    break;

  }
  return false;
}

void RWLockImpl::UnlockImpl(){
  switch(WaitForSingleObject(this->variableMutex,INFINITE))
  {
    case WAIT_OBJECT_0:
    {
      this->writers_count = 0;
      if(0==this->count_writersWaiting){
         SetEvent(this->readEvent);
      }

      if(--this->readers_count == 0){
        SetEvent(this->writeEvent);
      }
      ReleaseMutex(this->variableMutex);
    }
    break;
    default:
    {
      RunningLog::writeLog("cannot unlock reader/writer lock" , __LINE__);
    }
    break;
  }
}

DWORD RWLockImpl::TryReadLockOnce(){
  HANDLE h[2];
  h[0] = this->variableMutex;
  h[1] = this->readEvent;
  DWORD result = WaitForMultipleObjects(2, h, TRUE, 1);
  switch (result)
  {
    case WAIT_OBJECT_0:
    {
      ++this->readers_count;
      ResetEvent(this->writeEvent);
      ReleaseMutex(this->variableMutex);
      assert(this->writers_count == 0);
      return result;
    }
    break;
    case WAIT_TIMEOUT:
    default:
    {
      RunningLog::writeLog("cannot lock reader/writer lock" , __LINE__);
    }
    break;
  }
  return result;
}
//--------------------Class:PhysicalPoint--------------------------
/*Constructor:Default*/
PhysicalPoint::PhysicalPoint(){
 this->x = -1; //-1:not indicated
 this->y = -1;
 this->z = -1;
}
/*Constructor:Parameter*/
PhysicalPoint::PhysicalPoint(double x,double y,double z){
  this->x = x;
  this->y = y;
  this->z = z;
}

/*Destructor*/
PhysicalPoint::~PhysicalPoint(){
  //nothing to do
}

/*Copy constructor*/
PhysicalPoint::PhysicalPoint(const PhysicalPoint& r){
  this->x = r.x;
  this->y = r.y;
  this->z = r.z;
}

/*Overload operator*/
PhysicalPoint PhysicalPoint::operator = (const PhysicalPoint& r){
  this->x = r.x;
  this->y = r.y;
  this->z = r.z;

  return *this;
}

void PhysicalPoint::reset(){
  this->x = -1;
  this->y = -1;
  this->z = -1;
}


//-----------------------------Class:GridPoit-----------------------
/*Constructor:Default*/
GridPoint::GridPoint(){
  this->row = -1; //0 not indicated
  this->col = -1;
  this->level = -1;
}

/*Constructor:Parameter*/
GridPoint::GridPoint(int row,int col,int level){
  this->row = row;
  this->col = col;
  this->level = level;
}

/*Destructor*/
GridPoint::~GridPoint(){
  //nothing to do
}

/*Copy constructor*/
GridPoint::GridPoint(const GridPoint& r){
  if(NULL != &r){
    this->row = r.row;
    this->col = r.col;
    this->level = r.level;
  }else{
    this->row = -1;
    this->col = -1;
    this->level = -1;
  }
}

/*Overload operator*/
GridPoint GridPoint::operator = (const GridPoint& r){
  if(NULL != &r){
    this->row = r.row;
    this->col = r.col;
    this->level = r.level;
  }else{
    this->row = -1;
    this->col = -1;
    this->level = -1;
  }

  return *this;
}

//--------------GridPoint:Other functions
void GridPoint::setValue(int _row,int _col, int _level){
  this->row = _row;
  this->col = _col;
  this->level = _level;
}

void GridPoint::reset(){
  this->row = -1;
  this->col = -1;
  this->level = -1;
}

//-----------Get the suitable segments for each gridsize
int getGridSegments(double gridsize){
  int result;
  if(gridsize<0){
    result = -1;
  }
  else if(gridsize<1.01){
    result = 1;
  }
  else{
    result = TrimFloat_Up(gridsize,0.02);
  }
  return result;
}

//--------------------GetFormated System Time-----------------
string formatTime(){

  SYSTEMTIME time;
  GetLocalTime(&time);

  ostringstream ostr;
  ostr << time.wYear << "-" << time.wMonth << "-" << time.wDay << "-"
       << time.wHour<<":"<<time.wMinute<<":"<<time.wSecond<<":milliSecond:"<<time.wMilliseconds;
  return ostr.str();
}


//------------------------------Interpolation-----------------------------------
//------------------------------------双线性插值----------------------------------------
float* __fastcall regularBinearInterploate(float *array,int &row,int &col,int multi)
{
  if(multi<=0)
  {
    return NULL;
  }

  if(NULL == array)
  {
    return NULL;
  }
  int back_row = row;
  int back_col = col;
  row = (row-1)*multi + 1;
  col = (col-1)*multi + 1;

  float *result = new float[row*col];

  int count = 0;

  for(int j=0;j<row;j++)
  {
    for(int i=0;i<col;i++)
    {
       if(i%multi!=0 || j%multi!=0)
       {
         result[count] = ((multi - i%multi)*(multi - j%multi)*array[(j/multi)*back_col + (i/multi)] +
                         (i%multi)*(multi - j%multi)*array[(j/multi)*back_col + ((i/multi+1)<back_col?(i/multi+1):(back_col-1))] +
                         (multi - i%multi)*(j%multi)*array[((j/multi+1)<back_row?((j/multi+1)):(back_row-1))*back_col + (i/multi)] +
                         (i%multi)*(j%multi)*array[((j/multi+1)<back_row?((j/multi+1)):(back_row-1))*back_col + ((i/multi+1)<back_col?(i/multi+1):(back_col-1))])/(multi*multi);
       }
       else
       {
         result[count] = array[(j/multi)*back_col + (i/multi)];
       }
       count++;
    }
  }

  return result;

}

//-------------------------------------------------------------------------------------
//--------------------------------双三次插值-------------------------------------------
float* __fastcall BicubicInterploate(float *array,int &row,int &col,int multi)
{
  if(multi<=0)
  {
    return NULL;
  }

  if(NULL == array)
  {
    return NULL;
  }
  int back_row = row;
  int back_col = col;
  row = (row-1)*multi + 1;
  col = (col-1)*multi + 1;

  float *result = new float[row*col];
  float B[4][4];
  int count = 0;
  float u = 0.0;
  float v = 0.0;

  for(int j=0;j<row;j++)
  {
    for(int i=0;i<col;i++)
    {
       if(i%multi!=0 || j%multi!=0)
       {

       /*
         result[count] = ((multi - i%multi)*(multi - j%multi)*array[(j/multi)*back_col + (i/multi)] +
                         (i%multi)*(multi - j%multi)*array[(j/multi)*back_col + ((i/multi+1)<back_col?(i/multi+1):(back_col-1))] +
                         (multi - i%multi)*(j%multi)*array[((j/multi+1)<back_row?((j/multi+1)):(back_row-1))*back_col + (i/multi)] +
                         (i%multi)*(j%multi)*array[((j/multi+1)<back_row?((j/multi+1)):(back_row-1))*back_col + ((i/multi+1)<back_col?(i/multi+1):(back_col-1))])/(multi*multi);
       */
         if((i/multi)>=1 && (i/multi)<=(back_col-3) && (j/multi)>=1 && (j/multi)<=(back_row-3))
         {
           u = (j%multi)/((float)multi);
           v = (i%multi)/((float)multi);
           B[0][0] = array[(j/multi-1)*back_col + (i/multi-1)];   B[0][1] = array[(j/multi-1)*back_col + (i/multi)];  B[0][2] = array[(j/multi-1)*back_col + (i/multi+1)];  B[0][3] = array[(j/multi-1)*back_col + (i/multi + 2)];
           B[1][0] = array[(j/multi)*back_col + (i/multi-1)];     B[1][1] = array[(j/multi)*back_col + (i/multi)];    B[1][2] = array[(j/multi)*back_col + (i/multi+1)];    B[1][3] = array[(j/multi)*back_col + (i/multi + 2)];
           B[2][0] = array[(j/multi+1)*back_col + (i/multi-1)];   B[2][1] = array[(j/multi+1)*back_col + (i/multi)];  B[2][2] = array[(j/multi+1)*back_col + (i/multi+1)];  B[2][3] = array[(j/multi+1)*back_col + (i/multi + 2)];
           B[3][0] = array[(j/multi+2)*back_col + (i/multi-1)];   B[3][1] = array[(j/multi+2)*back_col + (i/multi)];  B[3][2] = array[(j/multi+2)*back_col + (i/multi+1)];  B[3][3] = array[(j/multi+2)*back_col + (i/multi + 2)];
           result[count] = getBicubicValue(u,v,B);

         }
         else //use the binear interpolation in boundary row:0 to (multi-1)|| ((back_row-3)*multi+1) to ((back_row-1)*multi+1)
         {    //                                         col:0 to (multi-1)|| ((back_col-3)*multi+1) to ((back_col-1)*multi+1)
           result[count] = ((multi - i%multi)*(multi - j%multi)*array[(j/multi)*back_col + (i/multi)] +
                         (i%multi)*(multi - j%multi)*array[(j/multi)*back_col + ((i/multi+1)<back_col?(i/multi+1):(back_col-1))] +
                         (multi - i%multi)*(j%multi)*array[((j/multi+1)<back_row?((j/multi+1)):(back_row-1))*back_col + (i/multi)] +
                         (i%multi)*(j%multi)*array[((j/multi+1)<back_row?((j/multi+1)):(back_row-1))*back_col + ((i/multi+1)<back_col?(i/multi+1):(back_col-1))])/(multi*multi);
         }
       }
       else
       {
         result[count] = array[(j/multi)*back_col + (i/multi)];
       }
       count++;
    }
  }

  return result;
}

//-----------------------------------------------------------------------------------------
//-------------------------使用双三次插值来获取某个待插值点的值---------------------------
//-------算法的详细说明可以参考[1] 贾永红.数字图像处理[M].武汉:武汉大学出版社,2003:108-110.
//-------------------------or--[2] SONKA M,HLAVAC V,BOYLE R.Image processing,analysis and machine vision,international student edition[M].3rd ed.Toronto:Thomson Learning,2007:122-123.
//-------------------------or--[3] 翟磊，黄宁，王鹏，范轶翔，夏翔，吴庆星.基于梯度特征的调强放疗计划剂量插值算法.生物医学工程学杂志.2016, 33(6): 1116-1123. doi: 10.7507/1001-5515.20160178
float __fastcall getBicubicValue(float u,float v,float B[4][4])
{

  float A[4] = {getBicubicParam(1+u),getBicubicParam(u),getBicubicParam(1-u),getBicubicParam(2-u)};
  float C[4] = {getBicubicParam(1+v),getBicubicParam(v),getBicubicParam(1-v),getBicubicParam(2-v)};

  /* A*B */
  float AB[4] = {0.0,0.0,0.0,0.0};
  for(int i=0;i<4;i++)
  {
    for(int j=0;j<4;j++)
    {
      AB[i] += A[j]*B[j][i];
    }
  }

  /* A*B*C */
  float ABC = 0.0;
  for(int i=0;i<4;i++)
  {
    ABC += AB[i]*C[i];
  }

  return ABC;

}

float __fastcall getBicubicParam(float uorV)
{
  //
  float result = 0.0;
  float absUorV = fabs(uorV);
  if(absUorV<1.0)
  {
    result = pow(absUorV,3) - 2*pow(absUorV,2) + 1;
  }
  else if(absUorV<2.0)
  {
    result = (-1)*pow(absUorV,3) + 5*pow(absUorV,2) - 8*absUorV + 4;
  }
  else
  {
    result = 0.0;
  }
  return result;
}

//----------------------------高斯平滑处理(5阶)-----------------------------------------
void GaussianSmoothingOrderFive(MatrixData<double> *matrixData)
{
  int orders = 5; //5阶模板
  int row = matrixData->getRowLength();
  int col = matrixData->getColLength();
  int height = matrixData->getHeightLength();

  MatrixData<double> *record = new MatrixData<double>(row,col,height);
  *record = *matrixData;

  //5阶模板
  int templates[5][5] = {{1, 4,  7,  4,  1},
                         {4, 16, 26, 16, 4},
                         {7, 26, 41, 26, 7},
                         {4, 16, 26, 16, 4},
                         {1, 4,  7,  4,  1}};

  float tempResult = 0.0;

  //int count = 0;
  for(int j=0;j<row;j++)
  {
    for(int i=0;i<col;i++)
    {
      if(j<=1 || j>=(row-2) || i<=1 || i>=(col-2))    //首尾一行/一列不作模糊处理
      {
        //result[count] = array[j*col + i];
        matrixData->modifyValue(i,j,0,record->at(i,j,0));
      }
      else
      {
        tempResult = 0.0;
        for(int templateRow = 0;templateRow<orders;templateRow++)
        {
          for(int templateCol = 0;templateCol<orders;templateCol++)
          {
            //tempResult += array[(j+templateRow-2)*col+i+templateCol-2]*templates[templateRow][templateCol];
            tempResult += record->at(i+templateCol-2,j+templateRow-2,0)*templates[templateRow][templateCol];
          }
        }
        //result[count] = tempResult/273.0;
        matrixData->modifyValue(i,j,0,tempResult/273.0);
      }

      //count++;
    }

  }

  TryToDelete< MatrixData<double> >(record);
  record = NULL;

}

//----------------------------高斯平滑处理(3阶)-----------------------------------------
void GaussianSmoothingOrderThree(MatrixData<double> *matrixData)
{
  /*3阶模板*/

  int templates[3][3] = {{1, 2, 1},
                         {2, 4, 2},
                         {1, 2, 1}};
  int orders = 3; //3阶模板

  int row = matrixData->getRowLength();
  int col = matrixData->getColLength();
  int height = matrixData->getHeightLength();

  MatrixData<double> *record = new MatrixData<double>(row,col,height);
  *record = *matrixData;

  float tempResult = 0.0;

  //int count = 0;
  for(int j=0;j<row;j++)
  {
    for(int i=0;i<col;i++)
    {
      if(j<=0 || j>=(row-1) || i<=0 || i>=(col-1))    //首尾一行/一列不作模糊处理
      {
        //result[count] = array[j*col + i];
        matrixData->modifyValue(i,j,0,record->at(i,j,0));
      }
      else
      {
        tempResult = 0.0;
        for(int templateRow = 0;templateRow<orders;templateRow++)
        {
          for(int templateCol = 0;templateCol<orders;templateCol++)
          {
            //tempResult += array[(j+templateRow-1)*col+i+templateCol-1]*templates[templateRow][templateCol];
            tempResult += record->at(i+templateCol-1,j+templateRow-1,0)*templates[templateRow][templateCol];
          }
        }
        //result[count] = tempResult/16.0;
        matrixData->modifyValue(i,j,0,tempResult/16.0);
      }

      //count++;
    }

  }

  TryToDelete< MatrixData<double> >(record);
  record = NULL;

}

//------------------------------中值平滑(滤波)----------------------------------
void midValueSmoothing(MatrixData<double> *matrixData,const int orders)
{
  int downHalf  = (orders-1)/2;         //若以每一个待平滑点为中心，那么一个大小为orders*orders的滤波窗口在其下的行数
  int leftHalf  = (orders-1)/2;         //若以每一个待平滑点为中心，那么一个大小为orders*orders的滤波窗口在其左的列数
  int upHalf    = orders - downHalf - 1;//若以每一个待平滑点为中心，那么一个大小为orders*orders的滤波窗口在其上的行数
  int rightHalf = orders - leftHalf - 1;//若以每一个待平滑点为中心，那么一个大小为orders*orders的滤波窗口在其右的列数

  int row = matrixData->getRowLength();
  int col = matrixData->getColLength();
  int height = matrixData->getHeightLength();

  MatrixData<double> *record = new MatrixData<double>(row,col,height);
  *record = *matrixData;

  float tempResult = 0.0;

  float* NeighborValues = new float[orders*orders];

  //int count = 0;
  for(int j=0;j<row;j++)
  {
    for(int i=0;i<col;i++)
    {
      if(j<downHalf || j>=(row-upHalf) || i<leftHalf || i>=(col-rightHalf))   //首尾downHalf,upHalf行/leftHalf,rightHalf列不作模糊处理
      {
        //result[count] = array[j*col + i];
        matrixData->modifyValue(i,j,0,record->at(i,j,0));
      }
      else
      {
        tempResult = 0.0;
        for(int templateRow = 0;templateRow<orders;templateRow++)
        {
          for(int templateCol = 0;templateCol<orders;templateCol++)
          {
            //NeighborValues[templateRow*orders + templateCol] = array[(j+templateRow-downHalf)*col+i+templateCol-leftHalf];
            NeighborValues[templateRow*orders + templateCol] = record->at(i+templateCol-leftHalf,j+templateRow-downHalf,0);
          }
        }
        //quickSort(NeighborValues,0,orders*orders-1);
        newQuickSortFloat(NeighborValues,orders*orders);
        //result[count] = NeighborValues[(orders*orders-1)/2];
        matrixData->modifyValue(i,j,0,NeighborValues[(orders*orders-1)/2]);
      }

      //count++;
    }

  }

  TryToDelete< MatrixData<double> >(record);
  record = NULL;

  TryToDelete<float>(NeighborValues);
  NeighborValues = NULL;

}

//------------------------------均值滤波----------------------------------
void averageSmoothing(MatrixData<double> *matrixData,const int orders)
{
  int downHalf  = (orders-1)/2;         //若以每一个待平滑点为中心，那么一个大小为orders*orders的滤波窗口在其下的行数
  int leftHalf  = (orders-1)/2;         //若以每一个待平滑点为中心，那么一个大小为orders*orders的滤波窗口在其左的列数
  int upHalf    = orders - downHalf - 1;//若以每一个待平滑点为中心，那么一个大小为orders*orders的滤波窗口在其上的行数
  int rightHalf = orders - leftHalf - 1;//若以每一个待平滑点为中心，那么一个大小为orders*orders的滤波窗口在其右的列数

  int row = matrixData->getRowLength();
  int col = matrixData->getColLength();
  int height = matrixData->getHeightLength();

  MatrixData<double> *record = new MatrixData<double>(row,col,height);
  *record = *matrixData;

  float tempResult = 0.0;

  //int count = 0;
  for(int j=0;j<row;j++)
  {
    for(int i=0;i<col;i++)
    {
      if(j<downHalf || j>=(row-upHalf) || i<leftHalf || i>=(col-rightHalf))   //首尾downHalf,upHalf行/leftHalf,rightHalf列不作模糊处理
      {
        //result[count] = array[j*col + i];
        matrixData->modifyValue(i,j,0,record->at(i,j,0));
      }
      else
      {
        tempResult = 0.0;
        for(int templateRow = 0;templateRow<orders;templateRow++)
        {
          for(int templateCol = 0;templateCol<orders;templateCol++)
          {
            tempResult += record->at(i+templateCol-leftHalf,j+templateRow-downHalf,0);
          }
        }
        //result[count] = tempResult/((float)(orders*orders));
        matrixData->modifyValue(i,j,0,tempResult/((float)(orders*orders)));
      }

      //count++;
    }

  }

  TryToDelete< MatrixData<double> >(record);
  record = NULL;
}

//------------------------------双边滤波-----------------------------------
float* bilateralSmoothing(float* array,int row,int col)
{
  return NULL;
}

//-----------------------------Trim float:Up---------------------------------
int TrimFloat_Up(double value,double standard){
  int result = -1;

  if(standard>1.0 || standard<0){
    RunningLog::writeLog("The TrimFloat is not suitable",__LINE__);
    return result;
  }


  if((ceil(value) - value)<standard){
    result = ceil(value);
  }else if( (value - floor(value))<standard){
    result = floor(value);
  }else if( (ceil(value) - value)> standard){
    result = ceil(value);
  }

  return result;
}

//-----------------------------Trim float:Down---------------------------------
int TrimFloat_Down(double value,double standard){
  int result = -1;

  if(standard>1.0 || standard<0){
    RunningLog::writeLog("The TrimFloat is not suitable",__LINE__);
    return result;
  }


  if((ceil(value) - value)<standard){
    result = ceil(value);
  }else if((value - floor(value))<standard){
    result = floor(value);
  }else if( (ceil(value) - value)> standard){
    result = floor(value);
  }

  return result;
}

//--------------If a float Value has a vibration Integer Central-------------------
bool floatValue_hasVibrationCentral(double value,double standard){
  bool result = false;
  int TrimDown = TrimFloat_Down(value,standard);
  int TrimUp = TrimFloat_Up(value,standard);
  if( TrimDown== TrimUp){
    result = true; //or result = -1
  }

  return result;

}

//-------------------------------------对齐并细化---------------------------------------
//对齐和细化一起进行的原因:一方面如毕业论文所述，这样避免在做Best5时每一次都要重新细化，加快计算速度
//-------------------------另一方面，同时进行可以利用原有的的原始数据在细化时进行双线性插值，避免使用对齐之后的数据进行双线性插值，提高计算精度-------
void alignmentAndSegment(MatrixData<double>* targetMatrix,double targetGridSize[2],PhysicalPoint targetPhysicCental,GridPoint& targetFirstAlignmentGridCentral,
               MatrixData<double>* todoMatrix,double todoGridSize[2],PhysicalPoint& todoPhysicCental,GridPoint& todoFirstAlignmentGridCentral,int segments[2],HANDLE_MODEL model){
  double originNew[2];
  int rowRange;
  int colRange;
  double floatVerbStand = 0.02;
  double posRow;//posRow/posCol为新平面上各点与原数据平面的原点(0,0)在i方向上差了多少行/列(不一定为整数，有可能为0.5,1.5行/列)
  double posCol;

  double a,b,c,d,d1,d2,d3,d4;

  double trimedFloatTodoGridSize[2];
  
  double todoRowSize = (todoMatrix->getRowLength()-1)*todoGridSize[0];
  double todoColSize = (todoMatrix->getColLength()-1)*todoGridSize[1];
  int targetRowLeftIntegerGrid = TrimFloat_Down(targetPhysicCental.x/targetGridSize[0],floatVerbStand);
  int targetColBottomIntegerGrid = TrimFloat_Down(targetPhysicCental.y/targetGridSize[1],floatVerbStand);
  double rowSegmentSize = targetGridSize[0]/segments[0];
  double colSegmentSize = targetGridSize[1]/segments[1];

  //若测量平面的剂量中心刚好位于某一个整行列位置点(如MapCHECK)，则对齐时从这个点开始向两边扩散
  //若测量平面的剂量中心位于一个非整行列位置点(如MD-1600)，则对齐时从这个点前面最近的一个整行列位置点开始向两边扩散
  //row
  if(floatValue_hasVibrationCentral(targetPhysicCental.x/targetGridSize[0],floatVerbStand)){
    //the dose central just located on a row line
    originNew[0] = todoPhysicCental.x;

  }else{
    //the dose central not located on a row line,so select the first row line before the dose central
    originNew[0] = todoPhysicCental.x - (targetPhysicCental.x - targetGridSize[0]*targetRowLeftIntegerGrid);

    if(originNew[0]<0){  //out of boundary
      //----------Little possible Case------------------------
      RunningLog::writeLog("The Central point is too away from central and nearby the boundary",__LINE__);
      return;
    }
  }
  rowRange =1 + segments[0]*(TrimFloat_Down(originNew[0]/targetGridSize[0],floatVerbStand)
                          +TrimFloat_Down((todoRowSize - originNew[0])/targetGridSize[0],floatVerbStand));

  todoFirstAlignmentGridCentral.row = segments[0]*TrimFloat_Down(originNew[0]/targetGridSize[0],floatVerbStand);
  todoPhysicCental.x = todoPhysicCental.x - originNew[0] + targetGridSize[0]*TrimFloat_Down(originNew[0]/targetGridSize[0],floatVerbStand);

  targetFirstAlignmentGridCentral.row = targetRowLeftIntegerGrid;

  //col
  if(floatValue_hasVibrationCentral(targetPhysicCental.y/targetGridSize[1],floatVerbStand)){
    //the dose central just located on a col line
    originNew[1] = todoPhysicCental.y;
  }else{
    //the dose central not located on a col line,so select the first col line before the dose central
    originNew[1] = todoPhysicCental.y - (targetPhysicCental.y - targetGridSize[1]*targetColBottomIntegerGrid);

    if(originNew[1]<0){  //out of boundary
      //----------Little possible Case------------------------
      RunningLog::writeLog("The Central point is too away from central and nearby the boundary",__LINE__);
      return;
    }
  }

  colRange =1 + segments[1]*(TrimFloat_Down(originNew[1]/targetGridSize[1],floatVerbStand)
                          +TrimFloat_Down((todoColSize - originNew[1])/targetGridSize[1],floatVerbStand));

  todoFirstAlignmentGridCentral.col = segments[1]*TrimFloat_Down(originNew[1]/targetGridSize[1],floatVerbStand);
  todoPhysicCental.y = todoPhysicCental.y - originNew[1] + targetGridSize[1]*TrimFloat_Down(originNew[1]/targetGridSize[1],floatVerbStand);

  targetFirstAlignmentGridCentral.col = targetColBottomIntegerGrid;


   //For ADAC(MapCHECK) model, the plan gridsize 0.9568..... is trimed to 0.957 in below operator

  switch(model)
  {
    case HANDLE_MODEL(SNDAC):
    {
      trimedFloatTodoGridSize[0] = todoGridSize[0];
      trimedFloatTodoGridSize[1] = todoGridSize[1];
    }
    break;

    case HANDLE_MODEL(ADAC):
    default:
    {
      trimedFloatTodoGridSize[0] = doubleTrim(todoGridSize[0],3);
      trimedFloatTodoGridSize[1] = doubleTrim(todoGridSize[1],3);
    }
    break;
  }


  MatrixData<double>* result = new MatrixData<double>(rowRange,colRange,1);
  for(int j=0;j<colRange;j++){
    posCol = (originNew[1] - (todoFirstAlignmentGridCentral.col - j)*colSegmentSize)/trimedFloatTodoGridSize[1];
    for(int i=0;i<rowRange;i++){
      posRow = (originNew[0] - (todoFirstAlignmentGridCentral.row - i)*rowSegmentSize)/trimedFloatTodoGridSize[0];
      d1 = posRow - floor(posRow);
      d2 = posCol - floor(posCol);
      d3 = 1 - d2;
      d4 = 1 - d1;
      a = todoMatrix->at((int)floor(posRow),(int)floor(posCol),0);
      b = todoMatrix->at((int)ceil(posRow),(int)floor(posCol),0);
      c = todoMatrix->at((int)floor(posRow),(int)ceil(posCol),0);
      d = todoMatrix->at((int)ceil(posRow),(int)ceil(posCol),0);
      result->modifyValue(i,j,0,(a*d4 + b*d1)*d3 + (c*d4 + d*d1)*d2);
    }
  }
  *todoMatrix = *result;

  TryToDelete< MatrixData<double> >(result);

  result = NULL;
}


void matrixDataDataCutoff(MatrixData<double>& data,MatrixData<int>& cutBian,double cutoffStandard){
  if(NULL == &data){
    RunningLog::writeLog("The data is NULL.",__LINE__);
    return;
  }
  if(NULL == &cutBian){
    RunningLog::writeLog("The cutBian is NULL.",__LINE__);
    return;
  }
  bool isbreak = false;
  int rows = data.getRowLength();
  int cols = data.getColLength();

  cutBian.reset();
  cutBian.allocate(2,2,1);

  //找剪切去掉0.000000之后的左边界
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      if(data.at(i,j,0)>cutoffStandard){
        cutBian.modifyValue(0,0,0,i+2);  //找到0.01之后再向右移动2行作为左边界
        isbreak = true;
        break;
      }
    }

    if(true == isbreak){
      break;
    }
  }


  //找剪切去掉0.000000之后的右边界
  isbreak = false;
  for(int i=rows-1;i>=0;i--){
    for(int j=0;j<cols;j++){
      if(data.at(i,j,0)>cutoffStandard){
        cutBian.modifyValue(0,1,0,i-2);  //找到0.01之后再向左移动2行作为右边界(所谓的上下左右是输出文本中的方向)
        isbreak = true;
        break;
      }
    }

    if(true == isbreak){
      break;
    }
  }

  //找剪切去掉0.000000之后的下边界
  isbreak = false;
  for(int j=0;j<cols;j++){
    for(int i=0;i<rows;i++){
      if(data.at(i,j,0)>cutoffStandard){
        cutBian.modifyValue(1,0,0,j+4);  //找到0.01之后再向上移动4行作为下边界
        isbreak = true;
        break;
      }
    }

    if(true == isbreak){
      break;
    }
  }


  //找剪切去掉0.000000之后的上边界
  isbreak = false;
  for(int j=cols-1;j>=0;j--){
    for(int i=0;i<rows;i++){
      if(data.at(i,j,0)>cutoffStandard){
        cutBian.modifyValue(1,1,0,j-4);  //找到0.01之后再向下移动4行作为上边界(所谓的上下左右是输出文本中的方向)
        isbreak = true;
        break;
      }
    }

    if(true == isbreak){
      break;
    }
  }

}

//---------------------Get max value point in a matrixData------------------------------------------
GridPoint getMaxValuePoint(MatrixData<double>& data){
  GridPoint result;
  double maxValue = -DBL_MAX;

  if(NULL == &data){
    RunningLog::writeLog("The data is NULL",__LINE__);
    return result;
  }

  double* ptr = data.getData();
  int rows = data.getRowLength();
  int cols = data.getColLength();

  for(int j=0;j<cols;j++){
    for(int i=0;i<rows;i++){
      if(*ptr>maxValue){
        maxValue = *ptr;
        result.row = i;
        result.col = j;
      }
      ptr++;
    }
  }
  result.level = 0;
  ptr = NULL;

  return result;
}

//---------------------Get max value in a matrixData------------------------------------------
double getMaxValue(MatrixData<double>& data){
  double result = -1;
  if(NULL == &data){
    RunningLog::writeLog("The data is NULL",__LINE__);
    return result;
  }
  result = data[getMaxValuePoint(data)];
  return result;
}
//---------------------Get min value point in a matrixData------------------------------------------
GridPoint getMinValuePoint(MatrixData<double>& data){
  GridPoint result;
  double minValue = DBL_MAX;

  if(NULL == &data){
    RunningLog::writeLog("The data is NULL",__LINE__);
    return result;
  }

  double* ptr = data.getData();
  int rows = data.getRowLength();
  int cols = data.getColLength();

  for(int j=0;j<cols;j++){
    for(int i=0;i<rows;i++){
      if(*ptr<minValue){
        minValue = *ptr;
        result.row = i;
        result.col = j;
      }
      ptr++;
    }
  }
  result.level = 0;
  ptr = NULL;

  return result;
}

GridPoint getMinValuePoint(MatrixData<double>& data,double lowestValue){
  GridPoint result;
  double minValue = DBL_MAX;

  if(NULL == &data){
    RunningLog::writeLog("The data is NULL",__LINE__);
    return result;
  }

  double* ptr = data.getData();
  int rows = data.getRowLength();
  int cols = data.getColLength();

  for(int j=0;j<cols;j++){
    for(int i=0;i<rows;i++){
      if(*ptr<minValue && *ptr>lowestValue){
        minValue = *ptr;
        result.row = i;
        result.col = j;
      }
      ptr++;
    }
  }
  result.level = 0;
  ptr = NULL;

  return result;
}

//---------------------Get min value in a matrixData------------------------------------------
double getMinValue(MatrixData<double>& data){
  double result = -1;
  if(NULL == &data){
    RunningLog::writeLog("The data is NULL",__LINE__);
    return result;
  }
  result = data[getMinValuePoint(data)];
  return result;

}

double getMinValue(MatrixData<double>& data,double lowestValue){

  double result = -1;
  if(NULL == &data){
    RunningLog::writeLog("The data is NULL",__LINE__);
    return result;
  }
  result = data[getMinValuePoint(data,lowestValue)];
  return result;
}

//--------------------Get the data in a special point(which unit is truly mm)------
double getDoseDataInAPosition(MatrixData<double>& data,PhysicalPoint& position,double gridSizes[3],INTEPOLATION_ALGORITHM algorithm,HANDLE_MODEL model){
  PhysicalPoint normPosition;
  
  normPosition.x = position.x/gridSizes[0];
  normPosition.y = position.y/gridSizes[1];

  return getDoseDataInAPosition(data,normPosition,algorithm,model);
}

double getDoseDataInAPosition(MatrixData<double>& data,PhysicalPoint& position,double gridSizes[3],int segments[3],INTEPOLATION_ALGORITHM algorithm,HANDLE_MODEL model){
  PhysicalPoint normPosition;
  
  normPosition.x = position.x/(gridSizes[0]/segments[0]);
  normPosition.y = position.y/(gridSizes[1]/segments[0]);

  return getDoseDataInAPosition(data,normPosition,algorithm,model);
}

//--------------------Get the data in a special point(which unit is per gridsize)----------
double getDoseDataInAPosition(MatrixData<double>& data,PhysicalPoint& position,INTEPOLATION_ALGORITHM algorithm,HANDLE_MODEL model){
  return  getDoseDataInAPosition(data,position.x,position.y,position.z,algorithm,model);
}

double getDoseDataInAPosition(MatrixData<double>& data,double xPos,double yPos,double zPos,INTEPOLATION_ALGORITHM algorithm,HANDLE_MODEL model){
  double result = -1;

  double d1,d2,d3,d4;
  double v1,v2,v3,v4;

  double floatStand = 0.0002;

  int tempRow,tempCol;

  int decimal = 3;
  
  if(NULL == &data){
    RunningLog::writeLog("The data is NULL",__LINE__);
    return result;
  }

  if(xPos>data.getRowLength() || yPos>data.getColLength()){
    RunningLog::writeLog("Out of boundary",__LINE__);
    return result;
  }

  d1 = xPos - TrimFloat_Down(xPos,floatStand);
  d2 = yPos - TrimFloat_Down(yPos,floatStand);
  d3 = 1 - d1;
  d4 = 1 - d2;

  v1 = data.at(TrimFloat_Down(xPos,floatStand),
                 TrimFloat_Down(yPos,floatStand),
                 0);
  v2 = data.at(TrimFloat_Down(xPos,floatStand),
                 TrimFloat_Up(yPos,floatStand),
                 0);
  v3 = data.at(TrimFloat_Up(xPos,floatStand),
                 TrimFloat_Down(yPos,floatStand),
                 0);
  v4 = data.at(TrimFloat_Up(xPos,floatStand),
                 TrimFloat_Up(yPos,floatStand),
                 0);

  switch(algorithm)
  {
    case INTEPOLATION_ALGORITHM(NEAREST):
    {

      if(d1<0.5){
        tempRow = TrimFloat_Down(xPos,floatStand);
      }else{
        tempRow = TrimFloat_Up(xPos,floatStand);
      }

      if(d2<0.5){
        tempCol = TrimFloat_Down(yPos,floatStand);
      }else{
        tempCol = TrimFloat_Up(yPos,floatStand);
      }

      
      switch(model)
      {
        case HANDLE_MODEL(SNDAC):
        {
          result = doubleToAroundPowInt(data.at(tempRow,tempCol,0),decimal);

          result = result/pow(10,decimal);
        }
        break;

        case HANDLE_MODEL(ADAC):
        default:
        {
          result = data.at(tempRow,tempCol,0);
        }
        break;
      }
    }
    break;

    case INTEPOLATION_ALGORITHM(LINER):
    default:
    {
      switch(model)
      {
        case HANDLE_MODEL(SNDAC):
        {
          result = d1*d2*doubleToAroundPowInt(v4,decimal)
                 + d1*d4*doubleToAroundPowInt(v3,decimal)
                 + d2*d3*doubleToAroundPowInt(v2,decimal)
                 + d3*d4*doubleToAroundPowInt(v1,decimal);

          result = result/pow(10,decimal);
        }
        break;

        case HANDLE_MODEL(ADAC):
        default:
        {
          result = d1*d2*v4 + d1*d4*v3 + d2*d3*v2 + d3*d4*v1;
        }
        break;
      }
    }
    break;
    
  }


  return result;

}



//--------------------Get the normlization data in a special point(which unit is truly mm)------
double getNormDoseDataInAPosition(MatrixData<double>& data,PhysicalPoint& position,double gridSizes[3],HANDLE_MODEL model){
  PhysicalPoint normPosition;
  
  normPosition.x = position.x/gridSizes[0];
  normPosition.y = position.y/gridSizes[1];

  return getNormDoseDataInAPosition(data,normPosition,model);
}

double getNormDoseDataInAPosition(MatrixData<double>& data,PhysicalPoint& position,PhysicalPoint measureDoseCentral,PhysicalPoint calcDoseCentral,double gridSizes[3],int segments[3],HANDLE_MODEL model){
  double result;
  int decimal = 2;
  PhysicalPoint normPosition;

  double originNew[2];

  double floatVerbStand = 0.002;

  int calcFirstAlignmentGridCentralRow,calcFirstAlignmentGridCentralCol;

  double tempUnitRow,tempUnitCol;

  PhysicalPoint calcCentralPosInTPDCModel;

  PhysicalPoint calcCentralPosInOmniProModel;

  double relatToCentralRow = position.x - measureDoseCentral.x;
  double relatToCentralCol = position.y - measureDoseCentral.y;

  int targetRowLeftIntegerGrid = TrimFloat_Down(measureDoseCentral.x/gridSizes[0],floatVerbStand);
  int targetColBottomIntegerGrid = TrimFloat_Down(measureDoseCentral.y/gridSizes[1],floatVerbStand);

  double calcGridSizeRow,calcGridSizeCol;

  double distanceToFirstAlginmentX,distanceToFirstAlginmentY;

  double actualPositionX,actualPositionY;

  switch(model)
  {
    case HANDLE_MODEL(SNDAC):
    {

      //rows
      if(floatValue_hasVibrationCentral(measureDoseCentral.x/gridSizes[0],floatVerbStand)){
        //the dose central just located on a row line
        originNew[0] = calcDoseCentral.x;

      }else{
        //the dose central not located on a row line,so select the first row line before the dose central
        originNew[0] = calcDoseCentral.x - (measureDoseCentral.x - gridSizes[0]*targetRowLeftIntegerGrid);

        if(originNew[0]<0){  //out of boundary
          //----------Little possible Case------------------------
          RunningLog::writeLog("The Central point is too away from central and nearby the boundary",__LINE__);
          return -1;
        }
      }

      //col
      if(floatValue_hasVibrationCentral(measureDoseCentral.y/gridSizes[1],floatVerbStand)){
      //the dose central just located on a col line
        originNew[1] = calcDoseCentral.y;

      }else{
        //the dose central not located on a col line,so select the first col line before the dose central
        originNew[1] = calcDoseCentral.y - (measureDoseCentral.y - gridSizes[1]*targetColBottomIntegerGrid);

        if(originNew[1]<0){  //out of boundary
         //----------Little possible Case------------------------
         RunningLog::writeLog("The Central point is too away from central and nearby the boundary",__LINE__);
         return -1;
        }
      }

      calcGridSizeRow = doubleTrim(gridSizes[0]/segments[0],decimal);
      calcGridSizeCol = doubleTrim(gridSizes[1]/segments[1],decimal);


      distanceToFirstAlginmentX = (relatToCentralRow - (calcDoseCentral.x - originNew[0]) )/calcGridSizeRow;
      distanceToFirstAlginmentY = (relatToCentralCol - (calcDoseCentral.y - originNew[1]) )/calcGridSizeCol;

      if( (TrimFloat_Up(distanceToFirstAlginmentX,floatVerbStand)- distanceToFirstAlginmentX)
          >(distanceToFirstAlginmentX - TrimFloat_Down(distanceToFirstAlginmentX,floatVerbStand))){
        actualPositionX = TrimFloat_Down(distanceToFirstAlginmentX,floatVerbStand)*calcGridSizeRow + (calcDoseCentral.x - originNew[0]);
      }else{
        actualPositionX = TrimFloat_Up(distanceToFirstAlginmentX,floatVerbStand)*calcGridSizeRow + (calcDoseCentral.x - originNew[0]);
      }

      if( (TrimFloat_Up(distanceToFirstAlginmentY,floatVerbStand)- distanceToFirstAlginmentY)
          >(distanceToFirstAlginmentY - TrimFloat_Down(distanceToFirstAlginmentY,floatVerbStand))){
        actualPositionY = TrimFloat_Down(distanceToFirstAlginmentY,floatVerbStand)*calcGridSizeCol + (calcDoseCentral.y - originNew[1]);
      }else{
        actualPositionY = TrimFloat_Up(distanceToFirstAlginmentY,floatVerbStand)*calcGridSizeCol + (calcDoseCentral.y - originNew[1]);
      }

      normPosition.x = (measureDoseCentral.x + actualPositionX)/(gridSizes[0]/segments[0]);
      normPosition.y = (measureDoseCentral.y + actualPositionY)/(gridSizes[1]/segments[1]);

      result = getDoseDataInAPosition(data,normPosition,INTEPOLATION_ALGORITHM(LINER),model);
    }
    break;

    case HANDLE_MODEL(ADAC):
    default:
    {
      /*
      //rows
      if(floatValue_hasVibrationCentral(measureDoseCentral.x/gridSizes[0],floatVerbStand)){
        //the dose central just located on a row line
        originNew[0] = calcDoseCentral.x;

      }else{
        //the dose central not located on a row line,so select the first row line before the dose central
        originNew[0] = calcDoseCentral.x - (measureDoseCentral.x - gridSizes[0]*targetRowLeftIntegerGrid);

        if(originNew[0]<0){  //out of boundary
          //----------Little possible Case------------------------
          RunningLog::writeLog("The Central point is too away from central and nearby the boundary",__LINE__);
          return -1;
        }
      }

      //col
      if(floatValue_hasVibrationCentral(measureDoseCentral.y/gridSizes[1],floatVerbStand)){
      //the dose central just located on a col line
        originNew[1] = calcDoseCentral.y;

      }else{
        //the dose central not located on a col line,so select the first col line before the dose central
        originNew[1] = calcDoseCentral.y - (measureDoseCentral.y - gridSizes[1]*targetColBottomIntegerGrid);

        if(originNew[1]<0){  //out of boundary
         //----------Little possible Case------------------------
         RunningLog::writeLog("The Central point is too away from central and nearby the boundary",__LINE__);
         return -1;
        }
      }

      calcCentralPosInTPDCModel.x = calcDoseCentral.x - originNew[0] + gridSizes[0]*TrimFloat_Down(originNew[0]/gridSizes[0],floatVerbStand);
      calcCentralPosInTPDCModel.y = calcDoseCentral.y - originNew[1] + gridSizes[1]*TrimFloat_Down(originNew[1]/gridSizes[1],floatVerbStand);

      normPosition.x = (relatToCentralRow + calcCentralPosInTPDCModel.x)/(gridSizes[0]/segments[0]);
      normPosition.y = (relatToCentralCol + calcCentralPosInTPDCModel.y)/(gridSizes[1]/segments[0]);
      */
      normPosition.x = position.x/(gridSizes[0]/segments[0]);
      normPosition.y = position.y/(gridSizes[1]/segments[1]);
      
      result = getDoseDataInAPosition(data,normPosition,INTEPOLATION_ALGORITHM(LINER),model);
    }
    break;

  }


  return result;
  
}

//--------------------Get the data in a special point(which unit is per gridsize)----------
double getNormDoseDataInAPosition(MatrixData<double>& data,PhysicalPoint& position,HANDLE_MODEL model){
  return  getNormDoseDataInAPosition(data,position.x,position.y,position.z,model);
}

double getNormDoseDataInAPosition(MatrixData<double>& data,double xPos,double yPos,double zPos,HANDLE_MODEL model){
  double result = -1;

  switch(model)
  {
    case HANDLE_MODEL(SNDAC):
    {
      result = getDoseDataInAPosition(data,xPos,yPos,zPos,INTEPOLATION_ALGORITHM(NEAREST),model);
    }
    break;
    
    case HANDLE_MODEL(ADAC):
    default:
    {
      result = getDoseDataInAPosition(data,xPos,yPos,zPos,INTEPOLATION_ALGORITHM(LINER),model);
    }
    break;
  }

  return result;

}


//-----------------------------statistic method----------------------------------------
map<double,int> statistic(Array<double>* source,double percentIncreasement){

  return statistic(source->getArray(),source->getLength(),percentIncreasement);
  
}

//-----------------------------statistic method----------------------------------------
map<double,int> statistic(double* source,int length,double percentIncreasement){
  map<double,int> result;
  if(NULL == source){
    return result;
  }

  double *tempSource = new double[length];

  for(int i=0;i<length;i++){
    tempSource[i] = source[i];
  }

  newQuickSort(tempSource,length);
  
  double segments = tempSource[length-1]*percentIncreasement/100.0;  //max*percentIncreasement/100.0

  int multi = 1;

  int tempCount = 0;
  int allcount = 0;
  for(int i=0;i<length;i++){
    tempCount++;
    if(tempSource[i]>multi*segments){
      allcount = allcount + tempCount;
      result.insert(map<double,int>::value_type(multi*segments,tempCount));
      tempCount = 0;
      multi++;
    }
  }

  if(allcount<length){
    result.insert(map<double,int>::value_type(multi*segments,tempCount));
  }

  delete []tempSource;
  tempSource= NULL;

  return result;
  
}

//-----------------------------statistic method----------------------------------------
map<double,int> statisticForCheckResult(double* source,int length,double percentIncreasement){
  map<double,int> result;
  if(NULL == source){
    return result;
  }

  double *tempSource = new double[length];

  for(int i=0;i<length;i++){
    tempSource[i] = source[i];
  }

  newQuickSort(tempSource,length);
  
  double segments = tempSource[length-1]*percentIncreasement/100.0;  //max*percentIncreasement/100.0

  int multi = 1;

  int tempCount = 0;
  int allcount = 0;
  for(int i=0;i<length;i++){
    tempCount++;
    if(tempSource[i]>multi*segments){
      allcount = allcount + tempCount;
      result.insert(map<double,int>::value_type(multi*segments,tempCount));
      tempCount = 0;
      multi++;
    }
  }

  if(allcount<length){
    result.insert(map<double,int>::value_type(multi*segments,tempCount));
  }

  delete []tempSource;
  tempSource= NULL;

  return result;
  
}


//------------------------------Trim the string-----------------------------------------
string trimStringFront(string source){
  /*
  string result = "";

  if(source.empty() || source.length()==0){
    return result;
  }
  int pos = source.find_first_not_of(" ");

  result = source.substr(pos,source.length());

  return result;
  */
  size_t n = source.find_first_not_of (" \r\n\t");
  if( n != string::npos ){
    source.erase(0,n);
  }

  return source;
}


string trimStringBack(string source){
  /*
  string result = "";
  if(source.empty() || source.length()==0){
    return result;
  }
  int pos = source.find_last_not_of(" ");

  result = source.substr(0,pos+1);

  return result;
  */

  size_t n = source.find_last_not_of(" \r\n\t");
  if( n != string::npos ){
    source.erase(n + 1,source.size() - n);
  }

  return source;
}

string trimStringFrontAndBack(string source){
  /*
  string result = str;
  result = trimStringFront(str);
  result = trimStringBack(result);
  
  return result;
  */
  size_t n = source.find_last_not_of(" \r\n\t");
  if( n != string::npos ){
    source.erase(n + 1,source.size() - n);
  }

  n = source.find_first_not_of (" \r\n\t");
  if( n != string::npos ){
    source.erase(0,n);
  }

  return source;
}

bool strHeadAgreeWithCompareStr(string source,string compareStr){

  bool result = false;

  if(source.length()<compareStr.length()){
    return result;
  }

  if(0==source.compare(0,compareStr.length(),compareStr.c_str(),0,compareStr.length())){
    result = true;
  }else{
    result = false;
  }

  return result;
}


string getLogFilePath(){

  string result;
  TRegistry *pReg = new TRegistry();
  
  pReg->RootKey = HKEY_CURRENT_USER; // 打开主键

  if(!pReg->KeyExists("Software\\TPDC")){
    pReg->CreateKey("Software\\TPDC");
  }
  pReg->OpenKey("Software\\TPDC",false);

  if(!pReg->ValueExists("LogPath")){
    pReg->WriteString("LogPath","./OperationLog.txt");
  }

  result = pReg->ReadString("LogPath").c_str();
  
  pReg->CloseKey();
  delete pReg;
  pReg = NULL;

  return result;
}

//----------------------------Convert gridPos to PhyPos---------------------------
PhysicalPoint convertFromGridPositionToPhyPosition(GridPoint gridPoint,double gridSize[3]){
  PhysicalPoint result;

  result.x =  convertFromGridPositionToPhyPosition(gridPoint.row,gridSize[0]);
  result.y =  convertFromGridPositionToPhyPosition(gridPoint.col,gridSize[1]);

  return result;
}


PhysicalPoint convertFromGridPositionToPhyPosition(GridPoint gridPoint,double gridSize[3],int segments[3]){
  PhysicalPoint result;

  result.x =  convertFromGridPositionToPhyPosition(gridPoint.row,gridSize[0]/segments[0]);
  result.y =  convertFromGridPositionToPhyPosition(gridPoint.col,gridSize[1]/segments[1]);

  return result;
}

double convertFromGridPositionToPhyPosition(int gridPos,double gridSize){

  return  gridPos*gridSize;
}


//---------------------------Convert physical Position to actually central----------------------------
PhysicalPoint convertPositionToActualPosition(PhysicalPoint position,PhysicalPoint physicalCentral){
  PhysicalPoint result;

  result.x = convertPositionToActualPosition(position.x,physicalCentral.x);
  result.y = convertPositionToActualPosition(position.y,physicalCentral.y);
  result.z = convertPositionToActualPosition(position.z,physicalCentral.z);

  return result;
}


double convertPositionToActualPosition(double position,double physicalCentral){

  return  position - physicalCentral;
}


//----------------------------Convert PhyPos to gridPos---------------------------s
int convertFromPhyPosToGridPoint(double physicalPos,int firstAllignment,double gridSize){
  int result = -1;
  
  double floatStand = 0.02;

  double tempPos = (physicalPos - firstAllignment*gridSize)/gridSize;
  if(floatValue_hasVibrationCentral(tempPos,floatStand)){  //the point exist
    result = TrimFloat_Up(tempPos,floatStand);
  }

  return result;
}


//--------------------------Trim double------------------------------------------
double doubleTrim(double value,int decimal){
  double result;
  int tempPowInt;
  
  double tempValue = value*pow(10,decimal);

  if(tempValue>0){
    tempPowInt = floor(tempValue + 0.5);
  }else{
    tempPowInt = ceil(tempValue - 0.5);
  }

  result = ((double)tempPowInt)/pow(10,decimal);

  return result;
}

//--------------------------Convert double to int----------------------------------
int doubleToAroundPowInt(double value,int decimal){
  int result;
  
  double tempValue = value*pow(10,decimal);

  if(tempValue>0){
    result = floor(tempValue + 0.5);
  }else{
    result = ceil(tempValue - 0.5);
  }

  return result;
}

//--------------------------Convert double to int(no adjust)----------------------------------
int doublePowInt(double value,int decimal){
  int result;
  
  result = value*pow(10,decimal);

  return result;
}


//--------------------------------------------------------------passedThreshold-----------------------------------------
bool passedThreshold(double measureNormValue,double correspondCalcNormValue,double threshold,HANDLE_MODEL handle_model){

  bool result = false;
  
  switch(handle_model)
  {
    case HANDLE_MODEL(SNDAC):
    {
      if(measureNormValue>=threshold || correspondCalcNormValue>=threshold){
        result = true;
      }
    }
    break;
    
    case HANDLE_MODEL(ADAC):
    default:
    {
      if(correspondCalcNormValue>=threshold){
        result = true;
      }
    }
    break;

  }

  return result;
}
