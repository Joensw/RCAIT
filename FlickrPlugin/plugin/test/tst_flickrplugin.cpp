#include "tst_flickrplugin.h"

QString TestFlickrPlugin::API_KEY_ANSWER = "3391c68aa039902833f0c7bb1e0755ae";
QString TestFlickrPlugin::API_SECRET_ANSWER = "6acffd9f01ca35c8";
QString TestFlickrPlugin::PYTHON_PATH_ANSWER = "C:/Python3/python.exe";

TestFlickrPlugin::TestFlickrPlugin() : QObject(nullptr)
{

}

void TestFlickrPlugin::init()
{

    cut_ = new FlickrPlugin();
    dir.mkdir(QDir::currentPath() + DOWNLOAD_SUBDIR);
}

void TestFlickrPlugin::cleanup()
{

    QDir deleteDir(QDir::currentPath() + DOWNLOAD_SUBDIR);
    //deleteDir.removeRecursively();

    delete cut_;
    cut_ = 0;
}

void TestFlickrPlugin::testAPIKey()
{

}

void TestFlickrPlugin::testAPISecret()
{

}

void TestFlickrPlugin::testProcessPythonScriptCall()
{
    cut_->loadImages(VALID_DOWNLOAD_PATH,VALID_IMAGE_COUNT,&VALID_LABELS);
}
