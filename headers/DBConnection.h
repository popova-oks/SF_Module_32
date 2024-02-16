#pragma once
#include "DBConnectionInterface.h"

class DBConnection : public DBConnectionInterface {
  public:
    DBConnection() {}
    virtual ~DBConnection() {}

    bool open(int socket) override {
            return true;
    }

    bool close(int socket) override {
            return true;
    }

    Result execQuery(const std::string& query) override {        
        return Result(query);
    }
};