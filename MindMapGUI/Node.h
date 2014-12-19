#pragma once
using namespace std;

class Node : public Composite
{
    private:
        Component* _parentNode;

    public:
        // Public Method
        Node(int id, string description);
        Component* getParent();
        Component* clone();
        string getTypeName();
        void setParent(Component* node);
        void addParent(Component* node);
        void addSibling(Component* node);
        bool isSelfAreParentLastNode();
        ~Node();
};