#include "../../include/tests/ioTests.h"

/* Start of IO Tests */

uint8_t newParseNodesTest(bool noisy);

bool IOTests_ALL(bool noisy){
  uint8_t correct = 0;
  uint8_t expected = 4;

  uint8_t nodeResult = parseNodesTest(false);
  uint8_t threadResult = parseThreadsTest(false);
  uint8_t commandResult = parseCommandsTest(noisy);

  correct = nodeResult + threadResult + commandResult;

  if(noisy){
    cout << "\tIO Tests: " << +(correct) << "/" << +(expected) << endl;
    cout << "\t\tIO Node Test Result: " << +(nodeResult) << "/" << 2 << " passed" << endl;
    cout << "\t\tIO Thread Test Result: " << +(threadResult) << "/" << 1 << " passed" << endl;
    cout << "\t\tIO Command Test Result: " << +(commandResult) << "/" << 1 << " passed" << endl;
  }

  return (correct == expected);
}


uint8_t parseFileTest(bool noisy){
  //TODO:
  return 0;
}

uint8_t parseNodesTest(bool noisy){

  uint8_t correct1 = 0;
  uint8_t expected1 = 8;

  string inputLineFromText1 = "3b, 7b, 8r, 10b, 11r, 18r, 22b, 26r";
  vector<Node> result;
  result = parseNodes(inputLineFromText1);

  if(result[0].key ==  3 && result[0].color == BLACK) correct1++;
  if(result[1].key ==  7 && result[1].color == BLACK) correct1++;
  if(result[2].key ==  8 && result[2].color == RED) correct1++;
  if(result[3].key == 10 && result[3].color == BLACK) correct1++;
  if(result[4].key == 11 && result[4].color == RED) correct1++;
  if(result[5].key == 18 && result[5].color == RED) correct1++;
  if(result[6].key == 22 && result[6].color == BLACK) correct1++;
  if(result[7].key == 26 && result[7].color == RED) correct1++;

  uint8_t partOneCorrect = (correct1 == expected1)? 1 : 0;
  string inputLineFromText2 = "7b, 3b, f, f, 18r, 10b, 8r, f, f, 11r, f, f, 22b, f, 26r, f, f";

  uint8_t correct2 = 0;
  uint8_t expected2 = 17;
  vector <Node> result2;
  result2 = parseNodes(inputLineFromText2);

  string expected_value[17] = {"7b", "3b", "f", "f", "18r", "10b", "8r", "f", "f", "11r", "f", "f", "22b", "f", "26r", "f", "f"};

  for(uint8_t i = 0; i < result2.size(); i++){
    Node currNode = result2[i];
    if(noisy){
      cout << "Expected: " << expected_value[i] << ", Actual: " << simpleString(&currNode) << endl;
    }
    if(expected_value[i] == simpleString(&currNode)) correct2++;
  }

  uint8_t partTwoCorrect = (correct2 == expected2)? 1 : 0;

  return (partOneCorrect + partTwoCorrect);
}

uint8_t parseThreadsTest(bool noisy){
  uint8_t correct = 0;
  uint8_t expected = 7;

  uint8_t tempVarRun = 0;

  string readerLineInput = "Search threads: 3";

  vector<Thread_t> readerThreads;
  readerThreads = parseThread(readerLineInput);

  for(uint8_t i = 0; i < readerThreads.size(); i++){
    if(readerThreads[i].threadType == THREAD_TYPE::READER && readerThreads[i].threadNum == i) correct++;
    if(noisy){
      string currThread = thread_to_str(readerThreads[i]);
      cout << "Run: " << +(tempVarRun++) << ", currThread:= " << currThread << endl;
    }
  }

  string writerLineInput = "Modify threads: 4";
  vector<Thread_t> writerThreads;
  writerThreads = parseThread(writerLineInput);

  for(uint8_t i = 0; i < writerThreads.size(); i++){
    if(writerThreads[i].threadType == THREAD_TYPE::WRITER && writerThreads[i].threadNum == i) correct++;
    if(noisy){
      string currThread = thread_to_str(writerThreads[i]);
      cout << "Run: " << +(tempVarRun++) << ", currThread:= " << currThread << endl;
    }
  }
  return (correct == expected)? 1 : 0;
}

// @ DEPRECATED
/*
uint8_t parseCommandsTest(bool noisy){

  string inputString = "thread1, search(10) || thread2, delete(10) || thread3, insert(15) || \n thread1, insert(5) || thread3, search(20)";

  vector<Command> result;
  result = parseCommands(inputString);

  uint8_t correct = 0;
  uint8_t expected = 6;
  if(result.size() == 5) correct++;
  if(result[0].threadNum == 1 && result[0].action == ACTION::SEARCH && result[0].arg == 10) correct++;
  if(result[1].threadNum == 2 && result[1].action == ACTION::DELETE && result[1].arg == 10) correct++;
  if(result[2].threadNum == 3 && result[2].action == ACTION::INSERT && result[2].arg == 15) correct++;
  if(result[3].threadNum == 1 && result[3].action == ACTION::INSERT && result[3].arg ==  5) correct++;
  if(result[4].threadNum == 3 && result[4].action == ACTION::SEARCH && result[4].arg == 20) correct++;

  return (correct == expected) ? 1 : 0;
}
*/

uint8_t parseCommandsTest(bool noisy){

  string inputString = "search(10) || delete(10) || insert(15) || insert(5) || search(20)";

  vector<Command> result;
  result = parseCommands(inputString);

  uint8_t correct = 0;
  uint8_t expected = 6;
  if(result.size() == 5) correct++;
  if(result[0].threadType == THREAD_TYPE::READER && result[0].action == ACTION::SEARCH && result[0].arg == 10) correct++;
  if(result[1].threadType == THREAD_TYPE::WRITER && result[1].action == ACTION::DELETE && result[1].arg == 10) correct++;
  if(result[2].threadType == THREAD_TYPE::WRITER && result[2].action == ACTION::INSERT && result[2].arg == 15) correct++;
  if(result[3].threadType == THREAD_TYPE::WRITER && result[3].action == ACTION::INSERT && result[3].arg ==  5) correct++;
  if(result[4].threadType == THREAD_TYPE::READER && result[4].action == ACTION::SEARCH && result[4].arg == 20) correct++;

  return (correct == expected) ? 1 : 0;
}

/* End of IO Tests */
