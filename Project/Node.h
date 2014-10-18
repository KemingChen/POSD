#pragma once
using namespace std;

class Node : public Composite
{
    public:
        // Public Method
        Node(int id, string description);
        void addParent(Component* node);
        void addSibling(Component* node);
        bool isSelfAreParentLastNode();
        ~Node();
};