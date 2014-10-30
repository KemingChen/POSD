#include "stdafx.h"
#include <gtest\gtest.h>
#include "CommandManager.h"
#include "MockCommand.h"

class CommandManagerTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
        }

        virtual void TearDown()
        {
        }

        void createMockCommands(int amount, stack<Command*>* stack)
        {
            for (int i = 0; i < amount; i++)
            {
                stack->push(new MockCommand());
            }
        }

        CommandManager commandManager;
};

TEST_F(CommandManagerTest, execute)
{
    ASSERT_EQ(0, commandManager._undoCommands.size());
    ASSERT_EQ(0, commandManager._redoCommands.size());
    commandManager.execute(new MockCommand());
    ASSERT_EQ(1, commandManager._undoCommands.size());
    ASSERT_NE(1, commandManager._redoCommands.size());
    commandManager._redoCommands.push(new MockCommand());
    ASSERT_EQ(1, commandManager._redoCommands.size());
    commandManager.execute(new MockCommand());
    ASSERT_EQ(2, commandManager._undoCommands.size());
    ASSERT_EQ(0, commandManager._redoCommands.size());
}

TEST_F(CommandManagerTest, clear)
{
    createMockCommands(5, &commandManager._redoCommands);
    createMockCommands(1, &commandManager._undoCommands);
    ASSERT_EQ(5, commandManager._redoCommands.size());
    ASSERT_EQ(1, commandManager._undoCommands.size());
    commandManager.clear();
    ASSERT_EQ(0, commandManager._redoCommands.size());
    ASSERT_EQ(0, commandManager._undoCommands.size());
}

TEST_F(CommandManagerTest, redo)
{
    createMockCommands(2, &commandManager._redoCommands);
    ASSERT_EQ(2, commandManager._redoCommands.size());
    ASSERT_EQ(0, commandManager._undoCommands.size());
    commandManager.redo();
    ASSERT_EQ(1, commandManager._redoCommands.size());
    ASSERT_EQ(1, commandManager._undoCommands.size());
    commandManager.redo();
    ASSERT_EQ(0, commandManager._redoCommands.size());
    ASSERT_EQ(2, commandManager._undoCommands.size());
    ASSERT_THROW(commandManager.redo(), string);
}

TEST_F(CommandManagerTest, undo)
{
    createMockCommands(2, &commandManager._undoCommands);
    ASSERT_EQ(2, commandManager._undoCommands.size());
    ASSERT_EQ(0, commandManager._redoCommands.size());
    commandManager.undo();
    ASSERT_EQ(1, commandManager._undoCommands.size());
    ASSERT_EQ(1, commandManager._redoCommands.size());
    commandManager.undo();
    ASSERT_EQ(0, commandManager._undoCommands.size());
    ASSERT_EQ(2, commandManager._redoCommands.size());
    ASSERT_THROW(commandManager.undo(), string);
}