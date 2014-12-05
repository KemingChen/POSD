#pragma once
#include "MindMapModel.h"
#include "CommandManager.h"
#define DB_FILE "file__exist.mm"

class PresentModel
{
        friend class PresentModelTest;
        FRIEND_TEST(PresentModelTest, deleteNode);
        FRIEND_TEST(PresentModelTest, confirmInsertNodeLegal);
        FRIEND_TEST(PresentModelTest, getMindMap);

    private:
        typedef void(MindMapModel::*InsertMethod)(Component*, Component*);

        // private variable
        MindMapModel* _model;
        CommandManager _commandManager;

    public:
        // public method
        PresentModel(MindMapModel* model);
        Component* tryFindNode(string id);
        Component* getRoot();
        void clearCommandManager();

        // Comfirm Method
        void confirmMindMapExist();
        void confirmChangeNodeLegal(Component* node);
        void confirmInsertNodeLegal(Component* node, InsertMethod insertMethod);

        // Action Method
        void createMindMap(string description);
        void insertParentNode(Component* choseNode, string description);
        void insertChildNode(Component* choseNode, string description);
        void insertSiblingNode(Component* choseNode, string description);
        void changeNodeParent(Component* node, Component* newParentNode);
        void editNodeDescription(Component* node, string description);
        void deleteNode(Component* node);
        void cutNode(Component* node);
        void pasteNode(Component* selectedNode, Component* cloneNode);
        void saveMindMap(string path = DB_FILE);
        void loadMindMap(string path);
        void redo();
        void undo();
        ~PresentModel();
};