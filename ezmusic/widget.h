#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QPainter>
#include <QPixmap>//jia zai tu pian
#include <QMediaMetaData>
#include <QMessageBox>
#include <QFileInfo>
#include <QTimer>
#include <QTime>
#include <QPaintEvent>
#include <QListWidget>
#include <QUrl>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void init_controls();
    static int t;
    static bool flag1;

private slots:
    void on_play_clicked();

    void on_addmusic_clicked();



    void on_before_clicked();
    void on_next_clicked();

    void on_playstyle_clicked();

    void clearMessage();

    void deletevoice();

    void on_volumeControl_sliderMoved(int position);

    void positionChange(qint64 position);

    void showMessage(bool);

    void posChange();
    void seekChange(int position);

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private:
    Ui::Widget *ui;
    QMediaPlayer *player;
    QMediaPlaylist * playList;
    bool flag;
    int time;
    QTimer *time1;
    QTimer *time2;
    QPoint dragPosition;
};

#endif // WIDGET_H
