#include "CubicProbing.h"
int sz3=150000;
int resize1=1;
void CubicProbing::createAccount(std::string id, int count) {
    if(resize1==1){
        bankStorage1d.resize(sz3);
        resize1=0;
    }
    Account a;
    a.balance=count;
    a.id=id;
    int i = hash(id);
    int j=0;
    while(bankStorage1d[i].id.length()!=0){
            
            j++;
            i=(i+j*j*j)%sz3;
            
    }
    bankStorage1d[i]=a;
}
// void CubicProbing::merge(std::vector<int>& arr, int left, int mid, int right) {
//     int n1 = mid - left + 1;    
//     int n2 = right - mid;       
//     std::vector<int> leftArr(n1);
//     std::vector<int> rightArr(n2);
//     for (int i = 0; i < n1; i++) {
//         leftArr[i] = arr[left + i];
//     }
//     for (int i = 0; i < n2; i++) {
//         rightArr[i] = arr[mid + 1 + i];
//     }
//     int i = 0; 
//     int j = 0;
//     int k = left; 

//     while (i < n1 && j < n2) {
//         if (leftArr[i] >= rightArr[j]) { 
//             arr[k] = leftArr[i];
//             i++;
//         } else {
//             arr[k] = rightArr[j];
//             j++;
//         }
//         k++;
//     }
//     while (i < n1) {
//         arr[k] = leftArr[i];
//         i++;
//         k++;
//     }
//     while (j < n2) {
//         arr[k] = rightArr[j];
//         j++;
//         k++;
//     }
// }
// void CubicProbing:: mergeSort(vector<int>& arr, int left, int right) {
//     if (left < right) {
//         int mid = left + (right - left) / 2;
//         mergeSort(arr, left, mid);
//         mergeSort(arr, mid + 1, right);
//         merge(arr, left, mid, right);
//     }
// }
std::vector<int> CubicProbing::getTopK(int k) {
    std::vector<int> top;
    std::vector<int> topK;
    int n=0;
    for(int i=0;i<sz3;i++){
        if (bankStorage1d[i].id.size()!=0){
            top.push_back(bankStorage1d[i].balance);
        }
    }
    // mergeSort(top, 0, top.size()-1);
    for(int i=0;i<top.size();i++){
        int j=i-1;
        int key=top[i];
        while (j>=0 && top[j]>key){
            top[j+1]=top[j];
            j=j-1;
        }     
        top[j+1]=key;
    }
    while(n<k && n<top.size() ){
        topK.push_back(top[n]);
        n++;
    }
    return topK; 
}

int CubicProbing::getBalance(std::string id) {
    for(int i=0;i<bankStorage1d.size();i++){
            if(bankStorage1d[i].id==id){
                return bankStorage1d[i].balance;
            }
    }
    return -1; 
}

bool CubicProbing::doesExist(std::string id) {
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id==id){
                return true;
            }
        }
    return false;
}

void CubicProbing::addTransaction(std::string id, int count) {
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

bool CubicProbing::deleteAccount(std::string id) {
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id==id){
                bankStorage1d[i].id="";
                return true;
        }
    }
    return false;
}
int CubicProbing::databaseSize() {
    int size=0;
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id.length()!=0){
            size++;    
        }
    }
    return size;  
}

int CubicProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    std::string last7Digits;
    
    last7Digits = id.substr(id.length() - 7);

    // Convert the substring to an integer using std::stoi
    int intNum = std::stoi(last7Digits);

    return intNum%142867; // Placeholder return value
}
