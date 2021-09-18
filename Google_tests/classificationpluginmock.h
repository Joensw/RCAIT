#ifndef CLASSIFICATIONPLUGINMOCK_H
#define CLASSIFICATIONPLUGINMOCK_H
#include <QObject>
#include <QtPlugin>
#include <QSettings>
#include <QLineEdit>
#include <QProcess>
#include <QProcessEnvironment>
#include "classificationplugin.h"
#include "progressableplugin.h"
#include "trainingresult.h"
#include "classificationresult.h"

class ClassificationPluginMock : public QObject, ClassificationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.Fraunhofer.IOSB.RCAIT.MockPlugin" FILE "ClassificationPluginMock.json")
    Q_INTERFACES(ClassificationPlugin)

public:

    QWidget* getConfigurationWidget() override;
    void saveConfiguration() override;
    void init() override;
    QString getName() override;
    QWidget*  getInputWidget() override;
    inline static const QString PLUGIN_NAME = "testplugin";
    QStringList getAssociatedModels() override;
    bool createNewModel(QString modelName, QString baseModel) override;
    bool getAugmentationPreview(QString modelName, QString inputPath, QString targetPath, int amount) override;
    QWidget *getDataAugmentationInputWidget() override;
    bool removeModel(QString modelName) override;
    TrainingResult *train(QString modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin *receiver) override;
    ClassificationResult *classify(QString inputImageDirPath, QString trainDatasetPath, QString workingDirPath, QString modelName, ProgressablePlugin *receiver) override;

private:


};

#endif
