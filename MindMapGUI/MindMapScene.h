#pragma once
#include <QGraphicsScene>
#include "Subject.h"

class MindMapScene : public Subject, public QGraphicsScene
{
    public:
        MindMapScene();
        void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
        ~MindMapScene();
};