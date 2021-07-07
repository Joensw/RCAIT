#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include <QtWidgets/QComboBox>
#include <QTranslator>
#include <QDir>
#include "newprojectdialog.h"

namespace Ui {
class StartWidget;
}

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = nullptr);
    ~StartWidget();
    QString getLanguageEntry();
    void addProjects(QStringList projects);
    void addProject(QString project);
    void clearProjectList();

private:
    Ui::StartWidget *ui;

    const QString m_langPath = QDir(":/i18n/").exists()? ":/i18n/" : QDir::currentPath() + "/"; /*< Path of language files. This is always fixed.*/


    void populateLanguageMenu(QComboBox *box);
    void loadLanguage(const QString& rLanguage);
    void switchTranslator(QTranslator& translator, const QString& filename);
private slots:
    void on_pushButton_newProject_clicked();
    void on_pushButton_removeProject_clicked();
signals:
    void sig_newProject();
    void sig_removeProject(QString projectName);
};

#endif // STARTWIDGET_H
