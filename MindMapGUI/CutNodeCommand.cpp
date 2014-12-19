#include "CutNodeCommand.h"

CutNodeCommand::CutNodeCommand(MindMapModel* model, Component* node)
{
    _model = model;
    _selectedNode = node;
    _parentNode = _selectedNode->getParent();
    _backFromNode = _selectedNode->getBackFromNode();
}

void CutNodeCommand::execute()
{
    _model->cutNode(_selectedNode);
}

void CutNodeCommand::unexecute()
{
    _parentNode->addChild(_selectedNode, _backFromNode);
}

CutNodeCommand::~CutNodeCommand()
{
}