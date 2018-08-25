#ifndef CONTENT_H
#define CONTENT_H

/**
 * @file   content.h
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  The declaration the Content class.
 */

#include <QtCore>

/**
 * @brief The Content class implements the
 * Content entity of the datamodel.
 */
class Content
{
public:

    /**
     * @brief Class constructor.
     */
    explicit Content();

    /**
     * @brief Class constructor.
     * @param id The content identifier.
     * @param protectionSystemId The Protection System used by this content.
     * @param key The encryption key used.
     * @param payloadData The encrypted content payload.
     */
    explicit Content(const qint64& id, qint8 protectionSystemId, const QString& key, const QByteArray& payloadData);

    /**
     * @return the Content identifier.
     */
    qint64 getId() const;

    /**
     * @return the Protection System used by this content.
     */
    qint8 getProtectionSystemId() const;

    /**
     * @return the encryption key used.
     */
    QString getDecryptKey() const;

    /**
     * @return the encrypted content payload.
     */
    QByteArray getPayloadData() const;

    /**
     * @brief Sets a new identifier.
     * @param id The new content identifier.
     */
    void setId(const qint64 &id);

    /**
     * @brief Sets a new Protection System.
     * @param id The new Protection System.
     */
    void setProtectionSystemId(const qint8 &protection_system_id);

    /**
     * @brief Sets a new decryption key.
     * @param id The new decryption key.
     */
    void setDecryptKey(const QString &decrypt_key);

    /**
     * @brief Sets a new payload.
     * @param id The new payload.
     */
    void setPayloadData(const QByteArray &payload_data);

private:
    qint64 id_;                     //!< A numerical identifier of the content
    qint8 protection_system_id_;    //!< An associated protection system
    QString decrypt_key_;           //!< The symmetric key to decipher the content
    QByteArray payload_data_;       //!<A payload of data that are protected with the protection system
};

#endif // CONTENT_H
