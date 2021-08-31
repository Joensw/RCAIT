#ifndef PROGRESSABLE_H
#define PROGRESSABLE_H

#include <QObject>


class Progressable : public QObject {
Q_OBJECT
public:
    Progressable() = default;

public slots:

    virtual void slot_makeProgress(int progress) = 0;

};

#endif // PROGRESSABLE_H
