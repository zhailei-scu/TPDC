//---------------------------------------------------------------------------
#pragma once

#ifndef LogFrameH
#define LogFrameH

//---------------------------------------------------------------------------
#define _LOG_BUFFER_MAX_ 4*1024
//#define _LOG_FILE_PATH "./OperationLog.txt"
//--------------------------------------------------

#include <sstream>
#include <string>
#include <windows.h>
#include <queue>

using namespace std;

//------------------------------Class:Tostringstream-----------------------------------------
class Tostringstream{
public:
  Tostringstream();
  Tostringstream(const Tostringstream& r);
  ~Tostringstream();
  Tostringstream operator=(const Tostringstream& r);
public:
  ostringstream stream;
public:
  void clear();
  void realease();
};
//----------------------------------------Class:LogThread---------------------------------------
class LogThread{
public:
  unsigned logThreadId;
  Tostringstream logThreadStream;

public:
  LogThread();
  LogThread(unsigned threadId, Tostringstream ostringstream);
  ~LogThread();
  LogThread(const LogThread& r);
  LogThread operator=(const LogThread& r);
};

//-----------------------------------------Class:RunningLog-------------------------------------
class RunningLog{
private:
  RunningLog();
  RunningLog(const RunningLog& r);
  RunningLog operator=(const RunningLog& r);

  static RunningLog* runningLogInstance;
public:
  ~RunningLog();

  static void writeLog(const char* _log);
  static void writeLog(const char* _log,int lineNum);
  static void releaseInstance();

  class RunningLogGarbo{
  public:
    RunningLogGarbo();
    ~RunningLogGarbo();
  };

  static RunningLogGarbo runningGarbo;

private:
  Tostringstream _osBuffer;

  queue<LogThread> logThreadQueue;

  HANDLE mutex;

  void flushToLogBeforeExit();

  friend unsigned __stdcall requestToWriteLogFileOnce(void* pvParam);
};
//--------------------------------------------------------------------------
#endif
