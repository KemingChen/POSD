#pragma once
#include "MindMapModel.h"
#include "CommandManager.h"

class PresentModel
{
    private:
        typedef void(MindMapModel::*InsertMethod)(Component*, Component*);

        // private variable
        MindMapModel* _model;
        CommandManager _commandManager;

        // private method
        string getNodeMap(Component* node, string prefix, bool isParentAreLastNode);
        Component* tryInsertNode(Component* choseNode, InsertMethod insertMethod);

    public:
        // public method
        PresentModel(MindMapModel* model);
        Component* tryFindNode(string id);

        // Comfirm Method
        void confirmMindMapExist();
        void confirmChangeNodeLegal(Component* node);

        // Action Method
        void createMindMap(string description);
        Component* insertParentNode(Component* choseNode);
        Component* insertChildNode(Component* choseNode);
        Component* insertSiblingNode(Component* choseNode);
        void changeNodeParent(Component* node, Component* newParentNode);
        void editNodeDescription(Component* node, string description);
        void deleteNode(Component* node);
        string getMindMap();
        void saveMindMap();
        void loadMindMap(string path);
        void redo();
        void undo();
        ~PresentModel();
};