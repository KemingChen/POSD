#pragma once
#include <stack>
#include "Command.h"
#include "EditComponentCommand.h"
#include "ChangeParentCommand.h"
#include "DeleteComponentCommand.h"
#include "InsertChildNodeCommand.h"
#include "InsertParentNodeCommand.h"
#include "InsertSiblingNodeCommand.h"
#include "CutNodeCommand.h"
#include "PasteNodeCommand.h"
#include "AddDecorateCommnad.h"
#include "CleanAllDecorateCommand.h"
using namespace std;

class CommandManager
{
        friend class PresentModelTest;
        FRIEND_TEST(CommandManagerTest, execute);
        FRIEND_TEST(CommandManagerTest, clear);
        FRIEND_TEST(CommandManagerTest, redo);
        FRIEND_TEST(CommandManagerTest, undo);

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
        bool canUndo();
        bool canRedo();
        ~CommandManager();
};