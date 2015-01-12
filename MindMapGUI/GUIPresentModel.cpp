#include "GUIPresentModel.h"
#include "ComponentFactory.h"
#include <iostream>

#define MIN_DELTA_CLICK_TIME 20

GUIPresentModel::GUIPresentModel(PresentModel* presentModel, MindMapModel* model)
{
    this->_prepareCloneNode = NULL;
    this->_selectedNodeId = NO_SELECTED;
    this->_lastClickTime = -1000;
    this->_presentModel = presentModel;
    this->_model = model;
    this->_commandManager = this->_presentModel->getCommandManager();
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
    this->_selectedNodeId = NO_SELECTED;
}

void GUIPresentModel::clickGraphicNode(int id)
{
    if (!isValidClick())
        return;
    this->cancelSelected();
    this->_selectedNodeId = id;
    this->notify(SELECTED_CHANGE);
}

void GUIPresentModel::editDescription(string text, bool isValid)
{
    if (this->isValidText(isValid, text) && this->isSelected())
    {
        this->_presentModel->editNodeDescription(this->getSelectedNode(), text);
        this->notify(MODEL_CHANGE);
    }
}

void GUIPresentModel::loadMindMap(string path)
{
    if (this->isValidText(true, path))
    {
        this->_selectedNodeId = NO_SELECTED;
        this->_presentModel->loadMindMap(path);
        this->notify(CREATE_NEW);
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
        this->_selectedNodeId = NO_SELECTED;
        this->_presentModel->createMindMap(text);
        this->notify(CREATE_NEW);
    }
}

void GUIPresentModel::insertParentNode(string text, bool isValid)
{
    if (this->isValidText(isValid, text))
    {
        this->_presentModel->insertParentNode(this->getSelectedNode(), text);
        this->notify(MODEL_CHANGE);
    }
}

void GUIPresentModel::insertChildNode(string text, bool isValid)
{
    if (this->isValidText(isValid, text))
    {
        this->_presentModel->insertChildNode(this->getSelectedNode(), text);
        this->notify(MODEL_CHANGE);
    }
}

void GUIPresentModel::insertSiblingNode(string text, bool isValid)
{
    if (this->isValidText(isValid, text))
    {
        this->_presentModel->insertSiblingNode(this->getSelectedNode(), text);
        this->notify(MODEL_CHANGE);
    }
}

bool GUIPresentModel::isSaveEnable()
{
    return this->isCreatedMindMap();
}

bool GUIPresentModel::isSelected()
{
    return this->_selectedNodeId != NO_SELECTED;
}

bool GUIPresentModel::isDeleteNodeEnable()
{
    return this->isSelected() && _presentModel->getRoot() != this->getSelectedNode();
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
            this->_presentModel->confirmInsertNodeLegal(this->getSelectedNode(), insertMethod);
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
    this->_presentModel->deleteNode(this->getSelectedNode());
    this->cancelSelected();
    this->notify(MODEL_CHANGE);
}

void GUIPresentModel::cutNode()
{
    this->_prepareCloneNode = this->getSelectedNode();
    this->_presentModel->cutNode(this->_prepareCloneNode);
    this->cancelSelected();
    this->notify(MODEL_CHANGE);
}

void GUIPresentModel::copyNode()
{
    this->_prepareCloneNode = this->getSelectedNode()->clone();
    this->notify(SELECTED_CHANGE);
}

void GUIPresentModel::pasteNode()
{
    this->_presentModel->pasteNode(this->getSelectedNode(), this->_prepareCloneNode);
    this->notify(MODEL_CHANGE);
}

bool GUIPresentModel::isSelectedNode(int id)
{
    return this->_selectedNodeId == id;
}

bool GUIPresentModel::isCreatedMindMap()
{
    return this->_presentModel->getRoot() != NULL;
}

bool GUIPresentModel::isCutNodeEnable()
{
    return this->isSelected() && this->_presentModel->getRoot() != this->getSelectedNode();
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
    return this->_model->findNode(this->_selectedNodeId);
}

Component* GUIPresentModel::getRoot()
{
    return this->_presentModel->getRoot();
}

Component* GUIPresentModel::tryFindNode(int id)
{
    return this->_model->findNode(id);
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
    if (this->isSelected())
    {
        Command* command = new AddDecorateCommnad(_model, this->getSelectedNode(), type);
        this->_commandManager->execute(command);
        this->notify(MODEL_CHANGE);
    }
}

void GUIPresentModel::cleanAllDecorate()
{
    if (this->isSelected())
    {
        Command* command = new CleanAllDecorateCommand(_model, this->getSelectedNode());
        this->_commandManager->execute(command);
        this->notify(MODEL_CHANGE);
    }
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

void GUIPresentModel::collapseAll()
{
    this->_model->collapseAll(this->getSelectedNode());
    this->notify(MODEL_CHANGE);
}

void GUIPresentModel::expandAll()
{
    this->_model->expandAll(this->getSelectedNode());
    this->notify(MODEL_CHANGE);
}

void GUIPresentModel::expandOneLevel()
{
    this->_model->expandOneLevel(this->getSelectedNode());
    this->notify(MODEL_CHANGE);
}

void GUIPresentModel::moveUp()
{
    Component* choseNode = this->getSelectedNode();
    Component* targetNode = this->_model->findSideUpNode(choseNode);
    targetNode = this->_model->findSideUpNode(targetNode);
    this->_model->moveToBack(choseNode, targetNode);
    this->notify(MODEL_CHANGE);
}

void GUIPresentModel::moveDown()
{
    Component* choseNode = this->getSelectedNode();
    Component* targetNode = this->_model->findSideDownNode(choseNode);
    this->_model->moveToBack(choseNode, targetNode);
    this->notify(MODEL_CHANGE);
}

GUIPresentModel::~GUIPresentModel()
{
}