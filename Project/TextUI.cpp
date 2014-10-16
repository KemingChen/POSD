#include "stdafx.h"
#include "TextUI.h"

TextUI::TextUI(PresentModel* presentModel)
{
    _presentModel = presentModel;
    _mainMenuMap["1"] = &TextUI::createNewMindMap;
    _mainMenuMap["2"] = &TextUI::insertNewNode;
    _mainMenuMap["3"] = &TextUI::editNode;
    _mainMenuMap["4"] = &TextUI::displayMindMap;
    _mainMenuMap["5"] = &TextUI::saveMindMap;
    _mainMenuMap["6"] = &TextUI::loadMindMap;
    _mainMenuMap["7"] = &TextUI::redo;
    _mainMenuMap["8"] = &TextUI::undo;
    _mainMenuMap["9"] = &TextUI::exit;
    _editMenuMap["a"] = &TextUI::editNodeDescription;
    _editMenuMap["b"] = &TextUI::changeNodeParent;
    _editMenuMap["c"] = &TextUI::deleteNode;
}

void TextUI::run()
{
    while (_isRun)
    {
        printActionMenu();
        string choice = handleInput();
        cout << endl;
        if (_mainMenuMap[choice])
        {
            try
            {
                (this->*_mainMenuMap[choice])();
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

void TextUI::printEditMenu()
{
    cout << "a.Edit the description of a node" << endl;
    cout << "b.Change the parent of a node" << endl;
    cout << "c.Delete a node" << endl;
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
    _presentModel->confirmMindMapExist();
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

void TextUI::editNodeDescription(Component* choseNode)
{
    _presentModel->getModel()->editNodeDescription(choseNode, handleInput("Enter the description: "));
}

void TextUI::changeNodeParent(Component* choseNode)
{
    Component* choseNewParentNode;
    _presentModel->confirmChangeNodeNotRoot(choseNode);
    while (true)
    {
        try
        {
            choseNewParentNode = _presentModel->tryFindNode(handleInput("Enter the parent ID: "));
            _presentModel->changeParentNode(choseNode, choseNewParentNode);
            break;
        }
        catch (string error)
        {
            cout << error << endl << endl;
        }
    }
}

void TextUI::deleteNode(Component* choseNode)
{
    throw string("No Imprement");
}

void TextUI::editNode()
{
    string choice;
    Component* choseNode = NULL;
    _presentModel->confirmMindMapExist();
    while (true)
    {
        try
        {
            if (choseNode == NULL)
            {
                printMindMap();
                choseNode = _presentModel->tryFindNode(handleInput("Enter the edit node ID:"));
            }
            printEditMenu();
            choice = handleInput();
            if (_editMenuMap[choice])
            {
                (this->*_editMenuMap[choice])(choseNode);
                printMindMap();
                break;
            }
            else
            {
                throw string("The command is not found!!");
            }
        }
        catch (string error)
        {
            cout << error << endl << endl;
        }
    }
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
    //_presentModel->loadMindMap(handleInput("Please input a file path:"));
    _presentModel->loadMindMap("file__exist.mm");
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