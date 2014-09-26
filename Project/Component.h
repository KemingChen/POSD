#pragma once

class Component
{
    protected:
        // Protected Variable
        string _description;

    public:
        // Public Method
        Component();
        void setDescription(string description);
        string getDescription();
        virtual ~Component();
};

