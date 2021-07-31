#include "flickrplugin.h"


bool FlickrPlugin::loadImages(QString path,ProgressablePlugin* receiver,  int imageCount,  QStringList label)
{
    m_receiver = receiver;
    QString fullCommand = createCommandlineString(path, imageCount, &label);
    qDebug() << fullCommand;
    m_process = new QProcess();
    m_process->setReadChannel(QProcess::StandardOutput);
    connect(m_process,&QProcess::readyReadStandardOutput,this,&FlickrPlugin::slot_readOutPut);
    connect(m_process,&QProcess::finished,this,&FlickrPlugin::slot_pluginFinished);

    m_process->startCommand(fullCommand);

}




QString FlickrPlugin::createCommandlineString( QString path,  int imageCount,  QStringList* label){
    //get and format command line parameters for python script call
    QString downloadPath = QString("-p ").append(path);
    QString imageCountStr = QString("-c ").append(QString::number(imageCount));
    QFileInfo pythonfile = QFileInfo("flickrapi_photosearch.py");
    //QFileInfo pythonfile = QFileInfo("test.py");

    QString scriptPath = pythonfile.absoluteFilePath();
    QString command = m_flickrSettings.getPythonPath();
    QString apiKey = QString("-k ").append(m_flickrSettings.getaAPIKey());
    QString apiSecret = QString("-s ").append(m_flickrSettings.getAPISecret());
    QString labelConcat = "-l";

    for ( const auto& i : *label  )
    {
        labelConcat.append(" ");
        labelConcat.append(i);
    }

    QString fullCommand = command +  " " + scriptPath + " " + downloadPath  + " " +imageCountStr +" " + labelConcat +" " + apiKey +" " + apiSecret;
    return fullCommand;

}


QWidget* FlickrPlugin::getConfigurationWidget()
{
  return pluginSettings;
}

void FlickrPlugin::saveConfiguration(){
    qobject_cast<FlickrSettings *>(pluginSettings)->saveSettings();
}

void FlickrPlugin::init()
{
    pluginSettings = new FlickrSettings();
}

QString FlickrPlugin::getName()
{
    return "Flickr API Plugin";
}

QWidget *FlickrPlugin::getInputWidget()
{
    return nullptr;
}

void FlickrPlugin::slot_readOutPut()
{

    while (m_process->canReadLine()) {
       bool ok;
       QString line = QString::fromLocal8Bit(m_process->readLine());
       QString parsedProgress = line.remove(QRegularExpression("[\r\n]"));
       int progress = parsedProgress.toInt(&ok,10);
       qDebug() << progress;
       if(ok){
       emit m_receiver->sig_progress(progress);
       }
    }
}

void FlickrPlugin::slot_pluginFinished()
{
    m_process->close();
    delete m_process;
    emit m_receiver->sig_pluginFinished();
}

//! [0]
