#include "stdafx.h"
#include "MindMapModel.h"
#include "ComponentFactory.h"
#include <iostream>
#include <sstream>
#include <vector>

MindMapModel::MindMapModel()
{
}

void MindMapModel::createMinMap(string description)
{
    _root = ComponentFactory::getInstance()->createComponent(ROOT);
    _root->setDescription(description);
}

Component* MindMapModel::getRootNode()
{
    return _root;
}

void MindMapModel::insertParentNode(Component* choseNode, Component* newNode)
{
    choseNode->addParent(newNode);
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

Component* MindMapModel::findNode(Component* node, string id)
{
    Component* foundNode = NULL;
    NodeList* nodeList = node->getNodeList();
    if (node->getId() == id)
    {
        return node;
    }
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        if (foundNode != NULL)
        {
            return foundNode;
        }
        if (node->getId() == id)
        {
            return *iNode;
        }
        foundNode = findNode(*iNode, id);
    }
    return foundNode;
}

string MindMapModel::convertIntArrayToString(list<int>* intList)
{
    string returnstring = "";
    for (list<int>::iterator it = intList->begin(); it != intList->end(); it++)
    {
        returnstring += " " + to_string(*it);
    }
    return returnstring;
}

void MindMapModel::navigateMindMap(Component* node, string* list)
{
    int id = atoi(node->getId().c_str());
    string output = "";
    NodeList* nodeList = node->getNodeList();
    output += node->getId() + " ";
    output += "\"" + node->getDescription() + "\"";
    output += convertIntArrayToString(node->getMap());
    list[id] = output;
    for (NodeList::iterator it = nodeList->begin(); it != nodeList->end(); it++)
    {
        navigateMindMap(*it, list);
    }
}

void MindMapModel::saveMindMap(ofstream* file)
{
    int nodeCount = ComponentFactory::getInstance()->getCreatedCount();
    string* list = new string[nodeCount];
    if (_root == NULL)
    {
        return;
    }
    navigateMindMap(_root, list);
    for (int i = 0; i < nodeCount; i++)
    {
        (*file) << list[i] << endl;
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
        Component* node = componentFactory->createComponent(componentList.size() == 0 ? ROOT : NODE);
        node->setDescription(description);
        componentList.push_back(node);
        nodeIdsList.push_back(nodeIds);
    }
    for (int i = 0; i < componentList.size(); i++)
    {
        Component* node = componentList[i];
        stringstream ssin(nodeIdsList[i]);
        int id;
        while (ssin >> id)
        {
            node->addChild(componentList[id]);
        }
    }
    _root = componentList[0];
}

void MindMapModel::editNodeDescription(Component* node, string description)
{
    node->setDescription(description);
}

void MindMapModel::changeNodeParent(Component* node, Component* newParentNode)
{
    // Node's Children Not Contain New Parent Node
    if (findNode(node, newParentNode->getId()) == NULL)
    {
        node->getParent()->removeChild(node);
        newParentNode->addChild(node);
    }
    // Node's Children Contain New Parent Node
    else
    {
        Component* oldParent = node->getParent();
        NodeList* nodeList = node->getNodeList();
        for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
        {
            oldParent->addChild(*iNode);
        }
        oldParent->removeChild(node);
        node->removeAllChild();
        newParentNode->addChild(node);
    }
}

void MindMapModel::deleteNode(Component* node)
{
    Component* parentNode = node->getParent();
    NodeList* nodeList = node->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        parentNode->addChild(*iNode);
    }
    parentNode->removeChild(node);
}

MindMapModel::~MindMapModel()
{
}