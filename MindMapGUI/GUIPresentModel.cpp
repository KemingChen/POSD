#include "GUIPresentModel.h"
#include "ComponentFactory.h"
#include <iostream>

#define MIN_DELTA_CLICK_TIME 20
#define ERROR_DESCRIPTION_EMPTY "Description is Empty!!!"

GUIPresentModel::GUIPresentModel(PresentModel* presentModel)
{
    _prepareCloneNode = NULL;
    _selectedNode = NULL;
    _lastClickTime = -1000;
    _presentModel = presentModel;
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

void GUIPresentModel::clickGraphicNode(string id)
{
    if (!isValidClick())
        return;
    Component* node = id.empty() ? NULL : _presentModel->tryFindNode(id);
    if (_selectedNode != node)
    {
        _selectedNode = node;
        notify(SUBJECT_PMODEL_CHANGE, "");
    }
}

void GUIPresentModel::editDescription(string text, bool isValid)
{
    if (isValid && _selectedNode != NULL)
    {
        if (!text.empty())
        {
            _presentModel->editNodeDescription(_selectedNode, text);
        }
        else
        {
            notify(SUBJECT_ERROR, ERROR_DESCRIPTION_EMPTY);
        }
    }
}

void GUIPresentModel::loadMindMap(string path)
{
    if (!path.empty())
    {
        _presentModel->loadMindMap(path);
    }
}

void GUIPresentModel::saveMindMap(string path)
{
    if (!path.empty())
    {
        _presentModel->saveMindMap(path);
    }
}

void GUIPresentModel::createMindMap(string text, bool isValid)
{
    if (isValid)
    {
        if (!text.empty())
        {
            _presentModel->createMindMap(text);
        }
        else
        {
            notify(SUBJECT_ERROR, ERROR_DESCRIPTION_EMPTY);
        }
    }
}

void GUIPresentModel::insertParentNode(string text, bool isValid)
{
    if (isValid)
    {
        if (!text.empty())
        {
            _presentModel->insertParentNode(_selectedNode, text);
        }
        else
        {
            notify(SUBJECT_ERROR, ERROR_DESCRIPTION_EMPTY);
        }
    }
}

void GUIPresentModel::insertChildNode(string text, bool isValid)
{
    if (isValid)
    {
        if (!text.empty())
        {
            _presentModel->insertChildNode(_selectedNode, text);
        }
        else
        {
            notify(SUBJECT_ERROR, ERROR_DESCRIPTION_EMPTY);
        }
    }
}

void GUIPresentModel::insertSiblingNode(string text, bool isValid)
{
    if (isValid)
    {
        if (!text.empty())
        {
            _presentModel->insertSiblingNode(_selectedNode, text);
        }
        else
        {
            notify(SUBJECT_ERROR, ERROR_DESCRIPTION_EMPTY);
        }
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

bool GUIPresentModel::isInsertParentNodeEnable()
{
    if (isSelected())
    {
        try
        {
            _presentModel->confirmInsertNodeLegal(_selectedNode, &MindMapModel::insertParentNode);
            return true;
        }
        catch (string error)
        {
        }
    }
    return false;
}

bool GUIPresentModel::isInsertChildNodeEnable()
{
    if (isSelected())
    {
        try
        {
            _presentModel->confirmInsertNodeLegal(_selectedNode, &MindMapModel::insertChildNode);
            return true;
        }
        catch (string error)
        {
        }
    }
    return false;
}

bool GUIPresentModel::isInsertSiblingNodeEnable()
{
    if (isSelected())
    {
        try
        {
            _presentModel->confirmInsertNodeLegal(_selectedNode, &MindMapModel::insertSiblingNode);
            return true;
        }
        catch (string error)
        {
        }
    }
    return false;
}

void GUIPresentModel::deleteNode()
{
    _presentModel->deleteNode(_selectedNode);
    _selectedNode = NULL;
}

void GUIPresentModel::cutNode()
{
    _presentModel->cutNode(_selectedNode);
    _prepareCloneNode = _selectedNode;
    _selectedNode = NULL;
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

GUIPresentModel::~GUIPresentModel()
{
}