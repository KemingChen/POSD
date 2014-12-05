#pragma once
#include <string>
#include <INotifyGraphics.h>

class MockINotifyGraphic : public INotifyGraphics
{
    private:
        string _info;

    public:
        MockINotifyGraphic();
        void clickGraphicNode(Component* node);
        void doubleClickGraphicNode(Component* node);
        void setupScene();
        void updateActions();
        void updateGraphics();
        void notifyError(string description);
        ~MockINotifyGraphic();

        string getInfo();
        void putInfo(string info);
};