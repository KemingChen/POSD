#include "stdafx.h"
#include "MindMapGUI.h"
#include <iostream>
#include <QTextCodec>
#define FILTER "MindMap Files (*.mm)"

MindMapGUI::MindMapGUI(PresentModel* presentModel) : QMainWindow()
{
    this->_name = "MindMapGUI";
    _scene = NULL;
    _view = NULL;
    _graphicList = new list<GraphicNode*>();

    _presentModel = new GUIPresentModel(presentModel);
    _presentModel->attach(this);

    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("MindMapGUIClass"));
    this->resize(800, 600);

    setupActions();
    setupMenus();
    setupToolBar();
    bindingActions();
    setupScene();
}

void MindMapGUI::setupMenus()
{
    _menuBar = new QMenuBar(this);
    _menuBar->setObjectName(QStringLiteral("menuBar"));
    _menuBar->setGeometry(QRect(0, 0, 600, 22));
    this->setMenuBar(_menuBar);
    this->setWindowTitle(QApplication::translate("this", "MindMapGUI", 0));

    _menuFile = new QMenu(QStringLiteral("File"), _menuBar);
    _menuFile->addAction(_actionNew);
    _menuFile->addAction(_actionSave);
    _menuFile->addAction(_actionLoad);
    _menuFile->addAction(_actionExit);

    _menuEdit = new QMenu(QStringLiteral("Edit"), _menuBar);
    _menuEdit->addAction(_actionUndo);
    _menuEdit->addAction(_actionRedo);
    _menuEdit->addSeparator();
    _menuEdit->addAction(_actionCut);
    _menuEdit->addAction(_actionCopy);
    _menuEdit->addAction(_actionPaste);
    _menuEdit->addSeparator();
    _menuEdit->addAction(_actionEdit);
    _menuEdit->addAction(_actionDelete);
    _menuEdit->addAction(_actionInsertChild);
    _menuEdit->addAction(_actionInsertSibling);
    _menuEdit->addAction(_actionInsertParent);

    _menuHelp = new QMenu(QStringLiteral("Help"), _menuBar);
    _menuHelp->addAction(_actionAbout);

    _menuBar->addAction(_menuFile->menuAction());
    _menuBar->addAction(_menuEdit->menuAction());
    _menuBar->addAction(_menuHelp->menuAction());
}

void MindMapGUI::setupActions()
{
    // File
    _actionNew = new QAction(QIcon("resource/new_icon.png"), QStringLiteral("New"), this);
    _actionSave = new QAction(QIcon("resource/save_icon.png"), QStringLiteral("Save"), this);
    _actionLoad = new QAction(QIcon("resource/open_icon.png"), QStringLiteral("Load"), this);
    _actionExit = new QAction(QIcon("resource/exit_icon.png"), QStringLiteral("Exit"), this);

    // Edit
    _actionEdit = new QAction(QIcon("resource/edit_icon.png"), QStringLiteral("Edit"), this);
    _actionDelete = new QAction(QIcon("resource/delete_icon.png"), QStringLiteral("Delete"), this);
    _actionInsertChild = new QAction(QIcon("resource/insert_child_icon.png"), QStringLiteral("Insert a child"), this);
    _actionInsertSibling = new QAction(QIcon("resource/insert_sibling_icon.png"), QStringLiteral("Insert a sibling"), this);
    _actionInsertParent = new QAction(QIcon("resource/insert_parent_icon.png"), QStringLiteral("Insert a parent"), this);
    _actionCut = new QAction(QIcon("resource/cut.png"), QStringLiteral("Cut"), this);
    _actionCopy = new QAction(QIcon("resource/copy.png"), QStringLiteral("Copy"), this);
    _actionPaste = new QAction(QIcon("resource/paste.png"), QStringLiteral("Paste"), this);
    _actionRedo = new QAction(QIcon("resource/redo.png"), QStringLiteral("Redo"), this);
    _actionUndo = new QAction(QIcon("resource/undo.png"), QStringLiteral("Undo"), this);

    // Help
    _actionAbout = new QAction(QIcon("resource/about_icon.png"), QStringLiteral("Abort"), this);
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
    _mainToolBar->addAction(_actionUndo);
    _mainToolBar->addAction(_actionRedo);
    _mainToolBar->addSeparator();
    _mainToolBar->addAction(_actionCut);
    _mainToolBar->addAction(_actionCopy);
    _mainToolBar->addAction(_actionPaste);
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
    connect(_actionCut, &QAction::triggered, this, &MindMapGUI::cut);
    connect(_actionCopy, &QAction::triggered, this, &MindMapGUI::copy);
    connect(_actionPaste, &QAction::triggered, this, &MindMapGUI::paste);
    connect(_actionUndo, &QAction::triggered, this, &MindMapGUI::undo);
    connect(_actionRedo, &QAction::triggered, this, &MindMapGUI::redo);

    // Help
    connect(_actionAbout, &QAction::triggered, this, &MindMapGUI::showAbout);
}

