#include "../../include/models/threads.h"

string thread_to_str(Thread_t input){
  ostringstream convert;
  convert << (int) input.threadNum;

  string result = "ThreadId: ?, Thread Num:= " + convert.str();
  result += ", ThreadType:= ";
  switch(input.threadType){
    case THREAD_TYPE::READER:
      result += "READER";
      break;
    case THREAD_TYPE::WRITER:
      result += "WRITER";
      break;
    default:
      result += "UNKNOWN";
      break;
  }

  return result;
}

Thread_t thread_init_from_str(string type, uint8_t threadNum, uint8_t threadId){
  //Turn into the thread object
  Thread_t result;

  string READER_KEY = "Search";
  string WRITER_KEY = "Modify";

  if(type == READER_KEY){
    result.threadType = THREAD_TYPE::READER;
  } else if(type== WRITER_KEY){
    result.threadType = THREAD_TYPE::WRITER;
  } else{
    result.threadType = THREAD_TYPE::UNKNOWN;
  }

  result.threadNum = threadNum;
  result.threadId = threadId;

  return result;
}

vector<Thread_t> threads_init_from_str(string input){
  vector<Thread_t> threads;
  //put string into a vector
  vector<string> parsedLine;
  istringstream ssCurrCycle;
  ssCurrCycle.str(input);
  //uint8_t tempI = 0;
  string token;
  while(ssCurrCycle.good()){
    getline(ssCurrCycle, token, ' ');//split on space and put into token
    parsedLine.push_back(token);
  }

  uint8_t numOfThreads = 0;
  numOfThreads = atoi(parsedLine[2].c_str());
  for(uint8_t currThreadNum = 0; currThreadNum < numOfThreads; currThreadNum++){
    Thread_t currThread;
    uint8_t threadTypeIndex = 0;
    currThread = thread_init_from_str(parsedLine[threadTypeIndex], currThreadNum, 0);
    threads.push_back(currThread);
  }

  return threads;

}
