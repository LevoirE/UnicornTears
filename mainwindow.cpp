#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    const QString STORE_DIR = "Tears";
    initFileView(STORE_DIR);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initFileView(const QString& dirName)
{
    QDir dir(QDir::current());
    if (!dir.exists(dirName)) {
        dir.mkdir(dirName);
    }
    dir.setCurrent(dirName);
    model = new QFileSystemModel(this);
    model->setReadOnly(true);
    model->setRootPath(QDir::currentPath());
    model->setNameFilterDisables(false);
    model->setNameFilters(QStringList("*.hex"));
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(QDir::currentPath()));
    ui->treeView->setColumnHidden(1, true);
    ui->treeView->setColumnHidden(2, true);
//    ui->treeView->header()->setStretchLastSection(true);
    ui->treeView->setColumnHidden(3, true);
}
