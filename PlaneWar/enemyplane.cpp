#include "enemyplane.h"

Enemyplane::Enemyplane()
{
    enemy.load(":/res/img-plane_5.png");

    m_x=0;
    m_y=0;
    m_free=true;
    m_speed=Enemy_speed;
    m_Rect.setWidth(enemy.width());
    m_Rect.setHeight(enemy.height());
    m_Rect.moveTo(m_x,m_y);

}

void Enemyplane::updatePosition()
{
    if(m_free)
    {
        return;
    }
    m_y+=m_speed;
    m_Rect.moveTo(m_x,m_y);
    //边框检测
    if(m_y>=GAME_HEIGHT)
    {
        m_free=true;
    }



}
