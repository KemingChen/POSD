#pragma once
#include "Component.h"

class Decorate : public Component
{
    protected:
        Component* _node;

    public:
        Decorate(int id, Component* node);
        Component* getBackFromNode();
        string getMap();
        void addChild(Component* node, Component* backFromNode = NULL, int side = NONE);
        void removeChild(Component* node);
        void removeAllChild();
        Component* getParent();
        void setParent(Component* node);
        void addParent(Component* node);
        void addSibling(Component* node);
        bool isSelfAreParentLastNode();
        NodeList* getNodeList();
        void accept(NodeVisitor* visitor);
        ~Decorate();

        // Virtual
        Component* clone() = 0;
        string getTypeName() = 0;
        void draw(IGraphic* painter) = 0;
};