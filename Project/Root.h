#pragma once
using namespace std;

class Root : public Composite
{
    public:
        // Public Method
        Root();
        void addParent(Component* node);
        void addSibling(Component* node);
        ~Root();
};