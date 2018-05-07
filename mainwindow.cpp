#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCompleter>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    const QString STORE_DIR = "Tears";
    QDir dir(QDir::current());
    if (!dir.exists(STORE_DIR)) {
        dir.mkdir(STORE_DIR);
    }
    dir.setCurrent(STORE_DIR);
    model = new QFileSystemModel(this);
    model->setReadOnly(true);
    model->setRootPath(QDir::currentPath());
    model->setNameFilterDisables(false);
    model->setNameFilters(QStringList("*.hex"));
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(QDir::currentPath()));
//    ui->treeView->setColumnHidden(1, true);
//    ui->treeView->setColumnHidden(2, true);
//    ui->treeView->setColumnHidden(3, true);
//    ui->treeWidget->setColumnCount(1);
//    ui->treeWidget->setHeaderLabel("车型类别");
//    QDir dir(QDir::current());
//    if (!dir.exists("Tears")) {
//        dir.mkdir("Tears");
//    }
//    QList<QTreeWidgetItem*> items;
//    exploreFolder("Tears", ui->treeWidget, items);
//    ui->treeWidget->insertTopLevelItems(0, items);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exploreFolder(const QString &dirName, QTreeWidgetItem *parent, QList<QTreeWidgetItem*> &items)
{
    QDir dir(QDir::current());
    dir.cd(dirName);
    dir.setCurrent(dir.path());

    QFileInfoList fileInfos = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < fileInfos.size(); ++i) {
        QFileInfo info = fileInfos.at(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(parent, QStringList(info.fileName()));
        items.append(item);
        exploreFolder(info.fileName(), item, items);
    }
    dir.cdUp();
    dir.setCurrent(dir.path());
}

void MainWindow::exploreFolder(const QString &dirName, QTreeWidget *view, QList<QTreeWidgetItem*> &items)
{
    QDir dir(QDir::current());
    dir.cd(dirName);
    dir.setCurrent(dir.path());

    QFileInfoList fileInfos = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < fileInfos.size(); ++i) {
        QFileInfo info = fileInfos.at(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(view, QStringList(info.fileName()));
        items.append(item);
        exploreFolder(info.fileName(), item, items);
    }
    dir.cdUp();
    dir.setCurrent(dir.path());
}

void MainWindow::on_lineEdit_search_returnPressed()
{
    emit wantSearch("./test1234125/" + ui->lineEdit_search->text() + ".txt");
}

void MainWindow::on_pushButton_upload_clicked()
{
    QDir dir(QFileDialog::getExistingDirectory(this));
    QFileInfoList fileInfos = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList fileNameList;
    for (int i = 0; i < fileInfos.size(); ++i) {
        QFileInfo info = fileInfos.at(i);
        fileNameList.append(info.fileName());
    }
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if (item->childCount() > 0 || !item->parent())
        return;
    QDir dir(QDir::current());
    QTreeWidgetItem *currentItem = item;
    QStringList pathList;
    QString path;
    pathList.append("/" + currentItem->text(column));
    while (currentItem->parent()) {
        currentItem = currentItem->parent();
        pathList.append("/" + currentItem->text(column));
    }
    for (int i = pathList.size(); i > 0; --i) {
        path += pathList.at(i - 1);
    }
    QFile file(dir.path() + "/Tears" + path + pathList.front() + ".txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    ui->label->setText(file.readAll());
    file.close();
}
