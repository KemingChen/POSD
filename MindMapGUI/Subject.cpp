#include "Subject.h"
#include <iostream>

Subject::Subject()
{
}

void Subject::attach(Observer* observer)
{
    _observerList.push_back(observer);
    //cout << "Push " << observer->getName() << endl;
    //cout << _subjectName << " => After attach, Observer Size: " << _observerList.size() << endl;
    //cout << endl;
}

void Subject::detach(Observer* observer)
{
    ObserverList::iterator it = find(_observerList.begin(), _observerList.end(), observer);
    if (it != _observerList.end())
    {
        _observerList.erase(it);
    }
    //cout << _subjectName << " => After detach, Observer Size : " << _observerList.size() << endl;
    //cout << endl;
}

void Subject::notify(int subject, string info)
{
    //cout << "Subject." << this->_subjectName << " Size " << _observerList.size() << endl;
    for (ObserverList::iterator it = _observerList.begin(); it != _observerList.end(); it++)
    {
        //cout << "notify." << (*it)->getName() << endl;
        (*it)->update(subject, info);
    }
    //cout << endl;
}

Subject::~Subject()
{
}