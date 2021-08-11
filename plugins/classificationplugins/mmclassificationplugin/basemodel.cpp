#include "basemodel.h"

BaseModel::BaseModel(const QString name,const QString relConfigFilePath, const QString checkpointFileName)
{
    m_name = name;
    m_relConfigFilePath = relConfigFilePath;
    m_checkpointFileName = checkpointFileName;
}

QString BaseModel::getName()
{
    return m_name;
}

QString BaseModel::getRelConfigFilePath()
{
    return m_relConfigFilePath;
}

QString BaseModel::getCheckpointFileName()
{
    return m_checkpointFileName;
}
