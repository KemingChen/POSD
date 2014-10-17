#pragma once
#include "Command.h"
#include "EditComponentCommand.h"
#include "ChangeParentCommand.h"
#include "DeleteComponentCommand.h"
#include <stack>

class CommandManager
{
    private:
        stack<Command*> redoCommands;
        stack<Command*> undoCommands;

    public:
        CommandManager();
        void execute(Command* commnad);
        void redo();
        void undo();
        ~CommandManager();
};