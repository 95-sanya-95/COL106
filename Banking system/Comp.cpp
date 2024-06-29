#include "Comp.h"
using namespace std;

Comp::Comp(){
    bankStorage1d.resize(100019, Account{"",0});
    datasize=0;
}

void Comp::createAccount(std::string id, int count) {
    Account MyAcc{id, count};
    int ix = hash(id);
    int temp = ix;
    int i = 1;
    while (bankStorage1d[ix].id != "" && bankStorage1d[ix].id != "*") {
        ix = (temp + (i * i * i)) % 100019;
        i++;
    }
    bankStorage1d[ix] = MyAcc;
    datasize++;\
}

std::vector<int> Comp::getTopK(int k) {
    std::vector<int> top;
    std::vector<int> bal;

    for (int i = 0; i < bankStorage1d.size(); i++) {
        bal.push_back(bankStorage1d[i].balance);
    }
    int databasesize= databaseSize();
    int p = min(k, databasesize);

    for (int i = 0; i < p; i++){
        int temp = bal[0];
        for (int j = 1; j < bal.size(); j++){
            temp = max(temp, bal[j]);
        }
        top.push_back(temp);
        for (int j = 0; j < bal.size(); j++){
            if (bal[j] == temp){
                bal.erase(bal.begin() + j);
                break;
            }
        }
    }
    return top;
}

int Comp::getBalance(std::string id) {
    int ix = hash(id);
        int temp =ix;
        int i = 1;
        while (bankStorage1d[ix].id!= id && bankStorage1d[ix].id != ""  && i<100020) {
            ix = (temp + ((i*i*i)) )% 100019;
            i++;
        }
        if(bankStorage1d[ix].id==id){
            return bankStorage1d[ix].balance;
        }
    return -1;
}

void Comp::addTransaction(std::string id, int count) {
    int ix = hash(id);
        int temp = ix;
        int i = 1;
        while (bankStorage1d[ix].id!= id && bankStorage1d[ix].id != "" && i<100020) {
            ix = (temp + (i*i*i)) % 100019;
            i++;
        }
        if(bankStorage1d[ix].id==id){
        bankStorage1d[ix].balance = bankStorage1d[ix].balance + count;
        return;
        }
}

bool Comp::doesExist(std::string id) {
    int ix = hash(id);
    int temp = ix; 
    int i = 1;
    
    while (bankStorage1d[ix].id != id && bankStorage1d[ix].id != "" && i<100020) {
        ix = (temp + ((i*i*i))) % 100019;
        i++;
    }
    if(bankStorage1d[ix].id==id){
        return true;
    }
    return false;
}

bool Comp::deleteAccount(std::string id) {
    int ix = hash(id);
    int temp = ix; 
    int i = 1;

    while (bankStorage1d[ix].id != id && bankStorage1d[ix].id != "" && i<100020) {
        ix = (temp + ((i*i*i))) % 100019;
        i++;
        if (ix == temp) {
            return false;
        }
    }
    if (bankStorage1d[ix].id == id) {
        bankStorage1d[ix].id = "*"; 
        bankStorage1d[ix].balance = 0;
        datasize--;
        return true;
    }
    return false;
}
int Comp::databaseSize() {
    return datasize;
}

int Comp::hash(std::string id) {
    int sum = 0;
    int arr[] = {37, 31, 47, 43, 43};
    int arr2[] = {263, 67, 199, 113, 281, 173, 157};
    for (int i = 0; i < id.size(); i++) {
        sum = abs((sum * arr2[i % 7] + static_cast<int>(id[i]) * arr[i % 5]));
    }
    // Calculating hash value of a string
    int idx = sum % 100019;
    return idx;
}


// Feel free to add any other helper functions you need
// Good Luck!
