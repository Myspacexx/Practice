#include "widget.h"
#include "ui_widget.h"
#include"config.h"
#include<QIcon>
#include<QMouseEvent>
#include"enemyplane.h"
#include<QSound>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initScene();
}

Widget::~Widget()
{
    delete ui;
}



void Widget::initScene()
{
    QSound::play(":/res/bg.wav");
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));

    m_Timer.setInterval(10);

    playgame();

    //敌机出场变量
    m_recorder=0;
     srand((unsigned int)time(NULL));
}

void Widget::playgame()
{
    m_Timer.start();
    connect(&m_Timer,&QTimer::timeout,[=]()
    {
        //敌机出现
        enemytoScene();
        updatePosition();
        //绘制到屏幕之后再调用paitEvent函数
        update();

    crash();


    });

}

void Widget::updatePosition()
{
   m_map.mapPosition();
   //发射子弹
   m_hero.shoot();
    //计算子弹坐标
   for(int i=0;i<Bullet_num;i++)
   {
       //子弹非空闲,绘制图片
       if(!m_hero.m_bullets[i].m_free)
       {
            m_hero.m_bullets[i].updatePosition();
       }

    }

//   bullect.m_free=false;
//   bullect.updatePosition();




   for(int i=0;i<Enemy_num;i++)
   {
       if(m_enemys[i].m_free==false)
       {
           m_enemys[i].updatePosition();
       }
   }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);
    //绘制飞机
    painter.drawPixmap(m_hero.m_x,m_hero.m_y,m_hero.m_plane);
    //绘制子弹
    //测试
 //  painter.drawPixmap(bullect.m_x,bullect.m_y,bullect.m_bullect);


    for(int i=0;i<Bullet_num;i++)
    {
        if(m_hero.m_bullets[i].m_free==false)
        {
        painter.drawPixmap(m_hero.m_bullets[i].m_x,m_hero.m_bullets[i].m_y,m_hero.m_bullets[i].m_bullect);
        }
    }
//敌机
    for(int i=0;i<Enemy_num;i++)
    {
        if(m_enemys[i].m_free==false)
        {


        painter.drawPixmap(m_enemys[i].m_x,m_enemys[i].m_y,m_enemys[i].enemy);
        }
    }

    for(int i=0;i<Bomb_num;i++)
    {
        if(m_bombs[i].m_free==false)
        {
           painter.drawPixmap(m_bombs[i].m_x,m_bombs[i].m_y,m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }

}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    int x=event->x();
    int y=event->y();
    m_hero.setPosition(x,y);

    //边界检测
    if(x<=0)
    {
        x=0;
    }
    if(x>=GAME_WIDTH-m_hero.m_Rect.width())
    {
        x=GAME_WIDTH-m_hero.m_Rect.width();
    }
    if(y<=0)
    {
       y=0;
    }
    if(y>=GAME_HEIGHT-m_hero.m_Rect.height())
    {
        y=GAME_HEIGHT-m_hero.m_Rect.height();
    }
    m_hero.setPosition(x,y);
}

void Widget::enemytoScene()
{
    m_recorder++;
    if(m_recorder<Enemy_Interval)
    {
        return;
    }
    m_recorder=0;


    for(int i=0;i<Enemy_num;i++)
    {
        if(m_enemys[i].m_free){
            m_enemys[i].m_free=false;
           m_enemys[i].m_x=rand()%(GAME_WIDTH-m_enemys[i].m_Rect.width());
           m_enemys[i].m_y=-m_enemys[i].m_Rect.height();
            break;

        }
    }

}

void Widget::crash()
{
    for(int i=0;i<Enemy_num;i++)
        {
        if(m_enemys[i].m_free)
            continue;
        for(int j=0;j<Bullet_num;j++)
        {
            if(m_hero.m_bullets[j].m_free)
                continue;
            //碰撞检测返回true
            if(m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect))
            {

                QSound::play(":/res/bomb.wav");
                    m_enemys[i].m_free=true;
                    m_hero.m_bullets[j].m_free=true;
                    for(int k=0;k<Bomb_num;k++)
                    {
                        if(m_bombs[k].m_free)
                        {
                            m_bombs[k].m_free=false;

                            //更新坐标
                            m_bombs[k].m_x=m_enemys[i].m_x;
                            m_bombs[k].m_y=m_enemys[i].m_y;
                            break;
                        }

                    }

            }

        }


    }



}




