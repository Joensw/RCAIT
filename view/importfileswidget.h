//
// Created by Paul on 02.07.2021.
//

#ifndef RCAIT_IMPORTFILESWIDGET_H
#define RCAIT_IMPORTFILESWIDGET_H

#include <QWidget>

namespace Ui {
class ImportFilesWidget;
}

class ImportFilesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImportFilesWidget(QWidget *parent = nullptr);
    ~ImportFilesWidget();

private:
    Ui::ImportFilesWidget *ui;

private slots:
    void on_pushButton_clearTags_clicked();
};

#endif // RCAIT_IMPORTFILESWIDGET_H
