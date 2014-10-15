#pragma once
#include "PresentModel.h"
#include <iostream>
#include <map>

class TextUI
{
    private:
        // Type Define
        typedef map<string, void (TextUI::*)(void)> ChoiceMap;

        // Variable
        ChoiceMap _choiceMap;
        PresentModel* _presentModel;
        bool _isRun = true;

        // Control
        string handleInput();

        // View
        void printActionMenu();
        void printInsertMenu();
        void printActionEnd();

        // ?
        void printNodeMap(Component* node, string prefix, bool isParentAreLastNode);
        void printRootMap();

        // Action Method
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