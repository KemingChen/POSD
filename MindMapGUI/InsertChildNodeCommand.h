#pragma once
#include "Command.h"
#include "MindMapModel.h"

class InsertChildNodeCommand :  public Command
{
    private:
        MindMapModel* _model;
        Component* _node;
        Component* _newNode;

    public:
        InsertChildNodeCommand(MindMapModel* model, Component* node, Component* newNode);
        void execute();
        void unexecute();
        ~InsertChildNodeCommand();
};