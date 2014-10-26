#pragma once
using namespace std;

class Composite : public Component
{
    protected:
        // Protected Variable
        NodeList _nodeList;

    public:
        // Public Method
        Composite(int id);
        string getMap();
        void addChild(Component* node);
        void removeChild(Component* node);
        void removeAllChild();
        void addParent(Component* node) = 0;
        void addSibling(Component* node) = 0;
        bool isSelfAreParentLastNode() = 0;
        NodeList* getNodeList();
        ~Composite();
};