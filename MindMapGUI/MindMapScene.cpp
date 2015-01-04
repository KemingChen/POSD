#include "MindMapScene.h"
#include <iostream>

MindMapScene::MindMapScene(GUIPresentModel* presentModel) : QGraphicsScene()
{
    this->_presentModel = presentModel;
}

void MindMapScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);
    this->_presentModel->clickGraphicNode(NULL);
}

MindMapScene::~MindMapScene()
{
}