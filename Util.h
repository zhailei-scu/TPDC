/*create by zhailei 2016
 * this Unit include some basic methods
*/

#pragma once

#ifndef UTILH
#define UTILH

#define OVECCOUNT 30

#include <malloc.h>
#include <iostream>
#include <excpt.h>
#include <windows.h>
#include <sstream>
#include <assert.h>
#include <process.h>
#include <math.h>
#include <map>
#include <algorithm>

#include "LogFrame.h"


//------------------------------------------------------------
using namespace std;

//------------------------FILETYPE----------------------------
//default 0 :not defined
//measureFileType = 100:中测测量剂量数据
//measureFileType = 101:MapCHECK格式测量剂量数据
//measureFileType = 102:Matrix格式测量剂量数据
//calcFileType = 11：DICOM格式的计算剂量数据
//calcFileType = 12: SCU格式计算剂量数据
enum FILETYPE{

  //default 0 :not defined

  ZCMeasureFileType = 100,
  MapCHECKMeasureFileType = 101,
  MatrixMeasureFileType = 102,

  DICOMCalcFileType = 11,
  SCUCalcFileType = 12,
};

//-------------------------enum DataSource----------------------------------------
enum DataSource{
  MEASURE = 1,
  CALCULATE = 2,
};

//-------------------------enum HANDLE_MODEL-------------------------------------
enum HANDLE_MODEL{
  ADAC = 0,   //In fact,it's MapCHECK model which use Acutal Dose for Absolute Check;use normlized(same position,differnt norm value) dose for relative check.


  SNDAC = 1,  //In fact,it's IBA(OmniPro) model which use Same Normlized Dose for Absolute Check;use normlized(same position,differnt norm value) dose for relative check(same with IBA matirx omniPro v1.7b)
};

//---------------------------------------------------------------------------
enum INTEPOLATION_ALGORITHM{
  LINER = 0, //default
  NEAREST,
};
//---------------------Implement:RWLockImpl---------------------------------
/*
This class is an implement to template a Read/Write lock for the protected data source;
Read/Write Lock rules:
1、Allow multi-process to read a protected data resource at the same time,
but only allow one process to write/modify the protected data resource;
2、While exist one or multi reader processes is visiting the protected data resource,
the later writer process should wait till all of these reader processes had leave the
protected data resource.
3、While there is a writer process is visting/modify the protected data resource,the
later reader/writer process should wait till this writer process had leave the protected
data resource.
*/
class RWLockImpl{
protected:
  /*Constructor*/
  RWLockImpl();

  /*Destructor*/
  ~RWLockImpl();

  /*Get a reader lock*/
  void ReadLockImpl();

  /*Try to get a reader lock*/
  /*If get the reader lock succussful,return true,else if the protected data is occupy
   by other writer lock,return false*/
  bool TryReadLockImpl();

  /*Get a reader lock*/
  void WriteLockImpl();

  /*Try to get a writer lock*/
  /*If get the writer lock succussful,return true,else if the protected data is occupy
   by other reader/writer lock,return false*/
  bool TryWriteLockImpl();

  /*release a reader/writer lock*/
  void UnlockImpl();
private:
  /*ban the copy constructor and operator = */
  RWLockImpl(const RWLockImpl& r);
  RWLockImpl operator = (const RWLockImpl& r);
private:
  void AddWriter();

  void RemoveWriter();

  DWORD TryReadLockOnce();

  HANDLE   variableMutex; /*a mutex for changing variable(readers_count、writersWaiting_count、writers_count)*/
  HANDLE   readEvent;     /*reader event*/
  HANDLE   writeEvent;    /*writer event*/
  unsigned readers_count; /*count for the reader processes of the protected data source*/
  unsigned count_writersWaiting; /*count for the waitting writer processes of the protected data source*/
  unsigned writers_count; /*count for the writer processes of the protected data source*/
};

