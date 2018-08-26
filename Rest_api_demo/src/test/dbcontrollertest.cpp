#include "dbcontrollertest.h"
#include "../customexception.h"

TEST_F(DBControllerTest, 0_open_close) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    ASSERT_TRUE(isDbOpened(db_controller));

    db_controller->close();

    ASSERT_FALSE(isDbOpened(db_controller));

    QFile("RakutenTv.db").remove();
}

TEST_F(DBControllerTest, 1_write_get_data) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    ASSERT_TRUE(isDbOpened(db_controller));

    Content content(1, 2, "KEY", QByteArray(1, 'c'));
    QString errormsg;
    ASSERT_TRUE(db_controller->registerContent(content, &errormsg));

    Content read_content;
    ASSERT_TRUE(db_controller->getContent(1, &read_content, &errormsg));

    ASSERT_EQ(content.getId(), read_content.getId());
    ASSERT_EQ(content.getProtectionSystemId(), read_content.getProtectionSystemId());
    ASSERT_STREQ(content.getDecryptKey().toStdString().c_str(), read_content.getDecryptKey().toStdString().c_str());
    ASSERT_STREQ(content.getPayloadData().toStdString().c_str(), read_content.getPayloadData().toStdString().c_str());

    db_controller->close();

    QFile("RakutenTv.db").remove();

}

TEST_F(DBControllerTest, 2_write_already_written_data) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    ASSERT_TRUE(isDbOpened(db_controller));

    Content content(1, 2, "KEY", QByteArray(1, 'c'));
    QString errormsg;
    ASSERT_TRUE(db_controller->registerContent(content, &errormsg));
    ASSERT_FALSE(db_controller->registerContent(content, &errormsg));

    Content read_content;
    db_controller->getContent(1, &read_content, &errormsg);

    ASSERT_EQ(content.getId(), read_content.getId());
    ASSERT_EQ(content.getProtectionSystemId(), read_content.getProtectionSystemId());
    ASSERT_STREQ(content.getDecryptKey().toStdString().c_str(), read_content.getDecryptKey().toStdString().c_str());
    ASSERT_STREQ(content.getPayloadData().toStdString().c_str(), read_content.getPayloadData().toStdString().c_str());

    db_controller->close();

    QFile("RakutenTv.db").remove();
}

TEST_F(DBControllerTest, 3_update_data) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    ASSERT_TRUE(isDbOpened(db_controller));

    Content content(1, 2, "KEY", QByteArray(1, 'c'));
    QString errormsg;
    ASSERT_TRUE(db_controller->registerContent(content, &errormsg));
    content.setDecryptKey("KEY2");
    ASSERT_TRUE(db_controller->updateContent(content, &errormsg));

    Content read_content;
    db_controller->getContent(1, &read_content, &errormsg);

    ASSERT_EQ(content.getId(), read_content.getId());
    ASSERT_EQ(content.getProtectionSystemId(), read_content.getProtectionSystemId());
    ASSERT_STREQ(content.getDecryptKey().toStdString().c_str(), read_content.getDecryptKey().toStdString().c_str());
    ASSERT_STREQ(content.getPayloadData().toStdString().c_str(), read_content.getPayloadData().toStdString().c_str());

    db_controller->close();

    QFile("RakutenTv.db").remove();
}

TEST_F(DBControllerTest, 4_update_unexisting_data) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    ASSERT_TRUE(isDbOpened(db_controller));

    Content content(1, 2, "KEY", QByteArray(1, 'c'));
    QString errormsg;
    ASSERT_FALSE(db_controller->updateContent(content, &errormsg));

    db_controller->close();

    QFile("RakutenTv.db").remove();
}

TEST_F(DBControllerTest, 5_remove_data) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    ASSERT_TRUE(isDbOpened(db_controller));

    QString errormsg;
    ASSERT_TRUE(db_controller->deleteContent(1, &errormsg));

    db_controller->close();

    QFile("RakutenTv.db").remove();
}

TEST_F(DBControllerTest, 6_remove_unexisting_data) {

    QSqlDatabase *database = new QSqlDatabase();
    *database = QSqlDatabase::addDatabase(DBController::DB_CONNECTION_NAME);
    DBController* db_controller = new DBController(database);

    ASSERT_TRUE(isDbOpened(db_controller));

    Content content(1, 2, "KEY", QByteArray(1, 'c'));
    QString errormsg;
    ASSERT_TRUE(db_controller->registerContent(content, &errormsg));

    ASSERT_TRUE(db_controller->deleteContent(1, &errormsg));

    Content read_content;
    ASSERT_FALSE(db_controller->getContent(1, &read_content, &errormsg));

    db_controller->close();

    QFile("RakutenTv.db").remove();
}
