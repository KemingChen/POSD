#ifndef MINDMAPGUI_H
#define MINDMAPGUI_H
#include <list>
#include "PresentModel.h"
#include <QtWidgets/QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QGraphicsView>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "INotifyGraphics.h"
#include "GraphicNode.h"
#include "MindMapScene.h"
#include "GUIPresentModel.h"

using namespace std;

class MindMapGUI : public INotifyGraphics, public QMainWindow
{
    private:
        QAction* _actionAbout;
        QAction* _actionNew;
        QAction* _actionSave;
        QAction* _actionLoad;
        QAction* _actionExit;
        QAction* _actionEdit;
        QAction* _actionDelete;
        QAction* _actionInsertChild;
        QAction* _actionInsertSibling;
        QAction* _actionInsertParent;
        QWidget* _centralWidget;
        QMenuBar* _menuBar;
        QMenu* _menuFile;
        QMenu* _menuEdit;
        QMenu* _menuHelp;
        QToolBar* _mainToolBar;
        QStatusBar* _statusBar;

        // Painter
        MindMapScene* _scene;
        QGraphicsView* _view;
        list<GraphicNode*>* _graphicList;
        GUIPresentModel* _presentModel;

        // Setup
        void setupActions();
        void setupMenus();
        void setupToolBar();
        void bindingActions();
        void setupScene();

        // Method
        void rebuildGraphics();
        int rebuildChildGraphics(GraphicNode* parent, Component* node, int levelX, int& nowY);

    public:
        MindMapGUI(PresentModel* presentModel);
        void show();
        ~MindMapGUI();

        // Event
        void clickGraphicNode(Component* node);
        void doubleClickGraphicNode(Component* node);
        void updateActions();
        void updateGraphics();
        void notifyError(string description);

        // Action
        void createMindMap();
        void editNodeDescription();
        void loadMindMap();
        void saveMindMap();
        void insertParentNode();
        void insertSiblingNode();
        void insertChildNode();
        void deleteNode();
        void showAbout();
        void exit();
};

#endif // MINDMAPGUI_H