#ifndef MINDMAPGUI_H
#define MINDMAPGUI_H
#include "PresentModel.h"
#include <map>
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

class MindMapGUI : public QMainWindow
{
    public:
        MindMapGUI(PresentModel* presentModel, QWidget* parent = 0);
        ~MindMapGUI();

    private:
        QAction* _actionAbort;
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

        void setupActions(QMainWindow* window);
        void setupMenus(QMainWindow* window);
        void setupToolBar(QMainWindow* window);
};

#endif // MINDMAPGUI_H