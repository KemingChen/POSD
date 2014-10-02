#pragma once
using namespace std;

class Component
{
    protected:
        // Protected Variable
        NodeMap* _node;

    public:
        typedef list<Component*> NodeList;

        // Public Method
        Component();
        int getId();
        NodeMap* getMap();
        string getDescription();
        void setDescription(string description);
        virtual void addChild(Component* node) = 0;
        virtual void addParent(Component* node) = 0;
        virtual void addSibling(Component* node) = 0;
        virtual NodeList* getNodeList() = 0;
        virtual ~Component();
};