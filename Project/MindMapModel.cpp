#include "stdafx.h"
#include "MindMapModel.h"
#include "ComponentFactory.h"
#include <iostream>
#include <fstream>

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

void MindMapModel::saveMindMap(string path)
{
    int nodeCount = ComponentFactory::getInstance()->getCreatedCount();
    string* list = new string[nodeCount];
    navigateMindMap(_root, list);
    ofstream myfile(path);
    for (int i = 0; i < nodeCount; i++)
    {
        myfile << list[i] << endl;
    }
    myfile.close();
}

void MindMapModel::loadMindMap(string path)
{
    string line;
    ifstream myfile(path);
    while (getline(myfile, line))
    {
        cout << line << endl;
    }
    myfile.close();
}

MindMapModel::~MindMapModel()
{
}