#ifndef SMTEST_H
#define SMTEST_H
#include <QTest>
#include "settingsmanager.h"
/**
 * There are two testing classing for SettingsManager because the in the GoogleTest the QSettings would not work properly
 * @brief The SettingsManagerTest class tests the settingsManager class
 *
 */
class SettingsManagerTest : public QObject
{
    Q_OBJECT

private slots:
    void qSettingsSimple();
    void saveDirectories();
    void verifyDirectories();
};

#endif // SMTEST_H
