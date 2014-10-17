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
        void navigateMindMap(Component* node, NodeList* list);
        string convertIntArrayToString(list<int>* intList);
        void splitMindMapLine(string line);

    public:
        // Public Method
        MindMapModel();
        void createMinMap(string description);
        void saveMindMap(ofstream* file);
        void loadMindMap(ifstream* file);
        void createNode();
        void editNodeDescription(Component* node, string description);
        void changeNodeParent(Component* node, Component* changeNode);
        void deleteNode(Component* node);
        void insertParentNode(Component* parent, Component* node);
        void insertChildNode(Component* parent, Component* node);
        void insertSiblingNode(Component* parent, Component* node);
        Component* getRootNode();
        Component* findNode(Component* node, string id);
        Component* findNode(string id);
        ~MindMapModel();
};