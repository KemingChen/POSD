#pragma once
using namespace std;

class Composite : public Component
{
    private:
        // Protected Variable
        NodeList _nodeList;

        // Private Method
        int childIndexOf(Component* node);

    public:
        // Public Method
        Composite(int id, string description);
        string getMap();
        void addChild(Component* node, Component* backFromNode = NULL);
        void removeChild(Component* node);
        void removeAllChild();
        Component* getParent() = 0;
        void setParent(Component* node) = 0;
        void addParent(Component* node) = 0;
        void addSibling(Component* node) = 0;
        bool isSelfAreParentLastNode() = 0;
        NodeList* getNodeList();
        ~Composite();
};