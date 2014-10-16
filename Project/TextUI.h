#pragma once
#include "PresentModel.h"
#include <iostream>
#include <map>

class TextUI
{
    private:
        // Type Define
        typedef map<string, void (TextUI::*)(void)> MainMenuMap;
        typedef map<string, void (TextUI::*)(Component*)> EditMenuMap;

        // Variable
        MainMenuMap _mainMenuMap;
        EditMenuMap _editMenuMap;
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