//------------------Class:TRWLock----------------------------------
class TRWLock:private RWLockImpl{
public:
  /*Constructor*/
  TRWLock(){};

  /*Destructor*/
  ~TRWLock(){};

  /*Get a reader lock*/
  void ReadLock();

  /*Try to get a reader lock*/
  /*If get the reader lock succussful,return true,else if the protected data is occupy
   by other writer lock,return false*/
  bool TryReadLock();

  /*Get a reader lock*/
  void WriteLock();

  /*Try to get a writer lock*/
  /*If get the writer lock succussful,return true,else if the protected data is occupy
   by other reader/writer lock,return false*/
  bool TryWriteLock();

  /*release a reader/writer lock*/
  void Unlock();

private:
  /*ban the copy constructor and operator = */
  TRWLock(const TRWLock&);
  TRWLock& operator = (const TRWLock&);
};

//---------------------------Class:TRWLock---------------------------------------
inline void TRWLock::ReadLock(){
  ReadLockImpl();
}

inline bool TRWLock::TryReadLock(){
  return TryReadLockImpl();
}

inline void TRWLock::WriteLock(){
  WriteLockImpl();
}

inline bool TRWLock::TryWriteLock(){
  return TryWriteLockImpl();
}

inline void TRWLock::Unlock(){
  UnlockImpl();
}

//---------------------------Class:PhysicalPoint---------------------------
class PhysicalPoint{
public:
  double x;
  double y;
  double z;
public:
  /*Constructor:Default*/
  PhysicalPoint();
  /*Constructor:Parameter*/
  PhysicalPoint(double x,double y,double z);

  /*Destructor*/
  ~PhysicalPoint();

  /*Copy constructor*/
  PhysicalPoint(const PhysicalPoint& r);

  /*Overload operator*/
  PhysicalPoint operator = (const PhysicalPoint& r);

public:
  void reset();

};

//---------------------------Class:GridPoint------------------------------
class GridPoint{
public:
  int row;
  int col;
  int level;
public:
  /*Constructor:Default*/
  GridPoint();
  /*Constructor:Parameter*/
  GridPoint(int row,int col,int level);

  /*Destructor*/
  ~GridPoint();

  /*Copy constructor*/
  GridPoint(const GridPoint& r);

  /*Overload operator*/
  GridPoint operator = (const GridPoint& r);
public:
  void setValue(int _row,int _col, int _level);
  void reset();
};

//---------------------Class:Array--------------------------------
template<class T>
class Array{
private:
  T* array;
  int length;
public:
  /*Constructor*/
  Array();
  Array(int _length);
  Array(int _length, T* _array);
  /*Destructor*/
  virtual ~Array();
  /*Copy Constructor*/
  Array(const Array& r);

public:
  /*Overload operator [] (start from 0)*/
  T operator[](int index);
  /*Overload operator = */
  Array operator=(const Array& r);

  /*(start from 0)*/
  T at(int index);

  /*(start from 0)*/
  bool updateOne(int index, T value);

  void allocateArray(int _length);

  void setArray(const Array<T> &r);
  T* getArray();

  int getLength();

  void copyArray(T* dest,int size);
  void copyArray(T* dest);

  void setArray(int _length, T* newArray);
  void removeArray();

  bool isEmpty();

private:
  bool check();
};

//------------------------------------------------------------------------
/*Constructor*/
template<class T>
Array<T>::Array(){
  this->array = NULL;
  this->length = 0;
}

template<class T>
Array<T>::Array(int _length){

  this->length = _length;
  if (0 == _length){
    this->array = NULL;
  }
  else{
    this->array = new T[_length];
  }

}

template<class T>
Array<T>::Array(int _length, T* _array){

  this->length = _length;

  if (0 == _length || NULL == _array){
    this->array = NULL;
    this->length = 0;
  }
  else{
    this->array = new T[_length];
    memcpy(this->array, _array, _length*sizeof(T));
  }

}

