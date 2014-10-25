#include "stdafx.h"
#include "InsertParentNodeCommand.h"
InsertParentNodeCommand::InsertParentNodeCommand(MindMapModel* model, Component* node, Component* newNode)
{
    _model = model;
    _node = node;
    _newNode = newNode;
    _oldParentNode = node->getParent();
}

void InsertParentNodeCommand::execute()
{
    _model->insertParentNode(_node, _newNode);
}

void InsertParentNodeCommand::unexecute()
{
    _model->revertInsertParentNode(_node, _newNode, _oldParentNode);
}

InsertParentNodeCommand::~InsertParentNodeCommand()
{
}