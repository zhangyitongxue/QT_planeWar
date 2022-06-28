#include "projectile.h"

Projectile::Projectile(Proj_Type t, Projectile::DIR D, bool CreatedByPlayer)
{
    dir = static_cast<int>(D);
    isCreatedByPlayer = CreatedByPlayer;
    Active = true;

    if(CreatedByPlayer){
        Speed = PROJ_PLAYER_SPEED;
    }
    else {
        Speed = PROJ_ENEMY_SPEED;
    }

    QString p;
    switch(t){
    case Proj_Type::PROJ_BULLET:
        if(CreatedByPlayer){
            p = QString(PROJ_PLAYER_BULLET_PATH);
        }
        else {
            p = QString(PROJ_ENEMY_BULLET_PATH);
        }

        Damage = PROJ_BULLET_DAMAGE;
        break;
    case Proj_Type::PROJ_MISSILE:
        if(CreatedByPlayer){
            p = QString(PROJ_PLAYER_MISSILE_PATH);
        }
        else {
            p = QString(PROJ_ENEMY_MISSILE_PATH);
        }

        Damage = PROJ_MISSILE_DAMAGE;
        break;
    }


    QPixmap pix;
    bool ret = pix.load(p);
    if(!ret){
        qDebug() << p << "发射物图像加载失败";
    }
    else{
        this->setFixedSize(pix.width(), pix.height());
        // this->setStyleSheet("QLabel{border:0px;}");
        this->setPixmap(pix);
    }

    // 加边框，方便玩家躲避碰撞，但是很丑 TaT
    this->setFrameShape(QFrame::Box);
    this->setFrameShadow(QFrame::Sunken);

}

//Projectile::~Projectile()
//{
//    qDebug() << "Proj destruct, x = " << this->x() << "y = " << this->y();
//}

bool Projectile::belongToPlayer()
{
    return isCreatedByPlayer;
}

int Projectile::getDamage()
{
    return Damage;
}

Projectile::Proj_Type Projectile::getType()
{
    return type;
}

void Projectile::updatePos()
{
    int tar_X = this->x() + Speed * dx[dir];
    int tar_Y = this->y() + Speed * dy[dir];
    this->move(tar_X, tar_Y);
}

bool Projectile::isActive()
{
    return Active;
}

void Projectile::setActive(bool flag)
{
    Active = flag;
}
