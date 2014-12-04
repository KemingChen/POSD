#include "stdafx.h"
#include "PresentModel.h"
#include "ComponentFactory.h"
#include <fstream>

PresentModel::PresentModel(MindMapModel* model)
{
    _model = model;
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

void PresentModel::createMindMap(string description)
{
    _model->createMinMap(description);
    _commandManager.clear();
}

void PresentModel::saveMindMap(string path)
{
    ofstream file(path);
    _model->saveMindMap(&file);
    file.close();
    _commandManager.clear();
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
    _commandManager.clear();
}

void PresentModel::insertParentNode(Component* choseNode, string description)
{
    Component* newNode = ComponentFactory::getInstance()->createComponent(NODE, description);
    Command* command = new InsertParentNodeCommand(_model, choseNode, newNode);
    _commandManager.execute(command);
}

void PresentModel::insertChildNode(Component* choseNode, string description)
{
    Component* newNode = ComponentFactory::getInstance()->createComponent(NODE, description);
    Command* command = new InsertChildNodeCommand(_model, choseNode, newNode);
    _commandManager.execute(command);
}

void PresentModel::insertSiblingNode(Component* choseNode, string description)
{
    Component* newNode = ComponentFactory::getInstance()->createComponent(NODE, description);
    Command* command = new InsertSiblingNodeCommand(_model, choseNode, newNode);
    _commandManager.execute(command);
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

Component* PresentModel::getRoot()
{
    return _model->getRootNode();
}

void PresentModel::editNodeDescription(Component* node, string description)
{
    Command* command = new EditComponentCommand(_model, node, description);
    _commandManager.execute(command);
}

void PresentModel::changeNodeParent(Component* node, Component* newParentNode)
{
    // Node == New Parent Node
    if (node == newParentNode)
    {
        throw string("You can’t select itself!!");
    }
    Command* command = new ChangeParentCommand(_model, node, newParentNode);
    _commandManager.execute(command);
}

void PresentModel::deleteNode(Component* node)
{
    if (_model->getRootNode() == node)
    {
        throw string("You can't delete the root.");
    }
    Command* command = new DeleteComponentCommand(_model, node);
    _commandManager.execute(command);
}

void PresentModel::confirmMindMapExist()
{
    if (_model->getRootNode() == NULL)
    {
        throw string("The MindMap Should be Created First!!!");
    }
}

void PresentModel::confirmChangeNodeLegal(Component* node)
{
    if (_model->getRootNode() == node)
    {
        throw string("Root can't be changed the parent.");
    }
}

void PresentModel::confirmInsertNodeLegal(Component* node, InsertMethod insertMethod)
{
    (_model->*insertMethod)(node, NULL);
}

void PresentModel::redo()
{
    _commandManager.redo();
}

void PresentModel::undo()
{
    _commandManager.undo();
}

void PresentModel::pasteNode(Component* selectedNode, Component* cloneNode)
{
    _model->pasteNode(selectedNode, cloneNode);
}

PresentModel::~PresentModel()
{
}