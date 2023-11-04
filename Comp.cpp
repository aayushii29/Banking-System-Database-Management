#include "Comp.h"
int resize=1;
void Comp::createAccount(std::string id, int count) {
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

std::vector<int> Comp::getTopK(int k) {
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


int Comp::getBalance(std::string id) {
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

void Comp::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
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

bool Comp::doesExist(std::string id) {
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

bool Comp::deleteAccount(std::string id) {
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
int Comp::databaseSize() {
    int size = 0;
    for (int i = 0; i < bankStorage2d.size(); i++) {
        size += bankStorage2d[i].size();
    }
    return size;
}

int Comp::hash(std::string id) {
    int hashValue = 0;
    for (int i = 0; i < id.length(); i++) {
        hashValue = (hashValue *128 + id[i]) % 31;
    }
    return hashValue;
}


// Feel free to add any other helper functions you need
// Good Luck!