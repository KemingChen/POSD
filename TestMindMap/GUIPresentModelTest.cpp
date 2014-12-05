#include "stdafx.h"
#include <gtest\gtest.h>
#include "PresentModel.h"
#include "GUIPresentModel.h"
#include "MockCommand.h"
#include "MockINotifyGraphic.h"
#include <thread>
#include <chrono>

class GUIPresentModelTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            _model = new MindMapModel();
            _presentModel = new PresentModel(_model);
            _guiPresentModel = new GUIPresentModel(_presentModel, &_iNotify);
        }

        void createMindMap()
        {
            _model->createMinMap("Root");
            _model->insertChildNode(_model->getRootNode(), new Node(1, "Node1"));
            _model->insertChildNode(_model->getRootNode(), new Node(2, "Node2"));
        }

        void sleep()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        virtual void TearDown()
        {
        }

        MindMapModel* _model;
        PresentModel* _presentModel;
        GUIPresentModel* _guiPresentModel;
        MockINotifyGraphic _iNotify;
};

TEST_F(GUIPresentModelTest, editDescription)
{
    createMindMap();
    Component* node = _model->findNode("0");
    _guiPresentModel->clickGraphicNode(node);

    _guiPresentModel->editDescription("", false);
    ASSERT_EQ(node->getDescription(), "Root");

    _guiPresentModel->editDescription("NewRoot", false);
    ASSERT_EQ(node->getDescription(), "Root");

    _iNotify.getInfo();
    _guiPresentModel->editDescription("", true);
    ASSERT_EQ(_iNotify.getInfo(), "ERROR: Description is Empty!!!; ");
    ASSERT_EQ(node->getDescription(), "Root");

    _iNotify.getInfo();
    _guiPresentModel->editDescription("NewRoot", true);
    ASSERT_EQ(_iNotify.getInfo(), "UPDATE_GRAPHICS; ");
    ASSERT_EQ(node->getDescription(), "NewRoot");
}

TEST_F(GUIPresentModelTest, loadMindMap)
{
    _guiPresentModel->loadMindMap("");
    ASSERT_FALSE(_guiPresentModel->isCreatedMindMap());
}

TEST_F(GUIPresentModelTest, saveMindMap)
{
    createMindMap();
    _guiPresentModel->saveMindMap("file__exist.mm");
    ASSERT_TRUE(_guiPresentModel->isCreatedMindMap());
}

TEST_F(GUIPresentModelTest, createMindMap)
{
    _guiPresentModel->createMindMap("", false);
    ASSERT_FALSE(_guiPresentModel->isCreatedMindMap());

    _guiPresentModel->createMindMap("Hello", false);
    ASSERT_FALSE(_guiPresentModel->isCreatedMindMap());

    _iNotify.getInfo();
    _guiPresentModel->createMindMap("", true);
    ASSERT_EQ(_iNotify.getInfo(), "ERROR: Description is Empty!!!; ");
    ASSERT_FALSE(_guiPresentModel->isCreatedMindMap());

    _iNotify.getInfo();
    _guiPresentModel->createMindMap("Hello", true);
    ASSERT_EQ(_iNotify.getInfo(), "SETUP_SCENE; UPDATE_ACTIONS; UPDATE_GRAPHICS; ");
    ASSERT_TRUE(_guiPresentModel->isCreatedMindMap());
}

TEST_F(GUIPresentModelTest, insertParentNode)
{
    createMindMap();
    _guiPresentModel->clickGraphicNode(_model->findNode("1"));

    _iNotify.getInfo();
    _guiPresentModel->insertParentNode("", false);
    ASSERT_EQ(_iNotify.getInfo(), "");

    _iNotify.getInfo();
    _guiPresentModel->insertParentNode("Hello", false);
    ASSERT_EQ(_iNotify.getInfo(), "");

    _iNotify.getInfo();
    _guiPresentModel->insertParentNode("", true);
    ASSERT_EQ(_iNotify.getInfo(), "ERROR: Description is Empty!!!; ");

    _iNotify.getInfo();
    _guiPresentModel->insertParentNode("Hello", true);
    ASSERT_EQ(_iNotify.getInfo(), "UPDATE_GRAPHICS; ");
}

