#include "PasteNodeCommand.h"

PasteNodeCommand::PasteNodeCommand(MindMapModel* model, Component* selectedNode, Component* cloneNode)
{
    _model = model;
    _selectedNode = selectedNode;
    _cloneNode = cloneNode;
    _pasteNode = cloneNode->clone();
}

void PasteNodeCommand::execute()
{
    _model->pasteNode(_selectedNode, _pasteNode);
}

void PasteNodeCommand::unexecute()
{
    _selectedNode->removeChild(_pasteNode);
}

PasteNodeCommand::~PasteNodeCommand()
{
}