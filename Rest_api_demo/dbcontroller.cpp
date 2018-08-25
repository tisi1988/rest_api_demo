#include "dbcontroller.h"
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include "customexception.h"

const QString DBController::DB_CONNECTION_NAME = "QSQLITE";
const QString DBController::DB_FILENAME = "RakutenTv.db";
const QString DBController::DB_USER = "rakuten";
const QString DBController::DB_PASSWORD = "X-(wT!J'2Da[Na3@";
const QString DBController::DB_TABLE_DEVICES_NAME = "Devices";
const QString DBController::DB_TABLE_PROTECTION_SYSTEMS_NAME = "Protection_Systems";
const QString DBController::DB_TABLE_CONTENT_NAME = "Content";

DBController::DBController(QSqlDatabase* database)
{
    // Open the database
    database_ = database;
    database_->setHostName("bigblue");
    database_->setDatabaseName(DB_FILENAME);
    database_->setUserName(DB_USER);
    database_->setPassword(DB_PASSWORD);
    db_is_opened_ = database_->open();

    if(db_is_opened_ &&
            (!database_->tables().contains("Devices") || !database_->tables().contains("Protection_Sytems"))){
        insertStaticData();
    }
}

void DBController::close() {
    if(nullptr != database_){
        database_->close();
        db_is_opened_ = false;
    }
}

bool DBController::registerContent(const Content& content, QString* errorMessage) {
    bool ret;
    if(!db_is_opened_){
        *errorMessage = "Database is closed";
        ret = false;
    } else {
        // Check if the content is already there
        Content previous_content;
        getContent(content.getId(), &previous_content, nullptr);
        if(previous_content.getId() > -1){
            if(nullptr != errorMessage) {
                *errorMessage = "Data already inserted";
            }
            ret = false;
        } else {
            QSqlQuery query;
            query.prepare(QString("INSERT INTO %1 (id, protection_system, key, payload) VALUES (:id, :protection_system, :key, :payload)").arg(DB_TABLE_CONTENT_NAME));
            query.bindValue(":id", content.getId());
            query.bindValue(":protection_system", content.getProtectionSystemId());
            query.bindValue(":key", content.getDecryptKey());
            query.bindValue(":payload", content.getPayloadData());
            ret = query.exec();
            if(!ret) {
                *errorMessage = database_->lastError().text();
            }
        }
    }
    return ret;
}

bool DBController::deleteContent(const qint64& id, QString* errorMessage){
    bool ret;
    if(!db_is_opened_){
        if(nullptr != errorMessage) {
            *errorMessage = "Database is closed";
        }
        ret = false;
    } else {
        QSqlQuery query;
        ret = query.exec(QString("DELETE FROM %1 WHERE id = %2").arg(DB_TABLE_CONTENT_NAME).arg(id));
        if(!ret && nullptr != errorMessage) {
            *errorMessage = database_->lastError().text();
        }
    }
    return ret;
}

bool DBController::updateContent(const Content& content, QString* errorMessage){
    bool ret = true;
    try{
        if(!db_is_opened_){
            if(nullptr != errorMessage) {
                throw CustomException("Database is closed");
            }
        } else {
            Content previous_content;
            getContent(content.getId(), &previous_content, nullptr);
            if(previous_content.getId() > -1){
                QSqlQuery query;
                query.prepare(QString("UPDATE %1 SET id=:new_id, protection_system=:new_protection_system, key=:new_key, payload=:new_payload WHERE id=%2")
                              .arg(DB_TABLE_CONTENT_NAME).arg(content.getId()));
                query.bindValue(":new_id", content.getId());
                query.bindValue(":new_protection_system", content.getProtectionSystemId());
                query.bindValue(":new_key", content.getDecryptKey());
                query.bindValue(":new_payload", content.getPayloadData());
                if(!query.exec()){
                    if(nullptr != errorMessage) {
                        throw CustomException(database_->lastError().text());
                    }
                }
                ret = true;
            } else {
                if(nullptr != errorMessage) {
                    throw CustomException("There is no such data");
                }
                ret = false;
            }
        }
    } catch (const CustomException &e) {
        qWarning() << e.getMessage();
        *errorMessage = e.getMessage();
        ret = false;
    }
    return ret;
}

