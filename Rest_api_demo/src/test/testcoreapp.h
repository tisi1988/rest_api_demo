#ifndef TESTCOREAPP_H
#define TESTCOREAPP_H

#include <QtCore>
#include <gtest/gtest.h>

class TestCoreApp : public QCoreApplication {
    Q_OBJECT
public:
    TestCoreApp(int& argc, char** argv) : QCoreApplication(argc, argv) {
        ::testing::InitGoogleTest(&argc, argv);
    }
    virtual ~TestCoreApp() {}
public slots:
    void execute() {
        RUN_ALL_TESTS();
        QCoreApplication::quit();
    }
};

#endif // TESTCOREAPP_H
