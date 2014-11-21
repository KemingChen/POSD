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

void MindMapScene::addItem(QGraphicsItem* node)
{
    QGraphicsScene::addItem(node);
    _list.append((GraphicNode*)node);
}

void MindMapScene::clear()
{
    for (int i = 0; i < _list.size(); ++i)
    {
        delete _list.at(i);
    }
    _list.clear();
}

MindMapScene::~MindMapScene()
{
}