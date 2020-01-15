#include "../../include/io/io.h"

#include <cctype>
#include <algorithm>

Command command_init(THREAD_TYPE threadType, ACTION action, uint8_t arg){
  Command command = {};
  command.threadType = threadType;
  command.action = action;
  command.arg = arg;
  return command;
}

FILE_SECTION determineFileSection(string input){
  if(isdigit(input.at(0)) || input.at(0) == 'f'){
    return TREE;
  }
  //Didn't include 1st letter b/c the case might differ
  if(input.find("hread") != string::npos && (input.find("earch") != string::npos || input.find("odify") != string::npos) ){
    return THREAD;
  }
  if(input.find("||") != string::npos){
    return COMMANDS;
  }
  if(input.length() == 0 || input.at(0) == '\n'){
    return EMPTY;//Idk if I will get empty lines, so
  }
  return EMPTY;
}

void parseFile(FileContents_t *fileContents, string inputFile){
  ifstream fileReader(inputFile.c_str());

  if(!fileReader.is_open()){
    cout << inputFile << ", file not found" << endl;
  }else{ //parse file
      vector<Node> nodes;
      vector<Thread_t> tempThread;
      vector<Thread_t> readerT;
      vector<Thread_t> writerT;
      //RBTree *tree = new RBTree();
      vector<Command> commands;

      string line;
      uint8_t lineCounter = 0;
      FILE_SECTION currSection;
      while(getline(fileReader, line)){
        lineCounter++;
        currSection = determineFileSection(line);
        switch(currSection){
          case TREE:
            nodes = parseNodes(line);
            break;
          case THREAD:
            tempThread = parseThread(line);//should change to pointer
            if(tempThread.size() != 0){
              if(tempThread[0].threadType == READER){
                readerT = tempThread;
              }else if(tempThread[0].threadType == WRITER){
                writerT = tempThread;
              }
            }
            break;
          case COMMANDS:
            commands = parseCommands(line);
            break;
          case EMPTY:
            break;
          default :
            break;
        }
      }
      //Node *inputNodes = &nodes[0];
      //buildTreeFromPreOrderNodes(tree, inputNodes, nodes.size());
      fileContents->inputNodes = nodes;
      //fileContents->tree = tree; //TBD
      fileContents->threads = tempThread;
      fileContents->readerThreads = readerT;
      fileContents->writerThreads = writerT;
      fileContents->commands = commands;
  }
}

vector<Node> parseNodes(string input){
  vector<Node> result;
  istringstream ssCurrCycle;
  ssCurrCycle.str(input);
  //uint8_t tempI = 0;
  string token;
  while(ssCurrCycle.good()){
    getline(ssCurrCycle, token, ',');
    //cout << "Run: " << +(tempI++) << ", token: " << token << endl; //Debugging, add a var tempI
    Node newNode = node_init_from_str(token);
    result.push_back(newNode);
  }
  return result;
}

vector<Thread_t> parseThread(string input){

  vector<Thread_t> threads;

  threads = threads_init_from_str(input);

  return threads;
}

vector<Thread_t> parseThread(vector<Thread_t> threads, string input){
  vector<Thread_t> newThreads = threads_init_from_str(input);
  vector<Thread_t> result;
  //If threads.size() == 0, then this is the first time.
  result.reserve(threads.size() + newThreads.size());
  result.insert(result.end(), threads.begin(), threads.end() );
  result.insert(result.end(), newThreads.begin(), newThreads.end() );

  return result;

}

Command command_init_from_str(string input){
  //extract ACTION & argument
  THREAD_TYPE threadType;
  ACTION act;
  uint8_t arg;
  if(input.find("search") != string::npos){
    threadType = READER;
    act = SEARCH;
    arg = extractNumber(input);
  } else if(input.find("insert") != string::npos){
    threadType = WRITER;
    act = INSERT;
    arg = extractNumber(input);
  } else if(input.find("delete") != string::npos){
    threadType = WRITER;
    act = DELETE;
    arg = extractNumber(input);
  } else{
    arg = extractNumber(input);
  }

  Command result;
  result = {};
  result.threadType = threadType;
  result.action = act;
  result.arg = arg;
  return result;
}

vector<Command> parseCommands(string input){
  //Adding this for easier parsing
  input += " ||";
  //cleanseInputString(&input);
  vector<Command> result;
  string toParse = input;
  string token;
  string delimiter = "||";
  size_t pos = 0;

  //uint8_t tempRunVar = 0;

  while((pos = toParse.find(delimiter)) != string::npos){
    token = toParse.substr(0, pos);
    //cout << "Run: " << +(tempRunVar++) << ", Token: " << token << endl;
    while(token.length() != 0){
        Command currCommand = command_init_from_str(token);
        result.push_back(currCommand);
        toParse.erase(0, pos + delimiter.length());
        token = "";//reset token
      }
    }

  return result;
}


/**
 * The ouput of the program will include the follow in an output file
 *      - Execution time
 *      - The output of each search operation (e.g., thread1, search(10) -> true)
 *      - The final red-black tree
 */
void createOutputFile(uint8_t executionTime, vector<operation> operations, RBTree*tree){

}
