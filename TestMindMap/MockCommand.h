#pragma once
#include "Command.h"

class MockCommand : public Command
{
    public:
        MockCommand();
        void execute();
        void unexecute();
        ~MockCommand();
};