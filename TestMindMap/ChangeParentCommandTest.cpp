#include "stdafx.h"
#include <gtest\gtest.h>
#include "ChangeParentCommand.h"
#include "MindMapModel.h"

class ChangeParentCommandTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            _oldParentNode = new Node(1, "Old Parent Node");
            _node = new Node(2, "Node");
            _oldParentNode->addChild(_node);
        }

        virtual void TearDown()
        {
        }

        void addChilds(int amount, Component* node)
        {
            for (int i = 0; i < amount; i++)
            {
                node->addChild(new Node(i, "Test Child Node " + to_string(i)));
            }
        }

        MindMapModel _model;
        Component* _oldParentNode;
        Component* _node;
};

TEST_F(ChangeParentCommandTest, newParentIsUnderNode)
{
    addChilds(5, _node);
    Component* newParentNode = new Node(3, "New Parent Node");
    _node->addChild(newParentNode);
    ChangeParentCommand changeParentCommand(&_model, _node, newParentNode);
    ASSERT_TRUE(changeParentCommand._revertOldNodeList);
    ASSERT_EQ(6, changeParentCommand._oldNodeList.size());
}

TEST_F(ChangeParentCommandTest, newParentNotUnderNode)
{
    addChilds(3, _node);
    Component* newParentNode = new Node(3, "New Parent Node");
    _oldParentNode->addChild(newParentNode);
    ChangeParentCommand changeParentCommand(&_model, _node, newParentNode);
    ASSERT_FALSE(changeParentCommand._revertOldNodeList);
    ASSERT_EQ(0, changeParentCommand._oldNodeList.size());
}