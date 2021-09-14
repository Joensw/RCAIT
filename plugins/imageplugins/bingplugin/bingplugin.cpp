/**
 * @file bingplugin.cpp
 *
 * @brief implements methods for BingPlugin class
 */
#include "bingplugin.h"


bool BingPlugin::loadImages(QString path, ProgressablePlugin *receiver, int imageCount, QStringList label) {
    connect(receiver, &ProgressablePlugin::sig_pluginAborted, this, &BingPlugin::slot_abort);
    m_receiver = receiver;
    QString fullCommand = createCommandlineString(path, imageCount, label);
    qDebug() << fullCommand;
    m_process.reset(new QProcess);
    m_process->setReadChannel(QProcess::StandardOutput);
    connect(&*m_process, &QProcess::readyReadStandardOutput, this, &BingPlugin::slot_readOutPut);
    connect(&*m_process, &QProcess::finished, this, &BingPlugin::slot_pluginFinished);

    m_process->startCommand(fullCommand);
    m_process->waitForStarted();
    m_process->waitForFinished(-1);
    return m_success;
}


QString BingPlugin::createCommandlineString(const QString &path, int imageCount, const QStringList &label) {
    //get and format command line parameters for python script call
    auto downloadPath = QString("-p ").append(path);
    auto imageCountStr = QString("-c ").append(QString::number(imageCount));
    auto pythonfile = QFileInfo("bingapi_photosearch.py");

    QString scriptPath = pythonfile.absoluteFilePath();
    QString command = m_bingSettings.getPythonPath();
    QString labelConcat = "-l";

    for (const auto &i: label) labelConcat.append(" " % ('"' % i % '"'));

    //set the -u flag to write directly to standardoutput without buffering
    QString fullCommand = command % " -u " % scriptPath % " " % downloadPath % " " % imageCountStr % " " % labelConcat;
    return fullCommand;

}


QWidget *BingPlugin::getConfigurationWidget() {
    return pluginSettings;
}

void BingPlugin::saveConfiguration() {
    qobject_cast<BingSettings *>(pluginSettings)->saveSettings();
}

void BingPlugin::init() {
    pluginSettings = new BingSettings();
}

QString BingPlugin::getName() {
    return "Bing API Plugin";
}

QWidget *BingPlugin::getInputWidget() {
    return nullptr;
}

void BingPlugin::slot_readOutPut() {
    static QRegularExpression lineBreak("[\r\n]");
    static QRegularExpression progressUpdate(QRegularExpression::escape("[%] Downloading Image"));
    static QRegularExpression errorUpdate(QRegularExpression::escape("[!] Issue getting"));

    while (m_process->canReadLine()) {
        QString line = QString::fromLocal8Bit(m_process->readLine());
        QString parsedProgress = line.remove(lineBreak);

        auto updateMatch = progressUpdate.match(parsedProgress, 0,
                                                QRegularExpression::PartialPreferCompleteMatch);
        if (updateMatch.hasMatch()) {
            qDebug() << parsedProgress;
            emit m_receiver->sig_statusUpdate(parsedProgress);
        } else {
            auto errorMatch = errorUpdate.match(parsedProgress, 0,
                                                QRegularExpression::PartialPreferCompleteMatch);
            if (errorMatch.hasMatch()) {
                qDebug() << parsedProgress;
                emit m_receiver->sig_statusUpdate(parsedProgress);
            }
        }

        bool ok;
        int progress = parsedProgress.toInt(&ok, 10);
        if (ok) m_receiver->slot_makeProgress(progress);

    }
}

void BingPlugin::slot_pluginFinished() {
    m_process->close();
    m_process.reset();
    emit m_receiver->sig_pluginFinished();
}

void BingPlugin::slot_abort() {
    m_process->kill();
}

//! [0]
