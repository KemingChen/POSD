#pragma once
#include <QGraphicsScene>
#include "Subject.h"
#include "GUIPresentModel.h"

class MindMapScene : public QGraphicsScene
{
    private:
        GUIPresentModel* _presentModel;

    public:
        MindMapScene(GUIPresentModel* presentModel);
        void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
        ~MindMapScene();
};