#ifndef NEWMODELDIALOG_H
#define NEWMODELDIALOG_H

#include <QDialog>
#include <animationutilities.h>


namespace Ui {
class NewModelDialog;
}
/**
 * @brief The NewModelDialog class is a UI class that is for specifying the details of a new model
 */
class NewModelDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief NewModelDialog create a newModelDialog
     * @param parent optional parent argument
     * @param classificationPlugins names of the classification plugins that are shown in the UI for selection
     */
    explicit NewModelDialog(QWidget *parent = nullptr, const QStringList &classificationPlugins = QStringList());

    /**
     * @brief destructor
     */
    ~NewModelDialog() override;

    /**
     * @brief setErrorMessage sets the displayed error message in the UI
     * @param error the error message to be shown in the UI
     */
    void setErrorMessage(const QString &error);

    /**
     * @brief populates the dropdown for the plugin bases with entries
     * @param bases names of the bases to be shown in the bases drop down
     */
    void setAvailableBases(const QStringList &bases);

    /**
     * @return returns the currently selected  plugin in the plugin dropdown, or nullstring if it is empty
     */
    [[nodiscard]] QString getCurrentSelectedPlugin() const;

public slots:

    /**
     * @brief slot_classificationPlugin_currentTextChanged called when the selected classification plugin changes
     * @param text the current classification plugin selected in the drop down
     */
    void slot_classificationPlugin_currentTextChanged(const QString &text);

signals:
    /**
     * @brief sig_newModelConfirm emitted when a model with the specified parameters is to be created
     * @param modelName name of the model
     * @param pluginName name of the classification plugin the model is from
     * @param baseModel chosen pre-trained base for the model
     */
    void sig_newModelConfirm(QString modelName, QString pluginName, QString baseModel);

    /**
     * @brief sig_pluginSelected emitted when a classification plugin is selected in the drop down
     * @param pluginName name of the selected plugin
     */
    void sig_pluginSelected(QString pluginName);
private:
    Ui::NewModelDialog *ui;

private slots:
    //slots correspond with the identically named button in the UI
    [[maybe_unused]] void on_buttonBox_accepted();
    [[maybe_unused]] void on_buttonBox_rejected();

};

#endif // NEWMODELDIALOG_H
