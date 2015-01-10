#pragma once
#include "NodeVisitor.h"

class SaveVisitor : public NodeVisitor
{
    public:
        SaveVisitor();
        void visit(Root* node);
        void visit(Node* node);
        void visit(Decorate* node);
        ~SaveVisitor();
};