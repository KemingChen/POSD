#include "stdafx.h"
#include "TextUI.h"


TextUI::TextUI(MindMapModel* model)
{
    _model = model;
    _choiceMap[CREATE_NEW_MIND_MAP] = &TextUI::createNewMindMap;
    _choiceMap[INSERT_NEW_NODE] = &TextUI::insertNewNode;
    _choiceMap[DISPLAY_MIND_MAP] = &TextUI::displayMindMap;
    _choiceMap[SAVE_MIND_MAP] = &TextUI::saveMindMap;
    _choiceMap[EXIT] = &TextUI::exit;
}

void TextUI::run()
{
    while (_isRun)
    {
        printMenu();
        handleChoice();
    }
}

void TextUI::handleChoice()
{
    int choice;
    cout << INPUT_START;
    cin >> choice;
    cout << INPUT_END;
    if (_choiceMap[choice])
    {
        (this->*_choiceMap[choice])();
    }
}

void TextUI::printMenu()
{
    printf("%s\n", MENU_DESCRIPTION);
    printf("%s\n", MENU_CHOICE_1_DESCRIPTION);
    printf("%s\n", MENU_CHOICE_2_DESCRIPTION);
    printf("%s\n", MENU_CHOICE_3_DESCRIPTION);
    printf("%s\n", MENU_CHOICE_4_DESCRIPTION);
    printf("%s\n", MENU_CHOICE_5_DESCRIPTION);
}

void TextUI::createNewMindMap()
{
    //_model->createMinMap();
}

void TextUI::insertNewNode()
{
}

void TextUI::displayMindMap()
{
}

void TextUI::saveMindMap()
{
}

void TextUI::exit()
{
    _isRun = false;
}

TextUI::~TextUI()
{
}
