#pragma once
#include "MindMapModel.h"
#include "ConstVariables.h"
#include <iostream>
#include <map>

class TextUI
{
    private:
        // Type Define
        typedef map<string, void (TextUI::*)(void)> ChoiceMap;

        // Variable
        ChoiceMap _choiceMap;
        MindMapModel* _model;
        bool _isRun = true;

        // Private Method
        void printMenu();
        string handleInput();
        void handleMenuChoice();
        void printMindMap();
        void printChildNode(Component* node, int level);
        void createNewMindMap();
        void printInsertMenu();
        void insertNewNode();
        void displayMindMap();
        void saveMindMap();
        void exit();

    public:
        // Public Method
        TextUI(MindMapModel* model);
        void run();
        ~TextUI();
};

