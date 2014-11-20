#include "stdafx.h"
#include "mindmapgui.h"

MindMapGUI::MindMapGUI(PresentModel* presentModel, QWidget* parent) : QMainWindow(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MindMapGUIClass"));
    this->resize(600, 400);

    setupActions();
    setupMenus();
    setupToolBar();
    bindingActions();
    setupNodes();
}

void MindMapGUI::setupMenus()
{
    _menuBar = new QMenuBar(this);
    _menuBar->setObjectName(QStringLiteral("menuBar"));
    _menuBar->setGeometry(QRect(0, 0, 600, 22));
    this->setMenuBar(_menuBar);
    this->setWindowTitle(QApplication::translate("this", "MindMapGUI", 0));

    _menuFile = new QMenu(QStringLiteral("menuFile"), _menuBar);
    _menuFile->setTitle(QApplication::translate("this", "File", 0));
    _menuFile->addAction(_actionNew);
    _menuFile->addAction(_actionSave);
    _menuFile->addAction(_actionLoad);
    _menuFile->addAction(_actionExit);

    _menuEdit = new QMenu(QStringLiteral("menuEdit"), _menuBar);
    _menuEdit->setTitle(QApplication::translate("this", "Edit", 0));
    _menuEdit->addAction(_actionEdit);
    _menuEdit->addAction(_actionDelete);
    _menuEdit->addAction(_actionInsertChild);
    _menuEdit->addAction(_actionInsertSibling);
    _menuEdit->addAction(_actionInsertParent);

    _menuHelp = new QMenu(QStringLiteral("menuHelp"), _menuBar);
    _menuHelp->setTitle(QApplication::translate("this", "Help", 0));
    _menuHelp->addAction(_actionAbort);

    _menuBar->addAction(_menuFile->menuAction());
    _menuBar->addAction(_menuEdit->menuAction());
    _menuBar->addAction(_menuHelp->menuAction());
}

void MindMapGUI::setupActions()
{
    // File
    _actionNew = new QAction(QIcon("resource/new_icon.png"), QStringLiteral("actionNew"), this);
    _actionSave = new QAction(QIcon("resource/save_icon.png"), QStringLiteral("actionSave"), this);
    _actionLoad = new QAction(QIcon("resource/open_icon.png"), QStringLiteral("actionLoad"), this);
    _actionExit = new QAction(QIcon("resource/exit_icon.png"), QStringLiteral("actionExit"), this);
    _actionNew->setText(QApplication::translate("this", "New", 0));
    _actionSave->setText(QApplication::translate("this", "Save", 0));
    _actionLoad->setText(QApplication::translate("this", "Load", 0));
    _actionExit->setText(QApplication::translate("this", "Exit", 0));

    // Edit
    _actionEdit = new QAction(QIcon("resource/edit_icon.png"), QStringLiteral("actionEdit"), this);
    _actionDelete = new QAction(QIcon("resource/delete_icon.png"), QStringLiteral("actionDelete"), this);
    _actionInsertChild = new QAction(QIcon("resource/insert_child_icon.png"), QStringLiteral("actionInsert_A_Child"), this);
    _actionInsertSibling = new QAction(QIcon("resource/insert_sibling_icon.png"), QStringLiteral("actionInsert_a_sibling"), this);
    _actionInsertParent = new QAction(QIcon("resource/insert_parent_icon.png"), QStringLiteral("actionInsert_a_parent"), this);
    _actionEdit->setText(QApplication::translate("this", "Edit", 0));
    _actionDelete->setText(QApplication::translate("this", "Delete", 0));
    _actionInsertChild->setText(QApplication::translate("this", "Insert a child", 0));
    _actionInsertSibling->setText(QApplication::translate("this", "Insert a sibling", 0));
    _actionInsertParent->setText(QApplication::translate("this", "Insert a parent", 0));

    // Abort
    _actionAbort = new QAction(QIcon("resource/about_icon.png"), QStringLiteral("actionAbort"), this);
    _actionAbort->setText(QApplication::translate("this", "Abort", 0));
}

void MindMapGUI::setupToolBar()
{
    _mainToolBar = new QToolBar(this);
    _mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
    this->addToolBar(Qt::TopToolBarArea, _mainToolBar);

    _mainToolBar->addAction(_actionNew);
    _mainToolBar->addAction(_actionLoad);
    _mainToolBar->addAction(_actionSave);
    _mainToolBar->addSeparator();
    _mainToolBar->addAction(_actionEdit);
    _mainToolBar->addAction(_actionDelete);
    _mainToolBar->addAction(_actionInsertChild);
    _mainToolBar->addAction(_actionInsertSibling);
    _mainToolBar->addAction(_actionInsertParent);
    _mainToolBar->addSeparator();
}

void MindMapGUI::bindingActions()
{
}

void MindMapGUI::setupNodes()
{
    _scene = new QGraphicsScene();
    _view = new QGraphicsView(_scene);
    GraphicNode* a = new GraphicNode(0, 0, NULL);
    GraphicNode* b = new GraphicNode(1, 0, NULL, a->getConnectPoint());
    GraphicNode* c = new GraphicNode(1, 1, NULL, a->getConnectPoint());
    GraphicNode* d = new GraphicNode(1, 2, NULL, a->getConnectPoint());
    GraphicNode* e = new GraphicNode(1, 3, NULL, a->getConnectPoint());
    GraphicNode* f = new GraphicNode(2, 0, NULL, b->getConnectPoint());
    GraphicNode* g = new GraphicNode(2, 1, NULL, d->getConnectPoint());
    _scene->addItem(a);
    _scene->addItem(b);
    _scene->addItem(c);
    _scene->addItem(d);
    _scene->addItem(e);
    _scene->addItem(f);
    _scene->addItem(g);
    b->setSelected(true);
    this->setCentralWidget(_view);
}

MindMapGUI::~MindMapGUI()
{
}