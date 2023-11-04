#include "QuadraticProbing.h"
int sz2=150000;
void QuadraticProbing::createAccount(std::string id, int count) {
    if(resize==1){
        bankStorage1d.resize(sz2);
        resize=0;
    }
    Account a;
    a.balance=count;
    a.id=id;
    int i = hash(id);
    int j=0;
    while(bankStorage1d[i].id.length()!=0){
            
            j++;
            i=(i+j*j)%sz2;
            
    }
    // indices.push_back(i);
    bankStorage1d[i]=a;
}

std::vector<int> QuadraticProbing::getTopK(int k) {
    std::vector<int> top;
    std::vector<int> topK;
    int n=0;
    for(int i=0;i<sz2;i++){
        if (bankStorage1d[i].id.size()!=0){
            top.push_back(bankStorage1d[i].balance);
        }
    }
    // Implementing insertion sort
    for(int i=0;i<top.size();i++){
        int j=i-1;
        int key=top[i];
        while (j>=0 && top[j]<key){
            top[j+1]=top[j];
            j--;
        }     
        top[j+1]=key;
    }
    while(n<k && n<top.size() ){
        topK.push_back(top[n]);
        n++;
    }
    return topK; 
}

int QuadraticProbing::getBalance(std::string id) {
    for(int i=0;i<bankStorage1d.size();i++){
            if(bankStorage1d[i].id==id){
                return bankStorage1d[i].balance;
            }
    }
    return -1; 
}

bool QuadraticProbing::doesExist(std::string id) {
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id==id){
                return true;
            }
        }
    return false;
}

void QuadraticProbing::addTransaction(std::string id, int count) {
    if(doesExist(id)==false){
        if(count>=0){
            createAccount(id,count);
        }
        else{
            createAccount(id,0);
        }
        
    }
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id==id){
            if(bankStorage1d[i].balance+count>=0){
                bankStorage1d[i].balance+=count;
            }
            else{
                bankStorage1d[i].balance=0;
            }
        }
    }
}

bool QuadraticProbing::deleteAccount(std::string id) {
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id==id){
                bankStorage1d[i].id="";
                return true;
        }
    }
    return false;
}
int QuadraticProbing::databaseSize() {
    int size=0;
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id.length()!=0){
            size++;    
        }
    }
    return size;  
}

int QuadraticProbing::hash(std::string id) {
    int n=0;
    for(int i=0;i<id.length();i++){
        n=n*id[i];
    }
    return n%142867; 
}

