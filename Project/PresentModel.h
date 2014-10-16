#pragma once
#include "MindMapModel.h"

class PresentModel
{
    private:
        typedef map<string, void (MindMapModel::*)(Component*, Component*)> InsertActionMap;

        // private variable
        MindMapModel* _model;
        InsertActionMap _insertActionMap;

        // private method
        string getNodeMap(Component* node, string prefix, bool isParentAreLastNode);

    public:
        // public method
        PresentModel(MindMapModel* model);
        MindMapModel* getModel();
        string getMindMap();
        void saveMindMap();
        void loadMindMap(string path);
        void comfirmMindMapExist();
        Component* insertNode(Component* choseNode, string action);
        Component* tryFindNode(string id);
        ~PresentModel();
};