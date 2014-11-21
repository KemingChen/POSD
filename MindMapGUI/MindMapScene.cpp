#include "MindMapScene.h"
#include "INotifyGraphics.h"
#include <iostream>

MindMapScene::MindMapScene(INotifyGraphics* notify) : QGraphicsScene()
{
    _notify = notify;
}

void MindMapScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);
    _notify->clickGraphicNode(NULL);
}

MindMapScene::~MindMapScene()
{
}