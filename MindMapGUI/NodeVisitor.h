#pragma once

class Root;
class Node;
class NodeVisitor
{
    public:
        virtual void visit(Root* node) = 0;
        virtual void visit(Node* node) = 0;
};