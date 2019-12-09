#include <iostream>

#include "../include/models/RBTree.h"
#include "../include/io/io.h"
#include "../include/tests/tests.h"

using namespace std;

uint8_t flagHandling(int argNum, char *args[]);
void outputHelp();

/**
 * Main runner of the classes
 */
int main(int argc, char *argv[]){
  uint8_t flags = flagHandling(argc, argv);

  if(flags == 2){
    string fileLocation = "";
    for(uint8_t i = 1; i < argc; i++){
      fileLocation += argv[i];
    }
    cout << "Given File:= " << fileLocation << endl;
    RBTree tree;
    FileContents_t fc;
    fc.tree = &tree;
    parseFile(&fc, fileLocation);

  }

  return 0;
}

uint8_t flagHandling(int argNum, char *args[]){
  if(argNum >= 2 ){
    if(args[1][0] == '-' && args[1][1] == 'D'){
      cout<< "----------Debug Mode----------"<<endl;

      cout<< "---End Of Debug Mode----------"<<endl;
      return 1;
    }
    else if(args[1][0] == '-' && args[1][1] == 'H'){
      outputHelp();
      return 0;
    }
    else if(args[1][0] == '-' && args[1][1] == 'T'){
      cout<< "----------Test Mode----------"<<endl;
      bool noisy = ( (argNum >= 3) && (args[2][0] == 'n') )? true : false;

      bool allTests = runAllTests(noisy);
      cout << "Test Success: " << ( (allTests)? "True" : "False") << endl;

      cout<< "-------End Of Test Mode------"<<endl;
      return 0;
    }
  }
  return 2;
}

void outputHelp(){
  cout << "Flag options" << endl;
  cout << "\t Help Screen (this): -H" << endl;
  cout << "\t Debugging: -D" << endl;
  cout << "\t Run All Tests: -T n " << endl;
  cout << "\t Run with inputFile: path/to/file" << endl;
}
