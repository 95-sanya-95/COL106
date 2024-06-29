#include "Chaining.h"
using namespace std;

Chaining::Chaining()
{
    bankStorage2d.resize(99991, std::vector<Account>(0));
}

void Chaining::createAccount(std::string id, int count) {                  //**********

    Account MyAcc{id, count};
   
    int idx = hash(id);                 

    bankStorage2d[idx].push_back(MyAcc);
    
};

std::vector<int> Chaining::getTopK(int k) {

    std::vector<int> top;
    std::vector<int> bal;

    for (int i = 0; i<bankStorage2d.size(); i++){
        for (int j = 0; j < bankStorage2d[i].size(); j++){
            bal.push_back(bankStorage2d[i][j].balance);
        }
    }
    int databasesize= databaseSize();
    int l = min(k, databasesize);

    for (int k = 0; k < l; k++){
        int temp = bal[0];
        for (int j = 1; j < bal.size(); j++){
            temp = max(temp,bal[j]);
        }
        top.push_back(temp);

        for (int q=0; q<bal.size(); q++){
            if (bal[q] == temp){
                bal.erase(bal.begin() + q);
                break;
            }
        }
    }
    return top;
}

int Chaining::getBalance(std::string id) {                                 //************

    int idx = hash(id);        

    int size = bankStorage2d[idx].size();
    for (int j=0; j<size; j++){
        if(bankStorage2d[idx][j].id == id){
            return bankStorage2d[idx][j].balance;
        }
    }     
    return 0; 
}

void Chaining::addTransaction(std::string id, int count) {            //************

    if(doesExist(id) == false){
        createAccount(id,count);
    }
    else{
        int idx = hash(id);        
        int size = bankStorage2d[idx].size();
        for (int j=0; j<size; j++){
            if(bankStorage2d[idx][j].id == id){
                bankStorage2d[idx][j].balance = bankStorage2d[idx][j].balance + count;
                    return;
                }
            }
        }
    }
    

bool Chaining::doesExist(std::string id) {                          //***********

    int idx = hash(id);        
    int size = bankStorage2d[idx].size();
    for (int j=0; j<size; j++){
        if(bankStorage2d[idx][j].id == id){
            return true;
       }
    }

    return false; 
}


bool Chaining::deleteAccount(std::string id) {                              //************

    int idx = hash(id);       
    int size = bankStorage2d[idx].size();
    for (int j=0; j<size; j++){
        if(bankStorage2d[idx][j].id == id){
            bankStorage2d[idx].erase(bankStorage2d[idx].begin() + j);
            return true;
        }
    }
    return false; 
}

int Chaining::databaseSize() {           
                                    // *******
    int t=0;
    for(int i=0; i<bankStorage2d.size(); i++){
        t = t+ bankStorage2d[i].size();
    }
    return t; 
}


int Chaining::hash(std::string id) {                                        // *******
 
    //calculating ASCII sum for all char in a string
    int sum=0;
    for (int i=0; i<id.size(); i++) {
        sum = abs(sum + (static_cast<int>(id[i])*(i+1)));
    }

    // Calculating hash value of a string
    int idx = sum % 99991;
    return idx;
}

