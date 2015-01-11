#pragma once
#include "Component.h"

class Decorate : public Component
{
    protected:
        Component* _node;

    public:
        Decorate(int id, Component* node);
        string getMap();
        void setPosition(int x, int y);
        void setRectSize(int width, int height);
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
        Component* getRealComponent();
        Component* getOriginalComponent();
        ~Decorate();

        // Virtual
        Component* clone() = 0;
        string getTypeName() = 0;
        void draw(IGraphic* painter) = 0;
};