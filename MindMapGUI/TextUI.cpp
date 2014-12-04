#include "stdafx.h"
#include "TextUI.h"
#define ENTER_NODE_NAME "Enter the node name:"
#define ERROR_COMMAND "The command is not found!!"

TextUI::TextUI(PresentModel* presentModel)
{
    _presentModel = presentModel;
    _guiWindow = new MindMapGUI(presentModel);
    _mainMenuMap["1"] = &TextUI::createNewMindMap;
    _mainMenuMap["2"] = &TextUI::insertNewNode;
    _mainMenuMap["3"] = &TextUI::editNode;
    _mainMenuMap["4"] = &TextUI::displayMindMap;
    _mainMenuMap["5"] = &TextUI::saveMindMap;
    _mainMenuMap["6"] = &TextUI::loadMindMap;
    _mainMenuMap["7"] = &TextUI::redo;
    _mainMenuMap["8"] = &TextUI::undo;
    _mainMenuMap["9"] = &TextUI::openGUI;
    _mainMenuMap["10"] = &TextUI::exit;
    _editMenuMap["a"] = &TextUI::editNodeDescription;
    _editMenuMap["b"] = &TextUI::changeNodeParent;
    _editMenuMap["c"] = &TextUI::deleteNode;
    _insertMenuMap["a"] = &TextUI::insertParentNode;
    _insertMenuMap["b"] = &TextUI::insertChildNode;
    _insertMenuMap["c"] = &TextUI::insertSiblingNode;
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
    const int maxSize = 100;
    char input[maxSize];
    cout << ">";
    do
    {
        cin.getline(input, maxSize);
    }
    while (input[0] == 0);
    return input;
}

string TextUI::handleInput(string description)
{
    cout << description << endl;
    return handleInput();
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
    cout << "9. OpenGUI" << endl;
    cout << "10. Exit" << endl;
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
    Component* root = _presentModel->getRoot();
    string output = "";
    if (root == NULL)
    {
        cout << "The mind map is Empty!!!" << endl;
        return;
    }
    output += "The mind map " + root->getDescription() + " is desplayed as follows: \n";
    output += root->toString() + "\n";
    NodeList* nodeList = root->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        output += getNodeMap(*iNode, "", true);
    }

    cout << output << endl;
}

string TextUI::getNodeMap(Component* node, string prefix, bool isParentAreLastNode)
{
    string output = "";
    prefix += isParentAreLastNode ? "¡@¡@" : "¡U¡@";
    output += prefix + node->toString() + "\n";
    NodeList* nodeList = node->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        output += getNodeMap(*iNode, prefix, node->isSelfAreParentLastNode());
    }
    return output;
}

void TextUI::printActionEnd()
{
    cout << "---------------------------------------------------------" << endl << endl;
}

void TextUI::createNewMindMap()
{
    string description;
    description = handleInput("Please enter the topic:");
    _presentModel->createMindMap(description);
    printMindMap();
}

void TextUI::insertParentNode(Component* choseNode)
{
    _presentModel->confirmInsertNodeLegal(choseNode, &MindMapModel::insertParentNode);
    _presentModel->insertParentNode(choseNode, handleInput(ENTER_NODE_NAME));
}

void TextUI::insertChildNode(Component* choseNode)
{
    _presentModel->confirmInsertNodeLegal(choseNode, &MindMapModel::insertChildNode);
    _presentModel->insertChildNode(choseNode, handleInput(ENTER_NODE_NAME));
}

void TextUI::insertSiblingNode(Component* choseNode)
{
    _presentModel->confirmInsertNodeLegal(choseNode, &MindMapModel::insertSiblingNode);
    _presentModel->insertSiblingNode(choseNode, handleInput(ENTER_NODE_NAME));
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
            string choice = handleInput();
            if (_insertMenuMap[choice])
            {
                (this->*_insertMenuMap[choice])(choseNode);
                printMindMap();
                break;
            }
            else
            {
                throw string(ERROR_COMMAND);
            }
        }
        catch (string error)
        {
            cout << error << endl << endl;
        }
    }
}

void TextUI::editNodeDescription(Component* choseNode)
{
    _presentModel->editNodeDescription(choseNode, handleInput("Enter the description: "));
}

void TextUI::changeNodeParent(Component* choseNode)
{
    Component* choseNewParentNode;
    _presentModel->confirmChangeNodeLegal(choseNode);
    while (true)
    {
        try
        {
            choseNewParentNode = _presentModel->tryFindNode(handleInput("Enter the parent ID: "));
            _presentModel->changeNodeParent(choseNode, choseNewParentNode);
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
    _presentModel->deleteNode(choseNode);
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
                throw string(ERROR_COMMAND);
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
    _presentModel->saveMindMap();
    printMindMap();
    cout << "Save MindMap Success" << endl;
}

void TextUI::loadMindMap()
{
    _presentModel->loadMindMap(handleInput("Please input a file path:"));
    displayMindMap();
}

void TextUI::redo()
{
    _presentModel->redo();
    displayMindMap();
}

void TextUI::undo()
{
    _presentModel->undo();
    displayMindMap();
}

void TextUI::openGUI()
{
    _guiWindow->show();
    _isRun = false;
}

void TextUI::exit()
{
    _isRun = false;
}

TextUI::~TextUI()
{
}