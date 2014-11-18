#include "stdafx.h"
#include "mindmapgui.h"

MindMapGUI::MindMapGUI(PresentModel* presentModel, QWidget* parent) : QMainWindow(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MindMapGUIClass"));
    this->resize(600, 400);

    mainToolBar = new QToolBar(this);
    mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
    this->addToolBar(Qt::TopToolBarArea, mainToolBar);

    setupActions(this);
    setupMenus(this);
}

void MindMapGUI::setupMenus(QMainWindow* window)
{
    menuBar = new QMenuBar(window);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 600, 22));
    window->setMenuBar(menuBar);
    this->setWindowTitle(QApplication::translate("this", "MindMapGUI", 0));

    menuFile = new QMenu(QStringLiteral("menuFile"), menuBar);
    menuFile->setTitle(QApplication::translate("this", "File", 0));
    menuFile->addAction(actionNew);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionLoad);
    menuFile->addAction(actionExit);

    menuEdit = new QMenu(QStringLiteral("menuEdit"), menuBar);
    menuEdit->setTitle(QApplication::translate("this", "Edit", 0));
    menuEdit->addAction(actionEdit);
    menuEdit->addAction(actionDelete);
    menuEdit->addAction(actionInsert_A_Child);
    menuEdit->addAction(actionInsert_a_sibling);
    menuEdit->addAction(actionInsert_a_parent);

    menuHelp = new QMenu(QStringLiteral("menuHelp"), menuBar);
    menuHelp->setTitle(QApplication::translate("this", "Help", 0));
    menuHelp->addAction(actionAbort);

    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuEdit->menuAction());
    menuBar->addAction(menuHelp->menuAction());
}

void MindMapGUI::setupActions(QMainWindow* window)
{
    // File
    actionNew = new QAction(QIcon("resource/new_icon.png"), QStringLiteral("actionNew"), window);
    actionSave = new QAction(QIcon("resource/save_icon.png"), QStringLiteral("actionSave"), window);
    actionLoad = new QAction(QIcon("resource/open_icon.png"), QStringLiteral("actionLoad"), window);
    actionExit = new QAction(QIcon("resource/exit_icon.png"), QStringLiteral("actionExit"), window);
    actionNew->setText(QApplication::translate("this", "New", 0));
    actionSave->setText(QApplication::translate("this", "Save", 0));
    actionLoad->setText(QApplication::translate("this", "Load", 0));
    actionExit->setText(QApplication::translate("this", "Exit", 0));

    // Edit
    actionEdit = new QAction(QIcon("resource/edit_icon.png"), QStringLiteral("actionEdit"), window);
    actionDelete = new QAction(QIcon("resource/delete_icon.png"), QStringLiteral("actionDelete"), window);
    actionInsert_A_Child = new QAction(QIcon("resource/insert_child_icon.png"), QStringLiteral("actionInsert_A_Child"), window);
    actionInsert_a_sibling = new QAction(QIcon("resource/insert_sibling_icon.png"), QStringLiteral("actionInsert_a_sibling"), window);
    actionInsert_a_parent = new QAction(QIcon("resource/insert_parent_icon.png"), QStringLiteral("actionInsert_a_parent"), window);
    actionEdit->setText(QApplication::translate("this", "Edit", 0));
    actionDelete->setText(QApplication::translate("this", "Delete", 0));
    actionInsert_A_Child->setText(QApplication::translate("this", "Insert a child", 0));
    actionInsert_a_sibling->setText(QApplication::translate("this", "Insert a sibling", 0));
    actionInsert_a_parent->setText(QApplication::translate("this", "Insert a parent", 0));

    // Abort
    actionAbort = new QAction(QIcon("resource/about_icon.png"), QStringLiteral("actionAbort"), window);
    actionAbort->setText(QApplication::translate("this", "Abort", 0));
}

MindMapGUI::~MindMapGUI()
{
}