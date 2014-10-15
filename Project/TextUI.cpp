#include "stdafx.h"
#include "TextUI.h"
#define DB_FILE "MindMap.db"

TextUI::TextUI(PresentModel* presentModel)
{
    _presentModel = presentModel;
    _choiceMap["1"] = &TextUI::createNewMindMap;
    _choiceMap["2"] = &TextUI::insertNewNode;
    _choiceMap["3"] = &TextUI::editNode;
    _choiceMap["4"] = &TextUI::displayMindMap;
    _choiceMap["5"] = &TextUI::saveMindMap;
    _choiceMap["6"] = &TextUI::loadMindMap;
    _choiceMap["7"] = &TextUI::redo;
    _choiceMap["8"] = &TextUI::undo;
    _choiceMap["9"] = &TextUI::exit;
}

void TextUI::run()
{
    while (_isRun)
    {
        printActionMenu();
        string choice = handleInput();
        cout << endl;
        if (_choiceMap[choice])
        {
            (this->*_choiceMap[choice])();
        }
    }
}

string TextUI::handleInput()
{
    string input;
    cout << ">";
    cin >> input;
    return input;
}

void TextUI::printActionMenu()
{
    cout << "Please enter your choice:" << endl;
    cout << "1. Create a new mind map" << endl;
    cout << "2. Insert a new node" << endl;
    cout << "3. Edit a node" << endl;
    cout << "4. Display a mind map" << endl;
    cout << "5. Save a mind map" << endl;
    cout << "6. Load a mind map" << endl;
    cout << "7. Redo" << endl;
    cout << "8. Undo" << endl;
    cout << "9. Exit" << endl;
}

void TextUI::printInsertMenu()
{
    cout << "a. Insert a parent node" << endl;
    cout << "b. Insert a child node" << endl;
    cout << "c. Insert a sibling node" << endl;
}

void TextUI::printActionEnd()
{
    cout << "---------------------------------------------------------" << endl << endl;
}

void TextUI::createNewMindMap()
{
    string description;
    cout << "Please enter the topic:" << endl;
    description = handleInput();
    _presentModel->getModel()->createMinMap(description);
    printRootMap();
    printActionEnd();
}

void TextUI::insertNewNode()
{
    printRootMap();
    string id;
    Component* newNode;
    cout << "Enter the node ID:" << endl;
    id = handleInput();
    bool success = false;
    while (!success)
    {
        try
        {
            printInsertMenu();
            string choice;
            choice = handleInput();
            newNode = _presentModel->getModel()->insertNode(id, choice);
            string description;
            cout << endl << "Enter the node name:" << endl;
            description = handleInput();
            newNode->setDescription(description);
            success = true;
        }
        catch (string error)
        {
            cout << error << endl << endl;
        }
    }
    printRootMap();
    printActionEnd();
}

void TextUI::editNode()
{
}

void TextUI::printRootMap()
{
    Component* root = _presentModel->getModel()->getRootNode();
    cout << "The mind map " << root->getDescription() << " is desplayed as follows: " << endl;
    cout << root->toString() << endl;
    NodeList* nodeList = root->getNodeList();
    for (NodeList::iterator it = nodeList->begin(); it != nodeList->end(); it++)
    {
        printNodeMap(*it, "", true);
    }
    cout << endl;
}

void TextUI::printNodeMap(Component* node, string prefix, bool isParentAreLastNode)
{
    prefix += isParentAreLastNode ? "¡@¡@" : "¡U¡@";
    cout << prefix + node->toString() << endl;
    NodeList* nodeList = node->getNodeList();
    for (NodeList::iterator it = nodeList->begin(); it != nodeList->end(); it++)
    {
        printNodeMap(*it, prefix, node->isSelfAreParentLastNode());
    }
}

void TextUI::displayMindMap()
{
    printRootMap();
    printActionEnd();
}

void TextUI::saveMindMap()
{
    printRootMap();
    _presentModel->getModel()->saveMindMap(DB_FILE);
    cout << "Save MindMap Success" << endl;
    printActionEnd();
}

void TextUI::loadMindMap()
{
    string path;
    cout << "Please input a file path:" << endl;
    path = handleInput();
    _presentModel->getModel()->loadMindMap(path);
}

void TextUI::redo()
{
}

void TextUI::undo()
{
}

void TextUI::exit()
{
    _isRun = false;
}

TextUI::~TextUI()
{
}