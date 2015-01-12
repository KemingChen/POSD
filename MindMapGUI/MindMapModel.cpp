#include "MindMapModel.h"
#include "ComponentFactory.h"
#include "GUIDisplayVisitor.h"
#include "SaveVisitor.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <regex>

MindMapModel::MindMapModel()
{
    _root = NULL;
}

void MindMapModel::createMinMap(string description)
{
    _root = ComponentFactory::getInstance()->createComponent(ComponentType::ROOT, description);
}

Component* MindMapModel::getRootNode()
{
    return _root;
}

void MindMapModel::insertParentNode(Component* choseNode, Component* newNode)
{
    choseNode->addParent(newNode);
}

void MindMapModel::revertInsertParentNode(Component* choseNode, Component* newNode, Component* oldParentNode, Component* backFromNode)
{
    newNode->removeChild(choseNode);
    oldParentNode->removeChild(newNode);
    oldParentNode->addChild(choseNode, backFromNode);
}

void MindMapModel::insertChildNode(Component* choseNode, Component* newNode)
{
    choseNode->addChild(newNode);
}

void MindMapModel::insertSiblingNode(Component* choseNode, Component* newNode)
{
    choseNode->addSibling(newNode);
}

void MindMapModel::addDecorate(Component* decorateNode, Component* originalNode)
{
    Component* parent = originalNode->getParent();
    if (parent)
    {
        parent->addChild(decorateNode, originalNode->getBackFromNode(), originalNode->getSide());
        parent->removeChild(originalNode);
    }
    else
    {
        this->_root = decorateNode;
    }
}

void MindMapModel::removeDecorate(Component* originalNode)
{
    Component* parent = originalNode->getParent();
    Component* decorateNode = this->findNode(originalNode->getId());
    if (parent)
    {
        parent->addChild(originalNode, decorateNode->getBackFromNode(), decorateNode->getSide());
        parent->removeChild(decorateNode);
    }
    else
    {
        this->_root = originalNode;
    }
}

Component* MindMapModel::findNode(int id)
{
    if (_root == NULL)
    {
        throw string("The Root is Empty!!!");
    }
    if (id == NO_SELECTED)
    {
        return NULL;
    }
    return findNode(_root, id);
}

Component* MindMapModel::findNode(Component* fromNode, int id)
{
    Component* foundNode = NULL;
    NodeList* nodeList = fromNode->getNodeList();
    if (fromNode->getId() == id)
    {
        return fromNode;
    }
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        if (foundNode != NULL)
        {
            return foundNode;
        }
        if (fromNode->getId() == id)
        {
            return *iNode;
        }
        foundNode = findNode(*iNode, id);
    }
    return foundNode;
}

void MindMapModel::saveMindMap(ofstream* file)
{
    SaveVisitor saveVisitor(file, this->_root);
}

void MindMapModel::loadMindMap(ifstream* file)
{
    ComponentFactory* componentFactory = ComponentFactory::getInstance();
    vector<Component*> componentList;
    vector<string> nodeIdsList;
    vector<int> nodeSideList;

    string line;
    int id;
    int side;
    string description;
    string decorate;
    string nodeList;
    string decorateList;
    while (getline(*file, line))
    {
        description = nodeList = decorateList = "";
        stringstream ssin(line);

        ssin >> id;
        ssin >> side;
        ssin >> description;
        ssin >> nodeList;
        ssin >> decorateList;

        // adjust
        description = regex_replace(description, regex(ENCODED_SPACE), SPACE);
        nodeList = regex_replace(nodeList, regex(SPLITE), SPACE);
        decorateList = regex_replace(decorateList, regex(SPLITE), SPACE);

        ComponentType type = componentList.size() == 0 ? ComponentType::ROOT : ComponentType::NODE;
        Component* node = componentFactory->createComponent(type, description);
        stringstream ssDecorateIn(decorateList);
        while (ssDecorateIn >> decorate)
        {
            node = componentFactory->createDecorate(decorate, node);
        }

        componentList.push_back(node);
        nodeSideList.push_back(side);
        nodeIdsList.push_back(nodeList);
    }

    vector<string>::iterator iNodeIds = nodeIdsList.begin();
    for (vector<Component*>::iterator iNode = componentList.begin(); iNode != componentList.end(); iNode++, iNodeIds++)
    {
        int id;
        stringstream ssin(*iNodeIds);
        while (ssin >> id)
        {
            (*iNode)->addChild(componentList[id], NULL, nodeSideList[id]);
        }
    }
    _root = componentList[0];
}

void MindMapModel::editNodeDescription(Component* choseNode, string description)
{
    choseNode->setDescription(description);
}

void MindMapModel::changeNodeParent(Component* choseNode, Component* newParentNode)
{
    // Node's Children Not Contain New Parent Node
    if (findNode(choseNode, newParentNode->getId()) == NULL)
    {
        choseNode->getParent()->removeChild(choseNode);
        newParentNode->addChild(choseNode);
    }
    // Node's Children Contain New Parent Node
    else
    {
        Component* oldParent = choseNode->getParent();
        NodeList* nodeList = choseNode->getNodeList();
        for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
        {
            oldParent->addChild(*iNode);
        }
        oldParent->removeChild(choseNode);
        choseNode->removeAllChild();
        newParentNode->addChild(choseNode);
    }
}

void MindMapModel::revertChangeNodeParent(Component* choseNode, Component* oldParentNode, NodeList* oldNodeList)
{
    changeNodeParent(choseNode, oldParentNode);
    for (NodeList::iterator iNode = oldNodeList->begin(); iNode != oldNodeList->end(); iNode++)
    {
        oldParentNode->removeChild(*iNode);
        choseNode->addChild(*iNode);
    }
}

void MindMapModel::deleteNode(Component* choseNode)
{
    Component* parentNode = choseNode->getParent();
    NodeList* nodeList = choseNode->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        Component* backFromNode = iNode == nodeList->begin() ? choseNode : *(iNode - 1);
        parentNode->addChild(*iNode, backFromNode);
    }
    parentNode->removeChild(choseNode);
}

void MindMapModel::revertDeleteNode(Component* choseNode, Component* backFromNode)
{
    NodeList* nodeList = choseNode->getNodeList();
    Component* parentNode = choseNode->getParent();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        parentNode->removeChild(*iNode);
        (*iNode)->setParent(choseNode);
    }
    parentNode->addChild(choseNode, backFromNode);
}

void MindMapModel::cutNode(Component* selectedNode)
{
    if (selectedNode != NULL)
    {
        selectedNode->getParent()->removeChild(selectedNode);
    }
}

void MindMapModel::pasteNode(Component* selectedNode, Component* cloneNode)
{
    if (cloneNode != NULL && selectedNode != NULL)
    {
        selectedNode->addChild(cloneNode);
    }
}

void MindMapModel::rebuildPosition(IGraphic* painter)
{
    GUIDisplayVisitor guiDisplayVisitor(painter, _root);
}

void MindMapModel::collapseAll(Component* choseNode)
{
    choseNode->setCollapse(true, true);
    choseNode->setCollapse(false, false);
}

void MindMapModel::expandAll(Component* choseNode)
{
    choseNode->setCollapse(false, true);
}

void MindMapModel::expandOneLevel(Component* choseNode)
{
    NodeList* nodeList = choseNode->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        (*iNode)->setCollapse(false, false);
    }
}

MindMapModel::~MindMapModel()
{
    if (_root)
        delete _root;
}