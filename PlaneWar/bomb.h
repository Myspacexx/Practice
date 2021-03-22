#ifndef BOMB_H
#define BOMB_H
#include<QPixmap>
#include"config.h"
#include<QVector>

class Bomb
{
public:
    Bomb();
    void updateInfo();


   QVector<QPixmap>m_pixArr;

    int m_x;
    int m_y;

    bool m_free;


    int m_recorder;
    int m_index;

};

#endif // BOMB_H
