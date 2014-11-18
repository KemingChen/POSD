#pragma once
#include "Command.h"
#include "MindMapModel.h"

class ChangeParentCommand : public Command
{
        friend class ChangeParentCommandTest;
        FRIEND_TEST(ChangeParentCommandTest, newParentIsUnderNode);
        FRIEND_TEST(ChangeParentCommandTest, newParentNotUnderNode);

    private:
        Component* _node;
        Component* _newParentNode;
        Component* _oldParentNode;
        MindMapModel* _model;
        NodeList _oldNodeList;
        bool _revertOldNodeList;

    public:
        ChangeParentCommand(MindMapModel* model, Component* node, Component* newParentNode);
        void execute();
        void unexecute();
        ~ChangeParentCommand();
};