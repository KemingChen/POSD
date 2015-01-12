#pragma once
#include "PresentModel.h"
#include <time.h>
#include "Subject.h"
#include "IGraphic.h"

using namespace std;

class GUIPresentModel : public Subject
{
    private:
        typedef void(MindMapModel::*InsertMethod)(Component*, Component*);

        PresentModel* _presentModel;
        MindMapModel* _model;
        CommandManager* _commandManager;

        // Variable
        clock_t _lastClickTime;

        // Property
        int _selectedNodeId;
        Component* _prepareCloneNode;

        // Method
        bool isValidClick();
        bool isValidText(bool isSubmit, string text);
        bool confirmInsertNodeLegal(InsertMethod insertMethod);
        void cancelSelected();

    public:
        GUIPresentModel(PresentModel* presentModel, MindMapModel* model);
        ~GUIPresentModel();

        // Action
        void clickGraphicNode(int id);
        void editDescription(string text, bool isValid);
        void loadMindMap(string path);
        void saveMindMap(string path);
        void createMindMap(string text, bool isValid);
        void insertParentNode(string text, bool isValid);
        void insertChildNode(string text, bool isValid);
        void insertSiblingNode(string text, bool isValid);
        void deleteNode();
        void cutNode();
        void copyNode();
        void pasteNode();
        void undo();
        void redo();
        void addDecorate(ComponentType type);
        void cleanAllDecorate();
        void collapseAll();
        void expandAll();
        void expandOneLevel();
        void moveUp();
        void moveDown();

        // File Status
        bool isSaveEnable();

        // Edit Status
        bool isSelected();
        bool isEditNodeEnable();
        bool isDeleteNodeEnable();
        bool isInsertParentNodeEnable();
        bool isInsertChildNodeEnable();
        bool isInsertSiblingNodeEnable();
        bool isCutNodeEnable();
        bool isCopyNodeEnable();
        bool isPasteNodeEnable();
        bool isUndoEnable();
        bool isRedoEnable();

        // Method
        void rebuildPosition(IGraphic* painter);
        Component* getSelectedNode();
        Component* getRoot();
        Component* tryFindNode(int id);
        bool isCreatedMindMap();
        bool isSelectedNode(int id);
};