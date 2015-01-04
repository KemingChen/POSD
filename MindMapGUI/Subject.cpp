#include "Subject.h"
#include <iostream>

Subject::Subject()
{
}

void Subject::attach(Observer* observer)
{
    _observerList.push_back(observer);
}

void Subject::detach(Observer* observer)
{
    ObserverList::iterator it = find(_observerList.begin(), _observerList.end(), observer);
    if (it != _observerList.end())
    {
        _observerList.erase(it);
    }
}

void Subject::notify(string subject)
{
    for (ObserverList::iterator it = _observerList.begin(); it != _observerList.end(); it++)
    {
        (*it)->update(subject);
    }
}

Subject::~Subject()
{
}