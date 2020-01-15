#include "../../include/lib/utils.h"


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
