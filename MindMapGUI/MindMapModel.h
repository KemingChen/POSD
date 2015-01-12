#pragma once
#include "stdafx.h"
#include "Subject.h"
#include "Component.h"
#include <map>
#include "IGraphic.h"
using namespace std;

class MindMapModel : public Subject
{
        friend class MindMapModelTest;
    private:
        // Private Variable
        Component* _root;
        Component* _empty;

        // Private Method
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
        void revertDeleteNode(Component* choseNode, Component* backFromNode);
        void insertParentNode(Component* choseNode, Component* newNode);
        void revertInsertParentNode(Component* choseNode, Component* newNode, Component* oldParentNode, Component* backFromNode);
        void insertChildNode(Component* choseNode, Component* newNode);
        void insertSiblingNode(Component* choseNode, Component* newNode);
        void addDecorate(Component* decorateNode, Component* originalNode);
        void removeDecorate(Component* originalNode);
        void cutNode(Component* selectedNode);
        void pasteNode(Component* selectedNode, Component* cloneNode);
        void MindMapModel::rebuildPosition(IGraphic* painter);
        void collapseAll(Component* choseNode);
        void expandAll(Component* choseNode);
        void expandOneLevel(Component* choseNode);
        Component* findSideUpNode(Component* choseNode);
        Component* findSideDownNode(Component* choseNode);
        void moveToBack(Component* choseNode, Component* targetNode);
        Component* getRootNode();
        Component* findNode(Component* fromNode, int id);
        Component* findNode(int id);
        ~MindMapModel();
};