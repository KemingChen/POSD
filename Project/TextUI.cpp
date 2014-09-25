#include "stdafx.h"
#include "TextUI.h"


TextUI::TextUI(MindMapModel* model)
{
    _model = model;
}

void TextUI::run()
{
    printf("Hello!!!");
    system("pause");
}

TextUI::~TextUI()
{
}
