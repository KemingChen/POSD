#include "stdafx.h"
#include "NodeMap.h"

NodeMap::NodeMap(int id)
{
    _id = to_string(id);
}

string NodeMap::getId()
{
    return _id;
}

string NodeMap::getDescription()
{
    return _description;
}

void NodeMap::setDescription(string description)
{
    _description = description;
}

string NodeMap::getTypeName()
{
    return _nodeName;
}

void NodeMap::setTypeName(string name)
{
    _nodeName = name;
}

string NodeMap::toString()
{
    string output;
    output += "¡Ï¡Ð " + _description;
    output += " (" + _nodeName + ", ID: " + _id + ")";
    return output;
}

NodeMap::~NodeMap()
{
}