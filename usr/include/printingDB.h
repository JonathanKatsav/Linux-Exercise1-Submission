#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <cstring> 
#include <cstdlib>

#include "DataBase.h"

using namespace std;

class List;
class Block;

// Ex1 - printhing all the data
void PrintBlockChain(List* blockchain);

// EX2 - searching by hash or height
void PrintByHash(List* blockchain, string searchVal);
void PrintByHeight(List* blockchain, int searchVal);

// EX3 - printing dtata as CSV
void printByCSV(List* blockchain);