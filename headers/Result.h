#pragma once
#include <iostream>
#include <string.h>

//класс для представления массива байт
class Result {
  public:
    Result() {}
    Result(const std::string& query) {
        data_ = new char[query.size()];
        for (int i = 0; i < query.size(); i++) {
            data_[i] = query[i];
        }
    }
    //~Result() { delete[] data_; }
    bool operator==(const Result& other) const { 
    if (data_ == nullptr || other.data_ == nullptr) {
        return false;
    }
    return strcmp(data_, other.data_) == 0;
}
    
 private:
    char* data_ = nullptr;
};