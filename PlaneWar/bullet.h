#ifndef BULLET_H
#define BULLET_H
#include<QPixmap>


class Bullet
{
public:
    Bullet();
    void updatePosition();

    QPixmap m_bullect;

    int m_x;
    int m_y;

    int m_speed;
//是否是限制状态
    bool m_free;

    QRect m_Rect;


};

#endif // BULLET_H
