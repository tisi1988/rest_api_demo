#ifndef PROTECTIONSYSTEM_H
#define PROTECTIONSYSTEM_H

/**
 * @file   protectionsystem.h
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  The declaration the Protection System class.
 */

#include <QtCore>

/**
 * @brief The Content class implements the
 * Protection System entity of the datamodel.
 */
class ProtectionSystem
{
public:

    /**
     * @brief Class cnstructor.
     */
    explicit ProtectionSystem();

    /**
     * @brief Class constructor.
     * @param id The Protection System identifier.
     * @param descriptiveName The descriptive name of a Protection System.
     * @param encryptionMode The encryption mode used by the Protection System.
     */
    explicit ProtectionSystem(qint8 id, const QString& descriptiveName, const QString& encryptionMode);

    /**
     * @return the Protection System identifier.
     */
    qint8 getId() const;

    /**
     * @return the descriptive name of a Protection System.
     */
    QString getDescriptiveName() const;

    /**
     * @return the encryption mode used by a Protection System.
     */
    QString getEncryptionMode() const;

    /**
     * @brief Sets a new identifier.
     * @param id The new Protection System identifier.
     */
    void setId(const qint8 &id);

    /**
     * @brief Seta a new descriptive name for a Protection System.
     * @param descriptive_name The new descriptive name.
     */
    void setDescriptiveName(const QString &descriptive_name);

    /**
     * @brief Seta a new encryption mode for a Protection System.
     * @param encryption_mode The new encryption mode.
     */
    void setEncryptionMode(const QString &encryption_mode);

private:
    qint8 id_;                  //!< A numerical identifier of the system
    QString descriptive_name_;  //!< Descriptive name of the Protection System
    QString encryption_mode_;   //!< Encryption mode (For instance, AES CBC)
};

#endif // PROTECTIONSYSTEM_H
