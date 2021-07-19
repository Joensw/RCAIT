//
// Created by Paul on 02.07.2021.
//

#ifndef RCAIT_IMPORTFILESWIDGET_H
#define RCAIT_IMPORTFILESWIDGET_H

#include <QWidget>
#include <QValidator>

namespace Ui {
class ImportFilesWidget;
}

class ImportFilesWidget : public QWidget
{
    Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit ImportFilesWidget(QWidget *parent = nullptr);
    ~ImportFilesWidget();

    void setAvailablePlugins(QStringList pluginNames);
private:
    Ui::ImportFilesWidget *ui;


    void retranslateUi();

private slots:
    void on_pushButton_clearTags_clicked();

    void on_pushButton_addModel_clicked();
    void on_pushButton_removeModel_clicked();
    void on_pushButton_loadModel_clicked();

    void on_pushButton_loadImages_clicked();
    void on_horizontalSlider_sliderMoved(int position);


signals:
    void sig_newModel();
    void sig_removeModel(QString modelName);
    void sig_loadModel(QString modelName);
    void sig_loadInputImages(QString pluginName, int count, QStringList label,int split);
};

#endif // RCAIT_IMPORTFILESWIDGET_H
