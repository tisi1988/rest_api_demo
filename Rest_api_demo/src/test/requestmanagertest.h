#ifndef REQUESTMANAGERTEST_H
#define REQUESTMANAGERTEST_H

#include <gtest/gtest.h>
#include "../requestsmanager.h"

class RequestManagerTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    bool accessValidateProtectionSystem(RequestsManager* m, const qint64 &deviceId, const qint64 &contentId) {
        return m->validateProtectionSystem(deviceId, contentId);
    }

    QByteArray accessDecryptPayload(RequestsManager* m, const qint64 contentId, QAESEncryption::Mode aesMode, QAESEncryption::Aes keyLength){
        return m->decryptPayload(contentId, aesMode, keyLength);
    }

    QAESEncryption::Mode accessGetAesMode(RequestsManager *m, const QString str){
        return m->getAesMode(str);
    }

    QAESEncryption::Aes accessGetKeyLength(RequestsManager *m, const qint64 &contentId){
        return m->getKeyLength(contentId);
    }

    bool accessIsKeyValid(RequestsManager *m, qint32 keySize) {
        return m->isKeyValid(keySize);
    }
};


#endif // REQUESTMANAGERTEST_H
