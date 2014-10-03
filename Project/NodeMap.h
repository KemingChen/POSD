#pragma once
using namespace std;

class NodeMap
{
    private:
        string _id;
        string _description;
        string _nodeName;

    public:
        NodeMap(int id);
        string getId();
        string getDescription();
        void setDescription(string description);
        string getNodeName();
        void setNodeName(string nodeName);
        ~NodeMap();
};