#include "Observer.h"

Observer::Observer()
{
}

string Observer::getName()
{
    return _name;
}

void Observer::update(int subject, string info)
{
    // do nothing
}

Observer::~Observer()
{
}