#pragma once
#include "Command.h"

class EditComponentCommand : public Command
{
    public:
        EditComponentCommand();
        void execute();
        void unexecute();
        ~EditComponentCommand();
};