QT -= gui
QT += sql

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    restdemoapp.h \
    requestsmanager.h \
    endpoints/endpointregister.h \
    endpoints/serverendpoint.h \
    endpoints/endpointdelete.h \
    endpoints/endpointupdate.h \
    endpoints/endpointview.h \
    endpoints/endpointgetdecrypdata.h \
    dbcontroller.h \
    datamodel/device.h \
    datamodel/protectionsystem.h \
    datamodel/content.h \
    qaescipher/qaesencryption.h \
    requestevents.h \
    customexception.h

SOURCES += \
        main.cpp \
    restdemoapp.cpp \
    requestsmanager.cpp \
    endpoints/endpointregister.cpp \
    endpoints/endpointdelete.cpp \
    endpoints/endpointupdate.cpp \
    endpoints/endpointview.cpp \
    endpoints/endpointgetdecrypdata.cpp \
    dbcontroller.cpp \
    datamodel/device.cpp \
    datamodel/protectionsystem.cpp \
    datamodel/content.cpp \
    requestevents.cpp \
    qaescipher/qaesencryption.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Include Libraries (CppRestSDK and static Qt)
SRC_DIR = $$PWD
INCLUDEPATH += $${SRC_DIR}/include
LIBS += -L$${SRC_DIR}/lib -lcpprest -lboost_system -lssl -lcrypto
