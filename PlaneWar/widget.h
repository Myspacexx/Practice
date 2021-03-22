#ifndef WIDGET_H
#define WIDGET_H
#include"bomb.h"
#include <QWidget>
#include<QTimer>
#include<QPainter>
#include"map.h"
#include"heroplane.h"
#include"enemyplane.h"
#include<ctime>
#include<QPixmap>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initScene();

//启动游戏
void playgame();
//更新坐标
void updatePosition();
//绘图事件
void paintEvent(QPaintEvent *event);
//重写鼠标移动事件
void mouseMoveEvent(QMouseEvent*);

void enemytoScene();
Map m_map;

Heroplane m_hero;

Enemyplane m_enemy;

Enemyplane m_enemys[Enemy_num];
//敌机出场间隔
int m_recorder;

QTimer m_Timer;

Bullet bullect;


Bullet m_bullets[Bullet_num];

//碰撞检测
void crash();

Bomb m_bombs[Bomb_num];


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
