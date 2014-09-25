#pragma once
#include "MindMapModel.h"

class TextUI
{
        MindMapModel* _model;

    public:
        TextUI(MindMapModel* model);
        void run();
        ~TextUI();
};

