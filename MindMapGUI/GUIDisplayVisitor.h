#pragma once
#include "stdafx.h"
#include "NodeVisitor.h"
#include <map>
using namespace std;

class GUIDisplayVisitor : public NodeVisitor
{
    private:
        int _yRight;
        int _yLeft;

        int _nowLevel;
        vector<int> _rootCollection;
        vector<int> _nodeCollection;
        map<int, int> _yLevelMap;

        // Private Method
        int calculateLevel(Component* node);
        int averageCollection(vector<int>* collection);
        void backupLastElementAndClean(vector<int>* collection);
        void saveLevelBottomY(int level, int y);
        int getLevelBottomY(int level);

    public:
        GUIDisplayVisitor();
        void visit(Root* node);
        void visit(Node* node);
        ~GUIDisplayVisitor();
};