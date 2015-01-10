#pragma once

class Root;
class Node;
class Decorate;
class NodeVisitor
{
    public:
        virtual void visit(Root* node) = 0;
        virtual void visit(Node* node) = 0;
        virtual void visit(Decorate* node) = 0;
};