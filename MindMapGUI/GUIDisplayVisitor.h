#pragma once
#include "NodeVisitor.h"

class GUIDisplayVisitor : public NodeVisitor
{
    public:
        GUIDisplayVisitor();
        void visit(Root* node);
        void visit(Node* node);
        ~GUIDisplayVisitor();
};