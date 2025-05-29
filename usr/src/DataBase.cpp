#include "DataBase.h"
#include "printingDB.h"





void load_db_txt(const char* filepath, List* list) {
    ifstream ifs(filepath);
    if (!ifs) {
        perror("Error opening merged file");
        return;
    }

    string hash;
    int height = 0;
    string total;
    string time;
    string received_time;
    string relayed_by;
    string prev_block;

    string line;
    bool hasData = false;

    while (getline(ifs, line)) {
        if (line.empty()) {
            Block* node = new Block(
                hash, height, total,
                time, received_time, relayed_by, prev_block);

            if (!list->head) list->head = list->tail = node;
            else {
                list->tail->next = node;
                list->tail = node;
            }
            continue;
        }

        auto pos = line.find(':');
        string key = line.substr(0, pos);
        string val = line.substr(pos + 2);
        if (key == "hash") {
            hash = val;
        }
        else if (key == "height") {
            height = stoi(val);
        }
        else if (key == "total") {
            total = val;
        }
        else if (key == "time") {
            time = val;
        }
        else if (key == "received_time" || key == "received") {
            received_time = val;
        }
        else if (key == "relayed_by") {
            relayed_by = val;
        }
        else if (key == "prev_block") {
            prev_block = val;
        }

        
    };
}

void clearList(List* blockchain) {
    while (blockchain->head) {
        Block* tmp = blockchain->head;
        blockchain->head = tmp->next;
        delete tmp;
    }
    blockchain->tail = nullptr;
}

void refreshData(List* blockchain){
    string numBlocks = promptNumBlocks();
    
    string forCMD = "../sbin/get_blocks.sh -n " + numBlocks;

    cout << "Refrashing data from API.." << endl;
    
    int rc = system(forCMD.c_str());
    if (rc != 0) {
        cerr << "Error: get_blocks.sh returned code " << rc << endl;
        return;
    }

    clearList(blockchain);
    load_db_txt("../var/blocks.txt", blockchain);

    cout << "Data is refreshed now!" << endl;

}

string promptNumBlocks() {
    string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        cout << "Enter how many blocks to fetch: ";
        if (!getline(cin, input)) {
            cin.clear();
            continue;
        }

        if (input.empty()) {
            cout << "Input is empty." << endl;
            continue;
        }

        bool allDigits = true;
        for (char c : input) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                allDigits = false;
                break;
            }
        }
        if (!allDigits) {
            cout << "Invalid input: please enter digits only." << endl;
            continue;
        }
        return input;
    }
}


void interactiveProg(List* blockchain){
    int userChoice = 1;

    while (userChoice){
        cout << "Choose an option:" << endl
        << "1. print db" << endl
        << "2. Print block by hash" << endl
        << "3. Print block by height" << endl
        << "4. export data to csv" << endl
        << "5.Refresh data" << endl
        << "0.Exit" << endl
        << "Enter your choise: ";

        while (true){
            if (!(cin >> userChoice)){
                cout << endl;
                cout << "invalid input, please choose again: ";
                continue;
            }
            cout << endl;
            if (userChoice < 0 || userChoice > 5){
                cout << "invalid input, please choose again: ";
                continue;
            }
            break;
        }
        
        switch (userChoice) {
            case 1: {
                PrintBlockChain(blockchain);
                break;
            }  
            case 2:{
                string hashVal;
                cout << "Enter block hash: ";
                cin >> hashVal; cout << endl;
                cout << "Printing block by hash: " << hashVal << endl;
                PrintByHash(blockchain, hashVal);
                break;
            }
            case 3:{
                int heightVal;
                cout << "Enter block height: ";
                cin >> heightVal; cout << endl;
                cout << "Printing block by height: " << heightVal << endl;
                PrintByHeight(blockchain, heightVal);
                break;
            }
            case 4: {
                printByCSV(blockchain);
                break;
            }
            case 5:{
                refreshData(blockchain);
            }

            break;
        }
    }
    
}
