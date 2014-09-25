#include "stdafx.h"
#include "TextUI.h"


TextUI::TextUI(MindMapModel* model)
{
    _model = model;
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
    scanf_s("%d", &choice);
    switch (choice)
    {
        case CREATE_NEW_MIND_MAP:
            createNewMindMap();
            break;
        case INSERT_NEW_NODE:
            insertNewNode();
            break;
        case DISPLAY_MIND_MAP:
            displayMindMap();
            break;
        case SAVE_MIND_MAP:
            saveMindMap();
            break;
        case EXIT:
            exit();
            break;
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
    printf("%s", MENU_END);
}

void TextUI::createNewMindMap()
{
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
