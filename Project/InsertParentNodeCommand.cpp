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
    _newNode->removeChild(_node);
    _oldParentNode->removeChild(_newNode);
    _oldParentNode->addChild(_node);
}

InsertParentNodeCommand::~InsertParentNodeCommand()
{
}