/*Destructor*/
template<class T>
Array<T>::~Array(){

  TryToDeleteArray<T>(this->array);
  this->length = 0;
  this->array = NULL;

}


/*Copy Constructor*/
template<class T>
Array<T>::Array(const Array<T>& r){
  if (NULL == this){
    RunningLog::writeLog("The equation leftside can not be NULL" + __LINE__);
  }
  
  this->array = NULL;
  this->length = 0;

  if(NULL != &r){

    this->length = r.length;
    if (0 == r.length || NULL == r.array){
      this->array = NULL;
      this->length = 0;
    }
    else{
      this->array = new T[r.length];
      memcpy(this->array, r.array, r.length*sizeof(T));
    }

  }

}

/*Overload operator = */
template<class T>
Array<T> Array<T>::operator = (const Array<T>& r){

  if (NULL == this){
    RunningLog::writeLog("The equation leftside can not be NULL", __LINE__);
    return *this;
  }

  TryToDeleteArray<T>(this->array);

  if(NULL != &r){

    this->length = r.length;
    if (0 == r.length || NULL == r.array){
      this->array = NULL;
      this->length = 0;
    }
    else{
      this->array = new T[r.length];
      memcpy(this->array, r.array, r.length*sizeof(T));
    }

  }else{
    this->array = NULL;
    this->length = 0;
  }

  return *this;
}

/*Class:Array,Functions*/
/*Overload operator [] (start from 0)*/
template<class T>
T Array<T>::operator[](int index){

  T result;
  if (index>(this->length - 1)){
    RunningLog::writeLog("Out of boundary",__LINE__);
    return result;
  }

  result = this->array[index];

  return result;
}


/*(start from 0)*/
template<class T>
T Array<T>::at(int index){

  T result;
  if (index>(this->length - 1)){
    RunningLog::writeLog("Out of boundary",__LINE__);
    return result;
  }

  result = this->array[index];

  return result;
}

template<class T>
T* Array<T>::getArray(){
  return this->array;
}

template<class T>
int Array<T>::getLength(){
  return this->length;
}

template<class T>
void Array<T>::copyArray(T* dest,int size){

  if( (this->length) <size){
    RunningLog::writeLog("The size is longer than Array length",__LINE__);
    return;
  }
  else{
    memcpy(dest, this->array, size*sizeof(T));
  }
}

template<class T>
void Array<T>::copyArray(T* dest){

  if(0==this->length || NULL==this->array){
    T = NULL;
  }
  else{
    memcpy(dest, this->array, this->length*sizeof(T));
  }

}

/*(start from 0)*/
template<class T>
bool Array<T>::updateOne(int index, T value){

  if (index>(this->length - 1)){
     RunningLog::writeLog("Out of boundary",__LINE__);
     return false;
  }

  this->array[index] = value;

  return true;
}

template<class T>
void Array<T>::allocateArray(int _length){
  TryToDeleteArray<T>(this->array);

  this->length = _length;
  if (0 != _length){
    this->array = new T[_length];
  }
  else{
    this->array = NULL;
  }

}

/*set the array*/
template<class T>
void Array<T>::setArray(int _length, T* newArray){
  if ((0 == _length && NULL != newArray) || (0 != _length && NULL == newArray)){
    RunningLog::writeLog("Please keep the array length be correct",__LINE__);
    return;
  }

  TryToDeleteArray<T>(this->array);
  this->length = _length;
  if (0 == _length || NULL == newArray){
    this->array = NULL;
    this->length = 0;
  }
  else{
    this->array = new T[_length];
    memcpy(this->array, newArray, _length*sizeof(T));
  }
}

template<class T>
void Array<T>::setArray(const Array &r){
  TryToDeleteArray<T>(this->array);
  *this = r;
}

template<class T>
void Array<T>::removeArray(){
  TryToDeleteArray<T>(this->array);
  this->length = 0;
  this->array = NULL;
}

