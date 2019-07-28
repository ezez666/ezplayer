#include "widget.h"
#include "ui_widget.h"
int Widget::t = 2;
bool Widget::flag1= true;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->player = new QMediaPlayer(this);
    this->playList = new QMediaPlaylist;
    flag= false;
    time1 = new QTimer(this);
    time2 = new QTimer(this);
    init_controls();

    connect(player, SIGNAL(metaDataAvailableChanged(bool)), this, SLOT(showMessage(bool)));
    connect(ui->seekSlider,SIGNAL(sliderMoved(int)), this,SLOT(seekChange(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init_controls()
{
     ui->addmusic->setToolTip("添加歌曲");
     ui->addmusic->setStyleSheet("QPushButton:!hover{border-image: url(:/image/Add.png);}"
                                 "QPushButton:hover{border-image: url(:/image/Add.png);}"
                                 "QPushButton:pressed{border-image: url(:/image/Add.png);}"
                                 );

      ui->addmusic->setCursor(QCursor(Qt::PointingHandCursor));


     ui->Close->setToolTip("退出");
     ui->Close->setStyleSheet("QPushButton:!hover{border-image: url(:/image/toclose.png);}"
                              "QPushButton:hover{border-image: url(:/image/toclose.png);}"
                              "QPushButton:pressed{border-image: url(:/image/toclose.png);}"
                              );
     ui->Close->setCursor(QCursor(Qt::PointingHandCursor));

     ui->Tomin->setToolTip("最小化");
     ui->Tomin->setStyleSheet("QPushButton:!hover{border-image: url(:/image/tomin.png);}"
                              "QPushButton:hover{border-image: url(:/image/tomin.png);}"
                              "QPushButton:pressed{border-image: url(:/image/tomin.png);}"
                              );
     ui->Tomin->setCursor(QCursor(Qt::PointingHandCursor));

     ui->play->setToolTip("播放");
     ui->play->setStyleSheet("QPushButton:!hover{border-image: url(:/image/play.png);}"
                            "QPushButton:hover{border-image: url(:/image/play.png);}"
                            "QPushButton:pressed{border-image: url(:/image/play.png);}"
                            );
     ui->play->setCursor(QCursor(Qt::PointingHandCursor));

     ui->playstyle->setToolTip("列表循环");
     ui->playstyle->setStyleSheet("QPushButton:!hover{border-image: url(:/image/comboxitem2.png);}"
                                  "QPushButton:hover{border-image: url(:/image/comboxitem2.png);}"
                                  "QPushButton:pressed{border-image: url(:/image/comboxitem2.png);}");
     ui->playstyle->setCursor(QCursor(Qt::PointingHandCursor));

     ui->before->setToolTip("上一首");
     ui->before->setStyleSheet("QPushButton:!hover{border-image: url(:/image/before.png);}"
                               "QPushButton:hover{border-image: url(:/image/before.png);}"
                               "QPushButton:pressed{border-image: url(:/image/before.png);}"
                               );
     ui->before->setCursor(QCursor(Qt::PointingHandCursor));

     ui->next->setToolTip("下一首");
     ui->next->setStyleSheet("QPushButton:!hover{border-image: url(:/image/next.png);}"
                                   "QPushButton:hover{border-image: url(:/image/next.png);}"
                                   "QPushButton:pressed{border-image: url(:/image/next.png);}"
                                   );
     ui->next->setCursor(QCursor(Qt::PointingHandCursor));

     ui->Voice->setToolTip("声音");
     ui->Voice->setStyleSheet("QPushButton:!hover{border-image: url(:/image/sound.png);}"
                              "QPushButton:hover{border-image: url(:/image/sound.png);}"
                              "QPushButton:pressed{border-image: url(:/image/sound.png);}"
                              );
     ui->Voice->setCursor(QCursor(Qt::PointingHandCursor));


     ui->volumeControl->setCursor(QCursor(Qt::PointingHandCursor));
     ui->volumeControl->setRange(0,100);//设置滑动条控件的最小值和最大值
     ui->volumeControl ->setValue(50);//设置初值为50；

     ui->seekSlider->setObjectName("seekSlider");
     ui->seekSlider -> setCursor(QCursor(Qt::PointingHandCursor));

     QPalette pac;//创建调色板
     pac.setColor(QPalette::WindowText,QColor(70,80,70));

     ui->list -> setFont(QFont("Times",10,QFont::Bold));
     ui->list -> setPalette(pac);
     ui->list ->setStyleSheet("background: rgba(0,0,0,0.1);");

     ui->message -> setFont(QFont("Times",10,QFont::Bold));
     ui->message -> setPalette(pac);

     ui->title ->setFont(QFont("Times",15,QFont::Bold));
     QPalette pa;
     pa.setColor(QPalette::WindowText,QColor(0,0,0));
     ui->title -> setPalette(pa);
     ui->title -> setText("MUSIC");



     ui->showMge -> setFont(QFont("Times",10,QFont::Bold));//字体使用Times,10号字体，加粗
     ui->showMge -> setPalette(pac);

     ui->showPro -> setFont(QFont("Times",10,QFont::Bold));
     ui->showPro -> setPalette(pac);
     QTime mov(0,0,0);
     ui->showPro ->setText(mov.toString("mm:ss"));

     connect(ui->Close, SIGNAL(clicked(bool)), this, SLOT(close()));
     connect(ui->Tomin, SIGNAL(clicked(bool)), this, SLOT(showMinimized()));
     connect(ui->Voice, SIGNAL(clicked(bool)), this, SLOT(deletevoice()));
     connect(player,SIGNAL(positionChanged(qint64)),this,SLOT( positionChange(qint64)));
}

void Widget::on_play_clicked()
{
    if(!flag)
    {
        QMessageBox::information(this,"添加音乐","请先添加音乐","确定");
    }
    else
    {

        if(player -> state() == QMediaPlayer::PlayingState)
        {
            player->pause();
            time1->stop();
            ui->play->setStyleSheet("QPushButton:!hover{border-image: url(:/image/play.png);}"
                                   "QPushButton:hover{border-image: url(:/image/play.png);}"
                                   "QPushButton:pressed{border-image: url(:/image/play.png);}"
                                   );

        }
        else
        {
            player -> play();
            connect(time1, SIGNAL(timeout()), this, SLOT(posChange()));
            time1->start(1000);

            ui->play->setStyleSheet("QPushButton:!hover{border-image: url(:/image/stop.png);}"
                                   "QPushButton:hover{border-image: url(:/image/stop.png);}"
                                   "QPushButton:pressed{border-image: url(:/image/stop.png);}"
                                   );

        }
    }
}

void Widget::on_addmusic_clicked()
{
    QString songFileName,songName;
    QFileInfo info;
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("打开文件"),"",tr("music(*.mp3)"));
    if(!fileNames.isEmpty())
    {
        flag= true;
    }
    for(int i = 0; i < fileNames.size(); i ++)
    {
        playList -> addMedia(QUrl::fromLocalFile(fileNames.at(i)));
        songFileName = fileNames.at(i);
        info = QFileInfo(songFileName);
        songName = info.fileName();
        ui->list->addItem(songName);
        ui->message -> setText(tr("添加成功"));
    }
    playList->setCurrentIndex(0);
    if(t == 0)
    {
        playList->setPlaybackMode(QMediaPlaylist::Random);
    }
    else if(t== 1)
    {
        playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }
    else
    {
        playList->setPlaybackMode(QMediaPlaylist::Sequential);
    }
    player -> setPlaylist(playList);
    ui->play->setStyleSheet("QPushButton:!hover{border-image: url(:/image/play.png);}"
                           "QPushButton:hover{border-image: url(:/image/play.png);}"
                           "QPushButton:pressed{border-image: url(:/image/stop.png);}"
                           );


    connect(time2, SIGNAL(timeout()), this, SLOT(clearMessage()));
    time2 ->start(2000);
}

void Widget::on_before_clicked()
{
    time = 0;
    playList ->previous();
}


void Widget::on_next_clicked()
{
    time = 0;
    playList->next();
}

void Widget::on_playstyle_clicked()
{
    if(t==0)
    {
        ui->playstyle->setStyleSheet("QPushButton:!hover{border-image: url(:/image/comboxitem2.png);}"
                                     "QPushButton:hover{border-image: url(:/image/comboxitem2.png);}"
                                     "QPushButton:pressed{border-image: url(:/image/comboxitem2.png);}");
        ui->playstyle->setToolTip(tr("列表循环"));
        this->playList->setPlaybackMode(QMediaPlaylist::Sequential);
        t=2;
    }
    else if(t==1)
    {
        ui->playstyle->setStyleSheet("QPushButton:!hover{border-image: url(:/image/comboxitem1.png);}"
                                   "QPushButton:hover{border-image: url(:/image/comboxitem1.png);}"
                                   "QPushButton:pressed{border-image: url(:/image/comboxitem1.png);}"
                                   );
        ui->playstyle->setToolTip(tr("随机播放"));
        playList->setPlaybackMode(QMediaPlaylist::Random);
        t--;
    }
    else if(t==2)
    {
        ui->playstyle->setStyleSheet("QPushButton:!hover{border-image: url(:/image/comboxitem3.png);}"
                                   "QPushButton:hover{border-image: url(:/image/comboxitem3.png);}"
                                   "QPushButton:pressed{border-image: url(:/image/comboxitem3.png);}"
                                   );
        ui->playstyle->setToolTip(tr("单曲循环"));
        playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        t--;
    }
}

void Widget::clearMessage()
{
    ui->message -> setText("");
}

void Widget::deletevoice()
{
    if(flag1){

        ui->Voice->setStyleSheet("QPushButton:!hover{border-image: url(:/image/sound_close.png)}"
                                  "QPushButton:hover{border-image: url(:/image/sound_close.png)}"
                                  "QPushButton:pressed{border-image: url(:/image/sound_close.png)}"
                                  "QPushButton:focus{padding:-1;}");
        ui->Voice->setToolTip(tr("打开声音"));
        player -> setMuted(true);

    }else{
        ui->Voice->setStyleSheet("QPushButton:!hover{border-image: url(:/image/sound.png)}"
                                  "QPushButton:hover{border-image: url(:/image/sound.png)}"
                                  "QPushButton:pressed{border-image: url(:/image/sound.png)}"
                                  "QPushButton:focus{padding:-1;}");

        ui->Voice->setToolTip(tr("关闭声音"));
        player -> setMuted(false);
    }
    flag1=!flag1;
}



void Widget::on_volumeControl_sliderMoved(int position)
{
    this->player -> setVolume(position);
}

void Widget::positionChange(qint64 position)
{
    ui->seekSlider->setMaximum(player->duration() / 1000);
    ui->seekSlider->setValue(position / 1000);
    time = position;
    QTime moveTime(0,(time/60000) % 60,(time / 1000) % 60);
    ui->showPro ->setText(moveTime.toString("mm:ss"));
}

void Widget::showMessage(bool ok)
{
    if(ok)
    {
        QString name= player->metaData(QMediaMetaData::Title).toString();
        QString author= player->metaData(QMediaMetaData::Author).toString();
        ui->showMge -> setText("正在播放："+name + " -" + author);


    }
}

void Widget::posChange()
{
    if(time >= player -> duration())
    {
        time = 0;
    }
}

void Widget::seekChange(int position)
{
    player -> setPosition(position * 1000);
    time = position * 1000;
    QTime moveTime(0,(time/60000) % 60,(time / 1000) % 60);
    ui->showPro ->setText(moveTime.toString("mm:ss"));
}

void Widget::paintEvent(QPaintEvent *event)
{
     QPainter paint(this);
     QPixmap backgound;
     backgound.load(":/image/7.jpg");
     paint.drawPixmap(0, 0,this->width(), this->height(),backgound);
     event ->accept();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton)
    {
        dragPosition=event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        this ->move(event->globalPos() - dragPosition);
        event->accept();
    }

}


