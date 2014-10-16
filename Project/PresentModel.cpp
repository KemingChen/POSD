#include "stdafx.h"
#include "PresentModel.h"
#include "ComponentFactory.h"
#include <fstream>
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

string PresentModel::getMindMap()
{
    Component* root = _model->getRootNode();
    string output = "";
    if (root == NULL)
    {
        return "The mind map is Empty!!!";
    }
    output += "The mind map " + root->getDescription() + " is desplayed as follows: \n";
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
    ofstream file(DB_FILE);
    _model->saveMindMap(&file);
    file.close();
}

void PresentModel::loadMindMap(string path)
{
    ifstream file(path);
    if (!file.good())
    {
        throw string("File not found!!");
    }
    _model->loadMindMap(&file);
    file.close();
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

void PresentModel::changeParentNode(Component* node, Component* newParentNode)
{
    // Node == New Parent Node
    if (node == newParentNode)
    {
        throw string("You can’t select itself!!");
    }
    // Node's Children Not Contain New Parent Node
    if (_model->findNode(node, newParentNode->getId()) == NULL)
    {
        node->getParent()->removeChild(node);
        newParentNode->addChild(node);
    }
    // Node's Children Contain New Parent Node
    else
    {
        Component* oldParent = node->getParent();
        NodeList* nodeList = node->getNodeList();
        for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
        {
            oldParent->addChild(*iNode);
        }
        oldParent->removeChild(node);
        node->removeAllChild();
        newParentNode->addChild(node);
    }
}

void PresentModel::confirmMindMapExist()
{
    if (_model->getRootNode() == NULL)
    {
        throw string("The MindMap Should be Created First!!!");
    }
}

void PresentModel::confirmChangeNodeNotRoot(Component* changeNode)
{
    if (_model->getRootNode() == changeNode)
    {
        throw string("Root can't be changed the parent.");
    }
}

PresentModel::~PresentModel()
{
}