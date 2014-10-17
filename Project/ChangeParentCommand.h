#pragma once
#include "Command.h"

class ChangeParentCommand : public Command
{
    private:
        Component* node;
        Component* changeParentNode;
        NodeList nodeList;

    public:
        ChangeParentCommand(Component* node, Component* changeParentNode);
        void execute();
        void unexecute();
        ~ChangeParentCommand();
};