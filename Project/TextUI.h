#pragma once
#include "MindMapModel.h"
#include "ConstVariables.h"

class TextUI
{
    private:
        // Variable
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

