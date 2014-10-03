#pragma once
using namespace std;

class Composite :
    public Component
{
    protected:
        // Protected Variable
        NodeList* _nodeList;

    public:
        // Public Method
        Composite();
        void addChild(Component* node);
        void removeChild(Component* node);
        void addParent(Component* node) = 0;
        void addSibling(Component* node) = 0;
        NodeList* getNodeList();
        ~Composite();
};