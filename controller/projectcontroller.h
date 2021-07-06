#ifndef PROJECTCONTROLLER_H
#define PROJECTCONTROLLER_H

#include <QString>


class ProjectController
{
public:
    ProjectController();
    static bool verifyName(QString input);

public slots:
    void newProjectConfirm(QString projectName);
};

#endif // PROJECTCONTROLLER_H