bool DBController::getContent(const qint64& id, Content* content, QString* errorMessage){
    bool ret = true;
    try{
        if(!db_is_opened_){
            if(nullptr != errorMessage) {
                throw CustomException("Database is closed");
            }
        } else if(nullptr == content) {
            throw CustomException("Invalid data pointer");
        } else {
            QSqlQuery query;
            ret = query.exec(QString("SELECT id, protection_system, key, payload FROM %1 WHERE id == %2").arg(DB_TABLE_CONTENT_NAME).arg(id));
            if(ret && query.next()) {
                content->setId(query.value(0).toInt());
                content->setProtectionSystemId(query.value(1).toInt());
                content->setDecryptKey(query.value(2).toString());
                content->setPayloadData(QByteArray::fromStdString(query.value(3).toString().toStdString()));
            } else {
                if(nullptr != errorMessage) {
                    throw CustomException(database_->lastError().text());
                }
            }
        }
    } catch (const CustomException &e) {
        qWarning() << e.getMessage();
        *errorMessage = e.getMessage();
        ret = false;
    }
    return ret;
}

bool DBController::getDevice(const qint64& id, Device* device, QString* errorMessage){
    bool ret = true;
    try{
        if(!db_is_opened_){
            if(nullptr != errorMessage) {
                throw CustomException("Database is closed");
            }
        } else {
            QSqlQuery query;
            ret = query.exec(QString("SELECT id, name, protection_system FROM %1 WHERE id == %2").arg(DB_TABLE_DEVICES_NAME).arg(id));
            if(ret && query.next()) {
                device->setId(query.value(0).toInt());
                device->setDescriptiveName(query.value(1).toString());
                device->setProtectionSystemId(query.value(2).toInt());
            } else {
                if(nullptr != errorMessage) {
                    throw CustomException(database_->lastError().text());
                }
            }
        }
    } catch (const CustomException &e) {
        qWarning() << e.getMessage();
        *errorMessage = e.getMessage();
        ret = false;
    }
    return ret;
}

bool DBController::getProtectionSystem(const qint64& id, ProtectionSystem* protectionSystem, QString* errorMessage) {
    bool ret = true;

    try {
        if(!db_is_opened_){
            if(nullptr != errorMessage) {
                throw CustomException("Database is closed");
            }
        } else {
            QSqlQuery query;
            ret = query.exec(QString("SELECT id, name, encryption_mode FROM %1 WHERE id == %2").arg(DB_TABLE_PROTECTION_SYSTEMS_NAME).arg(id));
            if(ret && query.next()) {
                protectionSystem->setId(query.value(0).toInt());
                protectionSystem->setDescriptiveName(query.value(1).toString());
                protectionSystem->setEncryptionMode(query.value(2).toString());
            } else {
                if(nullptr != errorMessage) {
                    throw CustomException(database_->lastError().text());
                }
            }
        }
    } catch (const CustomException &e) {
        qWarning() << e.getMessage();
        *errorMessage = e.getMessage();
        ret = false;
    }
    return ret;
}

void DBController::insertStaticData() {
    QSqlQuery query;
    // Insert Device
    query.exec(QString("create table IF NOT EXISTS %1 (id int primary key, name varchar(50), protection_system int);").arg(DB_TABLE_DEVICES_NAME));
    query.exec(QString("INSERT INTO %1 (id, name, protection_system) VALUES (1, 'Android', 1)").arg(DB_TABLE_DEVICES_NAME));
    query.exec(QString("INSERT INTO %1 (id, name, protection_system) VALUES (2, 'Samsung', 2)").arg(DB_TABLE_DEVICES_NAME));
    query.exec(QString("INSERT INTO %1 (id, name, protection_system) VALUES (3, 'iOS', 1)").arg(DB_TABLE_DEVICES_NAME));
    query.exec(QString("INSERT INTO %1 (id, name, protection_system) VALUES (4, 'LG', 2)").arg(DB_TABLE_DEVICES_NAME));

    // Insert Protection Systems
    query.exec(QString("create table IF NOT EXISTS %1 (id int primary key, name varchar(50), encryption_mode varchar(50));").arg(DB_TABLE_PROTECTION_SYSTEMS_NAME));
    query.exec(QString("INSERT INTO %2 (id, name, encryption_mode) VALUES (1, 'AES 1', 'AES + ECB')").arg(DB_TABLE_PROTECTION_SYSTEMS_NAME));
    query.exec(QString("INSERT INTO %2 (id, name, encryption_mode) VALUES (2, 'AES 2', 'AES + CBC')").arg(DB_TABLE_PROTECTION_SYSTEMS_NAME));

    // Create Contents table
    query.exec(QString("create table IF NOT EXISTS %1 (id int primary key, protection_system int, key varchar(256), payload varchar(256), FOREIGN KEY(protection_system) REFERENCES %2(id));").arg(DB_TABLE_CONTENT_NAME).arg(DB_TABLE_PROTECTION_SYSTEMS_NAME));
}
