#pragma once
#include "PresentModel.h"

class GUIPresentModel
{
    private:
        PresentModel* _presentModel;

    public:
        GUIPresentModel(PresentModel* presentModel);
        ~GUIPresentModel();
};