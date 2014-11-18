#include "stdafx.h"
#include "InsertSiblingNodeCommand.h"

InsertSiblingNodeCommand::InsertSiblingNodeCommand(MindMapModel* model, Component* node, Component* newNode)
{
    _model = model;
    _node = node;
    _newNode = newNode;
}

void InsertSiblingNodeCommand::execute()
{
    _model->insertSiblingNode(_node, _newNode);
}

void InsertSiblingNodeCommand::unexecute()
{
    _model->deleteNode(_newNode);
}

InsertSiblingNodeCommand::~InsertSiblingNodeCommand()
{
}