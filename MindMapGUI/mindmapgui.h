#ifndef MINDMAPGUI_H
#define MINDMAPGUI_H
#include <list>
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
#include "MindMapScene.h"
#include "GUIPresentModel.h"

using namespace std;

class GraphicNode;
class MindMapGUI : public Observer, public QMainWindow
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
        QAction* _actionCut;
        QAction* _actionCopy;
        QAction* _actionPaste;
        QAction* _actionRedo;
        QAction* _actionUndo;
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
        void rebuildGraphics(Component* node);

        // Event
        void updateActions();
        void updateGraphics();
        void notifyError(string description);

    protected:
        void update(string subject);

    public:
        MindMapGUI(GUIPresentModel* presentModel);
        void show();
        ~MindMapGUI();

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
        void cut();
        void copy();
        void paste();
        void undo();
        void redo();
        void exit();
};

#endif // MINDMAPGUI_H