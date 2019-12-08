#include "../../include/tests/ioTests.h"

/* Start of IO Tests */

uint8_t newParseNodesTest(bool noisy);


bool IOTests_ALL(bool noisy){
  uint8_t correct = 0;
  uint8_t expected = 4;

  uint8_t nodeResult = parseNodesTest(false);
  uint8_t newNodeResult = newParseNodesTest(false);
  uint8_t threadResult = parseThreadsTest(false);
  uint8_t commandResult = parseCommandsTest(false);

  correct = nodeResult + newNodeResult + threadResult + commandResult;

  if(noisy){
    cout << "\tIO Tests: " << +(correct) << "/" << +(expected) << endl;
    cout << "\t\tIO Node Test Result: " << +(nodeResult) << "/" << 1 << " passed" << endl;
    cout << "\t\tIO New Node Test Result: " << +(newNodeResult) << "/" << 1 << " passed" << endl;
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

  string inputLineFromText = "3b, 7b, 8r, 10b, 11r, 18r, 22b, 26r";
  vector<Node> result;
  result = parseNodes(inputLineFromText);

  //should be 8 nodes.
  uint8_t correct = 0;
  uint8_t expected = 8;
  if(result[0].key ==  3 && result[0].color == BLACK) correct++;
  if(result[1].key ==  7 && result[1].color == BLACK) correct++;
  if(result[2].key ==  8 && result[2].color == RED) correct++;
  if(result[3].key == 10 && result[3].color == BLACK) correct++;
  if(result[4].key == 11 && result[4].color == RED) correct++;
  if(result[5].key == 18 && result[5].color == RED) correct++;
  if(result[6].key == 22 && result[6].color == BLACK) correct++;
  if(result[7].key == 26 && result[7].color == RED) correct++;

  return (correct == expected) ? 1 : 0;
}

uint8_t newParseNodesTest(bool noisy){
  string inputLineFromText = "7b, 3b, f, f, 18r, 10b, 8r, f, f, 11r, f, f, 22b, f, 26r, f, f";

  vector <Node> result;
  result = parseNodes(inputLineFromText);

  uint8_t correct = 0;
  uint8_t expected = 17;

  string expected_value[17] = {"7b", "3b", "f", "f", "18r", "10b", "8r", "f", "f", "11r", "f", "f", "22b", "f", "26r", "f", "f"};

  for(uint8_t i = 0; i < result.size(); i++){
    Node currNode = result[i];
    if(noisy){
      cout << "Expected: " << expected_value[i] << ", Actual: " << simpleString(&currNode) << endl;
    }
    if(expected_value[i] == simpleString(&currNode)) correct++;
  }
  return (correct == expected) ? 1 : 0;
}

uint8_t parseThreadsTest(bool noisy){
  uint8_t correct = 0;
  uint8_t expected = 6;

  if(parseThread("thread1") == 1) correct++;
  if(parseThread("thread2") == 2) correct++;
  if(parseThread("thread3") == 3) correct++;
  if(parseThread("thread11") == 11) correct++;
  if(parseThread("thread") == 0) correct++;
  if(parseThread("") == 0) correct++;

  return (correct == expected)? 1 : 0;
}

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

/* End of IO Tests */
