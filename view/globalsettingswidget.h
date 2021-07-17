#ifndef GLOBALSETTINGSWIDGET_H
#define GLOBALSETTINGSWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class GlobalSettingsWidget;
}

class GlobalSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalSettingsWidget(QWidget *parent = nullptr);
    ~GlobalSettingsWidget();

    void setNewProjectPath(QString path);
    void setNewClassificationPluginPath(QString path);
    void setNewImageLoaderPath(QString path);
    void clearNewPaths();
    void showUpdate(int amount);
    void showNonUpdate();
    void setError(QString error);

    void setCurrentProjectsDir(QString path);
    void setCurrentClassificationDir(QString path);
    void setCurrentImageLoaderDir(QString path);
signals:
    void sig_setProjectDir();
    void sig_setClassificationPluginsDir();
    void sig_setImageLoaderPluginsDir();
private slots:
    void on_pushButton_project_clicked();

    void on_pushButton_classification_clicked();

    void on_pushButton_imageLoader_clicked();
private:
    Ui::GlobalSettingsWidget *ui;
};

#endif // GLOBALSETTINGSWIDGET_H
