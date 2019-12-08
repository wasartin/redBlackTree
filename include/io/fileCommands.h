#ifndef FILECOMMANDS_H
# define FILECOMMANDS_H

#include <iostream>
#include <string>

#include <stdint.h> //uint8_t

using namespace std;

typedef struct{
  uint8_t threadId; //thead1
  string action;    //serach(10)
  string result;    //-> true
}operation;

/**
 * The first line of a file is the content of the Tree
 * in prefix order.
 * Note: it can be null
 */
void parseTreeContents(string line);

/**
 * The second set of info from the input file is the sequence
 * of threads that need to be created.
 */
void threadSequenceCreation(vector<string> threads);

/**
 * The third segment of info from a given file is a
 * sequnce of invocations. The given thread, and the command
 */
void operationInvocations(vector<string> operations);


#endif
