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

    public:
        MindMapPainter(QGraphicsScene* scene, MindMapGUI* guiWindow, GUIPresentModel* presentModel);
        QFont getFont() const;
        int getFlags() const;
        void calculateTextRectSize(Component* node);
        void drawGraphicNode(Component* node);
        ~MindMapPainter();
};