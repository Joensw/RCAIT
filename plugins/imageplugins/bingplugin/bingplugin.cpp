#include "bingplugin.h"


bool BingPlugin::loadImages(QString path,ProgressablePlugin* receiver,  int imageCount,  QStringList label)
{
    m_receiver = receiver;
    QString fullCommand = createCommandlineString(path, imageCount, &label);
    qDebug() << fullCommand;
    m_process.reset(new QProcess);
    m_process->setReadChannel(QProcess::StandardOutput);
    connect(&*m_process,&QProcess::readyReadStandardOutput,this,&BingPlugin::slot_readOutPut);
    connect(&*m_process,&QProcess::finished,this,&BingPlugin::slot_pluginFinished);

    m_process->startCommand(fullCommand);
    m_process->waitForStarted();
    m_process->waitForFinished(-1);
    return m_success;
}




QString BingPlugin::createCommandlineString( QString path,  int imageCount,  QStringList* label){
    //get and format command line parameters for python script call
    QString downloadPath = QString("-p ").append(path);
    QString imageCountStr = QString("-c ").append(QString::number(imageCount));
    QFileInfo pythonfile = QFileInfo("bingapi_photosearch.py");

    QString scriptPath = pythonfile.absoluteFilePath();
    QString command = m_bingSettings.getPythonPath();
    QString labelConcat = "-l";

    for ( const auto& i : *label  )
    {
        labelConcat.append(" ");
        labelConcat.append('"' + i + '"');
    }

    //set the -u flag to write directly to standardoutput without buffering
    QString fullCommand = command +  " -u " + scriptPath + " " + downloadPath  + " " +imageCountStr +" " + labelConcat;
    return fullCommand;

}


QWidget* BingPlugin::getConfigurationWidget()
{
  return pluginSettings;
}

void BingPlugin::saveConfiguration(){
    qobject_cast<BingSettings *>(pluginSettings)->saveSettings();
}

void BingPlugin::init()
{
    pluginSettings = new BingSettings();
}

QString BingPlugin::getName()
{
    return "Bing API Plugin";
}

QWidget *BingPlugin::getInputWidget()
{
    return nullptr;
}

void BingPlugin::slot_readOutPut()
{
    QRegularExpression lineBreak("[\r\n]");

    QRegularExpression progressUpdate(QRegularExpression::escape("[%] Downloading Image"));
    QRegularExpression errorUpdate(QRegularExpression::escape("[!] Issue getting"));

    while (m_process->canReadLine()) {
       bool ok;
       QString line = QString::fromLocal8Bit(m_process->readLine());
       QString parsedProgress = line.remove(lineBreak);

       QRegularExpressionMatch updateMatch = progressUpdate.match(parsedProgress, 0, QRegularExpression::PartialPreferCompleteMatch);
       if(updateMatch.hasMatch()){
           qDebug() << parsedProgress;
           emit m_receiver->sig_statusUpdate(parsedProgress);
       } else {
           QRegularExpressionMatch errorMatch = errorUpdate.match(parsedProgress, 0, QRegularExpression::PartialPreferCompleteMatch);
           if(errorMatch.hasMatch()){
               qDebug() << parsedProgress;
               emit m_receiver->sig_statusUpdate(parsedProgress);
           }
       }

       int progress = parsedProgress.toInt(&ok,10);
       if(ok){

           m_receiver->slot_makeProgress(progress);
       }
    }
}

void BingPlugin::slot_pluginFinished()
{
    m_process->close();
    m_process.reset();
    emit m_receiver->sig_pluginFinished();
}

//! [0]
