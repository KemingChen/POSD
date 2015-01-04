#pragma once
#include <string>
using namespace std;

#define SELECTED_CHANGE "#Selected Change"
#define MODEL_CHANGE "#Model Change"

class Observer
{
    public:
        virtual void update(string subject) = 0;
};