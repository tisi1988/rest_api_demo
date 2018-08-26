#ifndef DBCONTROLLERTEST_H
#define DBCONTROLLERTEST_H

#include <gtest/gtest.h>
#include "../dbcontroller.h"

class DBControllerTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    bool isDbOpened(DBController *dbctl){
        return dbctl->db_is_opened_;
    }
};


#endif // DBCONTROLLERTEST_H
