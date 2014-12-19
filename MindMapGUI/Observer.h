#pragma once
#include <string>
using namespace std;

class Observer
{
    protected:
        string _name;

    public:
        Observer();
        string getName();
        virtual void update(int subject, string info);
        ~Observer();
};