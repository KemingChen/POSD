// Project.cpp : 定義主控台應用程式的進入點。
#include "stdafx.h"
#include "MindMapModel.h"
#include "TextUIPresentModel.h"
#include "TextUI.h"

int _tmain(int argc, _TCHAR* argv[])
{
    MindMapModel* model = new MindMapModel();
    TextUIPresentModel* presentModel = new TextUIPresentModel(model);
    TextUI* textUI = new TextUI(presentModel);
    textUI->run();
    return 0;
}