template<class T>
bool Array<T>::isEmpty(){

  if(0==this->length && NULL==this->array){
    return true;
  }
  return false;
}

template<class T>
bool Array<T>::check(){
  if((NULL == this->array && 0 != this->length)||
     (NULL!=this->array && 0==this->length)){
     RunningLog::writeLog("The array Length is not right",__LINE__);
     return false;
  }
  return true;
}

//---------------------Class:MatrixData----------------------------
//------------Used for constructorthree dimension arrays-----------
template<class T>
class MatrixData:private Array<T>{

private:
  int rowLength;
  int colLength;
  int heightLength;

public:
/*Constructor*/
  MatrixData();
  MatrixData(int _rowLength, int _colLength, int _heightLength);
  MatrixData(int _rowLength, int _colLength, int _heightLength, T* _data);

  /*Destructor*/
  ~MatrixData();

  /*Copy Constructor*/
  MatrixData(const MatrixData<T>& r);

  /*Overload the operator = */
  MatrixData operator = (const MatrixData<T>& r);

  /*Overload the operator [] (start from 0,0,0)*/
  T operator [](GridPoint gridPoint);

public:
  int getRowLength();
  int getColLength();
  int getHeightLength();

  T at(int _row, int _col,int _height);

  int getDataLength();

  bool setData(int _rowLength, int _colLength, int _heightLength, T* _newData);
  void allocate(int _rowLength, int _colLength, int _heightLength);
  T* getData();
  bool modifyValue(GridPoint gridPoint, T value);
  bool modifyValue(int rowPos,int colPos,int heightPos, T value);

  void copyData(T* dest,int size);
  void copyData(T* dest);
  void removeData();

  void clear();
  void reset();

  bool isEmpty();

private:
  bool check();
};
//------------------------------------------------------------------------------
/*Constructor*/
template<class T>
MatrixData<T>::MatrixData() :Array<T>(){
  rowLength = 0;
  colLength = 0;
  heightLength = 0;
}

template<class T>
MatrixData<T>::MatrixData(int _rowLength, int _colLength, int _heightLength) :Array<T>(_rowLength*_colLength*_heightLength){
  this->rowLength = _rowLength;
  this->colLength = _colLength;
  this->heightLength = _heightLength;
  this->allocateArray(_rowLength*_colLength*_heightLength);
}

template<class T>
MatrixData<T>::MatrixData(int _rowLength, int _colLength, int _heightLength, T* _data) :Array<T>(_rowLength*_colLength*_heightLength, _data){
  this->rowLength = _rowLength;
  this->colLength = _colLength;
  this->heightLength = _heightLength;
  this->setArray(_rowLength*_colLength*_heightLength, _data);
}


/*Destructor*/
template<class T>
MatrixData<T>::~MatrixData(){
  this->rowLength = 0;
  this->colLength = 0;
  this->heightLength = 0;
}

/*Copy Constructor*/
template<class T>
MatrixData<T>::MatrixData(const MatrixData<T>& r):Array<T>(r){

  if(NULL != &r){

    if (NULL == this){
      RunningLog::writeLog("The equation leftside can not be NULL",__LINE__);
    }

    this->rowLength = r.rowLength;
    this->colLength = r.colLength;
    this->heightLength = r.heightLength;
  }
}

/*Overload the operator = */
template<class T>
MatrixData<T> MatrixData<T>::operator = (const MatrixData<T>& r){

  if(NULL != &r){
    if (NULL == this){
      RunningLog::writeLog("The equation leftside can not be NULL",__LINE__);
      return *this;
    }
    this->rowLength = r.rowLength;
    this->colLength = r.colLength;
    this->heightLength = r.heightLength;

    this->setArray(r);

  }else{
    this->reset();
  }

  return *this;
}

