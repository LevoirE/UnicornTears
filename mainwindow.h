#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QFileSystemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void wantSearch(const QString&);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEdit_search_returnPressed();
    void on_pushButton_upload_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;
    void exploreFolder(const QString &dirName, QTreeWidgetItem *parent, QList<QTreeWidgetItem*> &items);
    void exploreFolder(const QString &dirName, QTreeWidget *view, QList<QTreeWidgetItem*> &items);
};

#endif // MAINWINDOW_H
