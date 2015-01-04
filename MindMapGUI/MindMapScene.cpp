#include "MindMapScene.h"
#include <iostream>

MindMapScene::MindMapScene() : QGraphicsScene()
{
}

void MindMapScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);
}

MindMapScene::~MindMapScene()
{
}