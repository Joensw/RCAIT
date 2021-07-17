#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>

#include "globalsettingswidget.h"

namespace Ui {
class SettingsView;
}

class SettingsView : public QWidget
{
    Q_OBJECT


public:
    explicit SettingsView(QWidget *parent = nullptr);
    ~SettingsView();
    SettingsView(QWidget *parent, QStringList pluginNames, QList<QWidget*> pluginConfigurationWidgets);

    void pathsUpdated(int amount);
    void clearPaths();
    void setGlobalSettingsError(QString error);

    void setCurrentProjectDirectory(QString path);
    void setCurrentClassificationPluginDirectory(QString path);
    void setCurrentImageLoaderPluginDirectory(QString path);


signals:
    void sig_applyGlobalSettings(QString projectsDir, QString classificationPluginsDir, QString imageLoaderPluginsDir);
    void sig_applySettings(int index);

protected:
    void changeEvent(QEvent *event);
private slots:
    void on_saveButton_clicked();

    void slot_setProjectDir();
    void slot_setClassificationPluginsDir();
    void slot_setImageLoaderPluginsDir();

private:
    Ui::SettingsView *ui;
    GlobalSettingsWidget * mGlobalSettingsWidget;

    QString mProjectDir;
    QString mClassificationPluginsDir;
    QString mImageLoaderPluginsDir;

    void retranslate();
};

#endif // SETTINGSVIEW_H
