#ifndef TST_FLICKRPLUGIN_H
#define TST_FLICKRPLUGIN_H

#include <QObject>
#include <QtTest/QTest>
#include "flickrplugin.h"
#include <QtDebug>
#include <QDir>
#include <iostream>

class TestFlickrPlugin : public QObject
{

    FlickrPlugin * cut_; //class under test
    QDir dir;
    Q_OBJECT

public:
    TestFlickrPlugin();
    const QString DOWNLOAD_SUBDIR = "/test_files";
    const QString VALID_DOWNLOAD_PATH = QDir::currentPath() + DOWNLOAD_SUBDIR;
    const int VALID_IMAGE_COUNT = 10;
    const QStringList VALID_LABELS = {"car","plane"};
    static QString API_KEY_ANSWER;
    static QString API_SECRET_ANSWER;
    static QString PYTHON_PATH_ANSWER;



signals:



private slots:
    void initTestCase(){};
    void cleanupTestCase(){};

    void init();
    void cleanup();

    void testAPIKey();
    void testAPISecret();
    void testProcessPythonScriptCall();

};

#endif // TST_FLICKRPLUGIN_H
