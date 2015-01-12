#include "stdafx.h"
#include "MindMapGUI.h"
#include "GraphicNode.h"
#include <iostream>
#include <QTextCodec>
#define FILTER "MindMap Files (*.mm)"

MindMapGUI::MindMapGUI(GUIPresentModel* presentModel) : QMainWindow()
{
    this->_scene = NULL;
    this->_view = NULL;
    this->_graphicList = new list<GraphicNode*>();

    this->_presentModel = presentModel;
    this->_presentModel->attach(this);

    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MindMapGUIClass"));
    this->resize(WINDOW_WIDTH, WINDOW_HEIGHT);

    this->setupActions();
    this->setupMenus();
    this->setupToolBar();
    this->bindingActions();
    this->setupScene();
}

void MindMapGUI::setupMenus()
{
    this->_menuBar = new QMenuBar(this);
    this->_menuBar->setObjectName(QStringLiteral("menuBar"));
    this->_menuBar->setGeometry(QRect(0, 0, 600, 22));
    this->setMenuBar(this->_menuBar);
    this->setWindowTitle(QApplication::translate("this", "MindMapGUI", 0));

    this->_menuFile = new QMenu(QStringLiteral("File"), this->_menuBar);
    this->_menuFile->addAction(this->_actionNew);
    this->_menuFile->addAction(this->_actionSave);
    this->_menuFile->addAction(this->_actionLoad);
    this->_menuFile->addAction(this->_actionExit);

    this->_menuEdit = new QMenu(QStringLiteral("Edit"), this->_menuBar);
    this->_menuEdit->addAction(this->_actionUndo);
    this->_menuEdit->addAction(this->_actionRedo);
    this->_menuEdit->addSeparator();
    this->_menuEdit->addAction(this->_actionMoveUp);
    this->_menuEdit->addAction(this->_actionMoveDown);
    this->_menuEdit->addSeparator();
    this->_menuEdit->addAction(this->_actionCut);
    this->_menuEdit->addAction(this->_actionCopy);
    this->_menuEdit->addAction(this->_actionPaste);
    this->_menuEdit->addSeparator();
    this->_menuEdit->addAction(this->_actionEdit);
    this->_menuEdit->addAction(this->_actionDelete);
    this->_menuEdit->addAction(this->_actionInsertChild);
    this->_menuEdit->addAction(this->_actionInsertSibling);
    this->_menuEdit->addAction(this->_actionInsertParent);
    this->_menuEdit->addSeparator();
    this->_menuEdit->addAction(this->_actionAddTriangle);
    this->_menuEdit->addAction(this->_actionAddRectangle);
    this->_menuEdit->addAction(this->_actionAddEllipse);
    this->_menuEdit->addAction(this->_actionRemoveAll);
    this->_menuEdit->addSeparator();
    this->_menuEdit->addAction(this->_actionCollapseAll);
    this->_menuEdit->addAction(this->_actionExpandAll);
    this->_menuEdit->addAction(this->_actionExpandOneLevel);

    this->_menuHelp = new QMenu(QStringLiteral("Help"), this->_menuBar);
    this->_menuHelp->addAction(this->_actionAbout);

    this->_menuBar->addAction(this->_menuFile->menuAction());
    this->_menuBar->addAction(this->_menuEdit->menuAction());
    this->_menuBar->addAction(this->_menuHelp->menuAction());
}

