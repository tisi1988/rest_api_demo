#include "content.h"

Content::Content() :
    id_(-1), protection_system_id_(-1), decrypt_key_(""), payload_data_()
{
    // Nothing to do here
}

Content::Content(const qint64& id, qint8 protectionSystemId, const QString& key, const QByteArray& payloadData) :
    id_(id), protection_system_id_(protectionSystemId), decrypt_key_(key), payload_data_(payloadData)
{
    // Nothing to do here
}

qint64 Content::getId() const
{
    return id_;
}

qint8 Content::getProtectionSystemId() const
{
    return protection_system_id_;
}

QString Content::getDecryptKey() const
{
    return decrypt_key_;
}

QByteArray Content::getPayloadData() const
{
    return payload_data_;
}

void Content::setId(const qint64 &id)
{
    id_ = id;
}

void Content::setProtectionSystemId(const qint8 &protection_system_id)
{
    protection_system_id_ = protection_system_id;
}

void Content::setDecryptKey(const QString &decrypt_key)
{
    decrypt_key_ = decrypt_key;
}

void Content::setPayloadData(const QByteArray &payload_data)
{
    payload_data_ = payload_data;
}
