#pragma once
#include "Command.h"
#include "MindMapModel.h"

class InsertSiblingNodeCommand : public Command
{
    private:
        MindMapModel* _model;
        Component* _node;
        Component* _newNode;

    public:
        InsertSiblingNodeCommand(MindMapModel* model, Component* node, Component* newNode);
        void execute();
        void unexecute();
        ~InsertSiblingNodeCommand();
};