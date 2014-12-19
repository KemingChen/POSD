#pragma once
#include <string>
using namespace std;

class Observer
{
    public:
        Observer();
        virtual void update(int subject, string info);
        ~Observer();
};