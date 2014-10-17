#include "stdafx.h"
#include "MindMapModel.h"
#include "ComponentFactory.h"
#include <iostream>

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

// 將從 Database 讀到的一行，分解成 id, description, childrenIds 的 string array
void MindMapModel::splitMindMapLine(string line)
{
    //string* array = new string[] {"123", "234", "345"};
    cout << line << endl;
    string quot = "\"";
    int startQuot = line.find_first_of(quot);
    int endQuot = line.find_last_of(quot);
    string id = "";
    string description = "";
    string childrenIds = "";
    //string id = true ? "" : line.substr(0, startQuot);
    //string description = true ? "" : line.substr(startQuot + 1, endQuot - startQuot);
    //string childrenIds = "";
    //if (endQuot /*+ 1 != line.size())
    //{
    //    line.substr(endQuot + 2, line.size() - endQuot - 2);
    //}*/
    cout << id << description << childrenIds << endl;
}

void MindMapModel::loadMindMap(ifstream* file)
{
    string line;
    while (getline(*file, line))
    {
        cout << "size: " << line.size() << endl;
        splitMindMapLine(line);
        //cout << data[0] << ", " << data[1] << ", " << data[2] << endl;
    }
}

void MindMapModel::editNodeDescription(Component* node, string description)
{
    node->setDescription(description);
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