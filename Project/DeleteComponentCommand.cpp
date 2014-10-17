#include "stdafx.h"
#include "DeleteComponentCommand.h"

DeleteComponentCommand::DeleteComponentCommand(MindMapModel* model, Component* node) : Command()
{
    _model = model;
    _node = node;
}

void DeleteComponentCommand::execute()
{
    _model->deleteNode(_node);
}

void DeleteComponentCommand::unexecute()
{
    NodeList* nodeList = _node->getNodeList();
    Component* parentNode = _node->getParent();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        parentNode->removeChild(*iNode);
    }
    parentNode->addChild(_node);
}

DeleteComponentCommand::~DeleteComponentCommand()
{
}