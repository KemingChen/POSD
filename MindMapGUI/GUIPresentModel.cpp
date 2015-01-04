#include "GUIPresentModel.h"
#include "ComponentFactory.h"
#include <iostream>

#define MIN_DELTA_CLICK_TIME 20

GUIPresentModel::GUIPresentModel(PresentModel* presentModel, MindMapModel* model)
{
    this->_prepareCloneNode = NULL;
    this->_selectedNode = NULL;
    this->_lastClickTime = -1000;
    this->_presentModel = presentModel;
    this->_model = model;
}

bool GUIPresentModel::isValidClick()
{
    bool isValid = clock() - _lastClickTime > MIN_DELTA_CLICK_TIME;
    if (!isValid)
    {
        return false;
    }
    else
    {
        _lastClickTime = clock();
        return true;
    }
}

bool GUIPresentModel::isValidText(bool isSubmit, string text)
{
    if (isSubmit && text.empty())
        this->notify("Text cannot be empty!!!");
    return isSubmit &&  !text.empty();
}

void GUIPresentModel::cancelSelected()
{
    if (_selectedNode != NULL)
    {
        _selectedNode->setIsSelected(false);
        _selectedNode = NULL;
    }
}

void GUIPresentModel::clickGraphicNode(string id)
{
    if (!isValidClick())
        return;
    Component* node = id.empty() ? NULL : _presentModel->tryFindNode(id);
    this->cancelSelected();
    if (node != NULL)
        node->setIsSelected(true);
    _selectedNode = node;
}

void GUIPresentModel::editDescription(string text, bool isValid)
{
    if (this->isValidText(isValid, text) && _selectedNode != NULL)
    {
        this->_presentModel->editNodeDescription(_selectedNode, text);
    }
}

void GUIPresentModel::loadMindMap(string path)
{
    if (this->isValidText(true, path))
    {
        this->_presentModel->loadMindMap(path);
    }
}

void GUIPresentModel::saveMindMap(string path)
{
    if (this->isValidText(true, path))
    {
        this->_presentModel->saveMindMap(path);
    }
}

void GUIPresentModel::createMindMap(string text, bool isValid)
{
    if (this->isValidText(isValid, text))
    {
        this->_presentModel->createMindMap(text);
    }
}

void GUIPresentModel::insertParentNode(string text, bool isValid)
{
    if (this->isValidText(isValid, text))
    {
        this->_presentModel->insertParentNode(_selectedNode, text);
    }
}

void GUIPresentModel::insertChildNode(string text, bool isValid)
{
    if (this->isValidText(isValid, text))
    {
        this->_presentModel->insertChildNode(_selectedNode, text);
    }
}

void GUIPresentModel::insertSiblingNode(string text, bool isValid)
{
    if (this->isValidText(isValid, text))
    {
        this->_presentModel->insertSiblingNode(_selectedNode, text);
    }
}

bool GUIPresentModel::isSaveEnable()
{
    return isCreatedMindMap();
}

bool GUIPresentModel::isSelected()
{
    return _selectedNode != NULL;
}

bool GUIPresentModel::isDeleteNodeEnable()
{
    return isSelected() && _presentModel->getRoot() != _selectedNode;
}

bool GUIPresentModel::isEditNodeEnable()
{
    return isSelected();
}

bool GUIPresentModel::confirmInsertNodeLegal(InsertMethod insertMethod)
{
    if (isSelected())
    {
        try
        {
            _presentModel->confirmInsertNodeLegal(_selectedNode, insertMethod);
            return true;
        }
        catch (string error)
        {
            notify(error);
        }
    }
    return false;
}

bool GUIPresentModel::isInsertParentNodeEnable()
{
    return this->confirmInsertNodeLegal(&MindMapModel::insertParentNode);
}

bool GUIPresentModel::isInsertChildNodeEnable()
{
    return this->confirmInsertNodeLegal(&MindMapModel::insertChildNode);
}

bool GUIPresentModel::isInsertSiblingNodeEnable()
{
    return this->confirmInsertNodeLegal(&MindMapModel::insertSiblingNode);
}

void GUIPresentModel::deleteNode()
{
    _presentModel->deleteNode(_selectedNode);
    this->cancelSelected();
}

void GUIPresentModel::cutNode()
{
    _presentModel->cutNode(_selectedNode);
    _prepareCloneNode = _selectedNode;
    this->cancelSelected();
}

void GUIPresentModel::copyNode()
{
    _prepareCloneNode = _selectedNode->clone();
}

void GUIPresentModel::pasteNode()
{
    _presentModel->pasteNode(_selectedNode, _prepareCloneNode);
}

bool GUIPresentModel::isSelectedNode(Component* node)
{
    return _selectedNode == node;
}

bool GUIPresentModel::isCreatedMindMap()
{
    return _presentModel->getRoot() != NULL;
}

bool GUIPresentModel::isCutNodeEnable()
{
    return isSelected() && _presentModel->getRoot() != _selectedNode;
}

bool GUIPresentModel::isCopyNodeEnable()
{
    return isCutNodeEnable();
}

bool GUIPresentModel::isPasteNodeEnable()
{
    return isSelected() && _prepareCloneNode != NULL;
}

Component* GUIPresentModel::getSelectedNode()
{
    return _selectedNode;
}

Component* GUIPresentModel::getRoot()
{
    return _presentModel->getRoot();
}

void GUIPresentModel::undo()
{
    this->cancelSelected();
    _presentModel->undo();
}

void GUIPresentModel::redo()
{
    this->cancelSelected();
    _presentModel->redo();
}

bool GUIPresentModel::isUndoEnable()
{
    return _presentModel->canUndo();
}

bool GUIPresentModel::isRedoEnable()
{
    return _presentModel->canRedo();
}

void GUIPresentModel::rebuildPosition()
{
    return _model->rebuildPosition();
}

GUIPresentModel::~GUIPresentModel()
{
}