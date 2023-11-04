#ifndef CUBICPROBING_H
#define CUBICPROBING_H

#include "BaseClass.h"
#include <iostream>

class CubicProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    // // Other data members and functions specific to Quadratic Probing
    // void merge(std::vector<int>& arr, int left, int mid, int right);
    // void mergeSort(std::vector<int>& arr, int left, int right);
    
};


#endif // CUBICPROBING_H
