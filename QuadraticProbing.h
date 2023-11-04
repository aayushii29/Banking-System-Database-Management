#ifndef QUADRATICPROBING_H
#define QUADRATICPROBING_H

#include "BaseClass.h"
#include <iostream>

class QuadraticProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    bool findindex(int k);
private:
    // Other data members and functions specific to Quadratic Probing
    int resize=1;
    // void merge(std::vector<int>& arr, int left, int mid, int right);
    // void mergeSort(std::vector<int>& arr, int left, int right);
};

#endif // QUADRATICPROBING_H
