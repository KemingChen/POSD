#pragma once
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
        void setParent(Component* node);
        void addParent(Component* node);
        void addSibling(Component* node);
        bool isSelfAreParentLastNode();
        ~Root();
};