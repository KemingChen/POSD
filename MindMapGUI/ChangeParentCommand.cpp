#include "stdafx.h"
#include "ChangeParentCommand.h"

ChangeParentCommand::ChangeParentCommand(MindMapModel* model, Component* node, Component* newParentNode) : Command()
{
    _model = model;
    _node = node;
    _newParentNode = newParentNode;
    _oldParentNode = node->getParent();
    _revertOldNodeList = model->findNode(node, newParentNode->getId()) != NULL;
    if (_revertOldNodeList)
    {
        NodeList* nodeList = node->getNodeList();
        for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
        {
            _oldNodeList.push_back(*iNode);
        }
    }
}

void ChangeParentCommand::execute()
{
    _model->changeNodeParent(_node, _newParentNode);
}

void ChangeParentCommand::unexecute()
{
    _model->revertChangeNodeParent(_node, _oldParentNode, &_oldNodeList);
}

ChangeParentCommand::~ChangeParentCommand()
{
}