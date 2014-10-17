#pragma once
#include "MindMapModel.h"
#include "CommandManager.h"

class PresentModel
{
    private:
        typedef map<string, void (MindMapModel::*)(Component*, Component*)> InsertActionMap;

        // private variable
        MindMapModel* _model;
        CommandManager _commandManager;
        InsertActionMap _insertActionMap;

        // private method
        string getNodeMap(Component* node, string prefix, bool isParentAreLastNode);

    public:
        // public method
        PresentModel(MindMapModel* model);
        MindMapModel* getModel();
        string getMindMap();
        void saveMindMap();
        void loadMindMap(string path);
        void changeNodeParent(Component* node, Component* newParentNode);
        void editNodeDescription(Component* node, string description);
        void deleteNode(Component* node);
        void confirmMindMapExist();
        void confirmChangeNodeLegal(Component* node);
        void redo();
        void undo();
        Component* insertNode(Component* choseNode, string action);
        Component* tryFindNode(string id);
        ~PresentModel();
};