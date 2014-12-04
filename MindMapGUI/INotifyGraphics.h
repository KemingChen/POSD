#pragma once
#include "Component.h"

class INotifyGraphics
{
    public:
        virtual void clickGraphicNode(Component* node) = 0;
        virtual void doubleClickGraphicNode(Component* node) = 0;
        virtual void setupScene() = 0;
        virtual void updateActions() = 0;
        virtual void updateGraphics() = 0;
        virtual void notifyError(string description) = 0;
};