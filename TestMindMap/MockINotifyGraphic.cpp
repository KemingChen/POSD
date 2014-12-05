#include "MockINotifyGraphic.h"

MockINotifyGraphic::MockINotifyGraphic()
{
}

void MockINotifyGraphic::clickGraphicNode(Component* node)
{
}

void MockINotifyGraphic::doubleClickGraphicNode(Component* node)
{
}

void MockINotifyGraphic::setupScene()
{
    putInfo("SETUP_SCENE");
}

void MockINotifyGraphic::updateActions()
{
    putInfo("UPDATE_ACTIONS");
}

void MockINotifyGraphic::updateGraphics()
{
    putInfo("UPDATE_GRAPHICS");
}

void MockINotifyGraphic::notifyError(string description)
{
    putInfo("ERROR: " + description);
}

void MockINotifyGraphic::putInfo(string info)
{
    _info += info + "; ";
}

string MockINotifyGraphic::getInfo()
{
    string info = _info;
    _info = "";
    return info;
}

MockINotifyGraphic::~MockINotifyGraphic()
{
}