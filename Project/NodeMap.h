#pragma once
using namespace std;

class NodeMap
{
    private:
        string _description;
        string _nodeName;
        int _id;

    public:
        NodeMap(int id);
        int getId();
        string getDescription();
        void setDescription(string description);
        string getNodeName();
        void setNodeName(string nodeName);
        ~NodeMap();
};