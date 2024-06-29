#include "QuadraticProbing.h"
using namespace std;

QuadraticProbing::QuadraticProbing(){
    bankStorage1d.resize(131072, Account{"",0});
    datasize=0;
}

void QuadraticProbing::createAccount(std::string id, int count) {
    Account MyAcc{id,count};
    int ix = hash(id);
    int temp =ix;
    int i = 1;
    while (bankStorage1d[ix].id!= "" && bankStorage1d[ix].id!="*") {
        ix = (temp +((i*(i+1))/2) ) % 131072;
        i++;
    }
    bankStorage1d[ix] = MyAcc;
    datasize++;
}

std::vector<int> QuadraticProbing::getTopK(int k) {
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

int QuadraticProbing::getBalance(std::string id) {
    int ix = hash(id);
        int temp =ix;
        int i = 1;
        while (bankStorage1d[ix].id!= id && bankStorage1d[ix].id != ""  && i<131073) {
            ix = (temp + ((i*(i+1))/2)) % 131072;
            i++;
        }
        if(bankStorage1d[ix].id==id){
            return bankStorage1d[ix].balance;
        }
    return -1;
}

void QuadraticProbing::addTransaction(std::string id, int count) {
    int ix = hash(id);
        int temp = ix;
        int i = 1;
        while (bankStorage1d[ix].id!= id && bankStorage1d[ix].id != "" && i<131073) {
            ix = (temp + ((i*(i+1))/2)) % 131072;
            i++;
        }
        if(bankStorage1d[ix].id==id){
        bankStorage1d[ix].balance = bankStorage1d[ix].balance + count;
        return;
        }
    createAccount(id,count);
}

bool QuadraticProbing::doesExist(std::string id) {
    int ix = hash(id);
    int temp = ix; 
    int i = 1;
    
    while (bankStorage1d[ix].id != id && bankStorage1d[ix].id != "" && i<131073) {
        ix = (temp + ((i*(i+1))/2)) % 131072;
        i++;
    }
    if(bankStorage1d[ix].id==id){
        return true;
    }
    return false;
}

bool QuadraticProbing::deleteAccount(std::string id) {
    int ix = hash(id);
    int temp = ix; 
    int i = 1;

    while (bankStorage1d[ix].id != id && bankStorage1d[ix].id != "" && i<131073) {
        ix = (temp + ((i*(i+1))/2)) % 131072;
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

int QuadraticProbing::databaseSize() {
    return datasize;
}

int QuadraticProbing::hash(std::string id) {
    //calculating ASCII sum for all char in a string
    int sum=0;
    int arr[]={37, 31, 47, 43, 43};
    for (int i=0; i<id.size(); i++) {
        sum = abs(sum + (static_cast<int>(id[i]))*arr[(i%5)]);
    }
    // Calculating hash value of a string
    int idx = sum % 131072;
    return idx;
}

// int main()
// {

//     QuadraticProbing *hash_table = new QuadraticProbing();

//     // hash_table->createAccount("HDRJ2671637_2748164828", 78646);
//     // hash_table->createAccount("KAUN6873643_1837490284", 2637);
//     // hash_table->createAccount("HDRJ2671637_2748164882", 183783);
//     // hash_table->createAccount("HDJR2671637_2748164882", 3);
//     // hash_table->createAccount("MDUF4816839_0197826749", 4893);

//     cout << hash_table->hash("HDRJ2671637_2748164828") << "\n";
//     cout << hash_table->hash("KAUN6873643_1837490284") << "\n";
//     cout << hash_table->hash("HDRJ2671637_2748164882") << "\n";
//     cout << hash_table->hash("HDJR2671637_2748164882") << "\n";
//     cout << hash_table->hash("MDUF4816839_0197826749") << "\n";

//     // cout << hash_table->getBalance("HDRJ2671637_2748164828") << "\n";
//     // cout << hash_table->getBalance("KAUN6873643_1837490284") << "\n";
//     // cout << hash_table->getBalance("HDRJ2671637_2748164882") << "\n";
//     // cout << hash_table->getBalance("HDJR2671637_2748164882") << "\n";
//     // cout << hash_table->getBalance("MDUF4816839_0197826749") << "\n";

//     // vector<int> abcd = hash_table->getTopK(7);
//     // for (int i = 0; i < abcd.size(); i++)
//     // {
//     //     cout << abcd[i] << " ";
//     // }

//     // cout << "done" << endl;

//     // hash_table->addTransaction("HDRJ2671637_2848164828", 79829272);

//     // cout << hash_table->databaseSize() << "\n";

//     // vector<int> a = hash_table->getTopK(5);
//     // for (int i = 0; i < a.size(); i++)
//     // {
//     //     cout << a[i] << " ";
//     // }
//     // cout << endl;

//     // cout << hash_table->deleteAccount("MDUF4816839_0197826749") << endl;
//     // cout << hash_table->databaseSize() << endl;
//     // cout << hash_table->deleteAccount("ZZUF4816839_0197826749") << endl;
//     // cout << hash_table->databaseSize() << endl;

//     // cout << hash_table->doesExist("MDUF4816839_0197826749") << endl;
//     // cout << hash_table->doesExist("MDUF4999839_0197826749") << endl;

//     // hash_table->addTransaction("KAUN6873643_1837490284", 637657);
//     // cout << hash_table->getBalance("KAUN6873643_1837490284") << "\n";
//     // cout << hash_table->databaseSize() << endl;

//     // cout << hash_table->getBalance("ZZZZ2671637_2748164828") << "\n";
//     // cout << "done" << endl;
// }