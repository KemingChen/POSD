#pragma once
#include <string>
using namespace std;

class MindMapModel
{
    public:
        MindMapModel();
        void createMinMap(string description);
        void insertNode();
        void saveMindMap();
        void createNode();

        ~MindMapModel();
};

