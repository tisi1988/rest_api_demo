#ifndef DEVICE_H
#define DEVICE_H

/**
 * @file   device.h
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  The declaration the Device class.
 */

#include <QtCore>

/**
 * @brief The Content class implements the
 * Device entity of the datamodel.
 */
class Device
{
public:

    /**
     * @brief Class constructor.
     */
    explicit Device();

    /**
     * @brief Class constructor.
     * @param id The device identifier.
     * @param descriptiveName The device descriptive name.
     * @param protectionSystemId The Protection System sued by the device.
     */
    explicit Device(const qint64& id, const QString& descriptiveName, qint8 protectionSystemId);

    /**
     * @return the device ID.
     */
    qint64 getId() const;

    /**
     * @return the device descriptive name.
     */
    QString getDescriptiveName() const;

    /**
     * @return the device Protection System.
     */
    qint8 getProtectionSystemId() const;

    /**
     * @brief Sets a a new id.
     * @param id The new device id.
     */
    void setId(const qint64 &id);

    /**
     * @brief Sets a new descriptive name.
     * @param id The new device descriptive name.
     */
    void setDescriptiveName(const QString &descriptive_name);

    /**
     * @brief Sets a new Protection System.
     * @param id The new device Protection System.
     */
    void setProtectionSystemId(const qint8 &protection_system_id);

private:
    qint64 id_;                    //!< A numerical identifier of the device
    QString descriptive_name_;     //!< Descriptive name
    qint8 protection_system_id_;   //!< Associated protection system
};

#endif // DEVICE_H
