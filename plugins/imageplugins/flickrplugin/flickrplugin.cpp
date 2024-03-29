/**
 * @file flickrplugin.cpp
 *
 * @brief implements methods of FlickrPlugin class
 *
 */
#include "flickrplugin.h"



bool FlickrPlugin::loadImages(const QString &path, ProgressablePlugin *receiver, int imageCount, const QStringList &label) {
    //Setup variables
    m_receiver = receiver;
    m_errorOutPutBuffer = "";
    QString fullCommand = createCommandlineString(path, imageCount, label);
    qDebug() << fullCommand;
    m_process.reset(new QProcess);
    m_process->setReadChannel(QProcess::StandardOutput);
    //Connect signals/slots
    connect(&*m_process, &QProcess::readyReadStandardOutput, this, &FlickrPlugin::slot_readOutPut);
    connect(&*m_process, &QProcess::readyReadStandardError, this, &FlickrPlugin::slot_readErrorOutPut);
    connect(&*m_process, &QProcess::finished, this, &FlickrPlugin::slot_pluginFinished);

    //check settings
    if(!pluginSettings->isConfigured()){

        emit m_receiver->sig_statusUpdate(pluginSettings->getMissingConfigError());
        return false;
    }

    //check inputs and get errors
    QStringList inputErrors = imagepluginerrorutil::checkInputs(path, label, imageCount);

    //print error messages and return if we have any
    if(!inputErrors.isEmpty()){
        emit m_receiver->sig_statusUpdate(imagepluginerrorutil::getErrorString(inputErrors));
        return false;
    }

    m_process->startCommand(fullCommand);
    m_process->waitForStarted();

    qDebug() << imagepluginerrorutil::getErrorString(inputErrors);
    m_process->waitForFinished(-1);
    return m_success;
}


QString FlickrPlugin::createCommandlineString(const QString &path, int imageCount, const QStringList &label) {
    //get and format command line parameters for python script call
    auto downloadPath = QString("-p ").append(path);
    auto imageCountStr = QString("-c ").append(QString::number(imageCount));
    auto pythonFile = QFileInfo("flickrapi_photosearch.py");

    QString scriptPath = pythonFile.absoluteFilePath();
    QString command = m_flickrSettings.getPythonPath();
    QString apiKey = QString("-k ").append(m_flickrSettings.getAPIKey());
    QString apiSecret = QString("-s ").append(m_flickrSettings.getAPISecret());
    QString labelConcat = "-l";

    for (const auto &i: label) labelConcat.append(" " % ('"' % i % '"'));

    QString fullCommand =
            command % " " % scriptPath % " " % downloadPath % " " %
            imageCountStr % " " % labelConcat % " " % apiKey % " " % apiSecret;
    return fullCommand;

}


QSharedPointer<QWidget> FlickrPlugin::getConfigurationWidget() {
    return pluginSettings;
}

void FlickrPlugin::saveConfiguration() {
    pluginSettings->saveSettings();
}

void FlickrPlugin::init() {
    pluginSettings.reset(new FlickrSettings, &QObject::deleteLater);
}

QString FlickrPlugin::getName() {
    return "Flickr API Plugin";
}

void FlickrPlugin::slot_readOutPut() {
    static QRegularExpression lineBreak("[\r\n]");
    m_process->setReadChannel(QProcess::StandardOutput);
    while (m_process->canReadLine()) {
        QString line = QString::fromLocal8Bit(m_process->readLine());
        QString parsedProgress = line.remove(lineBreak);
        bool ok;
        int progress = parsedProgress.toInt(&ok, 10);
        qDebug() << parsedProgress;

        if (ok)
            m_receiver->slot_makeProgress(progress);
        else
            emit m_receiver->sig_statusUpdate(parsedProgress);

    }
}

void FlickrPlugin::slot_pluginFinished() {
    m_process->close();
    m_process.reset();
}

void FlickrPlugin::slot_readErrorOutPut()
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

void FlickrPlugin::slot_abort() {
    m_process->kill();
}

QSharedPointer<QIcon> FlickrPlugin::getPluginIcon()
{
    return QSharedPointer<QIcon>(new QIcon(PLUGIN_ICON));
}

//! [0]
