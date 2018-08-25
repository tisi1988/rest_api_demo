#ifndef REQUESTEVENTS_H
#define REQUESTEVENTS_H

/**
 * @file   requestevents.h
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  Requests events declaration. These events
 * are used by the endpoints to notify the application
 * the requests received and their parameters.
 * These messages inherit from the Qt native QEvent class
 * and they're delivered to the application using the Qt's
 * native message system on an asynchronous way.
 * By this way we can ensure when a request is parsed, the
 * endpoints thread goes back to listening for new requests
 * since the message is then handled by another thread
 * (Qt's Event Loop thread).
 */

#include <QtCore>
#include "datamodel/content.h"

/******************
 * REQUEST EVENTS
 * ***************/

/**
 * @brief The RegisterRequestEvent class declares the message to notify
 * a new Register request.
 */
class RegisterRequestEvent : public QEvent {
public:

    static const QEvent::Type ID; //!< The message ID

    /**
     * @brief Class constructor.
     * @param requestId The request identifier.
     * @param content The content to insert on the database.
     */
    explicit RegisterRequestEvent(const quint64& requestId, const Content& content)
        : QEvent(ID), request_id_(requestId), content_(content) {
        // Nothing to do
    }

    /**
     * @return the request id this message belongs to.
     */
    inline quint64 getRequestId() const noexcept {
        return request_id_;
    }

    /**
     * @return the content to insert on the database.
     */
    inline Content getContent() const {
        return content_;
    }

    /**
     * @return message description.
     */
    inline QString toString() const {
        return QString("RegisterRequestEvent - Request Id %1").arg(request_id_);
    }

private:
    quint64 request_id_;    //!< The request id this message belongs to.
    Content content_;       //!< The content to insert on the database.
};

/**
 * @brief The UpdateRequestEvent class declares the message to notify
 * a new Update request.
 */
class UpdateRequestEvent : public QEvent {
public:

    static const QEvent::Type ID; //!< The message ID

    /**
     * @brief Class constructor.
     * @param requestId The request identifier.
     * @param content The content to insert on the database.
     */
    explicit UpdateRequestEvent(const quint64& requestId, const Content& content)
        : QEvent(ID), request_id_(requestId), content_(content) {
        // Nothing to do
    }

    /**
     * @return the request id this message belongs to.
     */
    inline quint64 getRequestId() const noexcept {
        return request_id_;
    }

    /**
     * @return the new content to write on the database.
     */
    inline Content getContent() const {
        return content_;
    }

    /**
     * @return message description.
     */
    inline QString toString() const {
        return QString("UpdateRequestEvent - Request Id %1").arg(request_id_);
    }

private:
    quint64 request_id_;    //!< The request id this message belongs to.
    Content content_;       //!< The new content to write on the database.
};

/**
 * @brief The DeleteRequestEvent class declares the message to notify
 * a new Delete request.
 */
class DeleteRequestEvent : public QEvent {
public:

    static const QEvent::Type ID; //!< The message ID

    /**
     * @brief Class constructor.
     * @param requestId The request identifier.
     * @param id The content id to remove.
     */
    explicit DeleteRequestEvent(const quint64& requestId, const qint64& id)
        : QEvent(ID), request_id_(requestId), content_id_(id) {
        // Nothing to do
    }

    /**
     * @return the request id this message belongs to.
     */
    inline quint64 getRequestId() const noexcept {
        return request_id_;
    }

    /**
     * @return the content id to remove.
     */
    inline qint64 getContentId() const {
        return content_id_;
    }

    /**
     * @return message description.
     */
    inline QString toString() const {
        return QString("DeleteRequestEvent - Request Id %1 Content Id: %2").arg(request_id_).arg(content_id_);
    }

private:
    quint64 request_id_;    //!< The request id this message belongs to.
    qint64 content_id_;     //!< The content id to remove.
};

/**
 * @brief The ViewRequestEvent class declares the message to notify
 * a new View request.
 */
class ViewRequestEvent : public QEvent {
public:

    static const QEvent::Type ID; //!< The message ID

    /**
     * @brief Class constructor.
     * @param requestId The request identifier.
     * @param id The content id to view.
     */
    explicit ViewRequestEvent(const quint64& requestId, const qint64& id)
        : QEvent(ID), request_id_(requestId), content_id_(id) {
        // Nothing to do
    }

    /**
     * @return the request id this message belongs to.
     */
    inline quint64 getRequestId() const noexcept {
        return request_id_;
    }

    /**
     * @return the content id to view.
     */
    inline qint64 getContentId() const {
        return content_id_;
    }

    /**
     * @return message description.
     */
    inline QString toString() const {
        return QString("ViewRequestEvent - Request Id %1 Content Id: %2").arg(request_id_).arg(content_id_);
    }

private:
    quint64 request_id_;    //!< The request id this message belongs to.
    qint64 content_id_;     //!< The content id to view.
};

/**
 * @brief The GetDecryptDataRequestEvent class declares the message to notify
 * a new request to get some content data decrypted.
 */
class GetDecryptDataRequestEvent : public QEvent {
public:

    static const QEvent::Type ID; //!< The message ID

    /**
     * @brief Class constructor.
     * @param deviceId The device id.
     * @param contentId The content id to decrypt.
     */
    explicit GetDecryptDataRequestEvent(const quint64& requestId, const qint64& deviceId, const qint64& contentId)
        : QEvent(ID), request_id_(requestId), device_id_(deviceId), content_id_(contentId) {
        // Nothing to do
    }

    /**
     * @return the request id this message belongs to.
     */
    inline quint64 getRequestId() const noexcept {
        return request_id_;
    }

    /**
     * @return the device id.
     */
    inline qint64 getDeviceId() const {
        return device_id_;
    }

    /**
     * @return the content id to decrypt.
     */
    inline qint64 getContentId() const {
        return content_id_;
    }

    /**
     * @return message description.
     */
    inline QString toString() const {
        return QString("ViewRequestEvent - Request Id %1 Device Id: %2 Content Id: %3").arg(request_id_).arg(device_id_).arg(content_id_);
    }

private:
    quint64 request_id_;    //!< The request id this message belongs to.
    qint64 device_id_;      //!< The device id.
    qint64 content_id_;     //!< The content id to decrypt.
};
#endif // REQUESTEVENTS_H
