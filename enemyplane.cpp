#include "enemyplane.h"

enemyPlane::enemyPlane(Enemy_Type t, int hp, DIR D, SpeedGrade g):Plane(enemImgP[ static_cast<int>(t) ], hp)
{
    enemType = t;
    Active = true;

    switch(g){
    case SpeedGrade::SLOW:
        Speed = ENEMY_SPEED_SLOW; break;
    case SpeedGrade::MEDIUM:
        Speed = ENEMY_SPEED_MEDIUM; break;
    case SpeedGrade::FAST:
        Speed = ENEMY_SPEED_FAST; break;
    }

    dir = static_cast<int>(D);

}

void enemyPlane::updatePos()
{
    int tar_X = this->x() + Speed * dx[dir];
    int tar_Y = this->y() + Speed * dy[dir];
    this->move(tar_X, tar_Y);
}

bool enemyPlane::isActive()
{
    return Active;
}

void enemyPlane::setActive(bool flag)
{
    Active = flag;
}

Projectile * enemyPlane::Fire()
{
    if(this->enemType == Enemy_Type::ENEMY_NO_PROJ){
        return NULL;
    }
    else if(this->enemType == Enemy_Type::ENEMY_BULLET ||
            this->enemType == Enemy_Type::ENEMY_MISSLE)
    {
        if(fireTime < ENEMY_FIRE_INTERVAL){
            fireTime++;
            return NULL;
        }
        else {
            fireTime = 0;

            // 发射物类型和创建的阵营归属
            Projectile::Proj_Type t = this->pType;
            bool createdByPlayer = false;
            Projectile::DIR d = Projectile::DIR::DOWN;

            Projectile * p = new Projectile(t, d, createdByPlayer);

            int pX, pY;
            pX = this->x() + this->width()/2 - p->width()/2;
            pY = this->y() + this->height();

            p->move(pX, pY);

            return p;
        }
    }
    else {
        return NULL;
    }
}
