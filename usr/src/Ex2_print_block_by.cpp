#include "DataBase.h"
#include "printingDB.h"


int main(int argc, char* argv[]) {
    string exe = argv[0];
    if (argc < 3) {
        cerr << "not enought arguments to search";
        return 1;
    }
    else if (argc > 3){
        cerr << "to many arguments to search";
        return 2;
    }
    

    List* blockchain = new List();
    load_db_txt("../var/blocks.txt", blockchain);

    string searchType = argv[1];
    string searchVal = argv[2];
    if (searchType == "--hash"){
        PrintByHash(blockchain, searchVal);
    }
    else if (searchType == "--height"){
        int searchHeight = stoi(searchVal);
        PrintByHeight(blockchain, searchHeight);
    }

    clearList(blockchain);
    delete blockchain;
    return 0;
}
