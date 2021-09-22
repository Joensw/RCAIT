#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QObject>

/**
 * @brief The BaseModel class connects the chosen base model with matching config and (ImageNet pretrained) checkpoint file
 */
class BaseModel
{
public:
    /**
     * @brief BaseModel creates a new base model
     * @param name of the base model, which serves as its identifier
     * @param relConfigFilePath is the relative path to the config file using the config hierarchy of MMClassification
     * @param checkpointFileName is the name of the with ImageNet pretrained checkpoint file and its extension
     */
    explicit BaseModel(const QString &name, const QString &relConfigFilePath, const QString &checkpointFileName);

    /**
     * @brief getName returns the name of the base model
     * @return the name to identify the base model
     */
    QString getName();

    /**
     * @brief getRelConfigFilePath returns the relative path of the config file
     * @return the relative file path to include its config file in a config file created by the user
     */
    QString getRelConfigFilePath();

    /**
     * @brief getCheckpointFileName returns the checkpoint file of the base model to serve as a starting point for further training
     * @return the checkpoint file, which was created by pretraining the base model on the ImageNet dataset
     */
    QString getCheckpointFileName();

private:
    QString m_name;
    QString m_relConfigFilePath;
    QString m_checkpointFileName;


};

#endif // BASEMODEL_H
