#pragma once

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
        Component* getRootNode();
        ~MindMapModel();
};