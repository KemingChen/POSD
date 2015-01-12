#include "stdafx.h"
#include <gtest\gtest.h>
#include "PresentModel.h"
#include <fstream>
#define TEST_DATA_DIR "testdata"
#define TEST_FILE "testdata/test_file1.mm"

class IntegrationTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            _mkdir(TEST_DATA_DIR);
            createTestFile();
            _model = new MindMapModel();
            _presentModel = new PresentModel(_model);
        }

        virtual void TearDown()
        {
            remove(TEST_FILE);
            _rmdir(TEST_DATA_DIR);
        }

        void createTestFile()
        {
            ofstream writeStream(TEST_FILE);
            writeStream << "0 0 Computer ##2#7# ##" << endl;
            writeStream << "1 1 windows ##5#6# ##" << endl;
            writeStream << "2 1 OS ##1#3#4# ##" << endl;
            writeStream << "3 1 IOS ## ##" << endl;
            writeStream << "4 1 Linux ## ##" << endl;
            writeStream << "5 1 DirectX ## ##" << endl;
            writeStream << "6 1 Microsoft&nbsp;Office ## ##" << endl;
            writeStream << "7 -1 Network ##8#9# ##" << endl;
            writeStream << "8 -1 Wireless ## ##" << endl;
            writeStream << "9 -1 Cable ## ##" << endl;
            writeStream.close();
        }

        void assertTestMindMap()
        {
            ASSERT_EQ("#2#7", _model->findNode(0)->getMap());
            ASSERT_EQ("#5#6", _model->findNode(1)->getMap());
            ASSERT_EQ("#1#3#4", _model->findNode(2)->getMap());
            ASSERT_EQ("", _model->findNode(3)->getMap());
            ASSERT_EQ("", _model->findNode(4)->getMap());
            ASSERT_EQ("", _model->findNode(5)->getMap());
            ASSERT_EQ("", _model->findNode(6)->getMap());
            ASSERT_EQ("#8#9", _model->findNode(7)->getMap());
            ASSERT_EQ("", _model->findNode(8)->getMap());
            ASSERT_EQ("", _model->findNode(9)->getMap());
        }

        MindMapModel* _model;
        PresentModel* _presentModel;
};

TEST_F(IntegrationTest, testLoadFileNotExist)
{
    ASSERT_THROW(_presentModel->loadMindMap("file_not_exist.erd"), string);
}

TEST_F(IntegrationTest, testUndoDeleteNode)
{
    _presentModel->loadMindMap(TEST_FILE);
    assertTestMindMap();
    Component* linuxNode = _presentModel->tryFindNode("4");
    _presentModel->insertChildNode(linuxNode, "Test");
    ASSERT_EQ("Test", _presentModel->tryFindNode("10")->getDescription());
    Component* testNode = _presentModel->tryFindNode("10");
    _presentModel->deleteNode(testNode);
    ASSERT_THROW(_presentModel->tryFindNode("10"), string);
    _presentModel->undo();
    ASSERT_EQ("Test", _presentModel->tryFindNode("10")->getDescription());
}

TEST_F(IntegrationTest, testRedoDeleteNode)
{
    _presentModel->loadMindMap(TEST_FILE);
    assertTestMindMap();
    Component* cableNode = _presentModel->tryFindNode("9");
    _presentModel->insertChildNode(cableNode, "Test");
    ASSERT_EQ("Test", _presentModel->tryFindNode("10")->getDescription());
    Component* testNode = _presentModel->tryFindNode("10");
    _presentModel->deleteNode(testNode);
    ASSERT_THROW(_presentModel->tryFindNode("10"), string);
    _presentModel->undo();
    ASSERT_EQ("Test", _presentModel->tryFindNode("10")->getDescription());
    _presentModel->redo();
    ASSERT_THROW(_presentModel->tryFindNode("10"), string);
}

TEST_F(IntegrationTest, testChangeNodeParent)
{
    _presentModel->loadMindMap(TEST_FILE);
    assertTestMindMap();
    Component* windowsNode = _presentModel->tryFindNode("1");
    Component* microsoftNode = _presentModel->tryFindNode("6");
    _presentModel->changeNodeParent(windowsNode, microsoftNode);
    ASSERT_EQ("Microsoft Office", windowsNode->getParent()->getDescription());
    ASSERT_EQ("OS", microsoftNode->getParent()->getDescription());
    _presentModel->undo();
    ASSERT_EQ("OS", windowsNode->getParent()->getDescription());
    ASSERT_EQ("windows", microsoftNode->getParent()->getDescription());
    _presentModel->redo();
    ASSERT_EQ("Microsoft Office", windowsNode->getParent()->getDescription());
    ASSERT_EQ("OS", microsoftNode->getParent()->getDescription());
}