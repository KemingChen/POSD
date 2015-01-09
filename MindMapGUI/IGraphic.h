#pragma once

class Component;
class IGraphic
{
    public:
        virtual void calculateTextRectSize(Component* node) = 0;
        virtual void drawGraphicNode(Component* node) = 0;
};