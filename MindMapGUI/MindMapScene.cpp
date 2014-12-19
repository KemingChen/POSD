#include "MindMapScene.h"
#include "INotifyGraphics.h"
#include <iostream>

MindMapScene::MindMapScene() : QGraphicsScene()
{
}

void MindMapScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);
    this->notify(SUBJECT_CLICK, "");
}

MindMapScene::~MindMapScene()
{
}