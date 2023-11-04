#include "LinearProbing.h"
#include "BaseClass.h"
int sz=150000;
void LinearProbing::createAccount(std::string id, int count) {
    if(resize==1){
        bankStorage1d.resize(sz);
        resize=0;
    }
    Account a;
    a.balance=count;
    a.id=id;
    int i = hash(id);
    int j=0;
    while(bankStorage1d[i].id.length()!=0){
            j++;
            i=(i+j)%sz;
            
    }
    // indices.push_back(i);
    bankStorage1d[i]=a;
    
}
std::vector<int> LinearProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std::vector<int> top;
    std::vector<int> topK;
    int n=0;
    for(int i=0;i<sz;i++){
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

int LinearProbing::getBalance(std::string id) {
    for(int i=0;i<bankStorage1d.size();i++){
            if(bankStorage1d[i].id==id){
                return bankStorage1d[i].balance;
            }
    }
    return -1; 
}

bool LinearProbing::doesExist(std::string id) {
   for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id==id){
                return true;
            }
        }
    return false; 
}

void LinearProbing::addTransaction(std::string id, int count) {
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


bool LinearProbing::deleteAccount(std::string id) {
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id==id){
                bankStorage1d[i].id="";
                return true;
        }
    }
    return false;
}
int LinearProbing::databaseSize() {
    int size=0;
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id.length()!=0){
            size++;    
        }
    }
    return size; 
}

int LinearProbing::hash(std::string id) {
    int n=0;
    for(int i=0;i<id.length();i++){
        n=n+id[i];
    }
    return n%142867; 
}