#pragma once
using namespace std;

class Component
{
    protected:
        // Protected Variable
        NodeMap* _node;
        Component* _parentNode;

    public:
        typedef list<Component*> NodeList;

        // Public Method
        Component(int id);
        string getId();
        NodeMap* getMap();
        string getDescription();
        void setDescription(string description);
        void setParent(Component* node);
        virtual void addChild(Component* node) = 0;
        virtual void removeChild(Component* node) = 0;
        virtual void addParent(Component* node) = 0;
        virtual void addSibling(Component* node) = 0;
        virtual bool isSelfAreParentLastNode() = 0;
        virtual NodeList* getNodeList() = 0;
        virtual ~Component();
};