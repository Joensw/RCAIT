#ifndef TABCONTROLLER_H
#define TABCONTROLLER_H

#include "customtabwidget.h"


class TabController : public QObject
{
     Q_OBJECT
public:
    TabController(CustomTabWidget * tWidget);
public slots:
    void slot_openProject();
    void slot_imagesLoaded();
    void slot_modelLoaded();
    //void slot_modelTrained(); not yet
    //void slot_Classified(); not yet
    //void slot_showResults(); not yet
private:
    void disableTemporaryTabs();

    CustomTabWidget * m_tabWidget;
};

#endif // TABCONTROLLER_H
