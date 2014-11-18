#pragma once
using namespace std;

class Component
{
    private:
        string _id;
        string _description;

    protected:
        // Protected Variable
        string _typeName;

    public:
        typedef list<Component*> NodeList;

        // Public Method
        Component(int id, string description);
        string getId();
        void setId(int id);
        string getTypeName();
        string getDescription();
        void setDescription(string description);
        string toString();
        virtual string getMap() = 0;
        virtual void addChild(Component* node) = 0;
        virtual void removeChild(Component* node) = 0;
        virtual void removeAllChild() = 0;
        virtual Component* getParent() = 0;
        virtual void setParent(Component* node) = 0;
        virtual void addParent(Component* node) = 0;
        virtual void addSibling(Component* node) = 0;
        virtual bool isSelfAreParentLastNode() = 0;
        virtual NodeList* getNodeList() = 0;
        virtual ~Component();
};