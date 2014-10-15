// Project.cpp : �w�q�D���x���ε{�����i�J�I�C
#include "stdafx.h"
#include "MindMapModel.h"
#include "PresentModel.h"
#include "TextUI.h"

int _tmain(int argc, _TCHAR* argv[])
{
    MindMapModel model;
    PresentModel presentModel(&model);
    TextUI textUI(&presentModel);
    textUI.run();
    return 0;
}