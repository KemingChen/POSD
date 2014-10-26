#include "stdafx.h"
#include <gtest\gtest.h>

class NodeTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            Component* root = new Root(0, "MindMap Root");
            root->addChild(_node = new Node(1, "Windows"));
        }

        virtual void TearDown()
        {
        }

        Component* _node;
};

TEST_F(NodeTest, setId)
{
    ASSERT_EQ("1", _node->getId());
    _node->setId(2);
    ASSERT_NE("1", _node->getId());
    ASSERT_EQ("2", _node->getId());
}

TEST_F(NodeTest, setDescription)
{
    ASSERT_EQ("Windows", _node->getDescription());
    _node->setDescription("Windows 7");
    ASSERT_EQ("Windows 7", _node->getDescription());
    ASSERT_NE("Windows", _node->getDescription());
}

TEST_F(NodeTest, getTypeName)
{
    ASSERT_EQ("Node", _node->getTypeName());
    ASSERT_NE("Root", _node->getTypeName());
}

TEST_F(NodeTest, setParent)
{
    _node->setParent(new Node(0, "OS"));
    ASSERT_EQ("OS", _node->getParent()->getDescription());
    ASSERT_EQ("0", _node->getParent()->getId());
    _node->setParent(new Node(2, "OS Level"));
    ASSERT_EQ("OS Level", _node->getParent()->getDescription());
    ASSERT_EQ("2", _node->getParent()->getId());
    ASSERT_NE("OS", _node->getParent()->getDescription());
    ASSERT_NE("0", _node->getParent()->getId());
}

TEST_F(NodeTest, toString)
{
    ASSERT_EQ("¡Ï¡Ð Windows (Node, ID: 1)", _node->toString());
    _node->setId(2);
    _node->setDescription("Windows XP");
    ASSERT_EQ("¡Ï¡Ð Windows XP (Node, ID: 2)", _node->toString());
}

TEST_F(NodeTest, getMap)
{
    _node->addChild(new Node(5, "Node5"));
    ASSERT_EQ(" 5", _node->getMap());
    _node->addChild(new Node(4, "Node4"));
    _node->addChild(new Node(3, "Node3"));
    ASSERT_EQ(" 3 4 5", _node->getMap());
}

TEST_F(NodeTest, addChild)
{
    _node->addChild(new Node(2, "Child2"));
    _node->addChild(new Node(3, "Child3"));
    _node->addChild(new Node(4, "Child4"));
    ASSERT_EQ(3, _node->getNodeList()->size());
    _node->addChild(NULL);
    ASSERT_EQ(3, _node->getNodeList()->size());
    _node->addChild(new Node(5, "Child5"));
    ASSERT_EQ(4, _node->getNodeList()->size());
}

TEST_F(NodeTest, removeChild)
{
    Component* prepareRemoveNode;
    _node->addChild(new Node(2, "Child2"));
    _node->addChild(prepareRemoveNode = new Node(3, "Child3"));
    _node->addChild(new Node(4, "Child4"));
    ASSERT_EQ(" 2 3 4", _node->getMap());
    _node->removeChild(prepareRemoveNode);
    ASSERT_NE(" 2 3 4", _node->getMap());
    ASSERT_EQ(" 2 4", _node->getMap());
}

TEST_F(NodeTest, removeAllChild)
{
    _node->addChild(new Node(2, "Child2"));
    _node->addChild(new Node(3, "Child3"));
    _node->addChild(new Node(4, "Child4"));
    ASSERT_EQ(3, _node->getNodeList()->size());
    _node->removeAllChild();
    ASSERT_NE(3, _node->getNodeList()->size());
    ASSERT_EQ(0, _node->getNodeList()->size());
}

TEST_F(NodeTest, addParent)
{
    ASSERT_EQ("MindMap Root", _node->getParent()->getDescription());
    _node->addParent(new Node(2, "Parent"));
    ASSERT_EQ("Parent", _node->getParent()->getDescription());
    _node->addParent(new Node(3, "New Parent"));
    ASSERT_EQ("New Parent", _node->getParent()->getDescription());
    ASSERT_EQ("Parent", _node->getParent()->getParent()->getDescription());
}

TEST_F(NodeTest, addSibling)
{
    ASSERT_EQ("MindMap Root", _node->getParent()->getDescription());
    ASSERT_EQ(" 1", _node->getParent()->getMap());
    _node->addSibling(new Node(3, "Sibling2"));
    ASSERT_EQ(" 1 3", _node->getParent()->getMap());
    _node->addSibling(new Node(2, "Sibling3"));
    ASSERT_EQ(" 1 2 3", _node->getParent()->getMap());
}

TEST_F(NodeTest, isSelfAreParentLastNode)
{
    Component* prepareTestNode;
    ASSERT_TRUE(_node->isSelfAreParentLastNode());
    _node->addSibling(prepareTestNode = new Node(2, "Test"));
    ASSERT_FALSE(_node->isSelfAreParentLastNode());
    ASSERT_TRUE(prepareTestNode->isSelfAreParentLastNode());
    _node->getParent()->removeChild(prepareTestNode);
    ASSERT_TRUE(_node->isSelfAreParentLastNode());
}