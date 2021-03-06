#include "stdafx.h"
#include "DeleteComponentCommand.h"

DeleteComponentCommand::DeleteComponentCommand(MindMapModel* model, Component* node) : Command()
{
    _model = model;
    _node = node;
    _backFromNode = node->getBackFromNode();
}

void DeleteComponentCommand::execute()
{
    _model->deleteNode(_node);
}

void DeleteComponentCommand::unexecute()
{
    _model->revertDeleteNode(_node, _backFromNode);
}

DeleteComponentCommand::~DeleteComponentCommand()
{
}