///*Overload the operator [] (start from 0,0,0)*/
template<class T>
T MatrixData<T>::operator [] (GridPoint gridPoint){
  T result;
  if ((gridPoint.row+1)>this->rowLength ||
    (gridPoint.col+1)>this->colLength ||
    (gridPoint.level+1)>this->heightLength){
      RunningLog::writeLog("out of boundary: ",__LINE__);
      return result;
  }

  result = Array<T>::at(this->rowLength*this->colLength*gridPoint.level + this->rowLength*gridPoint.col + gridPoint.row);

  return result;
}


/*Class:MatrixData,other function*/
template<class T>
int MatrixData<T>::getRowLength(){
  return this->rowLength;
}

template<class T>
int MatrixData<T>::getColLength(){
  return this->colLength;
}

template<class T>
int MatrixData<T>::getHeightLength(){
  return this->heightLength;
}

template<class T>
int MatrixData<T>::getDataLength(){
  if(this->getLength() != this->getRowLength()*getColLength()*getHeightLength()){
    RunningLog::writeLog("The dimension is not right",__LINE__);
    return -1;
  }
  return this->getLength();
}

template<class T>
T MatrixData<T>::at(int _row, int _col,int _height){
  T result;

  if ((_row+1)>this->rowLength ||
      (_col+1)>this->colLength ||
      (_height+1)>this->heightLength){
        RunningLog::writeLog("out of boundary: ",__LINE__);
        return result;
    }
    result = Array<T>::at(this->rowLength*this->colLength*_height + this->rowLength*_col + _row);

    return result;
}

template<class T>
bool MatrixData<T>::setData(int _rowLength, int _colLength, int _heightLength, T* _newData){
  if ((0 == _rowLength*_colLength*_heightLength&&NULL != _newData) ||
      (0 != _rowLength*_colLength*_heightLength&&NULL == _newData)){
       RunningLog::writeLog("The array length is not same as the setted data.At line: " + __LINE__);

       return false;
  }
  this->rowLength = _rowLength;
  this->colLength = _colLength;
  this->heightLength = _heightLength;

  this->setArray(_rowLength*_colLength*_heightLength, _newData);
  return true;
}

template<class T>
void MatrixData<T>::allocate(int _rowLength, int _colLength, int _heightLength){
  this->reset();
  if ((0 != _rowLength*_colLength*_heightLength)){
    this->rowLength = _rowLength;
    this->colLength = _colLength;
    this->heightLength = _heightLength;
    Array<T>::allocateArray(_rowLength*_colLength*_heightLength);
  }

}


template<class T>
T* MatrixData<T>::getData(){
  return this->getArray();
}

template<class T>
bool MatrixData<T>::modifyValue(GridPoint gridPoint, T value){
  if ((gridPoint.row+1)>this->rowLength ||
    (gridPoint.col+1)>this->colLength ||
    (gridPoint.level+1)>this->heightLength){
      RunningLog::writeLog("out of boundary: ",__LINE__);
      return false;
  }

  return  Array<T>::updateOne(this->rowLength*this->colLength*gridPoint.level
                              + this->rowLength*gridPoint.col + gridPoint.row,value);
}

template<class T>
bool MatrixData<T>::modifyValue(int rowPos,int colPos,int heightPos, T value){
  if ((rowPos+1)>this->rowLength ||
      (colPos+1)>this->colLength ||
      (heightPos+1)>this->heightLength){
      RunningLog::writeLog("out of boundary: ",__LINE__);
      return false;
  }

  return  Array<T>::updateOne(this->rowLength*this->colLength*heightPos
                              + this->rowLength*colPos + rowPos,value);
}

template<class T>
void MatrixData<T>::copyData(T* dest,int size){
  this->copyArray(dest,size);
}

template<class T>
void MatrixData<T>::copyData(T* dest){
  this->copyArray(dest);
}

template<class T>
void MatrixData<T>::removeData(){
  this->removeArray();
}


template<class T>
void MatrixData<T>::clear(){
  this->rowLength = 0;
  this->colLength = 0;
  this->heightLength = 0;
  this->removeArray();
}

