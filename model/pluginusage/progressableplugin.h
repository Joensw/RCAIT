#ifndef PROGRESSABLEPLUGIN_H
#define PROGRESSABLEPLUGIN_H

#include "progressable.h"

/**
 * @brief The ProgressablePlugin class defines an interface for all classes that use plugins
 *
 */
class ProgressablePlugin : public Progressable
{
    Q_OBJECT

signals:

    /**
     * @brief sig_pluginStarted signals that plugin has been started
     *
     */
    void sig_pluginStarted();

    /**
     * @brief sig_pluginAborted signals abortion of plugin
     *
     */
    void sig_pluginAborted();

    /**
     * @brief sig_pluginFinished signals finishing of plugin
     *
     */
    void sig_pluginFinished();

    /**
     * @brief sig_progress signals progress
     *
     * @param progress progress message
     */
    virtual void sig_progress(int progress);

    /**
     * @brief sig_statusUpdate signals status update
     *
     * @param status status message
     */
    void sig_statusUpdate(QString status);
};

#endif // PROGRESSABLEPLUGIN_H
