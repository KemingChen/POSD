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
        handleMenuChoice();
    }
}

string TextUI::handleInput()
{
    string input;
    cout << INPUT_START;
    cin >> input;
    return input;
}

void TextUI::handleMenuChoice()
{
    string choice = handleInput();
    cout << endl;
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
    if (root != NULL)
    {
        cout << PRINT_MIND_MAP_DESCRIPTION_START;
        cout << root->getDescription();
        cout << PRINT_MIND_MAP_DESCRIPTION_END;
        cout << endl;
        printChildNode(root, "", false);
        cout << endl;
    }
}

void TextUI::printChildNode(Component* node, string prefix, bool isParentAreLastNode)
{
    string output;
    NodeList* nodeList = node->getNodeList();
    if (node != _model->getRootNode())
    {
        if (isParentAreLastNode)
        {
            prefix += PRINT_MAP_BLANK;
        }
        else
        {
            prefix += PRINT_MAP_LINE;
        }
    }
    output += prefix;
    output += PRINT_NODE_START + node->getDescription();
    output += PRINT_NODE_LEFT + node->getTypeName();
    output += PRINT_NODE_ID_START + node->getId() + PRINT_NODE_RIGHT;
    cout << output << endl;
    for (NodeList::iterator it = nodeList->begin(); it != nodeList->end(); it++)
    {
        printChildNode(*it, prefix, node->isSelfAreParentLastNode());
    }
}

void TextUI::createNewMindMap()
{
    string description;
    cout << CREATE_NEW_MIND_MAP_DESCRIPTION << endl;
    description = handleInput();
    _model->createMinMap(description);
    printMindMap();
    cout << PRINT_ACTION_END << endl << endl;
}

void TextUI::printInsertMenu()
{
    cout << INSERT_MENU_CHOICE_1_DESCRIPTION << endl;
    cout << INSERT_MENU_CHOICE_2_DESCRIPTION << endl;
    cout << INSERT_MENU_CHOICE_3_DESCRIPTION << endl;
}

void TextUI::insertNewNode()
{
    string id;
    string choice;
    string description;
    Component* newNode;
    printMindMap();
    cout << ENTER_NODE_ID << endl;
    id = handleInput();
    while (true)
    {
        try
        {
            printInsertMenu();
            choice = handleInput();
            newNode = _model->insertNode(id, choice);
            break;
        }
        catch (string error)
        {
            cout << error << endl << endl;
        }
    }
    cout << endl << ENTER_NODE_NAME << endl;
    description = handleInput();
    newNode->setDescription(description);
    printMindMap();
    cout << PRINT_ACTION_END << endl << endl;
}

void TextUI::displayMindMap()
{
    printMindMap();
    cout << PRINT_ACTION_END << endl << endl;
}

void TextUI::navigateMindMap(Component* node, string* list)
{
    int id = atoi(node->getId().c_str());
    string output = "";
    output += id + OUTPUT_BLANK;
    output += OUTPUT_DOUBLE_QUOTES + node->getDescription() + OUTPUT_DOUBLE_QUOTES;
}

void TextUI::saveMindMap()
{
    int nodeCount = _model->getNodeCount();
    string* nodeDataList = new string[nodeCount];
}

void TextUI::exit()
{
    _isRun = false;
}

TextUI::~TextUI()
{
}