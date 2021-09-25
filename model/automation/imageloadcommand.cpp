#include "imageloadcommand.h"
#include "imageloaderpluginmanager.h"


ImageLoadCommand::ImageLoadCommand(QVariantMap map, const QString &imagePath, ProgressablePlugin *receiver)
        : mPluginName(map["imagePluginName"].toString()),
          mLabels(map["labels"].toStringList()),
          mPath(imagePath),
          mReceiver(receiver) {
    bool ok;
    mCount = map["count"].toInt(&ok);

    if (imagePath.isNull() || mPluginName.isNull() || !ok || mLabels.isEmpty()) {
        parsingFailed = true;
        return;
    }

    mInputWidget = mPluginManager.getInputWidget(mPluginName);
    if (!mInputWidget) return;

    for (const auto &[key, value]: MapAdapt(map)) {
        if (mInputWidget->property(key.toUtf8().data()).isValid()) {
            mWidgetOptions[key] = value;
        }
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
