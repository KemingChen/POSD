#pragma once
#include "TextUIPresentModel.h"
#include <iostream>
#include <map>

class TextUI
{
    private:
        // Type Define
        typedef map<string, void (TextUI::*)(void)> ChoiceMap;

        // Variable
        ChoiceMap _choiceMap;
        TextUIPresentModel* _presentModel;
        bool _isRun = true;

        // Private Method
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
        TextUI(TextUIPresentModel* presentModel);
        void run();
        ~TextUI();
};

