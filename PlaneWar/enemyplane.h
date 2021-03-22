#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include"config.h"
#include<QPixmap>
class Enemyplane
{
public:
    Enemyplane();
    //创建敌机对象
    QPixmap enemy;

    //更新坐标
    void updatePosition();
    //飞机坐标
    int m_x;
    int m_y;
    //碰撞检测
    QRect m_Rect;
    //碰撞状态
    bool m_free;
    //出现速度

    int m_speed;




};

#endif // ENEMYPLANE_H
