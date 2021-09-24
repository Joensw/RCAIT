#ifndef CLASSIFICATIONPLUGIN_H
#define CLASSIFICATIONPLUGIN_H

#include <QObject>
#include <QTextStream>
#include <results/trainingresult.h>
#include <results/classificationresult.h>
#include <pluginusage/progressableplugin.h>
#include "plugin.h"

/**
 * @brief The ClassificationPlugin class is an interface for all classification plugins.
 *
 */
class ClassificationPlugin : public Plugin
{
public:

    /**
     * ClassificationPlugin constructor.
     *
     */
    virtual ~ClassificationPlugin() = default;

    /**
     * @brief getAssociatedModels gets models associeted with plugin.
     *
     * @return list of models
     */
    virtual QStringList getAssociatedModels() = 0;

    /**
     * @brief createNewModel creates a new model with a name from a base model.
     *
     * @param modelName name of new model
     * @param baseModel base model of new model
     * @return true if creation was successful
     */
    virtual bool createNewModel(QString modelName, QString baseModel) = 0;

    /**
     * @brief getAugmentationPreview loads a preview of augmented images into a folder.
     *
     * @param modelName name of model
     * @param inputPath location of original images
     * @param targetPath location for new images
     * @param amount number of augmented images
     * @return true if successful
     */
    virtual bool getAugmentationPreview(const QString &modelName, const QString &inputPath, const QString &targetPath, int amount) = 0;

    /**
     * @brief getDataAugmentationInputWidget gets widget for augmentation config.
     *
     * @return data augmentation input widget
     */
    virtual QSharedPointer<QWidget> getDataAugmentationInputWidget() = 0;

    /**
     * @brief removeModel removes model with specified name.
     *
     * @param modelName name of model
     * @return true if removal was successful
     */
    virtual bool removeModel(QString modelName)= 0;

    /**
     * @brief train starts a training with the given arguments.
     *
     * @param modelName name of model
     * @param trainDatasetPath location of training images
     * @param validationDatasetPath location of validation images
     * @param workingDirectory working directory
     * @param receiver receives progress of training
     * @return result data of training
     */
    virtual TrainingResult* train(const QString &modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin *receiver)= 0;

    /**
     * @brief classify starts a classification with the given arguments.
     *
     * @param inputImageDirPath location of input images
     * @param trainDatasetPath location of training images
     * @param workingDirPath working directory
     * @param modelName name of model
     * @param receiver receives classification progress
     * @return result data of classification
     */
    virtual ClassificationResult* classify(const QString &inputImageDirPath, const QString &trainDatasetPath, const QString &workingDirPath, const QString &modelName, ProgressablePlugin *receiver)= 0;

    /**
     * @brief init initializes plugin.
     *
     */
    virtual void init() = 0;
};

QT_BEGIN_NAMESPACE

#define ClassificationPlugin_iid "de.Fraunhofer.IOSB.RCAIT.ClassificationPlugin"

Q_DECLARE_INTERFACE(ClassificationPlugin, ClassificationPlugin_iid)
QT_END_NAMESPACE

#endif
