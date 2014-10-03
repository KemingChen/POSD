#pragma once
using namespace std;

class Node : public Composite
{
    public:
        // Public Method
        Node(Component* node);
        void addParent(Component* node);
        void addSibling(Component* node);
        ~Node();
};