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

private:
    Ui::StartWidget *ui;

    const QString m_langPath = QDir(":/i18n/").exists()? ":/i18n/" : QDir::currentPath() + "/"; /*< Path of language files. This is always fixed.*/

    void populateLanguageMenu(QComboBox *box);
    void loadLanguage(const QString& rLanguage);
    void switchTranslator(QTranslator& translator, const QString& filename);

};

#endif // STARTWIDGET_H
