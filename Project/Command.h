#pragma once

class Command
{
    private:
    public:
        Command();
        virtual void execute() = 0;
        virtual void unexecute() = 0;
        ~Command();
};