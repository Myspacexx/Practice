#include "heroplane.h"
#include"config.h"
#include"bullet.h"


Heroplane::Heroplane()
{   //加载资源
    m_plane.load(":/res/hero2.png");
    //初始坐标
    m_x=GAME_WIDTH*0.5-m_plane.width()*0.5;
    m_y=GAME_HEIGHT-m_plane.height()-100;
    //碰撞检测
     m_Rect.setWidth(m_plane.width());
     m_Rect.setHeight(m_plane.height());
     m_Rect.moveTo(m_x,m_y);

     m_recorder=0;
}

void Heroplane::shoot()
{
//累加事件间隔

    m_recorder++;
    if(m_recorder<Bullet_Interval)
    {
        return;
    }
   m_recorder=0;


    for(int i=0;i<Bullet_num;i++)
    {
      if(m_bullets[i].m_free)
    {
        //是空闲的子弹，发射
       m_bullets[i].m_free=false;
       m_bullets[i].m_x=m_x+50;
       m_bullets[i].m_y=m_y-15;
       break;
      }
//
    }
}
void Heroplane::setPosition(int x, int y)
{
    m_x=x;
    m_y=y;
    m_Rect.moveTo(m_x,m_y);
}
