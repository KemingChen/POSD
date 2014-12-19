#include "stdafx.h"
#include "CommandManager.h"

CommandManager::CommandManager()
{
}

void CommandManager::execute(Command* command)
{
    _undoCommands.push(command);
    clearStack(&_redoCommands);
    command->execute();
}

// if stack is empty => throw error Message
Command* CommandManager::getCommand(CommandStack* stack, string errorMessage)
{
    if (stack->empty())
    {
        throw string(errorMessage);
    }
    Command* command = stack->top();
    stack->pop();
    return command;
}

void CommandManager::redo()
{
    Command* command = getCommand(&_redoCommands, "Can't Redo!");
    _undoCommands.push(command);
    command->execute();
}

void CommandManager::undo()
{
    Command* command = getCommand(&_undoCommands, "Can't Undo!");
    _redoCommands.push(command);
    command->unexecute();
}

void CommandManager::clear()
{
    clearStack(&_redoCommands);
    clearStack(&_undoCommands);
}

void CommandManager::clearStack(CommandStack* stack)
{
    while (!stack->empty())
    {
        delete stack->top();
        stack->pop();
    }
}

bool CommandManager::canUndo()
{
    return _undoCommands.size() > 0;
}

bool CommandManager::canRedo()
{
    return _redoCommands.size() > 0;
}

CommandManager::~CommandManager()
{
}