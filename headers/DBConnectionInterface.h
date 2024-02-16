#pragma once
#include <string>
#include "Result.h"

class DBConnectionInterface {
  public:
    DBConnectionInterface() {}
    virtual ~DBConnectionInterface() {}

    virtual bool open(int socket) = 0;
    virtual bool close(int socket) = 0;
    virtual Result execQuery(const std::string& query) = 0;
};