#pragma once

class Command
{
    public:
        Command();
        virtual void execute() = 0;
        virtual void unexecute() = 0;
        ~Command();
};