void MindMapGUI::update(int subject, string info)
{
    //cout << "MindMapGUI update " << subject << endl;
    switch (subject)
    {
        case SUBJECT_ERROR:
            notifyError(info);
            break;
        case SUBJECT_CLICK:
            this->clickGraphicNode(info);
            this->updateActions();
            _scene->update();
            break;
        case SUBJECT_DB_CLICK:
            this->editNodeDescription();
            break;
        case SUBJECT_MODEL_CHANGE:
            this->updateActions();
            this->updateGraphics();
            break;
        case SUBJECT_NEW:
            setupScene();
            updateActions();
            updateGraphics();
            break;
        case SUBJECT_PRESENT_CHANGE:
            this->updateActions();
            _scene->update();
            break;
    }
}

void MindMapGUI::setupScene()
{
    if (_scene != NULL)
        delete _scene;
    if (_view != NULL)
        delete _view;
    _scene = new MindMapScene();
    _scene->attach(this);
    _view = new QGraphicsView(_scene);
    this->setCentralWidget(_view);
}

void MindMapGUI::clickGraphicNode(string id)
{
    _presentModel->clickGraphicNode(id);
}

void MindMapGUI::doubleClickGraphicNode(string id)
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
    _actionCut->setEnabled(_presentModel->isCutNodeEnable());
    _actionCopy->setEnabled(_presentModel->isCopyNodeEnable());
    _actionPaste->setEnabled(_presentModel->isPasteNodeEnable());
    _actionUndo->setEnabled(_presentModel->isUndoEnable());
    _actionRedo->setEnabled(_presentModel->isRedoEnable());
}

void MindMapGUI::updateGraphics()
{
    _scene->clear();
    rebuildGraphics();
    for (list<GraphicNode*>::iterator iGraphic = _graphicList->begin(); iGraphic != _graphicList->end(); iGraphic++)
    {
        _scene->addItem(*iGraphic);
        _scene->addLine((*iGraphic)->getConnectLine());
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
    _presentModel->cutNode();
}

void MindMapGUI::copy()
{
    _presentModel->copyNode();
}

void MindMapGUI::paste()
{
    _presentModel->pasteNode();
}

void MindMapGUI::exit()
{
    this->close();
}

int MindMapGUI::rebuildChildGraphics(GraphicNode* parent, Component* node, int nowX, int& nowY)
{
    GraphicNode* graphicNode = new GraphicNode(node, parent);
    graphicNode->attach(this);
    NodeList* nodeList = node->getNodeList();
    int newY = 0;
    for (NodeList::iterator iNode = nodeList->begin(); iNode != nodeList->end(); iNode++)
    {
        int temp = rebuildChildGraphics(graphicNode, *iNode, nowX + BOUNDING_WIDTH, nowY);
        if (iNode == nodeList->begin() || iNode == nodeList->end() - 1)
        {
            newY += temp / (nodeList->size() == 1 ? 1 : 2);
        }
    }
    if (nodeList->size() == 0)
    {
        newY = nowY;
        nowY += node->getHeight() + 2 * INNER_PADDING + OUTER_PADDING;
    }
    graphicNode->setPosition(nowX, newY);
    _graphicList->push_back(graphicNode);
    return newY;
}

void MindMapGUI::rebuildGraphics()
{
    _graphicList->clear();
    Component* root = _presentModel->getRoot();
    if (root != NULL)
    {
        int nowY = 0;
        rebuildChildGraphics(NULL, root, 0, nowY);
    }
}

void MindMapGUI::undo()
{
    _presentModel->undo();
}

void MindMapGUI::redo()
{
    _presentModel->redo();
}

MindMapGUI::~MindMapGUI()
{
    delete _presentModel;
    _scene->clear();
    delete _scene;
}