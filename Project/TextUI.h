#pragma once
#include "MindMapModel.h"
#include "ConstVariables.h"
#include <iostream>
#include <map>
using namespace std;

class TextUI
{
    private:
        // Type Define
        typedef map<int, void (TextUI::*)(void)> ChoiceMap;

        // Variable
        ChoiceMap _choiceMap;
        MindMapModel* _model;
        bool _isRun = true;

        // Private Method
        void printMenu();
        void handleChoice();
        void createNewMindMap();
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

