#include "stdafx.h"
#include <iostream>
#include "PresentModel.h"


PresentModel::PresentModel(MindMapModel* model)
{
    _model = model;
}

MindMapModel* PresentModel::getModel()
{
    return _model;
}

PresentModel::~PresentModel()
{
}