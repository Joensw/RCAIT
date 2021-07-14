#ifndef COMMAND_H
#define COMMAND_H

#include <QVariantMap>


/**
 * @brief The Command class defines an interface for all commands in the application
 */
class Command
{
public:
    /**
     * @brief Command
     * @param info contains all information needed to use execute
     */
    Command(QVariantMap info = QVariantMap());
    virtual void execute() = 0;
};

#endif // COMMAND_H
