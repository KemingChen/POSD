#include "stdafx.h"
#include "PresentModel.h"
#include "ComponentFactory.h"
#define DB_FILE "file__exist.mm"

PresentModel::PresentModel(MindMapModel* model)
{
    _model = model;
    _insertActionMap["a"] = &MindMapModel::insertParentNode;
    _insertActionMap["b"] = &MindMapModel::insertChildNode;
    _insertActionMap["c"] = &MindMapModel::insertSiblingNode;
}

MindMapModel* PresentModel::getModel()
{
    return _model;
}

string PresentModel::getMindMap(Component* root)
{
    string output = "";
    output += root->toString() + "\n";
    NodeList* nodeList = root->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        output += getNodeMap(*iNode, "", true);
    }
    return output;
}

// 得到該 Node 的 for TextUI String
string PresentModel::getNodeMap(Component* node, string prefix, bool isParentAreLastNode)
{
    string output = "";
    prefix += isParentAreLastNode ? "　　" : "｜　";
    output += prefix + node->toString() + "\n";
    NodeList* nodeList = node->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        output += getNodeMap(*iNode, prefix, node->isSelfAreParentLastNode());
    }
    return output;
}

void PresentModel::saveMindMap()
{
    _model->saveMindMap(DB_FILE);
}

Component* PresentModel::insertNode(Component* choseNode, string action)
{
    Component* newNode = ComponentFactory::getInstance()->createComponent(NODE);
    try
    {
        if (!_insertActionMap[action])
        {
            throw string("Unknown Action: " + action);
        }
        (_model->*_insertActionMap[action])(choseNode, newNode);
    }
    catch (string error)
    {
        ComponentFactory::getInstance()->revertCreateId();
        throw error;
    }
    return newNode;
}

Component* PresentModel::tryFindNode(string id)
{
    Component* node = _model->findNode(id);
    if (node == NULL)
    {
        throw string("The node is not exist!!");
    }
    return node;
}

PresentModel::~PresentModel()
{
}