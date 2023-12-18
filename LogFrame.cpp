//---------------------------------------------------------------------------
#include "LogFrame.h"

#include <iostream>
#include <fstream>
#include <windows.h>
#include <process.h>
#include "Util.h"
//----------------------Class:Tostringstream----------------------------

Tostringstream::Tostringstream(){
  this->stream.str("");
}

Tostringstream::~Tostringstream(){
  this->stream.str("");
  //ostringstream().swap(this->stream);
}

Tostringstream::Tostringstream(const Tostringstream& r){
  if (NULL != &r){
    this->stream.str("");
    this->stream << r.stream.str();
  }
  else{
    this->stream.str("");
    //ostringstream().swap(this->stream);
  }

}

Tostringstream Tostringstream::operator=(const Tostringstream& r){
  if (NULL != &r){
    this->stream.str("");
    this->stream << r.stream.str();
  }
  else{
    this->stream.str("");
    //ostringstream().swap(this->stream);
  }

  return *this;
}

void Tostringstream::realease(){
  this->stream.str("");
  //ostringstream().swap(this->stream);
}

void Tostringstream::clear(){
  this->stream.str("");
}
//---------------------Class:LogThread---------------------------------
LogThread::LogThread(){
  this->logThreadStream.clear();
  this->logThreadId = -1;
}

LogThread::LogThread(unsigned threadId, Tostringstream ostringstream){
  this->logThreadId = threadId;
  this->logThreadStream = ostringstream;
}

LogThread::~LogThread(){
  this->logThreadStream.realease();
  this->logThreadId = -1;
}

LogThread::LogThread(const LogThread& r){
  if (NULL != &r){
    this->logThreadStream = r.logThreadStream;
    this->logThreadId = r.logThreadId;
  }
  else
  {
    this->logThreadStream.realease();
    this->logThreadId = -1;
  }
}

LogThread LogThread::operator=(const LogThread& r){
  if (NULL != &r){
    this->logThreadStream = r.logThreadStream;
    this->logThreadId = r.logThreadId;
  }
  else
  {
    this->logThreadStream.realease();
    this->logThreadId = -1;
  }
  return *this;
}



//----------------Class:RunningLog------------------------
/*----------Static Members-------------------------------*/
RunningLog* RunningLog::runningLogInstance = new RunningLog();
//---------------InnerClass:RunningLog::runningGarbo------
RunningLog::RunningLogGarbo RunningLog::runningGarbo;


/*Constructor:default*/
RunningLog::RunningLog(){
  this->runningLogInstance = NULL;

  this->_osBuffer.clear();

  while(!this->logThreadQueue.empty()){
    this->logThreadQueue.pop();
  }

  this->mutex = CreateMutex(NULL, FALSE, NULL);

  ReleaseMutex(this->mutex);
}


/*Copy Constructor*/
RunningLog::RunningLog(const RunningLog& r){
  if (NULL != &r){

    this->_osBuffer.clear();
    this->_osBuffer = r._osBuffer;

    while(!this->logThreadQueue.empty()){
      this->logThreadQueue.pop();
    }
    this->logThreadQueue = r.logThreadQueue;

    this->mutex = CreateMutex(NULL, FALSE, NULL);
    memcpy(this->mutex,r.mutex,sizeof(HANDLE));
  }
  else{
    this->_osBuffer.realease();

    while(!this->logThreadQueue.empty()){
      this->logThreadQueue.pop();
    }

    this->mutex = CreateMutex(NULL, FALSE, NULL);
    ReleaseMutex(this->mutex);
  }
  /*banned*/
}

/*Overload operator = */
RunningLog RunningLog::operator=(const RunningLog& r){
  if (NULL != &r){
    this->_osBuffer.clear();
    this->_osBuffer = r._osBuffer;

    while(!this->logThreadQueue.empty()){
      this->logThreadQueue.pop();
    }
    this->logThreadQueue = r.logThreadQueue;

    this->mutex = CreateMutex(NULL, FALSE, NULL);
    memcpy(this->mutex, r.mutex, sizeof(HANDLE));
  }
  else{
    this->_osBuffer.realease();

    while(!this->logThreadQueue.empty()){
      this->logThreadQueue.pop();
    }

    this->mutex = CreateMutex(NULL, FALSE, NULL);
    ReleaseMutex(this->mutex);
  }
  return *this;
  /*banned*/
}

