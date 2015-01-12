#pragma once
#include "Command.h"
#include "MindMapModel.h"

class CleanAllDecorateCommand : public Command
{
    private:
        MindMapModel* _model;
        Component* _node;

    public:
        CleanAllDecorateCommand(MindMapModel* model, Component* node);
        void execute();
        void unexecute();
        ~CleanAllDecorateCommand();
};