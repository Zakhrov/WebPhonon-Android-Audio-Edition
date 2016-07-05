#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSlider>
#include <QDirIterator>
#include <QStandardPaths>
#include <QFileSystemModel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    viz=new Visualizer(this);
    musicPaths = new QStringListModel(this);
    listView = new QListView(this);
    treeView = new QTreeView(this);
    widget = new QWidget(this);
    ui->gridLayout->addWidget(widget);
    widget->setLayout(new QVBoxLayout());
    widget->layout()->addWidget(listView);
    widget->layout()->addWidget(treeView);
    QStringList androidPaths =QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    androidPaths.append("/storage/sdcard1/Music/");
    musicPaths->setStringList(androidPaths);
    listView->setModel(musicPaths);
    fsmodel = new QFileSystemModel(this);
    fsmodel->setFilter(QDir::Files);
    fsmodel->setRootPath(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).at(0));
    treeView->setModel(fsmodel);
    treeView->setRootIndex(fsmodel->index(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).at(0)));
    ui->gridLayout_3->addWidget(viz);
    widget->hide();
    player = new QMediaPlayer(this);
    ui->toolBar->setIconSize(QSize(48,48));
    ui->horizontalSlider->setTracking(false);
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(seek(int)));
    connect(listView,SIGNAL(clicked(QModelIndex)),this,SLOT(listView_clicked(QModelIndex)));
    connect(treeView,SIGNAL(clicked(QModelIndex)),this,SLOT(treeView_clicked(QModelIndex)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(timeDisplayUpdate(qint64)));

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
    ui->horizontalSlider->setMaximum(sec_duration);
}

void MainWindow::seek(int position)
{
    player->setPosition(position*1000);
}
void MainWindow::on_actionPlayList_triggered()
{
   if(!widget->isVisible())
    widget->showMaximized();
   else
       widget->hide();
}

void MainWindow::treeView_clicked(const QModelIndex &index)
{
    player->setMedia(QMediaContent(QUrl::fromLocalFile(fsmodel->filePath(index))));
    player->play();
}

void MainWindow::listView_clicked(const QModelIndex &index)
{

    fsmodel->setRootPath(musicPaths->data(index,Qt::DisplayRole).toString());
    treeView->setModel(fsmodel);
    treeView->setRootIndex(fsmodel->index(musicPaths->data(index,Qt::DisplayRole).toString()));
    treeView->hideColumn(1);
    treeView->hideColumn(2);
    treeView->hideColumn(3);
}

void MainWindow::timeDisplayUpdate(qint64 time)
{
    qint64 hour,min,sec,dispsec,dmin;
        hour=min=dmin=0;
        sec=time/1000;
            dispsec=sec;
            if(sec>59)
            {
                min=sec/60;
                dispsec=sec%60;
                dmin=min;

            }
            if(min>59)
            {
                hour=min/60;
                dmin=min%60;
            }
    ui->hourlabel->setText(QString::number(hour));
    ui->minlabel->setText(QString::number(dmin));
    ui->seclabel->setText(QString::number(dispsec));
}
