#pragma once
#include "Command.h"
#include "MindMapModel.h"

class AddDecorateCommnad : public Command
{
    private:
        MindMapModel* _model;
        Component* _node;
        ComponentType _type;

    public:
        AddDecorateCommnad(MindMapModel* model, Component* node, ComponentType type);
        void execute();
        void unexecute();
        ~AddDecorateCommnad();
};