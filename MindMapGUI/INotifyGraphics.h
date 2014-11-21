#pragma once
#include "GraphicNode.h"

class INotifyGraphics
{
    public:
        virtual void clickGraphicNode(GraphicNode* node) = 0;
        virtual void doubleClickGraphicNode(GraphicNode* node) = 0;
        virtual void updateActions() = 0;
        virtual void updateGraphics() = 0;
        virtual void notifyError(string description) = 0;
};