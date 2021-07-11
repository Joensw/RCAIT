#ifndef AUTOMATIONCONTROLLER_H
#define AUTOMATIONCONTROLLER_H

#include <DataManager.h>
#include <QObject>
#include <automationwidget.h>
#include <automator.h>

class AutomationController : public QObject
{
    Q_OBJECT
public:
    AutomationController(DataManager *dataManager, AutomationWidget *automationWidget);

public slots:
    void slot_start();
    void slot_stop();
    void slot_remove(int index);
    void slot_import(QString path);
    void slot_queueAll();
    void slot_unqueueAll();
    void slot_queueSelected(int index);
    void slot_unqueueSelected(int index);

private:
    AutomationWidget *mWidget;
    DataManager *mDataManager;
    Automator* mAutomator;

};

#endif // AUTOMATIONCONTROLLER_H
