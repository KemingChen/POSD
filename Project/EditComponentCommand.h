#pragma once
#include "Command.h"
using namespace std;

class EditComponentCommand : public Command
{
    private:
        string _oldDescription;
        string _newDescription;
        Component* _node;

    public:
        //EditComponentCommand();
        EditComponentCommand(MindMapModel* model, Component* node, string description);
        void execute();
        void unexecute();
        ~EditComponentCommand();
};