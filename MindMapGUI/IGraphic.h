#pragma once
#include "Rect.h"

class Component;
class IGraphic
{
    public:
        virtual void calculateTextRectSize(Component* node) = 0;
        virtual void drawNode(Component* node) = 0;
        virtual void drawRectangle(Rect rect) = 0;
        virtual void drawTriangle(Rect rect) = 0;
        virtual void drawEllipse(Rect rect) = 0;
};