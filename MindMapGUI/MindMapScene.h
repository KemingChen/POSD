#pragma once
#include <QGraphicsScene>
#include "Subject.h"

class MindMapScene : public QGraphicsScene
{
    public:
        MindMapScene();
        void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
        ~MindMapScene();
};