#pragma once
#include "Command.h"

class DeleteComponentCommand : public Command
{
    public:
        DeleteComponentCommand();
        void execute();
        void unexecute();
        ~DeleteComponentCommand();
};