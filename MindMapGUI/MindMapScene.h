#pragma once
#include <QGraphicsScene>
#include "GraphicNode.h"

class INotifyGraphics;
class MindMapScene : public QGraphicsScene
{
    private:
        INotifyGraphics* _notify;
        QList<GraphicNode*> _list;

    public:
        MindMapScene(INotifyGraphics* notify);
        void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
        void addItem(QGraphicsItem* node);
        void clear();
        ~MindMapScene();
};