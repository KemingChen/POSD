#pragma once
#include "PresentModel.h"
#include "INotifyGraphics.h"
#include "GraphicNode.h"
#include <time.h>

using namespace std;

class GUIPresentModel
{
    private:
        PresentModel* _presentModel;
        INotifyGraphics* _notify;

        // Variable
        clock_t _lastClickTime;

        // Property
        GraphicNode* _selectedNode;

        // Method
        bool isValidClick();
        void pushChildGraphics(list<GraphicNode*>* result, GraphicNode* parent, NodeList* nodeList, int levelX, map<int, int>* levelYMap);

    public:
        GUIPresentModel(PresentModel* presentModel, INotifyGraphics* notify);
        ~GUIPresentModel();

        // Action
        void clickGraphicNode(GraphicNode* node);
        void editDescription(string text, bool isValid);
        void loadMindMap(string path);
        void saveMindMap(string path);
        void createMindMap(string text, bool isValid);

        // Status
        bool isMindMapCreated();
        bool isSelectedNode();
        GraphicNode* getSelectedNode();
        list<GraphicNode*>* getGraphicsList();
};