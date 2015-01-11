#pragma once
#include "IGraphic.h"
#include "Component.h"
#include <QGraphicsScene>

class MindMapGUI;
class GUIPresentModel;
class MindMapPainter : public IGraphic
{
    private:
        QGraphicsScene* _scene;
        MindMapGUI* _guiWindow;
        GUIPresentModel* _presentModel;

        QFont getFont() const;
        QPen getPen() const;

    public:
        MindMapPainter(QGraphicsScene* scene, MindMapGUI* guiWindow, GUIPresentModel* presentModel);
        void calculateTextRectSize(Component* node);
        void drawNode(Component* node);
        void drawRectangle(Rect rect);
        void drawTriangle(Rect rect);
        void drawEllipse(Rect rect);
        ~MindMapPainter();
};