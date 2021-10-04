/**
 * @file modelmanager.cpp
 *
 * @brief functions for managing models of image classification plugins
 *
 * @author Andreas Ott
 */
#include "modelmanager.h"

ModelManager::ModelManager()
        : mClassificationPluginManager(&ClassificationPluginManager::getInstance()) {

}

bool ModelManager::createNewModel(const QString &projectName, const QString &modelName, const QString &pluginName, const QString &baseModel) {
    m_userModelNamesPerProject.beginGroup(projectName);
    QStringList modelsOfProject = m_userModelNamesPerProject.childKeys();
    m_userModelNamesPerProject.endGroup();
    if (modelsOfProject.contains(modelName)) {
        qWarning() << "A model with this name already exists";
        return false;
    } else {
        if (mClassificationPluginManager->createNewModel(modelName, pluginName, baseModel)) {
            // add the new model to the saved user models
            QStringList modelSpecificData = {QString(), QString()};
            modelSpecificData[pluginNamePosition] = pluginName;
            m_userModelNamesPerProject.beginGroup(projectName);
            m_userModelNamesPerProject.setValue(modelName, modelSpecificData);
            m_userModelNamesPerProject.endGroup();
            return true;
        } else {
            qWarning() << "The new model could not be created";
            return false;
        }
    }
}

bool ModelManager::removeModel(const QString &projectName, const QString &modelName) {
    m_userModelNamesPerProject.beginGroup(projectName);
    if (!m_userModelNamesPerProject.childKeys().contains(modelName)) {
        m_userModelNamesPerProject.endGroup();
        qWarning() << "There is no plugin with this name";
        return false;
    }
    QStringList modelSpecificData = m_userModelNamesPerProject.value(modelName).toStringList();
    QString pluginName = modelSpecificData.at(pluginNamePosition);
    m_userModelNamesPerProject.endGroup();
    if (!pluginName.isEmpty()) {
        if (mClassificationPluginManager->removeModel(modelName, pluginName)) {
            m_userModelNamesPerProject.beginGroup(projectName);
            m_userModelNamesPerProject.remove(modelName);
            m_userModelNamesPerProject.endGroup();
            return true;
        } else {
            qWarning() << "The model " << modelName << " could not be deleted in the plugin " << pluginName;
        }
    } else {
        qWarning() << "The plugin was not found";
    }
    return false;
}

void ModelManager::loadModel(const QString &modelName, const QString &pluginName) {
    mCurrentModel = std::move(modelName);
    mCurrentPlugin = std::move(pluginName);
}

QString ModelManager::getCurrentPlugin() {
    return mCurrentPlugin;
}

QString ModelManager::getCurrentModel() {
    return mCurrentModel;
}

QStringList ModelManager::getModelNamesOfProject(const QString &projectName) {
    m_userModelNamesPerProject.beginGroup(projectName);
    QStringList modelNames = m_userModelNamesPerProject.childKeys();
    m_userModelNamesPerProject.endGroup();
    return modelNames;
}

void ModelManager::removeAllModelsOfProject(const QString &projectName) {
    QStringList modelsToRemove = getModelNamesOfProject(projectName);
    for (const QString &modelName: modelsToRemove) {
        removeModel(projectName, modelName);
    }
}

void ModelManager::saveLastWorkingDirectoryOfModel(const QString &projectName, const QString &modelName,
                                                   const QString &workingDirectory) {
    QStringList modelSpecificData;
    m_userModelNamesPerProject.beginGroup(projectName);
    modelSpecificData = m_userModelNamesPerProject.value(modelName).toStringList();
    if (!workingDirectory.trimmed().isEmpty() && modelSpecificData.size() == numberOfEntries) {
        modelSpecificData[lastWorkingDirectoryPosition] = workingDirectory;
        m_userModelNamesPerProject.setValue(modelName, modelSpecificData);
    }
    m_userModelNamesPerProject.endGroup();
}

QString ModelManager::recallLastWorkingDirectoryOfModel(const QString &projectName, const QString &modelName) {
    QStringList modelSpecificData;
    m_userModelNamesPerProject.beginGroup(projectName);
    modelSpecificData = m_userModelNamesPerProject.value(modelName).toStringList();
    m_userModelNamesPerProject.endGroup();

    if (modelSpecificData.size() == 2) {
        return modelSpecificData.at(lastWorkingDirectoryPosition);
    } else {
        return QString();
    }
}

QString ModelManager::recallPluginNameOfModell(const QString &projectName, const QString &modelName) {
    QStringList modelSpecificData;
    m_userModelNamesPerProject.beginGroup(projectName);
    modelSpecificData = m_userModelNamesPerProject.value(modelName).toStringList();
    m_userModelNamesPerProject.endGroup();

    if (modelSpecificData.size() == 2) {
        return modelSpecificData.at(pluginNamePosition);
    } else {
        return QString();
    }

}

QSharedPointer<QWidget> ModelManager::getInputWidget() {
    return mClassificationPluginManager->getInputWidget(mCurrentPlugin);
}

QSharedPointer<QWidget> ModelManager::getDataAugmentationInputWidget() {
    return mClassificationPluginManager->getDataAugmentationInputWidget(mCurrentPlugin);
}
