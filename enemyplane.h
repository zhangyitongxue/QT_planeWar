#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "plane.h"
#include<QtMath>
#include<complex>

class enemyPlane : public Plane
{
    Q_OBJECT
public:
    enum class DIR{
        RIGHT = 0,
        RIGHT_AND_UP = 1,
        UP = 2,
        LEFT_AND_UP = 3,
        LEFT = 4,
        LEFT_AND_DOWN = 5,
        DOWN = 6,
        RIGHT_AND_DOWN = 7,
    };
    enum class SpeedGrade{
        SLOW = 1,
        MEDIUM = 2,
        FAST = 3,
    };

    enum class Enemy_Type{
        ENEMY_NO_PROJ = 0,      // 无发射物的炮灰
        ENEMY_BULLET = 1,       // 能发射子弹的敌人
        ENEMY_MISSLE = 2,       // 能发射导弹的敌人
        ENEMY_BOSS_1 = 3,       // BOSS
    };
    enemyPlane(Enemy_Type t, int hp, DIR D, SpeedGrade = SpeedGrade::MEDIUM);

    void updatePos();

    bool isActive();

    void setActive(bool );

    Projectile * Fire();

private:
    const double Pi = 3.1415926;
    const double radians = static_cast<double>(45) * Pi / static_cast<double>(180) ;        // 第一个数是 移动的角度
    const double xRate = qCos(radians);
    const double yRate = qSin(radians);
    const double dx[8] = {1,  xRate,  0, -xRate, -1, -xRate,  0, xRate};
    const double dy[8] = {0, -yRate, -1, -yRate,  0,  yRate,  1, yRate};
    int dir;                    // 移动方向
    int Speed;
    Enemy_Type enemType;
    bool Active;

public:

signals:

public slots:
};

#endif // ENEMYPLANE_H
