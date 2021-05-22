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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clearTags_clicked();

    void on_comboBox_languageSelection_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QTranslator m_translator; /*< contains the translations for this application*/
    QString m_currLang; /*< contains the currently loaded language*/
    const QString m_langPath = ":/i18n/"; /*< Path of language files. This is always fixed.*/
    QPushButton * pushButton_settings = new QPushButton();

    static void populateResultCharts(Ui::MainWindow *ui);
    void populateLanguageMenu(QComboBox *box);
    void placeSettingsButton();
    void loadLanguage(const QString& rLanguage);
    void switchTranslator(QTranslator& translator, const QString& filename);
};
#endif // MAINWINDOW_H
