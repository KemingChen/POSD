#include "stdafx.h"
#include "MindMapGUI.h"
#include <iostream>
#include <QTextCodec>
#define FILTER "MindMap Files (*.mm)"

MindMapGUI::MindMapGUI(PresentModel* presentModel) : QMainWindow()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MindMapGUIClass"));
    this->resize(1024, 768);

    setupActions();
    setupMenus();
    setupToolBar();
    bindingActions();
    setupScene();

    _presentModel = new GUIPresentModel(presentModel, this);
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
    _menuHelp->addAction(_actionAbout);

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

    // Help
    _actionAbout = new QAction(QIcon("resource/about_icon.png"), QStringLiteral("actionAbort"), this);
    _actionAbout->setText(QApplication::translate("this", "Abort", 0));
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
    // File
    connect(_actionNew, &QAction::triggered, this, &MindMapGUI::createMindMap);
    connect(_actionLoad, &QAction::triggered, this, &MindMapGUI::loadMindMap);
    connect(_actionSave, &QAction::triggered, this, &MindMapGUI::saveMindMap);
    connect(_actionExit, &QAction::triggered, this, &MindMapGUI::exit);

    // Edit
    connect(_actionEdit, &QAction::triggered, this, &MindMapGUI::editNodeDescription);
    connect(_actionDelete, &QAction::triggered, this, &MindMapGUI::deleteNode);
    connect(_actionInsertChild, &QAction::triggered, this, &MindMapGUI::insertChildNode);
    connect(_actionInsertParent, &QAction::triggered, this, &MindMapGUI::insertParentNode);
    connect(_actionInsertSibling, &QAction::triggered, this, &MindMapGUI::insertSiblingNode);

    // Help
    connect(_actionAbout, &QAction::triggered, this, &MindMapGUI::showAbout);
}

void MindMapGUI::setupScene()
{
    _scene = new MindMapScene(this);
    _view = new QGraphicsView(_scene);
    this->setCentralWidget(_view);
}

void MindMapGUI::clickGraphicNode(Component* node)
{
    _presentModel->clickGraphicNode(node);
}

void MindMapGUI::doubleClickGraphicNode(Component* node)
{
    editNodeDescription();
}

void MindMapGUI::updateActions()
{
    // File
    _actionSave->setEnabled(_presentModel->isSaveEnable());

    // Edit
    _actionEdit->setEnabled(_presentModel->isEditNodeEnable());
    _actionDelete->setEnabled(_presentModel->isDeleteNodeEnable());
    _actionInsertChild->setEnabled(_presentModel->isInsertChildNodeEnable());
    _actionInsertSibling->setEnabled(_presentModel->isInsertSiblingNodeEnable());
    _actionInsertParent->setEnabled(_presentModel->isInsertParentNodeEnable());
}

void MindMapGUI::updateGraphics()
{
    _scene->clear();
    list<GraphicNode*>* graphicList = this->getGraphicsList();
    for (list<GraphicNode*>::iterator iGraphic = graphicList->begin(); iGraphic != graphicList->end(); iGraphic++)
    {
        _scene->addItem(*iGraphic);
    }
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
    _presentModel->createMindMap(text.toStdString(), ok);
}

void MindMapGUI::insertParentNode()
{
    bool ok;
    QString title = tr("Insert Parent Dialog");
    QString label = tr("Please input your description");
    QString text = QInputDialog::getText(this, title, label, QLineEdit::Normal, "", &ok);
    _presentModel->insertParentNode(text.toStdString(), ok);
}

void MindMapGUI::insertSiblingNode()
{
    bool ok;
    QString title = tr("Insert Sibling Dialog");
    QString label = tr("Please input your description");
    QString text = QInputDialog::getText(this, title, label, QLineEdit::Normal, "", &ok);
    _presentModel->insertSiblingNode(text.toStdString(), ok);
}

void MindMapGUI::insertChildNode()
{
    bool ok;
    QString title = tr("Insert Child Dialog");
    QString label = tr("Please input your description");
    QString text = QInputDialog::getText(this, title, label, QLineEdit::Normal, "", &ok);
    _presentModel->insertChildNode(text.toStdString(), ok);
}

void MindMapGUI::editNodeDescription()
{
    bool ok;
    Component* node = _presentModel->getSelectedNode();
    QString title = tr("Edit Dialog");
    QString label = tr("Please input your description");
    QString description = QString::fromStdString(node->getDescription());
    QString text = QInputDialog::getText(this, title, label, QLineEdit::Normal, description, &ok);
    _presentModel->editDescription(text.toStdString(), ok);
}

void MindMapGUI::loadMindMap()
{
    QString title = tr("Load MindMap");
    QString filter = tr(FILTER);
    QString fileName = QFileDialog::getOpenFileName(this, title, "", filter);
    _presentModel->loadMindMap(fileName.toStdString());
}

void MindMapGUI::saveMindMap()
{
    QString title = tr("Save MindMap");
    QString filter = tr(FILTER);
    QString fileName = QFileDialog::getSaveFileName(this, title, "", filter);
    _presentModel->saveMindMap(fileName.toStdString());
}

void MindMapGUI::deleteNode()
{
    _presentModel->deleteNode();
    _scene->update();
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

void MindMapGUI::exit()
{
    this->close();
}

int MindMapGUI::rebuildChildGraphics(GraphicNode* parent, Component* node, int levelX, int nowY)
{
    int count = 0;
    int y;
    GraphicNode* graphicNode = new GraphicNode(levelX, node, this);
    NodeList* nodeList = node->getNodeList();
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        count++;
        y += rebuildChildGraphics(graphicNode, *iNode, levelX + 1, 0);
    }
    graphicNode->setYPosition(count > 0 ? y / count : y);
    graphicNode->setSelected(_presentModel->isSelectedNode(node));
    _graphicList->push_back(graphicNode);
}

void MindMapGUI::rebuildGraphics()
{
    _graphicList->clear();
    Component* root = _presentModel->getRoot();
    if (root != NULL)
    {
        rebuildChildGraphics(NULL, root, 0, 0);
    }
}

MindMapGUI::~MindMapGUI()
{
}