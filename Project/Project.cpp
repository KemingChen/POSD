// Project.cpp : �w�q�D���x���ε{�����i�J�I�C
#include "stdafx.h"
#include "MindMapModel.h"
#include "TextUI.h"

int _tmain(int argc, _TCHAR* argv[])
{
    MindMapModel* model = new MindMapModel();
    TextUI* textUI = new TextUI(model);
    textUI->run();
    return 0;
}