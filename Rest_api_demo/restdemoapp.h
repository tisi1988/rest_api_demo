#ifndef RESTDEMOAPP_H
#define RESTDEMOAPP_H

/**
 * @file   restdemoapp.h
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  RestDemoApp class declaration.
 */

#include <QObject>
#include "requestsmanager.h"

/**
 * @brief The RestDemoApp class implements the initialization of the
 * application.
 * In addition, this class receives the messages from the endpoints notifying new requests
 * and delegates them to the Requests Manager. So, this class does not implements any business logic.
 */
class RestDemoApp : public QObject {
    Q_OBJECT
public:

    /**
     * @brief Class constructor.
     */
    explicit RestDemoApp();

    /**
     * @brief Class destructor.
     */
    ~RestDemoApp(){
        if(nullptr != requests_manager_){
            delete requests_manager_;
        }
    }

public slots:

    /**
     * @brief The method who handles all the QEvents received by this class.
     * @param event The event received.
     * @return True if the event must be handled by Qt, false otherwise.
     */
    bool event(QEvent* event);

private:
    RequestsManager* requests_manager_ = nullptr;   //!< The Requests Manager to delegate the received requests to.
};

#endif // RESTDEMOAPP_H
