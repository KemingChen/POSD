#ifndef MINDMAPGUI_H
#define MINDMAPGUI_H
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
        GUIPresentModel* _guiPresentModel;

        // Variable
        GraphicNode* _selectedNode;
        bool _lockClickEvent;

        void setupActions();
        void setupMenus();
        void setupToolBar();
        void bindingActions();
        void setupNodes();

    public slots:

    public:
        MindMapGUI(PresentModel* presentModel);
        ~MindMapGUI();

        // Event
        void clickGraphicNode(GraphicNode* node);
        void doubleClickGraphicNode(GraphicNode* node);

        // Action
        void showEditDialog();
        void showLoadDialog();
        void showSaveDialog();
        void showAbout();
        void exit();
};

#endif // MINDMAPGUI_H