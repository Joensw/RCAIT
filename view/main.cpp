#include "view/mainwindow.h"
#include "view/removeprojectdialog.h"
#include "view/newmodeldialog.h"
#include "view/removemodeldialog.h"
#include "view/newprojectdialog.h"
#include "view/startwidget.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleFactory>
#include <QFontDatabase>
#include <controller.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Set UI style and font
    QApplication::setStyle(QStyleFactory::create("fusion"));
    QFontDatabase::addApplicationFont(":/Resources/Fonts/SF-Pro-Text-Regular.otf");
    QFont sf_pro_text("SF Pro Text");
    sf_pro_text.setPixelSize(12);
    sf_pro_text.setHintingPreference(QFont::HintingPreference::PreferNoHinting); //This line did the trick
    QApplication::setFont(sf_pro_text);

    QCoreApplication::setOrganizationName("PSE_SS21");
    QCoreApplication::setApplicationName("RCAIT");

    Controller controller;


    //auskommentiert, nur zum erstellen der Dialog GUI Screenshots
    //RemoveProjectDialog r;
    //r.show();

    //NewModelDialog m;
   // m.show();

    //NewProjectDialog p;
    //p.show();

    //RemoveModelDialog t;
    //t.show();

    return a.exec();
}
