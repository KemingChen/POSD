#pragma once
#include "Command.h"
#include "MindMapModel.h"
using namespace std;

class EditComponentCommand : public Command
{
    private:
        string _oldDescription;
        string _newDescription;
        Component* _node;
        MindMapModel* _model;

    public:
        //EditComponentCommand();
        EditComponentCommand(MindMapModel* model, Component* node, string description);
        void execute();
        void unexecute();
        ~EditComponentCommand();
};