#pragma once
#include "stdafx.h"
#include "NodeVisitor.h"
#include <map>
#include "IGraphic.h"
using namespace std;

class GUIDisplayVisitor : public NodeVisitor
{
    private:
        int _yRight;
        int _yLeft;

        int _nowLevel;
        map<int, int> _yLevelMap;
        map<int, int> _maxWidthLevelMap;
        IGraphic* _painter;
        vector<Component*> _components;

        // Private Method
        int averageChildY(Component* node);
        void saveBottomY(Component* node);
        int getLevelBottomY(int level);
        void saveLevelMaxWidth(int level, int width);
        int getLevelX(int level);
        int* getNowY(Component* node);

    public:
        GUIDisplayVisitor(IGraphic* painter, Component* root);
        void visit(Root* node);
        void visit(Node* node);
        void visit(Decorate* node);
        void finish();
        ~GUIDisplayVisitor();
};