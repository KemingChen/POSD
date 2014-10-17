#include "stdafx.h"
#include "ChangeParentCommand.h"

ChangeParentCommand::ChangeParentCommand(MindMapModel* model, Component* node, Component* newParentNode) : Command()
{
    _model = model;
    _node = node;
    _newParentNode = newParentNode;
    _oldParentNode = node->getParent();
    _revertOldNodeList = model->findNode(node, newParentNode->getId()) != NULL;
    NodeList* nodeList = node->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        _oldNodeList.push_back(*iNode);
    }
}

void ChangeParentCommand::execute()
{
    _model->changeNodeParent(_node, _newParentNode);
}

void ChangeParentCommand::unexecute()
{
    _model->changeNodeParent(_node, _oldParentNode);
    if (_revertOldNodeList)
    {
        for (NodeList::iterator iNode = _oldNodeList.begin(); iNode != _oldNodeList.end(); iNode++)
        {
            _oldParentNode->removeChild(*iNode);
            _node->addChild(*iNode);
        }
    }
}

ChangeParentCommand::~ChangeParentCommand()
{
}