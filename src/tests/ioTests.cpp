#include "../../include/tests/ioTests.h"

/* Start of IO Tests */

uint8_t newParseNodesTest(bool noisy);

bool IOTests_ALL(bool noisy){
  uint8_t correct = 0;
  uint8_t expected = 5;

  uint8_t nodeResult = parseNodesTest(false);
  uint8_t threadResult = parseThreadsTest(false);
  uint8_t commandResult = parseCommandsTest(false);
  uint8_t fileContentsResult = parseFileTest(false);

  correct = nodeResult + threadResult + commandResult + fileContentsResult;

  if(noisy){
    cout << "\tIO Tests: " << +(correct) << "/" << +(expected) << endl;
    cout << "\t\tParse Node Test Result: " << +(nodeResult) << "/" << 2 << " passed" << endl;
    cout << "\t\tParse Thread Test Result: " << +(threadResult) << "/" << 1 << " passed" << endl;
    cout << "\t\tParse Command Test Result: " << +(commandResult) << "/" << 1 << " passed" << endl;
    cout << "\t\tParse File Test Result: " << +(fileContentsResult) << "/" << 1 << " passed" << endl;
  }

  return (correct == expected);
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

uint8_t parseFileTest(bool noisy){
  FileContents_t fileContents;

  string inputFileLocation = "resource/test_input1.txt";

  parseFile(&fileContents, inputFileLocation);

  //Input Nodes
  uint8_t correctNodes = 0;
  uint8_t expectedNodes = 17;
  string expected_value[17] = {"7b", "3b", "f", "f", "18r", "10b", "8r", "f", "f", "11r", "f", "f", "22b", "f", "26r", "f", "f"};

  for(uint8_t i = 0; i < fileContents.inputNodes.size(); i++){
    Node currNode = fileContents.inputNodes[i];
    if(noisy){
      cout << "Expected: " << expected_value[i] << ", Actual: " << simpleString(&currNode) << endl;
    }
    if(expected_value[i] == simpleString(&currNode)) correctNodes++;
  }

  uint8_t nodeResult = (correctNodes == expectedNodes)? 1 : 0;

  //Threads Tests
  uint8_t correctThread = 0;
  uint8_t expectedThread = 7;
  for(uint8_t i = 0; i < fileContents.readerThreads.size(); i++){
    if(fileContents.readerThreads[i].threadType == THREAD_TYPE::READER) correctThread++;
  }
  for(uint8_t i = 0; i < fileContents.writerThreads.size(); i++){
    if(fileContents.writerThreads[i].threadType == THREAD_TYPE::WRITER) correctThread++;
  }

  uint8_t threadResult = (correctThread == expectedThread)? 1 : 0;

  //Commands Test
  uint8_t correctCommands = 0;
  uint8_t expectedCommands = 5;
  if(fileContents.commands[0].threadType == THREAD_TYPE::READER && fileContents.commands[0].action == ACTION::SEARCH && fileContents.commands[0].arg == 10) correctCommands++;
  if(fileContents.commands[1].threadType == THREAD_TYPE::WRITER && fileContents.commands[1].action == ACTION::DELETE && fileContents.commands[1].arg == 10) correctCommands++;
  if(fileContents.commands[2].threadType == THREAD_TYPE::WRITER && fileContents.commands[2].action == ACTION::INSERT && fileContents.commands[2].arg == 15) correctCommands++;
  if(fileContents.commands[3].threadType == THREAD_TYPE::WRITER && fileContents.commands[3].action == ACTION::INSERT && fileContents.commands[3].arg ==  5) correctCommands++;
  if(fileContents.commands[4].threadType == THREAD_TYPE::READER && fileContents.commands[4].action == ACTION::SEARCH && fileContents.commands[4].arg == 20) correctCommands++;

  uint8_t commandResult = (correctCommands == expectedCommands)? 1 : 0;

  uint8_t correct = nodeResult + threadResult + commandResult;
  uint8_t expected = 3;

  return (correct == expected)? 1 : 0;
}

/* End of IO Tests */
