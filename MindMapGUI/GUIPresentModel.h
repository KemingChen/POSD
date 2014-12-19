#pragma once
#include "PresentModel.h"
#include "INotifyGraphics.h"
#include <time.h>
#include "Subject.h"

using namespace std;

class GUIPresentModel : public Subject
{
    private:
        PresentModel* _presentModel;
        //INotifyGraphics* _notify;

        // Variable
        clock_t _lastClickTime;

        // Property
        Component* _selectedNode;
        Component* _prepareCloneNode;

        // Method
        bool isValidClick();

    public:
        GUIPresentModel(PresentModel* presentModel);
        ~GUIPresentModel();

        // Action
        void clickGraphicNode(string id);
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

        // Method
        Component* getSelectedNode();
        Component* getRoot();
        bool isCreatedMindMap();
        bool isSelectedNode(Component* node);
};