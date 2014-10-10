#include "stdafx.h"
#include "TextUI.h"

TextUI::TextUI(MindMapModel* model)
{
    _model = model;
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
        printMenu();
        handleMenuChoice();
    }
}

string TextUI::handleInput()
{
    string input;
    cout << ">";
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
    cout << "Please enter your choice:" << endl;
    cout << "1. Create a new mind map" << endl;
    cout << "2. Insert a new node" << endl;
    cout << "3. Display mind map" << endl;
    cout << "4. Save mind map" << endl;
    cout << "5. Exit" << endl;
}

void TextUI::printMindMap()
{
    Component* root = _model->getRootNode();
    if (root != NULL)
    {
        cout << "The mind map " << root->getDescription() << " is desplayed as follows:" << endl;
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
            prefix += "¡@¡@";
        }
        else
        {
            prefix += "¡U¡@";
        }
    }
    output += prefix;
    output += "¡Ï¡Ð " + node->getDescription();
    output += " (" + node->getTypeName() + ", ID: " + node->getId() + ")";
    cout << output << endl;
    for (NodeList::iterator it = nodeList->begin(); it != nodeList->end(); it++)
    {
        printChildNode(*it, prefix, node->isSelfAreParentLastNode());
    }
}

void TextUI::createNewMindMap()
{
    string description;
    cout << "Please enter the topic:" << endl;
    description = handleInput();
    _model->createMinMap(description);
    printMindMap();
    printActionEnd();
}

void TextUI::printInsertMenu()
{
    cout << "a. Insert a parent node" << endl;
    cout << "b. Insert a child node" << endl;
    cout << "c. Insert a sibling node" << endl;
}

void TextUI::insertNewNode()
{
    string id;
    string choice;
    string description;
    Component* newNode;
    printMindMap();
    cout << "Enter the node ID:" << endl;
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
    cout << endl << "Enter the node name:" << endl;
    description = handleInput();
    newNode->setDescription(description);
    printMindMap();
    printActionEnd();
}

void TextUI::displayMindMap()
{
    printMindMap();
    printActionEnd();
}

void TextUI::saveMindMap()
{
    printMindMap();
    _model->saveMindMap();
    cout << "Save MindMap Success" << endl;
    printActionEnd();
}

void TextUI::printActionEnd()
{
    cout << "---------------------------------------------------------" << endl << endl;
}

void TextUI::exit()
{
    _isRun = false;
}

TextUI::~TextUI()
{
}