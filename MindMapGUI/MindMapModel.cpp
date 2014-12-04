#include "MindMapModel.h"
#include "ComponentFactory.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

MindMapModel::MindMapModel()
{
    _root = NULL;
}

void MindMapModel::createMinMap(string description)
{
    _root = ComponentFactory::getInstance()->createComponent(ROOT, description);
}

Component* MindMapModel::getRootNode()
{
    return _root;
}

void MindMapModel::insertParentNode(Component* choseNode, Component* newNode)
{
    choseNode->addParent(newNode);
}

void MindMapModel::revertInsertParentNode(Component* choseNode, Component* newNode, Component* oldParentNode)
{
    newNode->removeChild(choseNode);
    oldParentNode->removeChild(newNode);
    oldParentNode->addChild(choseNode);
}

void MindMapModel::insertChildNode(Component* choseNode, Component* newNode)
{
    choseNode->addChild(newNode);
}

void MindMapModel::insertSiblingNode(Component* choseNode, Component* newNode)
{
    choseNode->addSibling(newNode);
}

Component* MindMapModel::findNode(string id)
{
    if (_root == NULL)
    {
        throw string("The Root is Empty!!!");
    }
    return findNode(_root, id);
}

Component* MindMapModel::findNode(Component* fromNode, string id)
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

void MindMapModel::navigateMindMap(Component* node, NodeList* list)
{
    list->push_back(node);
    NodeList* nodeList = node->getNodeList();
    for (NodeList::iterator it = nodeList->begin(); it != nodeList->end(); it++)
    {
        navigateMindMap(*it, list);
    }
}

void MindMapModel::saveMindMap(ofstream* file)
{
    NodeList nodeList;
    if (_root == NULL)
    {
        return;
    }
    navigateMindMap(_root, &nodeList);
    std::sort(nodeList.begin(), nodeList.end(), CompareComponent());
    int newId = 0;
    Component* node;
    for (NodeList::iterator iNode = nodeList.begin(); iNode != nodeList.end(); iNode++)
    {
        (*iNode)->setId(newId);
        newId++;

    }
    for (NodeList::iterator iNode = nodeList.begin(); iNode != nodeList.end(); iNode++)
    {
        node = *iNode;
        string output = "";
        (*file) << node->getId() << " ";
        (*file) << "\"" << node->getDescription() << "\"";
        (*file) << node->getMap() << endl;
        newId++;
    }
}

void MindMapModel::loadMindMap(ifstream* file)
{
    ComponentFactory* componentFactory = ComponentFactory::getInstance();
    string line;
    vector<Component*> componentList;
    vector<string> nodeIdsList;
    while (getline(*file, line))
    {
        int firstQuot = line.find_first_of("\"");
        int secondQuot = line.find_last_of("\"");
        string description = line.substr(firstQuot + 1, secondQuot - firstQuot - 1);
        string nodeIds = line.substr(secondQuot + 1, line.size());
        Component* node = componentFactory->createComponent(componentList.size() == 0 ? ROOT : NODE, description);
        componentList.push_back(node);
        nodeIdsList.push_back(nodeIds);
    }
    vector<string>::iterator iNodeIds = nodeIdsList.begin();
    for (vector<Component*>::iterator iNode = componentList.begin(); iNode != componentList.end(); iNode++)
    {
        stringstream ssin(*iNodeIds);
        int id;
        while (ssin >> id)
        {
            (*iNode)->addChild(componentList[id]);
        }
        iNodeIds++;
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
        parentNode->addChild(*iNode);
    }
    parentNode->removeChild(choseNode);
}

void MindMapModel::revertDeleteNode(Component* choseNode)
{
    NodeList* nodeList = choseNode->getNodeList();
    Component* parentNode = choseNode->getParent();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        parentNode->removeChild(*iNode);
    }
    parentNode->addChild(choseNode);
}

void MindMapModel::cutNode(Component* node)
{
    if (node != getRootNode())
    {
        this->copyNode(node);
        node->getParent()->removeChild(node);
    }
}

void MindMapModel::copyNode(Component* node)
{
    _prepareCloneNode = node;
}

void MindMapModel::pasteNode(Component* selectedNode)
{
    if (_prepareCloneNode != NULL && selectedNode != NULL)
    {
        selectedNode->addChild(_prepareCloneNode->clone());
    }
}

MindMapModel::~MindMapModel()
{
}