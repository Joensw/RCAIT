#include "flickrsettings.h"
#include "tst_flickrplugin.h"

QString FlickrSettings::getaAPIKey()
{
    return TestFlickrPlugin::API_KEY_ANSWER;
}

QString FlickrSettings::getAPISecret()
{
    return TestFlickrPlugin::API_SECRET_ANSWER;
}

QString FlickrSettings::getPythonPath()
{
    return TestFlickrPlugin::PYTHON_PATH_ANSWER;
}


FlickrSettings::FlickrSettings(QWidget *parent)
{

}

FlickrSettings::~FlickrSettings()
{

}


void FlickrSettings::saveSettings()
{
}



void FlickrSettings::loadSettings()
{

}

