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
        QAction* actionAbort;
        QAction* actionNew;
        QAction* actionSave;
        QAction* actionLoad;
        QAction* actionExit;
        QAction* actionEdit;
        QAction* actionDelete;
        QAction* actionInsert_A_Child;
        QAction* actionInsert_a_sibling;
        QAction* actionInsert_a_parent;
        QWidget* centralWidget;
        QMenuBar* menuBar;
        QMenu* menuFile;
        QMenu* menuEdit;
        QMenu* menuHelp;
        QToolBar* mainToolBar;
        QStatusBar* statusBar;

        void setupActions(QMainWindow* window);
        void setupMenus(QMainWindow* window);
};

#endif // MINDMAPGUI_H