#include "stdafx.h"
#include "ChangeParentCommand.h"

ChangeParentCommand::ChangeParentCommand(Component* node, Component* changeParentNode) : Command(_model)
{
}

void ChangeParentCommand::execute()
{
}

void ChangeParentCommand::unexecute()
{
}

ChangeParentCommand::~ChangeParentCommand()
{
}