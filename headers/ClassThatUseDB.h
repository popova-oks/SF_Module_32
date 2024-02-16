#pragma once
#include "DBConnection.h"
#include "Result.h"

class ClassThatUseDB {
  public:
    ClassThatUseDB() : m_db (nullptr) {}
    virtual ~ClassThatUseDB() { }

    bool openConnection(DBConnectionInterface *db, int socket) {
        if (db == nullptr) {
            return false;
        }
        if (db->open(socket)) {
            m_db = db;
            return true;
        }
        return false; // Ошибка при открытии соединения
    }

    bool closeConnection(DBConnectionInterface *db, int socket) {
        if (db == nullptr) {
            return false;
        }
        if (db->close(socket)) {
            m_db = db;
            return true;
        }
        return false; // Ошибка при открытии соединения
    }

    Result useConnection (DBConnectionInterface *db, const std::string& query) {
        if (db == nullptr) {
            return Result();
        }
        m_db = db;        
        return m_db->execQuery(query);
    }

  private:
    DBConnectionInterface* m_db;
};