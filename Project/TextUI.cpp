#include "stdafx.h"
#include "TextUI.h"

TextUI::TextUI(TextUIPresentModel* presentModel)
{
    _presentModel = presentModel;
    _choiceMap["1"] = &TextUI::createNewMindMap;
    _choiceMap["2"] = &TextUI::insertNewNode;
    _choiceMap["3"] = &TextUI::displayMindMap;
    _choiceMap["4"] = &TextUI::saveMindMap;
    _choiceMap["5"] = &TextUI::exit;
}

void TextUI::run()
{
    while (_isRun)
    {
        _presentModel->printMenu();
        string choice = _presentModel->handleInput();
        cout << endl;
        if (_choiceMap[choice])
        {
            (this->*_choiceMap[choice])();
        }
    }
}

void TextUI::createNewMindMap()
{
    _presentModel->createMindMap();
    _presentModel->printRootMap();
    _presentModel->printActionEnd();
}

void TextUI::insertNewNode()
{
    Component* newNode;
    _presentModel->printRootMap();
    _presentModel->insertNode();
    _presentModel->printRootMap();
    _presentModel->printActionEnd();
}

void TextUI::displayMindMap()
{
    _presentModel->printRootMap();
    _presentModel->printActionEnd();
}

void TextUI::saveMindMap()
{
    _presentModel->printRootMap();
    _presentModel->saveMindMap();
}

void TextUI::exit()
{
    _isRun = false;
}

TextUI::~TextUI()
{
}