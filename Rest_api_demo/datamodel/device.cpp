#include "device.h"

Device::Device() :
    id_(-1), descriptive_name_(""), protection_system_id_(-1)
{
    // Nothing to do here
}

Device::Device(const qint64& id, const QString& descriptiveName, qint8 protectionSystemId) :
    id_(id), descriptive_name_(descriptiveName), protection_system_id_(protectionSystemId)
{
    // Nothing to do here
}

qint64 Device::getId() const
{
    return id_;
}

QString Device::getDescriptiveName() const
{
    return descriptive_name_;
}

qint8 Device::getProtectionSystemId() const
{
    return protection_system_id_;
}

void Device::setId(const qint64 &id)
{
    id_ = id;
}

void Device::setDescriptiveName(const QString &descriptive_name)
{
    descriptive_name_ = descriptive_name;
}

void Device::setProtectionSystemId(const qint8 &protection_system_id)
{
    protection_system_id_ = protection_system_id;
}