void MindMapGUI::setupActions()
{
    // File
    this->_actionNew = new QAction(QIcon("resource/new_icon.png"), QStringLiteral("New"), this);
    this->_actionSave = new QAction(QIcon("resource/save_icon.png"), QStringLiteral("Save"), this);
    this->_actionLoad = new QAction(QIcon("resource/open_icon.png"), QStringLiteral("Load"), this);
    this->_actionExit = new QAction(QIcon("resource/exit_icon.png"), QStringLiteral("Exit"), this);

    // Edit
    this->_actionEdit = new QAction(QIcon("resource/edit_icon.png"), QStringLiteral("Edit"), this);
    this->_actionDelete = new QAction(QIcon("resource/delete_icon.png"), QStringLiteral("Delete"), this);
    this->_actionInsertChild = new QAction(QIcon("resource/insert_child_icon.png"), QStringLiteral("Insert a child"), this);
    this->_actionInsertSibling = new QAction(QIcon("resource/insert_sibling_icon.png"), QStringLiteral("Insert a sibling"), this);
    this->_actionInsertParent = new QAction(QIcon("resource/insert_parent_icon.png"), QStringLiteral("Insert a parent"), this);
    this->_actionCut = new QAction(QIcon("resource/cut.png"), QStringLiteral("Cut"), this);
    this->_actionCopy = new QAction(QIcon("resource/copy.png"), QStringLiteral("Copy"), this);
    this->_actionPaste = new QAction(QIcon("resource/paste.png"), QStringLiteral("Paste"), this);
    this->_actionRedo = new QAction(QIcon("resource/redo.png"), QStringLiteral("Redo"), this);
    this->_actionUndo = new QAction(QIcon("resource/undo.png"), QStringLiteral("Undo"), this);
    this->_actionAddTriangle = new QAction(QIcon("resource/triangle.png"), QStringLiteral("Add triangle decorate"), this);
    this->_actionAddRectangle = new QAction(QIcon("resource/rectangle.png"), QStringLiteral("Add rectangle decorate"), this);
    this->_actionAddEllipse = new QAction(QIcon("resource/ellipse.png"), QStringLiteral("Add ellipse decorate"), this);
    this->_actionRemoveAll = new QAction(QIcon("resource/remove_all.png"), QStringLiteral("Remove all decorate"), this);
    this->_actionMoveUp = new QAction(QIcon("resource/move_up.png"), QStringLiteral("Move up"), this);
    this->_actionMoveDown = new QAction(QIcon("resource/move_down.png"), QStringLiteral("Move down"), this);
    this->_actionExpandAll = new QAction(QIcon("resource/expand.png"), QStringLiteral("Expend all"), this);
    this->_actionExpandOneLevel = new QAction(QIcon("resource/expand_one_level.png"), QStringLiteral("Expend one level"), this);
    this->_actionCollapseAll = new QAction(QIcon("resource/collapse.png"), QStringLiteral("Collapse all"), this);

    // Help
    this->_actionAbout = new QAction(QIcon("resource/about_icon.png"), QStringLiteral("Abort"), this);
}

void MindMapGUI::setupToolBar()
{
    // Main Tool Bar
    this->_mainToolBar = new QToolBar(this);
    this->_mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
    this->addToolBar(Qt::TopToolBarArea, this->_mainToolBar);

    this->_mainToolBar->addAction(this->_actionNew);
    this->_mainToolBar->addAction(this->_actionLoad);
    this->_mainToolBar->addAction(this->_actionSave);
    this->_mainToolBar->addSeparator();
    this->_mainToolBar->addAction(this->_actionUndo);
    this->_mainToolBar->addAction(this->_actionRedo);
    this->_mainToolBar->addSeparator();
    this->_mainToolBar->addAction(this->_actionCut);
    this->_mainToolBar->addAction(this->_actionCopy);
    this->_mainToolBar->addAction(this->_actionPaste);
    this->_mainToolBar->addSeparator();
    this->_mainToolBar->addAction(this->_actionEdit);
    this->_mainToolBar->addAction(this->_actionDelete);
    this->_mainToolBar->addAction(this->_actionInsertChild);
    this->_mainToolBar->addAction(this->_actionInsertSibling);
    this->_mainToolBar->addAction(this->_actionInsertParent);

    // Enhanced Tool Bar
    this->_enhancedBar = new QToolBar(this);
    this->_enhancedBar->setObjectName(QStringLiteral("EnhancedToolBar"));
    this->addToolBar(Qt::TopToolBarArea, this->_enhancedBar);

    this->_enhancedBar->addAction(this->_actionAddTriangle);
    this->_enhancedBar->addAction(this->_actionAddRectangle);
    this->_enhancedBar->addAction(this->_actionAddEllipse);
    this->_enhancedBar->addAction(this->_actionRemoveAll);
    this->_enhancedBar->addSeparator();
    this->_enhancedBar->addAction(this->_actionMoveUp);
    this->_enhancedBar->addAction(this->_actionMoveDown);
    this->_enhancedBar->addSeparator();
    this->_enhancedBar->addAction(this->_actionCollapseAll);
    this->_enhancedBar->addAction(this->_actionExpandAll);
    this->_enhancedBar->addAction(this->_actionExpandOneLevel);
}

