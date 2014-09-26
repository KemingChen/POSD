#pragma once
#include "Component.h"
#include "Root.h"
#include "Node.h"

class MindMapModel
{
    private:
        // Private Variable
        Component* _root;

    public:
        // Public Method
        MindMapModel();
        void createMinMap(string description);
        void insertNode();
        void saveMindMap();
        void createNode();

        ~MindMapModel();
};

