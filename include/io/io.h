#ifndef IO_H
# define IO_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

#include "fileCommands.h"
#include "../models/RBTree.h"
#include "../models/threads.h"

using namespace std;

enum class ACTION{SEARCH, INSERT, DELETE, UNKNOWN};
enum class FILE_SECTION{TREE, THREAD, COMMANDS, UNKNOWN};

FILE_SECTION determineFileSection(string input);

// @ DEPRECATED ATM b/c of parse threads
//void openFile(string inputFile);

typedef struct Command{
  THREAD_TYPE threadType;
  ACTION action;
  uint8_t arg;
}Command;

uint8_t extractNumber(string input);
Command command_init_from_str(string input);
Command command_init(THREAD_TYPE threadType, ACTION action, uint8_t arg);

vector<Node> parseNodes(string input);
vector<Thread_t> parseThread(string input);
vector<Command> parseCommands(string input);

/**
 * The ouput of the program will include the follow in an output file
 *      - Execution time
 *      - The output of each search operation (e.g., thread1, search(10) -> true)
 *      - The final red-black tree
 */
void createOutputFile(uint8_t executionTime, vector<operation> operations, RBTree*tree);

#endif
