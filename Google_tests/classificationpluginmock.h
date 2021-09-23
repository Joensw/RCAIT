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
    QStringList getAssociatedModels() override;
    bool createNewModel(QString modelName, QString baseModel) override;
    bool getAugmentationPreview(const QString &modelName, const QString &inputPath, const QString &targetPath, int amount) override;
    QWidget *getDataAugmentationInputWidget() override;
    bool removeModel(QString modelName) override;
    TrainingResult *train(const QString &modelName, QString trainDatasetPath, QString validationDatasetPath, QString workingDirectory, ProgressablePlugin *receiver) override;
    ClassificationResult *classify(const QString &inputImageDirPath, const QString &trainDatasetPath, const QString &workingDirPath, const QString &modelName, ProgressablePlugin *receiver) override;

private:

    static constexpr auto PLUGIN_NAME = "testplugin";

};

#endif
