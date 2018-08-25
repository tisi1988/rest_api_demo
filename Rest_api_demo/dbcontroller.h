#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

/**
 * @file   dbcontroller.h
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  Database Controller class declaration.
 */

#include <QtCore>
#include <QtSql/qsqldatabase.h>
#include "datamodel/content.h"
#include "datamodel/device.h"
#include "datamodel/protectionsystem.h"

/**
 * @brief The DBController class implements the API to handle
 * an SQLite database using the native Qt API for SQL databases.
 * This controller only provides methods to work with content
 * data as specified on the requeriments.
 * This class des not implements any business logic.
 */
class DBController
{
public:

    /**
     * @brief Class constructor.
     * @param database The database instance to use.
     */
    DBController(QSqlDatabase* database);

    /**
     * @brief Closes the database if it is open.
     */
    void close();

    /**
     * @brief Registers (creates) a new Content entrance on the database.
     * @param content The Content data to insert on the database.
     * @param errorMessage The resulting error message.
     * @return True if no error occurred, false otherwise.
     */
    bool registerContent(const Content& content, QString* errorMessage);

    /**
     * @brief Deletes a Content entrance from the database.
     * @param id The Content id of the Content data to remove from the database.
     * @param errorMessage The resulting error message.
     * @return True if no error occurred, false otherwise.
     */
    bool deleteContent(const qint64& id, QString* errorMessage);

    /**
     * @brief Updates a Content entrance on the database.
     * @param content The new Content data to write on the database.
     * @param errorMessage The resulting error message.
     * @return True if no error occurred, false otherwise.
     */
    bool updateContent(const Content& content, QString* errorMessage);

    /**
     * @brief Retrieves Content data from the database.
     * @param id The Content id of the Content data to get from the database.
     * @param errorMessage The resulting error message.
     * @return True if no error occurred, false otherwise.
     */
    bool getContent(const qint64& id, Content* content, QString* errorMessage);

    /**
     * @brief Retrieves Device data from the database.
     * @param id The Device id of the Content data to get from the database.
     * @param errorMessage The resulting error message.
     * @return True if no error occurred, false otherwise.
     */
    bool getDevice(const qint64& id, Device* device, QString* errorMessage);

    /**
     * @brief Retrieves Protection System data from the database.
     * @param id The Protection System id of the Content data to get from the database.
     * @param errorMessage The resulting error message.
     * @return True if no error occurred, false otherwise.
     */
    bool getProtectionSystem(const qint64& id, ProtectionSystem* protectionSystem, QString* errorMessage);

private:

    static const QString DB_CONNECTION_NAME;                //!< The kind of connection to the database.
    static const QString DB_FILENAME;                       //!< The database fielname
    static const QString DB_USER;                           //!< The username to open the database.
    static const QString DB_PASSWORD;                       //!< The password to open the database.
    static const QString DB_TABLE_DEVICES_NAME;             //!< The Device table name.
    static const QString DB_TABLE_PROTECTION_SYSTEMS_NAME;  //!< The Protection Systems table name.
    static const QString DB_TABLE_CONTENT_NAME;             //!< The Content table name.

    /**
     * @brief Called when the application starts. If the
     * database does not exists yet, it inserts some static
     * data as example.
     */
    void insertStaticData();

    bool db_is_opened_ = false;         //!< Falg to know if the databse is already open.
    QSqlDatabase* database_ = nullptr;  //!< The database pointer.
};

#endif // DBCONTROLLER_H
