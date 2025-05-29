#include "DataBase.h"
#include "printingDB.h"

void PrintBlockChain(List* blockchain) {
    for (Block* cur = blockchain->head; cur; cur = cur->next) {
        cur->print();
        if (cur->next){
            cout << "              |" << endl;
            cout << "              |" << endl;
            cout << "              |" << endl;
            cout << "              v" << endl;
        }
    }
}

void PrintByHash(List* blockchain, string searchVal){
    Block* cur = blockchain->head;

    while(cur){
        if(searchVal == cur->hash){
            cur->print();
            return;
        }
        cur = cur->next;
    }
    cout << "Hash not found in any Block" << endl;
}

void PrintByHeight(List* blockchain, int searchVal){
    Block* cur = blockchain->head;

    while(cur){
        if(searchVal == cur->height){
            cur->print();
            return;
        }
        cur = cur->next;
    }
    cout << "Height not found in any Block" << endl;
}

void printByCSV(List* blockchain){
    cout << "hash, height, total, recived_time, relayed_by, prev_block" << endl;
    Block* cur = blockchain->head;

    while(cur){
        cur->printCSV();
        cur = cur->next;
    }
}