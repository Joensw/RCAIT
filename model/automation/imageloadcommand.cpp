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

    mInputWidget = mPluginManager.getConfigurationWidget(mPluginName);

    auto end = map.end();
    for(auto it = map.begin(); it != end; ++it){
        if (mInputWidget->property(it.key().toUtf8().data()).isValid()){
            mWidgetOptions.insert(it.key(), it.value());
        }
    }
}

bool ImageLoadCommand::execute(){
    if(parsingFailed) return false;

    auto end = mWidgetOptions.end();
    for (auto it = mWidgetOptions.begin(); it != end; ++it){
        mInputWidget->setProperty(it.key().toUtf8().data(), it.value());
    }
    mPluginManager.saveConfiguration(mPluginName);

    return mPluginManager.loadImages(mPath, mReceiver, mPluginName, mCount, mLabels);
}
