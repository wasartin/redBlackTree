#include <iostream>

#include "../include/models/RBTree.h"
#include "../include/tests/tests.h"

using namespace std;

void init(bool noisy);
void flagHandling(int argNum, char *args[]);

/**
 * Main runner of the classes
 */
int main(int argc, char *argv[]){
  init(false);
  flagHandling(argc, argv);

  return 0;
}

void init(bool noisy){
  cout << "Always gotta init" << endl;
}

void flagHandling(int argNum, char *args[]){
  if(argNum >= 2 ){
    if(args[1][0] == '-' && args[1][1] == 'D'){
      cout<< "----------Debug Mode----------"<<endl;

      cout<< "---End Of Debug Mode----------"<<endl;
    }
    else if(args[1][0] == '-' && args[1][1] == 'T'){
      cout<< "----------Test Mode----------"<<endl;
      bool noisy = ( (argNum >= 3) && (args[2][0] == 'n') )? true : false;

      bool allTests = runAllTests(noisy);
      cout << "Test Success: " << ( (allTests)? "True" : "False") << endl;

      cout<< "-------End Of Test Mode------"<<endl;
    }
  }
}