template<class T>
void MatrixData<T>::reset(){
  this->rowLength = 0;
  this->colLength = 0;
  this->heightLength = 0;
  this->removeArray();
}

template<class T>
bool MatrixData<T>::isEmpty(){
  int length = this->rowLength*this->colLength*this->heightLength;

  if(0==length && NULL == Array<T>::getArray()){
    return true;
  }
  return false;
}

template<class T>
bool MatrixData<T>::check(){
  int length = this->rowLength*this->colLength*this->heightLength;
  if( (0==length && false==Array<T>::isEmpty()) ||
      (0!=length && true==Array<T>::isEmpty())||
      (length != Array<T>::getlength())){
      RunningLog("The matrixData lenght is not right",__LINE__);
      return false;
  }

  return true;

}


/*快排序*/
//very fast
void newQuickSort(double *tst,int length){
  sort(tst,tst+length);
}

void newQuickSortFloat(float *tst,int length){
  sort(tst,tst+length);
}

//-------------------------------------------------------------------------
/*快排序*/
/*do by myself: two slow while the array is big
template <class T>
extern void quickSort(T *tst,int low,int high){

  if(low>high)
    return;

  int first = low;
  int last = high;

  T keydat = tst[first];

  while(first<last){
    while(first<last&&tst[last]>=keydat){
      --last;
    }
    tst[first] = tst[last];

    while(first<last&&tst[first]<=keydat){
      ++first;
    }
    tst[last] = tst[first];
  }

  tst[first] = keydat;

  quickSort(tst,low,first-1);
  quickSort(tst,first+1,high);

}
*/
//-------------------------------------------------------------------------
/*快排序*/
template<class T,class K>
extern void quickSort(pair<T,K> *tst,int low,int high){

  if(low>high)
    return;

  int begin = low;
  int end = high;

  pair<T,K> keydat = tst[begin];

  while(begin<end){
    while(begin<end&&tst[end].first>=keydat.first){
      --end;
    }
    tst[begin] = tst[end];

    while(begin<end&&tst[begin].first<=keydat.first){
      ++begin;
    }
    tst[end] = tst[begin];
  }

  tst[begin] = keydat;

  quickSort(tst,low,begin-1);
  quickSort(tst,begin+1,high);

}


//由于很难获取new出的大小，对于一个指针只
//要不强制pointer=NULL,那么if(pointer)为true，这里面包含两种情况
//1.pointer指针对应于一个new出的栈，那么需要delete[] pointer,
//2.pointer指针只有4个字节大小，并没有指向一个new出的栈，但是这是if(pointer)
//也为true,所以用delete[] pointer会出错，因此需要在try块中进行
//而一般的Try/throw无法俘获上述错误，只有使用SEH(structed exception handled)的__try/__except
//通过 EXCEPTION_EXECUTE_HANDLER 来忽略结构化错误


/*对于基本类型，比如int,float,对于数组内存如 new int[10]，使用delete 和 delete[]都可以进行释放，
但是对于包含指针成员的某个类，如  class A{public: int member1,float* member2}; ,如果new A(),即
只new 了一个对象,那么只能使用delete，这是使用delete[] 会出错，而且SEH都无法处理；如果new A[10]，
即new 了一个对象数组，那么使用delete会出错，但是这种错误可用SEH处理，而且将无法释放其中的指针成员，只能使用delete[].
而且需要注意的是：由于使用了函数将所需要释放的内存的地址传入，那么不能简单的使用void*作为形参，因为这样
编译器认为所需要释放的只是基本类型，从而会报错(但是这种错误可以使用SEH处理)，从而内存将不会被释放，因此需要使用模板将数组类型传入，这样才能
正确的完成内存清理工作，且自定义类/结构体成员中的析构函数将会被正确调用*/


/*释放new XXX 的单个内存*/
template <class T>
extern void TryToDelete(T* ptr){

  if (NULL != ptr){
    __try{
      delete ptr;
    }
    __except (EXCEPTION_EXECUTE_HANDLER){
      //do nothing
      cout<<"移除单个对象有异常"<<endl;
    }
  }

}

