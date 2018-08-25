/**
 * @file   requestevents.cpp
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  Request events message id registration on Qt.
 */

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