/*Destructor*/
RunningLog::~RunningLog(){
  WaitForSingleObject(RunningLog::runningLogInstance->mutex, INFINITE);

  this->_osBuffer.realease();

  while(!this->logThreadQueue.empty()){
    this->logThreadQueue.pop();
  }

  ReleaseMutex(this->mutex);
  CloseHandle(this->mutex);
  this->mutex = NULL;
}

void RunningLog::releaseInstance(){

  runningLogInstance->flushToLogBeforeExit();

  if (NULL != runningLogInstance){
    delete runningLogInstance;
    runningLogInstance = NULL;
  }

}


void RunningLog::flushToLogBeforeExit(){

  runningLogInstance->_osBuffer.stream << "Quit the LogFile...." << endl <<formatTime() << endl << endl;

  unsigned logThreadId;

  HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, requestToWriteLogFileOnce, NULL, CREATE_SUSPENDED, &logThreadId);

  this->logThreadQueue.push(LogThread(logThreadId, this->_osBuffer));

  runningLogInstance->_osBuffer.realease();

  ResumeThread(handle);

  CloseHandle(handle);


  while (!runningLogInstance->logThreadQueue.empty()){
    //Wait until all the Log thread is done
  }
}

/*Class:RunningLog::RunningLogGarbo*/
/*Constructor:Default*/
RunningLog::RunningLogGarbo::RunningLogGarbo(){

}

/*Destructor*/
RunningLog::RunningLogGarbo::~RunningLogGarbo(){
  releaseInstance();
}

/*Other functions*/
void RunningLog::writeLog(const char* _log){

  int ossreamLen = runningLogInstance->_osBuffer.stream.str().length();
  int tempLogLen = strlen(_log);

  if ((_LOG_BUFFER_MAX_ - ossreamLen)>tempLogLen){
    runningLogInstance->_osBuffer.stream <<_log<<endl<<formatTime()<<endl<<endl;
  }
  else{
    unsigned logThreadId;

    HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, requestToWriteLogFileOnce, NULL, CREATE_SUSPENDED, &logThreadId);

    RunningLog::runningLogInstance->logThreadQueue.push(LogThread(logThreadId, RunningLog::runningLogInstance->_osBuffer));

    runningLogInstance->_osBuffer.clear();

    runningLogInstance->_osBuffer.stream <<_log<<endl<<formatTime()<<endl<<endl;

    ResumeThread(handle);

    CloseHandle(handle);
  }

}

void RunningLog::writeLog(const char* _log,int lineNum){

  int ossreamLen = runningLogInstance->_osBuffer.stream.str().length();
  int tempLogLen = strlen(_log);

  if ((_LOG_BUFFER_MAX_ - ossreamLen)>tempLogLen){
    runningLogInstance->_osBuffer.stream <<_log<<" at line: "<< lineNum<<endl<<formatTime()<<endl<<endl;
  }
  else{
    unsigned logThreadId;

    HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, requestToWriteLogFileOnce, NULL, CREATE_SUSPENDED, &logThreadId);

    RunningLog::runningLogInstance->logThreadQueue.push(LogThread(logThreadId, RunningLog::runningLogInstance->_osBuffer));

    runningLogInstance->_osBuffer.clear();

    runningLogInstance->_osBuffer.stream <<_log<<endl<<formatTime()<<endl<<endl;

    ResumeThread(handle);

    CloseHandle(handle);
  }

}


unsigned __stdcall requestToWriteLogFileOnce(void* pvParam){

  WaitForSingleObject(RunningLog::runningLogInstance->mutex, INFINITE);

  if (!RunningLog::runningLogInstance->logThreadQueue.empty()){
    fstream ofs;

    ofs.open(getLogFilePath().c_str(), ios::out | ios::app);

    //unsigned threadId = RunningLog::runningLogInstance->logThreadQueue.front().logThreadId;

    ofs << RunningLog::runningLogInstance->logThreadQueue.front().logThreadStream.stream.str();

    ofs.close();

    RunningLog::runningLogInstance->logThreadQueue.pop();
  }

  ReleaseMutex(RunningLog::runningLogInstance->mutex);

  return 0;
}
