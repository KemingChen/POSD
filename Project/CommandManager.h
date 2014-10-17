#pragma once
#include <stack>
#include "Command.h"
#include "EditComponentCommand.h"
#include "ChangeParentCommand.h"
#include "DeleteComponentCommand.h"
using namespace std;

class CommandManager
{
    private:
        typedef stack<Command*> CommandStack;
        CommandStack _redoCommands;
        CommandStack _undoCommands;

        // Private Method
        void clearStack(CommandStack* stack);
        Command* getCommand(CommandStack* stack, string errorMessage);

    public:
        CommandManager();
        void execute(Command* commnad);
        void clear();
        void redo();
        void undo();
        ~CommandManager();
};