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

MindMapModel::~MindMapModel()
{
}
