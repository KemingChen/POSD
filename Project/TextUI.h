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
        //string handleInput();
        void createNewMindMap();
        void insertNewNode();
        void displayMindMap();
        void saveMindMap();
        void exit();

    public:
        // Public Method
        TextUI(TextUIPresentModel* presentModel);
        void run();
        ~TextUI();
};

