#pragma once
#include "Observer.h"
#include <vector>
#include <algorithm>

class Subject
{
    private:
        typedef std::vector<Observer*> ObserverList;
        ObserverList _observerList;

    public:
        Subject();
        void attach(Observer* observer);
        void detach(Observer* observer);
        void notify(string subject);
        ~Subject();
};