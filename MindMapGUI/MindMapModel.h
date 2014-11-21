#pragma once
#include "stdafx.h"
#include <map>
#include <fstream>
using namespace std;

class MindMapModel
{
        friend class MindMapModelTest;
        friend class IntegrationTest;

    private:
        // Private Variable
        Component* _root;

        // Private Method
        void navigateMindMap(Component* node, NodeList* list);
        void splitMindMapLine(string line);

    public:
        // Public Method
        MindMapModel();
        void createMinMap(string description);
        void saveMindMap(ofstream* file);
        void loadMindMap(ifstream* file);
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