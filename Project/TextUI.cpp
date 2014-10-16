#include "stdafx.h"
#include "TextUI.h"

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
            try
            {
                (this->*_choiceMap[choice])();
            }
            catch (string error)
            {
                cout << error << endl;
            }
            printActionEnd();
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

string TextUI::handleInput(string description)
{
    string input;
    cout << description << endl << ">";
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

void TextUI::printMindMap()
{
    cout << _presentModel->getMindMap() << endl;
}

void TextUI::printActionEnd()
{
    cout << "---------------------------------------------------------" << endl << endl;
}

void TextUI::createNewMindMap()
{
    string description;
    description = handleInput("Please enter the topic:");
    _presentModel->getModel()->createMinMap(description);
    printMindMap();
}

void TextUI::insertNewNode()
{
    Component* newNode = NULL;
    Component* choseNode = NULL;
    _presentModel->comfirmMindMapExist();
    while (newNode == NULL)
    {
        try
        {
            if (choseNode == NULL)
            {
                printMindMap();
                choseNode = _presentModel->tryFindNode(handleInput("Enter the node ID:"));
            }
            printInsertMenu();
            newNode = _presentModel->insertNode(choseNode, handleInput());
            newNode->setDescription(handleInput("Enter the node name:"));
        }
        catch (string error)
        {
            cout << error << endl << endl;
        }
    }
    printMindMap();
}

void TextUI::editNode()
{
}

void TextUI::displayMindMap()
{
    printMindMap();
}

void TextUI::saveMindMap()
{
    printMindMap();
    _presentModel->saveMindMap();
    cout << "Save MindMap Success" << endl;
}

void TextUI::loadMindMap()
{
    try
    {
        //_presentModel->loadMindMap(handleInput("Please input a file path:"));
        _presentModel->loadMindMap("file__exist.mm");
    }
    catch (string error)
    {
        cout << error << endl;
    }
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