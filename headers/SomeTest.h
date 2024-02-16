#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../headers/DBConnection.h"
#include "../headers/ClassThatUseDB.h"

class  MockDBConnection : public DBConnectionInterface {
  public:
    MOCK_METHOD(bool, open, (int socket), (override));
    MOCK_METHOD(bool, close, (int socket), (override));
    MOCK_METHOD(Result, execQuery, (const std::string& query), (override));
};


//создаем фикстуру и тирдаун для наших тестов «на всякий случай»
class SomeTestSuite : public ::testing::Test {
  protected:
    void SetUp() { dbconnection = new DBConnection; }
    void TearDown() { delete dbconnection; }
  protected:
    DBConnectionInterface* dbconnection;
};

TEST_F(SomeTestSuite, testcase1) {
    int socket = 0;
    bool reference = true;
    bool responce = dbconnection->open (socket);
    ASSERT_EQ(reference, responce);
}

TEST_F(SomeTestSuite, testcase2) {
    int socket = 0;
    bool reference = true;
    bool responce = dbconnection->close (socket);
    ASSERT_EQ(reference, responce);
}

TEST_F(SomeTestSuite, testcase3) {
    std::string query {"XXXXX"};
    Result reference (query);
    Result responce = dbconnection->execQuery (query);
    ASSERT_EQ(reference, responce);
}

TEST_F(SomeTestSuite, testcase4) {
    int socket = 0;
    std::string query {"XXXXX"};
    Result result (query);

    // создаем мок объект для тестируемого класса
    MockDBConnection *DBConn_mock = new MockDBConnection;
    // задаем мок объекту методы класса для тестирования
    EXPECT_CALL(*DBConn_mock, open(socket)).WillOnce(::testing::Return(true));
    EXPECT_CALL(*DBConn_mock, close(socket)).WillOnce(::testing::Return(true));
    EXPECT_CALL(*DBConn_mock, execQuery(query)).WillOnce(::testing::Return(result));

    // создаем объект класса для тестирования
    ClassThatUseDB *classThatUseDB = new ClassThatUseDB;
    bool responce1 = classThatUseDB->openConnection(DBConn_mock, socket);
    bool responce2 = classThatUseDB->closeConnection(DBConn_mock, socket);
    Result responce3 = classThatUseDB->useConnection(DBConn_mock, query);

    ASSERT_EQ(true, responce1);
    ASSERT_EQ(true, responce2);
    ASSERT_EQ(result, responce3);

    delete classThatUseDB;
    delete DBConn_mock;
}
