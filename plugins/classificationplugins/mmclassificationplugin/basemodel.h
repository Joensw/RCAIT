#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QObject>

class BaseModel
{
private:
    QString m_name;
    QString m_relConfigFilePath;
    QString m_checkpointFileName;

public:
    explicit BaseModel(QString name, QString relConfigFilePath, QString checkpointFileName);
    QString getName();
    QString getRelConfigFilePath();
    QString getCheckpointFileName();
};

#endif // BASEMODEL_H
