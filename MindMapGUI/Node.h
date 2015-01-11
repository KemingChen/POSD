#pragma once
#include "Component.h"
#include "Composite.h"
using namespace std;

class Node : public Composite
{
    private:
        Component* _parentNode;

    public:
        // Public Method
        Node(int id, string description);
        //Component* getBackFromNode();
        Component* getParent();
        Component* clone();
        string getTypeName();
        void setParent(Component* node);
        void addChild(Component* node, Component* backFromNode = NULL, int side = NONE);
        void addParent(Component* node);
        void addSibling(Component* node);
        bool isSelfAreParentLastNode();
        void accept(NodeVisitor* visitor);
        void draw(IGraphic* painter);
        ~Node();
};