#include "requestevents.h"

const QEvent::Type RegisterRequestEvent::ID =
    static_cast<QEvent::Type>(QEvent::registerEventType());
const QEvent::Type UpdateRequestEvent::ID =
    static_cast<QEvent::Type>(QEvent::registerEventType());
const QEvent::Type DeleteRequestEvent::ID =
    static_cast<QEvent::Type>(QEvent::registerEventType());
const QEvent::Type ViewRequestEvent::ID =
    static_cast<QEvent::Type>(QEvent::registerEventType());
const QEvent::Type GetDecryptDataRequestEvent::ID =
    static_cast<QEvent::Type>(QEvent::registerEventType());
/*
const QEvent::Type RegisterResponseCommand::ID =
    static_cast<QEvent::Type>(QEvent::registerEventType());
const QEvent::Type UpdateResponseCommand::ID =
    static_cast<QEvent::Type>(QEvent::registerEventType());
const QEvent::Type DeleteResponseCommand::ID =
    static_cast<QEvent::Type>(QEvent::registerEventType());
const QEvent::Type ViewResponseCommand::ID =
    static_cast<QEvent::Type>(QEvent::registerEventType());
const QEvent::Type GetDecryptDataResponseCommand::ID =
    static_cast<QEvent::Type>(QEvent::registerEventType());
*/
