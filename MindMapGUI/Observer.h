#pragma once
#include <string>
using namespace std;

#define SELECTED_CHANGE "#Selected Change"
#define MODEL_CHANGE "#Model Change"
#define CREATE_NEW "#Create New"

class Observer
{
    public:
        virtual void update(string subject) = 0;
};