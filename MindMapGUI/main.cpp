#include "stdafx.h"
#include "MindMapModel.h"
#include "PresentModel.h"
#include "TextUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MindMapModel model;
    PresentModel presentModel(&model);
    GUIPresentModel guiPresentModel(&presentModel, &model);
    MindMapGUI guiWindow(&guiPresentModel);
    model.attach(&guiWindow);
    TextUI textUI(&presentModel, &guiWindow, & app);
    textUI.run();
    return 0;
}