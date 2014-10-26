#include "stdafx.h"
#include <gtest\gtest.h>

class NodeTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            _node = new Node(1, "Windows");
        }

        virtual void TearDown()
        {
        }

        Component* _node;
};

//void setParent(Component* node);
//Component* getParent();
//string toString();
//virtual list<int>* getMap() = 0;
//virtual void addChild(Component* node) = 0;
//virtual void removeChild(Component* node) = 0;
//virtual void removeAllChild() = 0;
//virtual void addParent(Component* node) = 0;
//virtual void addSibling(Component* node) = 0;
//virtual bool isSelfAreParentLastNode() = 0;
//virtual NodeList* getNodeList() = 0;

TEST_F(NodeTest, getId)
{
    ASSERT_EQ("1", _node->getId());
    ASSERT_NE("2", _node->getId());
}

TEST_F(NodeTest, setId)
{
    ASSERT_EQ("1", _node->_id);
    _node->setId(2);
    ASSERT_NE("1", _node->_id);
    ASSERT_EQ("2", _node->_id);
}

TEST_F(NodeTest, getDescription)
{
    ASSERT_EQ("Windows", _node->getDescription());
    ASSERT_NE("Windows2", _node->getDescription());
}

TEST_F(NodeTest, setDescription)
{
    ASSERT_EQ("Windows", _node->_description);
    _node->setDescription("Windows 7");
    ASSERT_EQ("Windows 7", _node->_description);
    ASSERT_NE("Windows", _node->_description);
}

TEST_F(NodeTest, getTypeName)
{
    ASSERT_EQ("Node", _node->getTypeName());
    ASSERT_NE("Root", _node->getTypeName());
}