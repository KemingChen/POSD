#include "GUIPresentModel.h"
#include "ComponentFactory.h"
#include <iostream>

#define MIN_DELTA_CLICK_TIME 20
#define ERROR_DESCRIPTION_EMPTY "Description is Empty!!!"

GUIPresentModel::GUIPresentModel(PresentModel* presentModel, INotifyGraphics* notify)
{
    _selectedNode = NULL;
    _lastClickTime = clock();
    _presentModel = presentModel;
    _notify = notify;
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

void GUIPresentModel::clickGraphicNode(GraphicNode* node)
{
    if (!isValidClick())
        return;

    _selectedNode = node ? node->getComponent() : NULL;
    _notify->updateActions();
    _notify->updateGraphics();
}

void GUIPresentModel::editDescription(string text, bool isValid)
{
    if (isValid)
    {
        if (!text.empty())
        {
            _selectedNode->setDescription(text);
            _notify->updateGraphics();
        }
        else
        {
            _notify->notifyError(ERROR_DESCRIPTION_EMPTY);
        }
    }
}

void GUIPresentModel::loadMindMap(string path)
{
    if (!path.empty())
    {
        _presentModel->loadMindMap(path);
        _notify->updateGraphics();
        _notify->updateActions();
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
            _notify->updateActions();
            _notify->updateGraphics();
        }
        else
        {
            _notify->notifyError(ERROR_DESCRIPTION_EMPTY);
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
            _notify->updateGraphics();
        }
        else
        {
            _notify->notifyError(ERROR_DESCRIPTION_EMPTY);
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
            _notify->updateGraphics();
        }
        else
        {
            _notify->notifyError(ERROR_DESCRIPTION_EMPTY);
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
            _notify->updateGraphics();
        }
        else
        {
            _notify->notifyError(ERROR_DESCRIPTION_EMPTY);
        }
    }
}

bool GUIPresentModel::isSaveEnable()
{
    return _presentModel->getRoot() != NULL;
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
    _notify->updateActions();
    _notify->updateGraphics();
}

bool GUIPresentModel::isSelectedNode(Component* node)
{
    return _selectedNode == node;
}

Component* GUIPresentModel::getSelectedNode()
{
    return _selectedNode;
}

void GUIPresentModel::pushChildGraphics(list<GraphicNode*>* result, GraphicNode* parent, NodeList* nodeList, int levelX, map<int, int>* levelYMap)
{
    if (!(*levelYMap)[levelX])
        (*levelYMap)[levelX] = 0;

    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        GraphicNode* graphicNode = new GraphicNode(levelX, (*levelYMap)[levelX], *iNode, _notify, parent->getConnectPoint());
        graphicNode->setSelected(isSelectedNode(*iNode));
        result->push_back(graphicNode);
        (*levelYMap)[levelX] += 1;
        pushChildGraphics(result, graphicNode, graphicNode->getComponent()->getNodeList(), levelX + 1, levelYMap);
        if ((*levelYMap)[levelX + 1] > (*levelYMap)[levelX])
        {
            (*levelYMap)[levelX] = (*levelYMap)[levelX + 1];
        }
    }
}

list<GraphicNode*>* GUIPresentModel::getGraphicsList()
{
    list<GraphicNode*>* result = new list<GraphicNode*>();
    Component* root = _presentModel->getRoot();
    if (root != NULL)
    {
        int levelX = 0;
        map<int, int> levelYMap;
        levelYMap[levelX] = 0;
        GraphicNode* graphicNode = new GraphicNode(levelX, levelYMap[levelX], root, _notify);
        graphicNode->setSelected(isSelectedNode(root));
        result->push_back(graphicNode);
        pushChildGraphics(result, graphicNode, root->getNodeList(), levelX + 1 , &levelYMap);
    }
    return result;
}

GUIPresentModel::~GUIPresentModel()
{
}