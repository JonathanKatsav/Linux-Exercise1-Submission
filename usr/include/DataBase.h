#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <cstring> 
#include <cstdlib>

#include "printingDB.h"

using namespace std;

// Represents a single Bitcoin block with required fields
class Block {
    

public:
    string hash;
    int height;
    string total;
    string time;
    string received_time;
    string relayed_by;
    string prev_block;
    Block* next; // Pointer to the next block in the list
    

    Block(const string& h, int ht, string t,
        const string& ti, const string& rt,
        const string& rb, const string& pb, Block* n = nullptr)
        : hash(h), height(ht), total(t), time(ti),
        received_time(rt), relayed_by(rb), prev_block(pb), next(n) {}

    void print() const {
        cout << "hash: " << hash << endl
            << "height: " << height << endl
            << "total: " << total << endl
            << "time: " << time << endl
            << "received_time: " << received_time << endl
            << "relayed_by: " << relayed_by << endl
            << "prev_block: " << prev_block << endl;
            
    }

    void printCSV(){
        cout << hash << "," 
        << height << ","
        << total << ","
        << received_time << ","
        << relayed_by << ","
        << prev_block << endl;
    }


};


struct List {
    Block* head;
    Block* tail;
    List() : head(nullptr), tail(nullptr) {}
};

// Loads all JSON block files from `dir` and builds the linked list
void load_db_txt(const char* filepath, List* list);

void clearList(List* list);





// EX4 - reloading data 
void refreshData(List* blockchain);
string promptNumBlocks();

// ex5 - interactive manu
void interactiveProg(List* blockchain);