void MindMapGUI::bindingActions()
{
    // File
    connect(this->_actionNew, &QAction::triggered, this, &MindMapGUI::createMindMap);
    connect(this->_actionLoad, &QAction::triggered, this, &MindMapGUI::loadMindMap);
    connect(this->_actionSave, &QAction::triggered, this, &MindMapGUI::saveMindMap);
    connect(this->_actionExit, &QAction::triggered, this, &MindMapGUI::exit);

    // Edit
    connect(this->_actionEdit, &QAction::triggered, this, &MindMapGUI::editNodeDescription);
    connect(this->_actionDelete, &QAction::triggered, this, &MindMapGUI::deleteNode);
    connect(this->_actionInsertChild, &QAction::triggered, this, &MindMapGUI::insertChildNode);
    connect(this->_actionInsertParent, &QAction::triggered, this, &MindMapGUI::insertParentNode);
    connect(this->_actionInsertSibling, &QAction::triggered, this, &MindMapGUI::insertSiblingNode);
    connect(this->_actionAddTriangle, &QAction::triggered, this, &MindMapGUI::addTriangle);
    connect(this->_actionAddRectangle, &QAction::triggered, this, &MindMapGUI::addRectangle);
    connect(this->_actionAddEllipse, &QAction::triggered, this, &MindMapGUI::addEllipse);
    connect(this->_actionRemoveAll, &QAction::triggered, this, &MindMapGUI::cleanAllDecorate);
    connect(this->_actionCut, &QAction::triggered, this, &MindMapGUI::cut);
    connect(this->_actionCopy, &QAction::triggered, this, &MindMapGUI::copy);
    connect(this->_actionPaste, &QAction::triggered, this, &MindMapGUI::paste);
    connect(this->_actionUndo, &QAction::triggered, this, &MindMapGUI::undo);
    connect(this->_actionRedo, &QAction::triggered, this, &MindMapGUI::redo);
    connect(this->_actionExpandAll, &QAction::triggered, this, &MindMapGUI::expandAll);
    connect(this->_actionExpandOneLevel, &QAction::triggered, this, &MindMapGUI::expandOneLevel);
    connect(this->_actionCollapseAll, &QAction::triggered, this, &MindMapGUI::collapseAll);
    connect(this->_actionMoveUp, &QAction::triggered, this, &MindMapGUI::moveUp);
    connect(this->_actionMoveDown, &QAction::triggered, this, &MindMapGUI::moveDown);

    // Help
    connect(this->_actionAbout, &QAction::triggered, this, &MindMapGUI::showAbout);
}

void MindMapGUI::update(string subject)
{
    //cout << "MindMapGUI update " << subject <<  endl;
    if (subject == MODEL_CHANGE)
    {
        this->updateActions();
        this->updateGraphics();
    }
    else if (subject == SELECTED_CHANGE)
    {
        this->updateActions();
        this->_scene->update();
    }
    else if (subject == CREATE_NEW)
    {
        this->setupScene();
        this->updateActions();
        this->updateGraphics();
    }
    else
    {
        this->notifyError(subject);
    }
}

void MindMapGUI::setupScene()
{
    if (this->_scene != NULL)
        delete this->_scene;
    if (this->_view != NULL)
        delete this->_view;
    this->_scene = new MindMapScene(this->_presentModel);
    this->_view = new QGraphicsView(this->_scene);
    this->setCentralWidget(this->_view);
}

void MindMapGUI::updateActions()
{
    // File
    this->_actionSave->setEnabled(this->_presentModel->isSaveEnable());

    // Edit
    this->_actionEdit->setEnabled(this->_presentModel->isEditNodeEnable());
    this->_actionDelete->setEnabled(this->_presentModel->isDeleteNodeEnable());
    this->_actionInsertChild->setEnabled(this->_presentModel->isInsertChildNodeEnable());
    this->_actionInsertSibling->setEnabled(this->_presentModel->isInsertSiblingNodeEnable());
    this->_actionInsertParent->setEnabled(this->_presentModel->isInsertParentNodeEnable());
    this->_actionCut->setEnabled(this->_presentModel->isCutNodeEnable());
    this->_actionCopy->setEnabled(this->_presentModel->isCopyNodeEnable());
    this->_actionPaste->setEnabled(this->_presentModel->isPasteNodeEnable());
    this->_actionUndo->setEnabled(this->_presentModel->isUndoEnable());
    this->_actionRedo->setEnabled(this->_presentModel->isRedoEnable());

    // Enhanced Tool Bar
    this->_enhancedBar->setEnabled(this->_presentModel->isSelected());
}

void MindMapGUI::updateGraphics()
{
    MindMapPainter* painter = new MindMapPainter(this->_scene, this, this->_presentModel);
    this->_scene->clear();
    this->_graphicList->clear();
    this->_presentModel->rebuildPosition(painter);
}