TEST_F(GUIPresentModelTest, insertChildNode)
{
    createMindMap();
    _guiPresentModel->clickGraphicNode(_model->findNode("1"));

    _iNotify.getInfo();
    _guiPresentModel->insertChildNode("", false);
    ASSERT_EQ(_iNotify.getInfo(), "");

    _iNotify.getInfo();
    _guiPresentModel->insertChildNode("Hello", false);
    ASSERT_EQ(_iNotify.getInfo(), "");

    _iNotify.getInfo();
    _guiPresentModel->insertChildNode("", true);
    ASSERT_EQ(_iNotify.getInfo(), "ERROR: Description is Empty!!!; ");

    _iNotify.getInfo();
    _guiPresentModel->insertChildNode("Hello", true);
    ASSERT_EQ(_iNotify.getInfo(), "UPDATE_GRAPHICS; ");
}

TEST_F(GUIPresentModelTest, insertSiblingNode)
{
    createMindMap();
    _guiPresentModel->clickGraphicNode(_model->findNode("1"));

    _iNotify.getInfo();
    _guiPresentModel->insertSiblingNode("", false);
    ASSERT_EQ(_iNotify.getInfo(), "");

    _iNotify.getInfo();
    _guiPresentModel->insertSiblingNode("Hello", false);
    ASSERT_EQ(_iNotify.getInfo(), "");

    _iNotify.getInfo();
    _guiPresentModel->insertSiblingNode("", true);
    ASSERT_EQ(_iNotify.getInfo(), "ERROR: Description is Empty!!!; ");

    _iNotify.getInfo();
    _guiPresentModel->insertSiblingNode("Hello", true);
    ASSERT_EQ(_iNotify.getInfo(), "UPDATE_GRAPHICS; ");
}

TEST_F(GUIPresentModelTest, deleteNode)
{
    createMindMap();
    _guiPresentModel->clickGraphicNode(_model->findNode("1"));

    _iNotify.getInfo();
    _guiPresentModel->deleteNode();
    ASSERT_EQ(_iNotify.getInfo(), "UPDATE_ACTIONS; UPDATE_GRAPHICS; ");
    ASSERT_FALSE(_guiPresentModel->isSelected());
}

TEST_F(GUIPresentModelTest, isSaveEnable)
{
    ASSERT_FALSE(_guiPresentModel->isSaveEnable());
    _guiPresentModel->createMindMap("Hello", true);
    ASSERT_TRUE(_guiPresentModel->isSaveEnable());
}

TEST_F(GUIPresentModelTest, isSelected)
{
    ASSERT_FALSE(_guiPresentModel->isSelected());
    createMindMap();
    ASSERT_FALSE(_guiPresentModel->isSelected());

    _guiPresentModel->clickGraphicNode(_model->findNode("0"));
    ASSERT_TRUE(_guiPresentModel->isSelected());

    sleep();
    _guiPresentModel->clickGraphicNode(_model->findNode("1"));
    ASSERT_TRUE(_guiPresentModel->isSelected());

    sleep();
    _guiPresentModel->clickGraphicNode(NULL);
    ASSERT_FALSE(_guiPresentModel->isSelected());
}

