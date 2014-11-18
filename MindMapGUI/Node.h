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
        void setParent(Component* node);
        void addParent(Component* node);
        void addSibling(Component* node);
        bool isSelfAreParentLastNode();
        ~Node();
};