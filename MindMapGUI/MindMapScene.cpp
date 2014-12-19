#include "MindMapScene.h"
#include <iostream>

MindMapScene::MindMapScene() : QGraphicsScene()
{
    this->_subjectName = "MindMapScene";
}

void MindMapScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);
    notify(SUBJECT_CLICK, "");
}

MindMapScene::~MindMapScene()
{
}