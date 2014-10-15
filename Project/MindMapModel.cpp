#include "stdafx.h"
#include "MindMapModel.h"
#include <iostream>
#include <fstream>

MindMapModel::MindMapModel()
{
    _insertActionMap["a"] = &MindMapModel::insertParentNode;
    _insertActionMap["b"] = &MindMapModel::insertChildNode;
    _insertActionMap["c"] = &MindMapModel::insertSiblingNode;
}

void MindMapModel::createMinMap(string description)
{
    _createId = 0;
    _root = new Root(_createId);
    _createId++;
    _root->setDescription(description);
}

Component* MindMapModel::getRootNode()
{
    return _root;
}

void MindMapModel::insertParentNode(Component* node, Component* newNode)
{
    node->addParent(newNode);
}

void MindMapModel::insertChildNode(Component* node, Component* newNode)
{
    node->addChild(newNode);
}

void MindMapModel::insertSiblingNode(Component* node, Component* newNode)
{
    node->addSibling(newNode);
}

Component* MindMapModel::findNode(Component* node, string id)
{
    Component* foundNode = NULL;
    NodeList* nodeList = node->getNodeList();
    if (node->getId() == id)
    {
        return node;
    }
    for (NodeList::iterator it = nodeList->begin(); it != nodeList->end(); it++)
    {
        if (foundNode != NULL)
        {
            break;
        }
        if (node->getId() == id)
        {
            foundNode = *it;
            break;
        }
        foundNode = findNode(*it, id);
    }
    return foundNode;
}

Component* MindMapModel::insertNode(string id, string action)
{
    Component* node = findNode(_root, id);
    Component* newNode = new Node(_createId);
    if (_insertActionMap[action])
    {
        (this->*_insertActionMap[action])(node, newNode);
        _createId++;
    }
    else
    {
        throw string("Unknown Action: " + action);
    }
    return newNode;
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
    int nodeCount = _createId;
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