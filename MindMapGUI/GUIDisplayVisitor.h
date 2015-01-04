#pragma once
#include "stdafx.h"
#include "NodeVisitor.h"
using namespace std;

class GUIDisplayVisitor : public NodeVisitor
{
    private:
        int _yRight;
        int _yLeft;

        int _nowLevel;
        vector<int> _rootCollection;
        vector<int> _nodeCollection;

        // Private Method
        int averageCollection(vector<int>* collection);
        void backupLastElementAndClean(vector<int>* collection);

    public:
        GUIDisplayVisitor();
        void visit(Root* node);
        void visit(Node* node);
        ~GUIDisplayVisitor();
};