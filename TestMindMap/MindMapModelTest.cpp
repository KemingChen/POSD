#include "stdafx.h"
#include <gtest\gtest.h>
#include "MindMapModel.h"
#define TEST_DATA_DIR "testdata"
#define TEST_TEMP_FILE "testdata/temp_file.mm"

class MindMapModelTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            _mkdir(TEST_DATA_DIR);
        }

        virtual void TearDown()
        {
            remove(TEST_TEMP_FILE);
            _rmdir(TEST_DATA_DIR);
        }

        /*
        	TestMindMap is follow as below
        	¡Ï¡Ð Computer(Root, ID: 0)
        		¡Ï¡Ð OS(Node, ID: 2)
        		¡U¡@¡Ï¡Ð windows(Node, ID: 1)
        		¡U¡@¡U¡@¡Ï¡Ð DirectX(Node, ID: 5)
        		¡U¡@¡U¡@¡Ï¡Ð Microsoft Office(Node, ID: 6)
        		¡U¡@¡Ï¡Ð IOS(Node, ID: 3)
        		¡U¡@¡Ï¡Ð Linux(Node, ID: 4)
        		¡Ï¡Ð Network(Node, ID: 7)
        			¡Ï¡Ð Wireless(Node, ID: 8)
        			¡Ï¡Ð Cable(Node, ID: 9)
        */
        void createTestMindMap()
        {
            _root = new Root(0, "Computer");
            Component* windowsNode = new Node(1, "windows");
            windowsNode->addChild(new Node(5, "DirectX"));
            windowsNode->addChild(new Node(6, "Microsoft Office"));
            Component* osNode = new Node(2, "OS");
            osNode->addChild(windowsNode);
            osNode->addChild(new Node(3, "IOS"));
            osNode->addChild(new Node(4, "Linux"));
            Component* networkNode = new Node(7, "Network");
            networkNode->addChild(new Node(8, "Wireless"));
            networkNode->addChild(new Node(9, "Cable"));
            _root->addChild(osNode);
            _root->addChild(networkNode);
            _model._root = _root;
        }

        void assertTestMindMap()
        {
            ASSERT_EQ(" 2 7", _model.findNode("0")->getMap());
            ASSERT_EQ(" 5 6", _model.findNode("1")->getMap());
            ASSERT_EQ(" 1 3 4", _model.findNode("2")->getMap());
            ASSERT_EQ("", _model.findNode("3")->getMap());
            ASSERT_EQ("", _model.findNode("4")->getMap());
            ASSERT_EQ("", _model.findNode("5")->getMap());
            ASSERT_EQ("", _model.findNode("6")->getMap());
            ASSERT_EQ(" 8 9", _model.findNode("7")->getMap());
            ASSERT_EQ("", _model.findNode("8")->getMap());
            ASSERT_EQ("", _model.findNode("9")->getMap());
        }

        // Change Parent Node is The Child under Node
        void testChangeParentUnderTheNode()
        {
            // New Parent is The Child under Node
            createTestMindMap();
            Component* networkNode = _model.findNode("7");
            Component* wirelessNode = _model.findNode("8");
            Component* oldParentNode = _model.findNode("0");
            NodeList oldNodeList;
            oldNodeList.push_back(_model.findNode("8"));
            oldNodeList.push_back(_model.findNode("9"));
            _model.changeNodeParent(networkNode, wirelessNode);
            ASSERT_EQ(" 2 8 9", _root->getMap());
            ASSERT_EQ(" 7", wirelessNode->getMap());
            ASSERT_EQ("", networkNode->getMap());
            _model.revertChangeNodeParent(networkNode, oldParentNode, &oldNodeList);
            assertTestMindMap();
        }

        // Change Parent Node is NOT The Child under Node
        void testChangeParentNotUnderNode()
        {
            createTestMindMap();
            Component* networkNode = _model.findNode("7");
            Component* windowsNode = _model.findNode("1");
            Component* oldParentNode = _model.findNode("0");
            NodeList oldNodeList;
            _model.changeNodeParent(networkNode, windowsNode);
            ASSERT_EQ(" 2", _root->getMap());
            ASSERT_EQ(" 5 6 7", windowsNode->getMap());
            ASSERT_EQ(" 8 9", networkNode->getMap());
            _model.revertChangeNodeParent(networkNode, oldParentNode, &oldNodeList);
            assertTestMindMap();
        }

        void clearMindMap()
        {
            _model._root = NULL;
        }

        MindMapModel _model;
        Component* _root;
};

TEST_F(MindMapModelTest, createMinMap)
{
    // No New Logic
}

TEST_F(MindMapModelTest, insertParentNode)
{
    createTestMindMap();
    Component* networkNode = _model.findNode("7");
    Component* oldParentNode = _model.findNode("0");
    Component* newParentNode = new Node(10, "New Parent Node");
    _model.insertParentNode(networkNode, newParentNode);
    ASSERT_EQ(" 2 10", _root->getMap());
    ASSERT_EQ("New Parent Node", _model.findNode("10")->getDescription());
    _model.revertInsertParentNode(networkNode, newParentNode, oldParentNode);
    assertTestMindMap();
}

TEST_F(MindMapModelTest, insertChildNode)
{
    // No New Logic
}

TEST_F(MindMapModelTest, insertSiblingNode)
{
    // No New Logic
}

TEST_F(MindMapModelTest, editNodeDescription)
{
    // No New Logic
}

TEST_F(MindMapModelTest, changeNodeParent)
{
    testChangeParentUnderTheNode();
    testChangeParentNotUnderNode();
}

TEST_F(MindMapModelTest, deleteNode)
{
    createTestMindMap();
    Component* networkNode = _model.findNode("7");
    Component* officeNode = _model.findNode("6");
    _model.deleteNode(networkNode);
    ASSERT_EQ(NULL, _model.findNode("7"));
    ASSERT_EQ(" 2 8 9", _root->getMap());
    _model.deleteNode(officeNode);
    ASSERT_EQ(NULL, _model.findNode("6"));
    ASSERT_EQ(" 5", _model.findNode("1")->getMap());
    // Revert Delete Node
    _model.revertDeleteNode(networkNode);
    ASSERT_TRUE(_model.findNode("7") != NULL);
    _model.revertDeleteNode(officeNode);
    ASSERT_TRUE(_model.findNode("6") != NULL);
    assertTestMindMap();
}

TEST_F(MindMapModelTest, revertDeleteNode)
{
    createTestMindMap();
    Component* networkNode = _model.findNode("7");
    _model.deleteNode(networkNode);
}

TEST_F(MindMapModelTest, saveAndLoadMindMap)
{
    ofstream writeStream(TEST_TEMP_FILE);
    createTestMindMap();
    _model.saveMindMap(&writeStream);
    writeStream.close();
    assertTestMindMap();
    clearMindMap();
    ASSERT_EQ(NULL, _model.getRootNode());
    ifstream readStream(TEST_TEMP_FILE);
    _model.loadMindMap(&readStream);
    assertTestMindMap();
    readStream.close();
}

TEST_F(MindMapModelTest, findNode)
{
    ASSERT_THROW(_model.findNode("0"), string);
    ASSERT_THROW(_model.findNode("1"), string);
    createTestMindMap();
    ASSERT_EQ("Computer", _model.findNode("0")->getDescription());
    ASSERT_EQ("windows", _model.findNode("1")->getDescription());
}