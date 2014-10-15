#pragma once
#include "MindMapModel.h"

class PresentModel
{
    private:
        // private variable
        MindMapModel* _model;

    public:
        // public method
        PresentModel(MindMapModel* model);
        MindMapModel* getModel();
        ~PresentModel();
};