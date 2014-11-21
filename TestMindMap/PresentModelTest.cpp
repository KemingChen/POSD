#include "stdafx.h"
#include <gtest\gtest.h>
#include "PresentModel.h"
#include "MockCommand.h"

class PresentModelTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            _model = new MindMapModel();
            _presentModel = new PresentModel(_model);
            // init some Commands for CommnadManager
            pushCommandManagerUndoStack();
            pushCommandManagerUndoStack();
            pushCommandManagerRedoStack();
            assertCommandManagerUndoStack(2);
            assertCommandManagerRedoStack(1);
        }

        virtual void TearDown()
        {
        }

        void pushCommandManagerUndoStack()
        {
            _presentModel->_commandManager._undoCommands.push(new MockCommand());
        }

        void pushCommandManagerRedoStack()
        {
            _presentModel->_commandManager._redoCommands.push(new MockCommand());
        }

        void assertCommandManagerUndoStack(int expectAmount)
        {
            ASSERT_EQ(expectAmount, _presentModel->_commandManager._undoCommands.size());
        }

        void assertCommandManagerRedoStack(int expectAmount)
        {
            ASSERT_EQ(expectAmount, _presentModel->_commandManager._redoCommands.size());
        }

        MindMapModel* _model;
        PresentModel* _presentModel;
};

TEST_F(PresentModelTest, createMindMap)
{
    _presentModel->createMindMap("Computer");
    assertCommandManagerUndoStack(0);
    assertCommandManagerRedoStack(0);
}

TEST_F(PresentModelTest, insertParentNode)
{
    // No New Logic
}

TEST_F(PresentModelTest, insertChildNode)
{
    // No New Logic
}

TEST_F(PresentModelTest, insertSiblingNode)
{
    // No New Logic
}

TEST_F(PresentModelTest, editNodeDescription)
{
    // No New Logic
}

TEST_F(PresentModelTest, changeNodeParent)
{
    Component* newNode = new Node(1, "OS");
    ASSERT_THROW(_presentModel->changeNodeParent(newNode, newNode), string);
}

TEST_F(PresentModelTest, deleteNode)
{
    _presentModel->createMindMap("Some Description");
    Component* root = _presentModel->_model->getRootNode();
    ASSERT_THROW(_presentModel->deleteNode(root), string);
}

TEST_F(PresentModelTest, redo)
{
    // No New Logic
}

TEST_F(PresentModelTest, undo)
{
    // No New Logic
}

TEST_F(PresentModelTest, tryFindNode)
{
    Component* node;
    _presentModel->createMindMap("Test");
    ASSERT_THROW(node = _presentModel->tryFindNode("-1"), string);
    ASSERT_NO_THROW(node = _presentModel->tryFindNode("0"));
    ASSERT_THROW(node = _presentModel->tryFindNode("1"), string);
}

TEST_F(PresentModelTest, confirmInsertNodeLegal)
{
    ASSERT_THROW(_presentModel->confirmMindMapExist(), string);
    _presentModel->createMindMap("Test");
    ASSERT_NO_THROW(_presentModel->confirmMindMapExist());
    Component* root = _presentModel->_model->getRootNode();
    ASSERT_THROW(_presentModel->confirmChangeNodeLegal(root), string);
}

TEST_F(PresentModelTest, saveMindMap)
{
    _presentModel->createMindMap("Test");
    _presentModel->saveMindMap();
    assertCommandManagerUndoStack(0);
    assertCommandManagerRedoStack(0);
}

TEST_F(PresentModelTest, loadMindMap)
{
    ASSERT_THROW(_presentModel->loadMindMap("not_exist.mm"), string);
}

TEST_F(PresentModelTest, getMindMap)
{
    ASSERT_EQ("The mind map is Empty!!!", _presentModel->getMindMap());
    _presentModel->createMindMap("Computer");
    _presentModel->insertChildNode(_presentModel->_model->getRootNode(), "OS");
    _presentModel->insertChildNode(_presentModel->_model->getRootNode(), "Network");
    Component* osNode = _presentModel->tryFindNode("1");
    _presentModel->insertChildNode(osNode, "Windows");
    string output = "";
    output += "The mind map Computer is desplayed as follows: \n";
    output += "¡Ï¡Ð Computer (Root, ID: 0)\n";
    output += "¡@¡@¡Ï¡Ð OS (Node, ID: 1)\n";
    output += "¡@¡@¡U¡@¡Ï¡Ð Windows (Node, ID: 3)\n";
    output += "¡@¡@¡Ï¡Ð Network (Node, ID: 2)\n";
    ASSERT_EQ(output, _presentModel->getMindMap());
}