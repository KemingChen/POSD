#pragma once
#include "MindMapModel.h"

class Command
{
    protected:
        MindMapModel* _model;

    public:
        Command(MindMapModel* model);
        virtual void execute() = 0;
        virtual void unexecute() = 0;
        ~Command();
};