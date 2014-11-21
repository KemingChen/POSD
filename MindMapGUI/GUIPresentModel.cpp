#include "GUIPresentModel.h"

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
    if (_selectedNode)
    {
        _selectedNode->setSelected(false);
        _selectedNode = NULL;
    }
    if (node)
    {
        node->setSelected(true);
        _selectedNode = node;
    }
    _notify->updateActions();
}

void GUIPresentModel::editDescription(string text, bool isValid)
{
    if (isValid)
    {
        if (!text.empty())
        {
            _selectedNode->getComponent()->setDescription(text);
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

bool GUIPresentModel::isMindMapCreated()
{
    return _presentModel->getRoot() != NULL;
}

bool GUIPresentModel::isSelectedNode()
{
    return _selectedNode != NULL;
}

GraphicNode* GUIPresentModel::getSelectedNode()
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
        result->push_back(graphicNode);
        (*levelYMap)[levelX]++;
        pushChildGraphics(result, graphicNode, graphicNode->getComponent()->getNodeList(), levelX + 1, levelYMap);
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
        result->push_back(graphicNode);
        pushChildGraphics(result, graphicNode, root->getNodeList(), levelX + 1 , &levelYMap);
    }
    return result;
}

GUIPresentModel::~GUIPresentModel()
{
}