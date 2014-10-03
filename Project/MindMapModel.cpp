#include "stdafx.h"
#include "MindMapModel.h"

MindMapModel::MindMapModel()
{
}

void MindMapModel::createMinMap(string description)
{
    _root = new Root();
    _root->setDescription(description);
}

Component* MindMapModel::getRootNode()
{
    return _root;
}

MindMapModel::~MindMapModel()
{
}
