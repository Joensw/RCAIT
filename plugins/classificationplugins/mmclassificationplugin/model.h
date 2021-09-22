#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "basemodel.h"

/**
 * @brief The Model class contains all user model specific data for better management
 */
class Model
{
public:
    /**
     * @brief Model creates a new instance of this class with the given parameters
     * @param name the name of the model
     * @param baseModelName the name of the base model, assocciated with this model, the name must be known to the MMClassificationPlugin
     * @param mainConfigPath the path to the main config of this model, which connects the other configs
     * @param modelConfigPath the path to the model config of this model
     * @param datasetConfigPath the path to the dataset config of this model
     * @param scheduleConfigPath the path of the schedule config of this model
     * @param runtimeConfigPath the path to the runtimeConfig of this model
     */
    explicit Model(const QString &name, const QString &baseModelName, const QString &mainConfigPath, const QString &modelConfigPath, const QString &datasetConfigPath, const QString &scheduleConfigPath, const QString &runtimeConfigPath);

    /**
     * @brief getName returns the name of this model, serving as a identifier
     * @return the name of this model
     */
    QString getName();

    /**
     * @brief getBaseModelName retuns the name of the associated base model
     * @return the name of the associated base model
     */
    QString getBaseModelName();

    /**
     * @brief getMainConfigPath returns the path to the main config
     * @return the path to the main config of this model
     */
    QString getMainConfigPath();

    /**
     * @brief getModelConfigPath returns the path to the model config
     * @return the path to the model config of this model
     */
    QString getModelConfigPath();

    /**
     * @brief getDatasetConfigPath returns the path to the dataset config
     * @return the path to the dataset config of this model
     */
    QString getDatasetConfigPath();

    /**
     * @brief getScheduleConfigPath returns the path to the schedule config
     * @return the path to the schedule config of this model
     */
    QString getScheduleConfigPath();

    /**
     * @brief getRuntimeConfigPath returns the path to the runtime config
     * @return the path to the runtime config of this model
     */
    QString getRuntimeConfigPath();

    /**
     * @brief isValid checks if the model is valid
     * @return true, if this model is valid, false otherwise
     */
    bool isValid();

private:
    QString m_name;
    QString m_baseModelName;
    QString m_mainConfigPath;
    QString m_modelConfigPath;
    QString m_datasetConfigPath;
    QString m_scheduleConfigPath;
    QString m_runtimeConfigPath;
};

#endif // MODEL_H
