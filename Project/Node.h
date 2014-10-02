#pragma once
using namespace std;

class Node : public Composite
{
    public:
        // Public Method
        Node();
        void addParent(Component* node);
        void addSibling(Component* node);
        ~Node();
};