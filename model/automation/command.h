#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

/**
 * @brief The Command class defines an interface for all commands in the application.
 *
 */
class Command : public QObject {
Q_OBJECT

public:
    /**
     * @brief execute executes the command.
     * @return true if execution was successful, false if it failed.
     */
    virtual bool execute() = 0;

};

#endif // COMMAND_H
