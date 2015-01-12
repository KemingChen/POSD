#include "SaveVisitor.h"
#include "Decorate.h"
#include "Root.h"
#include "Node.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>

SaveVisitor::SaveVisitor(ofstream* file, Component* root)
{
    this->_file = file;
    if (root)
    {
        root = root->clone();
        root->accept(this);
        this->finish();
    }
}

void SaveVisitor::saveComponentDecorate(Component* node, string typeName)
{
    this->_nodeDecorateList[node] += SPLITE + typeName;
}

string SaveVisitor::getComponentDecorate(Component* node)
{
    return this->_nodeDecorateList[node];
}

string SaveVisitor::getEncodedDescription(Component* node)
{
    return regex_replace(node->getDescription(), regex(SPACE), ENCODED_SPACE);
}

void SaveVisitor::visit(Root* node)
{
    this->_nodeList.push_back((Component*)node);
}

void SaveVisitor::visit(Node* node)
{
    this->_nodeList.push_back((Component*)node);
}

void SaveVisitor::visit(Decorate* node)
{
    this->saveComponentDecorate(node->getRealComponent(), node->getTypeName());
}

void SaveVisitor::finish()
{
    int newId = 0;
    std::sort(this->_nodeList.begin(), this->_nodeList.end(), CompareComponent());
    for (NodeList::iterator iNode = this->_nodeList.begin(); iNode != this->_nodeList.end(); iNode++)
    {
        (*iNode)->setId(newId);
        newId++;
    }
    for (NodeList::iterator iNode = this->_nodeList.begin(); iNode != this->_nodeList.end(); iNode++)
    {
        Component* node = *iNode;
        (*this->_file) << to_string(node->getId()) << SPACE;
        (*this->_file) << to_string(node->getSide()) << SPACE;
        (*this->_file) << this->getEncodedDescription(node) << SPACE;
        (*this->_file) << SPLITE << node->getMap() << SPLITE << SPACE;
        (*this->_file) << SPLITE << this->getComponentDecorate(node) << SPLITE << endl;
    }
}

SaveVisitor::~SaveVisitor()
{
}