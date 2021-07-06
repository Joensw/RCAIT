#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QComboBox>
#include <QTranslator>
#include <QPushButton>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sig_openSettings();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clearTags_clicked();

    void on_comboBox_languageSelection_currentTextChanged(const QString &arg1);

    void slot_settingsButton_clicked();

private:
    Ui::MainWindow *ui;
    QTranslator m_translator; /*< contains the translations for this application*/
    QString m_currLang; /*< contains the currently loaded language*/
    const QString m_langPath = QDir(":/i18n/").exists()? ":/i18n/" : QDir::currentPath() + "/"; /*< Path of language files. This is always fixed.*/
    QPushButton * pushButton_settings = new QPushButton();

    void populateResultCharts();
    void populateLanguageMenu(QComboBox *box);
    void placeSettingsButton();
    void loadLanguage(const QString& rLanguage);
    void switchTranslator(QTranslator& translator, const QString& filename);

    void populateConfusionMatrix();
};
#endif // MAINWINDOW_H
