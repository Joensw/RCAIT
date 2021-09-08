#ifndef PROGRESSABLE_H
#define PROGRESSABLE_H

#include <QObject>

/**
 * @brief The Progressable class defines an interface for all classes that accept progress messages
 *
 */
class Progressable : public QObject {
Q_OBJECT

public:
    /**
     * @brief constructor
     */
    Progressable() = default;

public slots:

    /**
     * @brief slot_makeProgress accepts progress message and does something
     *
     * @param progress progress message
     */
    virtual void slot_makeProgress(int progress) = 0;

};

#endif // PROGRESSABLE_H
