#pragma once
using namespace std;

class Root : public Composite
{
    public:
        // Public Method
        Root(int id);
        void addParent(Component* node);
        void addSibling(Component* node);
        ~Root();
};