#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSlider>
#include <QDirIterator>
#include <QStandardPaths>
#include <QFileSystemModel>
#include <QAndroidJniObject>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    viz=new Visualizer(this);
    musicPaths = new QStringListModel(this);
    QStringList androidPaths =QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    androidPaths.append("/storage/sdcard1/Music/");
    musicPaths->setStringList(androidPaths);
    ui->listView->setModel(musicPaths);
    fsmodel = new QFileSystemModel(this);
    fsmodel->setFilter(QDir::Files);
    fsmodel->setRootPath(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).at(0));
    ui->treeView->setModel(fsmodel);
    ui->treeView->setRootIndex(fsmodel->index(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).at(0)));
    ui->gridLayout_3->addWidget(viz);
    ui->widget->hide();
    player = new QMediaPlayer(this);
    ui->toolBar->setIconSize(QSize(48,48));
    ui->horizontalSlider->setTracking(false);
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(seek(int)));


    /*
    qDebug()<< QStandardPaths::standardLocations(QStandardPaths::MusicLocation).at(0);
    while (it.hasNext())
        qDebug() << it.next();
    */

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fname=QFileDialog::getOpenFileName(this);
    player->setMedia(QMediaContent(QUrl::fromLocalFile(fname)));
    player->play();



}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionPlay_triggered()
{
    player->play();
}

void MainWindow::on_actionPause_triggered()
{
    if(player->state()==QMediaPlayer::PlayingState)
    player->pause();
    else
        player->play();
}

void MainWindow::on_actionStop_triggered()
{
    player->stop();
}

void MainWindow::on_actionSkip_Foward_triggered()
{
    qint64 position = player->position();
    player->setPosition(position+10000);
}

void MainWindow::on_actionSkip_Backward_triggered()
{
    qint64 position = player->position();
    player->setPosition(position-10000);
}

void MainWindow::positionChanged(qint64 position)
{
    int sec_position = position/1000;
    ui->horizontalSlider->setValue(sec_position);
}
void MainWindow::durationChanged(qint64 duration)
{
    int sec_duration = duration/1000;
    ui->horizontalSlider->setRange(0,sec_duration);
}

void MainWindow::seek(int position)
{
    player->setPosition(position*1000);
}

void MainWindow::on_actionScan_triggered()
{


}

void MainWindow::on_actionPlayList_triggered()
{
   if(!ui->widget->isVisible())
    ui->widget->show();
   else
       ui->widget->hide();
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    player->setMedia(QMediaContent(QUrl::fromLocalFile(fsmodel->filePath(index))));
    player->play();
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{

    fsmodel->setRootPath(musicPaths->data(index,Qt::DisplayRole).toString());
    ui->treeView->setModel(fsmodel);
    ui->treeView->setRootIndex(fsmodel->index(musicPaths->data(index,Qt::DisplayRole).toString()));
}
