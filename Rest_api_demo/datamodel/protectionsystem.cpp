#include "protectionsystem.h"

ProtectionSystem::ProtectionSystem() :
    id_(-1), descriptive_name_(""), encryption_mode_(-1)
{
    // Nothing to do here
}

ProtectionSystem::ProtectionSystem(qint8 id, const QString& descriptiveName, const QString& encryptionMode) :
    id_(id), descriptive_name_(descriptiveName), encryption_mode_(encryptionMode)
{
    // Nothing to do here
}

qint8 ProtectionSystem::getId() const
{
    return id_;
}

QString ProtectionSystem::getDescriptiveName() const
{
    return descriptive_name_;
}

QString ProtectionSystem::getEncryptionMode() const
{
    return encryption_mode_;
}

void ProtectionSystem::setId(const qint8 &id)
{
    id_ = id;
}

void ProtectionSystem::setDescriptiveName(const QString &descriptive_name)
{
    descriptive_name_ = descriptive_name;
}

void ProtectionSystem::setEncryptionMode(const QString &encryption_mode)
{
    encryption_mode_ = encryption_mode;
}
