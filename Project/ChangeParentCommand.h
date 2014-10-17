#pragma once
#include "Command.h"

class ChangeParentCommand : public Command
{
    private:
        Component* _node;
        Component* _newParentNode;
        //NodeList _nodeList;

    public:
        ChangeParentCommand(Component* node, Component* newParentNode);
        void execute();
        void unexecute();
        ~ChangeParentCommand();
};