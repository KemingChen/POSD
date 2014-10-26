#include "stdafx.h"
#include <gtest\gtest.h>
#include "ComponentFactory.h"

class ComponentFactoryTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            factory = ComponentFactory::getInstance();
        }

        virtual void TearDown()
        {
        }

        ComponentFactory* factory;
};

TEST_F(ComponentFactoryTest, createComponent)
{
    for (int i = 0; i < 2; i++)
    {
        Component* root = factory->createComponent(ROOT, "Computer");
        Component* nodeOS = factory->createComponent(NODE, "OS");
        Component* nodeWindows = factory->createComponent(NODE, "Windows");
        ASSERT_EQ("Root", root->getTypeName());
        ASSERT_EQ("0", root->getId());
        ASSERT_EQ("Computer", root->getDescription());
        ASSERT_EQ("Node", nodeOS->getTypeName());
        ASSERT_EQ("1", nodeOS->getId());
        ASSERT_EQ("OS", nodeOS->getDescription());
        ASSERT_EQ("Node", nodeWindows->getTypeName());
        ASSERT_EQ("2", nodeWindows->getId());
        ASSERT_EQ("Windows", nodeWindows->getDescription());
    }
}