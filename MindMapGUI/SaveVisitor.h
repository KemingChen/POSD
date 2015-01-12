#pragma once
#include "NodeVisitor.h"
#include "Component.h"
#include "stdafx.h"
#include <string>
#include <map>

using namespace std;

class SaveVisitor : public NodeVisitor
{
    private:
        ofstream* _file;
        NodeList _nodeList;
        map<Component*, string> _nodeDecorateList;

        // Private Method
        void saveComponentDecorate(Component* node, string typeName);
        string getComponentDecorate(Component* node);
        string getEncodedDescription(Component* node);

    public:
        SaveVisitor(ofstream* file, Component* root);
        void visit(Root* node);
        void visit(Node* node);
        void visit(Decorate* node);
        void finish();
        ~SaveVisitor();
};