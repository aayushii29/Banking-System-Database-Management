#include "Chaining.h"

using namespace std;

void Chaining::createAccount(std::string id, int count) {
    if (resize == 1) {
        bankStorage2d.resize(100000);
        resize = 0;
    }
    Account a;
    a.balance = count;
    a.id = id;
    int i = hash(id);
    bankStorage2d[i].push_back(a);
}

std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> top;
    std::vector<int> topK;
    int n = 0;
    for (int i = 0; i < bankStorage2d.size(); i++) {
        for (int j = 0; j < bankStorage2d[i].size(); j++) {
            top.push_back(bankStorage2d[i][j].balance);
        }
    }
    // Implementing insertion sort
    for (int i = 0; i < top.size(); i++) {
        int j = i - 1;
        int key = top[i];
        while (j >= 0 && top[j] < key) {
            top[j + 1] = top[j];
            j--;
        }
        top[j + 1] = key;
    }
    while (n < k && n < top.size()) {
        topK.push_back(top[n]);
        n++;
    }
    return topK;
}

int Chaining::getBalance(std::string id) {
    int idx = hash(id);
    if (idx >= 0 && idx < bankStorage2d.size()) { // Bounds checking
        for (int i = 0; i < bankStorage2d[idx].size(); i++) {
            if (bankStorage2d[idx][i].id == id) {
                return bankStorage2d[idx][i].balance;
            }
        }
    }
    return -1;
}

void Chaining::addTransaction(std::string id, int count) {
    if (doesExist(id) == false) {
        if (count >= 0) {
            createAccount(id, count);
        } else {
            createAccount(id, 0);
        }
    }
    int idx = hash(id);
    if (idx >= 0 && idx < bankStorage2d.size()) { // Bounds checking
        for (int i = 0; i < bankStorage2d[idx].size(); i++) {
            if (bankStorage2d[idx][i].id == id) {
                if (bankStorage2d[idx][i].balance + count >= 0) {
                    bankStorage2d[idx][i].balance += count;
                } else {
                    bankStorage2d[idx][i].balance = 0;
                }
            }
        }
    }
}

bool Chaining::doesExist(std::string id) {
    int idx = hash(id);
    if (idx >= 0 && idx < bankStorage2d.size()) { // Bounds checking
        for (int i = 0; i < bankStorage2d[idx].size(); i++) {
            if (bankStorage2d[idx][i].id == id) {
                return true;
            }
        }
    }
    return false;
}

bool Chaining::deleteAccount(std::string id) {
    if (doesExist(id) == true) {
        int idx = hash(id);
        if (idx >= 0 && idx < bankStorage2d.size()) { // Bounds checking
            for (int i = 0; i < bankStorage2d[idx].size(); i++) {
                if (bankStorage2d[idx][i].id == id) {
                    // Instead of setting id to an empty string, erase the element
                    bankStorage2d[idx].erase(bankStorage2d[idx].begin() + i);
                    return true;
                }
            }
        }
    }
    return false;
}

int Chaining::databaseSize() {
    int size = 0;
    for (int i = 0; i < bankStorage2d.size(); i++) {
        size += bankStorage2d[i].size();
    }
    return size;
}

int Chaining::hash(std::string id) {
    // // Implement your hash function here
    // // The code you provided for the hash function seems fine
    // std::string last7Digits;
    // last7Digits = id.substr(id.length() - 7);
    // int intNum = std::stoi(last7Digits);
    // return intNum % 99991;
    int n=0;
    for(int i=0;i<id.length();i++){
        n=n+id[i];
    }
    return n%99991;
}