#include "SaveVisitor.h"
#include <fstream>
#include <algorithm>

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

}

void SaveVisitor::finish()
{
    int newId = 0;
    Component* node;
    std::sort(this->_nodeList.begin(), this->_nodeList.end(), CompareComponent());
    for (NodeList::iterator iNode = this->_nodeList.begin(); iNode != this->_nodeList.end(); iNode++)
    {
        (*iNode)->setId(newId);
        newId++;
    }
    for (NodeList::iterator iNode = this->_nodeList.begin(); iNode != this->_nodeList.end(); iNode++)
    {
        node = *iNode;
        string output = "";
        (*this->_file) << node->getId() << " ";
        (*this->_file) << "\"" << node->getDescription() << "\"";
        (*this->_file) << node->getMap() << endl;
        newId++;
    }
}

SaveVisitor::~SaveVisitor()
{
}