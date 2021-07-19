#include "flickrplugin.h"


bool FlickrPlugin::loadImages(QString path,ProgressablePlugin* receiver,  int imageCount,  QStringList label)
{



    QString fullCommand = createCommandlineString(path, imageCount, &label);
    qDebug() << fullCommand;
    QProcess *process = new QProcess();
    process->startCommand(fullCommand);

    process->waitForStarted();
    bool res = process->waitForFinished();

    QString strTemp = QString::fromLocal8Bit(process->readAll());  // Get the output
    qInfo() << qPrintable(strTemp.simplified());

    process->close();

    return res;
}


QString FlickrPlugin::createCommandlineString( QString path,  int imageCount,  QStringList* label){
    //get and format command line parameters for python script call
    QString downloadPath = QString("-p ").append(path);
    QString imageCountStr = QString("-c ").append(QString::number(imageCount));
    QFileInfo pythonfile = QFileInfo("flickrapi_photosearch.py");

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

//! [0]
