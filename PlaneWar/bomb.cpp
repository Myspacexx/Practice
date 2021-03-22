#include "bomb.h"

Bomb::Bomb()
{


    QPixmap bomb;
    bomb.load(":/res/bomb-1.png");
    for(int i=0;i<=Bomb_max;i++)
    {
        QString str=QString(":/res/bomb-1.png").arg(i);
        m_pixArr.push_back(QPixmap(str));



    }

    m_x=0;
    m_y=0;

    m_free=true;


    m_recorder=0;
    m_index=0;

}

void Bomb::updateInfo()
{
    if(m_free)
    {
        return;
    }
    m_recorder++;
    if(m_recorder<Bomb_Interval)
    {
        return;
    }
    //重置记录
    m_recorder=0;
    //切换图片
    m_index++;
    if(m_index>Bomb_max-1)
    {
        m_index=0;
        m_free=true;
    }

}
