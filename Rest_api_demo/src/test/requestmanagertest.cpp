#include "requestmanagertest.h"
#include "../customexception.h"

TEST_F(RequestManagerTest, 0_validate_protection_system_ok) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    RequestsManager manager(nullptr, nullptr, nullptr, nullptr, nullptr, db_controller);

    Content content(1, 1, "KEY", QByteArray(1, 'c'));
    QString errormsg;
    ASSERT_TRUE(db_controller->registerContent(content, &errormsg));

    ASSERT_TRUE(accessValidateProtectionSystem(&manager, 1, 1));

    db_controller->close();

    QFile("RakutenTv.db").remove();
}

TEST_F(RequestManagerTest, 1_validate_protection_system_invalid) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    RequestsManager manager(nullptr, nullptr, nullptr, nullptr, nullptr, db_controller);

    Content content(1, 2, "KEY", QByteArray(1, 'c'));
    QString errormsg;
    ASSERT_TRUE(db_controller->registerContent(content, &errormsg));

    ASSERT_FALSE(accessValidateProtectionSystem(&manager, 1, 1));

    db_controller->close();

    QFile("RakutenTv.db").remove();
}

TEST_F(RequestManagerTest, 2_decrypt_content) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    RequestsManager manager(nullptr, nullptr, nullptr, nullptr, nullptr, db_controller);

    Content content(1, 1, "1234567890123456", QByteArray("673d2d0e5bf09c2d0571173bd1381dba0d2232106701f5be6fd9e2f5911d8981b55fd7589a40a13a304e6c8e3a306537"));
    QString errormsg;
    ASSERT_TRUE(db_controller->registerContent(content, &errormsg));

    QByteArray decoded = accessDecryptPayload(&manager, 1, QAESEncryption::Mode::ECB, QAESEncryption::AES_128);

    ASSERT_STREQ(decoded.toStdString().c_str(), "This is the payload as plain text!");
    db_controller->close();

    QFile("RakutenTv.db").remove();
}

TEST_F(RequestManagerTest, 3_check_aes_modes) {

    RequestsManager manager(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    ASSERT_EQ(accessGetAesMode(&manager, "AES + ECB"), QAESEncryption::Mode::ECB);
    ASSERT_EQ(accessGetAesMode(&manager, "AES + CBC"), QAESEncryption::Mode::CBC);
    EXPECT_THROW(accessGetAesMode(&manager, "AES + XXX"), CustomException);
}

TEST_F(RequestManagerTest, 4_check_key_length_128) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    RequestsManager manager(nullptr, nullptr, nullptr, nullptr, nullptr, db_controller);

    Content content(1, 1, "1234567890123456", QByteArray("673d2d0e5bf09c2d0571173bd1381dba0d2232106701f5be6fd9e2f5911d8981b55fd7589a40a13a304e6c8e3a306537"));
    QString errormsg;
    ASSERT_TRUE(db_controller->registerContent(content, &errormsg));

    ASSERT_EQ(accessGetKeyLength(&manager, 1), QAESEncryption::AES_128);

    db_controller->close();

    QFile("RakutenTv.db").remove();
}

TEST_F(RequestManagerTest, 5_check_key_length_192) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    RequestsManager manager(nullptr, nullptr, nullptr, nullptr, nullptr, db_controller);

    Content content(1, 1, "123456789012345678901234", QByteArray("673d2d0e5bf09c2d0571173bd1381dba0d2232106701f5be6fd9e2f5911d8981b55fd7589a40a13a304e6c8e3a306537"));
    QString errormsg;
    ASSERT_TRUE(db_controller->registerContent(content, &errormsg));

    ASSERT_EQ(accessGetKeyLength(&manager, 1), QAESEncryption::AES_192);

    db_controller->close();

    QFile("RakutenTv.db").remove();
}

TEST_F(RequestManagerTest, 6_check_key_length_256) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    RequestsManager manager(nullptr, nullptr, nullptr, nullptr, nullptr, db_controller);

    Content content(1, 1, "12345678901234561234567890123456", QByteArray("673d2d0e5bf09c2d0571173bd1381dba0d2232106701f5be6fd9e2f5911d8981b55fd7589a40a13a304e6c8e3a306537"));
    QString errormsg;
    ASSERT_TRUE(db_controller->registerContent(content, &errormsg));

    ASSERT_EQ(accessGetKeyLength(&manager, 1), QAESEncryption::AES_256);

    db_controller->close();

    QFile("RakutenTv.db").remove();
}

TEST_F(RequestManagerTest, 7_check_key_length_invalid) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    RequestsManager manager(nullptr, nullptr, nullptr, nullptr, nullptr, db_controller);

    Content content(1, 1, "1", QByteArray("673d2d0e5bf09c2d0571173bd1381dba0d2232106701f5be6fd9e2f5911d8981b55fd7589a40a13a304e6c8e3a306537"));
    QString errormsg;
    ASSERT_TRUE(db_controller->registerContent(content, &errormsg));

    EXPECT_THROW(accessGetKeyLength(&manager, 1), CustomException);

    db_controller->close();

    QFile("RakutenTv.db").remove();
}

TEST_F(RequestManagerTest, 8_is_key_length_valid) {

    RequestsManager manager(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    ASSERT_FALSE(accessIsKeyValid(&manager, 0));
    ASSERT_FALSE(accessIsKeyValid(&manager, 1));
    ASSERT_TRUE(accessIsKeyValid(&manager, 128));
    ASSERT_TRUE(accessIsKeyValid(&manager, 192));
    ASSERT_TRUE(accessIsKeyValid(&manager, 256));
    ASSERT_FALSE(accessIsKeyValid(&manager, 512));

}
