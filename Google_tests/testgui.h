#ifndef TESTGUI_H
#define TESTGUI_H
#include <QtWidgets>
#include <QtTest/QtTest>
#include "importfileswidget.h"
#include "customlistwidget.h"
#include "tags.hpp"


class TestGui : public QObject
{
    Q_OBJECT


private slots:
    void testImportFilesWidget();
    void testTagField();

};

#endif // TESTGUI_H
