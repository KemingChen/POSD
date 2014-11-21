#pragma once
#include <QGraphicsScene>
#include "GraphicNode.h"

class INotifyGraphics;
class MindMapScene : public QGraphicsScene
{
    private:
        INotifyGraphics* _notify;

    public:
        MindMapScene(INotifyGraphics* notify);
        void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
        ~MindMapScene();
};