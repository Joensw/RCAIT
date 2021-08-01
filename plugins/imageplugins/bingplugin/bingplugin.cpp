#include "bingplugin.h"


bool BingPlugin::loadImages(QString path,ProgressablePlugin* receiver,  int imageCount,  QStringList label)
{
    m_receiver = receiver;
    QString fullCommand = createCommandlineString(path, imageCount, &label);
    qDebug() << fullCommand;
    m_process = new QProcess();
    m_process->setReadChannel(QProcess::StandardOutput);
    connect(m_process,&QProcess::readyReadStandardOutput,this,&BingPlugin::slot_readOutPut);
    connect(m_process,&QProcess::finished,this,&BingPlugin::slot_pluginFinished);

    m_process->startCommand(fullCommand);
}




QString BingPlugin::createCommandlineString( QString path,  int imageCount,  QStringList* label){
    //get and format command line parameters for python script call
    QString downloadPath = QString("-p ").append(path);
    QString imageCountStr = QString("-c ").append(QString::number(imageCount));
    QFileInfo pythonfile = QFileInfo("bingapi_photosearch.py");

    QString scriptPath = pythonfile.absoluteFilePath();
    QString command = m_bingSettings.getPythonPath();
    QString apiKey = QString("-k ").append(m_bingSettings.getaAPIKey());
    QString apiSecret = QString("-s ").append(m_bingSettings.getAPISecret());
    QString labelConcat = "-l";

    for ( const auto& i : *label  )
    {
        labelConcat.append(" ");
        labelConcat.append(i);
    }

    QString fullCommand = command +  " " + scriptPath + " " + downloadPath  + " " +imageCountStr +" " + labelConcat;
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

    while (m_process->canReadLine()) {
       bool ok;
       QString line = QString::fromLocal8Bit(m_process->readLine());
       QString parsedProgress = line.remove(QRegularExpression("[\r\n]"));
       int progress = parsedProgress.toInt(&ok,10);
       qDebug() << parsedProgress;
       if(ok){
           emit m_receiver->sig_progress(progress);
       } else {
           emit m_receiver->sig_statusUpdate(parsedProgress);
       }
    }
}

void BingPlugin::slot_pluginFinished()
{
    m_process->close();
    delete m_process;
    emit m_receiver->sig_pluginFinished();
}

//! [0]