TEST_F(GUIPresentModelTest, isEditNodeEnable)
{
    ASSERT_FALSE(_guiPresentModel->isEditNodeEnable());
    createMindMap();
    ASSERT_FALSE(_guiPresentModel->isEditNodeEnable());

    _guiPresentModel->clickGraphicNode(_model->findNode("0"));
    ASSERT_TRUE(_guiPresentModel->isEditNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(_model->findNode("1"));
    ASSERT_TRUE(_guiPresentModel->isEditNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(NULL);
    ASSERT_FALSE(_guiPresentModel->isEditNodeEnable());
}

TEST_F(GUIPresentModelTest, isDeleteNodeEnable)
{
    ASSERT_FALSE(_guiPresentModel->isDeleteNodeEnable());
    createMindMap();
    ASSERT_FALSE(_guiPresentModel->isDeleteNodeEnable());

    _guiPresentModel->clickGraphicNode(_model->findNode("0"));
    ASSERT_FALSE(_guiPresentModel->isDeleteNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(_model->findNode("1"));
    ASSERT_TRUE(_guiPresentModel->isDeleteNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(NULL);
    ASSERT_FALSE(_guiPresentModel->isDeleteNodeEnable());
}

TEST_F(GUIPresentModelTest, isInsertParentNodeEnable)
{
    ASSERT_FALSE(_guiPresentModel->isInsertParentNodeEnable());
    createMindMap();
    ASSERT_FALSE(_guiPresentModel->isInsertParentNodeEnable());

    _guiPresentModel->clickGraphicNode(_model->findNode("0"));
    ASSERT_FALSE(_guiPresentModel->isInsertParentNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(_model->findNode("1"));
    ASSERT_TRUE(_guiPresentModel->isInsertParentNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(NULL);
    ASSERT_FALSE(_guiPresentModel->isInsertParentNodeEnable());
}

TEST_F(GUIPresentModelTest, isInsertChildNodeEnable)
{
    ASSERT_FALSE(_guiPresentModel->isInsertChildNodeEnable());
    createMindMap();
    ASSERT_FALSE(_guiPresentModel->isInsertChildNodeEnable());

    _guiPresentModel->clickGraphicNode(_model->findNode("0"));
    ASSERT_TRUE(_guiPresentModel->isInsertChildNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(_model->findNode("1"));
    ASSERT_TRUE(_guiPresentModel->isInsertChildNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(NULL);
    ASSERT_FALSE(_guiPresentModel->isInsertChildNodeEnable());
}

TEST_F(GUIPresentModelTest, isInsertSiblingNodeEnable)
{
    ASSERT_FALSE(_guiPresentModel->isInsertSiblingNodeEnable());
    createMindMap();
    ASSERT_FALSE(_guiPresentModel->isInsertSiblingNodeEnable());

    _guiPresentModel->clickGraphicNode(_model->findNode("0"));
    ASSERT_FALSE(_guiPresentModel->isInsertSiblingNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(_model->findNode("1"));
    ASSERT_TRUE(_guiPresentModel->isInsertSiblingNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(NULL);
    ASSERT_FALSE(_guiPresentModel->isInsertSiblingNodeEnable());
}

TEST_F(GUIPresentModelTest, isCutNodeEnable)
{
    ASSERT_FALSE(_guiPresentModel->isCutNodeEnable());
    createMindMap();
    ASSERT_FALSE(_guiPresentModel->isCutNodeEnable());

    _guiPresentModel->clickGraphicNode(_model->findNode("0"));
    ASSERT_FALSE(_guiPresentModel->isCutNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(_model->findNode("1"));
    ASSERT_TRUE(_guiPresentModel->isCutNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(NULL);
    ASSERT_FALSE(_guiPresentModel->isCutNodeEnable());
}

TEST_F(GUIPresentModelTest, isCopyNodeEnable)
{
    ASSERT_FALSE(_guiPresentModel->isCopyNodeEnable());
    createMindMap();
    ASSERT_FALSE(_guiPresentModel->isCopyNodeEnable());

    _guiPresentModel->clickGraphicNode(_model->findNode("0"));
    ASSERT_FALSE(_guiPresentModel->isCopyNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(_model->findNode("1"));
    ASSERT_TRUE(_guiPresentModel->isCopyNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(NULL);
    ASSERT_FALSE(_guiPresentModel->isCopyNodeEnable());
}

TEST_F(GUIPresentModelTest, isPasteNodeEnable)
{
    ASSERT_FALSE(_guiPresentModel->isPasteNodeEnable());
    createMindMap();
    ASSERT_FALSE(_guiPresentModel->isPasteNodeEnable());

    _guiPresentModel->clickGraphicNode(_model->findNode("0"));
    ASSERT_FALSE(_guiPresentModel->isPasteNodeEnable());

    sleep();
    _guiPresentModel->clickGraphicNode(_model->findNode("1"));
    ASSERT_FALSE(_guiPresentModel->isPasteNodeEnable());

    _guiPresentModel->copyNode();
    ASSERT_TRUE(_guiPresentModel->isPasteNodeEnable());

    _guiPresentModel->cutNode();
    ASSERT_FALSE(_guiPresentModel->isPasteNodeEnable());
    sleep();
    _guiPresentModel->clickGraphicNode(_model->findNode("0"));
    ASSERT_TRUE(_guiPresentModel->isPasteNodeEnable());
}