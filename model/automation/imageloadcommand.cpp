#include "imageloadcommand.h"
#include "imageloaderpluginmanager.h"


ImageLoadCommand::ImageLoadCommand(const QVariantMap &map, ProgressablePlugin *receiver)
        : mPluginName(map["imagePluginName"].toString()),
          mLabels(map["labels"].toStringList()),
          mPath(mDataManager.getProjectImageTempDir()),
          mReceiver(receiver) {
    bool ok;
    mCount = map["count"].toInt(&ok);

    if (mPath.isNull() || mPluginName.isNull() || !ok || mLabels.isEmpty()) {
        parsingFailed = true;
        return;
    }

    mInputWidget = mPluginManager.getInputWidget(mPluginName);
    if (!mInputWidget) return;

    for (const auto &[key, value]: MapAdapt(map)) {
        if (mInputWidget->property(key.toUtf8().data()).isValid())
            mWidgetOptions[key] = value;
    }
}

bool ImageLoadCommand::execute() {
    if (parsingFailed) return false;

    for (const auto &[key, value]: MapAdapt(mWidgetOptions)) {
        mInputWidget->setProperty(key.toUtf8().data(), value);
    }
    mPluginManager.saveConfiguration(mPluginName);

    return mPluginManager.loadImages(mPath, mReceiver, mPluginName, mCount, mLabels);
}
