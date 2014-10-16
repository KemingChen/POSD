#pragma once
#include <map>
#include <fstream>
using namespace std;

class MindMapModel
{
    private:
        // Private Variable
        Component* _root;

        // Private Method
        void navigateMindMap(Component* node, string* list);
        string convertIntArrayToString(list<int>* intList);
        void splitMindMapLine(string line);

    public:
        // Public Method
        MindMapModel();
        void createMinMap(string description);
        void saveMindMap(ofstream* file);
        void loadMindMap(ifstream* file);
        void createNode();
        void insertParentNode(Component* parent, Component* node);
        void insertChildNode(Component* parent, Component* node);
        void insertSiblingNode(Component* parent, Component* node);
        Component* getRootNode();
        Component* findNode(Component* node, string id);
        Component* findNode(string id);
        ~MindMapModel();
};