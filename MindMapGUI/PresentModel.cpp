#include "stdafx.h"
#include "PresentModel.h"
#include "ComponentFactory.h"
#include <fstream>

PresentModel::PresentModel(MindMapModel* model)
{
    _model = model;
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
    _commandManager.clear();
    _model->loadMindMap(&file);
    file.close();
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
        throw string("You can¡¦t select itself!!");
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

bool PresentModel::canUndo()
{
    return _commandManager.canUndo();
}

bool PresentModel::canRedo()
{
    return _commandManager.canRedo();
}

void PresentModel::redo()
{
    _commandManager.redo();
}

void PresentModel::undo()
{
    _commandManager.undo();
}

void PresentModel::clearCommandManager()
{
    _commandManager.clear();
}

void PresentModel::cutNode(Component* selectedNode)
{
    Command* command = new CutNodeCommand(_model, selectedNode);
    _commandManager.execute(command);
}

void PresentModel::pasteNode(Component* selectedNode, Component* cloneNode)
{
    Command* command = new PasteNodeCommand(_model, selectedNode, cloneNode);
    _commandManager.execute(command);
}

PresentModel::~PresentModel()
{
}