#pragma once
using namespace std;
#include <vector>
#define ROOT 0
#define NODE 1

class Component
{
    private:
        string _id;
        string _description;
        bool _isSelected;

    public:
        typedef vector<Component*> NodeList;

        // Public Method
        Component(int id, string description);
        string getId();
        void setId(int id);
        string getDescription();
        void setDescription(string description);
        string toString();
        bool getIsSelected();
        void setIsSelected(bool value);
        virtual string getTypeName() = 0;
        virtual Component* clone() = 0;
        virtual string getMap() = 0;
        virtual void addChild(Component* node, Component* backFromNode = NULL) = 0;
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