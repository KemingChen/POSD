#include "AddDecorateCommnad.h"
#include "ComponentFactory.h"

AddDecorateCommnad::AddDecorateCommnad(MindMapModel* model, Component* node, ComponentType type)
{
    this->_model = model;
    this->_node = node;
    this->_decorateNode = ComponentFactory::getInstance()->createDecorate(type, node);
}

void AddDecorateCommnad::execute()
{
    this->_model->addDecorate(this->_decorateNode, this->_node);
}

void AddDecorateCommnad::unexecute()
{
    this->_model->removeDecorate(this->_node);
}

AddDecorateCommnad::~AddDecorateCommnad()
{
}