#include "DataBase.h"
#include "printingDB.h"

int main(int argc, char* argv[]){
    string exe = argv[0];
    
    List* blockchain = new List();

    load_db_txt("../var/blocks.txt", blockchain);

    
    interactiveProg(blockchain);
    

    clearList(blockchain);
    delete blockchain;
    return 0;
}