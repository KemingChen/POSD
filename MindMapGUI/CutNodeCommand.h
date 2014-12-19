#pragma once
#include "Command.h"
#include "MindMapModel.h"

class CutNodeCommand : public Command
{
    private:
        MindMapModel* _model;
        Component* _parentNode;
        Component* _selectedNode;
        Component* _backFromNode;

    public:
        CutNodeCommand(MindMapModel* model, Component* node);
        void execute();
        void unexecute();
        ~CutNodeCommand();
};