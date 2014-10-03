#pragma once
using namespace std;

class NodeMap
{
    private:
        int _id;
        string _description;
        string _nodeName;

    public:
        NodeMap(int id);
        int getId();
        string getDescription();
        void setDescription(string description);
        string getNodeName();
        void setNodeName(string nodeName);
        ~NodeMap();
};