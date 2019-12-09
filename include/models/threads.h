#ifndef THREADS_H
# define THREADS_H

#include <iostream> /* For cout */
#include <string> /* For the string data type */
#include <cstdlib> /* For itoa function */
#include <sstream> /* for istringstream when making a thread from a string */

#include <vector> /* For the inorder traveral */

#include <pthread.h> /* For threads */
#include <stdint.h> /* For uint8_t */

using namespace std;

/**
 * An enum to represent the type of thread.
 *      READER: For Search Actions
 *      WRITER: For Insert/Delete Actions
 *      UNKNOWN: For the NULL object design pattern
 */
enum THREAD_TYPE{READER, WRITER};

typedef struct Thread_t{
  THREAD_TYPE threadType;
  uint8_t threadNum;
  uint8_t threadId; //idk
} Thread_t;


string thread_to_str(Thread_t input);
Thread_t thread_init_from_str(string type, uint8_t threadNum, uint8_t threadId);
vector<Thread_t> threads_init_from_str(string input);
#endif /* END OF THREADS_H */
