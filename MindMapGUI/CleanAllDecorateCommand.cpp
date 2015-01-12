#include "CleanAllDecorateCommand.h"

CleanAllDecorateCommand::CleanAllDecorateCommand(MindMapModel* model, Component* node)
{
    this->_model = model;
    this->_node = node;
}

void CleanAllDecorateCommand::execute()
{
    this->_model->removeDecorate(this->_node->getRealComponent());
}

void CleanAllDecorateCommand::unexecute()
{
    this->_model->addDecorate(this->_node, this->_node->getRealComponent());
}

CleanAllDecorateCommand::~CleanAllDecorateCommand()
{
}