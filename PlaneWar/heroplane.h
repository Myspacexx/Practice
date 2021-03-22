#ifndef HEROPLANE_H
#define HEROPLANE_H
#include"config.h"
#include<QPixmap>
#include"bullet.h"

class Heroplane
{
public:
    Heroplane();
    //发射子弹
    void shoot();
    //设置位置
    void setPosition(int x,int y);
    int m_x ;
    int m_y;
    //加载飞机图片
    QPixmap m_plane;

    //触碰边框检测
    QRect m_Rect;
    Bullet m_bullets[Bullet_num];
    int  m_recorder;
};

#endif // HEROPLANE_H