/*释放 new XXX[] 出的数组内存*/
template <class T>
extern void TryToDeleteArray(T* ptr){
  if (NULL != ptr){
    __try{
      delete[] ptr;
    }
    __except(EXCEPTION_EXECUTE_HANDLER){
      //do nothing
      cout<<"移除分配的数组有异常"<<endl;
    }
  }
}

//-----------Get the suitable segments for each gridsize
int getGridSegments(double gridsize);

//-----------Get Formated System Time------------------------
string formatTime();

//-----------Interpolation-----------------------------------
//------------------------------------双线性插值----------------------------------------
float* __fastcall regularBinearInterploate(float *array,int &row,int &col,int multi);
//--------------------------------双三次插值-------------------------------------------
//-------------------------使用双三次插值来获取某个待插值点的值---------------------------
//-------算法的详细说明可以参考[1] 贾永红.数字图像处理[M].武汉:武汉大学出版社,2003:108-110.
//-------------------------or--[2] SONKA M,HLAVAC V,BOYLE R.Image processing,analysis and machine vision,international student edition[M].3rd ed.Toronto:Thomson Learning,2007:122-123.
//-------------------------or--[3] 翟磊，黄宁，王鹏，范轶翔，夏翔，吴庆星.基于梯度特征的调强放疗计划剂量插值算法.生物医学工程学杂志.2016, 33(6): 1116-1123. doi: 10.7507/1001-5515.20160178
float* __fastcall BicubicInterploate(float *array,int &row,int &col,int multi);
float __fastcall getBicubicValue(float u,float v,float B[4][4]);
float __fastcall getBicubicParam(float uorV);
//----------------------------高斯平滑处理(5阶)-----------------------------------------
//float* GaussianSmoothingOrderFive(float* array,int row,int col);
void GaussianSmoothingOrderFive(MatrixData<double> *matrixData);
//----------------------------高斯平滑处理(3阶)-----------------------------------------
void GaussianSmoothingOrderThree(MatrixData<double> *matrixData);
//------------------------------中值平滑(滤波)----------------------------------
void midValueSmoothing(MatrixData<double> *matrixData,const int orders);
//------------------------------均值滤波----------------------------------
void averageSmoothing(MatrixData<double> *matrixData,const int orders);
//------------------------------双边滤波-----------------------------------
float* bilateralSmoothing(float* array,int row,int col);
//------------------------------alignment And Segments----------------------------------
void alignmentAndSegment(MatrixData<double>* targetMatrix,
                         double targetGridSize[2],
                         PhysicalPoint targetPhysicCental,
                         GridPoint& targetFirstAlignmentGridCentral,
                         MatrixData<double>* todoMatrix,
                         double todoGridSize[2],
                         PhysicalPoint& todoPhysicCental,
                         GridPoint& todoFirstAlignmentGridCentral,
                         int segments[2],
                         HANDLE_MODEL model);

//-----------------------------Trim float:Up---------------------------------
int TrimFloat_Up(double value,double standard);
//-----------------------------Trim float:Down---------------------------------
int TrimFloat_Down(double value,double standard);
//--------------If a float Value has a vibration Integer Central-------------------
bool floatValue_hasVibrationCentral(double value,double standard);
//-----------------Cut off the data in a matrix which below the cutoffStandard----------------------------
void matrixDataDataCutoff(MatrixData<double>& data,MatrixData<int>& cutBian,double cutoffStandard);

//---------------------Get max value point in a matrixData------------------------------------------
GridPoint getMaxValuePoint(MatrixData<double>& data);
//---------------------Get max value in a matrixData------------------------------------------
double getMaxValue(MatrixData<double>& data);

