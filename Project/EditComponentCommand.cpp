#include "stdafx.h"
#include "EditComponentCommand.h"

EditComponentCommand::EditComponentCommand(MindMapModel* model, Component* node, string description) : Command(_model)
{
    _model = model;
    _node = node;
    _newDescription = description;
    _oldDescription = node->getDescription();
}

void EditComponentCommand::execute()
{
    _model->editNodeDescription(_node, _newDescription);
}

void EditComponentCommand::unexecute()
{
    _model->editNodeDescription(_node, _oldDescription);
}

EditComponentCommand::~EditComponentCommand()
{
}