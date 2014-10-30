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

        CommandManager _commandManager;
};

TEST_F(CommandManagerTest, execute)
{
    ASSERT_EQ(0, _commandManager._undoCommands.size());
    ASSERT_EQ(0, _commandManager._redoCommands.size());
    _commandManager.execute(new MockCommand());
    ASSERT_EQ(1, _commandManager._undoCommands.size());
    ASSERT_NE(1, _commandManager._redoCommands.size());
    _commandManager._redoCommands.push(new MockCommand());
    ASSERT_EQ(1, _commandManager._redoCommands.size());
    _commandManager.execute(new MockCommand());
    ASSERT_EQ(2, _commandManager._undoCommands.size());
    ASSERT_EQ(0, _commandManager._redoCommands.size());
}

TEST_F(CommandManagerTest, clear)
{
    createMockCommands(5, &_commandManager._redoCommands);
    createMockCommands(1, &_commandManager._undoCommands);
    ASSERT_EQ(5, _commandManager._redoCommands.size());
    ASSERT_EQ(1, _commandManager._undoCommands.size());
    _commandManager.clear();
    ASSERT_EQ(0, _commandManager._redoCommands.size());
    ASSERT_EQ(0, _commandManager._undoCommands.size());
}

TEST_F(CommandManagerTest, redo)
{
    createMockCommands(2, &_commandManager._redoCommands);
    ASSERT_EQ(2, _commandManager._redoCommands.size());
    ASSERT_EQ(0, _commandManager._undoCommands.size());
    _commandManager.redo();
    ASSERT_EQ(1, _commandManager._redoCommands.size());
    ASSERT_EQ(1, _commandManager._undoCommands.size());
    _commandManager.redo();
    ASSERT_EQ(0, _commandManager._redoCommands.size());
    ASSERT_EQ(2, _commandManager._undoCommands.size());
    ASSERT_THROW(_commandManager.redo(), string);
}

TEST_F(CommandManagerTest, undo)
{
    createMockCommands(2, &_commandManager._undoCommands);
    ASSERT_EQ(2, _commandManager._undoCommands.size());
    ASSERT_EQ(0, _commandManager._redoCommands.size());
    _commandManager.undo();
    ASSERT_EQ(1, _commandManager._undoCommands.size());
    ASSERT_EQ(1, _commandManager._redoCommands.size());
    _commandManager.undo();
    ASSERT_EQ(0, _commandManager._undoCommands.size());
    ASSERT_EQ(2, _commandManager._redoCommands.size());
    ASSERT_THROW(_commandManager.undo(), string);
}