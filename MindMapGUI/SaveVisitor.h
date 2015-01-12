#pragma once
#include "NodeVisitor.h"
#include "Component.h"
#include "stdafx.h"
#include <string>

using namespace std;

class SaveVisitor : public NodeVisitor
{
    private:
        ofstream* _file;
        NodeList _nodeList;

    public:
        SaveVisitor(ofstream* file, Component* root);
        void visit(Root* node);
        void visit(Node* node);
        void visit(Decorate* node);
        void finish();
        ~SaveVisitor();
};