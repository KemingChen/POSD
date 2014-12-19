#pragma once
#include "Command.h"
#include "MindMapModel.h"

class DeleteComponentCommand : public Command
{
    private:
        MindMapModel* _model;
        Component* _node;
        Component* _backFromNode;

    public:
        DeleteComponentCommand(MindMapModel* model, Component* node);
        void execute();
        void unexecute();
        ~DeleteComponentCommand();
};