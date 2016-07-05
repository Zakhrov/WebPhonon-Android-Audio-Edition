#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "visualizer.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QFileSystemModel>
#include <QStringListModel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_actionStop_triggered();

    void on_actionSkip_Foward_triggered();

    void on_actionSkip_Backward_triggered();
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void seek(int position);

    void on_actionScan_triggered();

    void on_actionPlayList_triggered();

    void on_treeView_clicked(const QModelIndex &index);

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Visualizer *viz;
    QMediaPlayer *player;
    QFileSystemModel *fsmodel;
    QStringListModel *musicPaths;


};

#endif // MAINWINDOW_H
