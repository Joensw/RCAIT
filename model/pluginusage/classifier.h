#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <trainingresult.h>
#include <classificationpluginmanager.h>
#include <progressableplugin.h>
#include <classificationresult.h>
#include <qfuturewatcher.h>

/**
 * @brief The Classifier class is used to start a classification and handle incoming results
 *
 */
class Classifier : public ProgressablePlugin
{
    Q_OBJECT

public:

    /**
     * @brief Classifier constructs Classifier
     *
     */
    Classifier();

    /**
     * @brief classify starts classification in new thread with the given arguments
     *
     * @param pluginName name of selected plugin
     * @param inputImageDirPath path of images to classify
     * @param trainDatasetPath path of dataset used for training
     * @param workingDirectory model working dir
     * @param modelName name of selected model
     */
    void classify(const QString& pluginName, const QString& inputImageDirPath, const QString& trainDatasetPath, const QString& workingDirectory, const QString& modelName);


signals:

    /**
     * @brief sig_classificationResultUpdated signals new classification result
     *
     * @param classificationResult new classification result
     */
    void sig_classificationResultUpdated(const QSharedPointer<ClassificationResult>& classificationResult);

    /**
     * @brief sig_startClassification signals start of classification
     *
     */
    void sig_startClassification();


public slots:

    /**
     * @brief slot_handleClassificationResult is used to handle new classification results
     *
     */
    void slot_handleClassificationResult();

    /**
     * @brief slot_makeProgress is called when classification made progress
     *
     * @param progress number in percent
     */
    void slot_makeProgress(int progress) override;

private:
    ClassificationPluginManager& mManager = ClassificationPluginManager::getInstance();
    QFuture<QSharedPointer<ClassificationResult>> mClassificationResult;

};

#endif // CLASSIFIER_H
