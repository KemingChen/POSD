#pragma once
#include "Command.h"
#include "MindMapModel.h"

class PasteNodeCommand : public Command
{
    private:
        MindMapModel* _model;
        Component* _selectedNode;
        Component* _cloneNode;
        Component* _pasteNode;

    public:
        PasteNodeCommand(MindMapModel* model, Component* selectedNode, Component* cloneNode);
        void execute();
        void unexecute();
        ~PasteNodeCommand();
};