#include "model.h"

Model::Model(QString name, QString baseModelName, QString mainConfigPath, QString modelConfigPath, QString datasetConfigPath, QString scheduleConfigPath, QString runtimeConfigPath)
{
    m_name = name;
    m_baseModelName = baseModelName;
    m_mainConfigPath = mainConfigPath;
    m_modelConfigPath = modelConfigPath;
    m_datasetConfigPath = datasetConfigPath;
    m_scheduleConfigPath = scheduleConfigPath;
    m_runtimeConfigPath = runtimeConfigPath;
}

QString Model::getName()
{
    return m_name;
}

QString Model::getBaseModelName()
{
    return m_baseModelName;
}

QString Model::getMainConfigPath()
{
    return m_mainConfigPath;
}

QString Model::getModelConfigPath()
{
    return m_modelConfigPath;
}

QString Model::getDatasetConfigPath()
{
    return m_datasetConfigPath;
}

QString Model::getScheduleConfigPath()
{
    return m_scheduleConfigPath;
}

QString Model::getRuntimeConfigPath()
{
    return m_runtimeConfigPath;
}

bool Model::isValid()
{
    return !(m_name.isEmpty() || m_baseModelName.isEmpty() || m_mainConfigPath.isEmpty() || m_modelConfigPath.isEmpty() || m_datasetConfigPath.isEmpty()
             || m_scheduleConfigPath.isEmpty() || m_runtimeConfigPath.isEmpty());
}
