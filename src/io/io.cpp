#include "../../include/io/io.h"

#include <cctype>
#include <algorithm>


/**
 * Helper function for cleaning the input line up.
 */
void cleanseInputString(string *input){
  //Remove newlines
  input->erase(std::remove(input->begin(), input->end(), '\n'), input->end());
  //Remove the spaces
  input->erase(std::remove_if(
    begin(*input), end(*input),
    [l = std::locale{}](auto ch) { return std::isspace(ch, l); }
  ), end(*input));
}

Command command_init(THREAD_TYPE threadType, ACTION action, uint8_t arg){
  Command command = {};
  command.threadType = threadType;
  command.action = action;
  command.arg = arg;
  return command;
}

FILE_SECTION determineFileSection(string input){
  if(isdigit(input.at(0))){
    return FILE_SECTION::TREE;
  }
  if(input.find("||") != string::npos){
    return FILE_SECTION::THREAD;
  } else {
    return FILE_SECTION::COMMANDS;
  }
  return FILE_SECTION::UNKNOWN;
}

/*
void openFile(string inputFile){
  ifstream fileReader(inputFile.c_str());

  if(!fileReader.is_open()){
    cout << inputFile << ", file not found" << endl;
  }else{

    vector<Node> nodes;
    vector<uint8_t> threads;
    vector<Command> commands;

    string line;
    uint8_t lineCounter = 0;
    FILE_SECTION currSection;
    while(getline(fileReader, line)){
      lineCounter++;

      currSection = determineFileSection(line);
      if(currSection == FILE_SECTION::TREE){
        nodes = parseNodes(line);
      }
      else if(currSection == FILE_SECTION::THREAD){
        threads.push_back(parseThread(line));
      }
      else if(currSection == FILE_SECTION::COMMANDS){
        commands = parseCommands(line);
      }else{
        //Empty Line
      }
    }
  }
}
*/

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


uint8_t extractNumber(string input) {
  string numberFound;
  for(uint8_t i = 0; i < input.length(); i++){
    if(isdigit(input.at(i))){
      numberFound+= input.at(i);
    }
  }

  if(numberFound.length() == 0) numberFound = "0";//if nothing is found

  return atoi(numberFound.c_str());
}

Command command_init_from_str(string input){
  //extract ACTION & argument
  THREAD_TYPE threadType;
  ACTION act;
  uint8_t arg;
  if(input.find("search") != string::npos){
    threadType = THREAD_TYPE::READER;
    act = ACTION::SEARCH;
    arg = extractNumber(input);
  } else if(input.find("insert") != string::npos){
    threadType = THREAD_TYPE::WRITER;
    act = ACTION::INSERT;
    arg = extractNumber(input);
  } else if(input.find("delete") != string::npos){
    threadType = THREAD_TYPE::WRITER;
    act = ACTION::DELETE;
    arg = extractNumber(input);
  } else{
    threadType = THREAD_TYPE::UNKNOWN;
    act = ACTION::UNKNOWN;
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
  cleanseInputString(&input);
  vector<Command> result;
  string toParse = input;
  string token;
  string delimiter = "||";
  size_t pos = 0;

  uint8_t tempRunVar = 0;

  while((pos = toParse.find(delimiter)) != string::npos){
    token = toParse.substr(0, pos);
    cout << "Run: " << +(tempRunVar++) << ", Token: " << token << endl;
    while(token.length() != 0){
        Command currCommand = command_init_from_str(token);
        result.push_back(currCommand);
        toParse.erase(0, pos + delimiter.length());
        token = "";//reset token
      }
    }

  return result;
}
