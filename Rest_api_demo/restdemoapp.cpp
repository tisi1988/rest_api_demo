#include "restdemoapp.h"

RestDemoApp::RestDemoApp() : QObject(nullptr){

    // Create endpoints
    quint16 webservice_port = 8088;
    // Create Register endpoint
    EndpointRegister* ep_register = new EndpointRegister(this, webservice_port);
    // Create Delete endpoint
    EndpointDelete* ep_delete = new EndpointDelete(this, webservice_port);
    // Create Update endpoint
    EndpointUpdate* ep_update = new EndpointUpdate(this, webservice_port);
    // Create View endpoint
    EndpointView* ep_view = new EndpointView(this, webservice_port);
    // Create GetDecryptedData endpoint
    EndpointGetDecrypData* ep_get_decryp_data = new EndpointGetDecrypData(this, webservice_port);

    // Create DBController
    QSqlDatabase *database = new QSqlDatabase();
    DBController* db_controller = new DBController(database);

    // Create the manager (business logic)
    requests_manager_ = new RequestsManager(ep_register,
                                            ep_delete,
                                            ep_update,
                                            ep_view,
                                            ep_get_decryp_data,
                                            db_controller);

}

bool RestDemoApp::event(QEvent* event) {
    // Identify the message received trough a dynamic cast and delegate the call to the manager
    if(event->type() == RegisterRequestEvent::ID) {
        RegisterRequestEvent *m =static_cast<RegisterRequestEvent*>(event);
        qDebug() << QString("-->%1").arg(m->toString());
        requests_manager_->onRegisterRequestEvent(m->getRequestId(), m->getContent());
    } else if(event->type() == UpdateRequestEvent::ID) {
        UpdateRequestEvent *m =static_cast<UpdateRequestEvent*>(event);
        qDebug() << QString("-->%1").arg(m->toString());
        requests_manager_->onUpdateRequestEvent(m->getRequestId(), m->getContent());
    } else if(event->type() == DeleteRequestEvent::ID) {
        DeleteRequestEvent *m =static_cast<DeleteRequestEvent*>(event);
        qDebug() << QString("-->%1").arg(m->toString());
        requests_manager_->onDeleteRequestEvent(m->getRequestId(), m->getContentId());
    } else if(event->type() == ViewRequestEvent::ID) {
        ViewRequestEvent *m =static_cast<ViewRequestEvent*>(event);
        qDebug() << QString("-->%1").arg(m->toString());
        requests_manager_->onViewRequestEvent(m->getRequestId(), m->getContentId());
    } else if(event->type() == GetDecryptDataRequestEvent::ID) {
        GetDecryptDataRequestEvent *m =static_cast<GetDecryptDataRequestEvent*>(event);
        qDebug() << QString("-->%1").arg(m->toString());
        requests_manager_->onGetDecryptDataRequestEvent(m->getRequestId(), m->getDeviceId(), m->getContentId());
    } else {
        qWarning() << "Unknown message id " << event->type();
    }
    return true;
}
