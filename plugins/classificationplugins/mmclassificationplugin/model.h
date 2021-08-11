#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "basemodel.h"

class Model
{
private:
    QString m_name;
    QString m_baseModelName;
    QString m_mainConfigPath;
    QString m_modelConfigPath;
    QString m_datasetConfigPath;
    QString m_scheduleConfigPath;
    QString m_runtimeConfigPath;
public:
    explicit Model(QString name, QString baseModelName, QString mainConfigPath, QString modelConfigPath, QString datasetConfigPath, QString scheduleConfigPath, QString runtimeConfigPath);
    QString getName();
    QString getBaseModelName();
    QString getMainConfigPath();
    QString getModelConfigPath();
    QString getDatasetConfigPath();
    QString getScheduleConfigPath();
    QString getRuntimeConfigPath();

    bool isValid();
};

#endif // MODEL_H
