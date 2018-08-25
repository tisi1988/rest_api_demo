#include "restdemoapp.h"
#include <QCoreApplication>
#include <QtDebug>

#define RUN_MODE_NORMAL 0
#define RUN_MODE_UNIT_TEST 1

int main(int argc, char *argv[])
{
    quint16 op_mode = QString::fromStdString(argv[1]).toUShort();
    qint32 ret = 0;

    if(argc != 2){
        qDebug() << "App usage: ./Rest_api_demo <mode>";
        qDebug() << "Modes: 0 for normal run, 1 for unit testing";
    } else {
        switch(op_mode){
        case RUN_MODE_NORMAL:
        {
            QCoreApplication a(argc, argv);
            new RestDemoApp();
            ret = a.exec();
            break;
        }
        case RUN_MODE_UNIT_TEST:
            qInfo() << "Running unit tests";
            // Run unit testing
            //        RUN_ALL_TESTS();
            break;
        default:
            qWarning() << "Operation mode " << op_mode << " is invalid";
            break;
        }
    }
    return ret;
}