void MindMapGUI::notifyError(string description)
{
    QString title = tr("MindMap Error Message");
    QString information = QString::fromStdString(description);
    QMessageBox::critical(this, title, information);
}

void MindMapGUI::createMindMap()
{
    bool ok;
    QString title = tr("Create Dialog");
    QString label = tr("Please input your description");
    QString text = QInputDialog::getText(this, title, label, QLineEdit::Normal, "", &ok);
    this->_presentModel->createMindMap(text.toStdString(), ok);
}

void MindMapGUI::insertParentNode()
{
    bool ok;
    QString title = tr("Insert Parent Dialog");
    QString label = tr("Please input your description");
    QString text = QInputDialog::getText(this, title, label, QLineEdit::Normal, "", &ok);
    this->_presentModel->insertParentNode(text.toStdString(), ok);
}

void MindMapGUI::insertSiblingNode()
{
    bool ok;
    QString title = tr("Insert Sibling Dialog");
    QString label = tr("Please input your description");
    QString text = QInputDialog::getText(this, title, label, QLineEdit::Normal, "", &ok);
    this->_presentModel->insertSiblingNode(text.toStdString(), ok);
}

void MindMapGUI::insertChildNode()
{
    bool ok;
    QString title = tr("Insert Child Dialog");
    QString label = tr("Please input your description");
    QString text = QInputDialog::getText(this, title, label, QLineEdit::Normal, "", &ok);
    this->_presentModel->insertChildNode(text.toStdString(), ok);
}

void MindMapGUI::editNodeDescription()
{
    bool ok;
    Component* node = _presentModel->getSelectedNode();
    QString title = tr("Edit Dialog");
    QString label = tr("Please input your description");
    QString description = QString::fromStdString(node->getDescription());
    QString text = QInputDialog::getText(this, title, label, QLineEdit::Normal, description, &ok);
    this->_presentModel->editDescription(text.toStdString(), ok);
}

void MindMapGUI::loadMindMap()
{
    QString title = tr("Load MindMap");
    QString filter = tr(FILTER);
    QString fileName = QFileDialog::getOpenFileName(this, title, "", filter);
    this->_presentModel->loadMindMap(fileName.toStdString());
}

void MindMapGUI::saveMindMap()
{
    QString title = tr("Save MindMap");
    QString filter = tr(FILTER);
    QString fileName = QFileDialog::getSaveFileName(this, title, "", filter);
    this->_presentModel->saveMindMap(fileName.toStdString());
}

void MindMapGUI::deleteNode()
{
    this->_presentModel->deleteNode();
}

void MindMapGUI::showAbout()
{
    QString title = tr("About MindMap");
    QString information = tr(
                              "2014  -  POSD  -  Homework\n\n"
                              "MindMapGUI   -   version 1.0\n\n"
                              "By  Keming Chen   (103598011)"
                          );
    QMessageBox::about(this, title, information);
}

void MindMapGUI::show()
{
    QMainWindow::show();
    this->updateActions();
    this->updateGraphics();
}

void MindMapGUI::cut()
{
    this->_presentModel->cutNode();
}

void MindMapGUI::copy()
{
    this->_presentModel->copyNode();
}

void MindMapGUI::paste()
{
    this->_presentModel->pasteNode();
}

void MindMapGUI::exit()
{
    this->close();
}

void MindMapGUI::undo()
{
    this->_presentModel->undo();
}

void MindMapGUI::redo()
{
    this->_presentModel->redo();
}

void MindMapGUI::addTriangle()
{
    this->_presentModel->addDecorate(ComponentType::TRIANGLE);
}

void MindMapGUI::addRectangle()
{
    this->_presentModel->addDecorate(ComponentType::RECTANGLE);
}

void MindMapGUI::addEllipse()
{
    this->_presentModel->addDecorate(ComponentType::ELLIPSE);
}

void MindMapGUI::cleanAllDecorate()
{
    this->_presentModel->cleanAllDecorate();
}

void MindMapGUI::collapseAll()
{
    this->_presentModel->collapseAll();
}

void MindMapGUI::expandAll()
{
    this->_presentModel->expandAll();
}

void MindMapGUI::expandOneLevel()
{
    this->_presentModel->expandOneLevel();
}

void MindMapGUI::moveUp()
{
    this->_presentModel->moveUp();
}

void MindMapGUI::moveDown()
{
    this->_presentModel->moveDown();
}

MindMapGUI::~MindMapGUI()
{
    this->_scene->clear();
    delete this->_scene;
}