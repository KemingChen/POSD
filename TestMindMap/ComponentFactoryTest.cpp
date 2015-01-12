#include "stdafx.h"
#include <gtest\gtest.h>
#include "ComponentFactory.h"

class ComponentFactoryTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            _factory = ComponentFactory::getInstance();
        }

        virtual void TearDown()
        {
        }

        ComponentFactory* _factory;
};

TEST_F(ComponentFactoryTest, createComponent)
{
    for (int i = 0; i < 2; i++)
    {
        Component* root = _factory->createComponent(ComponentType::ROOT, "Computer");
        Component* nodeOS = _factory->createComponent(ComponentType::NODE, "OS");
        Component* nodeWindows = _factory->createComponent(ComponentType::NODE, "Windows");
        ASSERT_EQ("Root", root->getTypeName());
        ASSERT_EQ(0, root->getId());
        ASSERT_EQ("Computer", root->getDescription());
        ASSERT_EQ("Node", nodeOS->getTypeName());
        ASSERT_EQ(1, nodeOS->getId());
        ASSERT_EQ("OS", nodeOS->getDescription());
        ASSERT_EQ("Node", nodeWindows->getTypeName());
        ASSERT_EQ(2, nodeWindows->getId());
        ASSERT_EQ("Windows", nodeWindows->getDescription());
    }
}

TEST_F(ComponentFactoryTest, createDecorate)
{
    for (int i = 0; i < 2; i++)
    {
        Component* root = _factory->createComponent(ComponentType::ROOT, "Computer");
        Component* node = _factory->createComponent(ComponentType::NODE, "Node");
        Component* ellipse = _factory->createDecorate("Ellipse", root);
        Component* triangle = _factory->createDecorate("Triangle", ellipse);
        Component* rectangle = _factory->createDecorate("Rectangle", triangle);
        ellipse->addChild(node);
        rectangle->removeChild(node);
        triangle->addChild(node);
        rectangle->removeAllChild();
        ASSERT_EQ("Ellipse", ellipse->getTypeName());
        ASSERT_EQ("Triangle", triangle->getTypeName());
        ASSERT_EQ("Rectangle", rectangle->getTypeName());
        ASSERT_EQ("Computer", rectangle->getRealComponent()->getDescription());
    }
}