//---------------------Get min value point in a matrixData------------------------------------------
GridPoint getMinValuePoint(MatrixData<double>& data);
GridPoint getMinValuePoint(MatrixData<double>& data,double lowestValue);
//---------------------Get min value in a matrixData------------------------------------------
double getMinValue(MatrixData<double>& data);
double getMinValue(MatrixData<double>& data,double lowestValue);

//--------------------Get the data in a special point(which unit is truly mm)------
double getDoseDataInAPosition(MatrixData<double>& data,PhysicalPoint& position,double gridSizes[3],INTEPOLATION_ALGORITHM algorithm,HANDLE_MODEL model);

double getDoseDataInAPosition(MatrixData<double>& data,PhysicalPoint& position,double gridSizes[3],int segments[3],INTEPOLATION_ALGORITHM algorithm,HANDLE_MODEL model);

//--------------------Get the data in a special point(which unit is per gridsize)----------
double getDoseDataInAPosition(MatrixData<double>& data,PhysicalPoint& position,INTEPOLATION_ALGORITHM algorithm,HANDLE_MODEL model);

//--------------------Get the data in a special point(which unit is per gridsize)----------
double getDoseDataInAPosition(MatrixData<double>& data,double xPos,double yPos,double zPos,INTEPOLATION_ALGORITHM algorithm,HANDLE_MODEL model);



//--------------------Get the normlization data in a special point(which unit is truly mm)------
double getNormDoseDataInAPosition(MatrixData<double>& data,PhysicalPoint& position,double gridSizes[3],HANDLE_MODEL model);

double getNormDoseDataInAPosition(MatrixData<double>& data,PhysicalPoint& position,PhysicalPoint measureDoseCentral,PhysicalPoint calcDoseCentral,double gridSizes[3],int segments[3],HANDLE_MODEL model);

//--------------------Get the normlization data in a special point(which unit is per gridsize)----------
double getNormDoseDataInAPosition(MatrixData<double>& data,PhysicalPoint& position,HANDLE_MODEL model);

//--------------------Get the normlization data in a special point(which unit is per gridsize)----------
double getNormDoseDataInAPosition(MatrixData<double>& data,double xPos,double yPos,double zPos,HANDLE_MODEL model);


//-----------------------------statistic method----------------------------------------
map<double,int> statistic(Array<double>* source,double percentIncreasement);
map<double,int> statistic(double* source,int length,double percentIncreasement);
map<double,int> statisticForCheckResult(double* source,int length,double percentIncreasement);



//------------------------------Trim the string-----------------------------------------
string trimStringFront(string source);
string trimStringBack(string source);

string trimStringFrontAndBack(string str);

bool strHeadAgreeWithCompareStr(string source,string compareStr);


//-----------------------------Registry-------------------------------------------
string getLogFilePath();


//----------------------------Convert gridPos to PhyPos---------------------------
PhysicalPoint convertFromGridPositionToPhyPosition(GridPoint gridPoint,double gridSize[3]);

PhysicalPoint convertFromGridPositionToPhyPosition(GridPoint gridPoint,double gridSize[3],int segments[3]);

double convertFromGridPositionToPhyPosition(int gridPos,double gridSize);


//---------------------------Convert physical Position to actually central----------------------------
PhysicalPoint convertPositionToActualPosition(PhysicalPoint position,PhysicalPoint physicalCentral);

double convertPositionToActualPosition(double position,double physicalCentral);

//----------------------------Convert PhyPos to gridPos---------------------------
int convertFromPhyPosToGridPoint(double physicalPos,int firstAllignment,double gridSize);

//--------------------------Trim double------------------------------------------
double doubleTrim(double value,int decimal);

//--------------------------Convert double to int----------------------------------
int doubleToAroundPowInt(double value,int decimal);

//--------------------------Convert double to int(no adjust)----------------------------------
int doublePowInt(double value,int decimal);

//---------------------------------------------------------------------------------
bool passedThreshold(double measureNormValue,double correspondCalcNormValue,double threshold,HANDLE_MODEL handle_model);
#endif