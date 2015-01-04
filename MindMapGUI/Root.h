#pragma once
#include "Component.h"
#include "Composite.h"
using namespace std;

class Root : public Composite
{
    public:
        // Public Method
        Root(int id, string description);
        Component* getBackFromNode();
        Component* getParent();
        Component* clone();
        string getTypeName();
        int getSide();
        void setSide(int side);
        void setParent(Component* node);
        void addParent(Component* node);
        void addSibling(Component* node);
        bool isSelfAreParentLastNode();
        void accept(NodeVisitor* visitor);
        ~Root();
};