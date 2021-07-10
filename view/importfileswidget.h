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

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent *) override;

public:
    explicit ImportFilesWidget(QWidget *parent = nullptr);
    ~ImportFilesWidget();

private:
    Ui::ImportFilesWidget *ui;

    void retranslateUi();

private slots:
    void on_pushButton_clearTags_clicked();
};

#endif // RCAIT_IMPORTFILESWIDGET_H
