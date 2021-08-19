#include "imageloadcommand.h"
#include "imageloaderpluginmanager.h"


ImageLoadCommand::ImageLoadCommand(QVariantMap map, QString imagePath, ProgressablePlugin* receiver)
{   bool ok;

    mPluginName = map.value("imagePluginName").toString();
    mCount  = map.value("count").toInt(&ok);
    mLabels = map.value("labels").toStringList();
    mPath = imagePath;
    mReceiver = receiver;

    if (imagePath.isNull() || mPluginName.isNull() || !ok || mLabels.isEmpty()){
        parsingFailed = true;
        return;
    }

    QWidget* inputWidget = mPluginManager.getConfigurationWidget(mPluginName);

    auto end = map.end();
    for(auto it = map.begin(); it != end; ++it){
        const char* charstring = it.key().toUtf8().data();
        inputWidget->setProperty(charstring, it.value());
    }

    mPluginManager.saveConfiguration(mPluginName);
}

bool ImageLoadCommand::execute(){
    if(parsingFailed) return false;
    return mPluginManager.loadImages(mPath, mReceiver, mPluginName, mCount, mLabels);
}
