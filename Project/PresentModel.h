#pragma once
#include "MindMapModel.h"

class PresentModel
{
    private:
        // private variable
        MindMapModel* _model;

        // private method
        string getNodeMap(Component* node, string prefix, bool isParentAreLastNode);

    public:
        // public method
        PresentModel(MindMapModel* model);
        MindMapModel* getModel();
        string getMindMap(Component* root);
        void saveMindMap();
        ~PresentModel();
};