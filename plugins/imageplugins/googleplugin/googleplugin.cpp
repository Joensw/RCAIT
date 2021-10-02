/**
 * @file googleplugin.cpp
 *
 * @brief implements methods for GooglePlugin class
 */
#include "googleplugin.h"


bool GooglePlugin::loadImages(const QString &path, ProgressablePlugin *receiver, int imageCount, const QStringList &label) {
    m_progress = 0;
    m_imageCount = imageCount;
    m_labels = label;
    m_errorOutPutBuffer = "";

    connect(receiver, &ProgressablePlugin::sig_pluginAborted, this, &GooglePlugin::slot_abort);
    m_receiver = receiver;
    QString fullCommand = createCommandlineString(path, imageCount, label);
    qDebug() << fullCommand;
    m_process.reset(new QProcess);
    m_process->setReadChannel(QProcess::StandardOutput);
    connect(&*m_process, &QProcess::readyReadStandardOutput, this, &GooglePlugin::slot_readOutPut);
    connect(&*m_process, &QProcess::finished, this, &GooglePlugin::slot_pluginFinished);
    connect(&*m_process, &QProcess::readyReadStandardError, this, &GooglePlugin::slot_readErrorOutPut);


    //check settings
    if(!pluginSettings->isConfigured()){
        emit m_receiver->sig_statusUpdate(pluginSettings->getMissingConfigError());
        return false;
    }

    //check inputs and get errors


    //print error messages and return if we have any
    if(QStringList inputErrors = imagepluginerrorutil::checkInputs(path, label, imageCount); !inputErrors.isEmpty()){
        emit m_receiver->sig_statusUpdate(imagepluginerrorutil::getErrorString(inputErrors));
        return false;
    }


    m_process->startCommand(fullCommand);
    m_process->waitForStarted();
    m_process->waitForFinished(-1);
    return m_success;
}


QString GooglePlugin::createCommandlineString(const QString &path, int imageCount, const QStringList &label) const {
    //get and format command line parameters for python script call
    auto downloadPath = QString("-p ").append(path);
    auto imageCountStr = QString("-c ").append(QString::number(imageCount));
    auto pythonfile = QFileInfo("googleapi_photosearch.py");

    QString scriptPath = pythonfile.absoluteFilePath();
    QString command = pluginSettings->getPythonPath();
    QString APIKey = QString("-k ").append(pluginSettings->getAPIKey());
    QString projectCX = QString("-x ").append(pluginSettings->getProjectCX());
    QString labelConcat = "-l";

    for (const auto &i: label) {
        labelConcat.append(" " % ('"' % i % '"'));
    }

    //set the -u flag to write directly to standardoutput without buffering
    QString fullCommand =
            command % " -u " % scriptPath % " " % projectCX % " " % APIKey % " " % downloadPath % " " % imageCountStr %
            " " % labelConcat;
    return fullCommand;

}


QSharedPointer<QWidget> GooglePlugin::getConfigurationWidget() {
    return pluginSettings;
}

void GooglePlugin::saveConfiguration() {
    pluginSettings->saveSettings();
}

void GooglePlugin::init() {
    pluginSettings.reset(new GoogleSettings, &QObject::deleteLater);
}

QString GooglePlugin::getName() {
    return "Google API Plugin";
}

void GooglePlugin::slot_readOutPut() {
    static QRegularExpression lineBreakRegex("[\r\n]");
    static QRegularExpression downloadRegex(QRegularExpression::escape("[%] Downloading Image"));
    static QRegularExpression successRegex(QRegularExpression::escape("[%] File Downloaded !"));
    static QRegularExpression errorRegex(QRegularExpression::escape("[!] Issue getting"));
    m_process->setReadChannel(QProcess::StandardOutput);
    while (m_process->canReadLine()) {
        QString line = QString::fromLocal8Bit(m_process->readLine());
        QString strippedLine = line.remove(lineBreakRegex);

        auto downloadMatch = downloadRegex.match(strippedLine, 0,
                                                 QRegularExpression::PartialPreferCompleteMatch);
        auto successMatch = successRegex.match(strippedLine, 0,
                                               QRegularExpression::PartialPreferCompleteMatch);
        auto errorMatch = errorRegex.match(strippedLine, 0,
                                           QRegularExpression::PartialPreferCompleteMatch);

        if (downloadMatch.hasMatch() || errorMatch.hasMatch()) {
            emit m_receiver->sig_statusUpdate(strippedLine);
            qDebug() << strippedLine;
        }

        if (successMatch.hasMatch()) {
            auto total = m_imageCount * m_labels.size();
            auto progress = ++m_progress * 100.0 / (double) total;
            m_receiver->slot_makeProgress((int) progress);
        }
    }
}

void GooglePlugin::slot_pluginFinished() {
    m_process->close();
    m_process.reset();
}

void GooglePlugin::slot_readErrorOutPut()
{
    static QRegularExpression lineBreak("[\r\n]");
    static QRegularExpression multiSpace("( )( )+");
    m_process->setReadChannel(QProcess::StandardError);
    while (m_process->canReadLine()) {
        QString line = QString::fromLocal8Bit(m_process->readLine());
        QString parsedProgress = line.remove(lineBreak);
        parsedProgress = line.remove(multiSpace);
        m_errorOutPutBuffer = m_errorOutPutBuffer % " " % parsedProgress;
        emit m_receiver->sig_statusUpdate(m_errorOutPutBuffer);
    }
}

void GooglePlugin::slot_abort() {
    m_process->kill();
}


QSharedPointer<QIcon> GooglePlugin::getPluginIcon()
{
    return QSharedPointer<QIcon>(new QIcon(PLUGIN_ICON));
}



//! [0]
