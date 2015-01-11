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
    if (_selectedNode)
    {
        _selectedNode->setIsSelected(false);
        _selectedNode = NULL;
    }
}

void GUIPresentModel::clickGraphicNode(Component* node)
{
    if (!isValidClick())
        return;
    if (node)
        cout << "Click: " << node->getDescription() << " Type ( " + node->getTypeName() << endl;
    this->cancelSelected();
    if (node)
        node->setIsSelected(true);
    this->_selectedNode = node;
    this->notify(SELECTED_CHANGE);
}

void GUIPresentModel::editDescription(string text, bool isValid)
{
    if (this->isValidText(isValid, text) && this->_selectedNode)
    {
        this->_presentModel->editNodeDescription(this->_selectedNode, text);
        this->notify(MODEL_CHANGE);
    }
}

void GUIPresentModel::loadMindMap(string path)
{
    if (this->isValidText(true, path))
    {
        this->_presentModel->loadMindMap(path);
        this->notify(MODEL_CHANGE);
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
        this->notify(CREATE_NEW);
    }
}

void GUIPresentModel::insertParentNode(string text, bool isValid)
{
    if (this->isValidText(isValid, text))
    {
        this->_presentModel->insertParentNode(this->_selectedNode, text);
        this->notify(MODEL_CHANGE);
    }
}

void GUIPresentModel::insertChildNode(string text, bool isValid)
{
    if (this->isValidText(isValid, text))
    {
        this->_presentModel->insertChildNode(this->_selectedNode, text);
        this->notify(MODEL_CHANGE);
    }
}

void GUIPresentModel::insertSiblingNode(string text, bool isValid)
{
    if (this->isValidText(isValid, text))
    {
        this->_presentModel->insertSiblingNode(this->_selectedNode, text);
        this->notify(MODEL_CHANGE);
    }
}

bool GUIPresentModel::isSaveEnable()
{
    return this->isCreatedMindMap();
}

bool GUIPresentModel::isSelected()
{
    return this->_selectedNode != NULL;
}

bool GUIPresentModel::isDeleteNodeEnable()
{
    return this->isSelected() && _presentModel->getRoot() != this->_selectedNode;
}

bool GUIPresentModel::isEditNodeEnable()
{
    return this->isSelected();
}

bool GUIPresentModel::confirmInsertNodeLegal(InsertMethod insertMethod)
{
    if (this->isSelected())
    {
        try
        {
            this->_presentModel->confirmInsertNodeLegal(this->_selectedNode, insertMethod);
            return true;
        }
        catch (string error)
        {
            // notify(error);
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
    this->_presentModel->deleteNode(this->_selectedNode);
    this->cancelSelected();
    this->notify(MODEL_CHANGE);
}

void GUIPresentModel::cutNode()
{
    this->_presentModel->cutNode(this->_selectedNode);
    this->_prepareCloneNode = this->_selectedNode;
    this->cancelSelected();
    this->notify(MODEL_CHANGE);
}

void GUIPresentModel::copyNode()
{
    this->_prepareCloneNode = this->_selectedNode->clone();
}

void GUIPresentModel::pasteNode()
{
    this->_presentModel->pasteNode(this->_selectedNode, this->_prepareCloneNode);
    this->notify(MODEL_CHANGE);
}

bool GUIPresentModel::isSelectedNode(Component* node)
{
    return this->_selectedNode == node;
}

bool GUIPresentModel::isCreatedMindMap()
{
    return this->_presentModel->getRoot() != NULL;
}

bool GUIPresentModel::isCutNodeEnable()
{
    return this->isSelected() && this->_presentModel->getRoot() != _selectedNode;
}

bool GUIPresentModel::isCopyNodeEnable()
{
    return this->isCutNodeEnable();
}

bool GUIPresentModel::isPasteNodeEnable()
{
    return this->isSelected() && this->_prepareCloneNode != NULL;
}

Component* GUIPresentModel::getSelectedNode()
{
    return this->_selectedNode;
}

Component* GUIPresentModel::getRoot()
{
    return this->_presentModel->getRoot();
}

void GUIPresentModel::undo()
{
    this->cancelSelected();
    this->_presentModel->undo();
    this->notify(MODEL_CHANGE);
}

void GUIPresentModel::redo()
{
    this->cancelSelected();
    this->_presentModel->redo();
    this->notify(MODEL_CHANGE);
}

void GUIPresentModel::addDecorate(ComponentType type)
{
    if (this->_selectedNode)
    {
        this->_selectedNode->setIsSelected(false);
        this->_selectedNode = this->_model->addDecorate(type, this->_selectedNode);
        this->_selectedNode->setIsSelected(true);
        this->notify(MODEL_CHANGE);
    }
}

void GUIPresentModel::cleanAllDecorate()
{
}

bool GUIPresentModel::isUndoEnable()
{
    return this->_presentModel->canUndo();
}

bool GUIPresentModel::isRedoEnable()
{
    return this->_presentModel->canRedo();
}

void GUIPresentModel::rebuildPosition(IGraphic* painter)
{
    return this->_model->rebuildPosition(painter);
}

GUIPresentModel::~GUIPresentModel()
{
}