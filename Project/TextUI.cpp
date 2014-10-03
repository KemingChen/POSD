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
    cout << MENU_DESCRIPTION << endl;
    cout << MENU_CHOICE_1_DESCRIPTION << endl;
    cout << MENU_CHOICE_2_DESCRIPTION << endl;
    cout << MENU_CHOICE_3_DESCRIPTION << endl;
    cout << MENU_CHOICE_4_DESCRIPTION << endl;
    cout << MENU_CHOICE_5_DESCRIPTION << endl;
}

void TextUI::printMindMap()
{
    Component* root = _model->getRootNode();
    cout << PRINT_MIND_MAP_DESCRIPTION_START;
    cout << root->getDescription();
    cout << PRINT_MIND_MAP_DESCRIPTION_END;
    cout << endl;
    printChildNode(root, 0);
    cout << endl << PRINT_MIND_MAP_END << endl << endl;
}

void TextUI::printChildNode(Component* node, int level)
{
    string output;
    NodeMap* nodeMap = node->getMap();
    NodeList* nodeList = node->getNodeList();
    for (int i = 0; i < level; i++)
    {
        output += PRINT_MAP_BLANK;
    }
    output += PRINT_NODE_START + nodeMap->getDescription();
    output += PRINT_NODE_LEFT + nodeMap->getNodeName();
    output += PRINT_NODE_ID_START + nodeMap->getId() + PRINT_NODE_RIGHT;
    cout << output << endl;
    for (NodeList::iterator it = nodeList->begin(); it != nodeList->end(); it++)
    {
        printChildNode(*it, level + 1);
    }
}

void TextUI::createNewMindMap()
{
    string description;
    cout << CREATE_NEW_MIND_MAP_DESCRIPTION << endl;
    cout << INPUT_START;
    cin >> description;
    cout << INPUT_END;
    _model->createMinMap(description);
    printMindMap();
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
