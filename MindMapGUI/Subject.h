#pragma once
#include "Observer.h"
#include <vector>
#include <algorithm>

#define SUBJECT_CLICK 0
#define SUBJECT_DB_CLICK 1
#define SUBJECT_RESET_SCENE 2
#define SUBJECT_MODEL_CHANGE 3
#define SUBJECT_PMODEL_CHANGE 4
#define SUBJECT_ERROR 5

class Subject
{
    private:
        typedef std::vector<Observer*> ObserverList;
        ObserverList _observerList;

    public:
        Subject();
        void attach(Observer* observer);
        void detach(Observer* observer);
        void notify(int subject, string info);
        ~Subject();
};