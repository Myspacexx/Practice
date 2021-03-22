#include "bullet.h"
#include"config.h"
Bullet::Bullet()
{

    m_bullect.load(":/res/bullet_11.png");
    //子弹初始位置
    m_x=GAME_WIDTH*0.5-m_bullect.width()*0.5;
    m_y=GAME_HEIGHT-30;
    //子弹空闲
    m_free=true;
    //速度
    m_speed=BULLECT_SCROLL_SPEED;
    //碰撞检测
    m_Rect.setWidth(m_bullect.width());
    m_Rect.setHeight(m_bullect.height());
    m_Rect.moveTo(m_x,m_y);
}

void Bullet::updatePosition()
{
    if(m_free)
    {
        return;
    }
    //子弹向上移动
    m_y-=m_speed;
    m_Rect.moveTo(m_x,m_y);
    //边框检测
    if(m_y<=-m_Rect.height())
    {
        m_free=true;
    }
}
