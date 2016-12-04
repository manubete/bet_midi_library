#include <cstdlib>
#include <fstream>
#include <iostream>
#include "call_exe.h"

void call_exe()
{
  std::system("clang++-3.8 -O3 -Wall -Iinclude -std=c++11 -o betmidi src-programs/betmidi.cpp -Llib -lmidifile");
  std::system("./betmidi");
}
