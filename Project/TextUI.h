#pragma once
#include "PresentModel.h"
#include <iostream>
#include <map>

class TextUI
{
    private:
        // Variable
        map<string, void (TextUI::*)(void)> _mainMenuMap;
        map<string, void (TextUI::*)(Component*)> _insertMenuMap;
        map<string, void (TextUI::*)(Component*)> _editMenuMap;
        PresentModel* _presentModel;
        bool _isRun = true;

        // Control
        string handleInput();
        string handleInput(string description);

        // View
        void printActionMenu();
        void printInsertMenu();
        void printEditMenu();
        void printActionEnd();
        void printMindMap();

        // InsertAction Method
        void insertParentNode(Component* choseNode);
        void insertChildNode(Component* choseNode);
        void insertSiblingNode(Component* choseNode);

        // EditAction Method
        void editNodeDescription(Component* choseNode);
        void changeNodeParent(Component* choseNode);
        void deleteNode(Component* choseNode);

        // MainAction Method
        void createNewMindMap();
        void insertNewNode();
        void editNode();
        void displayMindMap();
        void saveMindMap();
        void loadMindMap();
        void redo();
        void undo();
        void exit();

    public:
        // Public Method
        TextUI(PresentModel* presentModel);
        void run();
        ~TextUI();
};