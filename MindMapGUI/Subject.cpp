#include "Subject.h"
#include <iostream>

Subject::Subject()
{
}

void Subject::attach(Observer* observer)
{
    _observerList.push_back(observer);
    cout << "After attach, Observer Size: " << _observerList.size() << endl;
}

void Subject::detach(Observer* observer)
{
    ObserverList::iterator it = find(_observerList.begin(), _observerList.end(), observer);
    if (it != _observerList.end())
    {
        _observerList.erase(it);
    }
    cout << "After detach, Observer Size: " << _observerList.size() << endl;
}

void Subject::notify(int subject, string info)
{
    for (ObserverList::iterator it = _observerList.begin(); it != _observerList.end(); it++)
    {
        (*it)->update(subject, info);
    }
}

Subject::~Subject()
{
}