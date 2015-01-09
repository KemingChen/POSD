#pragma once
#include "Component.h"
using namespace std;

class Composite : public Component
{
    private:
        // Protected Variable
        NodeList _nodeList;

    public:
        // Public Method
        Composite(int id, string description);
        string getMap();
        int childIndexOf(Component* node);
        void removeChild(Component* node);
        void removeAllChild();
        NodeList* getNodeList();
        ~Composite();

        // Virtual Method
        Component* getBackFromNode() = 0;
        string getTypeName() = 0;
        Component* clone() = 0;
        Component* getParent() = 0;
        void setParent(Component* node) = 0;
        void addChild(Component* node, Component* backFromNode = NULL, int side = NONE) = 0;
        void addParent(Component* node) = 0;
        void addSibling(Component* node) = 0;
        bool isSelfAreParentLastNode() = 0;
        void accept(NodeVisitor* visitor) = 0;
        void draw(IGraphic* painter) = 0;
};