#include "stdafx.h"
#include <iostream>
#include "PresentModel.h"
#define DB_FILE "MindMap.db"

PresentModel::PresentModel(MindMapModel* model)
{
    _model = model;
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

PresentModel::~PresentModel()
{
}