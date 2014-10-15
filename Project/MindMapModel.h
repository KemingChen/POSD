#pragma once
#include <map>
using namespace std;

class MindMapModel
{
    private:
        // Private Variable
        Component* _root;

        // Private Method
        void navigateMindMap(Component* node, string* list);
        string convertIntArrayToString(list<int>* intList);

    public:
        // Public Method
        MindMapModel();
        void createMinMap(string description);
        void saveMindMap(string path);
        void loadMindMap(string path);
        void createNode();
        void insertParentNode(Component* parent, Component* node);
        void insertChildNode(Component* parent, Component* node);
        void insertSiblingNode(Component* parent, Component* node);
        Component* getRootNode();
        Component* findNode(Component* node, string id);
        Component* findNode(string id);
        ~MindMapModel();
};