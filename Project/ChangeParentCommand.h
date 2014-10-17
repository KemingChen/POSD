#pragma once
#include "Command.h"
#include "MindMapModel.h"

class ChangeParentCommand : public Command
{
    private:
        Component* _node;
        Component* _newParentNode;
        Component* _oldParentNode;
        MindMapModel* _model;
        NodeList _oldNodeList;
        bool _revertOldNodeList;

    public:
        ChangeParentCommand(MindMapModel* model, Component* node, Component* newParentNode);
        void execute();
        void unexecute();
        ~ChangeParentCommand();
};