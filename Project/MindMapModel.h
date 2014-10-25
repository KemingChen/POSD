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
        void editNodeDescription(Component* choseNode, string description);
        void changeNodeParent(Component* choseNode, Component* newParentNode);
        void revertChangeNodeParent(Component* choseNode, Component* oldParentNode, NodeList* oldNodeList);
        void deleteNode(Component* choseNode);
        void revertDeleteNode(Component* choseNode);
        void insertParentNode(Component* choseNode, Component* newNode);
        void revertInsertParentNode(Component* choseNode, Component* newNode, Component* oldParentNode);
        void insertChildNode(Component* choseNode, Component* newNode);
        void insertSiblingNode(Component* choseNode, Component* newNode);
        Component* getRootNode();
        Component* findNode(Component* fromNode, string id);
        Component* findNode(string id);
        ~MindMapModel();
};