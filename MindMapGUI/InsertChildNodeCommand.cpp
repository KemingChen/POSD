#include "stdafx.h"
#include "InsertChildNodeCommand.h"

InsertChildNodeCommand::InsertChildNodeCommand(MindMapModel* model, Component* node, Component* newNode)
{
    _model = model;
    _node = node;
    _newNode = newNode;
}

void InsertChildNodeCommand::execute()
{
    _model->insertChildNode(_node, _newNode);
}

void InsertChildNodeCommand::unexecute()
{
    _model->deleteNode(_newNode);
}

InsertChildNodeCommand::~InsertChildNodeCommand()
{
}