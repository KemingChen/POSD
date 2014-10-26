#include "stdafx.h"
#include <gtest\gtest.h>
using namespace std;

class RootTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            _root = new Root(0, "Computer");
        }

        virtual void TearDown()
        {
        }

        Component* _root;
};

TEST_F(RootTest, setId)
{
    ASSERT_EQ("0", _root->getId());
    _root->setId(1);
    ASSERT_NE("0", _root->getId());
    ASSERT_EQ("1", _root->getId());
}

TEST_F(RootTest, setDescription)
{
    ASSERT_EQ("Computer", _root->getDescription());
    _root->setDescription("Windows");
    ASSERT_EQ("Windows", _root->getDescription());
    ASSERT_NE("Computer", _root->getDescription());
}

TEST_F(RootTest, getTypeName)
{
    ASSERT_NE("Node", _root->getTypeName());
    ASSERT_EQ("Root", _root->getTypeName());
}

TEST_F(RootTest, setParent)
{
    ASSERT_THROW(_root->setParent(new Node(0, "OS")), string);
}

TEST_F(RootTest, toString)
{
    ASSERT_EQ("¡Ï¡Ð Computer (Root, ID: 0)", _root->toString());
    _root->setId(1);
    _root->setDescription("Windows");
    ASSERT_EQ("¡Ï¡Ð Windows (Root, ID: 1)", _root->toString());
}

TEST_F(RootTest, getMap)
{
    _root->addChild(new Node(5, "Node5"));
    ASSERT_EQ(" 5", _root->getMap());
    _root->addChild(new Node(4, "Node4"));
    _root->addChild(new Node(3, "Node3"));
    ASSERT_EQ(" 3 4 5", _root->getMap());
}

TEST_F(RootTest, addChild)
{
    _root->addChild(new Node(2, "Child2"));
    _root->addChild(new Node(3, "Child3"));
    _root->addChild(new Node(4, "Child4"));
    ASSERT_EQ(3, _root->getNodeList()->size());
    _root->addChild(NULL);
    ASSERT_EQ(3, _root->getNodeList()->size());
    _root->addChild(new Node(5, "Child5"));
    ASSERT_EQ(4, _root->getNodeList()->size());
}

TEST_F(RootTest, removeChild)
{
    Component* prepareRemoveNode;
    _root->addChild(new Node(2, "Child2"));
    _root->addChild(prepareRemoveNode = new Node(3, "Child3"));
    _root->addChild(new Node(4, "Child4"));
    ASSERT_EQ(" 2 3 4", _root->getMap());
    _root->removeChild(prepareRemoveNode);
    ASSERT_NE(" 2 3 4", _root->getMap());
    ASSERT_EQ(" 2 4", _root->getMap());
}

TEST_F(RootTest, removeAllChild)
{
    _root->addChild(new Node(2, "Child2"));
    _root->addChild(new Node(3, "Child3"));
    _root->addChild(new Node(4, "Child4"));
    ASSERT_EQ(3, _root->getNodeList()->size());
    _root->removeAllChild();
    ASSERT_NE(3, _root->getNodeList()->size());
    ASSERT_EQ(0, _root->getNodeList()->size());
}

TEST_F(RootTest, addParent)
{
    ASSERT_THROW(_root->addParent(new Node(2, "Parent")), string);
}

TEST_F(RootTest, addSibling)
{
    ASSERT_THROW(_root->addSibling(new Node(2, "Sibling")), string);
}

TEST_F(RootTest, isSelfAreParentLastNode)
{
    Component* prepareTestNode;
    ASSERT_TRUE(_root->isSelfAreParentLastNode());
    _root->addChild(prepareTestNode = new Node(2, "Test"));
    ASSERT_TRUE(_root->isSelfAreParentLastNode());
    ASSERT_TRUE(prepareTestNode->isSelfAreParentLastNode());
    _root->removeChild(prepareTestNode);
    ASSERT_TRUE(_root->isSelfAreParentLastNode());
}