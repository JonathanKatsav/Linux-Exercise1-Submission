#include "DataBase.h"
#include "printingDB.h"

int main(int argc, char* argv[]){
    string exe = argv[0];
    if (argc > 1){
        cerr << "to many arguments to search";
        return 2;
    }
    List* blockchain = new List();

    load_db_txt("../var/blocks.txt", blockchain);

    
    printByCSV(blockchain);


    clearList(blockchain);
    delete blockchain;
    return 0;
}


