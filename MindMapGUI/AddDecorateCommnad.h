#pragma once
#include "Command.h"
#include "MindMapModel.h"

class AddDecorateCommnad : public Command
{
    private:
        MindMapModel* _model;
        Component* _decorateNode;
        Component* _node;

    public:
        AddDecorateCommnad(MindMapModel* model, Component* node, ComponentType type);
        void execute();
        void unexecute();
        ~AddDecorateCommnad();
};