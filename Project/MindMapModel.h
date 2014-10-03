#pragma once
#include <map>
using namespace std;

class MindMapModel
{
    private:
        typedef map<string, void (MindMapModel::*)(Component*, Component*)> InsertActionMap;

        // Private Variable
        int _createId = 0;
        Component* _root;
        InsertActionMap _insertActionMap;

        // Private Method
        Component* findNode(Component* node, string id);
        void insertParentNode(Component* parent, Component* node);
        void insertChildNode(Component* parent, Component* node);
        void insertSiblingNode(Component* parent, Component* node);
        void navigateMindMap(Component* node, string* list);
        string convertIntArrayToString(list<int>* intList);

    public:
        // Public Method
        MindMapModel();
        void createMinMap(string description);
        Component* insertNode(string id, string action) throw (string);
        void saveMindMap();
        void createNode();
        Component* getRootNode();
        ~MindMapModel();
};