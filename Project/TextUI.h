#pragma once
#include "MindMapModel.h"
#include <iostream>
#include <map>

class TextUI
{
    private:
        // Type Define
        typedef map<string, void (TextUI::*)(void)> ChoiceMap;
        typedef list<int> NeedLineList;

        // Variable
        ChoiceMap _choiceMap;
        MindMapModel* _model;
        bool _isRun = true;

        // Private Method
        void printMenu();
        string handleInput();
        void handleMenuChoice();
        void printMindMap();
        void printChildNode(Component* node, string prefix, bool isParentAreLastNode);
        void createNewMindMap();
        void printInsertMenu();
        void insertNewNode();
        void displayMindMap();
        void navigateMindMap(Component* node, string* list);
        void saveMindMap();
        void printActionEnd();
        void exit();

    public:
        // Public Method
        TextUI(MindMapModel* model);
        void run();
        ~TextUI();
};

