#include <QApplication>
#include <QtDebug>
#include <iostream>
#include "test/tst_flickrplugin.h"


//! [0]
int main(int argv, char *args[])
{
    TestFlickrPlugin testcases;

    QApplication app(argv, args);
    return QTest::qExec(&testcases, argv, args);

}
//! [0]
