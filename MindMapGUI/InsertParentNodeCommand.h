#pragma once
#include "Command.h"
#include "MindMapModel.h"

class InsertParentNodeCommand : public Command
{
    private:
        MindMapModel* _model;
        Component* _oldParentNode;
        Component* _node;
        Component* _newNode;
        Component* _backFromNode;

    public:
        InsertParentNodeCommand(MindMapModel* model, Component* node, Component* newNode);
        void execute();
        void unexecute();
        ~InsertParentNodeCommand();
};